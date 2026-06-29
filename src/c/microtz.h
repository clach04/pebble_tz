#ifndef MICROTZ_H
#define MICROTZ_H

#include <stdint.h>
#include <time.h>

typedef struct {
    uint8_t month;
    uint8_t occur;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} microtz_rule;

#define MICROTZ_NAME_LEN 8
typedef struct {
    char name[MICROTZ_NAME_LEN];
    int offset;  // offset in minutes (TODO consider seconds)
    char dst_name[MICROTZ_NAME_LEN];
    uint8_t has_dst;
    microtz_rule start;
    microtz_rule end;
} microtz_info;

microtz_info microtz_parse(const char *posix_tz);
time_t mktime_utc(int year, int month, int day, int hour, int min, int sec);
int microtz_offset(const microtz_info *info, time_t now);

#endif
