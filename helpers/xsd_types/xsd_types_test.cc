//
// Created by Lukas Rosenthaler on 27.11.20.
//

#include "gtest/gtest.h"

#include "helpers/xsd_types/date_time.h"

TEST(XsdDateTime, Parsing) {

EXPECT_NO_THROW(xsd::DateTime
t9 = xsd::DateTime()
);

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T19:32:52.3+14:00")
), "2001-10-26T19:32:52.3+14:00");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T19:32:52.3Z")
), "2001-10-26T19:32:52.3Z");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T19:32:52.3+11:22")
), "2001-10-26T19:32:52.3+11:22");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T24:00:00Z")
), "2001-10-26T00:00:00Z");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T24:00:00.000Z")
), "2001-10-26T00:00:00Z");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T19:32:52+11:22")
), "2001-10-26T19:32:52+11:22");

EXPECT_EQ(static_cast
<std::string>(xsd::DateTime("2001-10-26T19:32:52.3456+00:00")
), "2001-10-26T19:32:52.3456Z");

EXPECT_THROW(xsd::DateTime("2001-10-26X19:32:52+00:00"), xsd::Error);

}

TEST(XsdDateTime, ByValueConstructor) {

EXPECT_EQ(static_cast<std::string>(xsd::DateTime(2000, 2, 10, 12, 30, 33, xsd::TZ_WEST_GMT, 1, 0)), "2000-02-10T12:30:33-01:00");

EXPECT_EQ(static_cast<std::string>(xsd::DateTime(2000, 2, 29, 12, 0, 2.345, xsd::TZ_WEST_GMT, 1, 0)), "2000-02-29T12:00:02.345-01:00");
EXPECT_THROW(xsd::DateTime(2000, 2, 30, 12, 0, 2.345, xsd::TZ_WEST_GMT, 1, 0), xsd::Error);

EXPECT_EQ(static_cast<std::string>(xsd::DateTime(1884, 2, 29, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0)), "1884-02-29T12:00:00Z");

EXPECT_EQ(static_cast<std::string>(xsd::DateTime(1884, 2, 29, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0)), "1884-02-29T12:00:00Z");

}

TEST(XsdDateTime, ValueValidation) {

EXPECT_THROW(xsd::DateTime(2021, 1, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 1, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 2, 29, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 2, 28, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 3, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 3, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 4, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 4, 30, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 5, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 5, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 6, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 6, 30, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 7, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 7, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 8, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 8, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 9, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 9, 30, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 10, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 10, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 11, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 11, 30, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 12, 32, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 12, 31, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));

EXPECT_THROW(xsd::DateTime(2021, 0, 15, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 1, 15, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));
EXPECT_THROW(xsd::DateTime(2021, 13, 15, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0), xsd::Error);
EXPECT_NO_THROW(xsd::DateTime(2021, 12, 15, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0));

}