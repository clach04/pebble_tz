/*
** Watchface Framework - Color or Mono
**
**    https://github.com/clach04/watchface_framework
**
** This file may not be needed. This is only needed if additional C code is required.
*/

#include <pebble.h>

#include "watchface.h"

#include <pebble-packet/pebble-packet.h>


//FIXME watchface.c
extern void cleanup_text_time();
extern void setup_text_time(Window *window);
//FIXME

#define INIT_TZ01_NAME "GMT+00"  // Winter time for UK or CET for Western Europe
#define INIT_TZ01_OFFSET (0)  // TODO document these are UTC (whole) hour offsets (not minutes) rather than names and thus not DST aware

#define INIT_TZ02_NAME "GMT-08"  // PST. PDT is GMT-07 and typically starts March, ends November
#define INIT_TZ02_OFFSET (-8)


#define MAX_TZ_NAME_LEN 6 // Long enough for "GMT-xx"
typedef struct persist {
    char tz01_name[MAX_TZ_NAME_LEN+1];
    int tz01_offset;
    char tz02_name[MAX_TZ_NAME_LEN+1];
    int tz02_offset;
#ifdef PBL_PLATFORM_APLITE
    // Aplite times are all base on local time
    int local_offset_in_hours;
#endif  // PBL_PLATFORM_APLITE
} __attribute__((__packed__)) persist;

persist settings = {
    .tz01_name = INIT_TZ01_NAME,
    .tz01_offset = INIT_TZ01_OFFSET,
    .tz02_name = INIT_TZ02_NAME,
    .tz02_offset = INIT_TZ02_OFFSET,
#ifdef PBL_PLATFORM_APLITE
    .local_offset_in_hours = 0,
#endif  // PBL_PLATFORM_APLITE
};

TextLayer *tz01_time_layer=NULL;
TextLayer *tz02_time_layer=NULL;

void update_tz_time(struct tm *tick_time);

// tz_config_handler
bool CUSTOM_IN_RECV_HANDLER(DictionaryIterator *iterator, void *context)
{
    bool wrote_config=false;
    int value_written=-1;

#ifdef PBL_PLATFORM_APLITE
    if(packet_contains_key(iterator, MESSAGE_KEY_LOCAL_UTC_OFFSET_MINS))
    {
        // NOTE this is ONLY needed for Aplite
        settings.local_offset_in_hours = packet_get_integer(iterator, MESSAGE_KEY_LOCAL_UTC_OFFSET_MINS) / 60;  // only integer (complete) hours supported
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found local offset: %d", settings.local_offset_in_hours);
    }
#endif  // PBL_PLATFORM_APLITE

    if(packet_contains_key(iterator, MESSAGE_KEY_TZ01_NAME))
    {
        strncpy(settings.tz01_name, packet_get_string(iterator, MESSAGE_KEY_TZ01_NAME), MAX_TZ_NAME_LEN);
        if(!strcmp(settings.tz01_name, ""))
        {
            strcpy(settings.tz01_name, INIT_TZ01_NAME);
        }
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz1 name: %s", settings.tz01_name);
    }

    if(packet_contains_key(iterator, MESSAGE_KEY_TZ01_UTC_OFFSET))
    {
        settings.tz01_offset = packet_get_integer(iterator, MESSAGE_KEY_TZ01_UTC_OFFSET);
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz1 offset: %d", settings.tz01_offset);
    }
        
    if(packet_contains_key(iterator, MESSAGE_KEY_TZ02_NAME))
    {
        strncpy(settings.tz02_name, packet_get_string(iterator, MESSAGE_KEY_TZ02_NAME), MAX_TZ_NAME_LEN);
        if(!strcmp(settings.tz02_name, ""))
        {
            strcpy(settings.tz02_name, INIT_TZ02_NAME);
        }
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz2 name: %s", settings.tz02_name);
    }
        
    if(packet_contains_key(iterator, MESSAGE_KEY_TZ02_UTC_OFFSET))
    {
        settings.tz02_offset = packet_get_integer(iterator, MESSAGE_KEY_TZ02_UTC_OFFSET);
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz2 offset: %d", settings.tz02_offset);
    }

    value_written = persist_write_data(MESSAGE_KEY_PEBBLE_SETTINGS, &settings, sizeof(settings));
    APP_LOG(APP_LOG_LEVEL_DEBUG, "write settings: %d", value_written);
    if (value_written >= 0)  // TODO compare with sizeof()?
    {
        wrote_config = true;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "write settings SUCCESS");
    }
    else
    {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "write settings FAILURE");
    }

    update_tz_time(NULL);  // FIXME this is a quick-n-dirty "mark dirty" call. Call tick handler instead?
    return wrote_config;
}

void setup_tz_text_time(Window *window)
{
//#define TZ01_CLOCK_POS GRect(100, 52, 180, 180)  // deliberately larger than needed, if too small run risk of not being displayed
//#define TZ02_CLOCK_POS GRect(100, 102, 180, 180)  // deliberately larger than needed, if too small run risk of not being displayed
//#define TZ01_CLOCK_POS GRect(2, 85, 50, 16)
#define TZ01_CLOCK_POS GRect(2, 73, 180, 180)
#define TZ02_CLOCK_POS GRect(2, 85, 180, 180)
#define TZ_FONT FONT_DATE_SYSTEM_NAME
    
#define TZ_TIME_ALIGN GTextAlignmentLeft

    setup_text_time(window);

    // Create time TextLayer
    tz01_time_layer = text_layer_create(TZ01_CLOCK_POS);
    text_layer_set_background_color(tz01_time_layer, GColorClear);
    text_layer_set_text_color(tz01_time_layer, time_color);
    text_layer_set_text(tz01_time_layer, "00:00");

    // Apply to TextLayer
    text_layer_set_font(tz01_time_layer, fonts_get_system_font(TZ_FONT));
    /* Consider GTextAlignmentLeft (with monospaced font) in cases where colon is proportional */
    text_layer_set_text_alignment(tz01_time_layer, TZ_TIME_ALIGN);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(tz01_time_layer));
    // TODO two layers, one for text and one for time?

    // Create time TextLayer
    tz02_time_layer = text_layer_create(TZ02_CLOCK_POS);
    text_layer_set_background_color(tz02_time_layer, GColorClear);
    text_layer_set_text_color(tz02_time_layer, time_color);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "setup_tz_text_time() about to set time for tz2");
    text_layer_set_text(tz02_time_layer, "00:00");

    // Apply to TextLayer
    text_layer_set_font(tz02_time_layer, fonts_get_system_font(TZ_FONT));
    /* Consider GTextAlignmentLeft (with monospaced font) in cases where colon is proportional */
    text_layer_set_text_alignment(tz02_time_layer, TZ_TIME_ALIGN);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(tz02_time_layer));
    // TODO two layers, one for text and one for time?
}

void cleanup_tz_text_time()
{
    /* Destroy TextLayers */
    text_layer_destroy(tz02_time_layer);
    text_layer_destroy(tz01_time_layer);

    cleanup_text_time();
}

void update_tz_time(struct tm *tick_time)
{
    // Create a long-lived buffer
    static char buffer[]="00:00";
    static char tz01_time_str[]="timezonename 00:00";  // need one string per layer, reusing same buffer results in same text
    static char tz02_time_str[MAX_TZ_NAME_LEN+1 + sizeof("00:00")] = "GMT-00 00:00";  // need one string per layer, reusing same buffer results in same text
    char *time_format=NULL;
    time_t utc_time=time(NULL);
    struct tm *utc_tm=NULL;

    if (clock_is_24h_style())
    {
        time_format = "%R";		
    }
    else
    {
        time_format = "%I:%M";
    }

    // With SDK3/Firmware 3
    //      struct tm *current_time is local time
    //      time_t time(NULL) is UTC time
    // FIXME above is true for non-APLITE platforms, but not for Aplite in CloudPebble Emulator.
    // This does NOT appear to be documented

    // TODO convert below into a macro (or function?)
    utc_tm = gmtime(&utc_time);
    // TODO perform minute math on utc_time instead? then skip crap below
    utc_tm->tm_hour += (settings.tz01_offset
#ifdef PBL_PLATFORM_APLITE
                        + settings.local_offset_in_hours
#endif // PBL_PLATFORM_APLITE
                       );
    if (utc_tm->tm_hour >= 24)
    {
        utc_tm->tm_hour -= 24;
    }  
    if (utc_tm->tm_hour < 0)
    {
        utc_tm->tm_hour += 24;
    }  
    strftime(buffer, sizeof(buffer), time_format, utc_tm);
    snprintf(tz01_time_str, sizeof(tz01_time_str), "%s %s", buffer, settings.tz01_name);

    text_layer_set_text(tz01_time_layer, tz01_time_str);


    utc_tm = gmtime(&utc_time);
    // TODO perform minute math on utc_time instead? then skip crap below
    utc_tm->tm_hour += (settings.tz02_offset
#ifdef PBL_PLATFORM_APLITE
                        + settings.local_offset_in_hours
#endif // PBL_PLATFORM_APLITE
                       );
    if (utc_tm->tm_hour >= 24)
    {
        utc_tm->tm_hour -= 24;
    }  
    if (utc_tm->tm_hour < 0) {
        utc_tm->tm_hour += 24;
    }  
    strftime(buffer, sizeof(buffer), time_format, utc_tm);
    snprintf(tz02_time_str, sizeof(tz02_time_str), "%s %s", buffer, settings.tz02_name);

    text_layer_set_text(tz02_time_layer, tz02_time_str);
    // mark dirty?
}
void tz_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time(tick_time);
    update_tz_time(tick_time);  // switch order?
}

void tz_init()
{
    int value_read=-1;
    // load config
    if (persist_exists(MESSAGE_KEY_PEBBLE_SETTINGS))
    {
        value_read = persist_read_data(MESSAGE_KEY_PEBBLE_SETTINGS, &settings, sizeof(settings));
        APP_LOG(APP_LOG_LEVEL_DEBUG, "tz settings loaded %d bytes", value_read);
    }
    else
    {
        APP_LOG(APP_LOG_LEVEL_DEBUG, "tz settings NOTE loaded");
    }
}
void tz_deinit()
{
}

int main(void)
{
    init();
    tz_init();

    app_event_loop();

    tz_deinit();
    deinit();
}
