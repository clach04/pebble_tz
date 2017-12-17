#pragma once

//#define USE_GENERIC_MAIN

#define CUSTOM_IN_RECV_HANDLER tz_config_handler
#define TICK_HANDLER tz_tick_handler
#define SETUP_TIME setup_tz_text_time
#define CLEANUP_TIME cleanup_tz_text_time

#undef REMOVE_LEADING_ZERO_FROM_TIME  /* 12 hour display will not have a leading '0' or ' ' if this is defined */
#undef FONT_NAME
#undef FONT_SYSTEM_NAME  /* the default font system will be used */
#undef DEBUG_TIME
//#define USE_TIME_MACHINE  // NOTE mixing with DEBUG_TIME doesn't make sense

// Show step count using builtin code
//#define USE_HEALTH
//#define UPDATE_HEALTH_ON_ACTIVITY  /* If not set, only updates step count display once per minute */

#define BAT_FMT_STR "%d%%"
#undef DRAW_BATTERY
//#define DRAW_BATTERY
//#define DRAW_SMALL_BATTERY

//#define QUIET_TIME_IMAGE RESOURCE_ID_IMAGE_QUIET_TIME
//#define QUIET_TIME_IMAGE_GRECT GRect(20, 20, 20, 20)  // Example assumes a 20x20 image

#define BT_DISCONNECT_IMAGE RESOURCE_ID_IMAGE_BT_DISCONNECT

#define QUIET_TIME_IMAGE RESOURCE_ID_IMAGE_QUIET_TIME
#define QUIET_TIME_IMAGE_GRECT GRect(3, 60, 17, 17)  // 17x17 image

#ifdef PBL_ROUND /* 180x180 */
/*TODO center/move right*/
    #define CLOCK_POS GRect(0, 5, 180, 180) /* probably taller than really needed */
    #define HEALTH_POS GRect(0, 40, 180, 180)
    #define BT_POS GRect(0, 100, 180, 180) /* probably taller than really needed */

    #define DATE_ALIGN GTextAlignmentCenter
    #define DATE_POS GRect(0, 135, 180, 180) /* probably taller than really needed */

    #define BAT_ALIGN GTextAlignmentCenter
    #ifdef DRAW_BATTERY
        #define BAT_POS GRect(85, 10, 180, 180) /* probably taller than really needed */
    #else
        #define BAT_POS GRect(0, 150, 180, 180) /* probably taller than really needed */
    #endif /* DRAW_BATTERY */

#else /* PBL_RECT 144x168*/
    #define CLOCK_POS GRect(0, -15, 144, 168) /* TOP of screen, completely avoids preview popoup obscuring time. probably taller than really needed */
    #define HEALTH_POS GRect(0, 40, 144, 168)
    #define BT_POS GRect(0, 120, 144, 168) /* probably taller than really needed */
    #define DATE_POS GRect(0, 140, 144, 168) /* probably taller than really needed */
    //#define BT_DISCONNECT_IMAGE_GRECT GRect(144 - 20, 168 - (2 * 30 + 4), 20, 30)
    #define BT_DISCONNECT_IMAGE_GRECT GRect(144 - 20, 30, 20, 30)
    #ifdef DRAW_BATTERY
        #define BAT_POS GRect(5, 150, 144, 168)
    #else
        #define BAT_POS GRect(0, 140, 144, 168) /* probably taller than really needed */
    #endif /* DRAW_BATTERY */
#endif /* end of Round or rectangle */

/* for screen shots and font testing
#define DEBUG_TIME
#define DEBUG_TIME_SCREENSHOT
 */
