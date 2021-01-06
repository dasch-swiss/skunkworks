//
// Created by Lukas Rosenthaler on 05.01.21.
//

#include "json_mem_kv_store_adapter.h"

#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"
#include "shared/xsd_types/xsd.h"
static const char file_[] = __FILE__;

using namespace std::string_literals;

namespace dsp {



void JsonMemKVStoreAdapter::create(GenericObjectDescription& obj) {
  nlohmann::json json_obj = {
      {"version", obj.version()},
      {"object_type", obj.object_type()}
  };
  if (!obj.has_member("id")) throw Error(file_, __LINE__, R"(Object has no "id" field)"s);
  dsp::Identifier id(obj.member<xsd::String>("id"));
  for (const auto &s: obj) {
    json_obj[s.first] = *(s.second);
  }
  std::vector<std::uint8_t> cbor_obj = nlohmann::json::to_cbor(json_obj);
  store_->create(id, cbor_obj);
  std::cerr << std::setw(4) << json_obj << std::endl;
}


GenericObjectDescription JsonMemKVStoreAdapter::read(const dsp::Identifier& id) {
  std::vector<std::uint8_t> data = store_->read(id); // throws an error if id is not found in store
  nlohmann::json json_obj = nlohmann::json::from_cbor(data);

  if (!json_obj.contains("version")) throw Error(file_, __LINE__, R"(Object has no "version" field.)"s);
  if (!json_obj.contains("object_type")) throw Error(file_, __LINE__, R"(Object has no "object_type" field.)"s);
  GenericObjectDescription obj(json_obj["version"], json_obj["object_type"]);

  for (const auto& [key, value]: json_obj.items()) {
    if (value.is_string()) {
      obj.member(key, xsd::String(value));
    } else if (value.is_number_integer()) {
      obj.member(key, xsd::Integer((int64_t) value));
    } else if (value.is_number_float()) {
      obj.member(key, xsd::Decimal((double) value));
    } else if (value.is_array()) {
      ; // ToDo !!!
    } else if (value.is_object()) {
      ; // ToDo !!!
    }
  }
  obj.print();
  return obj;
}

void JsonMemKVStoreAdapter::update(const dsp::Identifier& id, GenericObjectDescription& obj) {
  GenericObjectDescription old_obj = read(id); // may throw an error if something prevents from reading the object

  if (!obj.has_member("version")) throw Error(file_, __LINE__, R"(Object has no "version" field)"s);
  if (!obj.has_member("object_type")) throw Error(file_, __LINE__, R"(Object has no "object_type" field)"s);
  nlohmann::json json_obj = {
      {"version", obj.version()},
      {"object_type", obj.object_type()}
  };
  dsp::Identifier id2(obj.member<xsd::String>("id"));
  for (const auto& s: obj) {
    json_obj[s.first] = *(s.second);
  }
  std::vector<std::uint8_t> cbor_obj = nlohmann::json::to_cbor(json_obj);
  store_->update(id, cbor_obj);
};

void JsonMemKVStoreAdapter::remove(const dsp::Identifier& id) {
  store_->remove(id);
}

}