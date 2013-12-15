/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
  Pebble SDK  : 2.0-BETA2
*/

#pragma once

// Some handy macros
#define ConstantGRect(x, y, w, h) {{(x), (y)}, {(w), (h)}}
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


// Forward declarations
void update_time();


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
                                 , "Pa Sa Ça Pe Cu Cu Pa"
                                 , "De Tr Te Pé Pa Sá Ku"
                                 };


// GRect for day highlights (fixed y=78, h=11)
typedef struct GBox { int16_t x; int16_t w; } GBox;
#define GBox(x, w) {(x), (w)}
static const GBox highlight_box[][7] = { { GBox( 4, 20 ), GBox( 26, 16 ), GBox( 46, 20 ), GBox( 68, 16 ), GBox( 88, 14 ), GBox( 105, 15 ), GBox( 124, 15 ) }
                                       , { GBox( 3, 20 ), GBox( 27, 12 ), GBox( 43, 20 ), GBox( 67, 16 ), GBox( 87, 15 ), GBox( 105, 16 ), GBox( 125, 16 ) }
                                       , { GBox( 6, 20 ), GBox( 30, 12 ), GBox( 46, 16 ), GBox( 66, 16 ), GBox( 86, 14 ), GBox( 103, 15 ), GBox( 122, 15 ) }
                                       , { GBox( 3, 15 ), GBox( 22, 20 ), GBox( 46, 20 ), GBox( 69, 16 ), GBox( 89, 16 ), GBox( 109, 15 ), GBox( 128, 12 ) }
                                       , { GBox( 6, 16 ), GBox( 26, 14 ), GBox( 44, 14 ), GBox( 61, 16 ), GBox( 81, 16 ), GBox( 101, 15 ), GBox( 120, 17 ) }
                                       , { GBox( 5, 15 ), GBox( 24, 20 ), GBox( 48, 16 ), GBox( 67, 16 ), GBox( 87, 12 ), GBox( 103, 15 ), GBox( 122, 16 ) }
                                       , { GBox( 3, 15 ), GBox( 22, 20 ), GBox( 46, 20 ), GBox( 70, 12 ), GBox( 86, 16 ), GBox( 106, 15 ), GBox( 125, 16 ) }
                                       , { GBox( 8, 20 ), GBox( 30, 12 ), GBox( 46, 16 ), GBox( 64, 16 ), GBox( 84, 14 ), GBox( 101, 15 ), GBox( 120, 15 ) }
                                       , { GBox( 6, 20 ), GBox( 28, 12 ), GBox( 44, 17 ), GBox( 63, 16 ), GBox( 83, 16 ), GBox( 103, 15 ), GBox( 122, 15 ) }
                                       , { GBox( 4, 16 ), GBox( 24, 15 ), GBox( 43, 16 ), GBox( 63, 16 ), GBox( 83, 16 ), GBox( 103, 16 ), GBox( 123, 16 ) }
                                       , { GBox( 7, 16 ), GBox( 25, 15 ), GBox( 41, 16 ), GBox( 61, 16 ), GBox( 81, 16 ), GBox( 101, 15 ), GBox( 120, 17 ) }
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
                                           , { "Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran", "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık" }
                                           , { "Ianuários", "Fevruários", "Mártios", "Aprílios", "Máios", "Iúnios", "Iúlios", "Avghustos", "Septémvrios", "Októvrios", "Noémvrios", "Thekémvrios" }
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
                                    , "Hafta %V"
                                    , "Evdomáda %V"
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
                                    , "%e "
                                    , "%e "
                                    };


// Formats for second line
static const char *alt_formats[] = { "<See date_formats[]>"
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