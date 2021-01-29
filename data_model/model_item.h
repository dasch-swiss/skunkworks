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

using namespace std::string_literals;

namespace dsp {

class ModelItem : public std::enable_shared_from_this<ModelItem> {
  /*!
   * This abstract class maintains an internal map of id's and the associated items. It is used in order
   * to map the internal id's of the data model items to the actual c++ pointers. Each data mode item must
   * therefore inherit from the ModelItem class!
   */
 public:
  /*!
   * Default constructor. Should be overridden by the implementations of tha actual data model items.
   * The implementation of the constructor should also set the id (protected variable "id_"!)
   */
  inline ModelItem() = default;

  /*!
   * Virtual destructor (needed to prevent memory leeks...)
   */
  inline virtual ~ModelItem(){}

  /*!
   * Getter for the id
   * @return dsp::Identifier instance
   */
  dsp::Identifier id() const { return id_; }

  /*!
   * Checks if an item with the given ID exists in the internal map
   * @param id dsp::Identifier instance
   * @return "true", if item exists, else "false"
   */
  bool static item_exists(const dsp::Identifier& id) {
    try {
      std::shared_ptr<ModelItem> tmp = items_.at(id);
      return true;
    } catch(const std::out_of_range &err) {
      return false;
    }
  }

  /*!
   * Adds the item to the internal list. Has to be called by the Factory that creates the
   * data model items. We need a factory because we cannot put this into the constructor
   * @tparam T
   */

  template<typename T>
  inline void add_item() {
    items_[id_] = shared_from_this();
  }

  /*!
   * Get an item with the given id from the internal list
   * @tparam T Class type of item to retrieve
   * @param id dsp::Identifier of item
   * @return Shared pointer to the item
   */
  template<typename T>
  inline static std::shared_ptr<T> get_item(const dsp::Identifier& id) {
    try {
      return std::dynamic_pointer_cast<T>(items_.at(id));
    } catch(const std::out_of_range &err) {
      throw Error(__FILE__, __LINE__, fmt::format(R"(Item with id="{}" not found in map!)"s, id.to_string()));
    }
  }

  /*!
   * Delete the item from the internal list
   * @tparam T Class type
   * @param item
   */
  template<typename T>
  inline static void delete_item(std::shared_ptr<ModelItem> item) {
    item->remove_item();
    //item.reset();
  }

  /*!
   * Return the number of items in the internal list
   * @return Number of items in list
   */
  inline static int size() { return items_.size(); };

  /*!
   * Print all items to std::cerr (for debugging purposes only)
   */
  inline static void print() {
    for (const auto& [key, val]: items_) std::cerr << key << " : " << std::endl << val << std::endl;
  }


  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<ModelItem> item_ptr) {
    out_stream << std::setw(4) << item_ptr->to_json();
    return out_stream;
  }

  /*!
   * Purre virtual function that converts the item into a json object
   * @return A json object
   */
  virtual nlohmann::json to_json() = 0;

  virtual std::string to_string() = 0;

 protected:
  dsp::Identifier id_;
 private:
  inline void remove_item() { items_.erase(id_); }

  inline static std::unordered_map<dsp::Identifier, std::shared_ptr<ModelItem>> items_;
};



}

#endif //SKUNKWORKS_DATA_MODEL_MODEL_ITEM_H_
