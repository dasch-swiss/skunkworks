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
}

TEST(XsdString_Generic_Test, Restrictions) {
  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga", xsd::StringRestrictionLength(4))), "gaga");
  EXPECT_THROW(xsd::String("gaga", xsd::StringRestrictionLength(5)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga", xsd::StringRestrictionMinLength(4))), "gaga");
  EXPECT_THROW(xsd::String("gaga", xsd::StringRestrictionMinLength(5)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga", xsd::StringRestrictionMaxLength(4))), "gaga");
  EXPECT_THROW(xsd::String("gaga", xsd::StringRestrictionMaxLength(3)), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("gaga@1234", xsd::StringRestrictionPattern("\\w*@[0-9]*"))), "gaga@1234");
  EXPECT_THROW(xsd::String("gaga@1234X", xsd::StringRestrictionPattern("\\w*@[0-9]*")), xsd::Error);

  EXPECT_EQ(static_cast<std::string>(xsd::String("yes", xsd::StringRestrictionEnumeration({"yes", "no", "maybe"}))),
            "yes");
  EXPECT_EQ(static_cast<std::string>(xsd::String("no", xsd::StringRestrictionEnumeration({"yes", "no", "maybe"}))),
            "no");
  EXPECT_EQ(static_cast<std::string>(xsd::String("maybe", xsd::StringRestrictionEnumeration({"yes", "no", "maybe"}))),
            "maybe");
  EXPECT_THROW(xsd::String("omg", xsd::StringRestrictionEnumeration({"yes", "no", "maybe"})), xsd::Error);

}

TEST(XsdAnyUri, Generic) {
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org")), "http://example.org");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#")), "http://example.org#");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#frag")), "http://example.org#frag");

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org/a/b#id")), "http://example.org/a/b#id");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org#frag?a=b")), "http://example.org#frag?a=b");

  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("http://example.org:25/gaga/test")),
            "http://example.org:25/gaga/test");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri(u8"http://aé.org")), u8"http://aé.org");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org/wiki/Wikipedia/en")),
            "https://zh.wikipedia.org/wiki/Wikipedia/en");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("https://zh.wikipedia.org:42/wiki/Wikipedia关于中文维基百科/en?gaga=gugu&x=y")),
      "https://zh.wikipedia.org:42/wiki/Wikipedia关于中文维基百科/en?gaga=gugu&x=y");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gaga/gugus")), "/gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("//gaga/gugus")), "//gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("/gaga/gugus#frag")), "/gaga/gugus#frag");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga/gugus")), "gaga/gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga//gugus")), "gaga//gugus");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("gaga.xml")), "gaga.xml");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("doi:10.1000/182")), "doi:10.1000/182");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("git://github.com/user/project-name.git")), "git://github.com/user/project-name.git");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("ark:/12025/654xz321/s3/f8.05v.tiff")), "ark:/12025/654xz321/s3/f8.05v.tiff");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("s3://mybucket/puppy.jpg")), "s3://mybucket/puppy.jpg");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("svn+ssh://svn.example.org/gaga")), "svn+ssh://svn.example.org/gaga");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("urn:oasis:names:specification:docbook:dtd:xml:4.1.2")), "urn:oasis:names:specification:docbook:dtd:xml:4.1.2");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("ws://localhost:9998/echo")), "ws://localhost:9998/echo");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("wss://localhost:9998/echo")), "wss://localhost:9998/echo");
  EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("xri://broadview.library.example.com/(urn:isbn:0-395-36341-1)/(+hardcover)")), "xri://broadview.library.example.com/(urn:isbn:0-395-36341-1)/(+hardcover)");
  //EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("xri://@cordance*(urn:isbn:0-395-36341-1)/book-description.html")), "xri://@cordance*(urn:isbn:0-395-36341-1)/book-description.html");

  try {
    EXPECT_EQ(static_cast<std::string>(xsd::AnyUri("file://gugus/gaga.xml")), "file://gugus/gaga.xml");
  } catch (const xsd::Error &err) {
    std::cerr << err;
    throw 1;
  }
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