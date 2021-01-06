//
// Created by Lukas Rosenthaler on 05.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_KV_STORE_H_
#define SKUNKWORKS_DATA_MODEL_KV_STORE_H_

#include <vector>

#include "shared/dsp_types/id.h"

namespace dsp {

class KVStore {
 public:
  virtual ~KVStore() {};

  virtual void create(const dsp::Identifier &id, const std::vector<uint8_t> data) = 0;

  virtual std::vector<uint8_t> read(const dsp::Identifier &id) = 0;

  virtual void update(const dsp::Identifier &id, const std::vector<uint8_t> data) = 0;

  virtual void remove(const dsp::Identifier &id) = 0;

};


}

#endif //SKUNKWORKS_DATA_MODEL_KV_STORE_H_
