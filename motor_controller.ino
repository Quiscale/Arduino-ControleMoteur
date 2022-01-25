
#include "motors.h"
#include "config.h"
#include "serial.h"
#include "utils.h"

long steps = MOTOR_FULL_TURN*10;


void setup() {

  serial_init();

  motors_init(testCb);
  motors_set(0, 0, 0, 0);

}

void loop() {

  motors_run();

  String inMsg = serial_read();
  if(inMsg.length()) {
    utils_parseSerialMessage(inMsg);
  }

}


/**
 * Callback function when the motors are done moving
 */
void testCb() {
  Serial.println("move done");
}
