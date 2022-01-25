
// /////////////////////////  ////////////////////////////////////////
//                            INCLUDES
// /////////////////////////  ////////////////////////////////////////

#include "motors.h"
#include "config.h"

// /////////////////////////  ////////////////////////////////////////
//                            VARIABLES
// /////////////////////////  ////////////////////////////////////////

long mStepX;
long mStepY;
long mStepZ;
long mStepE0;

bool mCallbackCalled;
void (*mCallback)();

// /////////////////////////  ////////////////////////////////////////
//                            FUNCTIONS
// /////////////////////////  ////////////////////////////////////////

void motors_init(void (*callback)()) {

  // Set pins mode
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  pinMode(E0_STEP_PIN, OUTPUT);
  pinMode(E0_DIR_PIN, OUTPUT);
  pinMode(E0_ENABLE_PIN, OUTPUT);

  // Disable all motors

  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);
  digitalWrite(E0_ENABLE_PIN, HIGH);

  // Post initialization of motors
  
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(E0_STEP_PIN, LOW);
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);
  digitalWrite(E0_DIR_PIN, LOW);

  // Initialize variables

  mStepX = 0;
  mStepY = 0;
  mStepZ = 0;
  mStepE0 = 0;

  mCallbackCalled = true;
  mCallback = callback;
}

void motors_set(long x, long y, long z, long e0) {

  // Set motor bound on X
  if(x) {
    digitalWrite(X_ENABLE_PIN, LOW);  
    digitalWrite(X_DIR_PIN, x < 0 ? LOW : HIGH);
    mStepX = abs(x);
  }
  // Disable motor X
  else {
    digitalWrite(X_ENABLE_PIN, HIGH);
  }
  
  // Set motors bound on Y
  if(y) {
    digitalWrite(Y_ENABLE_PIN, LOW);  
    digitalWrite(Y_DIR_PIN, y < 0 ? LOW : HIGH);
    mStepY = abs(y);
  }
  // Disable motor Y
  else {
    digitalWrite(Y_ENABLE_PIN, HIGH);
  }
  
  // Set motors bound on Z
  if(z) {
    digitalWrite(Z_ENABLE_PIN, LOW);  
    digitalWrite(Z_DIR_PIN, z < 0 ? LOW : HIGH);
    mStepZ = abs(z);
  }
  // Disable motor Z
  else {
    digitalWrite(Z_ENABLE_PIN, HIGH);
  }
  
  // Set motors bound on E0
  if(e0) {
    digitalWrite(E0_ENABLE_PIN, LOW);  
    digitalWrite(E0_DIR_PIN, e0 < 0 ? LOW : HIGH);
    mStepE0 = abs(e0);
  }
  // Disable motor E0
  else {
    digitalWrite(E0_ENABLE_PIN, HIGH);
  }

  // Set callback
  mCallbackCalled = false;
}

void motors_run() {

  if(!mStepX) digitalWrite(X_ENABLE_PIN, HIGH);
  else mStepX -= 1;
  if(!mStepY) digitalWrite(Y_ENABLE_PIN, HIGH);
  else mStepY -= 1;
  if(!mStepZ) digitalWrite(Z_ENABLE_PIN, HIGH);
  else mStepZ -= 1;
  if(!mStepE0) digitalWrite(E0_ENABLE_PIN, HIGH);
  else mStepE0 -= 1;
  
  digitalWrite(X_STEP_PIN, HIGH);
  digitalWrite(Y_STEP_PIN, HIGH);
  digitalWrite(Z_STEP_PIN, HIGH);
  digitalWrite(E0_STEP_PIN, HIGH);
  delayMicroseconds(MOTOR_SPEED);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  digitalWrite(E0_STEP_PIN, LOW);
  delayMicroseconds(MOTOR_SPEED);

  if(!mStepX && !mStepY && !mStepZ && !mStepE0 && !mCallbackCalled) {
    mCallbackCalled = true;
    mCallback();
  }
  
}
