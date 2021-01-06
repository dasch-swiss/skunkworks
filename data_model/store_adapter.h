//
// Created by Lukas Rosenthaler on 04.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_
#define SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_

#include "shared/generic_object_description/generic_object_description.h"
#include "shared/dsp_types/id.h"

namespace dsp {

class StoreAdapter {
 public:
  StoreAdapter() = default;
  virtual ~StoreAdapter() {};

  virtual void create(GenericObjectDescription& obj) = 0;

  virtual GenericObjectDescription read(const dsp::Identifier& id) = 0;

  virtual void update(const dsp::Identifier& id, GenericObjectDescription& obj) = 0;

  virtual void remove(const dsp::Identifier& id) = 0;
};

}

#endif //SKUNKWORKS_DATA_MODEL_STORE_ADAPTER_H_
