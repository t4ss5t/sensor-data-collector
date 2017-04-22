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

For ARMv6 based models:
```
$ wget https://nodejs.org/dist/v6.10.2/node-v6.10.2-linux-armv6l.tar.gz
$ tar -xvf node-v6.10.2-linux-armv6l.tar.gz
$ cd node-v6.10.2-linux-armv6l
$ sudo cp -R * /usr/local/
$ sudo reboot
```

#### Python

Install python-serial:
```
$ sudo apt-get install python-serial
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

Install sdk:
```
$ npm install ibmiotf
```
