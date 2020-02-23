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
                "defaultValue": "GMT+1 Germany",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ1 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ01_UTC_OFFSET",
                //"defaultValue": -60,  // -1 * 60
                "defaultValue": +60,  // -1 * 60
                "min": -720,  // -12 * 60 == 720 TODO consider supporting minute offsets (instead of integer hours)? E.g India, IST (UTC +5:30 == +330mins)
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ2 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ02_NAME",
                //"defaultValue": "GMT+1",
                "defaultValue": "GMT-0 UK win",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ2 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ02_UTC_OFFSET",
                //"defaultValue": 60, // +1 * 60
                "defaultValue": 0, // +0 * 60
                "min": -720,
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ3 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ03_NAME",
                //"defaultValue": "GMT+8",
                "defaultValue": "San Francisco",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ3 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ03_UTC_OFFSET",
                //"defaultValue": +480,  // 8 * 60
                "defaultValue": -480,  // 8 * 60
                "min": -720,
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ4 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ04_NAME",
                "defaultValue": "GMT+5:30 India",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ4 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ04_UTC_OFFSET",
                "defaultValue": +330,  // 5 * 60 + 30
                "min": -720,
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ5 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ05_NAME",
                "defaultValue": "GMT+8 Hong Kong",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ5 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ05_UTC_OFFSET",
                "defaultValue": +480,  // +8 * 60
                "min": -720,
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ6 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ06_NAME",
                "defaultValue": "GMT+8 Hong Kong",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ6 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ06_UTC_OFFSET",
                "defaultValue": +480,  // +8 * 60
                "min": -720,
                "max": +720,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ7 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ07_NAME",
                "defaultValue": "GMT-6 Austin",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "slider",
                "label": "TZ7 UTC offset",
                "description": "UTC offset (whole minutes only)",
                "messageKey": "TZ07_UTC_OFFSET",
                "defaultValue": -360,  // -6 * 60
                "min": -720,
                "max": +720,
                "step": 1
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
