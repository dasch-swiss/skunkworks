//
// Created by Lukas Rosenthaler on 29.12.20.
//

#ifndef SKUNKWORKS_HELPERS_DSP_TYPES_SHORTNAME_H_
#define SKUNKWORKS_HELPERS_DSP_TYPES_SHORTNAME_H_

#include "helpers/xsd_types/xsd.h"

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
  explicit Shortname(const std::string &shortname);

  /*!
   * Constructor taking a xsd::string as parameter
   * @param shortname
   */
  explicit Shortname(const xsd::String &shortname);

  /*!
   * Copy constructor taking a dsp::Shortname as parameter
   * @param shortname
   */
  Shortname(const Shortname &shortname);

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
  explicit operator std::string() const;

  /*!
   * Equality operator with other shortname
   * @param other
   * @return
   */
  bool operator==(const Shortname &other) const;

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
  xsd::String shortname_;

};

}


#endif //SKUNKWORKS_HELPERS_DSP_TYPES_SHORTNAME_H_
