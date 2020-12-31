//
// Created by Lukas Rosenthaler on 28.12.20.
//

#ifndef SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_
#define SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_

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
  explicit Shortcode(const std::string &shortcode);

  /*!
   * Constructor taking a xsd::string as parameter
   * @param shortcode
   */
  explicit Shortcode(const xsd::String &shortcode);

  /*!
   * Copy constructor taking a dsp::Shortname as parameter
   * @param shortcode
   */
  Shortcode(const Shortcode &shortcode);

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
  explicit operator std::string() const;

  /*!
   * Equality operator with other shortcode
   * @param other
   * @return
   */
  bool operator==(const Shortcode &other) const;

  /*!
   * Equality operator with xsd::String
   * @param other
   * @return
   */
  bool operator==(const xsd::String &other) const;

  /*!
   * Equality operator with std::string
   * @param other
   * @return
   */
  bool operator==(const std::string &other) const;

 private:
  xsd::String shortcode_;

};

}


#endif //SKUNKWORKS_HELPERS_DSP_TYPES_SHORTCODE_H_
