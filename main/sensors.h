#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "Wire.h"
#include "VL53L0X.h"

namespace sensors {

    VL53L0X vl;
    bool initialized = false;
    long lastDistance = -1;

    void init() {
        Wire.begin();
        //Wire.setClock(200000); // Set I²C to 400kHz

        vl.setTimeout(100);
        //vl.setAddress(0x25);
        //Serial.println(vl.getAddress(), HEX);
        if(!vl.init(false)) {
            Serial.println("Fail to init VL53L0X");
        }
        else {
            /*vl.setDistanceMode(VL53L1X::Long);
            vl.setMeasurementTimingBudget(50000);*/
            vl.startContinuous(100);
            Serial.println("Sensor initialized");
            initialized = true;
        }
    }

    void run() {
      static long timePassed = 0;

      // Compute distance
      if(millis() -timePassed > 200) {
        timePassed = millis();
        if(initialized) {
  
          lastDistance = vl.readRangeContinuousMillimeters();
          
          if(vl.timeoutOccurred()) {
            lastDistance = -1;
            Serial.print("TIMEOUT : ");
            sensors::init();
          }
        }
        else {
          lastDistance = -1;
          Serial.print("NOT INIT : ");
          sensors::init();
        }
      }
    }

    long getDistance() {
      return lastDistance;
    }
    n=
}

#endif
