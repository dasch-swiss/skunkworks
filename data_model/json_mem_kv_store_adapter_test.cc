//
// Created by Lukas Rosenthaler on 18.01.21.
//

//
// Created by Lukas Rosenthaler on 18.01.21.
//

#include "catch2/catch.hpp"

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"

#include "kv_store.h"
#include "in_mem_kv_store.h"
#include "json_mem_kv_store_adapter.h"

TEST_CASE("Resource class tests", "[catch2]") {
  SECTION("Unit tests") {
    std::shared_ptr<dsp::InMemKVStore> kvstore = std::make_shared<dsp::InMemKVStore>();
    dsp::JsonMemKVStoreAdapter store(kvstore);
    dsp::Identifier id;
    nlohmann::json json_obj{{"a", "AA"}, {"b", 42}};
    REQUIRE_NOTHROW(store.create(id, json_obj));
    REQUIRE_THROWS_AS(store.create(id, json_obj), dsp::Error);
    nlohmann::json json_res = store.read(id);
    REQUIRE(json_obj == json_res);

    json_obj = nlohmann::json{{"a", "AAA"}, {"b", 4711}, {"pi", 3.14159}};
    REQUIRE_NOTHROW(store.update(id, json_obj));
    json_res = store.read(id);
    REQUIRE(json_obj == json_res);

    dsp::Identifier id2;
    REQUIRE_THROWS_AS(store.update(id2, json_obj), dsp::Error);
    REQUIRE_NOTHROW(store.remove(id));
    REQUIRE_THROWS_AS(store.read(id), dsp::Error);
  }
}