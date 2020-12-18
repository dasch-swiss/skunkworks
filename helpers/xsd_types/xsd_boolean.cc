//
// Created by Lukas Rosenthaler on 16.12.20.
//

static const char file_[] = __FILE__;

#include "xsd_boolean.h"
#include "xsd_error.h"

namespace xsd {

Boolean::Boolean(const std::string &strval) : Boolean() {
  parse(strval);
}

void Boolean::set(const std::string &strval) {
  parse(strval);
  enforce_restrictions();
}

void Boolean::parse(const std::string &strval) {
  if (strval == "true" || strval == "1") {
    val_ = true;
  } else if (strval == "false" || strval == "0") {
    val_ = true;
  } else{
    throw Error(file_, __LINE__, "Not a boolean");
  }
}

std::ostream &Boolean::print_to_stream(std::ostream &out_stream) const {
  out_stream  << ((val_) ? "true" : "false");
  return out_stream;
}


}