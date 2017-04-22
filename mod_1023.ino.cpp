/*

Copyright (c) 2015, Embedded Adventures
All rights reserved.

Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.

*/

// Test sketch for MOD1023 
// Communicating with the BME280 weather multi-sensor and the indoor air quality sensor

#include <BME280_MOD-1022.h>
#include <iAQ-MOD1023.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  uns8 chipID = BME280.readChipId();
  bme280_forcedSample();
}

void loop() {
  iaqUpdate();
  bme280_indoorSample();
  delay(5000);
}

//Update and print data from iAQ
void iaqUpdate() {
  String status;
  int pred, ohm, tvoc;

  iaq.readRegisters();

  status = iaq.getStatus();
  pred = iaq.getPrediction();
  ohm = iaq.getResistance();
  tvoc = iaq.getTVOC();

  Serial.print("{");
  Serial.print("'sensor':'iAQ'");
  Serial.print(",");
  Serial.print("'status':'");
  Serial.print(status);
  Serial.print("',");
  Serial.print("'pred':");
  Serial.print(pred);
  Serial.print(",");
  Serial.print("'ohm':");
  Serial.print(ohm);
  Serial.print(",");
  Serial.print("'tvoc':");
  Serial.print(tvoc);
  Serial.print("}");
  Serial.println();
}

void printCompensatedMeasurements(void) {
  float temp, humidity, pressure, pressureMoreAccurate;
  double tempMostAccurate, humidityMostAccurate, pressureMostAccurate;

  temp      = BME280.getTemperature();
  humidity  = BME280.getHumidity();
  pressure  = BME280.getPressure();
  
  pressureMoreAccurate = BME280.getPressureMoreAccurate();
  tempMostAccurate     = BME280.getTemperatureMostAccurate();
  humidityMostAccurate = BME280.getHumidityMostAccurate();
  pressureMostAccurate = BME280.getPressureMostAccurate();

  Serial.print("{");
  Serial.print("'sensor':'BME280'");
  Serial.print(",");
  Serial.print("'mode':'compensated'");
  Serial.print(",");
  Serial.print("'temperature':");
  Serial.print(temp);
  Serial.print(",");
  Serial.print("'temperature_most_accurate':");
  Serial.print(tempMostAccurate);
  Serial.print(",");
  Serial.print("'humidity':");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print("'humidity_most_accurate':");
  Serial.print(humidityMostAccurate);
  Serial.print(",");
  Serial.print("'pressure':");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print("'pressure_more_accurate':");
  Serial.print(pressureMoreAccurate);
  Serial.print(",");
  Serial.print("'pressure_most_accurate':");
  Serial.print(pressureMostAccurate);
  Serial.print("}");
  Serial.println();
}

// example of a forced sample.  After taking the measurement the chip goes back to sleep
void bme280_forcedSample() {
  float temp, humidity, pressure, pressureMoreAccurate;
  double tempMostAccurate, humidityMostAccurate, pressureMostAccurate;

  // need to read the NVM compensation parameters
  BME280.readCompensationParams();
  
  // Need to turn on 1x oversampling, default is os_skipped, which means it doesn't measure anything
  BME280.writeOversamplingPressure(os1x);  // 1x over sampling (ie, just one sample)
  BME280.writeOversamplingTemperature(os1x);
  BME280.writeOversamplingHumidity(os1x);

  BME280.writeMode(smForced);

  while (BME280.isMeasuring()) {    }
  
  // read out the data - must do this before calling the getxxxxx routines
  BME280.readMeasurements();

  temp      = BME280.getTemperature();
  humidity  = BME280.getHumidity();
  pressure  = BME280.getPressure();
  
  pressureMoreAccurate = BME280.getPressureMoreAccurate();
  tempMostAccurate     = BME280.getTemperatureMostAccurate();
  humidityMostAccurate = BME280.getHumidityMostAccurate();
  pressureMostAccurate = BME280.getPressureMostAccurate();

  Serial.print("{");
  Serial.print("'sensor':'BME280'");
  Serial.print(",");
  Serial.print("'mode':'forced'");
  Serial.print(",");
  Serial.print("'temperature':");
  Serial.print(temp);
  Serial.print(",");
  Serial.print("'temperature_most_accurate':");
  Serial.print(tempMostAccurate);
  Serial.print(",");
  Serial.print("'humidity':");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print("'humidity_most_accurate':");
  Serial.print(humidityMostAccurate);
  Serial.print(",");
  Serial.print("'pressure':");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print("'pressure_more_accurate':");
  Serial.print(pressureMoreAccurate);
  Serial.print(",");
  Serial.print("'pressure_most_accurate':");
  Serial.print(pressureMostAccurate);
  Serial.print("}");
  Serial.println();
}

// Example for "indoor navigation"
// We'll switch into normal mode for regular automatic samples
void bme280_indoorSample() {
  
  BME280.writeStandbyTime(tsb_0p5ms);        // tsb = 0.5ms
  BME280.writeFilterCoefficient(fc_16);      // IIR Filter coefficient 16
  BME280.writeOversamplingPressure(os16x);    // pressure x16
  BME280.writeOversamplingTemperature(os2x);  // temperature x2
  BME280.writeOversamplingHumidity(os1x);     // humidity x1
  
  BME280.writeMode(smNormal);
  //Do nothing while measuring
  while (BME280.isMeasuring()) {    }
    
  // read out the data - must do this before calling the getxxxxx routines
  BME280.readMeasurements();
  printCompensatedMeasurements();
}
