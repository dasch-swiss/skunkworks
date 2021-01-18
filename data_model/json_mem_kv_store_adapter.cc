//
// Created by Lukas Rosenthaler on 05.01.21.
//

#include "json_mem_kv_store_adapter.h"

#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"
#include "shared/xsd_types/xsd.h"
//static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {



void JsonMemKVStoreAdapter::create(const dsp::Identifier& id, nlohmann::json& json_obj) {
  std::vector<std::uint8_t> cbor_obj = nlohmann::json::to_cbor(json_obj);
  store_->create(id, cbor_obj);
}

nlohmann::json JsonMemKVStoreAdapter::read(const dsp::Identifier& id) {
  std::vector<std::uint8_t> data = store_->read(id); // throws an error if id is not found in store
  return nlohmann::json::from_cbor(data);
}

void JsonMemKVStoreAdapter::update(const dsp::Identifier& id, nlohmann::json& json_obj) {
  nlohmann::json old_json_obj = read(id); // may throw an error if something prevents from reading the object

  //if (!json_obj.contains("version")) throw Error(file_, __LINE__, R"(update: Object has no "version" field)"s);
  //if (!json_obj.contains("type")) throw Error(file_, __LINE__, R"(update: Object has no "object_type" field)"s);
  //if (!json_obj.contains("id")) throw Error(file_, __LINE__, R"(update: Object has no "id".)"s);
  //if (id != dsp::Identifier(json_obj["id"])) throw Error(file_, __LINE__, R"(update: Object has different "id" from the one to be updated.)"s);
  std::vector<std::uint8_t> cbor_obj = nlohmann::json::to_cbor(json_obj);
  store_->update(id, nlohmann::json::to_cbor(json_obj));
};

void JsonMemKVStoreAdapter::remove(const dsp::Identifier& id) {
  store_->remove(id);
}

}