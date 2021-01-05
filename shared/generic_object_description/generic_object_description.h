//
// Created by Lukas Rosenthaler on 04.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_
#define SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_

#include <string>
#include <unordered_map>
#include <memory>

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"


namespace dsp {

class GenericObjectDescription {
 private:
  typedef std::unordered_map<std::string, std::shared_ptr<xsd::DataType>> DataMap;

 public:
  inline explicit GenericObjectDescription(int version, const std::string& object_type) : version_(version), object_type_(object_type) {};

  inline int version() const { return version_; }

  inline std::string object_type() const { return object_type_; }

  template<typename T>
  inline void member(const std::string& name, const T& data) {
    data_[name] = std::make_shared<T>(data);
  }

  template<typename T>
  inline T member(const std::string& name) const {
    try {
      T* ptr = dynamic_cast<T*>(data_.at(name).get());
      return *ptr;
    } catch (const std::out_of_range &err) {
      throw Error(__FILE__, __LINE__, "GenericObjectDescription has no member \"" + name + "\".");
    }
  }

  bool has_member(const std::string& name) const;

  typedef DataMap::iterator iterator;
  typedef DataMap::const_iterator const_iterator;
  iterator begin() { return data_.begin(); }
  iterator end() { return data_.end(); }

 private:
  int version_;
  std::string object_type_;
  DataMap data_;

};


}


#endif //SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_
