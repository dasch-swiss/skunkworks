//
// Created by Lukas Rosenthaler on 02.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_IN_MEM_KV_STORE_H_
#define SKUNKWORKS_DATA_MODEL_IN_MEM_KV_STORE_H_

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "kv_store.h"

namespace dsp {

class InMemKVStore : public KVStore {
  /*!
   * This class implements an in-memory key-value store.
   */
 public:
  inline InMemKVStore() {};

  inline ~InMemKVStore() { };

  /*!
   * Create an entry in the key-value store
   * @param id dsp identifier
   * @param data
   */
  void create(const dsp::Identifier &id, const std::vector<uint8_t> data) override ;

  /*!
   * Read the data for a given key
   * @param id
   * @return
   */
  std::vector<uint8_t> read(const dsp::Identifier &id) override ;

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
  void remove(const dsp::Identifier &id) override ;

 private:
  std::unordered_map<dsp::Identifier, std::vector<uint8_t>> kvstore_;
};

}


#endif //SKUNKWORKS_DATA_MODEL_IN_MEM_KV_STORE_H_
