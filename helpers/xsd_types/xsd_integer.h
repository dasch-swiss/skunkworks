//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include <string>

#include "xsd_data_type.h"
#include "xsd.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_

namespace xsd {

class Integer : public DataType{
 public:
  inline Integer() { xsd_type_ = "int"; };

  inline Integer(int val) : val_(val) { xsd_type_ = "int"; };

  Integer(const std::string &val);

  operator std::string() const override ;

  inline operator int () const { return val_; }


 private:
  int val_;

  std::ostream &print_to_stream(std::ostream &out_stream) const override;

};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
