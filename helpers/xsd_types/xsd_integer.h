//
// Created by Lukas Rosenthaler on 12.12.20.
//



#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_

#include <string>

#include "xsd_data_type.h"
#include "xsd_restriction.h"
#include "xsd_error.h"

namespace xsd {

class Integer : public DataType {
  /*!
   * This class implements the xsd:integer datatype
   */
 public:
  /*!
   * Default constructor. Initializes the value to 0
   */
  inline Integer() { xsd_type_ = "integer"; val_ = 0ll;};

  /*!
   * Constructor with just one restriction (shared_ptr) as parameter
   * @param restriction
   */
  inline explicit Integer(const std::shared_ptr<Restriction> &restriction) : Integer() {
    restrictions_.push_back(restriction);
  }

  /*!
   * Constructor with a vector of restrictions (shared_ptr's) as parameter
   * @param restrictions
   */
  inline explicit Integer(const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer() {
    restrictions_ = restrictions;
  }

  /*!
   * Constructor with string parameter
   * @param val
   */
  explicit Integer(const std::string &val);

  /*!
   * Constructor with in64_t parameter
   * @param val (int64_t)
   */
  inline explicit Integer(int64_t val) : Integer() { val_ = val; };

  /*!
   * Constructor with int64_t parameter and one restriction
   * @param val
   * @param restriction
   */
  Integer(int64_t val, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor with int64_t parameter and vector of restrictions
   * @param val
   * @param restrictions
   */
  Integer(int64_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
   * Constructor with string parameter and one restriction
   * @param val
   * @param restriction
   */
  Integer(const std::string &val, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor with string parameter and multiple restrictions given as vector
   * @param val
   * @param restrictions
   */
  inline Integer(const std::string &val, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
   * Conversion to int64_t
   * @return
   */
  inline explicit operator int64_t () const { return val_; }

  Integer &operator=(const std::string &strval) override ;

  Integer &operator=(int64_t val);

  /*!
   * Getter for value as int64_t
   * @return
   */
  inline virtual int64_t get() { return val_; }

  void set(const std::string &strval) override ;

 protected:
  int64_t val_;

  void parse(const std::string &strval);


 private:


  std::ostream &print_to_stream(std::ostream &out_stream) const override;


};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_INT_H_
