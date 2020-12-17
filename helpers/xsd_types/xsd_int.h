//
// Created by Lukas Rosenthaler on 14.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_INT_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_INT_H_

#include "xsd_integer.h"
#include "xsd_restriction.h"
#include "xsd_error.h"

namespace xsd {

class Int : public Integer {
 public:
  /*!
   * Default constructor
   */
  Int();

  /*!
   * Constructor with just one restriction
   * @param restriction
   */
  inline explicit Int(const std::shared_ptr<Restriction> &restriction) : Int() {
    restrictions_.push_back(restriction);
  }

  inline explicit Int(const std::vector<std::shared_ptr<Restriction>> &restrictions) : Int() {
    restrictions_.insert(restrictions_.end(), restrictions.begin(), restrictions.end());
  }

  /*!
   * Constructor taking a int32_t (32-Bit) integer
   * @param val
   */
  explicit Int(int32_t val);

  /*!
   * Constrctor taking a int32_t integer and one restriction (shared_ptr)
   * @param val
   * @param restriction
   */
  Int(int32_t val, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a int32_t integer and a vector of restrictions (shared_ptr's)
   * @param val
   * @param restrictions
   */
  Int(int32_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
   * Constructor taking a std::string value
   * @param val
   */
  explicit Int(const std::string &strval);

  /*!
   * Constructor taking a std::string value and one restriction (shared_ptr)
   * @param val
   * @param restriction
   */
  Int(const std::string &strval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a std::string and a vector of restrictions (shared_ptr's)
   * @param val
   * @param restrictions
   */
  Int(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);


  /*!
   * Assignment operator taking a string
   * @param strval
   * @return
   */
  Int &operator=(const std::string &strval) override;

  /*!
   * Assignment operator taking a int32_t value
   * @param val
   * @return
   */
  Int &operator=(int32_t val);

};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
