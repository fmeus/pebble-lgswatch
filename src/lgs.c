/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
  Pebble SDK  : 2.0-BETA2
*/

#include <pebble.h>
#include "lgs_languages.h"


// Setting values
static enum statusKeys { STATUS_OFF = 0, STATUS_ON } current_status;
static enum formatKeys { FORMAT_WEEK = 0, FORMAT_DOTY, FORMAT_DDMMYY, FORMAT_MMDDYY, FORMAT_WXDX } current_format;
static enum languageKeys { LANG_EN = 0, LANG_NL, LANG_DE, LANG_FR, LANG_HR, LANG_ES, LANG_IT, LANG_NO, LANG_FI } current_language;


// Setting keys
enum settingKeys {
  SETTING_STATUS_KEY = 0x0,
  SETTING_LANGUAGE_KEY = 0x1,
  SETTING_FORMAT_KEY = 0x2
};


// All UI elements
static Window         *window;
static GBitmap        *background_image;
static GBitmap        *battery_image;
static GBitmap        *bluetooth_image;
static BitmapLayer    *background_layer;
static BitmapLayer    *battery_layer;
static BitmapLayer    *bluetooth_layer;
static TextLayer      *text_time_layer;
static TextLayer      *text_ampm_layer;
static TextLayer      *text_days_layer;
static TextLayer      *text_date_layer;
static TextLayer      *text_week_layer;
static GFont          *font_time;
static GFont          *font_days;
static GFont          *font_date;
static InverterLayer  *currentDayLayer;
static AppSync        app;
static uint8_t        sync_buffer[256];


// Define layer rectangles (x, y, width, height)
GRect TIME_RECT      = ConstantGRect(   9,   8, 124,  45 );
GRect AMPM_RECT      = ConstantGRect(  51,  55,  40,  16 );
GRect DATE_RECT      = ConstantGRect(   0, 105, 144,  25 );
GRect WEEK_RECT      = ConstantGRect(   0, 132, 144,  25 );
GRect DAYS_RECT      = ConstantGRect(   0,  76, 144,  13 );
GRect BATT_RECT      = ConstantGRect( 123,  94,  17,   9 );
GRect BT_RECT        = ConstantGRect(   4,  94,  17,   9 );
GRect EMPTY_RECT     = ConstantGRect(   0,   0,   0,   0 );
GRect OFF_DATE_RECT  = ConstantGRect(   0, 100, 144,  25 );
GRect OFF_WEEK_RECT  = ConstantGRect(   0, 130, 144,  25 );


// Define placeholders for time and date
static char time_text[] = "00:00";
static char ampm_text[] = "AM";


// Previous bluetooth connection status
static bool prev_bt_status = false;


#ifdef LANGUAGE_TESTING
  static int ct = 1;
  static int speed = 5;
#endif


/*
  Setup new TextLayer
*/
static TextLayer * setup_text_layer( GRect rect, GTextAlignment align , GFont font ) {
  TextLayer *newLayer = text_layer_create( rect );
  text_layer_set_text_color( newLayer, GColorWhite );
  text_layer_set_background_color( newLayer, GColorClear );
  text_layer_set_text_alignment( newLayer, align );
  text_layer_set_font( newLayer, font );

  return newLayer;
}


/*
  Handle bluetooth events
*/
void handle_bluetooth( bool connected ) {
  if ( bluetooth_image != NULL ) {
    gbitmap_destroy( bluetooth_image );
  }

  if ( connected ) {
    bluetooth_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BLUETOOTH );
  } else {
    bluetooth_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_NO_BLUETOOTH );
    if ( prev_bt_status != connected ) {
      vibes_short_pulse();
    }
  }

  prev_bt_status = connected;

  bitmap_layer_set_bitmap( bluetooth_layer, bluetooth_image );
}


/*
  Handle battery events
*/
void handle_battery( BatteryChargeState charge_state ) {
  if ( battery_image != NULL ) {
    gbitmap_destroy( battery_image );
  }

  if ( charge_state.is_charging ) {
    battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_CHARGING );
  } else {
    switch ( charge_state.charge_percent ) {
      case 0 ... 20:
        battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_000_020 );
        break;
      case 21 ... 40:
        battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_020_040 );
        break;
      case 41 ... 60:
        battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_040_060 );
        break;
      case 61 ... 80:
        battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_060_080 );
        break;
      case 81 ... 100:
        battery_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BATT_080_100 );
        break;
      }
  }

  bitmap_layer_set_bitmap( battery_layer, battery_image );
}


/*
  Update status indicators for the battery and bluetooth connection
*/
void update_status( void ) {
  handle_battery( battery_state_service_peek() );
  handle_bluetooth( bluetooth_connection_service_peek() );
}


/*
  Handle update in settings
*/
static void tuple_changed_callback( const uint32_t key, const Tuple* tuple_new, const Tuple* tuple_old, void* context ) {
  int value = tuple_new->value->uint8;  

  switch ( key ) {
    case SETTING_STATUS_KEY:
      persist_write_int( SETTING_STATUS_KEY, value );
      current_status = value;

      // Reposition status layers
      layer_set_frame( bitmap_layer_get_layer( battery_layer ), ( current_status == STATUS_ON ) ? BATT_RECT : EMPTY_RECT );
      layer_set_frame( bitmap_layer_get_layer( bluetooth_layer ), ( current_status == STATUS_ON ) ? BT_RECT : EMPTY_RECT );

      // Repasition date and week layers
      layer_set_frame( text_layer_get_layer( text_date_layer ), ( current_status == STATUS_ON ) ? DATE_RECT : OFF_DATE_RECT );
      layer_set_frame( text_layer_get_layer( text_week_layer ), ( current_status == STATUS_ON ) ? WEEK_RECT : OFF_WEEK_RECT );
      break;

    case SETTING_LANGUAGE_KEY:
      persist_write_int( SETTING_LANGUAGE_KEY, value );
      current_language = value;
      text_layer_set_text( text_days_layer, day_lines[current_language] );
      break;

    case SETTING_FORMAT_KEY:
      persist_write_int( SETTING_FORMAT_KEY, value );
      current_format = value;
      break;
  }

  // Refresh display
  update_time();
}


/*
  Handle errors
*/
static void app_error_callback( DictionaryResult dict_error, AppMessageResult app_message_error, void* context ) {
  APP_LOG( APP_LOG_LEVEL_DEBUG, "app error %d", app_message_error );
  vibes_double_pulse();
}


/*
  Handle tick events
*/
void handle_tick( struct tm *tick_time, TimeUnits units_changed ) {
  // Update text layer for current day
  int today = tick_time->tm_wday - 1; if ( today < 0 ) { today = 6; }
  layer_set_frame( inverter_layer_get_layer( currentDayLayer ), highlight_rect[current_language][today] );

  #ifdef LANGUAGE_TESTING
    layer_set_frame( inverter_layer_get_layer( currentDayLayer ), hightlight_rect[current_language][ct] );
    if ( tick_time->tm_sec % speed == 0 ) { ct++; }
    if ( ct == 7 ) { ct = 0; }
  #endif

  strftime( date_text, sizeof( date_text ), date_formats[current_language], tick_time );
  if ( current_language == LANG_EN ) {
    strcat( date_text, ordinal_numbers[tick_time->tm_mday - 1] );
  } else {
    strcat( date_text, month_names_arr[current_language][tick_time->tm_mon] );
  }
  text_layer_set_text( text_date_layer, date_text );

  // Update week or day of the year (i.e. Week 15 or 2013-118)
  if ( current_format == FORMAT_WEEK ) {
    strftime( week_text, sizeof( week_text ), week_formats[current_language], tick_time );
    text_layer_set_text( text_week_layer, week_text );
  } else {
    strftime( alt_text, sizeof( alt_text ), alt_formats[current_format], tick_time );
    text_layer_set_text( text_week_layer, alt_text );
  }

  // Display hours (i.e. 18 or 06)
  strftime( time_text, sizeof( time_text ), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time );

  // Remove leading zero (only in 12h-mode)
  if ( !clock_is_24h_style() && (time_text[0] == '0') ) {
    memmove( time_text, &time_text[1], sizeof( time_text ) - 1 );
  }
  text_layer_set_text( text_time_layer, time_text );

  // Update AM/PM indicator (i.e. AM or PM or nothing when using 24-hour style)
  strftime( ampm_text, sizeof( ampm_text ), clock_is_24h_style() ? "" : "%p", tick_time );
  text_layer_set_text( text_ampm_layer, ampm_text );

  // Update status information 
  if ( current_status == STATUS_ON ) {
    update_status();
  }
}

/*
  Force update of time
*/
void update_time() {
    // Get current time
  time_t now = time( NULL );
  struct tm *tick_time = localtime( &now );

  // Force update to avoid a blank screen at startup of the watchface
  handle_tick( tick_time, SECOND_UNIT );
}

/*
  Initialization
*/
void handle_init( void ) {
  window = window_create();
  window_stack_push( window, true );
  Layer *window_layer = window_get_root_layer( window );

  // Read persistent data
  if ( persist_exists( SETTING_STATUS_KEY ) ) {
    current_status = persist_read_int( SETTING_STATUS_KEY );
  } else {
    current_status = STATUS_ON;
  }
  if ( persist_exists( SETTING_LANGUAGE_KEY ) ) {
    current_language = persist_read_int( SETTING_LANGUAGE_KEY );
  } else {
    current_language = LANG_EN;
  }
  if ( persist_exists( SETTING_FORMAT_KEY ) ) {
    current_format = persist_read_int( SETTING_FORMAT_KEY );
  } else {
    current_format = FORMAT_WEEK;
  }

  // Read watchface settings from persistent data or use default values
  current_status = persist_exists( SETTING_STATUS_KEY ) ? persist_read_int( SETTING_STATUS_KEY ) : STATUS_ON;
  current_language = persist_exists( SETTING_LANGUAGE_KEY ) ? persist_read_int( SETTING_LANGUAGE_KEY ) : LANG_EN;
  current_format = persist_exists( SETTING_FORMAT_KEY ) ? persist_read_int( SETTING_FORMAT_KEY ) : FORMAT_WEEK;

  // Background image
  background_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BACKGROUND );
  background_layer = bitmap_layer_create( layer_get_frame( window_layer ) );
  bitmap_layer_set_bitmap( background_layer, background_image );
  layer_add_child( window_layer, bitmap_layer_get_layer( background_layer ) );

  // Initial settings
  Tuplet initial_values[] = { TupletInteger( SETTING_STATUS_KEY, current_status )
                            , TupletInteger( SETTING_LANGUAGE_KEY, current_language )
                            , TupletInteger( SETTING_FORMAT_KEY, current_format )
                            };

  // Open AppMessage to transfers
  app_message_open( 160, 160 );

  // Initialize AppSync
  app_sync_init( &app, sync_buffer
               , sizeof( sync_buffer )
               , initial_values
               , ARRAY_LENGTH( initial_values )
               , tuple_changed_callback
               , app_error_callback
               , NULL 
               );

  // Perform sync
  app_sync_set( &app, initial_values, ARRAY_LENGTH( initial_values ) );

  // Adjust GRect for Hours, Minutes and Blink to compensate for missing AM/PM indicator
  if ( clock_is_24h_style() ) {
    TIME_RECT.origin.y = TIME_RECT.origin.y + 6;
  }

  // Load fonts
  font_time = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_SUBSET_40 ) );
  font_days = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_12 ) );
  font_date = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_20 ) );

  // Setup time layer
  text_time_layer = setup_text_layer( TIME_RECT, GTextAlignmentCenter, font_time );
  layer_add_child( window_layer, text_layer_get_layer( text_time_layer ) );

  // Setup AM/PM name layer
  text_ampm_layer = setup_text_layer( AMPM_RECT, GTextAlignmentCenter, font_days );
  layer_add_child( window_layer, text_layer_get_layer( text_ampm_layer ) );

  // Setup days line layer
  text_days_layer = setup_text_layer( DAYS_RECT, GTextAlignmentCenter, font_days );
  layer_add_child( window_layer, text_layer_get_layer( text_days_layer ) );
  text_layer_set_text( text_days_layer, day_lines[current_language] );

  // Setup date layer
  text_date_layer = setup_text_layer( ( current_status == STATUS_ON ) ? DATE_RECT : OFF_DATE_RECT
                                    , GTextAlignmentCenter
                                    , font_date );
  layer_add_child( window_layer, text_layer_get_layer( text_date_layer ) );

  // Setup week layer
  text_week_layer = setup_text_layer( ( current_status == STATUS_ON ) ? WEEK_RECT : OFF_WEEK_RECT
                                    , GTextAlignmentCenter
                                    , font_date );
  layer_add_child( window_layer, text_layer_get_layer( text_week_layer ) );

  // Setup battery layer
  battery_layer = bitmap_layer_create( ( current_status == STATUS_ON ) ? BATT_RECT : EMPTY_RECT );
  layer_add_child( window_layer, bitmap_layer_get_layer( battery_layer ) );

  // Setup bluetooth layer
  bluetooth_layer = bitmap_layer_create( ( current_status == STATUS_ON ) ? BT_RECT : EMPTY_RECT );
  layer_add_child( window_layer, bitmap_layer_get_layer( bluetooth_layer ) );

  // Add inverter layer (indicator for the current day of the week)
  currentDayLayer = inverter_layer_create( EMPTY_RECT );
  layer_add_child( window_layer, inverter_layer_get_layer( currentDayLayer ) );

  // Subscribe to services
  tick_timer_service_subscribe( SECOND_UNIT, handle_tick );

  // Force update to avoid a blank screen at startup of the watchface
  update_time();
}


/*
  Destroy GBitmap and BitmapLayer
*/
void destroy_graphics( GBitmap *image, BitmapLayer *layer ) {
  layer_remove_from_parent( bitmap_layer_get_layer( layer ) );
  bitmap_layer_destroy( layer );
  if ( image != NULL ) {
    gbitmap_destroy( image );
  }
}


/*
  dealloc
*/
void handle_deinit( void ) {
  // Unsubscribe from services
  tick_timer_service_unsubscribe();

  // Destroy image objects
  destroy_graphics( background_image, background_layer );
  destroy_graphics( battery_image, battery_layer );
  destroy_graphics( bluetooth_image, bluetooth_layer );

  // Destroy text objects
  text_layer_destroy( text_time_layer );
  text_layer_destroy( text_ampm_layer );
  text_layer_destroy( text_days_layer );
  text_layer_destroy( text_date_layer );
  text_layer_destroy( text_week_layer );

  // Destroy inverter layer
  inverter_layer_destroy( currentDayLayer );
  
  // Destroy font objects
  fonts_unload_custom_font( font_time );
  fonts_unload_custom_font( font_days );
  fonts_unload_custom_font( font_date );

  // Clean up AppSync system
  app_sync_deinit( &app );

  // Destroy window
  window_destroy( window );
}


/*
  Main process
*/
int main( void ) {
  handle_init();
  app_event_loop();
  handle_deinit();
}