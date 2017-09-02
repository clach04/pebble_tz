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
                "description": "Name limited to 6 bytes", // TODO figure out reasonable length
                "messageKey": "TZ01_NAME",
                "defaultValue": "GMT-1",
                "attributes": {
                    "limit": 6
                }
            },
            {
                "type": "slider",
                "label": "TZ1 UTC offset",
                "description": "UTC offset (whole hours only)",
                "messageKey": "TZ01_UTC_OFFSET",
                "defaultValue": -1,
                "min": -12,  // TODO consider supporting minute offsets (instead of integer hours)? E.g India, IST (UTC +5:30 == +330mins)
                "max": +12,
                "step": 1
            },
            {
                "type": "input",
                "label": "TZ2 name",
                "description": "Name limited to 6 bytes",
                "messageKey": "TZ02_NAME",
                "defaultValue": "GMT+1",
                "attributes": {
                    "limit": 6
                }
            },
            {
                "type": "slider",
                "label": "TZ2 UTC offset",
                "description": "UTC offset (whole hours only)",
                "messageKey": "TZ02_UTC_OFFSET",
                "defaultValue": +1,
                "min": -12,
                "max": +12,
                "step": 1
            },
            {
                "type": "text",
                "defaultValue": "GMT+01 == BST for UK or CET for Western Europe<br>GMT+00 == Winter time for UK or CET for Western Europe<br>GMT-07 == PDT typically starts March, ends November<br>GMT-08 == PST Pacific Standard Time (Winter)"
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
