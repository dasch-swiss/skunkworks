//
// Created by Lukas Rosenthaler on 29.12.20.
//

#ifndef SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_
#define SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_

#include <string>

#define UUID_SYSTEM_GENERATOR

#include "third_party/stduuid/gsl/gsl"
#include "third_party/stduuid/uuid.h"

#include "shared/xsd_types/xsd_string.h"

namespace dsp {

class Id {
 public:
  Id();

  Id(const uuids::uuid &uuid) { uuid_ = uuid; }

  Id(const std::string &uuid_str);

  Id(const std::string &base, const std::string &name);

  inline bool operator==(const Id &other) const { return uuid_ == other.uuid_; }

  inline bool operator!=(const Id &other) const { return  uuid_ != other.uuid_; }

  inline bool operator<(const Id &other) const { return  uuid_ < other.uuid_; }

  inline uuids::uuid uuid() { return uuid_; }

  inline std::string to_string() const { return uuids::to_string(uuid_); }

  inline friend std::ostream &operator<<(std::ostream &out_stream, const Id &rhs) {
    out_stream << rhs.to_string();
    return out_stream;
  }


 private:
  uuids::uuid uuid_;
};

}

namespace std {

template<>
struct hash<dsp::Id> {
  std::size_t operator()(dsp::Id id) const noexcept {
    return std::hash<uuids::uuid>{}(id.uuid());
  }
};

}
#endif //SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_
