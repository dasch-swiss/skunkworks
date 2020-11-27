//
// Created by Lukas Rosenthaler on 26.11.20.
//

#include <time.h>

#include "date_time.h"

namespace xsd {

    const static std::regex re("^-?([1-9][0-9]{3,}|0[0-9]{3})"
                               "-(0[1-9]|1[0-2])"
                               "-(0[1-9]|[12][0-9]|3[01])"
                               "T(([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9](\\.[0-9]+)?|(24:00:00(\\.0+)?))"
                               "(Z|(\\+|-)((0[0-9]|1[0-3]):[0-5][0-9]|14:00))?$");

    DateTime::DateTime() {
        char time_buf[27];
        time_t now;
        time(&now);
        strftime(time_buf, 27, "%Y-%m-%dT%H:%M:%SZ+00:00", gmtime(&now));
        value_ = time_buf;
    }

    DateTime::DateTime(std::string value) {
        std::cmatch m;
        if (std::regex_match(value.c_str(), m, re)) {
            value_ = value;
        } else {
            throw Error(__file__, __LINE__, "Invalid xsd:dateTime string!");
        }
    }
    //=====================================================================

    DateTime::DateTime(int year, int month, int day,
                       int hour, int min, float second,
                       int tz_hour, int tz_min) {
        if (((month < 1) || (month > 12)) || ((day < 1) || (day > 31))
        || ((hour < 0) || (hour > 16)) || ((min < 0) || (min > 60))
        || ((tz_hour < -12) || (tz_hour > 12)) || ((tz_min < 0) || (tz_min > 60))) {
            throw Error(__file__, __LINE__, "Invalid xsd:dateTime");
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) {
            throw Error(__file__, __LINE__, "Invalid xsd:dateTime");
        }
        if (month == 2) {
            if ((((year % 400) == 0 || (year % 4) == 0) && (year % 100) != 0) && (day > 29)) {
                throw Error(__file__, __LINE__, "Invalid xsd:dateTime");
            } else if (day > 28) {
                throw Error(__file__, __LINE__, "Invalid xsd:dateTime");
            }
        }
        std::stringstream ss;
        ss << year << "-" << std::setfill('0') << std::setw(2) << month << "-" << std::setw(2) << day
        << "T" << std::setw(2) << hour << ":" << std::setw(2) << min << ":"
        << std::fixed << std::setw(6) << std::setprecision(3) << second
        << "Z" << ((tz_hour < 0) ? "-" : "+") << std::setw(2) << ((tz_hour < 0) ? -tz_hour : tz_hour) << ":" << std::setw(2) << tz_min;
        value_ = ss.str();
    }
    //=====================================================================

    std::ostream &operator<<(std::ostream &out_stream, const DateTime &rhs) {
        out_stream << rhs.value_;
        return out_stream;
    }
    //=====================================================================
}
