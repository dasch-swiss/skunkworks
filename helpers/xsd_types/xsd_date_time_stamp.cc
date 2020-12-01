//
// Created by Lukas Rosenthaler on 26.11.20.
//

#include "xsd_date_time_stamp.h"

namespace xsd {

const static std::regex re("^-?([1-9][0-9]{3,}|0[0-9]{3})"
                           "-(0[1-9]|1[0-2])"
                           "-(0[1-9]|[12][0-9]|3[01])"
                           "T(([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9](\\.[0-9]+)?|(24:00:00(\\.0+)?))"
                           "(Z|(\\+|-)((0[0-9]|1[0-3]):[0-5][0-9]|14:00))$");

DateTimeStamp::DateTimeStamp(std::string value) : DateTime(value){
  std::cmatch m;
  if (!std::regex_match(value.c_str(), m, re)) {
    throw Error(__file__, __LINE__, "Invalid xsd:dateTimeStamp string!");
  }
}
//=====================================================================

DateTimeStamp::DateTimeStamp(int year, int month, int day,
                             int hour, int min, float second,
                             int tz_hour, int tz_min) : DateTime(year, month, day,
                                                                 hour, min, second,
                                                                 tz_hour, tz_min) {

}

}