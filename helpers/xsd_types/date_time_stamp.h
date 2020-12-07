//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_DATE_TIME_STAMP_H
#define SKUNKWORKS_DATE_TIME_STAMP_H

#include "date_time.h"

namespace xsd {

class DateTimeStamp : DateTime {
 public:
  // inline DateTimeStamp() : DateIme() {}

  DateTimeStamp(std::string value);

  DateTimeStamp(int year, int month, int day,
                int hour, int min, float second,
                int tz_hour, int tz_min);

};

}

#endif //SKUNKWORKS_DATE_TIME_STAMP_H
