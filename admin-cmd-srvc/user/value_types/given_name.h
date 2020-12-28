//
// Created by Ivan Subotic on 23/12/2020.
//

#ifndef SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_
#define SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_

namespace admin::user {

class GivenName {
 public:
  GivenName(const std::string &value);
  inline std::string value() { return value_.get(); }
  bool operator==(const GivenName &rhs) const;

 private:
  xsd::String value_;
};

}

#endif //SKUNKWORKS_ENTITIES_USER_GIVEN_NAME_H_
