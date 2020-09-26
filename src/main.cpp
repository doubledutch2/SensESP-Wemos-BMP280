// BMP280_example.cpp

#include <Arduino.h>

//#define SERIAL_DEBUG_DISABLED

#define USE_LIB_WEBSOCKET true

#include "sensesp_app.h"
#include "signalk/signalk_output.h"
#include "sensors/bmp280.h"
#include "i2c_tools.h"

// #include "sensors/i2c_tools.h"

ReactESP app([] () {
  #ifndef SERIAL_DEBUG_DISABLED
  Serial.begin(115200);

  // A small arbitrary delay is required to let the
  // serial port catch up

  delay(100);
  Debug.setSerialEnabled(true);
  #endif

  scan_i2c();
  
  // true will disable systemHz, freemem, uptime, and ipaddress "sensors"
  
  sensesp_app = new SensESPApp("SensESP","","","",0,NONE);

//scan_i2c();

// Create a BMP280, which represents the physical sensor.
// 0x77 is the default address. Some chips use 0x76, which is shown here.
auto* pBMP280 = new BMP280(0x76);


const uint read_delay = 30000;
const uint pressure_read_delay = 30000;

// Create a BMP280value, which is used to read a specific value from the BMP280, and send its output
// to SignalK as a number (float). This one is for the temperature reading.
auto* pBMPtemperature = new BMP280value(pBMP280, temperature,  read_delay, "/Temperature");
      
      pBMPtemperature->connectTo(new SKOutputNumber("environment.outside.temp"));


// Do the same for the barometric pressure value.
auto* pBMPpressure = new BMP280value(pBMP280, pressure,  pressure_read_delay, "/Pressure");
      
      pBMPpressure->connectTo(new SKOutputNumber("environment.outside.pressure"));
/*
// Do the same for the humidity value.
auto* pBMPhumidity = new BMP280value(pBMP280, humidity,  read_delay, "/Humidity");
      
      pBMPhumidity->connectTo(new SKOutputNumber());      

*/
  sensesp_app->enable();
});
