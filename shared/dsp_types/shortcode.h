//
// Created by Lukas Rosenthaler on 28.12.20.
//

#ifndef SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_
#define SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_

#include <string>

#include "shared/xsd_types/xsd.h"

namespace dsp {

class Shortcode {
 public:
  /*!
   * Default constructor. Sets RestrictionPattern
   */
  Shortcode();

  /*!
   * Constructor taking a std::string as parameter
   * @param shortcode
   */
  inline explicit Shortcode(const std::string &shortcode)  : Shortcode() { shortcode_ = shortcode; }

  /*!
   * Constructor taking a xsd::string as parameter
   * @param shortcode
   */
  inline explicit Shortcode(const xsd::String &shortcode)  : Shortcode() { shortcode_ = shortcode; }

  /*!
   * Copy constructor taking a dsp::Shortname as parameter
   * @param shortcode
   */
  inline Shortcode(const Shortcode &shortcode) : Shortcode() { shortcode_ = shortcode.shortcode_; }

  /*!
   * Assignment operator with dsp:Shortcode
   * @param shortcode
   * @return
   */
  Shortcode &operator=(const Shortcode &shortcode);

  /*!
   * Assignment operator with xsd::String as parameter
   * @param shortcode
   * @return
   */
  Shortcode &operator=(const xsd::String &shortcode);

  /*!
   * Assignment operator with std::string as parameter
   * @param shortcode
   * @return
   */
  Shortcode &operator=(const std::string &shortcode);

  /*!
   * Explicit type cast to std::string
   * @return
   */
  inline explicit operator std::string() const { return static_cast<std::string>(shortcode_); }

  /*!
   * Equality operator with other shortcode
   * @param other
   * @return
   */
  inline bool operator==(const Shortcode &other) const { return shortcode_ == other.shortcode_; }

  /*!
   * Equality operator with xsd::String
   * @param other
   * @return
   */
  inline bool operator==(const xsd::String &other) const { return shortcode_ == other; }

  /*!
   * Equality operator with std::string
   * @param other
   * @return
   */
  inline bool operator==(const std::string &other) const { return static_cast<std::string>(shortcode_) == other; }

 private:
  xsd::String shortcode_;

};

}


#endif //SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_
