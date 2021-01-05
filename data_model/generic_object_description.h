//
// Created by Lukas Rosenthaler on 04.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_
#define SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_

#include <string>
#include <unordered_map>

#include "shared/xsd_types/xsd.h"
#include "shared/error/error.h"


namespace dsp {

class GenericObjectDescription {
 private:
  typedef std::unordered_map<std::string, std::shared_ptr<xsd::DataType>> DataMap;

 public:
  enum class ObjectType {
    AgentType, ProjectType, ResourceClassType, PropertyType
  };

  inline explicit GenericObjectDescription(ObjectType object_type) : object_type_(object_type) {};

  inline ObjectType object_type() const { return object_type_; }

  template<typename T>
  void member(const std::string& name, const T& data);

  template<typename T>
  T member(const std::string& name) const;

  bool has_member(const std::string& name) const;

  typedef DataMap::iterator iterator;
  typedef DataMap::const_iterator const_iterator;
  iterator begin() { return data_.begin(); }
  iterator end() { return data_.end(); }

 private:
  ObjectType object_type_;
  DataMap data_;

};


}


#endif //SKUNKWORKS_DATA_MODEL_GENERIC_OBJECT_DESCRIPTION_H_
