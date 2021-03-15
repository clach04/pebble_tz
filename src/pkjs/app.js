var Clay = require('pebble-clay');
var clayConfig = require('./config');
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
            console.log('failed to send options to pebble. Error: ' + e.error.message);
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

  // Get the keys and values from each config item
  var dict = clay.getSettings(e.response);

  // hack offsets to be integer
  // dict.THING = parseInt(dict.THING)
  // TZ01_UTC_OFFSET
  // TZ02_UTC_OFFSET
  // TZ03_UTC_OFFSET
  // TZ04_UTC_OFFSET
  // TZ05_UTC_OFFSET
  // TZ06_UTC_OFFSET
  // TZ07_UTC_OFFSET
  // TODO loop though instead of hard coded?
  dict.TZ01_UTC_OFFSET = parseInt(dict.TZ01_UTC_OFFSET);
  dict.TZ02_UTC_OFFSET = parseInt(dict.TZ02_UTC_OFFSET);
  dict.TZ03_UTC_OFFSET = parseInt(dict.TZ03_UTC_OFFSET);
  dict.TZ04_UTC_OFFSET = parseInt(dict.TZ04_UTC_OFFSET);
  dict.TZ05_UTC_OFFSET = parseInt(dict.TZ05_UTC_OFFSET);
  dict.TZ06_UTC_OFFSET = parseInt(dict.TZ06_UTC_OFFSET);
  dict.TZ07_UTC_OFFSET = parseInt(dict.TZ07_UTC_OFFSET);

  // Send settings values to watch side
  Pebble.sendAppMessage(dict, function(e) {
    console.log('Sent config data to Pebble');
  }, function(e) {
    console.log('Failed to send config data!');
    console.log(JSON.stringify(e));
  });
});
