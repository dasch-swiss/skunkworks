//
// Created by Lukas Rosenthaler on 30.12.20.
//

#include "catch2/catch.hpp"

#include <string>
#include <memory>
#include <unordered_map>

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"

#include "id.h"

using namespace std::string_literals;

TEST_CASE("DSP data types: Identifier", "SId") {
  CHECK_NOTHROW(dsp::Identifier());
  std::unordered_map<dsp::Identifier, std::string> mm;
  dsp::Identifier id1;
  dsp::Identifier id2;
  mm[id1] = "eins"s;
  mm[id2] = "zwei"s;
  CHECK(mm[id1] == "eins"s);
  dsp::Identifier my_id;
  std::string my_id_string = my_id.to_string();
  dsp::Identifier my_id2(my_id_string);
  CHECK(my_id == my_id2);
  auto named_id1 = dsp::Identifier("dasch.swiss"s, "lukas"s);
  auto named_id2 = dsp::Identifier("dasch.swiss"s, "lukas"s);
  CHECK(named_id1 == named_id2);
}
