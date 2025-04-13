var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);

Pebble.addEventListener('ready', function(e) {
    var timezone_offset = new Date().getTimezoneOffset();  // time-zone offset from UTC, in minutes, for the current locale (Aplite only). Later platforms can lookup current GMT time offset
    var options = {"LOCAL_UTC_OFFSET_MINS": timezone_offset};

    console.log('sending options to Pebble: ' + JSON.stringify(options));
    Pebble.sendAppMessage(options,
        function(e) {
            console.log('successfully sent options to pebble');
        },
        function(e) {
            console.log('failed to send options to pebble. Error: ' + e.error.message);
            console.log(JSON.stringify(e));
        }
    );
    // TODO is it possible to lookup defaults and send them now?

});

// override send config, in case want to modify (change types) values or debug
Pebble.addEventListener('webviewclosed', function(e) {
    if (e && !e.response) {
        return;
    }

    var dict = clay.getSettings(e.response);
    //console.log(dict.VIBRATE_ON_DISCONNECT);

    console.log('string config data length=' + JSON.stringify(e).length);
    // Send settings values to watch side
    Pebble.sendAppMessage(dict, function(e) {
        console.log('Sent config data to Pebble');
    }, function(e) {
        console.log('Failed to send data options to Pebble. Error: ' + e.error.message);
        console.log(JSON.stringify(e));  // NOTE possibly secret leakage if adding secrets to config
    });
});
