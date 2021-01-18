//
// Created by Lukas Rosenthaler on 18.01.21.
//

#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"

#include "kv_store.h"
#include "in_mem_kv_store.h"

TEST_CASE("Resource class tests", "[catch2]") {
  SECTION("Unit tests") {
    dsp::InMemKVStore store;
    std::vector<uint8_t> data{11,22,33,44};
    dsp::Identifier id;
    REQUIRE_NOTHROW(store.create(id, data));
    REQUIRE_THROWS_AS(store.create(id, data), dsp::Error);
    std::vector<uint8_t> res = store.read(id);
    REQUIRE(data == res);
    std::vector<uint8_t> data2{1,2,3,4};
    REQUIRE_NOTHROW(store.update(id, data2));
    res = store.read(id);
    REQUIRE(data2 == res);
    dsp::Identifier id2;
    REQUIRE_THROWS_AS(store.update(id2, data), dsp::Error);
    REQUIRE_NOTHROW(store.remove(id));
    REQUIRE_THROWS_AS(store.read(id), dsp::Error);
  }
}