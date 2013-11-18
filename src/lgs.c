/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
  Pebble SDK  : 2.0-BETA2
*/

// #define LANGUAGE_TESTING
#ifdef LANGUAGE_TESTING
  static int ct = 1;
  static int speed = 5;
#endif


// Include the usual stuff
#include <pebble.h>


// Specific watch face includes
#include "lgs_config.h"
#include "lgs_languages.h"


// All UI elements
static Window      *window;
static GBitmap     *background_image;
static BitmapLayer *background_layer;
static GBitmap     *line_image;
static BitmapLayer *line_layer;
static TextLayer   *text_time_layer;
static TextLayer   *text_ampm_layer;
static TextLayer   *text_days_layer;
static TextLayer   *text_today_layer;
static TextLayer   *text_date_layer;
static TextLayer   *text_week_layer;


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
static TextLayer * setup_text_layer( GRect rect, GTextAlignment align , GFont font ) {
  TextLayer *newLayer = text_layer_create( rect );
  text_layer_set_text_color( newLayer, GColorWhite );
  text_layer_set_background_color( newLayer, GColorClear );
  text_layer_set_text_alignment( newLayer, align );
  text_layer_set_font( newLayer, font );

  return newLayer;
}


/*
  Handle tick event
*/
void handle_tick( struct tm *tick_time, TimeUnits units_changed ) {
  // Handle day change
  if ( ( ( units_changed & DAY_UNIT ) == DAY_UNIT ) || first_cycle ) {
    // Update text layer for current day
    int today = tick_time->tm_wday - 1; if ( today < 0 ) { today = 6; }
    text_layer_set_text_alignment( text_today_layer, day_align[today] );
    layer_set_frame( text_layer_get_layer(text_today_layer), day_rect[today] );
    text_layer_set_text( text_today_layer, day_names[today] );

    #ifdef LANGUAGE_EN
      strftime( date_text, sizeof( date_text ), format_date, tick_time );
      strcat( date_text, ordinal_numbers[tick_time->tm_mday - 1] );
    #else
      strftime( date_text, sizeof( date_text ), format_date, tick_time );
      strcat( date_text, month_names[tick_time->tm_mon] );    
    #endif

    text_layer_set_text( text_date_layer, date_text );

    // Update week or day of the year (i.e. Week 15 or 2013-118)
    #if defined(FORMAT_DOTY) || defined(FORMAT_DDMMYY) || defined(FORMAT_MMDDYY) || defined(FORMAT_WXDX)
      strftime( alt_text, sizeof( alt_text ), alt_format, tick_time );
      text_layer_set_text( text_week_layer, alt_text );
    #else
      strftime( week_text, sizeof( week_text ), format_week, tick_time );
      text_layer_set_text( text_week_layer, week_text );
    #endif
  }

  // Handle time (hour and minute) change
  if ( ( ( units_changed & MINUTE_UNIT ) == MINUTE_UNIT ) || first_cycle ) {
    // Display hours (i.e. 18 or 06)
    strftime( time_text, sizeof( time_text ), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time );

    // Remove leading zero (only in 12h-mode)
    if ( !clock_is_24h_style() && (time_text[0] == '0') ) {
      memmove( time_text, &time_text[1], sizeof( time_text ) - 1 );
    }

    text_layer_set_text( text_time_layer, time_text );

    // Update AM/PM indicator (i.e. AM or PM or nothing when using 24-hour style)
    // strftime( ampm_text, sizeof( ampm_text ), clock_is_24h_style() ? "\0" : "%p", tick_time );
    strftime( ampm_text, sizeof( ampm_text ), clock_is_24h_style() ? "" : "%p", tick_time );
    text_layer_set_text( text_ampm_layer, ampm_text );
  }

#ifdef LANGUAGE_TESTING
    // Walk though all the days of the week
    text_layer_set_text_alignment( text_today_layer, day_align[ct] );
    layer_set_frame( text_layer_get_layer(text_today_layer), day_rect[ct] );
    text_layer_set_text( text_today_layer, day_names[ct] );

    if ( tick_time->tm_sec % speed == 0 ) { ct++; }
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
void handle_init( void ) {
  window = window_create();
  window_stack_push( window, true );
  Layer *window_layer = window_get_root_layer( window );

  // Background image
  background_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BACKGROUND );
  background_layer = bitmap_layer_create( layer_get_frame( window_layer ) );
  bitmap_layer_set_bitmap( background_layer, background_image );
  layer_add_child( window_layer, bitmap_layer_get_layer( background_layer ) );

  // Adjust GRect for Hours, Minutes and Blink to compensate for missing AM/PM indicator
  if ( clock_is_24h_style() ) {
    TIME_RECT.origin.y = TIME_RECT.origin.y + 6;
  }

  // Setup time layer
  text_time_layer = setup_text_layer( TIME_RECT, GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_SUBSET_40 ) ) );
  layer_add_child( window_layer, text_layer_get_layer(text_time_layer) );

  // Setup AM/PM name layer
  text_ampm_layer = setup_text_layer( AMPM_RECT, GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_12 ) ) );
  layer_add_child( window_layer, text_layer_get_layer(text_ampm_layer) );

  // Setup days line layer
  text_days_layer = setup_text_layer( DAYS_RECT, GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_12 ) ) );
  layer_add_child( window_layer, text_layer_get_layer(text_days_layer) );
  text_layer_set_text( text_days_layer, day_line );

  // Setup current day layer
  text_today_layer = setup_text_layer( day_rect[0], GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_12 ) ) );
  text_layer_set_text_color( text_today_layer, GColorBlack );
  text_layer_set_background_color( text_today_layer, GColorWhite );
  layer_add_child( window_layer, text_layer_get_layer(text_today_layer) );

  // Setup date layer
  text_date_layer = setup_text_layer( DATE_RECT, GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_20 ) ) );
  layer_add_child( window_layer, text_layer_get_layer(text_date_layer) );

  // Setup week layer
  text_week_layer = setup_text_layer( WEEK_RECT, GTextAlignmentCenter, fonts_load_custom_font( resource_get_handle( RESOURCE_ID_FONT_CHICAGO_20 ) ) );
  layer_add_child( window_layer, text_layer_get_layer(text_week_layer) );

  // Draw image to divide day box from top line
  line_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_LINE );
  GRect frame = (GRect) {
    .origin = {2,77},
    .size = (line_image)->bounds.size
  };

  // line_layer = bitmap_layer_create( layer_get_frame( window_layer ) );
  line_layer = bitmap_layer_create( frame );
  bitmap_layer_set_bitmap( line_layer, line_image );
  layer_add_child( window_layer, bitmap_layer_get_layer( line_layer ) );

  // Subscribe to services
  #ifdef LANGUAGE_TESTING
    tick_timer_service_subscribe( SECOND_UNIT, handle_tick );
  #else
    tick_timer_service_subscribe( MINUTE_UNIT, handle_tick );
  #endif

  // Avoids a blank screen on watch start.
  time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
  handle_tick( tick_time, MINUTE_UNIT );
}


/*
  dealloc
*/
void handle_deinit( void ) {
  // Subscribe from services
  tick_timer_service_unsubscribe();

  // Destroy image objects
  layer_remove_from_parent( bitmap_layer_get_layer( background_layer ) );
  bitmap_layer_destroy( background_layer );
  gbitmap_destroy( background_image );
  layer_remove_from_parent( bitmap_layer_get_layer( line_layer ) );
  bitmap_layer_destroy( line_layer );
  gbitmap_destroy( line_image );

  // Destroy tex tobjects
  text_layer_destroy(text_time_layer);
  text_layer_destroy(text_ampm_layer);
  text_layer_destroy(text_days_layer);
  text_layer_destroy(text_today_layer);
  text_layer_destroy(text_date_layer);
  text_layer_destroy(text_week_layer);

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