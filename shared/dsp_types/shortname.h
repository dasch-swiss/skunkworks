//
// Created by Ivan Subotic on 05/01/2021.
//

#ifndef SKUNKWORKS_SHARED_DSP_TYPES_SHORTNAME_H_
#define SKUNKWORKS_SHARED_DSP_TYPES_SHORTNAME_H_

#include "shared/xsd_types/xsd.h"

namespace dsp {

class Shortname {
 public:
  /*!
   * Default constructor. Sets RestrictionPattern
   */
  Shortname();

  /*!
   * Constructor taking a std::string as parameter
   * @param Shortname
   */
  inline explicit Shortname(const std::string &shortname) : Shortname() { shortname_ = shortname; }

  /*!
   * Constructor taking a xsd::string as parameter
   * @param shortname
   */
  inline explicit Shortname(const xsd::String &shortname) : Shortname() { shortname_ = shortname; }

  /*!
   * Copy constructor taking a dsp::Shortname as parameter
   * @param shortname
   */
  inline Shortname(const Shortname &shortname) : Shortname() { shortname_ = shortname.shortname_; }

  /*!
   * Assignment operator with dsp:Shortname
   * @param shortname
   * @return
   */
  Shortname &operator=(const Shortname &shortname);

  /*!
   * Assignment operator with xsd::String as parameter
   * @param shortname
   * @return
   */
  Shortname &operator=(const xsd::String &shortname);

  /*!
   * Assignment operator with std::string as parameter
   * @param shortname
   * @return
   */
  Shortname &operator=(const std::string &shortname);

  /*!
   * Explicit type cast to std::string
   * @return
   */
  inline explicit operator std::string() const { return static_cast<std::string>(shortname_); }

  /*!
   * Equality operator with other shortname
   * @param other
   * @return
   */
  inline bool operator==(const Shortname &other) const { return shortname_ == other.shortname_; }

  /*!
   * Equality operator with xsd::String
   * @param other
   * @return
   */
  bool operator==(const xsd::String &other) const { return shortname_ == other; }

  /*!
   * Equality operator with std::string
   * @param other
   * @return
   */
  bool operator==(const std::string &other) const { return static_cast<std::string>(shortname_) == other; }

  inline friend std::ostream &operator<<(std::ostream &out_stream, const Shortname &rhs) {
    out_stream << static_cast<std::string>(rhs);
    return out_stream;
  }

 private:
  xsd::String shortname_;

};

}

#endif //SKUNKWORKS_SHARED_DSP_TYPES_SHORTNAME_H_
