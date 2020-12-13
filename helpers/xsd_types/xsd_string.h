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

namespace xsd {

/*!
 * This abstract class defines the interface for restrictions that can be applied for a xsd::String class.
 * It basically requires one method to be implemented that tests if a string fullfills the restrictions
 * and returns "true" (everything ok) or "false" if the restriction is not fullfilled.
 */
class StringRestriction {
 public:
  /*!
   * Virtual destructor (is required!)
   */
  virtual ~StringRestriction() {};

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
class StringRestrictionLength final : public StringRestriction {
 public:
  /*!
   * Constructor with the length a parameter
   * @param length Length restriction for string
   */
  inline StringRestrictionLength(int length) : length_(length) {}

  /*!
   *  Destructor (final)
   */
  inline ~StringRestrictionLength() final {}

  /*!
   * Validate exact length restriction
   * @param strval
   * @return true if validation passes, otherwise false
   */
  inline bool validate(const std::string &strval) const final { return strval.length() == length_; }

 private:
  int length_;
};

/*!
 * Implements the minimal length restriction
 */
class StringRestrictionMinLength final : public StringRestriction {
 public:
  /*!
   * Constructor with minimal lengt as parameter
   * @param min_length Minimal length of the string
   */
  inline StringRestrictionMinLength(int min_length) : min_length_(min_length) {}

  /*!
   * Destructor (final)
   */
  inline ~StringRestrictionMinLength() final {}

  /*!
   * Validates minimal length of string
   * @param strval
   * @return true if validation passes, otherwise false
   */
  inline bool validate(const std::string &strval) const final { return strval.length() >= min_length_; }

 private:
  int min_length_;
};

/*!
 * Implements the maximal length restriction
 */
class StringRestrictionMaxLength final : public StringRestriction {
 public:
  /*!
   * Constructor for the minimal length restriction
   * @param min_length Minimal length required
   */
  inline StringRestrictionMaxLength(int max_length) : max_length_(max_length) {}

  /*!
   * Destructor (final)
   */
  inline ~StringRestrictionMaxLength() final {}

  /*!
   * Validates maximal length of destructor
   * @param strval
   * @return true if validation passes, otherwise false
   */
  inline bool validate(const std::string &strval) const final { return strval.length() <= max_length_; }

 private:
  int max_length_;
};

/*!
 * Implements for the pattern restriction which tests the string if it fullfills a given regex pattern
 */
class StringRestrictionPattern final : public StringRestriction {
 public:
  /*!
   * Constructor for the pattern restriction
   * @param pattern A valid C++ regex pattern
   */
  inline StringRestrictionPattern(const std::string &pattern) : pattern_(pattern) {}

  /*!
   * Destructor (final)
   */
  inline ~StringRestrictionPattern() final {}

  /*!
   * Validate the pattern using standard c++ regex
   * @param strval
   * @return true if validation passes, otherwise false
   */
  inline bool validate(const std::string &strval) const final {
    return std::regex_match(strval, std::regex(pattern_));
  }

 private:
  std::string pattern_;
};

/*!
 * Enumeration restrictions which tests if the string is out of a set of valid strings
 */
class StringRestrictionEnumeration final : public StringRestriction {
 private:
  std::set<std::string> enums_;
 public:
  /*!
   * Constructor for the enumeration restriction
   * @param enums Set of strings that indicate the allowed values for the string
   */
  inline StringRestrictionEnumeration(const std::set<std::string> &enums) : enums_(enums) {}

  /*!
   * Destructor (final)
   */
  inline ~StringRestrictionEnumeration() final {}

  /*!
   * Validate if string is in set
   * @param strval
   * @return true if validation passes, otherwise false
   */
  inline bool validate(const std::string &strval) const final {
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
   * xsd::String("gaga@1234", std::make_shared<xsd::StringRestrictionPattern>("\\w*@[0-9]*"))
   * ```
   *
   * @param strval String to ba assigned
   * @param restriction Restriction to be applied
   */
  inline String(const std::string &strval, const std::shared_ptr<StringRestriction> restriction) : String(strval) {
    restrictions_.push_back(restriction);
    validate();
  }

  /*!
   * Constructor which assigns a given c++ string to the state and adds a set of restrictions
  *
   * Please note that the restriction has to be passed as shared pointer of a vector of shared pointers, e.g.:
   * ```C++
   *   std::vector<std::shared_ptr<xsd::StringRestriction>> restrictions = {
   *     std::make_shared<xsd::StringRestrictionMinLength>(5),
   *     std::make_shared<xsd::StringRestrictionMaxLength>(10)
   *   };
   *   xsd::String tmp("abcdefg", restrictions);
   * ```
   *
   * @param strval String to ba assigned
   * @param restrictions Set of restrictions to be applied
   */
  inline String(const std::string &strval, const std::vector<std::shared_ptr<StringRestriction>> &restrictions) : strval_(strval) {
    xsd_type_ = "string";
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
  std::vector<std::shared_ptr<StringRestriction>> restrictions_;

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
