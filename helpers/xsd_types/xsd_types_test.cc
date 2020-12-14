//
// Created by Lukas Rosenthaler on 27.11.20.
//

#include <sstream>
#include "gtest/gtest.h"

//#include "helpers/xsd_types/date_time.h"
#include "helpers/xsd_types/xsd.h"

TEST(XsdString, Generic) {

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga")), "gaga");

  xsd::String teststr("Waseliwas");
  std::ostringstream ss;
  ss << teststr;
  EXPECT_EQ(ss.str(), "Waseliwas");
  teststr.set("So is das");
  EXPECT_EQ(teststr.get(), "So is das");
}

TEST(XsdString_Generic_Test, Restrictions) {
  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga",
      std::make_shared<xsd::RestrictionLength>(4))), "gaga");
  EXPECT_THROW(xsd::String("gaga",
      std::make_shared<xsd::RestrictionLength>(5)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga",
      std::make_shared<xsd::RestrictionMinLength>(4))), "gaga");

  EXPECT_THROW(xsd::String("gaga",
      std::make_shared<xsd::RestrictionMinLength>(5)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga",
      std::make_shared<xsd::RestrictionMaxLength>(4))), "gaga");

  EXPECT_THROW(xsd::String("gaga",
      std::make_shared<xsd::RestrictionMaxLength>(3)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga@1234",
      std::make_shared<xsd::RestrictionPattern>("\\w*@[0-9]*"))), "gaga@1234");

  EXPECT_THROW(xsd::String("gaga@1234X",
      std::make_shared<xsd::RestrictionPattern>("\\w*@[0-9]*")), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("yes",
      std::make_shared<xsd::RestrictionEnumeration>(std::set<std::string>({"yes", "no", "maybe"})))), "yes");

  EXPECT_EQ(static_cast<std::string>(xsd::String("no",
      std::make_shared<xsd::RestrictionEnumeration>(std::set<std::string>({"yes", "no", "maybe"})))), "no");

  EXPECT_EQ(static_cast<std::string>(xsd::String("maybe",
      std::make_shared<xsd::RestrictionEnumeration>(std::set<std::string>({"yes", "no", "maybe"})))), "maybe");

  EXPECT_THROW(xsd::String("omg",
      std::make_shared<xsd::RestrictionEnumeration>(std::set<std::string>({"yes", "no", "maybe"}))), xsd::Error);

  xsd::String tt("gaga@1234", std::make_shared<xsd::RestrictionPattern>("\\w*@[0-9]*"));
  tt.set("gugus@4123");
  EXPECT_EQ(tt.get(), "gugus@4123");
  EXPECT_THROW(tt.set("gaga@gugu"), xsd::Error);

  std::vector<std::shared_ptr<xsd::Restriction>> restrictions = {
      std::make_shared<xsd::RestrictionMinLength>(5),
      std::make_shared<xsd::RestrictionMaxLength>(10)
  };
  EXPECT_NO_THROW(xsd::String tmp("abcdefg", restrictions));
  EXPECT_THROW(xsd::String tmp("abcd", restrictions), xsd::Error);
  EXPECT_THROW(xsd::String tmp("abcdefghijk", restrictions), xsd::Error);

}

TEST(XsdNormalizedString, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::NormalizedString("gaga")), "gaga");
  EXPECT_EQ(static_cast<std::string>(xsd::NormalizedString("gaga\tgugus\n newline")), "gaga gugus  newline");
  EXPECT_EQ(static_cast<std::string>(xsd::NormalizedString("gaga\tgugus\n newline\r")), "gaga gugus  newline ");
  EXPECT_EQ(static_cast<std::string>(xsd::NormalizedString("gaga\tgugus\n newline\r",
      std::make_shared<xsd::RestrictionMinLength>(5))), "gaga gugus  newline ");
  EXPECT_THROW(xsd::NormalizedString("gaga\tgugus\n newline\r",
                                     std::make_shared<xsd::RestrictionMaxLength>(5)), xsd::Error);

  xsd::NormalizedString tt("X");
  tt.set("aa\tbb");
  EXPECT_EQ(tt.get(), "aa bb");
}

TEST(XsdToken, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::Token("gaga")), "gaga");
  EXPECT_EQ(static_cast<std::string>(xsd::Token("gaga\tgugus\n newline")), "gaga gugus newline");
  EXPECT_EQ(static_cast<std::string>(xsd::Token("  gaga\tgugus\n newline\r")), "gaga gugus newline");
}


TEST(XsdAnyUri, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org")),
      "http://example.org");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#")),
      "http://example.org#");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#frag")),
      "http://example.org#frag");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org/a/b#id")),
      "http://example.org/a/b#id");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#frag?a=b")),
      "http://example.org#frag?a=b");

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org:25000/gaga/test")),
            "http://example.org:25000/gaga/test");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri(u8"http://aé.org/цудовнымъ")),
      u8"http://aé.org/цудовнымъ");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org/wiki/Wikipedia/en")),
            "https://zh.wikipedia.org/wiki/Wikipedia/en");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org:42/wiki/WikipediaПóйдзьце/en?gaga=gugu&x=y")),
      "https://zh.wikipedia.org:42/wiki/WikipediaПóйдзьце/en?gaga=gugu&x=y");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org:42/wiki/Wikipedia/مَايِنْتْس،/en?gaga=gugu&x=y")),
            "https://zh.wikipedia.org:42/wiki/Wikipedia/مَايِنْتْس،/en?gaga=gugu&x=y");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gaga/gugus")), "/gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("//gaga/gugus")), "//gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gaga/gugus#frag")), "/gaga/gugus#frag");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga/gugus")), "gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga//gugus")), "gaga//gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga.xml")), "gaga.xml");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("doi:10.1000/182")), "doi:10.1000/182");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("git://github.com/user/project-name.git")),
      "git://github.com/user/project-name.git");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("ark:/12025/654xz321/s3/f8.05v.tiff")),
      "ark:/12025/654xz321/s3/f8.05v.tiff");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("s3://mybucket/!puppy(15)*'A'.jpg")),
      "s3://mybucket/!puppy(15)*'A'.jpg");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("urn:oasis:names:specification:docbook:dtd:xml:4.1.2")),
      "urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("ws://localhost:9998/echo/gaga?a=b")),
      "ws://localhost:9998/echo/gaga?a=b");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("wss://localhost/echo")),
      "wss://localhost/echo");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("file://gugus/gaga.xml")),
      "file://gugus/gaga.xml");
  EXPECT_THROW(xsd::AnyUri("://gaga/gugus"), xsd::Error);
}

TEST(XsdDateTime, Parsing) {

  EXPECT_NO_THROW(xsd::DateTime());

  EXPECT_EQ(xsd::DateTime().xsd_type(), "dateTime");

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime("2001-10-26T19:32:52.3+14:00")), "2001-10-26T19:32:52.3+14:00");

  EXPECT_EQ(xsd::DateTime("2001-10-26T19:32:52.3+14:00").xsd_type(), "dateTime");

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime("2001-10-26T19:32:52.3Z")), "2001-10-26T19:32:52.3Z");

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

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime(2000, 2, 10, 12, 30, 33, xsd::TZ_WEST_GMT, 1, 0)),
            "2000-02-10T12:30:33-01:00");
  EXPECT_EQ(xsd::DateTime(2000, 2, 10, 12, 30, 33, xsd::TZ_WEST_GMT, 1, 0).xsd_type(), "dateTime");

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime(2000, 2, 29, 12, 0, 2.345, xsd::TZ_WEST_GMT, 1, 0)),
            "2000-02-29T12:00:02.345-01:00");
  EXPECT_THROW(xsd::DateTime(2000, 2, 30, 12, 0, 2.345, xsd::TZ_WEST_GMT, 1, 0), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime(1884, 2, 29, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0)),
            "1884-02-29T12:00:00Z");

  EXPECT_EQ(static_cast<std::string>(xsd::DateTime(1884, 2, 29, 12, 0, 0, xsd::TZ_WEST_GMT, 0, 0)),
            "1884-02-29T12:00:00Z");

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

TEST(XsdDateTimeStamp, Instantiation) {
  EXPECT_NO_THROW(xsd::DateTimeStamp("2001-10-26T24:00:00Z"));
  EXPECT_NO_THROW(xsd::DateTimeStamp("2001-10-26T19:32:52.3456+00:00"));
  EXPECT_THROW(xsd::DateTimeStamp("2001-10-26T24:00:00"), xsd::Error);
}

TEST(XsdInteger, Generic) {
  EXPECT_NO_THROW(xsd::Integer(2));
  EXPECT_EQ(static_cast<std::string>(xsd::Integer(99,
      std::make_shared<xsd::RestrictionMaxInclusive>(100ll))), "99");
  EXPECT_EQ(static_cast<std::string>(xsd::Integer(100,
                                                  std::make_shared<xsd::RestrictionMaxInclusive>(100ll))), "100");
  EXPECT_THROW(xsd::Integer("101", std::make_shared<xsd::RestrictionMaxInclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Integer("100", std::make_shared<xsd::RestrictionMaxExclusive>(100ll)), xsd::Error);
  EXPECT_EQ(static_cast<std::string>(xsd::Integer(100,
                                                  std::make_shared<xsd::RestrictionMinInclusive>(100ll))), "100");
  EXPECT_THROW(xsd::Integer("99", std::make_shared<xsd::RestrictionMinInclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Integer("100", std::make_shared<xsd::RestrictionMinExclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Integer("3.14"), xsd::Error);
  EXPECT_EQ(static_cast<std::string>(xsd::Integer(10000)), "10000");
}