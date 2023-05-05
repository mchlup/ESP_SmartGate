#include <elapsedMillis.h>
#include "io.h" ;
#include "eeprom.h" ;
#include "wifi.h"
#include "ntp.h"
#include "webserver.h"
#include "handleCalendar.h"

#include "sta.h" ;
 
void setup() {
  Serial.begin(115200);
  setup_IO();
  setup_eeprom() ;
     delay(100);
  setup_Wifi() ;
     delay (100) ;
  setup_ntp() ;
  setup_Webserver() ;
}
 
void loop() {
  read_IOs();
  loop_Webserver() ;
  loop_ntp() ;
  handleDateTimeIO();
  handleRelayFunctions();

  print_STA();
}
