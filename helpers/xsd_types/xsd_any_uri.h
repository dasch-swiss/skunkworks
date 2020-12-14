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
  /*!
   * This class implements the [xsd:anyURI](https://www.w3.org/TR/xmlschema11-2/#anyURI) class
   */
 public:
  /*!
   * Constructor which takes one std::string as parameter which is validated if the string corresponds to a
   * valid URI (dependoing on the protocol).
   * @param strval
   */
  explicit AnyUri(const std::string &strval);

  /*!
   * Conversion to std::string
   * @return
   */
  explicit operator std::string() const override;

  /*!
   * Set a new value
   * @param strval
   */
  void set(const std::string &strval) override;

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

  void parse(const std::string &str);

  void validate();

  std::ostream &print_to_stream(std::ostream &out_stream) const override;
};

}

#endif //SKUNKWORKS_HELPERS_XSD_TYPES_XSD_ANY_URI_H_