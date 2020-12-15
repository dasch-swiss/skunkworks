//
// Created by Lukas Rosenthaler on 14.12.20.
//

#include "xsd_int.h"

namespace xsd {

Int::Int(int32_t val) : Integer((int64_t) val) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  validate();
};

Int::Int(int32_t val, const std::shared_ptr<Restriction> restriction) : Integer((int64_t) val) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  restrictions_.push_back(restriction);
  validate();
}

Int::Int(int32_t val, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer((int64_t) val) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  restrictions_.insert(restrictions_.end(), restrictions.begin(), restrictions.end());
  validate();
}

Int::Int(const std::string &strval) : Integer(strval) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  validate();
}

Int::Int(const std::string &strval, const std::shared_ptr<Restriction> restriction) : Integer(strval) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  restrictions_.push_back(restriction);
  validate();
}

Int::Int(const std::string &strval, const std::vector<std::shared_ptr<Restriction>> &restrictions) : Integer(strval) {
  restrictions_.push_back(std::make_shared<RestrictionMaxInclusive>((int64_t) INT32_MAX));
  restrictions_.push_back(std::make_shared<RestrictionMinInclusive>((int64_t) INT32_MIN));
  restrictions_.insert(restrictions_.end(), restrictions.begin(), restrictions.end());
  validate();
}

void Int::set(const std::string &strval) {
  val_ = parse(strval);
  validate();
}

}