//
// Created by Lukas Rosenthaler on 05.01.21.
//
#include <memory>

#include "catch2/catch.hpp"

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"
#include "generic_object_description.h"

TEST_CASE("Unit tests for dsp::GenericObjectDescription", "[catch2]") {
  INFO("Testing all xsd data types...");
  CHECK_NOTHROW(dsp::GenericObjectDescription(1, "GAGA"));
  dsp::GenericObjectDescription gaga(1, "GAGA");
  gaga.member<xsd::String>("test-string", xsd::String("a test"));
  gaga.member<xsd::Decimal>("test-decimal", xsd::Decimal(3.1415));
  gaga.member<xsd::NormalizedString>("test-normalized", xsd::NormalizedString("gaga\tgugus\n newline"));
  gaga.member<xsd::Boolean>("test-boolean", xsd::Boolean(true));
  gaga.member<xsd::AnyUri>("test-anyuri", xsd::AnyUri("https://zh.wikipedia.org:42/wiki/Wikipedia/γιατι-εμασ/τιμεσ-προσφορεσ/en?gaga=gugu&x=y"));
  gaga.member<xsd::DateTime>("test-datetime", xsd::DateTime("2001-10-26T19:32:52.3+14:00"));
  gaga.member<xsd::DateTimeStamp>("test-datetimestamp", xsd::DateTimeStamp("2001-10-26T19:32:52.3456+00:00"));
  gaga.member<xsd::Int>("test-int", xsd::Int(33));
  gaga.member<xsd::Integer>("test-integer", xsd::Integer(42));
  gaga.member<xsd::Language>("test-language", xsd::Language("en"));
  gaga.member<xsd::NormalizedString>("test-normalizedstring", xsd::NormalizedString("gaga\tgugus\n newline"));
  gaga.member<xsd::QName>("test-qname", xsd::QName("ab:cde"));
  gaga.member<xsd::Token>("test-token", xsd::Token("  gaga\tgugus\n newline\r"));

  CHECK(gaga.version() == 1);
  CHECK(gaga.object_type() == "GAGA");
  CHECK(gaga.member<xsd::String>("test-string") == xsd::String("a test"));
  CHECK(gaga.member<xsd::Decimal>("test-decimal") == xsd::Decimal(3.1415));
  CHECK(gaga.member<xsd::NormalizedString>("test-normalized") == xsd::NormalizedString("gaga gugus  newline"));
  CHECK(gaga.member<xsd::Boolean>("test-boolean") == xsd::Boolean(true));
  CHECK(gaga.member<xsd::AnyUri>("test-anyuri") == xsd::AnyUri("https://zh.wikipedia.org:42/wiki/Wikipedia/γιατι-εμασ/τιμεσ-προσφορεσ/en?gaga=gugu&x=y"));
  CHECK(gaga.member<xsd::DateTime>("test-datetime") == xsd::DateTime("2001-10-26T19:32:52.3+14:00"));
  CHECK(gaga.member<xsd::DateTimeStamp>("test-datetimestamp") == xsd::DateTimeStamp("2001-10-26T19:32:52.3456+00:00"));
  CHECK(gaga.member<xsd::Int>("test-int") == xsd::Int(33));
  CHECK(gaga.member<xsd::Integer>("test-integer") == xsd::Integer(42));
  CHECK(gaga.member<xsd::Language>("test-language") == xsd::Language("en"));
  CHECK(gaga.member<xsd::NormalizedString>("test-normalizedstring") == xsd::NormalizedString("gaga gugus  newline"));
  CHECK(gaga.member<xsd::QName>("test-qname") == xsd::QName("ab:cde"));
  CHECK(gaga.member<xsd::Token>("test-token") == xsd::Token("gaga gugus newline"));
}