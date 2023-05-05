#include <EEPROM.h>

int eeprom_add_Func[] = { 400, 401, 402, 403, 404, 405 } ;
int eeprom_add_Weekdays[] = {406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419 } ;
int eeprom_add_MyDate[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150 } ;
int eeprom_add_StartTime[] = { 200, 205, 210, 215, 220, 225, 230 } ;
int eeprom_add_R2_imp = 250 ; 
int eeprom_add_StopTime[] = { 300, 305, 310, 315, 320, 325, 330 } ;
int eeprom_add_NTP_server = 420 ;                                     // 32b
int eeprom_add_NTP_offset = 455 ;                                     // 4b
int eeprom_add_NTP_interval = 460 ;                                   // 4b
int eeprom_add_Hostname = 465 ;                                       // 16b
int eeprom_add_www_pass = 482 ;                                       // 16b
String eeprom_Function[5] ;
String eeprom_Holidays ;
String eeprom_MyDates ;
String eeprom_myWeekdays[14] ;
String eeprom_myDate[15] ;
String eepromStartTime[7] ;
String eepromEndTime[7] ;

void TextToEEPROM(int adresa, int maxVelikost, String text) {
  for (int i = 0;i < text.length();i++) {
    EEPROM.write(adresa + i, (byte)text[i]);
    }
  for (int i = text.length();i < maxVelikost;i++) {
    EEPROM.write(adresa + i, ' ');
  }  
}
 
String TextFromEEPROM(int adresa, int maxVelikost) {
  String TextFromEEPROM = "";
  for (int i = 0;i < maxVelikost;i++) {
    char znak = (char)EEPROM.read(adresa + i);
    TextFromEEPROM = TextFromEEPROM + znak;  
  }
  while (TextFromEEPROM[TextFromEEPROM.length() - 1] == ' ') {  
      TextFromEEPROM = TextFromEEPROM.substring(0,TextFromEEPROM.length() - 1);
    }
  return  TextFromEEPROM;
}

void setup_eeprom() {
  EEPROM.begin(512);
}

void clear_eeprom() {
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.end();
  ESP.reset();
}
