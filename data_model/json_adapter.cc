//
// Created by Lukas Rosenthaler on 02.01.21.
//

#include <memory>

#include "external/nlohmann/json.hpp"

#include "json_adapter.h"
#include "json_serializer.h"

namespace dsp {

template <typename T>
std::shared_ptr<T> JsonAdapter<T>::read(const Identifier &id, const std::shared_ptr<KeyValueStore> &store) {
  std::vector<uint8_t> data = store->read(id); // read data from store
  nlohmann::json json_obj = nlohmann::json::from_bson(data); // convert data to json object
  std::shared_ptr<T> objptr = std::make_shared<T>();
  objptr = serializer_.from_json(json_obj, objptr);
  return objptr;
}

template <typename T>
void JsonAdapter<T>::create(const std::shared_ptr<T> &obj, const std::shared_ptr<KeyValueStore> &store) {
  nlohmann::json json_obj = JsonSerializer::to_json(obj);
  store->create(obj->id(), nlohmann::json::to_bson(json_obj));
};

}