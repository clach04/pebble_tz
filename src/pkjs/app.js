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
            console.log('failed to send options to pebble. Error: ' + JSON.stringify(e));  // NOTE possibly secret leakage if adding secrets to config
        }
    );
    // TODO is it possible to lookup defaults and send them now?

});

// override send config, in case want to modify (change types) values or debug
// TODO consider js-message-queue
Pebble.addEventListener('webviewclosed', function(e) {
    console.log('webviewclosed entry');
    if (e && !e.response) {
        return;
    }

    var dict = clay.getSettings(e.response);
    //console.log(dict.VIBRATE_ON_DISCONNECT);

    console.log('e string config data length=' + JSON.stringify(e).length);
    console.log('dict config data length=' + JSON.stringify(dict).length);
    console.log(JSON.stringify(e));  // NOTE possibly secret leakage if adding secrets to config
    console.log(JSON.stringify(dict));  // NOTE possibly secret leakage if adding secrets to config

    // debug
    //dict = {"10000":16777215,"10001":1,"10002":0};  / this does not work, seems to use original value

    console.log('DEBUG pre-send');
    // Send settings values to watch side
    Pebble.sendAppMessage(dict, function(e) {
        console.log('DEBUG success send');
        console.log('Sent config data to Pebble');
    }, function(e) {
        console.log('DEBUG FAIL send');
        console.log('Failed to send data options to Pebble. Error: ' + JSON.stringify(e));  // NOTE possibly secret leakage if adding secrets to config
        //console.log('Failed to send data options to Pebble. Error: ' + e);  // [object Event]
        //console.log('Failed to send data options to Pebble. Error: ' + e.error); // undefined
        //console.log('Failed to send data options to Pebble. Error: ' + e.error.message); // FIXME this does NOT work and fails
        //console.log(JSON.stringify(e));  // NOTE possibly secret leakage if adding secrets to config
    });
    console.log('DEBUG post-send');
});
