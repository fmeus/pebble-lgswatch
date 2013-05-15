/*
  Project     : LGS Watch watchface
  Copyright   : Copyright (c) 2011-2013 Little Gem Software. All rights reserved.
  Revision    : $Id: lgs_languages.h 1077 2013-05-06 08:28:02Z fmeus_lgs $

  Data collected from http://www.tuxx.nl/maandnamen/talen/
*/

// This works around the inability to use the current GRect macro for constants. (Taken from drop_zone.c)
#define ConstantGRect(x, y, w, h) {{(x), (y)}, {(w), (h)}}


// Special configuration for the information displayed on the last line of the watchface
#if defined(FORMAT_DOTY)
	#define MY_UUID { 0xFC, 0x3F, 0x2F, 0x4D, 0xD1, 0x0B, 0x4B, 0xD4, 0xB4, 0xF1, 0x97, 0xA2, 0xA1, 0x38, 0x22, 0x5D }

	static char alt_text[] = "0000-000";
	static char alt_format[] = "%Y-%j";
#elif defined(FORMAT_DDMMYY)
	#define MY_UUID { 0x2C, 0xC6, 0xAA, 0xA0, 0x88, 0x87, 0x47, 0x20, 0x88, 0x7A, 0x51, 0xA9, 0xA1, 0x68, 0xFE, 0xC6 }

	static char alt_text[] = "00/00/00";
	static char alt_format[] = "%d/%m/%y";
#elif defined(FORMAT_MMDDYY)
	#define MY_UUID { 0xF0, 0xD0, 0x40, 0x92, 0x5B, 0xB9, 0x40, 0x06, 0xB0, 0x7C, 0x4C, 0x07, 0xCE, 0x39, 0xA0, 0xA0 }

	static char alt_text[] = "00/00/00";
	static char alt_format[] = "%m/%d/%y";
#elif defined(FORMAT_WXDX)
	#define MY_UUID { 0xA8, 0x1A, 0xCC, 0x45, 0xD7, 0xC4, 0x49, 0x5F, 0xA6, 0x18, 0x23, 0xCF, 0x06, 0x54, 0xDD, 0x76 }

	static char alt_text[] = "W00 D000";
	static char alt_format[] = "W%V D%j";
#elif defined(FORMAT_WEEK)
	#define MY_UUID { 0x52, 0xD5, 0x92, 0x34, 0xA5, 0x4B, 0x4D, 0xA1, 0xB0, 0x48, 0x5C, 0x5E, 0xC1, 0x21, 0xF5, 0x4D }
#endif

// Additional pre-generated UUIDs (one for each language version)
// #define MY_UUID { 0x29, 0x15, 0xA3, 0x4A, 0xC0, 0xEC, 0x4D, 0xCA, 0xBE, 0x00, 0x3B, 0x27, 0x38, 0x18, 0x88, 0x9D }
// #define MY_UUID { 0x3C, 0x95, 0x78, 0x22, 0xEF, 0x01, 0x4E, 0x07, 0x88, 0x67, 0x11, 0x24, 0x53, 0xB1, 0x23, 0xC0 }
// #define MY_UUID { 0xB9, 0xC6, 0x10, 0x2C, 0xBE, 0x06, 0x47, 0xB4, 0xA9, 0x43, 0x9E, 0x3F, 0x54, 0x1B, 0x0A, 0x2E }
// #define MY_UUID { 0xBE, 0x95, 0xD3, 0x81, 0xC4, 0xA1, 0x4B, 0x89, 0xB4, 0x15, 0x2F, 0x14, 0xB5, 0xFF, 0xC9, 0x7B }
// #define MY_UUID { 0x5F, 0x88, 0xC1, 0xA6, 0x5F, 0x85, 0x4F, 0x5F, 0xB9, 0x19, 0x11, 0xDB, 0x73, 0x98, 0xD3, 0x12 }
// #define MY_UUID { 0x0A, 0x1B, 0x84, 0x52, 0xFD, 0x8C, 0x4D, 0x72, 0xA5, 0x97, 0x25, 0x0D, 0xD8, 0x49, 0xC8, 0xCF }
// #define MY_UUID { 0x1C, 0xAC, 0x7A, 0x9B, 0x53, 0x2A, 0x42, 0xF7, 0x96, 0x86, 0xE1, 0xAF, 0x78, 0xAA, 0x0E, 0xAD }
// #define MY_UUID { 0xD7, 0xF7, 0xA0, 0x6E, 0x7F, 0x1A, 0x48, 0x6D, 0x9F, 0x23, 0x8A, 0x84, 0x13, 0x97, 0xCC, 0x78 }
// #define MY_UUID { 0xDC, 0xAD, 0xC1, 0x01, 0x3E, 0x83, 0x42, 0x6B, 0x9B, 0xD3, 0x2F, 0x82, 0xE7, 0x41, 0x49, 0x33 }

// English
#ifdef LANGUAGE_EN
	#define LGS_APP_NAME "LGS Watch EN"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "Week %V";
		static char week_text[] = "Week 00";
	#endif
	static char format_date[] = "%b ";
	static char date_text[] = "Feb 23rd";

	// Month names
	// static const char *month_names[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	// Day names
	static const GRect day_rect[] = { ConstantGRect(   4, 76, 20, 13 )
			                        , ConstantGRect(  26, 76, 17, 13 )
			                        , ConstantGRect(  46, 76, 20, 13 )
			                        , ConstantGRect(  68, 76, 17, 13 )
			                        , ConstantGRect(  88, 76, 14, 13 ) 
			                        , ConstantGRect( 105, 76, 15, 13 )
			                        , ConstantGRect( 124, 76, 15, 13 )
			                        };
	static const GTextAlignment day_align[] = { GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  };
	static const char *day_line = "Mo Tu We Th Fr Sa Su";
	static const char *day_names[] = { "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" };

	// Ordinal numbers
	static const char *ordinal_numbers[] = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"
	                                       , "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th"
	                                       , "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th"
	                                       , "31st" };
#endif


// Dutch
#ifdef LANGUAGE_NL
	#define LGS_APP_NAME "LGS Watch NL"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "Week %V";
		static char week_text[] = "Week 00";
	#endif
	static char format_date[] = "%e ";
	static char date_text[] = "23 feb";

	// Month names
	static const char *month_names[] = { "jan", "feb", "mrt", "apr", "mei", "jun", "jul", "aug", "sep", "okt", "nov", "dec" };

	// Day names
	static const GRect day_rect[] = { ConstantGRect(   4, 76, 20, 13 )
		                            , ConstantGRect(  27, 76, 12, 13 )
		                            , ConstantGRect(  43, 76, 20, 13 )
		                            , ConstantGRect(  67, 76, 16, 13 )
		                            , ConstantGRect(  87, 76, 15, 13 )
		                            , ConstantGRect( 105, 76, 16, 13 )
		                            , ConstantGRect( 125, 76, 16, 13 )
		                            };
	static const GTextAlignment day_align[] = { GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  };
	static const char *day_line = "Ma Di Wo Do Vr Za Zo";
	static const char *day_names[] = { "Ma", "Di", "Wo", "Do", "Vr", "Za", "Zo" };
#endif


// German
#ifdef LANGUAGE_DE
	#define LGS_APP_NAME "LGS Watch DE"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "Woche %V";
		static char week_text[] = "Woche 00";
	#endif
	static char format_date[] = "%e. ";
	static char date_text[] = "23. März";

	// Month names
	static const char *month_names[] = { "Jan", "Feb", "März", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };

	// Day names
	static GRect day_rect[] = { ConstantGRect(   6, 76, 20, 13 )
		                      , ConstantGRect(  30, 76, 12, 13 )
		                      , ConstantGRect(  46, 76, 16, 13 )
		                      , ConstantGRect(  66, 76, 16, 13 )
		                      , ConstantGRect(  86, 76, 14, 13 )
		                      , ConstantGRect( 103, 76, 15, 13 )
		                      , ConstantGRect( 122, 76, 15, 13 )
		                      };
	static const GTextAlignment day_align[] = { GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  };
	static const char *day_line = "Mo Di Mi Do Fr Sa So";
	static const char *day_names[] = { "Mo", "Di", "Mi", "Do", "Fr", "Sa", "So" };
#endif


// French
#ifdef LANGUAGE_FR
	#define LGS_APP_NAME "LGS Watch FR"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "Semaine %V";
		static char week_text[] = "Semaine 00";
	#endif
	static char format_date[] = "%e ";
	static char date_text[] = "23 Févr";

	// Month names
	static const char *month_names[] = { "janv", "févr", "mars", "avr", "mai", "juin", "juil", "août", "sept", "oct", "nov", "déc" };

	// Day names
	static GRect day_rect[] = { ConstantGRect(   3, 76, 15, 13 )
		                      , ConstantGRect(  22, 76, 20, 13 )
		                      , ConstantGRect(  46, 76, 20, 13 )
		                      , ConstantGRect(  69, 76, 17, 13 )
		                      , ConstantGRect(  89, 76, 16, 13 )
		                      , ConstantGRect( 109, 76, 15, 13 )
		                      , ConstantGRect( 128, 76, 12, 13 )
		                      };
	static const GTextAlignment day_align[] = { GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  };
	static const char *day_line = "Lu Ma Me Je Ve Sa Di";
	static const char *day_names[] = { "Lu", "Ma", "Me", "Je", "Ve", "Sa", "Di" };
#endif


// Croation
#ifdef LANGUAGE_HR
	#define LGS_APP_NAME "LGS Watch HR"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "%V. tjedan";
		static char week_text[] = "00. tjedan";
	#endif
	static char format_date[] = "%e. ";
	static char date_text[] = "23. siječanj";

	// Month names
	// static const char *month_names[] = { "sij", "velj", "ožuj", "trav", "svib", "lip", "srp", "kol", "ruj", "list", "stud", "pros" };
	static const char *month_names[] = { "siječanj", "veljača", "ožujak", "travanj", "svibanj", "lipanj", "srpanj", "kolovoz", "rujan", "listopad", "studeni", "prosinac" };

	// Day names
	static const GRect day_rect[] = { ConstantGRect(   6, 76, 16, 13 )
			                        , ConstantGRect(  26, 76, 15, 13 )
			                        , ConstantGRect(  44, 76, 14, 13 )
			                        , ConstantGRect(  61, 76, 16, 13 )
			                        , ConstantGRect(  81, 76, 16, 13 ) 
			                        , ConstantGRect( 101, 76, 15, 13 )
			                        , ConstantGRect( 120, 76, 17, 13 ) };
	static const GTextAlignment day_align[] = { GTextAlignmentCenter
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentRight
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentCenter };
	static const char *day_line = "Po Vt Sr Ce Pe Su Ne"; // Č
	static const char *day_names[] = { "Po", "Vt", "Sr", "Ce", "Pe", "Su", "Ne" };
#endif


// Spanish
#ifdef LANGUAGE_ES
	#define LGS_APP_NAME "LGS Watch ES"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "%V. semana";
		static char week_text[] = "00. semana";
	#endif
	static char format_date[] = "%e. ";
	static char date_text[] = "23. agosto";

	// Month names
	static const char *month_names[] = { "enero", "feb", "marzo", "abr", "mayo", "jun", "jul", "agosto", "sept", "oct", "nov", "dic" };

	// Day names
	static const GRect day_rect[] = { ConstantGRect(   5, 76, 15, 13 )
			                        , ConstantGRect(  24, 76, 20, 13 )
			                        , ConstantGRect(  48, 76, 16, 13 )
			                        , ConstantGRect(  66, 76, 17, 13 )
			                        , ConstantGRect(  87, 76, 12, 13 ) 
			                        , ConstantGRect( 103, 76, 15, 13 )
			                        , ConstantGRect( 122, 76, 16, 13 ) };
	static const GTextAlignment day_align[] = { GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft };
	static const char *day_line = "Lu Ma Mi Ju Vi Sá Do";
	static const char *day_names[] = { "Lu", "Ma", "Mi", "Ju", "Vi", "Sá", "Do" };
#endif


// Italian
#ifdef LANGUAGE_IT
	#define LGS_APP_NAME "LGS Watch IT"

	// Define date formats
	#ifdef FORMAT_WEEK
		static char format_week[] = "%V. Setti.	";
		static char week_text[] = "00. Setti.";
	#endif
	static char format_date[] = "%e. ";
	static char date_text[] = "23. luglio";

	// Month names
	static const char *month_names[] = { "genn", "febbr", "mar", "apr", "magg", "giugno", "luglio", "ag", "sett", "ott", "nov", "dic" };

	// Day names
	static const GRect day_rect[] = { ConstantGRect(   4, 76, 15, 13 )
			                        , ConstantGRect(  22, 76, 20, 13 )
			                        , ConstantGRect(  46, 76, 20, 13 )
			                        , ConstantGRect(  70, 76, 12, 13 )
			                        , ConstantGRect(  87, 76, 16, 13 ) 
			                        , ConstantGRect( 107, 76, 15, 13 )
			                        , ConstantGRect( 125, 76, 16, 13 ) };
	static const GTextAlignment day_align[] = { GTextAlignmentLeft
		 									  , GTextAlignmentCenter
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft
		 									  , GTextAlignmentLeft };
	static const char *day_line = "Lu Ma Me Gi Ve Sa Do";
	static const char *day_names[] = { "Lu", "Ma", "Me", "Gi", "Ve", "Sa", "Do" };
#endif