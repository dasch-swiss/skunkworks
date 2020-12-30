//
// Created by Lukas Rosenthaler on 29.11.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DATA_TYPE_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DATA_TYPE_H_

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "shared/xsd_types/xsd_error.h"
#include "shared/xsd_types/xsd_restriction.h"

namespace xsd {

/*!
 * This is an abstract class that defines the common interface for all xsd data types
 */
class DataType {
 public:

  /*!
   * Default constructor; Usually has to be overridden!! It must set the "xsd_type_" variable
   */
  inline DataType() = default;


  /*!
   * Getter for the data type
   *
   * @return
   */
  [[nodiscard]] inline std::string xsd_type() const { return xsd_type_; };

  /*!
   * Convert the  value to string (no xsd type modifiers)
   *
   * @return C++ string with the value converted to a string
   */
  operator std::string() const {
    std::stringstream ss;
    ss.imbue(std::locale::classic());
    ss << *this;
    return ss.str();
  }

  virtual DataType &operator=(const std::string &strval) = 0;


  /*!
   * Getter for the string representation of the xsd:value
   * @return
   */
  [[nodiscard]] std::string get() const { return static_cast<std::string>(*this); }

  virtual void set(const std::string &strval) =  0;

  void add_restriction(const std::shared_ptr<Restriction> &restriction) { restrictions_.push_back(restriction); }

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


  /*!
   * This protected function validates all restrictions.
   */
  virtual void enforce_restrictions(void) const final {
    for (auto r: restrictions_) {
      Restriction::Result result = r->validate(static_cast<std::string>(*this));
      if (!result.success) throw Error(__FILE__, __LINE__,
          "The type " + xsd_type_ + "did not pass validation of restrictions: " + result.msg + "!");
    }
  }

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
