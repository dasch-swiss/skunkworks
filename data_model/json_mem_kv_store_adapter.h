//
// Created by Lukas Rosenthaler on 05.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_JSON_MEM_KV_STORE_ADAPTER_H_
#define SKUNKWORKS_DATA_MODEL_JSON_MEM_KV_STORE_ADAPTER_H_

#include "kv_store.h"
#include "shared/generic_object_description/generic_object_description.h"
#include "store_adapter.h"

namespace dsp {

class JsonMemKVStoreAdapter : public StoreAdapter  {
 public:
  inline explicit JsonMemKVStoreAdapter(const std::shared_ptr<KVStore> &store) :  store_(store) { }

  inline ~JsonMemKVStoreAdapter() override = default;

  void create(GenericObjectDescription& obj) override ;

  GenericObjectDescription read(const dsp::Identifier& id) override ;

  void update(const dsp::Identifier& id, GenericObjectDescription& obj) override ;

  void remove(const dsp::Identifier& id) override ;

 private:
  std::shared_ptr<KVStore> store_;

};

}


#endif //SKUNKWORKS_DATA_MODEL_JSON_MEM_KV_STORE_ADAPTER_H_
