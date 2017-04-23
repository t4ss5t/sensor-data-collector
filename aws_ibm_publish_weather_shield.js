var SerialPort = require("serialport");
var awsIot = require('aws-iot-device-sdk');
var ibmIot = require("ibmiotf");

// credentials

var awsCredentials = require('./.aws_credentials.json');
var ibmCredentials = require('./.ibm_credentials.json');

// devices

var awsDevice = awsIot.device(awsCredentials);

awsDevice.on('connect', function() {
  console.log('AWS device connected');
});

awsDevice.on('message', function(topic, payload) {
  console.log('message', topic, payload.toString());
});

var ibmDevice = new ibmIot.IotfDevice(ibmCredentials);

ibmDevice.log.setLevel('info');
ibmDevice.connect();

ibmDevice.on("connect", function () {
  console.log("IBM device connected");
});

ibmDevice.on("error", function (err) {
  console.log("Error : "+err);
});

// serial

var port = new SerialPort("/dev/ttyACM0", {
  baudRate: 9600,
  parser: SerialPort.parsers.readline('\n')
});

port.on('error', function(err) {
  console.log('Error: ', err.message);
})

port.on('data', function (data) {
  try {
    var obj = JSON.parse( (data).replace(/'/g,'"') );
    console.log(obj);
    var timestamp = Date.now();
    if( obj && obj.sensor ) {
      obj.timestamp = timestamp;

      obj.id = awsCredentials.clientId;
      awsDevice.publish('weather_shield_measure_data/' + obj.sensor, JSON.stringify(obj));

      obj.id = ibmCredentials.id;
      ibmDevice.publish(obj.sensor,"json", JSON.stringify(obj));
    }
  } catch(e) {}
});
