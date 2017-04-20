#include <TEWeatherShield.h>

static TEWeatherShield weatherShield;

void setup() {
  Serial.begin(9600);
  weatherShield.begin();
}

void measure_htu21d() {
  float temperature;
  float humidity;

  weatherShield.selectHTU21D();

  if (weatherShield.HTU21D.is_connected()) {
    weatherShield.HTU21D.set_i2c_master_mode(htu21_i2c_no_hold);       
    weatherShield.HTU21D.read_temperature_and_relative_humidity(&temperature, &humidity); 
  
    Serial.print("{");
    Serial.print("'sensor':'HTU21D'");
    Serial.print(",");
    Serial.print("'temperature':");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print("'humidity':");
    Serial.print(humidity, 1);
    Serial.print("}");
    Serial.println();
  }
}

void measure_ms5637() {
  float temperature;
  float pressure;

  weatherShield.selectMS5637();

  if (weatherShield.MS5637.is_connected()) {    
    weatherShield.MS5637.read_temperature_and_pressure(&temperature, &pressure);
    
    Serial.print("{");
    Serial.print("'sensor':'MS5637'");
    Serial.print(",");
    Serial.print("'temperature':");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print("'pressure':");
    Serial.print(pressure, 1);
    Serial.print("}");
    Serial.println();
  }
}

void measure_ms8607() {
  float temperature;
  float pressure;
  float humidity;

  weatherShield.selectMS8607();

  if (weatherShield.MS8607.is_connected()) {    
    weatherShield.MS8607.set_humidity_i2c_master_mode(ms8607_i2c_hold); 
    weatherShield.MS8607.read_temperature_pressure_humidity( &temperature, &pressure, &humidity);
    
    Serial.print("{");
    Serial.print("'sensor':'MS8607'");
    Serial.print(",");
    Serial.print("'temperature':");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print("'pressure':");
    Serial.print(pressure, 1);
    Serial.print(",");
    Serial.print("'humidity':");
    Serial.print(humidity, 1);
    Serial.print("}");
    Serial.println();
  }
}

void measure_tsys01() {
  float temperature;

  weatherShield.selectTSYS01();

  if (weatherShield.TSYS01.is_connected()) {    
    weatherShield.TSYS01.read_temperature(&temperature);
    
    Serial.print("{");
    Serial.print("'sensor':'TSYS01'");
    Serial.print(",");
    Serial.print("'temperature':");
    Serial.print(temperature, 1);
    Serial.print("}");
    Serial.println();
  }
}

void measure_tsd305() {
  float temperature;
  float object_temperature;

  weatherShield.selectTSD305();

  if (weatherShield.TSD305.is_connected()) {    
    weatherShield.TSD305.read_temperature_and_object_temperature(&temperature, &object_temperature);
    
    Serial.print("{");
    Serial.print("'sensor':'TSD305'");
    Serial.print(",");
    Serial.print("'temperature':");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print("'object_temperature':");
    Serial.print(object_temperature, 1);
    Serial.print("}");
    Serial.println();
  }
}

void loop() {    
  measure_htu21d();
  measure_ms5637();
  measure_ms8607();
  measure_tsys01();
  measure_tsd305();

  //delay(5000);
  delay(300000);
}
