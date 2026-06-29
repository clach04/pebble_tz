var meta = require('../../package.json');

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
                "defaultValue": "NOTE uses POSIX TZ rules"
            },
            {
                "type": "input",
                "label": "TZ1 name",
                "description": "Name limited to 12 bytes", // TODO figure out reasonable length
                "messageKey": "TZ01_NAME",
                "defaultValue": "GMT+8 Hong Kong",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ1 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ01_TZ_RULE",
                "defaultValue": "CST-8",  // +8 * 60
                "attributes": {"limit": 38}  // TODO review max length for TZ rule
            },
            {
                "type": "input",
                "label": "TZ2 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ02_NAME",
                "defaultValue": "GMT+5:30 India",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ2 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ02_TZ_RULE",
                "defaultValue": "IST-5:30",  // 5 * 60 + 30  -- India, IST (UTC +5:30 == +330mins)
                "attributes": {"limit": 38}
            },
            {
                "type": "input",
                "label": "TZ3 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ03_NAME",
                "defaultValue": "GMT+1 Germany",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ3 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ03_TZ_RULE",
                "defaultValue": "CET-1CEST,M3.5.0,M10.5.0/3",  // -1 * 60
                "attributes": {"limit": 38}
            },
            {
                "type": "input",
                "label": "TZ4 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ04_NAME",
                "defaultValue": "GMT-0 UK win",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ4 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ04_TZ_RULE",
                "defaultValue": "GMT0BST,M3.5.0/1,M10.5.0", // +0 * 60
                "attributes": {"limit": 38}
            },
            {
                "type": "input",
                "label": "TZ5 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ05_NAME",
                "defaultValue": "New York",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ5 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ05_TZ_RULE",
                "defaultValue": "EST5EDT,M3.2.0,M11.1.0",  // -5 * 60
                "attributes": {"limit": 38}
            },
            {
                "type": "input",
                "label": "TZ6 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ06_NAME",
                "defaultValue": "GMT-6 Austin",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ6 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ06_TZ_RULE",
                "defaultValue": "CST6CDT,M3.2.0,M11.1.0",  // -6 * 60
                "attributes": {"limit": 38}
            },
            {
                "type": "input",
                "label": "TZ7 name",
                "description": "Name limited to 12 bytes",
                "messageKey": "TZ07_NAME",
                "defaultValue": "San Francisco",
                "attributes": {
                    "limit": 12
                }
            },
            {
                "type": "input",
                "label": "TZ7 POSIX TZ Rule",
                "description": "POSIX TZ Rule (whole minutes only)",
                "messageKey": "TZ07_TZ_RULE",
                "defaultValue": "PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00",  // 8 * 60
                "attributes": {"limit": 38}
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
    },
    {
        "type": "text",
        "defaultValue": "v" + meta.version
    }
];
