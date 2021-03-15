module.exports = [
    { 
        "type": "heading", 
        "defaultValue": "Preferences" ,
        "size": 3
    }, 
    { 
        "type": "section",
        "items": [
            {
                "type": "heading",
                "defaultValue": "Colors"
            },
            {
                "type": "text",
                "defaultValue": "Only available on compatible platforms."
            },
            {
                "type": "color",
                "allowGray": true,
                "label": "Background",
                "messageKey": "BACKGROUND_COLOR",
                "defaultValue": "000000"
            },
            {
                "type": "color",
                "label": "Foreground",
                "messageKey": "TIME_COLOR",
                "defaultValue": "FFFFFF"
            }
        ]
    },
    { 
        "type": "section",
        "items": [
            {
                "type": "heading",
                "defaultValue": "Timezone"
            },
            {
                "type": "text",
                "defaultValue": "NOTE not DST aware."
            },
            {
                "type": "input",
                "label": "TZ1 name",
                "description": "Name limited to 12 bytes", // TODO figure out reasonable length
                "messageKey": "TZ01_NAME",
                //"defaultValue": "GMT-1",
                "defaultValue": "GMT+5:30 India",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ1 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ01_UTC_OFFSET",
                "defaultValue": "330",  // 5 * 60 + 30
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ2 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ02_NAME",
                //"defaultValue": "GMT+1",
                "defaultValue": "GMT+1 Germany",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ2 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ02_UTC_OFFSET",
                "defaultValue": "60",  // -1 * 60
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ3 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ03_NAME",
                "defaultValue": "UK DST",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ3 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ03_UTC_OFFSET",
                "defaultValue": "0", // +0 * 60
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ4 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ04_NAME",
                "defaultValue": "New York",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ4 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ04_UTC_OFFSET",
                "defaultValue": "-240",  // -4 * 60
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ5 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ05_NAME",
                "defaultValue": "Austin",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ5 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ05_UTC_OFFSET",
                "defaultValue": "300",  // -5 * 60
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ6 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ06_NAME",
                //"defaultValue": "GMT+8",
                "defaultValue": "San Francisco",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ6 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ06_UTC_OFFSET",
                "defaultValue": "-420",  // 7 * 60
                //"defaultValue": "-480",  // 8 * 60  -- DST
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "input",
                "label": "TZ7 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ07_NAME",
                "defaultValue": "GMT+8 Hong Kong",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "select",
                "label": "TZ7 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ07_UTC_OFFSET",
                "defaultValue": "480",  // +8 * 60
                "options": [
                    {"label": "-12:00", "value": "-720" },
                    {"label": "-11:00", "value": "-660" },
                    {"label": "-10:00", "value": "-600" },
                    {"label": "-09:30", "value": "-510" },
                    {"label": "-09:00", "value": "-540" },
                    {"label": "-08:00", "value": "-480" },
                    {"label": "-07:00", "value": "-420" },
                    {"label": "-06:00", "value": "-360" },
                    {"label": "-05:00", "value": "-300" },
                    {"label": "-04:30", "value": "-210" },
                    {"label": "-04:00", "value": "-240" },
                    {"label": "-03:30", "value": "-150" },
                    {"label": "-03:00", "value": "-180" },
                    {"label": "-02:00", "value": "-120" },
                    {"label": "-01:00", "value": "-60" },
                    {"label": " 00:00", "value": "0" },
                    {"label": "+01:00", "value": "60" },
                    {"label": "+02:00", "value": "120" },
                    {"label": "+03:00", "value": "180" },
                    {"label": "+03:30", "value": "210" },
                    {"label": "+04:00", "value": "240" },
                    {"label": "+04:30", "value": "270" },
                    {"label": "+05:00", "value": "300" },
                    {"label": "+05:30", "value": "330" },
                    {"label": "+05:45", "value": "345" },
                    {"label": "+06:00", "value": "360" },
                    {"label": "+06:30", "value": "390" },
                    {"label": "+07:00", "value": "420" },
                    {"label": "+08:00", "value": "480" },
                    {"label": "+08:30", "value": "510" },
                    {"label": "+08:45", "value": "525" },
                    {"label": "+09:00", "value": "540" },
                    {"label": "+09:30", "value": "570" },
                    {"label": "+09:45", "value": "585" },
                    {"label": "+10:00", "value": "600" },
                    {"label": "+10:30", "value": "630" },
                    {"label": "+11:00", "value": "660" },
                    {"label": "+12:00", "value": "720" },
                    {"label": "+12:45", "value": "765" },
                    {"label": "+13:00", "value": "780" },
                    {"label": "+14:00", "value": "840" }
                ]
            },
            {
                "type": "text",
                "defaultValue": "GMT+01 (60) == BST for UK or CET for Western Europe<br>GMT+00 == Winter time for UK or CET for Western Europe<br>GMT-07 (-420) == PDT typically starts March, ends November<br>GMT-08 (-480) == PST Pacific Standard Time (Winter)<br>GMT+5:30 (330) IST India time<br>GMT+8 (480) == Hong Kong time"
            },
        ]
    },
    {
        "type": "section",
        "items": [
            {
                "type": "heading",
                "defaultValue": "Features"
            },
            {
                "type": "toggle",
                "label": "Vibrate on Bluetooth disconnect",
                "messageKey": "VIBRATE_ON_DISCONNECT",
                "defaultValue": false
            },
            {
                "type": "text",
                "defaultValue": "Will NOT vibrate during Quiet Time or if health monitoring detects sleeping."
            }
        ]
    },
    {
        "type": "submit",
        "defaultValue": "Save"
    }
];
