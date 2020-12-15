//
// Created by Lukas Rosenthaler on 29.11.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DATA_TYPE_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DATA_TYPE_H_

#include <string>
#include <iomanip>
#include <iostream>

#include "xsd_restriction.h"

namespace xsd {

/*!
 * This is an abstract class that defines the common interface for all xsd data types
 */
class DataType {
 public:
  inline const std::string xsd_type(void) const { return xsd_type_; };

  /*!
   * Convert the pure value to string (no xsd type modifiers)
   *
   * @return C++ string with the value converted to a string
   */
  virtual explicit operator std::string(void) const = 0;

  std::string get() { return static_cast<std::string>(*this); }

  virtual void set(const std::string &strval) = 0;

  /*!
   * Friend method to use the "<<" operator for xsd:values
   *
   * @param out_stream Output stream
   * @param rhs Right hand side
   * @return Output stream
   */
  inline friend std::ostream &operator<<(std::ostream &out_stream, const DataType &rhs) {
    return rhs.print_to_stream(out_stream);
  }

 protected:
  std::string xsd_type_;
  std::vector<std::shared_ptr<Restriction>> restrictions_;


 private:
  /*!
   * Prints the pure value to a ostream
   *
   * @param out_stream A ostream to print the pure string value
   * @return the ostream used
   */
  virtual std::ostream &print_to_stream(std::ostream &out_stream) const = 0;
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DATA_TYPE_H_
