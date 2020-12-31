//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_
#define SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_

namespace admin::user {

class GivenName {
 public:
  /*!
   * Default constructor. Sets Restrictions.
   */
  GivenName();

  /*!
   * Constructor taking a std::string as parameter.
   * @param value
   */
  inline explicit GivenName(const std::string &value) : GivenName() { value_ = value; };

  /*!
   * Constructor taking a xsd::String as parameter.
   * @param value
   */
  inline explicit GivenName(const xsd::String &value) : GivenName() { value_ = value; };

  /*!
   * Copy constructor taking a dsp::FamilyName as parameter.
   * @param value
   */
  inline explicit GivenName(const GivenName &value) : GivenName() { value_ = value.value_ ;};

  /*!
   * Direct assignment operator. Allows assigning a std::string directly as a value.
   * @param value of type std::string which is being directly assigned.
   * @return
   */
  inline GivenName &operator=(const std::string &value) { value_ = value; return *this; }

  /*!
   * Direct assignment operator. Allows assigning a GivenName directly as a value.
   * @param value of type GivenName which is being directly assigned.
   * @return
   */
  inline GivenName &operator=(const GivenName &value) = default;

  /*!
   * Accessor returning the value as std::string.
   * @return std::string
   */
  inline std::string value() { return value_.get(); }

  /*!
   * Equality comparison operator.
   * @param rhs the other value that we compare against.
   * @return true if if both values are the same.
   */
  inline bool operator==(const GivenName &rhs) const {
    return static_cast<std::string>(value_) == static_cast<std::string>(rhs.value_);
  }

  /*!
   * Check for empty value.
   * @return
   */
  inline bool empty() {
    return static_cast<std::string>(value_).empty();
  }

 private:
  xsd::String value_;
};

}

#endif //SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_
