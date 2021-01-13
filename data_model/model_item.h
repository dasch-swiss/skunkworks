//
// Created by Lukas Rosenthaler on 07.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_MODEL_ITEM_H_
#define SKUNKWORKS_DATA_MODEL_MODEL_ITEM_H_

#include <memory>
#include <unordered_map>

#include "external/nlohmann/json.hpp"

#include "shared/error/error.h"
#include "shared/dsp_types/identifier.h"

namespace dsp {

class ModelItem : public std::enable_shared_from_this<ModelItem> {
 public:
  inline ModelItem() { managed_ = false; }

  inline virtual ~ModelItem(){}

  dsp::Identifier id() const { return id_; }

  bool managed() const { return managed_; }

  bool static item_exists(const dsp::Identifier& id) {
    try {
      std::shared_ptr<ModelItem> tmp = items_.at(id);
      return true;
    } catch(const std::out_of_range &err) {
      return false;
    }
  }

  template<typename T>
  inline void add_item() {
    items_[id_] = shared_from_this();
    managed_ = true;
  }

  template<typename T>
  inline static std::shared_ptr<T> get_item(const dsp::Identifier& id) {
    try {
      return std::dynamic_pointer_cast<T>(items_.at(id));
    } catch(const std::out_of_range &err) {
      throw Error(__FILE__, __LINE__, "Item not found in map! " + id.to_string());
    }
  }

  inline void remove_item() {
    items_.erase(id_);
    managed_ = false;
  }

  template<typename T>
  inline static void delete_item(std::shared_ptr<T> &item) {
    item->remove_item();
    item.reset();
  }

  inline static int size() { return items_.size(); };

  inline static void print() {
    for (const auto& [key, val]: items_) std::cerr << key << " : " << std::endl << val << std::endl;
  }

  //virtual void to_cerr() = 0;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<ModelItem> item_ptr) {
    out_stream << std::setw(4) << item_ptr->to_json();
    return out_stream;
  }


  virtual nlohmann::json to_json() = 0;

 protected:
  dsp::Identifier id_;
 private:
  bool managed_;
  inline static std::unordered_map<dsp::Identifier, std::shared_ptr<ModelItem>> items_;

};



}

#endif //SKUNKWORKS_DATA_MODEL_MODEL_ITEM_H_
