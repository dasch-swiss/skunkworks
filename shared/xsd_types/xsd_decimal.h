//
// Created by Lukas Rosenthaler on 14.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DECIMAL_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DECIMAL_H_

#include "xsd_data_type.h"
#include "xsd_restriction.h"
#include "xsd_error.h"

namespace xsd {

class Decimal : public DataType {
 public:
  /*!
   * Default constructor
   */
  inline Decimal() { xsd_type_ = "decimal"; dval_ = 0.0; };

  /*!
   * Constructor with just one restriction (shared_ptr)
   * @param restriction
   */
  inline explicit Decimal(const std::shared_ptr<Restriction> &restriction) : Decimal() {
    restrictions_.push_back(restriction);
  }

  /*!
   * Constructor with a vector of restrictions (shared_ptr's)
   * @param restrictions
   */
  inline explicit Decimal(const std::vector<std::shared_ptr<Restriction>> &restrictions) : Decimal() {
    restrictions_ = restrictions;
  }

  /*!
   * Constructor taking a native double value
   * @param dval
   */
  inline explicit Decimal(double dval) : Decimal() { dval_ = dval;  };

  /*!
   * Constructor taking a native double value and one restriction (shared_ptr)
   * @param dval
   * @param restriction
   */
  Decimal(double dval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a native double and a vector of restrictions (shared_ptr's)
   * @param dval
   * @param restrictions
   */
  Decimal(double dval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  /*!
   * Constructor taking a string value (shared_ptr)
   * @param strval
   */
  inline explicit Decimal(const std::string &strval) { parse(strval); };

  /*!
   * Constructor taking a string value and single restriction (shared_ptr)
   * @param strval
   * @param restriction
   */
  Decimal(const std::string &strval, const std::shared_ptr<Restriction> &restriction);

  /*!
   * Constructor taking a string value and a vector of restrictions (shared_ptr's)
   * @param strval
   * @param restrictions
   */
  Decimal(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  void set(const std::string &strval) override ;

  /*!
   * Getter for native double value
   * @return
   */
  inline double getVal() const { return dval_; }

  /*!
   * Assignment operator with std::string right hand side
   * @param strval
   * @return
   */
  Decimal &operator=(const std::string& strval) override ;

  /*!
   * Assignment operator with double right hand side
   * @param dval
   * @return
   */
  Decimal &operator=(double dval);

  bool operator==(const Decimal &other) const ;

 protected:
  double dval_;

  void parse(const std::string &strval);


 private:

  std::ostream &print_to_stream(std::ostream &out_stream) const override;

};

}

namespace std {

template<> struct hash<xsd::Decimal> {
  std::size_t  operator()(xsd::Decimal const &value) const noexcept {
    return std::hash<double>{}(value.getVal());
  }
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DECIMAL_H_
