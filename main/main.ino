
#include "command.h"
#include "motors.h"
#include "sensors.h"
#include "config.h"

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Helo");

  sensors::init();

  motors::init(testCb);
  motors::set(0, 0, 6400, 0);
}

void loop() {

  sensors::run();
  motors::run();

  /*if(Serial.available()) {
    Command* command = new Command(Serial.readString());
    command->execute();
    delete command;
  }*/

}

/**
 * Callback function when the motors are done moving
 */
void testCb() {

  long distance = sensors::getDistance();

  if(distance != -1) {
    
    if(distance > 100) {
      Serial.println("MOVE FRONT");
      motors::set(0, 0, 6400, 0);
    }
    else {
      Serial.println("MOVE LEFT");
      motors::set(0, 0, -6400, 0);
    }
  }
  else {
    motors::set(0, 0, 0, 0);
  }
  
}
