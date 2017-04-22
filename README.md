# sensor-data-collector

Repo for distribute scripts for sensor data collection

## Raspberry Pi

### Setup

#### Node

npm:
```
$ sudo apt-get install npm
```

Node.js (newer version to fix serialport bug):
```
$ curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
$ sudo apt-get install -y nodejs
```

#### Python

Install python-serial:
```
sudo apt-get install minicom python-serial
```

#### Serial

```
$ npm install serialport
```

### Usage

#### Find Arduino device

Use script:
```
$ python find_arduino_on_serial.py
```

List devices manually:
```
$ ls /dev/tty*
```

#### Test serial port

Open serial port and print data:
```
$ node get_serial.js
```

#### Run script (in background)

## AWS

### Setup

Install sdk:

```
$ npm install aws-iot-device-sdk
```

## IBM Bluemix
