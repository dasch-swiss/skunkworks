//
// Created by Lukas Rosenthaler on 04.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_KV_JSON_STORE_H_
#define SKUNKWORKS_DATA_MODEL_KV_JSON_STORE_H_

#include "store.h"

namespace dsp {

class KVJsonStore : Store {
  void create(GenericObjectDescription& obj) override ;

  GenericObjectDescription read(const dsp::Identifier& id) override {};

  void update(const dsp::Identifier& id, const GenericObjectDescription& obj) override {};

  void remove(const dsp::Identifier& id) override {};

};

}


#endif //SKUNKWORKS_DATA_MODEL_KV_JSON_STORE_H_
