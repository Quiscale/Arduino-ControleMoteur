#ifndef UTILS_H
#define UTILS_H

// ////////////////////////////////////////////////////////
// Includes

#include "Arduino.h"
#include "motors.h"

// ////////////////////////////////////////////////////////
// Typedefs

struct Command_s {
  char letter;
  long value;
};
typedef struct Command_s Command_t;

// ////////////////////////////////////////////////////////
// Prototypes

Command_t utils_parseCommand(String command);
void utils_parseSerialMessage(String message);
void utils_mathForMotors(long x, long y, long r);

// ////////////////////////////////////////////////////////
// Functions

/**
 * Transforme une chaine de caractère composé de commandes (sous la forme XY, X commande, Y valeur) séparées par des espaces.
 * 
 */
void utils_parseSerialMessage(String message) {
  
  int i = 0;
  String tmp = "";

  Command_t comG;
  Command_t comX;
  Command_t comY;
  Command_t comR;

  // Go through the string and extract commands
  do {

    char c = message.charAt(i);
    if(c == ' ') {

      Command_t com = utils_parseCommand(tmp);

      switch(com.letter) {
        case 'G':
          comG = com; break;
        case 'X':
          comX = com; break;
        case 'Y':
          comY = com; break;
        case 'R':
          comR = com; break;
        default:
          break;
      }
      
      tmp = "";
        
    }
    else {
      tmp += c;
    }
    
  } while(message.charAt(++i) != '\0');
  
  Command_t com = utils_parseCommand(tmp);
  
  switch(com.letter) {
    case 'G':
      comG = com; break;
    case 'X':
      comX = com; break;
    case 'Y':
      comY = com; break;
    case 'R':
      comR = com; break;
    default:
      break;
  }

  if(comG.value == 1)
    utils_mathForMotors(comX.value, comY.value, comR.value);
  
}

/**
 * Parce a command string into a command struct
 */
Command_t utils_parseCommand(String command) {

   return {
    command.charAt(0),
    command.substring(1).toInt()
  };
}

/**
 * This functions do the math then ask the motors to go to a position
 */
void utils_mathForMotors(long x, long y, long r) {
  
  motors_set(x, y, r, 0);
}


#endif
