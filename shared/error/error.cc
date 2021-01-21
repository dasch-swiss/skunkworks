//
// Created by Lukas Rosenthaler on 27.11.20.
//
#include <cstring>      // std::strerror
#include <sstream>      // std::ostringstream

#include "fmt/core.h"

#include "error.h"

namespace dsp {
/*
Error::Error(const char *file_p, const int line_p, const char *msg, int errno_p) : runtime_error(
    std::string(msg)
        + "\nFile: "
        + std::string(file_p)
        + std::string(" Line: ")
        + std::to_string(line_p)), line(line_p), file(file_p), message(msg), sysErrno(errno_p) {
}*/
Error::Error(const char *file_p, const int line_p, const char *msg, int errno_p) : runtime_error(
    fmt::format("File: {} Line: {}: Msg: {}", file_p, line_p, msg)),
    line(line_p), file(file_p), message(msg), sysErrno(errno_p) {
}
//=========================================================================


Error::Error(const char *file_p, const int line_p, const std::string &msg, int errno_p) : runtime_error(
    fmt::format("File: {} Line: {}: Msg: {}", file_p, line_p, msg)),
    line(line_p), file(file_p), message(msg), sysErrno(errno_p) {
}
//=========================================================================

std::string Error::to_string(void) const {
  std::ostringstream err_stream;
  err_stream << "xsd-Error at [" << file << ": " << line << "]";
  if (sysErrno != 0) err_stream << " (system error: " << std::strerror(sysErrno) << ")";
  err_stream << ": " << message;
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