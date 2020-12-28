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
  xsd::String gaga;
  EXPECT_NO_THROW(gaga = "That's it...");
  EXPECT_EQ(static_cast<std::string>(gaga), "That's it...");
  xsd::String gugus(std::make_shared<xsd::RestrictionLength>(5));
  try {
    gugus = xsd::String("gaga", std::make_shared<xsd::RestrictionLength>(15));
  } catch (const xsd::Error &err) {
    std::cerr << "***********" << std::endl;
   }
}

TEST(XsdString_Generic_Test, Restrictions) {
  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga",
      std::make_shared<xsd::RestrictionLength>(4))), "gaga");
  EXPECT_THROW(xsd::String("gaga",
      std::make_shared<xsd::RestrictionLength>(5, "This is gaga")), xsd::Error);

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
  xsd::NormalizedString ns;
  EXPECT_NO_THROW(ns = "This\nis\tit");
  EXPECT_EQ(static_cast<std::string>(ns), "This is it");
  std::string gaga;
  EXPECT_NO_THROW(gaga = ns);
  EXPECT_EQ(gaga, "This is it");
}

TEST(XsdToken, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::Token("gaga")), "gaga");
  EXPECT_EQ(static_cast<std::string>(xsd::Token("gaga\tgugus\n newline")), "gaga gugus newline");
  EXPECT_EQ(static_cast<std::string>(xsd::Token("  gaga\tgugus\n newline\r")), "gaga gugus newline");
  xsd::Token ttt;
  EXPECT_NO_THROW(ttt = "  gaga\tgugus\n newline\r");
  std::string stt = ttt;
  EXPECT_EQ(stt, "gaga gugus newline");
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

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org:42/wiki/Wikipedia/γιατι-εμασ/τιμεσ-προσφορεσ/en?gaga=gugu&x=y")),
            "https://zh.wikipedia.org:42/wiki/Wikipedia/γιατι-εμασ/τιμεσ-προσφορεσ/en?gaga=gugu&x=y");

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gaga/gugus")), "/gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gagä/gugus")), "/gagä/gugus");
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

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("mailto:lukas.rosenthaler@unibas.ch")),
            "mailto:lukas.rosenthaler@unibas.ch");

/*
  xsd::AnyUri any_uri;
  EXPECT_NO_THROW(any_uri = "https://zh.wikipedia.org:42/wiki/Wikipedia/مَايِنْتْس");
  std::string tmpstr = any_uri;
  EXPECT_EQ(tmpstr, "https://zh.wikipedia.org:42/wiki/Wikipedia/مَايِنْتْس");
*/
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

  xsd::DateTime test;

  EXPECT_NO_THROW(test = "1888-01-02T19:32:52.3Z");
  EXPECT_EQ(static_cast<std::string>(test), "1888-01-02T19:32:52.3Z");
  std::string gaga = test;
  EXPECT_EQ(gaga, "1888-01-02T19:32:52.3Z");

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

  xsd::Integer ii;
  EXPECT_NO_THROW(ii = 5017);
  EXPECT_EQ(static_cast<std::string>(ii), "5017");
}

TEST(XsdInt, Generic) {
  EXPECT_NO_THROW(xsd::Int(2));
  EXPECT_THROW(xsd::Int("2147483648"), xsd::Error);
  EXPECT_EQ(static_cast<std::string>(xsd::Int(99,
                                                  std::make_shared<xsd::RestrictionMaxInclusive>(100ll))), "99");
  EXPECT_EQ(static_cast<std::string>(xsd::Int(100,
                                                  std::make_shared<xsd::RestrictionMaxInclusive>(100ll))), "100");
  EXPECT_THROW(xsd::Int("101", std::make_shared<xsd::RestrictionMaxInclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Int("100", std::make_shared<xsd::RestrictionMaxExclusive>(100ll)), xsd::Error);
  EXPECT_EQ(static_cast<std::string>(xsd::Int(100,
                                                  std::make_shared<xsd::RestrictionMinInclusive>(100ll))), "100");
  EXPECT_THROW(xsd::Int("99", std::make_shared<xsd::RestrictionMinInclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Int("100", std::make_shared<xsd::RestrictionMinExclusive>(100ll)), xsd::Error);
  EXPECT_THROW(xsd::Int("3.14"), xsd::Error);
  EXPECT_EQ(static_cast<std::string>(xsd::Int(10000)), "10000");

  xsd::Int ii;
  EXPECT_NO_THROW(ii = 512);
  EXPECT_EQ(static_cast<std::string>(ii), "512");
  EXPECT_THROW(ii = "2147483648", xsd::Error);
}

TEST(XsdDecimal, Generic) {
  EXPECT_NO_THROW(xsd::Decimal(3.1415));
  EXPECT_EQ(static_cast<std::string>(xsd::Decimal(3.1415)), "3.1415");
  EXPECT_EQ(static_cast<std::string>(xsd::Decimal(.1415E2)), "14.15");
  EXPECT_EQ(static_cast<std::string>(xsd::Decimal(100.0,
                                              std::make_shared<xsd::RestrictionMinInclusive>(100.0))), "100");
  EXPECT_THROW(xsd::Decimal("99.99", std::make_shared<xsd::RestrictionMinExclusive>(100.0)), xsd::Error);

}

TEST(XsdQName, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::QName("ab:cde")), "ab:cde");
  EXPECT_EQ(static_cast<std::string>(xsd::QName("mySchema9")), "mySchema9");
  EXPECT_THROW(xsd::QName("0ab:gaga"), xsd::Error);
  EXPECT_THROW(xsd::QName("hy:hy:any"), xsd::Error);
}

TEST(XsdLanguage, Generic) {
  EXPECT_NO_THROW(xsd::Language language("en"));
  EXPECT_THROW(xsd::Language("xx"), xsd::Error);
}

TEST(XsdLangString, Generic) {
  EXPECT_NO_THROW(xsd::LangString gaga("en", xsd::String("This is a test")));
  xsd::LangString lang_string;
  lang_string["en"] = xsd::String("What is this");
  lang_string["de"] = xsd::String("Was ist das");
  xsd::String res = lang_string["de"];
  EXPECT_EQ(static_cast<std::string>(res), "Was ist das");
  xsd::String res2 = lang_string["xx"];
  EXPECT_EQ(static_cast<std::string>(res2), "");

}
