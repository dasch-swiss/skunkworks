//
// Created by Lukas Rosenthaler on 30.11.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_

#include <string>
#include <regex>
#include <vector>
#include <set>

#include "xsd_data_type.h"
#include "xsd_error.h"

namespace xsd {

/*!
 * This abstract class defines the interface for restrictions that can be applied for a xsd::String class.
 * It basically requires one method to be implemented that tests if a string fullfills the restrictions
 * and returns "true" (everything ok) or "false" if the restriction is not fullfilled.
 */
class StringRestriction {
 public:
  /*!
   * Check if the string given a parameter fullfills the restriction
   * @param strval String to be checked
   * @return "true" if restriction is fullfilled, "false" otherwise
   */
  virtual bool validate(const std::string &strval) const = 0;
};

/*!
 * Implements the length restriction which requires the string to have exactely a given length
 */
class StringRestrictionLength : public StringRestriction {
 private:
  int length_;
 public:
  /*!
   * Constructor with the length a parameter
   * @param length Length restriction for string
   */
  inline StringRestrictionLength(int length) : length_(length) {}
  inline bool validate(const std::string &strval) const override { return strval.length() == length_; }
};

/*!
 * Implements the minimal length restriction
 */
class StringRestrictionMinLength : public StringRestriction {
 private:
  int min_length_;
 public:
  /*!
   * Constructor with minimal lengt as parameter
   * @param min_length Minimal length of the string
   */
  inline StringRestrictionMinLength(int min_length) : min_length_(min_length) {}
  inline bool validate(const std::string &strval) const override { return strval.length() >= min_length_; }
};

/*!
 * Implements the maximal length restriction
 */
class StringRestrictionMaxLength : public StringRestriction {
 private:
  int max_length_;
 public:
  /*!
   * Constructor for the minimal length restriction
   * @param min_length Minimal length required
   */
  inline StringRestrictionMaxLength(int min_length) : max_length_(min_length) {}
  inline bool validate(const std::string &strval) const override { return strval.length() <= max_length_; }
};

/*!
 * Implements for the pattern restriction which tests the string if it fullfills a given regex pattern
 */
class StringRestrictionPattern : public StringRestriction {
 private:
  std::string pattern_;
 public:
  /*!
   * Constructor for the pattern restriction
   * @param pattern A valid C++ regex pattern
   */
  inline StringRestrictionPattern(const std::string &pattern) : pattern_(pattern) {}
  inline bool validate(const std::string &strval) const override {
    return std::regex_match(strval, std::regex(pattern_));
  }
};

/*!
 * Enumeration restrictions which tests if the string is out of a set of valid strings
 */
class StringRestrictionEnumeration : public StringRestriction {
 private:
  std::set<std::string> enums_;
 public:
  /*!
   * Constructor for the enumeration restriction
   * @param enums Set of strings that indicate the allowed values for the string
   */
  inline StringRestrictionEnumeration(const std::set<std::string> &enums) : enums_(enums) {}
  inline bool validate(const std::string &strval) const override {
    for (auto s: enums_) {
      if (s == strval) return true;
    }
    return false;
  }
};

/*!
 * Implements the xsd:string datatype (including restrictions)
 */
class String : public DataType {
 protected:
  std::string strval_;

 private:
  /*!
   * Implement interface requirement (parsing)
   * @param str String to be parsed
   */
  inline void parse(const std::string &str) override {
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

 public:
  /*!
   * Default constructor
   */
  inline String() {};

  /*!
   * Constructor which assigns a given c++ string to the state
   * @param strval c++ string value
   */
  inline String(const std::string &strval) : strval_(strval) {}

  /*!
   * Constructor which assigns a given c++ string to the state and adds a single restriction
   * @param strval String to ba assigned
   * @param restriction Restriction to be applied
   */
  inline String(const std::string &strval, const StringRestriction &restriction) : strval_(strval) {
    if (!restriction.validate(strval_)) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
  }

  /*!
   * Constructor which assigns a given c++ string to the state and adds a set of restrictions
   * @param strval String to ba assigned
   * @param restrictions Set of restrictions to be applied
   */
  inline String(const std::string &strval, const std::vector<StringRestriction> &restrictions) : strval_(strval) {
    for (int i = 0; i < restrictions.size(); i++) {
      if (!restrictions[i].validate(strval_)) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
    }
  }

  /*!
   * type conversion to std::string
   * @return A std::string containing the value
   */
  inline operator std::string(void) const override {
    return strval_;
  }

};


}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_STRING_H_
