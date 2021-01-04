//
// Created by Lukas Rosenthaler on 02.01.21.
//


static const char file_[] = __FILE__;

#include "in_mem_store.h"
#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"

namespace dsp {

void InMemStore::create(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore.at(id);
    throw dsp::Error(file_, __LINE__, "InMemStore::create: Key " + static_cast<std::string>(id) + " already exists in kvstore.");
  } catch (const std::out_of_range &err) {
    kvstore[id] = data;
  }
}

std::vector<uint8_t> InMemStore::read(const dsp::Identifier &id) {
  try {
    return kvstore[id];
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemStore::read: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

void InMemStore::update(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore.at(id);
    kvstore[id] = data;
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemStore::update: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

void InMemStore::remove(const dsp::Identifier &id) {
  try {
    auto tmp = kvstore.at(id);
    kvstore.erase(id);
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, "InMemStore::remove: Key " + static_cast<std::string>(id) + " does not exist in kvstore.");
  }
}

}