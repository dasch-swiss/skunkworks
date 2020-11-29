//
// Created by Lukas Rosenthaler on 27.11.20.
//
#include <sstream>

#include "gtest/gtest.h"

#include "helpers/xsd_types/date_time.h"

TEST(XsdDateTime, GetGreet) {

EXPECT_NO_THROW(xsd::DateTime t9 = xsd::DateTime());

xsd::DateTime t10 = xsd::DateTime("2001-10-26T19:32:52.3+14:00");
std::ostringstream ss10;
ss10 << t10;
EXPECT_EQ(ss10.str(), "2001-10-26T19:32:52.3+14:00");

xsd::DateTime t11 = xsd::DateTime("2001-10-26T19:32:52.3Z");
std::ostringstream ss11;
ss11 << t11;
EXPECT_EQ(ss11.str(), "2001-10-26T19:32:52.3Z");

xsd::DateTime t12 = xsd::DateTime("2001-10-26T19:32:52.3+11:22");
std::ostringstream ss12;
ss12 << t12;
EXPECT_EQ(ss12.str(), "2001-10-26T19:32:52.3+11:22");

xsd::DateTime t13 = xsd::DateTime("2001-10-26T24:00:00Z");
std::ostringstream ss13;
ss13 << t13;
EXPECT_EQ(ss13.str(), "2001-10-26T00:00:00Z");

xsd::DateTime t14 = xsd::DateTime("2001-10-26T24:00:00.000Z");
std::ostringstream ss14;
ss14 << t14;
EXPECT_EQ(ss14.str(), "2001-10-26T00:00:00Z");

xsd::DateTime t1 = xsd::DateTime("2001-10-26T19:32:52+11:22");
std::ostringstream ss1;
ss1 << t1;
EXPECT_EQ(ss1.str(), "2001-10-26T19:32:52+11:22");

xsd::DateTime t2 = xsd::DateTime("2001-10-26T19:32:52.3456+00:00");
std::ostringstream ss2;
ss2 << t2;
EXPECT_EQ(ss2.str(), "2001-10-26T19:32:52.3456Z");


xsd::DateTime t3 = xsd::DateTime(2000, 2, 10, 12, 30, 33, xsd::TZ_WEST_GMT, 1, 0);
std::ostringstream ss3;
ss3 << t3;
EXPECT_EQ(ss3.str(), "2000-02-10T12:30:33-01:00");

xsd::DateTime t4 = xsd::DateTime(2000, 2, 10, 12, 0, 2.345, xsd::TZ_WEST_GMT, 1, 0);
std::ostringstream ss4;
ss4 << t4;
EXPECT_EQ(ss4.str(), "2000-02-10T12:00:02.345-01:00");

EXPECT_THROW(xsd::DateTime("2001-10-26X19:32:52+00:00"), xsd::Error);

}