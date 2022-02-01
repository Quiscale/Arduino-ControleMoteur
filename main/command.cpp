
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include "command.h"
#include "motors.h"

// ////////////////////////////////////////////////////////////////////////////
// Command's method
// ////////////////////////////////////////////////////////////////////////////

Command::Command(String strCommand) {
    int size = strCommand.indexOf(' ');
    if(size == -1) {
        this->command = strCommand;
        this->nextCommand = nullptr;
    }
    else {
        this->command = strCommand.substring(0, size);
        this->nextCommand = new Command(strCommand.substring(size +1)); // +1 to jump the space
    }
}

Command::~Command() {
    delete this->nextCommand;
}

/**
 * @brief Can be use to execute registered command
 * 
 */
void Command::execute() {

    if(this->getLetter() == 'G') {
        switch(this->getValue()) {
            case 1:
                Command::controlDirection(this->getNext());
                break;
            default:
                Serial.println("Command not found");
        }
    }
}

/**
 * @brief Get the command
 * 
 * @return String The command
 */
String Command::getCommand() {
    return this->command;
}

/**
 * @brief Get the first character of getCommand()
 * 
 * @return char The command's letter
 */
char Command::getLetter() {
    return this->command.charAt(0);
}

/**
 * @brief Get the value stored after the command's letter
 * 
 * @return uint64_t The command's value
 */
long Command::getValue() {
    return this->command.substring(1).toInt();
}

/**
 * @brief Return the next command
 * 
 * @return Command* The next command
 */
Command* Command::getNext() {
    return this->nextCommand;
}

/**
 * @brief Set the motors from a given command
 * 
 * @param command 
 */
void Command::controlDirection(Command* command) {

    long x = 0, y = 0, r = 0;

    while(command != nullptr) {
        char l = command->getLetter();
        long v = command->getValue();

        if(l == 'X')
            x = v;
        if(l == 'Y')
            y = v;
        if(l == 'R')
            r = v;

        command = command->getNext();
    }

    // Do the maths
    Serial.print("X ");
    Serial.print(x);
    Serial.print(" Y ");
    Serial.print(y);
    Serial.print(" R ");
    Serial.println(r);

    motors::set(x, y, r, 0);
}