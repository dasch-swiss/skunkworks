//
// Created by Lukas Rosenthaler on 12.12.20.
//

#include <string>

#include "xsd_data_type.h"
#include "xsd.h"

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_

namespace xsd {

class Integer : public DataType{
  /*!
   * This class implements the xsd:integer datatype
   */
 public:
  /*!
   * Default constructor
   */
  inline Integer() { xsd_type_ = "int"; };

  /*!
   * Constructor with in64_t parameter
   * @param val (int64_t)
   */
  inline Integer(int64_t val) : val_(val) { xsd_type_ = "int"; };

  /*!
   * Constructor with int64_t parameter and one restriction
   * @param val
   * @param restriction
   */
  inline Integer(int64_t val, const std::shared_ptr<Restriction> restriction) : Integer(val) {
    restrictions_.push_back(restriction);
    validate();
  };

  /*!
   * Constructor with int64_t parameter and vector of restrictions
   * @param val
   * @param restrictions
   */
  inline Integer(int64_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer(val) {
    restrictions_ = restrictions;
    validate();
  };

  /*!
   * Constructor with string parameter
   * @param val
   */
  Integer(const std::string &val);

  /*!
   * Constructor with string parameter and one restriction
   * @param val
   * @param restriction
   */
  inline Integer(const std::string &val, const std::shared_ptr<Restriction> restriction) : Integer(val) {
    restrictions_.push_back(restriction);
    validate();
  }

  /*!
   * Constructor with string parameter and multiple restrictions given as vector
   * @param val
   * @param restrictions
   */
  inline Integer(const std::string &val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer(val) {
    restrictions_ = restrictions;
    validate();
  }

  /*!
   * Conversion to string
   * @return
   */
  operator std::string() const override;

  /*!
   * Conversion to int64_t
   * @return
   */
  inline operator int64_t () const { return val_; }

  /*!
   * Getter for value as int64_t
   * @return
   */
  inline int64_t get() { return val_; }

  inline void set(const std::string &strval) override;

 protected:
  int64_t val_;
  std::vector<std::shared_ptr<Restriction>> restrictions_;

  inline void validate() {
    for (auto r: restrictions_) {
      if (!r->validate(std::to_string(val_))) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
    }
  }

 private:


  std::ostream &print_to_stream(std::ostream &out_stream) const override;

  int64_t parse(const std::string &strval);

};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
