//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
#define SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_

#include <string>
#include <unordered_map>

#include "agent.h"
#include "project.h"
#include "store_adapter.h"
#include "model_item.h"

namespace dsp {

class DomainModel {
 public:
  DomainModel(const std::shared_ptr<StoreAdapter> &store_adapter) : store_adapter_(store_adapter) {}

  template<typename T>
  void create(const std::shared_ptr<T> &item);

  template<typename T>
  std::shared_ptr<T> read(const dsp::Identifier &id);

  template<typename T>
  void update(const dsp::Identifier &id, const std::shared_ptr<T> &item);

 private:
  std::shared_ptr<StoreAdapter> store_adapter_;
  std::unordered_map<dsp::Identifier, std::shared_ptr<ModelItem>> items_;
};

}

#endif //SKUNKWORKS_DATA_MODEL_DOMAIN_MODEL_H_
