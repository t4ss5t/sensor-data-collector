var awsIot = require('aws-iot-device-sdk');
var SerialPort = require("serialport");

var device = awsIot.device({
   keyPath: 'private.pem.key',
  certPath: 'certificate.pem.crt',
    caPath: 'root-CA.pem',
  clientId: '123',
    region: 'eu-west-1'
});

var port = new SerialPort("/dev/ttyACM0", {
  baudRate: 9600,
  //autoOpen: false,
  parser: SerialPort.parsers.readline('\n')
});

port.on('error', function(err) {
  console.log('Error: ', err.message);
})

port.on('data', function (data) {
  //console.log(data);
  try {
  	var obj = JSON.parse( (data).replace(/'/g,'"') );
  	console.log(obj);
  	var timestamp = Date.now();
  	if( obj && obj.sensor ) {
		obj.timestamp = timestamp;
		//device.publish('weather_shield_measure_data', JSON.stringify(obj));
		device.publish('weather_shield_measure_data/' + obj.sensor, JSON.stringify(obj));
  	}
  } catch(e) {}
});


/*
device
  .on('connect', function() {
    console.log('connect');
    device.subscribe('topic_1');
    device.publish('topic_2', JSON.stringify({ test_data: 1}));
    });
*/

device
  .on('message', function(topic, payload) {
    console.log('message', topic, payload.toString());
  });
