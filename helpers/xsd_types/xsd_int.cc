//
// Created by Lukas Rosenthaler on 14.12.20.
//

#include "xsd_int.h"

namespace xsd {

Int::Int() : Integer() {
  xsd_type_ = "int";
  val_ = 0ll;
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
}

Int::Int(int32_t val) : Integer((int64_t) val) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  enforce_restrictions();
};

Int::Int(int32_t val, const std::shared_ptr<Restriction> &restriction) : Int((int64_t) val) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Int::Int(int32_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Int((int64_t) val) {
  restrictions_.insert(restrictions_.end(), restrictions.begin(), restrictions.end());
  enforce_restrictions();
}

Int::Int(const std::string &strval) : Integer(strval) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  enforce_restrictions();
}

Int::Int(const std::string &strval, const std::shared_ptr<Restriction> &restriction) : Int(strval) {
  restrictions_.push_back(restriction);
  enforce_restrictions();
}

Int::Int(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Int(strval) {
  restrictions_.insert(restrictions_.end(), restrictions.begin(), restrictions.end());
  enforce_restrictions();
}

Int &Int::operator=(const std::string &strval) {
  set(strval);
  return *this;
}

Int &Int::operator=(int32_t val) {
  val_ = val;
  enforce_restrictions();
  return *this;
}


}