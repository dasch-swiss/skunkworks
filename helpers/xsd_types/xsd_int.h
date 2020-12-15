//
// Created by Lukas Rosenthaler on 14.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_INT_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_INT_H_

#include "xsd_integer.h"
#include "xsd_restriction.h"
#include "xsd_error.h"

namespace xsd {

class Int : public Integer {
 public:
  inline Int() : Integer() { xsd_type_ = "int"; }

  Int(int32_t val);

  Int(int32_t val, const std::shared_ptr<Restriction> restriction);

  Int(int32_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  Int(const std::string &val);

  Int(const std::string &val, const std::shared_ptr<Restriction> restriction);

  Int(const std::string &val, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
 * Getter for value as int64_t
 * @return
 */
  inline int32_t get() { return (int32_t) val_; }

  void set(const std::string &strval) override;

};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
