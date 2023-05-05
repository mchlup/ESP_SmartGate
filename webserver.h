//#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Arduino_JSON.h>
#include <FS.h>

ESP8266WebServer server(80);
JSONVar StatusData ;
JSONVar jsonSettings ;
JSONVar jsonWeekdays ;
JSONVar jsonExceptions ;
JSONVar jsonMyDates ;

const char* www_username = "admin";
const char* www_password = "admin";
String Awww_password ;
// allows you to set the realm of authentication Default:"Login Required"
const char* www_realm = "Custom Auth Realm";
// the Content of the HTML response in case of Unautherized Access Default:empty
String authFailResponse = "Authentication Failed";

String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);
String getStatus() ;
String getSettings() ;
String getPeriodicalTimes() ;
String getExceptionsDates() ;
String getDatesTimes() ;
void handleFormDates() ;
void handleLogin();
void handlePeriodicalTimes() ;
void handlePeriodicalControl() ;
void handleExceptions() ;
void handleFunction() ;
void handleRoot();
void handleNotFound();
void convertFormTimesToInt();
void convertFormMyDatesToInt();

String Function[6] ;
String myWeekday[14] ;
String myWeekdayCtrl[7];
String myDate[15] ;
String StartAtTime[7] ;
String StopAtTime[7] ;
int myDateInt[10] ;
int StartTime[7] ;
int StopTime[7] ;

void read_eeprom_data() {
  Serial.println ("VYCTENI DAT Z EEPROM");
  Function[0] = TextFromEEPROM(eeprom_add_Func[0],1);
  Function[1] = TextFromEEPROM(eeprom_add_Func[1],1);
  Function[2] = TextFromEEPROM(eeprom_add_Func[2],1);
  Function[3] = TextFromEEPROM(eeprom_add_Func[3],1);
  Function[4] = TextFromEEPROM(eeprom_add_Func[4],1);
  Function[5] = TextFromEEPROM(eeprom_add_Func[5],1);
  myWeekday[0] = TextFromEEPROM(eeprom_add_Weekdays[0],1);
  myWeekday[1] = TextFromEEPROM(eeprom_add_Weekdays[1],1);
  myWeekday[2] = TextFromEEPROM(eeprom_add_Weekdays[2],1);
  myWeekday[3] = TextFromEEPROM(eeprom_add_Weekdays[3],1);
  myWeekday[4] = TextFromEEPROM(eeprom_add_Weekdays[4],1);
  myWeekday[5] = TextFromEEPROM(eeprom_add_Weekdays[5],1);
  myWeekday[6] = TextFromEEPROM(eeprom_add_Weekdays[6],1);
  myWeekday[7] = TextFromEEPROM(eeprom_add_Weekdays[7],1);
  myWeekday[8] = TextFromEEPROM(eeprom_add_Weekdays[8],1);
  myWeekday[9] = TextFromEEPROM(eeprom_add_Weekdays[9],1);
  myWeekday[10] = TextFromEEPROM(eeprom_add_Weekdays[10],1);
  myWeekday[11] = TextFromEEPROM(eeprom_add_Weekdays[11],1);
  myWeekday[12] = TextFromEEPROM(eeprom_add_Weekdays[12],1);
  myWeekday[13] = TextFromEEPROM(eeprom_add_Weekdays[13],1);
  myWeekdayCtrl[0] = myWeekday[7] ;
  myWeekdayCtrl[1] = myWeekday[8] ;
  myWeekdayCtrl[2] = myWeekday[9] ;
  myWeekdayCtrl[3] = myWeekday[10] ;
  myWeekdayCtrl[4] = myWeekday[11] ;
  myWeekdayCtrl[5] = myWeekday[12] ;
  myWeekdayCtrl[6] = myWeekday[13] ;
  myDate[0] = TextFromEEPROM(eeprom_add_MyDate[0],10);
  myDate[1] = TextFromEEPROM(eeprom_add_MyDate[1],10);
  myDate[2] = TextFromEEPROM(eeprom_add_MyDate[2],10);
  myDate[3] = TextFromEEPROM(eeprom_add_MyDate[3],10);
  myDate[4] = TextFromEEPROM(eeprom_add_MyDate[4],10);
  myDate[5] = TextFromEEPROM(eeprom_add_MyDate[5],10);
  myDate[6] = TextFromEEPROM(eeprom_add_MyDate[6],10);
  myDate[7] = TextFromEEPROM(eeprom_add_MyDate[7],10);
  myDate[8] = TextFromEEPROM(eeprom_add_MyDate[8],10);
  myDate[9] = TextFromEEPROM(eeprom_add_MyDate[9],10);
  myDate[10] = TextFromEEPROM(eeprom_add_MyDate[10],10);
  myDate[11] = TextFromEEPROM(eeprom_add_MyDate[11],10);
  myDate[12] = TextFromEEPROM(eeprom_add_MyDate[12],10);
  myDate[13] = TextFromEEPROM(eeprom_add_MyDate[13],10);
  myDate[14] = TextFromEEPROM(eeprom_add_MyDate[14],10);
  StartAtTime[0] = TextFromEEPROM(eeprom_add_StartTime[0],5);
  StartAtTime[1] = TextFromEEPROM(eeprom_add_StartTime[1],5);
  StartAtTime[2] = TextFromEEPROM(eeprom_add_StartTime[2],5);
  StartAtTime[3] = TextFromEEPROM(eeprom_add_StartTime[3],5);
  StartAtTime[4] = TextFromEEPROM(eeprom_add_StartTime[4],5);
  StartAtTime[5] = TextFromEEPROM(eeprom_add_StartTime[5],5);
  StartAtTime[6] = TextFromEEPROM(eeprom_add_StartTime[6],5);
  StopAtTime[0] = TextFromEEPROM(eeprom_add_StopTime[0],5);
  StopAtTime[1] = TextFromEEPROM(eeprom_add_StopTime[1],5);
  StopAtTime[2] = TextFromEEPROM(eeprom_add_StopTime[2],5);
  StopAtTime[3] = TextFromEEPROM(eeprom_add_StopTime[3],5);
  StopAtTime[4] = TextFromEEPROM(eeprom_add_StopTime[4],5);
  StopAtTime[5] = TextFromEEPROM(eeprom_add_StopTime[5],5);
  StopAtTime[6] = TextFromEEPROM(eeprom_add_StopTime[6],5);
  REL2_interval = TextFromEEPROM(eeprom_add_R2_imp,4).toInt();
  NTPOffset = TextFromEEPROM(eeprom_add_NTP_offset,4).toInt();
    timeClient.setTimeOffset(NTPOffset);
  aNTPServer = TextFromEEPROM(eeprom_add_NTP_server,32) ;
  NTPServer = aNTPServer.c_str();
  aHostname = TextFromEEPROM(eeprom_add_Hostname,16) ;
  Awww_password = TextFromEEPROM(eeprom_add_www_pass,16) ;
  www_password = Awww_password.c_str();
}

void setup_Webserver() {
  /*
  if (!MDNS.begin("ESP8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder didn't started");
  } else {
    Serial.println("Setting up MDNS responder!");
  }
  */
  SPIFFS.begin() ;
  server.on("/", []() {
    if (!server.authenticate(www_username, www_password))
      {
      return server.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
    }
    //server.serveStatic("/", SPIFFS, "/index.html");
    server.sendHeader("Location", String("/index.html"), true);
    server.send(302, "text/plain", "");
    //server.send(200, SPIFFS, "/index.html");
  });
  server.serveStatic("/", SPIFFS, "/index.html");
  //server.on("/login", HTTP_POST, handleLogin);
  server.serveStatic("/index.html", SPIFFS, "/index.html");
  server.serveStatic("/style.css", SPIFFS, "/style.css");
  server.on("/status", [](){
    String jsonStatus = getStatus();
    server.send(200, "application/json", jsonStatus);
  });
  server.on("/loadPeriodicalTimes", [](){
    String jsonloadPeriodicalTimes = getPeriodicalTimes();
    server.send(200, "application/json", jsonloadPeriodicalTimes);
  });
  server.on("/loadExceptions", [](){
    String jsonloadExceptions = getExceptionsDates();
    server.send(200, "application/json", jsonloadExceptions);
  });
  server.on("/loadDatesTimes", [](){
    String jsonloadDatesTimes = getDatesTimes();
    server.send(200, "application/json", jsonloadDatesTimes);
  });
  server.on("/wifireset", wifiReset);
  server.on("/cleareeprom", clear_eeprom);
  server.on("/relay2off", Relay2off);
  server.on("/relay2on", Relay2on);
  server.on("/update", handleFunction);
  server.on("/setWeekdays", handlePeriodicalTimes);
  server.on("/setWeekdaysControl", handlePeriodicalControl);
  server.on("/saveSettings", HTTP_POST, handleFormDates);
  server.onNotFound([]() { // If the client requests any URI
    if (!handleFileRead(server.uri())) // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });  
  server.begin();
  Serial.println("Webserver started");
  delay(100);
  read_eeprom_data();
  delay(100);
  convertFormTimesToInt();
  delay(100);
  convertFormMyDatesToInt();
}

void loop_Webserver() {
  server.handleClient(); //make the ESP32 respond to web clients
}

String getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html"; // If a folder is requested, send the index file
  String contentType = getContentType(path); // Get the MIME type
  if (SPIFFS.exists(path)) { // If the file exists
    File file = SPIFFS.open(path, "r"); // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close(); // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false; // If the file doesn't exist, return false
}

String getStatus(){
  StatusData["FunctionPeriodic"] = String(Function[0]);
  StatusData["FunctionHolidays"] = String(Function[1]);
  StatusData["FunctionExceptions"] = String(Function[2]);
  StatusData["FunctionMyDates"] = String(Function[3]);
  StatusData["FunctionPeriodicControl"] = String(Function[4]);
  StatusData["FunctionMyDatesControl"] = String(Function[5]);
  StatusData["DateTime"] = String(currentDate);
  StatusData["Relay1State"] = String(relay1State);
  StatusData["Relay2State"] = String(relay2State);
  StatusData["Input1State"] = String(input1State);
  StatusData["Input2State"] = String(input2State);
  StatusData["Hostname"] = String(aHostname);
  StatusData["NTPserver"] = String(NTPServer);
  StatusData["NTPoffset"] = String(NTPOffset);
  StatusData["NTPinterval"] = String(NTPUpdateInterval);
  StatusData["REL2_interval"] = String(REL2_interval);
  String jsonString = JSON.stringify(StatusData);
  return jsonString;
}

String getPeriodicalTimes(){
  jsonWeekdays["myMondays"] = String(myWeekday[1]) ;
  jsonWeekdays["myTuesdays"] = String(myWeekday[2]);
  jsonWeekdays["myWednesdays"] = String(myWeekday[3]);
  jsonWeekdays["myThursdays"] = String(myWeekday[4]);
  jsonWeekdays["myFridays"] = String(myWeekday[5]);
  jsonWeekdays["mySaturdays"] = String(myWeekday[6]);
  jsonWeekdays["mySundays"] = String(myWeekday[0]);
  jsonWeekdays["myMondaysControl"] = String(myWeekday[8]) ;
  jsonWeekdays["myTuesdaysControl"] = String(myWeekday[9]);
  jsonWeekdays["myWednesdaysControl"] = String(myWeekday[10]);
  jsonWeekdays["myThursdaysControl"] = String(myWeekday[11]);
  jsonWeekdays["myFridaysControl"] = String(myWeekday[12]);
  jsonWeekdays["mySaturdaysControl"] = String(myWeekday[13]);
  jsonWeekdays["mySundaysControl"] = String(myWeekday[7]);
  jsonWeekdays["StartTime6"] = String(StartAtTime[5]);
  jsonWeekdays["EndTime6"] = String(StopAtTime[5]);
  jsonWeekdays["StartTime7"] = String(StartAtTime[6]);
  jsonWeekdays["EndTime7"] = String(StopAtTime[6]);
  String jsonStringPeriodicals = JSON.stringify(jsonWeekdays);
  return jsonStringPeriodicals;
}

String getExceptionsDates(){
  jsonExceptions["myException1"] = String(myDate[10]);
  jsonExceptions["myException2"] = String(myDate[11]);
  jsonExceptions["myException3"] = String(myDate[12]);
  jsonExceptions["myException4"] = String(myDate[13]);
  jsonExceptions["myException5"] = String(myDate[14]);
  String jsonStringExceptions = JSON.stringify(jsonExceptions);
  //Serial.println(jsonString);
  return jsonStringExceptions ;
}

String getDatesTimes(){
  jsonMyDates["myDate1"] = String(myDate[0]);
  jsonMyDates["myDate2"] = String(myDate[1]);
  jsonMyDates["myDate3"] = String(myDate[2]);
  jsonMyDates["myDate4"] = String(myDate[3]);
  jsonMyDates["myDate5"] = String(myDate[4]);
  jsonMyDates["myDate6"] = String(myDate[5]);
  jsonMyDates["myDate7"] = String(myDate[6]);
  jsonMyDates["myDate8"] = String(myDate[7]);
  jsonMyDates["myDate9"] = String(myDate[8]);
  jsonMyDates["myDate10"] = String(myDate[9]);
  jsonMyDates["StartTime1"] = String(StartAtTime[0]);
  jsonMyDates["StartTime2"] = String(StartAtTime[1]);
  jsonMyDates["StartTime3"] = String(StartAtTime[2]);
  jsonMyDates["StartTime4"] = String(StartAtTime[3]);
  jsonMyDates["StartTime5"] = String(StartAtTime[4]);
  jsonMyDates["EndTime1"] = String(StopAtTime[0]);
  jsonMyDates["EndTime2"] = String(StopAtTime[1]);
  jsonMyDates["EndTime3"] = String(StopAtTime[2]);
  jsonMyDates["EndTime4"] = String(StopAtTime[3]);
  jsonMyDates["EndTime5"] = String(StopAtTime[4]);
  String jsonStringFunctions = JSON.stringify(jsonMyDates);
  //Serial.println(jsonString);
  return jsonStringFunctions;
}

void convertFormTimesToInt() {
  String StartHour[7] ;
  String StartMinute[7] ;
  String EndHour[7] ;
  String EndMinute[7] ;
  for (byte a = 0; a < 7; a = a + 1) {
    int commaIndex = StartAtTime[a].indexOf(':');
    int secondCommaIndex = StartAtTime[a].indexOf(':', commaIndex+1);
    int commaIndex2 = StopAtTime[a].indexOf(':');
    int secondCommaIndex2 = StopAtTime[a].indexOf(':', commaIndex2+1);
    StartHour[a] = StartAtTime[a].substring(0, commaIndex);
    StartMinute[a] = StartAtTime[a].substring(commaIndex+1, secondCommaIndex);
    EndHour[a] = StopAtTime[a].substring(0, commaIndex2);
    EndMinute[a] = StopAtTime[a].substring(commaIndex2+1, secondCommaIndex2);
    StartTime[a] = String(String(StartHour[a])+String(StartMinute[a])).toInt();
    StopTime[a] = String(String(EndHour[a])+String(EndMinute[a])).toInt();
  }
}



void convertFormMyDatesToInt() {
  String myYearInt[10] ;
  String myMonthInt[10] ;
  String myDayInt[10] ;
  //for (int date = 0; date < 6; date = date++) {
    int myDateCommaIndex0 = myDate[0].indexOf('-');
    int myDateSecondCommaIndex0 = myDate[0].indexOf('-', myDateCommaIndex0+1);
    int myDateThirdCommaIndex0 = myDate[0].indexOf('-', myDateSecondCommaIndex0+1);
   
    int myDateCommaIndex1 = myDate[1].indexOf('-');
    int myDateSecondCommaIndex1 = myDate[1].indexOf('-', myDateCommaIndex1+1);
    int myDateThirdCommaIndex1 = myDate[1].indexOf('-', myDateSecondCommaIndex1+1);
    
    int myDateCommaIndex2 = myDate[2].indexOf('-');
    int myDateSecondCommaIndex2 = myDate[2].indexOf('-', myDateCommaIndex2+1);
    int myDateThirdCommaIndex2 = myDate[2].indexOf('-', myDateSecondCommaIndex2+1);
    
    int myDateCommaIndex3 = myDate[3].indexOf('-');
    int myDateSecondCommaIndex3 = myDate[3].indexOf('-', myDateCommaIndex3+1);
    int myDateThirdCommaIndex3 = myDate[3].indexOf('-', myDateSecondCommaIndex3+1);

    int myDateCommaIndex4 = myDate[4].indexOf('-');
    int myDateSecondCommaIndex4 = myDate[4].indexOf('-', myDateCommaIndex4+1);
    int myDateThirdCommaIndex4 = myDate[4].indexOf('-', myDateSecondCommaIndex4+1);

    int myDateCommaIndex5 = myDate[5].indexOf('-');
    int myDateSecondCommaIndex5 = myDate[5].indexOf('-', myDateCommaIndex5+1);
    int myDateThirdCommaIndex5 = myDate[5].indexOf('-', myDateSecondCommaIndex5+1);

    int myDateCommaIndex6 = myDate[6].indexOf('-');
    int myDateSecondCommaIndex6 = myDate[6].indexOf('-', myDateCommaIndex6+1);
    int myDateThirdCommaIndex6 = myDate[6].indexOf('-', myDateSecondCommaIndex6+1);

    int myDateCommaIndex7 = myDate[7].indexOf('-');
    int myDateSecondCommaIndex7 = myDate[7].indexOf('-', myDateCommaIndex7+1);
    int myDateThirdCommaIndex7 = myDate[7].indexOf('-', myDateSecondCommaIndex7+1);

    int myDateCommaIndex8 = myDate[8].indexOf('-');
    int myDateSecondCommaIndex8 = myDate[8].indexOf('-', myDateCommaIndex8+1);
    int myDateThirdCommaIndex8 = myDate[8].indexOf('-', myDateSecondCommaIndex8+1);

    int myDateCommaIndex9 = myDate[9].indexOf('-');
    int myDateSecondCommaIndex9 = myDate[9].indexOf('-', myDateCommaIndex9+1);
    int myDateThirdCommaIndex9 = myDate[9].indexOf('-', myDateSecondCommaIndex9+1);
    
    myYearInt[0] = myDate[0].substring(0, myDateCommaIndex0);
    myMonthInt[0] = myDate[0].substring(myDateCommaIndex0+1, myDateSecondCommaIndex0);
    myDayInt[0] = myDate[0].substring(myDateSecondCommaIndex0+1, myDateThirdCommaIndex0) ;

    myYearInt[1] = myDate[1].substring(0, myDateCommaIndex1);
    myMonthInt[1] = myDate[1].substring(myDateCommaIndex1+1, myDateSecondCommaIndex1);
    myDayInt[1] = myDate[1].substring(myDateSecondCommaIndex1+1, myDateThirdCommaIndex1) ;

    myYearInt[2] = myDate[2].substring(0, myDateCommaIndex2);
    myMonthInt[2] = myDate[2].substring(myDateCommaIndex2+1, myDateSecondCommaIndex2);
    myDayInt[2] = myDate[2].substring(myDateSecondCommaIndex2+1, myDateThirdCommaIndex2) ;

    myYearInt[3] = myDate[3].substring(0, myDateCommaIndex3);
    myMonthInt[3] = myDate[3].substring(myDateCommaIndex3+1, myDateSecondCommaIndex3);
    myDayInt[3] = myDate[3].substring(myDateSecondCommaIndex3+1, myDateThirdCommaIndex3) ;

    myYearInt[4] = myDate[4].substring(0, myDateCommaIndex4);
    myMonthInt[4] = myDate[4].substring(myDateCommaIndex4+1, myDateSecondCommaIndex4);
    myDayInt[4] = myDate[4].substring(myDateSecondCommaIndex4+1, myDateThirdCommaIndex4) ;

    myYearInt[5] = myDate[5].substring(0, myDateCommaIndex5);
    myMonthInt[5] = myDate[5].substring(myDateCommaIndex5+1, myDateSecondCommaIndex5);
    myDayInt[5] = myDate[5].substring(myDateSecondCommaIndex5+1, myDateThirdCommaIndex5) ;

    myYearInt[6] = myDate[6].substring(0, myDateCommaIndex6);
    myMonthInt[6] = myDate[6].substring(myDateCommaIndex6+1, myDateSecondCommaIndex6);
    myDayInt[6] = myDate[6].substring(myDateSecondCommaIndex6+1, myDateThirdCommaIndex6) ;

    myYearInt[7] = myDate[7].substring(0, myDateCommaIndex7);
    myMonthInt[7] = myDate[7].substring(myDateCommaIndex7+1, myDateSecondCommaIndex7);
    myDayInt[7] = myDate[7].substring(myDateSecondCommaIndex7+1, myDateThirdCommaIndex7) ;

    myYearInt[8] = myDate[8].substring(0, myDateCommaIndex8);
    myMonthInt[8] = myDate[8].substring(myDateCommaIndex8+1, myDateSecondCommaIndex8);
    myDayInt[8] = myDate[8].substring(myDateSecondCommaIndex8+1, myDateThirdCommaIndex8) ;

    myYearInt[9] = myDate[9].substring(0, myDateCommaIndex9);
    myMonthInt[9] = myDate[9].substring(myDateCommaIndex9+1, myDateSecondCommaIndex9);
    myDayInt[9] = myDate[9].substring(myDateSecondCommaIndex9+1, myDateThirdCommaIndex9) ;
    
    myDateInt[0] = String(String(myYearInt[0]) + String(myMonthInt[0]) + String(myDayInt[0]) ).toInt();
    myDateInt[1] = String(String(myYearInt[1]) + String(myMonthInt[1]) + String(myDayInt[1]) ).toInt();
    myDateInt[2] = String(String(myYearInt[2]) + String(myMonthInt[2]) + String(myDayInt[2]) ).toInt();
    myDateInt[3] = String(String(myYearInt[3]) + String(myMonthInt[3]) + String(myDayInt[3]) ).toInt();
    myDateInt[4] = String(String(myYearInt[4]) + String(myMonthInt[4]) + String(myDayInt[4]) ).toInt();
    myDateInt[5] = String(String(myYearInt[5]) + String(myMonthInt[5]) + String(myDayInt[5]) ).toInt();
    myDateInt[6] = String(String(myYearInt[6]) + String(myMonthInt[6]) + String(myDayInt[6]) ).toInt();
    myDateInt[7] = String(String(myYearInt[7]) + String(myMonthInt[7]) + String(myDayInt[7]) ).toInt();
    myDateInt[8] = String(String(myYearInt[8]) + String(myMonthInt[8]) + String(myDayInt[8]) ).toInt();
    myDateInt[9] = String(String(myYearInt[8]) + String(myMonthInt[9]) + String(myDayInt[9]) ).toInt();
  //}
  
}


void handleFormDates() {
  for (byte b = 0 ; b < 15 ; b++) {
    String myDateString = "date" + String((b)+1);
        //----------------MyDates--------------
    if ( server.hasArg( myDateString ) && server.arg( myDateString ) != NULL ) {
      myDate[b] = server.arg( myDateString );
      TextToEEPROM(eeprom_add_MyDate[b],10,String(myDate[b]));
      Serial.println (myDateString);
    }
  }
  for (byte c = 0 ; c < 7 ; c++) {
    String StartTimeString = "startTime" + String((c)+1);
    String StopTimeString = "endTime" + String((c)+1);
    //---------------Spousteci casy-----------------------------
    if ( server.hasArg( StartTimeString ) && server.arg( StartTimeString ) != NULL ) {
      StartAtTime[c] = server.arg( StartTimeString );
      TextToEEPROM(eeprom_add_StartTime[c],5,String(StartAtTime[c]));
      Serial.println ("StartTimeString: " + StartAtTime[c]);
    }
    //------------------Stopovaci casy--------------------
    if ( server.hasArg( StopTimeString ) && server.arg( StopTimeString ) != NULL ) {
      StopAtTime[c] = server.arg( StopTimeString );
      TextToEEPROM(eeprom_add_StopTime[c],5,String(StopAtTime[c]));
      Serial.println ("StopTimeString: " + StopAtTime[c]);
    }
  }
  // -------------- NASTAVENI ------------------
  if (server.arg("hostname") != NULL ) {
    Serial.println ("Hostname: " + String(server.arg("hostname")) );
    aHostname = server.arg("hostname") ;
    TextToEEPROM(eeprom_add_Hostname,16,String(aHostname));
  }
  if (server.arg("ntpServer") != NULL ) {
    Serial.println ("NTP server: " + String(server.arg("ntpServer")) );
    aNTPServer = server.arg("ntpServer") ;
    NTPServer = aNTPServer.c_str();
    //timeClient.update();
    TextToEEPROM(eeprom_add_NTP_server,32,String(aNTPServer));
  }
  if (server.arg("ntpUpdate") != NULL ) {
    Serial.println ("NTP update interval: " + String(server.arg("ntpUpdate")) );
    NTPUpdateInterval = server.arg("ntpUpdate").toInt() ;
    TextToEEPROM(eeprom_add_NTP_interval,4,String(NTPUpdateInterval));
  }
  if (server.arg("ntpOffset") != NULL ) {
    Serial.println ("NTP Offset: " + String(server.arg("ntpOffset")) );
    NTPOffset = server.arg("ntpOffset").toInt() ;
    TextToEEPROM(eeprom_add_NTP_offset,4,String(NTPOffset));
    timeClient.setTimeOffset(NTPOffset);
  }
  if (server.arg("www_password") != NULL ) {
    Serial.println ("WWW pass: " + String(server.arg("www_password")) );
    Awww_password = server.arg("www_password") ;
    www_password = Awww_password.c_str();
    TextToEEPROM(eeprom_add_www_pass,16,String(Awww_password));
  }
  if (server.arg("r2_impuls") != NULL ) {
    Serial.println ("R2 Imp. Lenght: " + String(server.arg("r2_impuls")) );
    REL2_interval = server.arg("r2_impuls").toInt() ;
    TextToEEPROM(eeprom_add_R2_imp,4,String(REL2_interval));
  }

  convertFormTimesToInt();  
  convertFormMyDatesToInt();
  EEPROM.commit();
  server.sendHeader("Location", String("/index.html#timers"), true);
  server.send(302, "text/plain", "");
}

void handlePeriodicalTimes(){
  String message = "#Args:" + String(server.args()) + "\n";
  for (int d = 0; d < server.args(); d++)
    message.concat(server.argName(d) + ": "+ server.arg(d) + "\n"); 
  Serial.print(message);
  
  if (server.arg("monday") == "1" ) {
    Serial.println ("Zapinam PO");
    myWeekday[1] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[1],1,String(myWeekday[1]));
  } else if (server.arg("monday") == "0" ) {
    Serial.println ("Vypinam PO");
    myWeekday[1] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[1],1,String(myWeekday[1]));
  }
  if (server.arg("tuesday") == "1" ) {
    Serial.println ("Zapinam UT");
    myWeekday[2] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[2],1,String(myWeekday[2]));
  } else if (server.arg("tuesday") == "0" ) {
    Serial.println ("Vypinam UT");
    myWeekday[2] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[2],1,String(myWeekday[2]));
  }
  if (server.arg("wednesday") == "1" ) {
    Serial.println ("Zapinam ST");
    myWeekday[3] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[3],1,String(myWeekday[3]));
  } else if (server.arg("wednesday") == "0" ) {
    Serial.println ("Vypinam ST");
    myWeekday[3] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[3],1,String(myWeekday[3]));
  }
  if (server.arg("thursday") == "1" ) {
    Serial.println ("Zapinam CT");
    myWeekday[4] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[4],1,String(myWeekday[4]));
  } else if (server.arg("thursday") == "0" ) {
    Serial.println ("Vypinam CT");
    myWeekday[4] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[4],1,String(myWeekday[4]));
  }
  if (server.arg("friday") == "1" ) {
    Serial.println ("Zapinam PA");
    myWeekday[5] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[5],1,String(myWeekday[5]));
  } else if (server.arg("friday") == "0" ) {
    Serial.println ("Vypinam PA");
    myWeekday[5] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[5],1,String(myWeekday[5]));
  }
  if (server.arg("saturday") == "1" ) {
    Serial.println ("Zapinam SO");
    myWeekday[6] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[6],1,String(myWeekday[6]));
  } else if (server.arg("saturday") == "0" ) {
    Serial.println ("Vypinam SO");
    myWeekday[6] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[6],1,String(myWeekday[6]));
  }
  if (server.arg("sunday") == "1" ) {
    Serial.println ("Zapinam NE");
    myWeekday[0] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[0],1,String(myWeekday[0]));
  } else if (server.arg("sunday") == "0" ) {
    Serial.println ("Vypinam NE");
    myWeekday[0] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[0],1,String(myWeekday[0]));
  }
  EEPROM.commit();
  server.send(200, "text/plain", "");
}

void handlePeriodicalControl(){
  String message = "#Args:" + String(server.args()) + "\n";
  for (int d = 0; d < server.args(); d++)
    message.concat(server.argName(d) + ": "+ server.arg(d) + "\n"); 
  Serial.print(message);
  
  if (server.arg("monday_ctrl") == "1" ) {
    Serial.println ("Zapinam PO CTRL");
    myWeekdayCtrl[1] = "1" ;
    myWeekday[8] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[8],1,String(myWeekday[8]));
  } else if (server.arg("monday_ctrl") == "0" ) {
    Serial.println ("Vypinam PO CTRL");
    myWeekdayCtrl[1] = "0" ;
    myWeekday[8] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[8],1,String(myWeekday[8]));
  }
  if (server.arg("tuesday_ctrl") == "1" ) {
    Serial.println ("Zapinam UT CTRL");
    myWeekdayCtrl[2] = "1" ;
    myWeekday[9] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[9],1,String(myWeekday[9]));
  } else if (server.arg("tuesday_ctrl") == "0" ) {
    Serial.println ("Vypinam UT CTRL");
    myWeekdayCtrl[2] = "0" ;
    myWeekday[9] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[9],1,String(myWeekday[9]));
  }
  if (server.arg("wednesday_ctrl") == "1" ) {
    Serial.println ("Zapinam ST CTRL");
    myWeekdayCtrl[3] = "1" ;
    myWeekday[10] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[10],1,String(myWeekday[10]));
  } else if (server.arg("wednesday_ctrl") == "0" ) {
    Serial.println ("Vypinam ST CTRL");
    myWeekdayCtrl[3] = "0" ;
    myWeekday[10] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[10],1,String(myWeekday[10]));
  }
  if (server.arg("thursday_ctrl") == "1" ) {
    Serial.println ("Zapinam CT CTRL");
    myWeekdayCtrl[4] = "1" ;
    myWeekday[11] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[11],1,String(myWeekday[11]));
  } else if (server.arg("thursday_ctrl") == "0" ) {
    Serial.println ("Vypinam CT CTRL");
    myWeekdayCtrl[4] = "0" ;
    myWeekday[11] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[11],1,String(myWeekday[11]));
  }
  if (server.arg("friday_ctrl") == "1" ) {
    Serial.println ("Zapinam PA CTRL");
    myWeekdayCtrl[5] = "1" ;
    myWeekday[12] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[12],1,String(myWeekday[12]));
  } else if (server.arg("friday_ctrl") == "0" ) {
    Serial.println ("Vypinam PA CTRL");
    myWeekday[12] = "0" ;
    myWeekdayCtrl[5] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[12],1,String(myWeekday[12]));
  }
  if (server.arg("saturday_ctrl") == "1" ) {
    Serial.println ("Zapinam SO CTRL");
    myWeekdayCtrl[6] = "1" ;
    myWeekday[13] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[13],1,String(myWeekday[13]));
  } else if (server.arg("saturday_ctrl") == "0" ) {
    Serial.println ("Vypinam SO CTRL");
    myWeekdayCtrl[6] = "0" ;
    myWeekday[13] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[13],1,String(myWeekday[13]));
  }
  if (server.arg("sunday_ctrl") == "1" ) {
    Serial.println ("Zapinam NE CTRL");
    myWeekdayCtrl[0] = "1" ;
    myWeekday[7] = "1" ;
    TextToEEPROM(eeprom_add_Weekdays[7],1,String(myWeekday[7]));
  } else if (server.arg("sunday_ctrl") == "0" ) {
    Serial.println ("Vypinam NE CTRL");
    myWeekdayCtrl[0] = "0" ;
    myWeekday[7] = "0" ;
    TextToEEPROM(eeprom_add_Weekdays[7],1,String(myWeekday[7]));
  }
  EEPROM.commit();
  server.send(200, "text/plain", "");
}

void handleFunction() {
  for (int e = 0; e < 7 ; e++) {
    if (server.arg("F" + String(e) + "state") == "1" ) {
      Serial.println ("Zapinam F" + String(e));
      Function[e] = "1" ;
      TextToEEPROM(eeprom_add_Func[e],1,String(Function[e]));
      EEPROM.commit();
    } else if (server.arg("F" + String(e) + "state") == "0" ) {
      Serial.println ("Vypinam F" + String(e));
      Function[e] = "0" ;
      TextToEEPROM(eeprom_add_Func[e],1,String(Function[e]));
      EEPROM.commit();
    }
  }
  server.send(200, "text/plain", "OK");
}
