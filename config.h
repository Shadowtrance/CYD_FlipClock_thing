// ------------------------------------
// Configuration Header: config.h
// This file holds all user-specific settings.
// ------------------------------------

#ifndef CONFIG_H
#define CONFIG_H


// --- 2. Time Configuration ---
static const bool TIME_FORMAT_24H = true;       
static const bool DST_ACTIVE = false;         
static const char* ntpServer = "pool.ntp.org"; 

// --- 3. TOUCH SCREEN PINS ---
#define TS_SDA 33     
#define TS_SCL 32 
#define TS_INT 21 
#define TS_RST 25  

// --- MODE SELECTORS ---
static const bool USE_CITY_ID = false; 
static const bool USE_FAHRENHEIT = false; 

// Interval to fetch new weather data (in minutes). 
// Note: This is now an unsigned long value (in milliseconds)
static const unsigned long WEATHER_UPDATE_INTERVAL_MS = 60 * 60000UL; 

// Base URL for the API
static const char* OPENWEATHER_URL_BASE = "https://api.openweathermap.org/data/2.5/weather?";



#endif // CONFIG_H