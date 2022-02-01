
#include "command.h"
#include "motors.h"
#include "config.h"

void setup() {
  Serial.begin(SERIAL_SPEED);

  motors::init(testCb);
  motors::set(0, 0, 0, 0);
}

void loop() {

  motors::run();

  if(Serial.available()) {
    Command* command = new Command(Serial.readString());
    command->execute();
    delete command;
  }

}

/**
 * Callback function when the motors are done moving
 */
void testCb() {
  Serial.println("move done");
}
