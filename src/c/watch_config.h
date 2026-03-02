#pragma once

// FIXME below is fine on Basalt+, USE_MAX_MESSAGE_SIZE is too big for aplite - not enough heap memory :-(
//#define USE_MAX_MESSAGE_SIZE  // for nowuse this, without 6 timezones is bigger than 200, TODO set max_in only
#define MAX_MESSAGE_SIZES
#define MAX_MESSAGE_SIZE_IN 2000  // actually need under 1.5K, extra for just-in-case
#define MAX_MESSAGE_SIZE_OUT 0

//#define USE_GENERIC_MAIN

#define CUSTOM_IN_RECV_HANDLER tz_config_handler
#define TICK_HANDLER tz_tick_handler
#define SETUP_TIME setup_tz_text_time
#define CLEANUP_TIME cleanup_tz_text_time

#undef REMOVE_LEADING_ZERO_FROM_TIME  /* 12 hour display will not have a leading '0' or ' ' if this is defined */
#undef FONT_NAME
#undef FONT_SYSTEM_NAME  /* the default font system will be used */
#undef DEBUG_TIME
//#define USE_TIME_MACHINE  // NOTE mixing with DEBUG_TIME doesn't make sense. Requires update to package.json for dependencies

// Show step count using builtin code
//#define USE_HEALTH
//#define UPDATE_HEALTH_ON_ACTIVITY  /* If not set, only updates step count display once per minute */

#define BAT_FMT_STR "%d%%"
#undef DRAW_BATTERY
//#define DRAW_BATTERY
//#define DRAW_SMALL_BATTERY

#define PERCENT_WIDTH(x) (PBL_DISPLAY_WIDTH * x / 1000)  // where x is a 1000th. E.g. x=18 == 1.8%, x=1000 == 100%
#define PERCENT_HEIGHT(x) (PBL_DISPLAY_HEIGHT * x / 1000)  // where x is a 1000th. E.g. x=18 == 1.8%, x=1000 == 100%

#define QUIET_TIME_POS  GRect(20, 20, 60, 60)
//#define QUIET_TIME_IMAGE RESOURCE_ID_IMAGE_QUIET_TIME
//#define QUIET_TIME_IMAGE_GRECT GRect(20, 20, 20, 20)  // Example assumes a 20x20 image

#define BT_DISCONNECT_IMAGE RESOURCE_ID_IMAGE_BT_DISCONNECT

#define QUIET_TIME_IMAGE RESOURCE_ID_IMAGE_QUIET_TIME


#if PBL_DISPLAY_HEIGHT == 228  // 200x228 Pebble Time 2 (emery)
    #define FONT_DATE_SYSTEM_NAME FONT_KEY_GOTHIC_24_BOLD
#elif PBL_DISPLAY_HEIGHT == 260  // 260x260 Pebble Round 2 (gabbro)
    #define FONT_DATE_SYSTEM_NAME FONT_KEY_GOTHIC_24_BOLD  // same as emery
#else  // if 168
    #define FONT_DATE_SYSTEM_NAME FONT_KEY_GOTHIC_18_BOLD
#endif


#if defined(PBL_PLATFORM_EMERY) || defined(PBL_PLATFORM_GABBRO)
    #define FONT_BAT_SYSTEM_NAME FONT_KEY_GOTHIC_24
#else  // Original
    #define FONT_BAT_SYSTEM_NAME FONT_KEY_GOTHIC_18
#endif

// See https://developer.rebble.io/guides/best-practices/building-for-every-pebble/#available-defines-and-macros for hardware specific defines
#ifdef PBL_ROUND /* 180x180 */
    #define QUIET_TIME_IMAGE_GRECT GRect(17, 48, 17, 17)  // TODO consider placing in top of screen/circle
    #define CLOCK_POS GRect(0, 5, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* probably taller than really needed */
    #define HEALTH_POS GRect(0, 40, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT)
    //#define BT_POS GRect(0, 100, 180, 180) /* probably taller than really needed */
    #define BT_DISCONNECT_IMAGE_GRECT GRect(148, 47, 18, 22)  // TODO consider placing in top of screen/circle

    #define DATE_ALIGN GTextAlignmentCenter
    #define DATE_POS GRect(0, 0, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* probably taller than really needed */

    #define BAT_ALIGN GTextAlignmentCenter
    #ifdef DRAW_BATTERY
        #define BAT_POS GRect(85, 10, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* probably taller than really needed */
    #else
        #define BAT_POS GRect(0, PERCENT_HEIGHT(862), PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* probably taller than really needed */
    #endif /* DRAW_BATTERY */

#else /* PBL_RECT 144x168*/
    #define QUIET_TIME_IMAGE_GRECT GRect(0, 35+3, 17, 17)  // 17x17 image

    #if defined(PBL_PLATFORM_EMERY)
        // TODO revisit, consider -9 or -8?
        #define CLOCK_POS GRect(0, -10, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* TOP of screen, completely avoids preview popoup obscuring time. probably taller than really needed */

        #define DATE_ALIGN GTextAlignmentLeft
        #define DATE_POS GRect(45 + 10, 35, 100, 30) // to the right of watch battery
    #else
        #define CLOCK_POS GRect(0, -15, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* TOP of screen, completely avoids preview popoup obscuring time. probably taller than really needed */

        #define DATE_ALIGN GTextAlignmentRight  // TODO make left then math will be easier below!
        //#define DATE_POS GRect(0, 140, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* bottom right hand side (covered by quick view) */
        #define DATE_POS GRect(26, 35, 100, 30) /* try for near top/center, want almost centered */
        //#define DATE_POS GRect(0, 40, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* try for near top/center, want centered */
    #endif
    #define HEALTH_POS GRect(0, 40, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT)


    //#define BT_POS GRect(0, 120, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* probably taller than really needed */
    #define BT_DISCONNECT_IMAGE_GRECT GRect(144 - 20 + 3, 35, 18, 22)
    #ifdef DRAW_BATTERY
        #define BAT_POS GRect(5, 150, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT)
    #else
        #define BAT_ALIGN GTextAlignmentLeft
        //#define BAT_POS GRect(0, 140, PBL_DISPLAY_WIDTH, PBL_DISPLAY_HEIGHT) /* bottom left hand side (covered by quick view) */
        #define BAT_POS GRect(14, 35, 50, 30) /* 14 is quiet time icon size */
    #endif /* DRAW_BATTERY */
#endif /* end of Round or rectangle */

/* for screen shots and font testing
#define DEBUG  // If set will update each second and use seconds as minutes for checking updates (not the best for screenshots)
#ifdef DEBUG
#define TICK_HANDLER_INTERVAL SECOND_UNIT
#endif // DEBUG

#define DEBUG_TIME
#define DEBUG_TIME_SCREENSHOT
// ensure quiet time and bluetooth disconnection info is shown
#ifndef quiet_time_is_active  // so not aplite
#define quiet_time_is_active() true  // DEBUG!
#else
#undef quiet_time_is_active  // See if we can force this to always be true
#define quiet_time_is_active() true  // DEBUG!
#endif
#define bluetooth_connection_service_peek() false  // DEBUG!
*/
