/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
*/

#define LANGUAGE_TESTING
#ifdef LANGUAGE_TESTING
  static int ct = 1;
  static int speed = 5;
#endif


// Include the usual stuff
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


// Specific watch face includes
#include "lgs_config.h"
#include "lgs_languages.h"


// Define the watch face structure
PBL_APP_INFO( MY_UUID, LGS_APP_NAME, "Little Gem Software", 1, 4, RESOURCE_ID_IMAGE_MENU_ICON, APP_INFO_WATCH_FACE );


// All UI elements
Window        window;
BmpContainer  background_image;
BmpContainer  line_image;
TextLayer     text_time_layer;
TextLayer     text_ampm_layer;
TextLayer     text_days_layer;
TextLayer     text_today_layer;
TextLayer     text_date_layer;
TextLayer     text_week_layer;
GFont         font_time;
GFont         font_date;
GFont         font_days;


// Define layer rectangles (x, y, width, height)
GRect TIME_RECT   = ConstantGRect(  9,   8, 124, 45 );
GRect AMPM_RECT   = ConstantGRect( 51,  55,  40, 16 );
GRect DATE_RECT   = ConstantGRect(  0, 100, 144, 25 );
GRect WEEK_RECT   = ConstantGRect(  0, 130, 144, 25 );
GRect DAYS_RECT   = ConstantGRect(  0,  76, 144, 13 );


// Define placeholders for time and date
static char time_text[] = "00:00";
static char ampm_text[] = "AM";


// Work around to handle initial display for minutes to work when testing units_changed
static bool first_cycle = true;


/*
  Setup new TextLayer
*/
void setup_text_layer( TextLayer *newLayer, GRect rect, GTextAlignment align , GFont font ) {
  text_layer_init( newLayer, rect );
  text_layer_set_text_color( newLayer, GColorWhite );
  text_layer_set_background_color( newLayer, GColorClear );
  text_layer_set_text_alignment( newLayer, align );
  text_layer_set_font( newLayer, font );
}


/*
  Handle tick event
*/
void handle_tick( AppContextRef ctx, PebbleTickEvent *event ) {
  (void)ctx;

  // Get the current time
  PblTm currentTime;
  get_time( &currentTime );

  // Handle day change
  if ( ( ( event->units_changed & DAY_UNIT ) == DAY_UNIT ) || first_cycle ) {
    // Update text layer for current day
    int today = currentTime.tm_wday - 1; if ( today < 0 ) { today = 6; }
    text_layer_set_text_alignment( &text_today_layer, day_align[today] );
    layer_set_frame( &text_today_layer.layer, day_rect[today] );
    text_layer_set_text( &text_today_layer, day_names[today] );

    #ifdef LANGUAGE_EN
      string_format_time( date_text, sizeof( date_text ), format_date, &currentTime );
      strcat( date_text, ordinal_numbers[currentTime.tm_mday - 1] );
    #else
      string_format_time( date_text, sizeof( date_text ), format_date, &currentTime );
      strcat( date_text, month_names[currentTime.tm_mon] );    
    #endif

    text_layer_set_text( &text_date_layer, date_text );

    // Update week or day of the year (i.e. Week 15 or 2013-118)
    #if defined(FORMAT_DOTY) || defined(FORMAT_DDMMYY) || defined(FORMAT_MMDDYY) || defined(FORMAT_WXDX)
      string_format_time( alt_text, sizeof( alt_text ), alt_format, &currentTime );
      text_layer_set_text( &text_week_layer, alt_text );
    #else
      string_format_time( week_text, sizeof( week_text ), format_week, &currentTime );
      text_layer_set_text( &text_week_layer, week_text );
    #endif
  }

  // Handle time (hour and minute) change
  if ( ( ( event->units_changed & MINUTE_UNIT ) == MINUTE_UNIT ) || first_cycle ) {
    // Display hours (i.e. 18 or 06)
    string_format_time( time_text, sizeof( time_text ), clock_is_24h_style() ? "%H:%M" : "%I:%M", &currentTime );

    // Remove leading zero (only in 12h-mode)
    if ( !clock_is_24h_style() && (time_text[0] == '0') ) {
      memmove( time_text, &time_text[1], sizeof( time_text ) - 1 );
    }

    text_layer_set_text( &text_time_layer, time_text );

    // Update AM/PM indicator (i.e. AM or PM or nothing when using 24-hour style)
    string_format_time( ampm_text, sizeof( ampm_text ), clock_is_24h_style() ? "\0" : "%p", &currentTime );
    text_layer_set_text( &text_ampm_layer, ampm_text );
  }

#ifdef LANGUAGE_TESTING
    // Walk though all the days of the week
    text_layer_set_text_alignment( &text_today_layer, day_align[ct] );
    layer_set_frame( &text_today_layer.layer, day_rect[ct] );
    text_layer_set_text( &text_today_layer, day_names[ct] );

    if ( currentTime.tm_sec % speed == 0 ) { ct++; }
    if ( ct == 7 ) { ct = 0; }
#endif

  // Clear
  if ( first_cycle ) {
    first_cycle = false;
  }
}


/*
  Initialization
*/
void handle_init( AppContextRef ctx ) {
  (void)ctx;

  // ct = 0;
  window_init( &window, "LGS Watch" );
  window_stack_push( &window, true );

  // Load resources
  resource_init_current_app( &APP_RESOURCES );

  // Load background image
  bmp_init_container( RESOURCE_ID_IMAGE_BACKGROUND, &background_image );

  // Add background image to the window
  layer_add_child( &window.layer, &background_image.layer.layer );

  // Adjust GRect for Hours, Minutes and Blink to compensate for missing AM/PM indicator
  if ( clock_is_24h_style() ) {
    TIME_RECT.origin.y = TIME_RECT.origin.y + 6;
  }

  // Load custom fonts
  font_time = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_SUBSET_40 ) );
  font_date = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_20 ) );
  font_days = fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_12 ) );

  // Setup time layer
  setup_text_layer( &text_time_layer, TIME_RECT, GTextAlignmentCenter, font_time );
  layer_add_child( &window.layer, &text_time_layer.layer );

  // Setup AM/PM name layer
  setup_text_layer( &text_ampm_layer, AMPM_RECT, GTextAlignmentCenter, font_days );
  layer_add_child( &window.layer, &text_ampm_layer.layer );

  // Setup days line layer
  setup_text_layer( &text_days_layer, DAYS_RECT, GTextAlignmentCenter, font_days );
  layer_add_child( &window.layer, &text_days_layer.layer );
  text_layer_set_text( &text_days_layer, day_line );

  // Setup current day layer
  setup_text_layer( &text_today_layer, day_rect[0], GTextAlignmentCenter, font_days );
  text_layer_set_text_color( &text_today_layer, GColorBlack );
  text_layer_set_background_color( &text_today_layer, GColorWhite );
  layer_add_child( &window.layer, &text_today_layer.layer );

  // Setup date layer
  setup_text_layer( &text_date_layer, DATE_RECT, GTextAlignmentCenter, font_date );
  layer_add_child( &window.layer, &text_date_layer.layer );

  // Setup week layer
  setup_text_layer( &text_week_layer, WEEK_RECT, GTextAlignmentCenter, font_date );
  layer_add_child( &window.layer, &text_week_layer.layer );

  // Draw image to divide day box from top line
  bmp_init_container( RESOURCE_ID_IMAGE_LINE, &line_image );
  line_image.layer.layer.frame.origin.x = 2;
  line_image.layer.layer.frame.origin.y = 77;
  layer_add_child( &window.layer, &line_image.layer.layer );

  // Force tick event (to avoid blank screen)
  handle_tick( ctx, NULL );
}


/*
  dealloc
*/
void handle_deinit( AppContextRef ctx ) {
  (void)ctx;

  // Unload bitmaps
  bmp_deinit_container( &background_image );
  bmp_deinit_container( &line_image );

  // Unload custom fonts
  fonts_unload_custom_font( font_time );
  fonts_unload_custom_font( font_date );
  fonts_unload_custom_font( font_days );
}


/*
  Main process
*/
void pbl_main( void *params ) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,
    .tick_info = {
      .tick_handler = &handle_tick,
#ifdef LANGUAGE_TESTING
      .tick_units = SECOND_UNIT
#else
      .tick_units = MINUTE_UNIT
#endif
    }
  };
  app_event_loop( params, &handlers );
}