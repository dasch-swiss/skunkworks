//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_IN_MEM_STORE_H_
#define SKUNKWORKS_DATA_MODEL_IN_MEM_STORE_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd.h"
#include "shared/dsp_types/identifier.h"

#include "project.h"

#include "adapter.h"

#include "key_value_store.h"

namespace dsp {

class InMemStore : public KeyValueStore {
  /*!
   * This class implements an in-memory key-value store. It is a singleton with a static method "getInstance" which
   * is used to get access to the stire
   */
 public:
  InMemStore() {}

  /*!
   * Create an entry in the key-value store
   * @param id dsp identifier
   * @param data
   */
  void create(const dsp::Identifier &id, const std::vector<uint8_t> data) override;

  /*!
   * Read the data for a given key
   * @param id
   * @return
   */
  std::vector<uint8_t> read(const dsp::Identifier &id) override;

  /*!
   * Update the data of a given key
   * @param id
   * @param data
   */
  void update(const dsp::Identifier &id, const std::vector<uint8_t> data) override;

  /*!
   * Remove a given key and it's data from the key value store
   * @param id
   */
  void remove(const dsp::Identifier &id) override;

  /*!
   * No copy constructor
   */
  InMemStore(InMemStore const&) = delete;

  /*!
   * No assignment constructor
   */
  void operator=(InMemStore const&) = delete;
 private:
  std::unordered_map<dsp::Identifier, std::vector<uint8_t>> kvstore;
};

}


#endif //SKUNKWORKS_DATA_MODEL_IN_MEM_STORE_H_
