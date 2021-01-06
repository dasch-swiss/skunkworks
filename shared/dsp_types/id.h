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

class Identifier {
 public:
  Identifier();

  Identifier(const uuids::uuid &uuid) { uuid_ = uuid; }

  Identifier(const std::string &uuid_str);

  Identifier(const std::string &base, const std::string &name);

  inline bool operator==(const Identifier &other) const { return uuid_ == other.uuid_; }

  inline bool operator!=(const Identifier &other) const { return  uuid_ != other.uuid_; }

  inline bool operator<(const Identifier &other) const { return  uuid_ < other.uuid_; }

  inline uuids::uuid uuid() { return uuid_; }

  inline std::string to_string() const { return uuids::to_string(uuid_); }

  inline xsd::String to_xsd() const { return xsd::String(uuids::to_string(uuid_)); }

  inline operator std::string() const { return to_string(); }

  inline friend std::ostream &operator<<(std::ostream &out_stream, const Identifier &rhs) {
    out_stream << rhs.to_string();
    return out_stream;
  }


 private:
  uuids::uuid uuid_;
};

}

namespace std {

template<>
struct hash<dsp::Identifier> {
  std::size_t operator()(dsp::Identifier id) const noexcept {
    return std::hash<uuids::uuid>{}(id.uuid());
  }
};

}
#endif //SKUNKWORKS_HELPERS_DSP_TYPES_ID_H_
