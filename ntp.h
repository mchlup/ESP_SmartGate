#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
const char* NTPServer = "europe.pool.ntp.org" ;
String aNTPServer ;
int NTPOffset ;
int NTPUpdateInterval = 86400 ;
NTPClient timeClient(ntpUDP, NTPServer);

String weekDays[7]={"NE", "PO", "UT", "ST", "CT", "PA", "SO"};
String months[12]={"Leden", "Únor", "Březen", "Duben", "Květen", "Červen", "Červenec", "Srpen", "Září", "Říjen", "Listopad", "Prosinec"};
String currentDate ;
String ActualDate ;
String ActualTime ;
int ActualTimeInt ;
int ActualDateInt ;
int currentHour ;
int currentMinute ;
int currentSecond ;
String currentWeekDay ;
int monthDay ;
int currentMonth ;
String currentMonthName ;
int currentYearInt ;
String  Holiday[12] ;

void setup_ntp() {
  timeClient.begin();
  timeClient.setTimeOffset(NTPOffset);
  timeClient.setUpdateInterval(NTPUpdateInterval);
  timeClient.update();
}

void recalc_Holidays() {
  Holiday[0] = String(currentYearInt)+String("-01-01") ;
  Holiday[1] = String(currentYearInt)+String("-10-28") ;
  Holiday[2] = String(currentYearInt)+String("-05-08") ;
  Holiday[3] = String(currentYearInt)+String("-07-05") ;
  Holiday[4] = String(currentYearInt)+String("-07-06") ;
  Holiday[5] = String(currentYearInt)+String("-09-28") ;
  Holiday[6] = String(currentYearInt)+String("-10-28") ;
  Holiday[7] = String(currentYearInt)+String("-11-17") ;
  Holiday[8] = String(currentYearInt)+String("-12-24") ;
  Holiday[9] = String(currentYearInt)+String("-12-25") ;
  Holiday[10] = String(currentYearInt)+String("-12-26") ;
  //Holiday[11] = String(currentYearInt)+String("-11-01") ;
}

void loop_ntp() {
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  ActualDate = formattedDate.substring(0, splitT);
  currentHour = timeClient.getHours();
  currentMinute = timeClient.getMinutes();
  currentSecond = timeClient.getSeconds();
  currentWeekDay = weekDays[timeClient.getDay()];
  currentDate = String(currentWeekDay) + " " + String(ActualDate) + " / " + String(formattedTime) ;
  
  //Extract Dates
  int commaIndexDate = formattedDate.indexOf('-');
  int secondCommaIndexDate = formattedDate.indexOf('-', commaIndexDate+1);
  int thirdCommaIndexDate = formattedDate.indexOf('-', secondCommaIndexDate+1);
  String currentYear = formattedDate.substring(0, commaIndexDate);
  String currentMonth = formattedDate.substring(commaIndexDate+1, secondCommaIndexDate);
  String monthDay = formattedDate.substring(secondCommaIndexDate+1, thirdCommaIndexDate);
  //Get a time structure
  ActualTime = String(currentHour) + String(currentMinute) ;
  int commaIndex = formattedTime.indexOf(':');
  int secondCommaIndex = formattedTime.indexOf(':', commaIndex+1);
  String formatedHour = formattedTime.substring(0, commaIndex);
  String formatedMinute = formattedTime.substring(commaIndex+1, secondCommaIndex);
  ActualTimeInt = String(String(formatedHour)+String(formatedMinute)).toInt();
  ActualDateInt = String(String(currentYear)+String(currentMonth)+String(monthDay)).toInt();
  currentYearInt = String(String(currentYear)).toInt();
  recalc_Holidays();
}
