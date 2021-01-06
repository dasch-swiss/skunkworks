//
// Created by Lukas Rosenthaler on 04.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_
#define SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_

//#include "shared/generic_object_description/generic_object_description.h"
#include "external/nlohmann/json.hpp"
#include "shared/dsp_types/identifier.h"

namespace dsp {

class StoreAdapter {
 public:
  StoreAdapter() = default;
  virtual ~StoreAdapter() {};

  virtual void create(nlohmann::json& obj) = 0;

  virtual nlohmann::json read(const dsp::Identifier& id) = 0;

  virtual void update(const dsp::Identifier& id, nlohmann::json& obj) = 0;

  virtual void remove(const dsp::Identifier& id) = 0;
};

}

#endif //SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_
