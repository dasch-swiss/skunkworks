//
// Created by Lukas Rosenthaler on 13.12.20.
//

#include <string>
#include <regex>
#include <utility>
#include <vector>
#include <memory>
#include <set>
#include <regex>

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_RESTRICTION_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_RESTRICTION_H_

namespace xsd {

/*!
 * This abstract class defines the interface for restrictions that can be applied for a xsd::String class.
 * It basically requires one method to be implemented that tests if a string fullfills the restrictions
 * and returns "true" (everything ok) or "false" if the restriction is not fullfilled.
 */
class Restriction {
 public:
  /*!
   * Virtual destructor (is required!)
   */
  virtual ~Restriction() = default;;

  /*!
   * Check if the string given a parameter fullfills the restriction
   * @param strval String to be checked
   * @return "true" if restriction is fullfilled, "false" otherwise
   */
  [[nodiscard]] virtual bool validate(const std::string &strval) const = 0;
};

/*!
 * Implements the length restriction which requires the string to have exactely a given length
 */
class RestrictionLength final : public Restriction {
 public:
  /*!
   * Constructor with the length a parameter
   * @param length Length restriction for string
   */
  inline explicit RestrictionLength(int length) : length_(length) {}

  /*!
   *  Destructor (final)
   */
  inline ~RestrictionLength() final = default;

  /*!
   * Validate exact length restriction
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline bool validate(const std::string &strval) const final { return strval.length() == length_; }

 private:
  int length_;
};

/*!
 * Implements the minimal length restriction
 */
class RestrictionMinLength final : public Restriction {
 public:
  /*!
   * Constructor with minimal lengt as parameter
   * @param min_length Minimal length of the string
   */
  inline explicit RestrictionMinLength(int min_length) : min_length_(min_length) {}

  /*!
   * Destructor (final)
   */
  inline ~RestrictionMinLength() final = default;

  /*!
   * Validates minimal length of string
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline bool validate(const std::string &strval) const final { return strval.length() >= min_length_; }

 private:
  int min_length_;
};

/*!
 * Implements the maximal length restriction
 */
class RestrictionMaxLength final : public Restriction {
 public:
  /*!
   * Constructor for the minimal length restriction
   * @param min_length Minimal length required
   */
  inline explicit RestrictionMaxLength(int max_length) : max_length_(max_length) {}

  /*!
   * Destructor (final)
   */
  inline ~RestrictionMaxLength() final = default;

  /*!
   * Validates maximal length of destructor
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline bool validate(const std::string &strval) const final { return strval.length() <= max_length_; }

 private:
  int max_length_;
};

/*!
 * Implements for the pattern restriction which tests the string if it fullfills a given regex pattern
 */
class RestrictionPattern final : public Restriction {
 public:
  /*!
   * Constructor for the pattern restriction
   * @param pattern A valid C++ regex pattern
   */
  inline explicit RestrictionPattern(std::string pattern) : pattern_(std::move(pattern)) {}

  /*!
   * Destructor (final)
   */
  inline ~RestrictionPattern() final = default;

  /*!
   * Validate the pattern using standard c++ regex
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    return std::regex_match(strval, std::regex(pattern_));
  }

 private:
  std::string pattern_;
};

/*!
 * Enumeration restrictions which tests if the string is out of a set of valid strings
 */
class RestrictionEnumeration final : public Restriction {
 private:
  std::set<std::string> enums_;
 public:
  /*!
   * Constructor for the enumeration restriction
   * @param enums Set of strings that indicate the allowed values for the string
   */
  inline explicit RestrictionEnumeration(std::set<std::string> enums) : enums_(std::move(enums)) {}

  /*!
   * Destructor (final)
   */
  inline ~RestrictionEnumeration() final = default;

  /*!
   * Validate if string is in set
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    for (const auto &s: enums_) {
      if (s == strval) return true;
    }
    return false;
  }
};

class RestrictionMaxInclusive final : public Restriction {
 private:
  double dmaxval_;
 public:
  inline explicit RestrictionMaxInclusive(const std::string &strval) {
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dmaxval_ = std::stof(strval);
    }
  }

  inline explicit RestrictionMaxInclusive(int64_t maxval) { dmaxval_ = (double) maxval; }

  inline explicit RestrictionMaxInclusive(double maxval) : dmaxval_(maxval) {}

  inline ~RestrictionMaxInclusive() final = default;

  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return (dval <= dmaxval_);
  }
};

class RestrictionMaxExclusive final : public Restriction {
 private:
  double dmaxval_;
 public:
  inline explicit RestrictionMaxExclusive(const std::string &strval) {
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dmaxval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMaxExclusive(int64_t maxval) { dmaxval_ = (double) maxval; }

  inline explicit RestrictionMaxExclusive(double maxval) : dmaxval_(maxval) {}

  inline ~RestrictionMaxExclusive() final = default;

  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return (dval < dmaxval_);
  }
};

class RestrictionMinInclusive final : public Restriction {
 private:
  double dminval_;
 public:
  inline explicit RestrictionMinInclusive(const std::string &strval) {
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dminval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMinInclusive(int64_t maxval) { dminval_ = (double) maxval; }

  inline explicit RestrictionMinInclusive(double maxval) : dminval_(maxval) {}

  inline ~RestrictionMinInclusive() final = default;

  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return (dval >= dminval_);
  }
};

class RestrictionMinExclusive final : public Restriction {
 private:
  double dminval_;
 public:
  inline explicit RestrictionMinExclusive(const std::string &strval) {
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dminval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMinExclusive(int64_t maxval) { dminval_ = (double) maxval; }

  inline explicit RestrictionMinExclusive(double maxval) : dminval_(maxval) {}

  inline ~RestrictionMinExclusive() final = default;

  [[nodiscard]] inline bool validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return (dval > dminval_);
  }
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_RESTRICTION_H_
