var Clay = require('@rebble/clay');
var clayConfig = require('./config');
var messageKeys = require('message_keys');
var clay = new Clay(clayConfig, null, { autoHandleEvents: false });

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

// want to override offset to be integer value (not string)
// Clay does not support ints for select/option values - https://github.com/pebble/clay/issues/9
Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener('webviewclosed', function(e) {
  if (e && !e.response) {
    return;
  }

  //console.log('e type ' + typeof(e)); // type object
  //console.log('e.response type ' + typeof(e.response));  // type string, contains json payload

  // Get the keys and values from each config item
  var dict = clay.getSettings(e.response);  // this is a dict, but the keys are numeric
  //console.log(JSON.stringify(dict));

  // hack offsets to be integer
  // TODO loop though instead of hard coded?
  dict[messageKeys.TZ01_UTC_OFFSET] = parseInt(dict[messageKeys.TZ01_UTC_OFFSET]);
  dict[messageKeys.TZ02_UTC_OFFSET] = parseInt(dict[messageKeys.TZ02_UTC_OFFSET]);
  dict[messageKeys.TZ03_UTC_OFFSET] = parseInt(dict[messageKeys.TZ03_UTC_OFFSET]);
  dict[messageKeys.TZ04_UTC_OFFSET] = parseInt(dict[messageKeys.TZ04_UTC_OFFSET]);
  dict[messageKeys.TZ05_UTC_OFFSET] = parseInt(dict[messageKeys.TZ05_UTC_OFFSET]);
  dict[messageKeys.TZ06_UTC_OFFSET] = parseInt(dict[messageKeys.TZ06_UTC_OFFSET]);
  dict[messageKeys.TZ07_UTC_OFFSET] = parseInt(dict[messageKeys.TZ07_UTC_OFFSET]);
  //console.log(JSON.stringify(dict));

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
