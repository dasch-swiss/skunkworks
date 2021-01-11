//
// Created by Lukas Rosenthaler on 02.01.21.
//
#include <memory>
#include "shared/error/error.h"
#include "domain_model.h"


namespace dsp {

template<typename T>
void DomainModel::create(const std::shared_ptr<T> &item) {
  nlohmann::json json_obj = item->to_json();
  store_adapter_->create(json_obj);
  items_[item->id()] = item;

}

template<typename T>
std::shared_ptr<T> DomainModel::read(const dsp::Identifier &id) {
  try {
    std::shared_ptr<T> item = std::dynamic_pointer_cast<T>(items_.at(id));
    return item;
  } catch (const std::out_of_range &err) {
    nlohmann::json json_obj = store_adapter_->read(id);
    T item(json_obj);
    std::shared_ptr<T> item_ptr = std::make_shared<Agent>(item);
    items_[id] = item_ptr;
    return item_ptr;
  }
}

template<typename T>
void DomainModel::update(const dsp::Identifier &id, const std::shared_ptr<T> &item) {
  nlohmann::json old_json_obj = store_adapter_->read(id);
  nlohmann::json json_obj = item->to_json();
  store_adapter_->update(id, json_obj);
}

}