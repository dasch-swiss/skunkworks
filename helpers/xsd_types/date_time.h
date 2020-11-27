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

#include "error.h"

static const char __file__[] = __FILE__;

namespace xsd {

    class DateTime {
    private:
        std::string value_;
    public:
        DateTime();

        /**
         * Constructor with correctly formatted xsd:dateTime string. Format is being validated
         * using th official W3C regexp.
         *
         * @param value String with correctly formated dateTime
         */
        DateTime(std::string value);

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
                    int tz_hour = 0, int tz_min = 0);

        /**
         * Output to stream
         *
         * @param out_stream
         * @param rhs
         * @return out_stream
         */
        friend std::ostream &operator<<(std::ostream &out_stream, const DateTime &rhs);
    };

}

#endif //SKUNKWORKS_DATE_TIME_H
