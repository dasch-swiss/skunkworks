//
// Created by Lukas Rosenthaler on 01.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_

#include <string>

#include <regex>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "xsd_data_type.h"
#include "xsd_string.h"

namespace xsd {
//
// https://en.wikipedia.org/wiki/List_of_URI_schemes
//



class AnyUri : public DataType {
 public:
  explicit AnyUri(const std::string &strval);

  AnyUri(const std::string &protocol, const std::string &server, const std::string &path);

  explicit operator std::string() const override;

 private:
  static std::unordered_map<std::string, std::string> protocol_schemes;
  bool has_protocol_;
  std::string  protocol_;
  bool has_host_;
  std::string  host_;
  bool has_user_;
  std::string  user_;
  bool has_password_;
  std::string  password_;
  bool has_port_;
  int port_;
  bool has_path_;
  std::string path_sep_;
  std::vector<std::string> path_;
  bool has_fragment_;
  std::string  fragment_;
  bool has_options_;
  std::vector<std::string> options_;

  void parse_host_part(const std::string &rest, char user_passwd_separator = ':', char user_host_separator = '@');

  void parse(const std::string &str);
  std::ostream &print_to_stream(std::ostream &out_stream) const override;
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_
