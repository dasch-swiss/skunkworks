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
  inline Decimal() { xsd_type_ = "decimal"; };

  inline Decimal(double dval) : Decimal() { dval_ = dval;  };

  Decimal(double dval, const std::shared_ptr<Restriction> restriction);

  Decimal(double dval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  inline Decimal(const std::string strval) { dval_ = parse(strval); };

  Decimal(const std::string strval, const std::shared_ptr<Restriction> restriction);

  Decimal(const std::string strval, const std::vector<std::shared_ptr<Restriction>> &restrictions);

  inline double get() { return dval_; }

  void set(const std::string &strval) override;

  operator std::string() const override;

 protected:
  double dval_;

  double parse(const std::string &strval);

  inline void validate() {
    for (auto r: restrictions_) {
      if (!r->validate(std::to_string(dval_))) throw Error(__FILE__, __LINE__, "xsd:string did not pass validation!");
    }
  }

 private:

  std::ostream &print_to_stream(std::ostream &out_stream)  const override;

};

}


#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_DECIMAL_H_
