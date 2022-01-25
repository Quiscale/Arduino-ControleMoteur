
// /////////////////////////  ////////////////////////////////////////
//                            INCLUDES
// /////////////////////////  ////////////////////////////////////////

#include "serial.h"
#include "config.h"

// /////////////////////////  ////////////////////////////////////////
//                            FUNCTIONS
// /////////////////////////  ////////////////////////////////////////

const char separator = '\n';
const uint16_t buffer_size = 1000;
char buffer[buffer_size] = {0};
uint16_t buffer_i = 0;

/**
 * @brief Initialise la partie communicant via l'UART
 * 
 */
void serial_init() {

    Serial.begin(115200);

    // Serial.println("Serial begin");

}


/**
 * @brief Lit les octets entrant de l'UART, retourne une chaine de caractères contenant un message s'il y en a un
 * 
 * @return String Chaine de caractère contenant le topic et le message
 */
String serial_read() {

  uint16_t available = Serial.available();

  if(available) {

    return Serial.readStringUntil('\n');
  }

  return "";
}

/**
 * @brief Envoie toutes les données, reçues sur Rx, sur Tx
 * 
 */
void serial_echo() {
  if(Serial.available())
    Serial.print(Serial.readString());
}
