//
// Created by Lukas Rosenthaler on 26.11.20.
//

#include <ctime>
#include <cmath>
#include <locale>

#include "xsd_date_time.h"

static const char file_[] = __FILE__;

namespace xsd {

// m[0] : total match
// m[1] : year
// m[2] : month
// m[3] : day
// m[4] : total time
// m[5] : hour
// m[6] : min
// m[7] : second with decimal
// m[8] : decimal only of seconds
// m[9] : 24:00:00 if present
// m[10] : fragments of seconds of 24:00:00.000000
// m[11] : timezone-offset or "Z"
// m[12] : sign of timezone or empty
// m[13] : if set, "14:00" without signed
// m[14] : hours of timezone-offset
// m[15] : minutes of timezone offset

const static std::regex re("^-?([1-9][0-9]{3,}|0[0-9]{3})"
                           "-(0[1-9]|1[0-2])"
                           "-(0[1-9]|[12][0-9]|3[01])"
                           "T(([01][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9](\\.[0-9]+)?)|(24:00:00(\\.0+)?))"
                           "(Z|(\\+|-)((0[0-9]|1[0-3]):([0-5][0-9])|14:00))?$");

//---------------------------------------------------------------------
void DateTime::parse(const std::string &str) {
  //...................................................................
  std::cmatch m;
  if (std::regex_match(str.c_str(), m, re)) {
    //
    // first processing the date part
    //
    year_ = std::stoi(m[1]);
    month_ = std::stoi(m[2]);
    day_ = std::stoi(m[3]);
    //
    // now processing the time part
    //
    if (m[9].matched) { // we have 24:00:00, is same as 00:00:00
      hour_ = 0;
      min_ = 0;
      second_ = 0;
    } else {
      hour_ = std::stoi(m[5]);
      min_ = std::stoi(m[6]);
      second_ = std::stof(m[7]);
    }

    //
    // processing timezone
    //
    tz_sign_ = TZ_EAST_GMT;
    if (m[12].matched && m[12] == '-') {
      tz_sign_ = TZ_WEST_GMT;
    }
    if (m[11].matched && m[11] == 'Z') {
      tz_hour_ = 0;
      tz_min_ = 0;
    } else {
      if (m[13].matched && m[13] == "14:00") {
        tz_hour_ = 14;
        tz_min_ = 0;
      } else {
        if (m[14].matched && m[15].matched) {
          tz_hour_ = std::stoi(m[14]);
          tz_min_ = std::stoi(m[15]);
        }
      }
    }
  } else {
    throw Error(file_, __LINE__, "Invalid xsd:dateTime string!");
  }
  std::cerr << "#" << __LINE__ << std::endl;

}
//=====================================================================

//---------------------------------------------------------------------
void DateTime::validate() const {
  //...................................................................
  if (tz_sign_ != TZ_WEST_GMT && tz_sign_ != TZ_EAST_GMT) {
    throw Error(file_, __LINE__, "Invalid xsd:dateTime");
  }
  if (((month_ < 1) || (month_ > 12))
      || ((day_ < 1) || (day_ > 31))
      || ((hour_ < 0) || (hour_ > 23))
      || ((min_ < 0) || (min_ > 59))
      || ((tz_hour_ < -14) || (tz_hour_ > 14))
      || ((tz_min_ < 0) || (tz_min_ > 60))) {
    throw Error(file_, __LINE__, "Invalid xsd:dateTime");
  }

  if ((month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) && (day_ > 30)) {
    throw Error(file_, __LINE__, "Invalid xsd:dateTime");
  }
  if (month_ == 2) {
    bool leap_year = ((year_ % 4) == 0);
    if (leap_year) {
      leap_year = ((year_ % 100) != 0);
      if (!leap_year) {
        leap_year = ((year_ % 400) == 0);
      }
    }
    if (leap_year && (day_ > 29)) {
      std::cerr << __LINE__ << "! year=" << year_ << " day=" << day_ << std::endl;
      throw Error(file_, __LINE__, "Invalid xsd:dateTime");
    } else if (!leap_year && (day_ > 28)) {
      std::cerr << __LINE__ << "! year=" << year_ << " day=" << day_ << std::endl;
      throw Error(file_, __LINE__, "Invalid xsd:dateTime");
    }
  }
}
//=====================================================================

//---------------------------------------------------------------------
std::ostream &DateTime::print_to_stream(std::ostream &out_stream) const {
  //...................................................................
  out_stream << year_ << "-"
  << std::setfill('0') << std::setw(2) << month_ << "-"
  << std::setw(2) << day_
  << "T" << std::setw(2) << hour_ << ":"
  << std::setw(2) << min_ << ":";

  int width = 2;
  int precision = 0;
  float seconds = second_;
  for (int i = 0; i < 7; ++i) {
    float intpart, fracpart = modf(seconds, &intpart);
    if (fracpart == 0.0f) break;
    if (i == 0) ++width; // decimal point
      ++width;
      ++precision;
      seconds *= 10.0f;
  }
  out_stream << std::fixed << std::setw(width) << std::setprecision(precision) << second_;

  if (tz_hour_ == 0 && tz_min_ == 0) {
    out_stream << "Z";
  } else {
    out_stream << ((tz_sign_ == TZ_WEST_GMT) ? "-" : "+") << std::setw(2)
    << ((tz_hour_ < 0) ? -tz_hour_ : tz_hour_) << ":"
    << std::setw(2) << tz_min_;
  }
  return out_stream;
}
//=====================================================================

DateTime::DateTime() {
  year_ = 0;
  month_ = 0;
  day_ = 0;
  hour_ = 0;
  min_ = 0;
  second_ = 0.0f;
  tz_sign_ = TZ_WEST_GMT;
  tz_hour_ = 0;
  tz_min_ = 0;
  xsd_type_ = "dateTime";
  char time_buf[21];
  time_t now;
  time(&now);
  strftime(time_buf, 21, "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
  parse(time_buf);
}
//=====================================================================

DateTime::DateTime(const std::string &value) {
  xsd_type_ = "dateTime";
  year_ = 0;
  month_ = 0;
  day_ = 0;
  hour_ = 0;
  min_ = 0;
  second_ = 0.0f;
  tz_sign_ = TZ_WEST_GMT;
  tz_hour_ = 0;
  tz_min_ = 0;
  parse(value);
  validate();
}
//=====================================================================

DateTime::DateTime(int year, int month, int day,
                   int hour, int min, float second,
                   int tz_sign, int tz_hour, int tz_min) :
                   year_(year), month_(month), day_(day),
                   hour_(hour), min_(min), second_(second),
                   tz_sign_(tz_sign), tz_hour_(tz_hour), tz_min_(tz_min) {
  xsd_type_ = "dateTime";
  validate();
}
//=====================================================================

DateTime::operator std::string() const {
  std::stringstream ss;
  ss.imbue(std::locale::classic());
  ss << *this;
  return ss.str();
}
//=====================================================================

void DateTime::set(const std::string &strval) {
  parse(strval);
  validate();
}
//=====================================================================


}
