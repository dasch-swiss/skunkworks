//
// Created by Lukas Rosenthaler on 02.01.21.
//


static const char file_[] = __FILE__;
#include <string>

using namespace std::string_literals;

#include "in_mem_kv_store.h"
#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"

namespace dsp {

void InMemKVStore::create(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore_.at(id);
    throw dsp::Error(file_, __LINE__,
        fmt::format(R"(InMemKVStore::create: Key "{}" already exists in kvstore!)"s, id.to_string()));
  } catch (const std::out_of_range &err) {
    kvstore_[id] = data;
  }
}

std::vector<uint8_t> InMemKVStore::read(const dsp::Identifier &id) {
  try {
    return kvstore_.at(id);
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, fmt::format(R"(InMemKVStore::read: Key "{}" does not exist in kvstore.)"s, id.to_string()));
  }
}

void InMemKVStore::update(const dsp::Identifier &id, const std::vector<uint8_t> data) {
  try {
    auto tmp = kvstore_.at(id);
    kvstore_[id] = data;
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, fmt::format(R"(InMemKVStore::read: Key "{}" does not exist in kvstore.)"s, id.to_string()));
  }
}

void InMemKVStore::remove(const dsp::Identifier &id) {
  try {
    auto tmp = kvstore_.at(id);
    kvstore_.erase(id);
  } catch (const std::out_of_range &err) {
    throw dsp::Error(file_, __LINE__, fmt::format(R"(InMemKVStore::read: Key "{}" does not exist in kvstore.)"s, id.to_string()));
  }
}

}