//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_JSON_ADAPTER_H_
#define SKUNKWORKS_DATA_MODEL_JSON_ADAPTER_H_

#include "adapter.h"
#include "json_serializer.h"
namespace dsp {

template <typename T>
class JsonAdapter: public Adapter<T>{
 public:
  inline JsonAdapter(const JsonSerializer &serializer) : serializer_(serializer) {};
  std::shared_ptr<T> read(const Identifier &id, const std::shared_ptr<KeyValueStore> &store) override ;
  void create(const std::shared_ptr<T> &obj, const std::shared_ptr<KeyValueStore> &store) override ;
  void update(const T &obj) override {};
  void remove(const Identifier &id) override {};
 private:
  JsonSerializer serializer_;
};


}

#endif //SKUNKWORKS_DATA_MODEL_JSON_ADAPTER_H_
