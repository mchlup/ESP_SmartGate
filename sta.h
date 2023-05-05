//#include <elapsedMillis.h>
elapsedMillis STA_timeElapsed; //declare global if you don't want it reset every time loop runs
unsigned int STA_interval = 3000;

void print_STA() {
  if (STA_timeElapsed > STA_interval)   {
    Serial.println(" ----- STA ----- ");
    Serial.println ("Hostname: " + String(aHostname));
    Serial.print ("IP: ");
      Serial.println(WiFi.localIP());
    Serial.println ("Current Date & Time: " + currentDate) ;
    Serial.println ("HTTP Status: " + getStatus()) ;
    Serial.println ("HTTP Exceptions: " + getExceptionsDates());
    Serial.println ("HTTP MyDates: " + getDatesTimes());
    Serial.println ("NTP offset: " + String(NTPOffset));
    Serial.println ("NTP Server: " + String(NTPServer));
    Serial.println ("Pass: " + String(www_password));
    //Serial.println ("Per.Start Time: " + String(StartTime[5])) ;
    //Serial.println ("Per.Stop Time: " + String(StopTime[5])) ;
    //Serial.println ("Active function: " + String(setFunction));
    Serial.println ("Periodical TAG: " + String(isPeriod) ) ;
    Serial.println ("Holiday TAG: " + String(isHoliday) ) ;
    Serial.println ("Exception TAG: " + String(isException) ) ;
    Serial.println ("MyDate TAG: " + String(isMyDate) ) ;
    Serial.print ("myDate0-1: " + String(myDateInt[0]));
     Serial.println (" - " + String(myDateInt[1]));
    Serial.print ("myDate2-3: " + String(myDateInt[2]) ) ;
     Serial.println (" - " + String(myDateInt[3]) ) ;
    Serial.print ("myDate4-5: " + String(myDateInt[4]) ) ;
     Serial.println (" - " + String(myDateInt[5]) ) ;
    Serial.print ("myDate6-7: " + String(myDateInt[6]) ) ;
     Serial.println (" - " + String(myDateInt[7]) ) ;
    Serial.print ("myDate8-9: " + String(myDateInt[8]) ) ;
     Serial.println (" - " + String(myDateInt[9]) ) ;
    Serial.println ("CTRL Relay2: " + String(isControlRelay) ) ;
    Serial.println ("CTRL Relay2st: " + String(relay2State) ) ;
    Serial.println ("REL2_timer: " + String(REL2_interval) ) ;
    Serial.println ("REL2_elasp: " + String(REL2_timeElapsed));
    Serial.println ("REL2_run: " + String(R2_run));
    Serial.println();
    
    STA_timeElapsed = 0; // reset the counter to 0 so the counting starts over...
  }
}
