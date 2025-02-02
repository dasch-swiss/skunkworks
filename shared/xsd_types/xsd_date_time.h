//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_DATE_TIME_H
#define SKUNKWORKS_DATE_TIME_H

#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <tuple>

#include "xsd_error.h"
#include "xsd_data_type.h"

namespace xsd {

const int TZ_WEST_GMT = -1;
const int TZ_EAST_GMT = 1;

class DateTime : public DataType {
  /*!
   * This class implements the xsd:dateTime datatype (see https://www.w3.org/TR/xmlschema11-2/#dateTime)
   */
 public:
  /*!
   * Default constructor. Uses the current system time to fill in the value
   */
  DateTime();

  /**
   * Constructor with correctly formatted xsd:dateTime string. Format is being validated
   * using th official W3C regexp.
   *
   * @param value String with correctly formated dateTime
   */
  explicit DateTime(const std::string &value);

  /**
   *
   * @param year
   * @param month
   * @param day
   * @param hour
   * @param min
   * @param second
   * @param tz_hour [optional, default=00]
   * @param tz_min  [optional, default=00]
   */
  DateTime(int year, int month, int day,
           int hour, int min, float second,
           int tz_sign = TZ_EAST_GMT, int tz_hour = 0, int tz_min = 0);

  /*!
   * Set a new value as std::string
   * @param strval
   */
  void set(const std::string &strval) override ;

  DateTime &operator=(const std::string &strval) override;

  bool operator==(const DateTime &other) const ;

  bool operator!=(const DateTime &other) const ;

  bool operator>(const DateTime &other) const;

  bool operator>=(const DateTime &other) const;

  bool operator<(const DateTime &other) const;

  bool operator<=(const DateTime &other) const;

 private:
  int year_;
  int month_;
  int day_;
  int hour_;
  int min_;
  float second_;
  int tz_sign_;
  int tz_hour_;
  int tz_min_;

  void parse(const std::string &str);
  std::ostream &print_to_stream(std::ostream &out_stream) const override;
  void validate() const;

  std::tuple<int, int>rectify_time_zone(void) const ;
};

}

namespace std {

template<> struct hash<xsd::DateTime> {
  std::size_t  operator()(xsd::DateTime const &date_time) const noexcept {
    std::string strval = static_cast<std::string>(date_time);
    return std::hash<std::string>{}(strval);
  }
};

}


#endif //SKUNKWORKS_DATE_TIME_H
