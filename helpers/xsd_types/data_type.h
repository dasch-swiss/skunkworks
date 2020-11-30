//
// Created by Lukas Rosenthaler on 29.11.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_DATA_TYPE_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_DATA_TYPE_H_

#include <string>
#include <iomanip>
#include <iostream>

namespace xsd {

/*!
 * This is an abstract class that defines the common interface for all xsd datatypes
 */
class DataType {
 private:
  /*!
   * Parse a xsd date from a string. This does not include parsing xsd datatypes references such as "^^xsd:dateTime"
   *
   * @param str String with the value
   */
  virtual void parse(const std::string &str) = 0;

  /*!
   * Prints the pure value to a ostream
   *
   * @param out_stream A ostream to print the pure string value
   * @return the ostream used
   */
  virtual std::ostream &print_to_stream(std::ostream &out_stream) const = 0;
 public:

  /*!
   * Convert the pure value to string (no xsd type modifiers)
   *
   * @return C++ string with the value converted toa string
   */
  virtual operator std::string(void) const = 0;

  /*!
   * Friend method to use the "<<" operator for xsd:values
   *
   * @param out_stream Output stream
   * @param rhs Right hand side
   * @return Output stream
   */
  friend std::ostream &operator<<(std::ostream &out_stream, const DataType &rhs) {
    return rhs.print_to_stream(out_stream);
  }
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_DATA_TYPE_H_
