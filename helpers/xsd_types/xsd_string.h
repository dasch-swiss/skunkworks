//
// Created by Lukas Rosenthaler on 30.11.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_

#include <string>
#include <regex>
#include <vector>
#include <memory>
#include <set>

#include "xsd_data_type.h"
#include "xsd_error.h"
#include "xsd_restriction.h"

namespace xsd {


/*!
 * Implements the xsd:string datatype (including restrictions)
 */
class String : public DataType {
  /*!
   * Implements the xsd:string class with restrictions
   */
 public:
  /*!
   * Default constructor
   */
  inline String() { xsd_type_ = "string"; };

  /*!
   * Constructor which assigns a given c++ string to the state
   * @param strval c++ string value
   */
  inline String(const std::string &strval) : strval_(strval) { xsd_type_ = "string"; }

  /*!
   * Constructor which assigns a given c++ string to the state and adds a single restriction
   *
   * Please note that the restriction has to be passed as shared pointer, e.g.:
   * ```C++
   * xsd::String("gaga@1234", std::make_shared<xsd::RestrictionPattern>("\\w*@[0-9]*"))
   * ```
   *
   * @param strval String to ba assigned
   * @param restriction Restriction to be applied
   */
  inline String(const std::string &strval, const std::shared_ptr<Restriction> restriction) : String(strval) {
    restrictions_.push_back(restriction);
    validate();
  }

  /*!
   * Constructor which assigns a given c++ string to the state and adds a set of restrictions
  *
   * Please note that the restriction has to be passed as shared pointer of a vector of shared pointers, e.g.:
   * ```C++
   *   std::vector<std::shared_ptr<xsd::Restriction>> restrictions = {
   *     std::make_shared<xsd::RestrictionMinLength>(5),
   *     std::make_shared<xsd::RestrictionMaxLength>(10)
   *   };
   *   xsd::String tmp("abcdefg", restrictions);
   * ```
   *
   * @param strval String to ba assigned
   * @param restrictions Set of restrictions to be applied
   */
  inline String(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : String(strval) {
    restrictions_ = restrictions;
    validate();
  }

  /*!
   * type conversion to std::string
   * @return A std::string containing the value
   */
  inline operator std::string(void) const override {
    return strval_;
  }

  inline void set(const std::string &strval) override {
    strval_ = strval;
    validate();
  }

 protected:
  std::string strval_;
  std::vector<std::shared_ptr<Restriction>> restrictions_;

  inline void validate() {
    for (auto r: restrictions_) {
      if (!r->validate(strval_)) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
    }
  }

 private:
  /*!
   * Implement interface requirement (parsing)
   * @param str String to be parsed
   */
  inline void parse(const std::string &str) {
    strval_ = str;
  }

  /*!
   * Implements the interface requirements by sending the interal state (data) to a character output stream
   * @param out_stream
   * @return output stream
   */
  inline std::ostream &print_to_stream(std::ostream &out_stream) const override {
    return out_stream << strval_;
  }


};


}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_
