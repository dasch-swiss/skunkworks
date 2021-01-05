//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_KEY_VALUE_STORE_H_
#define SKUNKWORKS_DATA_MODEL_KEY_VALUE_STORE_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd.h"
#include "shared/dsp_types/identifier.h"

#include "project.h"


namespace dsp {

class KeyValueStore {
 public:
  virtual void create(const dsp::Identifier &id, const std::vector<uint8_t> data) = 0;

  virtual std::vector<uint8_t> read(const dsp::Identifier &id) = 0;

  virtual void update(const dsp::Identifier &id, const std::vector<uint8_t> data) = 0;

  virtual void remove(const dsp::Identifier &id) = 0;
};

}


#endif //SKUNKWORKS_DATA_MODEL_KEY_VALUE_STORE_H_
