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

#### Run scripts

In background:
```
$ nohup node SCRIPT &:
```

## AWS

### Setup

Install sdk:
```
$ npm install aws-iot-device-sdk
```

## IBM Bluemix

### Setup

Install service:
```
$ curl -LO https://github.com/ibm-messaging/iot-raspberrypi/releases/download/1.0.2.1/iot_1.0-2_armhf.deb 
$ sudo dpkg -i iot_1.0-2_armhf.deb 
```

Configure:
```
$ sudo nano /etc/iotsample-raspberrypi/device.cfg
```

Install sdk:
```
$ npm install ibmiotf
```

## Credentials

### Transfer

Transfer device specific file via SSH:
```
$ scp FILES pi@rpi-X:/home/pi/sensor-data-collector
```

Files to transfer:
```
.aws_credentials.json
.ibm_credentials.json
XYZ-certificate.pem.crt
XYZ-public.pem.key
XYZ-private.pem.key
device.cfg
VeriSign-Class\ 3-Public-Primary-Certification-Authority-G5.pem
```

### IBM

Copy device config to etc:
```
$ sudo service iot stop
$ sudo cp device.cfg /etc/iotsample-raspberrypi/device.cfg
$ sudo service iot start
```
