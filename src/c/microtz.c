#include <string.h>

#ifdef PBL_DISPLAY_WIDTH  // Horrible if Pebble SDK check
#include <pebble.h> // <time.h>
#endif // PBL_DISPLAY_WIDTH  // Horrible if Pebble SDK check

#include "microtz.h"

static int parse_num(const char **p) {
    int v = 0;
    while (**p >= '0' && **p <= '9') {
        v = v * 10 + (**p - '0');
        (*p)++;
    }
    return v;
}

static void parse_name_offset(const char *s, microtz_info *info) {
    const char *p = s;
    char *n = info->name;
    int end = sizeof(info->name) - 1;
    int i = 0;
    while (*p && *p >= 'A' && *p <= 'Z' && i < end) {
        *n++ = *p++;
        i++;
    }
    *n = '\0';

    info->offset = 0;
    if (*p == '-') {
        p++;
        info->offset = parse_num(&p) * 3600;
        if (*p == ':') { p++; info->offset += parse_num(&p) * 60; }
    } else if (*p == '+') {
        p++;
        info->offset = -(parse_num(&p) * 3600);
        if (*p == ':') { p++; info->offset -= parse_num(&p) * 60; }
    } else if (*p >= '0' && *p <= '9') {
        info->offset = -(parse_num(&p) * 3600);
        if (*p == ':') { p++; info->offset -= parse_num(&p) * 60; }
    }

    n = info->dst_name;
    end = sizeof(info->dst_name) - 1;
    i = 0;
    while (*p && *p != ',' && i < end) {
        *n++ = *p++;
        i++;
    }
    *n = '\0';
}

static void parse_rule(const char *s, microtz_rule *r) {
    memset(r, 0, sizeof(*r));
    if (*s != 'M') return;
    s++;
    r->month = (uint8_t)parse_num(&s);
    if (*s == '.') s++;
    r->occur = (uint8_t)parse_num(&s);
    if (*s == '.') s++;
    r->day = (uint8_t)parse_num(&s);
    if (*s == '/') {
        s++;
        r->hour = (uint8_t)parse_num(&s);
        if (*s == ':') { s++; r->min = (uint8_t)parse_num(&s); }
        if (*s == ':') { s++; r->sec = (uint8_t)parse_num(&s); }
    } else {
        r->hour = 2;
    }
}

static int is_leap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

time_t mktime_utc(int year, int month, int day, int hour, int min, int sec) {
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;
    t.tm_isdst = 0;
#ifdef _WIN32
    return _mkgmtime(&t);
#else
    //return timegm(&t);  // NOTE currently untested, only tested gcc under Windows so far
    return mktime(&t);  // https://developer.rebble.io/docs/c/Standard_C/Time/#mktime
#endif
}

static time_t determine_change(const microtz_rule *r, int year, int offset_sec) {
    if (!r || r->month == 0) {
        return mktime_utc(year, 1, 1, 0, 0, 0);
    }

    int month = r->month;
    int occur = r->occur;
    int day = r->day;
    int h = r->hour;
    int m = r->min;
    int s = r->sec;

    int min_offset = offset_sec / 60;
    h -= min_offset / 60;
    m -= min_offset % 60;

    static const int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_day = month_days[month - 1];
    if (month == 2 && is_leap(year)) max_day = 29;

    int x = year - ((14 - month) / 12);
    int y = x + x / 4 - x / 100 + x / 400;
    int z = month + 12 * ((14 - month) / 12) - 2;
    int first_dow = (1 + y + (31 * z) / 12) % 7;

    int dom = 1 + (occur - 1) * 7 + (day - first_dow + 7) % 7;
    if (dom > max_day) dom -= 7;

    return mktime_utc(year, month, dom, h, m, s);
}

microtz_info microtz_parse(const char *posix_tz) {
    microtz_info info;
    memset(&info, 0, sizeof(info));

    parse_name_offset(posix_tz, &info);

    const char *comma = strchr(posix_tz, ',');
    if (comma) {
        info.has_dst = 1;
        const char *r1 = comma + 1;
        const char *r2 = strchr(r1, ',');
        if (r2) {
            r2++;
            parse_rule(r1, &info.start);
            parse_rule(r2, &info.end);
        }
    }

    return info;
}

int microtz_offset(const microtz_info *info, time_t now) {
    if (!info || !info->has_dst) {
        return info ? info->offset / 60 : 0;
    }

    struct tm *gt = gmtime(&now);
    int year = gt->tm_year + 1900;

    time_t start = determine_change(&info->start, year, info->offset);
    time_t end = determine_change(&info->end, year, info->offset + 3600);

    if (now > start && now < end) {
        return (info->offset + 3600) / 60;
    }
    return info->offset / 60;
}
