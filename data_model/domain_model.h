//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
#define SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_

#include <string>
#include <unordered_map>
#include <utility>

//#include "agent.h"
//#include "project.h"
#include "store_adapter.h"
#include "model_item.h"

namespace dsp {

class DomainModel {
 public:
  inline explicit DomainModel(std::shared_ptr<StoreAdapter> store_adapter) : store_adapter_(std::move(store_adapter)) {}

  template<typename T>
  inline void create(std::shared_ptr<T> item)  {
    static_assert(std::is_base_of<ModelItem, T>::value, "T not derived from ModelItem");
    nlohmann::json json_obj = item->to_json();
    store_adapter_->create(item->id(), json_obj);
  }

  template<typename T>
  inline std::shared_ptr<T> read(const dsp::Identifier &id)  {
    static_assert(std::is_base_of<ModelItem, T>::value, "T not derived from ModelItem");
    nlohmann::json json_obj = store_adapter_->read(id);
    std::shared_ptr<T> item_ptr = T::Factory(json_obj);
    return item_ptr;
  }

  template<typename T>
  inline void update(const std::shared_ptr<T> &item)  {
    static_assert(std::is_base_of<ModelItem, T>::value, "T not derived from ModelItem");
    nlohmann::json old_json_obj = store_adapter_->read(item->id());
    nlohmann::json json_obj = item->to_json();
    store_adapter_->update(item->id(), json_obj);
  }

 private:
  std::shared_ptr<StoreAdapter> store_adapter_;
  // std::unordered_map<dsp::Identifier, std::shared_ptr<ModelItem>> items_;
};

}

#endif //SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
