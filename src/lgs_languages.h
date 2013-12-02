/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
  Pebble SDK  : 2.0-BETA2
*/

#pragma once


// Forward declarations
void update_time();


// This works around the inability to use the current GRect macro for constants
#define ConstantGRect(x, y, w, h) {{(x), (y)}, {(w), (h)}}


// Day line information
static const char *day_lines[] = { "Mo Tu We Th Fr Sa Su"
                                 , "Ma Di Wo Do Vr Za Zo"
                                 , "Mo Di Mi Do Fr Sa So"
                                 , "Lu Ma Me Je Ve Sa Di"
                                 , "Po Vt Sr Ce Pe Su Ne"
                                 , "Lu Ma Mi Ju Vi Sá Do"
                                 , "Lu Ma Me Gi Ve Sa Do"
                                 , "Ma Ti On To Fr Lø Sø"
                                 , "Ma Ti Ke To Pe La Su"
                                 };


// GRect for day highlights
static const GRect highlight_rect[][7] = { { ConstantGRect( 4, 78, 20, 11 ) , ConstantGRect( 26, 78, 16, 11 ) , ConstantGRect( 46, 78, 20, 11 ) , ConstantGRect( 68, 78, 16, 11 ) , ConstantGRect( 88, 78, 14, 11 ) , ConstantGRect( 105, 78, 15, 11 ) , ConstantGRect( 124, 78, 15, 11 ) }
                                         , { ConstantGRect( 3, 78, 20, 11 ) , ConstantGRect( 27, 78, 12, 11 ) , ConstantGRect( 43, 78, 20, 11 ) , ConstantGRect( 67, 78, 16, 11 ) , ConstantGRect( 87, 78, 15, 11 ) , ConstantGRect( 105, 78, 16, 11 ) , ConstantGRect( 125, 78, 16, 11 ) }
                                         , { ConstantGRect( 6, 78, 20, 11 ) , ConstantGRect( 30, 78, 12, 11 ) , ConstantGRect( 46, 78, 16, 11 ) , ConstantGRect( 66, 78, 16, 11 ) , ConstantGRect( 86, 78, 14, 11 ) , ConstantGRect( 103, 78, 15, 11 ) , ConstantGRect( 122, 78, 15, 11 ) }
                                         , { ConstantGRect( 3, 78, 15, 11 ) , ConstantGRect( 22, 78, 20, 11 ) , ConstantGRect( 46, 78, 20, 11 ) , ConstantGRect( 69, 78, 16, 11 ) , ConstantGRect( 89, 78, 16, 11 ) , ConstantGRect( 109, 78, 15, 11 ) , ConstantGRect( 128, 78, 12, 11 ) }
                                         , { ConstantGRect( 6, 78, 16, 11 ) , ConstantGRect( 26, 78, 14, 11 ) , ConstantGRect( 44, 78, 14, 11 ) , ConstantGRect( 61, 78, 16, 11 ) , ConstantGRect( 81, 78, 16, 11 ) , ConstantGRect( 101, 78, 15, 11 ) , ConstantGRect( 120, 78, 17, 11 ) }
                                         , { ConstantGRect( 5, 78, 15, 11 ) , ConstantGRect( 24, 78, 20, 11 ) , ConstantGRect( 48, 78, 16, 11 ) , ConstantGRect( 67, 78, 16, 11 ) , ConstantGRect( 87, 78, 12, 11 ) , ConstantGRect( 103, 78, 15, 11 ) , ConstantGRect( 122, 78, 16, 11 ) }
                                         , { ConstantGRect( 3, 78, 15, 11 ) , ConstantGRect( 22, 78, 20, 11 ) , ConstantGRect( 46, 78, 20, 11 ) , ConstantGRect( 70, 78, 12, 11 ) , ConstantGRect( 86, 78, 16, 11 ) , ConstantGRect( 106, 78, 15, 11 ) , ConstantGRect( 125, 78, 16, 11 ) }
                                         , { ConstantGRect( 8, 78, 20, 11 ) , ConstantGRect( 30, 78, 12, 11 ) , ConstantGRect( 46, 78, 16, 11 ) , ConstantGRect( 64, 78, 16, 11 ) , ConstantGRect( 84, 78, 14, 11 ) , ConstantGRect( 101, 78, 15, 11 ) , ConstantGRect( 120, 78, 15, 11 ) }
                                         , { ConstantGRect( 6, 78, 20, 11 ) , ConstantGRect( 28, 78, 12, 11 ) , ConstantGRect( 44, 78, 17, 11 ) , ConstantGRect( 63, 78, 16, 11 ) , ConstantGRect( 83, 78, 16, 11 ) , ConstantGRect( 103, 78, 15, 11 ) , ConstantGRect( 122, 78, 15, 11 ) }
                                         };


// Month names
static const char *month_names_arr[][12] = { { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" }
                                           , { "jan", "feb", "mrt", "apr", "mei", "jun", "jul", "aug", "sep", "okt", "nov", "dec" }
                                           , { "Jan", "Feb", "März", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" }
                                           , { "janv", "févr", "mars", "avr", "mai", "juin", "juil", "août", "sept", "oct", "nov", "déc" }
                                           , { "siječanj", "veljača", "ožujak", "travanj", "svibanj", "lipanj", "srpanj", "kolovoz", "rujan", "listopad", "studeni", "prosinac" }
                                           , { "enero", "feb", "marzo", "abr", "mayo", "jun", "jul", "agosto", "sept", "oct", "nov", "dic" }
                                           , { "genn", "febbr", "mar", "apr", "magg", "giugno", "luglio", "ag", "sett", "ott", "nov", "dic" }
                                           , { "Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Des" }
                                           , { "tammikuu", "helmikuu", "maaliskuu", "huhtikuu", "toukokuu", "kesäkuu", "heinäkuu", "elokuu", "syyskuu", "lokakuu", "marraskuu", "joulukuu" }
                                           };


// Format week
static const char *week_formats[] = { "Week %V"
                                    , "Week %V"
                                    , "Woche %V"
                                    , "Semaine %V"
                                    , "%V. tjedan"
                                    , "%V. semana"
                                    , "%V. Setti."
                                    , "Uke %V"
                                    , "VKO %V"
                                    };


// Format date
static const char *date_formats[] = { "%b %e"
                                    , "%e "
                                    , "%e. "
                                    , "%e "
                                    , "%e. "
                                    , "%e. "
                                    , "%e. "
                                    , "%e. "
                                    , "%e. "
                                    };


// Formats for second line
static const char *alt_formats[] = { "Week %V"
                                   , "%Y-%j"
                                   , "%d/%m/%y"
                                   , "%m/%d/%y"
                                   , "W%V D%j"
                                   };


static char week_text[] = "               ";
static char date_text[] = "               ";
static char alt_text[]  = "               ";


// Ordinal numbers
static const char *ordinal_numbers[] = { "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th"
                                       , "th", "th", "th", "th", "th", "th", "th", "th", "th", "th"
                                       , "st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th"
                                       , "st" };