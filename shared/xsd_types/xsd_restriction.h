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
  struct Result {
    bool success;
    std::string msg;
  };
  /*!
   * Virtual destructor (is required!)
   */
  virtual ~Restriction() = default;

  /*!
   * Check if the string given a parameter fulfills the restriction
   * @param strval String to be checked
   * @return "true" if restriction is fulfilled, "false" otherwise
   */
  [[nodiscard]] virtual Result validate(const std::string &strval) const = 0;
 protected:
  std::string message_;
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
  inline explicit RestrictionLength(int length, std::string message = "") : length_(length) { message_ = message; }

  /*!
   *  Destructor (final)
   */
  inline ~RestrictionLength() final = default;

  /*!
   * Validate exact length restriction
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    return {strval.length() == length_, message_ + ": Validation of RestrictionLength failed"}; }

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
  inline explicit RestrictionMinLength(int min_length, std::string message = "") : min_length_(min_length) { message_ = message; }

  /*!
   * Destructor (final)
   */
  inline ~RestrictionMinLength() final = default;

  /*!
   * Validates minimal length of string
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    return { strval.length() >= min_length_, message_ + ": Validation of RestrictionMinLength failed"} ;
  }

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
  inline explicit RestrictionMaxLength(int max_length, std::string message = "") : max_length_(max_length) { message_ = message; }

  /*!
   * Destructor (final)
   */
  inline ~RestrictionMaxLength() final = default;

  /*!
   * Validates maximal length of destructor
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    return { strval.length() <= max_length_, message_ + ": Validation of RestrictionMaxLength failed"};
  }

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
  inline explicit RestrictionPattern(std::string pattern, std::string message = "") : pattern_(std::move(pattern)) { message_ = message_; }

  /*!
   * Destructor (final)
   */
  inline ~RestrictionPattern() final = default;

  /*!
   * Validate the pattern using standard c++ regex
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    return { std::regex_match(strval, std::regex(pattern_)), message_ + ": Validation of RestrictionPattern failed" };
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
  inline explicit RestrictionEnumeration(std::set<std::string> enums, std::string message = "") : enums_(std::move(enums)) { message_ = message; }

  /*!
   * Destructor (final)
   */
  inline ~RestrictionEnumeration() final = default;

  /*!
   * Validate if string is in set
   * @param strval
   * @return true if validation passes, otherwise false
   */
  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    for (const auto &s: enums_) {
      if (s == strval) return {true, "Validation of RestrictionEnumeration ok"};
    }
    return {false, message_ + ": Validation of RestrictionEnumeration failed"};
  }
};

class RestrictionMaxInclusive final : public Restriction {
 private:
  double dmaxval_;
 public:
  inline explicit RestrictionMaxInclusive(const std::string &strval, std::string message = "") {
    message_ = message;
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dmaxval_ = std::stof(strval);
    }
  }

  inline explicit RestrictionMaxInclusive(double maxval, std::string message = "") : dmaxval_(maxval) { message_ = message; }

  inline ~RestrictionMaxInclusive() final = default;

  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return {dval <= dmaxval_, message_ + ": Validation of RestrictionMaxInclusive failed"};
  }
};

class RestrictionMaxExclusive final : public Restriction {
 private:
  double dmaxval_;
 public:
  inline explicit RestrictionMaxExclusive(const std::string &strval, std::string message = "") {
    message_ = message;
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dmaxval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMaxExclusive(double maxval, std::string message = "") : dmaxval_(maxval) {
    message_ = message;
  }

  inline ~RestrictionMaxExclusive() final = default;

  [[nodiscard]] inline  Result validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return { dval < dmaxval_, message_ + "Validation of RestrictionMaxExclusive failed"};
  }
};

class RestrictionMinInclusive final : public Restriction {
 private:
  double dminval_;
 public:
  inline explicit RestrictionMinInclusive(const std::string &strval, std::string message = "") {
    message_ = message;
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dminval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMinInclusive(double maxval, std::string message = "") : dminval_(maxval) {
    message_ = message;
  }

  inline ~RestrictionMinInclusive() final = default;

  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return {dval >= dminval_, message_ + ": Validation of RestrictionMinInclusive failed"};
  }
};

class RestrictionMinExclusive final : public Restriction {
 private:
  double dminval_;
 public:
  inline explicit RestrictionMinExclusive(const std::string &strval, std::string message = "") {
    message_ = message;
    if (std::regex_match(strval.c_str(), std::regex(R"((\+|\-)?([0-9]+)?(\.[0-9]+)?)"))) {
      dminval_ = std::stod(strval);
    }
  }

  inline explicit RestrictionMinExclusive(double maxval, std::string message = "") : dminval_(maxval) {}

  inline ~RestrictionMinExclusive() final = default;

  [[nodiscard]] inline Result validate(const std::string &strval) const final {
    double dval = std::stod(strval);
    return {dval > dminval_, message_ + ": Validation of RestrictionMinExclusive failed"};
  }
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_RESTRICTION_H_
