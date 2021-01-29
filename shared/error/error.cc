//
// Created by Lukas Rosenthaler on 27.11.20.
//
#include <cstring>      // std::strerror
#include <sstream>      // std::ostringstream


#include "error.h"

namespace dsp {

Error::Error(const char *file, int line, const std::string msg, int errno) :
runtime_error(fmt::format("File: {} Line: {}: Msg: {}", file, line, msg)), line_(line), file_(file), message_(msg)
{
}
//=========================================================================

std::string Error::to_string(void) const {
  std::ostringstream err_stream;
  err_stream << "xsd-Error at [" << file_ << ": " << line_ << "]";
  if (sys_errno_ != 0) err_stream << " (system error: " << std::strerror(sys_errno_) << ")";
  err_stream << ": " << message_;
  return err_stream.str();
}
//=========================================================================

std::ostream &operator<<(std::ostream &out_stream, const Error &rhs) {
  std::string errStr = rhs.to_string();
  out_stream << errStr;
  return out_stream;
}
//============================================================================

}