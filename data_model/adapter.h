//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_ADAPTER_H_
#define SKUNKWORKS_ENTITIES_ADAPTER_H_

#include "generic_object_description.h"
#include "key_value_store.h"

namespace dsp {

class Adapter {
 public:
  Adapter(const std::shared_ptr<KeyValueStore> &store) : store_(store) {};
  virtual GenericObjectDescription read(const Identifier &id) = 0;
  virtual void create(const GenericObjectDescription &obj) = 0;
  virtual void update(const GenericObjectDescription &obj) = 0;
  virtual void remove(const Identifier &id) = 0;
 private:
  std::shared_ptr<KeyValueStore> store_;
};

}

#endif //SKUNKWORKS_ENTITIES_ADAPTER_H_
