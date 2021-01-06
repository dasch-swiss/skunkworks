//
// Created by Lukas Rosenthaler on 02.01.21.
//


static const char file_[] = __FILE__;

#include "in_mem_kv_store.h"
#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"

namespace dsp {

void InMemKVStore::create(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore_.at(id);
    throw dsp::Error(file_, __LINE__, "InMemKVStore::create: Key " + static_cast<std::string>(id) + " already exists in kvstore.");
  } catch (const std::out_of_range &err) {
    kvstore_[id] = data;
  }
}

std::vector<uint8_t> InMemKVStore::read(const dsp::Identifier &id) {
  try {
    return kvstore_[id];
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemKVStore::read: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

void InMemKVStore::update(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore_.at(id);
    kvstore_[id] = data;
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemKVStore::update: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

void InMemKVStore::remove(const dsp::Identifier &id) {
  try {
    auto tmp = kvstore_.at(id);
    kvstore_.erase(id);
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemKVStore::remove: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

}