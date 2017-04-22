var SerialPort = require("serialport");

var port = new SerialPort("/dev/ttyACM0", {
  baudRate: 115200,
  parser: SerialPort.parsers.readline('\n')
});

port.on('open', function() {
   console.log('port open');
});

port.on('error', function(err) {
  console.log('Error: ', err.message);
})

port.on('data', function (data) {
  console.log(data);
});
