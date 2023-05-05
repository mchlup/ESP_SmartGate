/*
 * Function[0] = Periodicke spinani
 * Function[1] = Svatky
 * Function[2] = vyjimky
 * Function[2] = Vlastni datumy
 */
byte isPeriod = 0 ;
byte isHoliday = 0 ;
byte isException = 0 ;
byte isMyDate = 0 ;
//byte isControlRelay = 0 ;

void handleDateTimeIO() {
    if ( Function[0] == "1" ) {
      if ( ActualTimeInt >= StartTime[5] and ActualTimeInt < StopTime[5] and isHoliday == 0 and isException == 0 and isMyDate == 0 ) {
        for (int Periodicals = 0; Periodicals < 7; Periodicals++) {
          if ( currentWeekDay == weekDays[Periodicals] and myWeekday[Periodicals] == "1" ) {
            isPeriod = 1 ;
          } else if ( currentWeekDay == weekDays[Periodicals] and myWeekday[Periodicals] == "0" ) {
            isPeriod = 0 ;
          }
        }
      } else {
        isPeriod = 0 ;
      }
    } else {
      isPeriod = 0 ;
    }
    // --------------------------------
    if ( Function[1] == "1" ) {
      for (int HoliDay = 0; HoliDay < 12; HoliDay++) {
        if ( ActualDate == Holiday[HoliDay] ) {
          isHoliday = 1 ;
        } else {
          isHoliday = 0 ;
        }
      }
     } else {
       isHoliday = 0 ;
    }
    // -------------------------------
    for (int Exception = 10; Exception < 15; Exception++) {
    if ( ActualDate == myDate[Exception] ) {
      if ( Function[2] == "1" ) {  
        currentWeekDay = "VYJIMKA" ;
        isException = 1 ;
      } else if (currentWeekDay != "VYJIMKA" ) {
        isException = 0 ;
      }
    } if (currentWeekDay != "VYJIMKA" ) {
        isException = 0 ;
    }
    }

    // ------------------------------

    if ( Function[3] == "1" ) {      
      if ( ActualDateInt >= myDateInt[0] and ActualTimeInt >= StartTime[0] and isMyDate == 0 ) {
        isMyDate = 1 ;
      }
      if ( ActualDateInt >= myDateInt[1] and ActualTimeInt >= StopTime[0] and isMyDate == 1 ) {
        isMyDate = 0 ;
      }
      //------------------------------
      if ( ActualDateInt >= myDateInt[2] and ActualTimeInt >= StartTime[1] and isMyDate == 0  ) {
        isMyDate = 2 ;
      }
      if ( ActualDateInt >= myDateInt[3] and ActualTimeInt >= StopTime[1] and isMyDate == 2 ) {
        isMyDate = 0 ;
      }
      //------------------------------
      if ( ActualDateInt >= myDateInt[4] and ActualTimeInt >= StartTime[2] and isMyDate == 0  ) {
        isMyDate = 3 ;
      }
      if ( ActualDateInt >= myDateInt[5] and ActualTimeInt >= StopTime[2] and isMyDate == 3 ) {
        isMyDate = 0 ;
      }

      if ( ActualDateInt >= myDateInt[6] and ActualTimeInt >= StartTime[3] and isMyDate == 0  ) {
        isMyDate = 4 ;
      }
      if ( ActualDateInt >= myDateInt[7] and ActualTimeInt >= StopTime[3] and isMyDate == 4 ) {
        isMyDate = 0 ;
      }

      if ( ActualDateInt >= myDateInt[8] and ActualTimeInt >= StartTime[4] and isMyDate == 0  ) {
        isMyDate = 5 ;
      }
      if ( ActualDateInt >= myDateInt[9] and ActualTimeInt >= StopTime[4] and isMyDate == 5 ) {
        isMyDate = 0 ;
      }
    } else {
      isMyDate = 0 ;
    }
    //--------------------------------------
    if ( Function[4] == "1" ) {
      //if ( ActualTimeInt >= StartTime[6] and ActualTimeInt < StopTime[6] and isHoliday == 0 and isException == 0 and isMyDate == 0 ) {
      if ( ActualTimeInt == StartTime[6] and currentSecond <= 1 and isHoliday == 0 and isException == 0 and isMyDate == 0 ) {
        for (int PeriodicalCtrl = 0; PeriodicalCtrl < 7; PeriodicalCtrl++) {
          if ( currentWeekDay == weekDays[PeriodicalCtrl] and myWeekdayCtrl[PeriodicalCtrl] == "1" ) {
            isControlRelay = 1 ;
            
          } else if ( currentWeekDay == weekDays[PeriodicalCtrl] and myWeekdayCtrl[PeriodicalCtrl] == "0" ) {
            isControlRelay = 0 ;
          }
        }
      } else {
        isControlRelay = 0 ;
      }
    } else {
      isControlRelay = 0 ;
    }
    //--------------------------------------
    if ( Function[5] == "1" ) {
      if ( isMyDate != 0 and ActualTimeInt == StartTime[0] and currentSecond <= 1 or StartTime[1] or StartTime[2] or StartTime[3] or StartTime[4]) {
        Relay2on();
      }
    }
}

void handleRelayFunctions() {
  if ( isPeriod == 1 or isMyDate != 0 ) {
    Relay1(1);
  } else {
    Relay1(0);
  }
  //---------------
  
  //---------------
  if ( isControlRelay == 1 or relay2State == 1 ) {
    Relay2on() ;
  } else {
    Relay2off();
  }
}
