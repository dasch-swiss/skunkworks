//
// Created by Lukas Rosenthaler on 16.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_BOOLEAN_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_BOOLEAN_H_

#include <string>

#include "xsd_data_type.h"

namespace xsd {

class Boolean : public DataType {
  /*!
   * Class implementing the xsd:boolean value
   */
 public:
  Boolean() {
    xsd_type_ = "boolean";
    val_ = false;
  }

  /*!
   * Implements the std::string based constructor which creates an instance out of a string
   * @param strval
   */
  explicit Boolean(const std::string &strval);

  /*!
   * Constructor taking a C++ bool value as parameter
   * @param val
   */
  inline explicit Boolean(bool val) : Boolean() { val_ = val; };

  inline explicit operator bool() const { return val_; }

  void set(const std::string &strval) override;


  Boolean &operator=(const std::string &strval) override ;

  Boolean &operator=(bool bval);

  inline bool operator==(const Boolean &other) const { return val_ == other.val_; };

 protected:
  void parse(const std::string &strval);

  std::ostream &print_to_stream(std::ostream &out_stream) const override;

 private:
  bool val_;

};

}



#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_BOOLEAN_H_
