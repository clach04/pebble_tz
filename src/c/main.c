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
#define INIT_TZ01_OFFSET (0 * 60)  // TODO document these are UTC (whole) hour offsets (not minutes) rather than names and thus not DST aware
//#define INIT_TZ01_NAME "GMT+05:30 IST"  // has a half hour tz
//#define INIT_TZ01_OFFSET (5 * 60 + 30)  // minutes and not DST aware

#define INIT_TZ02_NAME "GMT-08"  // PST. PDT is GMT-07 and typically starts March, ends November
#define INIT_TZ02_OFFSET (-8 * 60)

#define INIT_TZ03_NAME "GMT+08"  // HKT - no DST for Hong Kong
#define INIT_TZ03_OFFSET (+8 * 60)

#define INIT_TZ04_NAME "GMT+01"  // summer time for UK or Winter for Western Europe
#define INIT_TZ04_OFFSET (+1 * 60)


//#define MAX_TZ_NAME_LEN 6 // Long enough for "GMT-xx"
#define MAX_TZ_NAME_LEN 12  // Long enough for "timezonename"
typedef struct persist {
    char tz01_name[MAX_TZ_NAME_LEN+1];
    int tz01_offset;  // Number of mins
    char tz02_name[MAX_TZ_NAME_LEN+1];
    int tz02_offset;
    char tz03_name[MAX_TZ_NAME_LEN+1];
    int tz03_offset;
    char tz04_name[MAX_TZ_NAME_LEN+1];
    int tz04_offset;
    // Aplite times are all base on local time so need to know local offset, for later platforms this is always zero
    int local_offset_in_mins;  // zero for non-Aplite devices
} __attribute__((__packed__)) persist;

persist settings = {
    .tz01_name = INIT_TZ01_NAME,
    .tz01_offset = INIT_TZ01_OFFSET,
    .tz02_name = INIT_TZ02_NAME,
    .tz02_offset = INIT_TZ02_OFFSET,
    .tz03_name = INIT_TZ03_NAME,
    .tz03_offset = INIT_TZ03_OFFSET,
    .tz04_name = INIT_TZ04_NAME,
    .tz04_offset = INIT_TZ04_OFFSET,
    .local_offset_in_mins = 0,  // This will be calculated and sent from javascript on phone
};

TextLayer *tz01_time_layer=NULL;
TextLayer *tz02_time_layer=NULL;
TextLayer *tz03_time_layer=NULL;
TextLayer *tz04_time_layer=NULL;

void update_tz_time(struct tm *tick_time);

// tz_config_handler
bool CUSTOM_IN_RECV_HANDLER(DictionaryIterator *iterator, void *context)
{
    bool wrote_config=false;
    int value_written=-1;

#ifdef PBL_PLATFORM_APLITE
    if(packet_contains_key(iterator, MESSAGE_KEY_LOCAL_UTC_OFFSET_MINS))
    {
        // NOTE this is ONLY needed for Aplite, later platforms must keep this as zero
        settings.local_offset_in_mins = packet_get_integer(iterator, MESSAGE_KEY_LOCAL_UTC_OFFSET_MINS);  // only integer (complete) hours supported
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found local offset: %d", settings.local_offset_in_mins);
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

    if(packet_contains_key(iterator, MESSAGE_KEY_TZ03_NAME))
    {
        strncpy(settings.tz03_name, packet_get_string(iterator, MESSAGE_KEY_TZ03_NAME), MAX_TZ_NAME_LEN);
        if(!strcmp(settings.tz03_name, ""))
        {
            strcpy(settings.tz03_name, INIT_TZ03_NAME);
        }
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz3 name: %s", settings.tz03_name);
    }
        
    if(packet_contains_key(iterator, MESSAGE_KEY_TZ03_UTC_OFFSET))
    {
        settings.tz03_offset = packet_get_integer(iterator, MESSAGE_KEY_TZ03_UTC_OFFSET);
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz3 offset: %d", settings.tz03_offset);
    }

#define TZ_DO_SETTINGS(TZ_MACRO, MSG_TZ_MACRO) if(packet_contains_key(iterator, MESSAGE_KEY_ ## MSG_TZ_MACRO ##_NAME)) { strncpy(settings.TZ_MACRO ## _name, packet_get_string(iterator, MESSAGE_KEY_ ## MSG_TZ_MACRO ##_NAME), MAX_TZ_NAME_LEN); if(!strcmp(settings.TZ_MACRO ## _name, "")) { strcpy(settings.TZ_MACRO ## _name, INIT_## MSG_TZ_MACRO ##_NAME); } APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz3 name: %s", settings.TZ_MACRO ## _name); } if(packet_contains_key(iterator, MESSAGE_KEY_ ## MSG_TZ_MACRO ##_UTC_OFFSET)) { settings.TZ_MACRO ## _offset = packet_get_integer(iterator, MESSAGE_KEY_ ## MSG_TZ_MACRO ##_UTC_OFFSET); APP_LOG(APP_LOG_LEVEL_DEBUG, "Found tz3 offset: %d", settings.TZ_MACRO ## _offset); } 

    TZ_DO_SETTINGS(tz04, TZ04)

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
#define TZ_SPACING 15
#define tz01_clock_pos GRect(2, 73, 180, 180)
#define tz02_clock_pos GRect(2, 73 + TZ_SPACING, 180, 180)
#define tz03_clock_pos GRect(2, 73 + (2 * TZ_SPACING), 180, 180)
#define tz04_clock_pos GRect(2, 73 + (3 * TZ_SPACING), 180, 180)
#define TZ_FONT FONT_DATE_SYSTEM_NAME
    
#define TZ_TIME_ALIGN GTextAlignmentLeft

    setup_text_time(window);

    // Create time TextLayer
    tz01_time_layer = text_layer_create(tz01_clock_pos);
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
    tz02_time_layer = text_layer_create(tz02_clock_pos);
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

    // Create time TextLayer
    tz03_time_layer = text_layer_create(tz03_clock_pos);
    text_layer_set_background_color(tz03_time_layer, GColorClear);
    text_layer_set_text_color(tz03_time_layer, time_color);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "setup_tz_text_time() about to set time for tz3");
    text_layer_set_text(tz03_time_layer, "00:00");

    // Apply to TextLayer
    text_layer_set_font(tz03_time_layer, fonts_get_system_font(TZ_FONT));
    /* Consider GTextAlignmentLeft (with monospaced font) in cases where colon is proportional */
    text_layer_set_text_alignment(tz03_time_layer, TZ_TIME_ALIGN);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(tz03_time_layer));
    // TODO two layers, one for text and one for time?

// Create time TextLayer
// Add it as a child layer to the Window's root layer
// TODO two layers, one for text and one for time?
#define TZ_TEXT_LAYER(TZ_MACRO) TZ_MACRO ## _time_layer = text_layer_create(TZ_MACRO ## _clock_pos); text_layer_set_background_color(TZ_MACRO ## _time_layer, GColorClear); text_layer_set_text_color(TZ_MACRO ## _time_layer, time_color); APP_LOG(APP_LOG_LEVEL_DEBUG, "setup_tz_text_time() about to set time for tz3"); text_layer_set_text(TZ_MACRO ## _time_layer, "00:00");  text_layer_set_font(TZ_MACRO ## _time_layer, fonts_get_system_font(TZ_FONT)); text_layer_set_text_alignment(TZ_MACRO ## _time_layer, TZ_TIME_ALIGN);  layer_add_child(window_get_root_layer(window), text_layer_get_layer(TZ_MACRO ## _time_layer)); 

    TZ_TEXT_LAYER(tz04)
}

void cleanup_tz_text_time()
{
    /* Destroy TextLayers */
    text_layer_destroy(tz04_time_layer);
    text_layer_destroy(tz03_time_layer);
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
    static char tz03_time_str[MAX_TZ_NAME_LEN+1 + sizeof("00:00")] = "GMT-00 00:00";  // need one string per layer, reusing same buffer results in same text
    static char tz04_time_str[MAX_TZ_NAME_LEN+1 + sizeof("00:00")] = "GMT-00 00:00";  // need one string per layer, reusing same buffer results in same text
    char *time_format=NULL;
    time_t utc_time=time(NULL);
    struct tm *utc_tm=NULL;

    if (clock_is_24h_style())
    {
        time_format = "%R";  // TODO show a/p?
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

    utc_time=time(NULL);
    // Not supposd to peak at a time_t but know it is number of seconds since epoc.
    // So perform arithmetic on second s
    utc_time += (60 * settings.tz01_offset) + (60 * settings.local_offset_in_mins);
    utc_tm = gmtime(&utc_time);
    strftime(buffer, sizeof(buffer), time_format, utc_tm);
    snprintf(tz01_time_str, sizeof(tz01_time_str), "%s %s", buffer, settings.tz01_name);

    text_layer_set_text(tz01_time_layer, tz01_time_str);


    utc_time = time(NULL);
    // Not supposd to peak at a time_t but know it is number of seconds since epoc.
    // So perform arithmetic on second s
    utc_time += (60 * settings.tz02_offset) + (60 * settings.local_offset_in_mins);
    utc_tm = gmtime(&utc_time);
    strftime(buffer, sizeof(buffer), time_format, utc_tm);
    snprintf(tz02_time_str, sizeof(tz02_time_str), "%s %s", buffer, settings.tz02_name);

    text_layer_set_text(tz02_time_layer, tz02_time_str);

    utc_time = time(NULL);
    // Not supposd to peak at a time_t but know it is number of seconds since epoc.
    // So perform arithmetic on second s
    utc_time += (60 * settings.tz03_offset) + (60 * settings.local_offset_in_mins);
    utc_tm = gmtime(&utc_time);

    strftime(buffer, sizeof(buffer), time_format, utc_tm);
    snprintf(tz03_time_str, sizeof(tz03_time_str), "%s %s", buffer, settings.tz03_name);

    text_layer_set_text(tz03_time_layer, tz03_time_str);

    utc_time = time(NULL); // TODO add to macro
    // TODO minute math, not just hours and seconds
#define TZ_DO_TIME(TZ_MACRO)     utc_time += (60 * settings.TZ_MACRO ## _offset) + (60 * settings.local_offset_in_mins); utc_tm = gmtime(&utc_time); strftime(buffer, sizeof(buffer), time_format, utc_tm); snprintf(TZ_MACRO ## _time_str, sizeof(TZ_MACRO ## _time_str), "%s %s", buffer, settings.TZ_MACRO ## _name); text_layer_set_text(TZ_MACRO ## _time_layer, TZ_MACRO ## _time_str); 

TZ_DO_TIME(tz04)

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
