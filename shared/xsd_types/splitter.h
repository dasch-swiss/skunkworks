//
// Created by Lukas Rosenthaler on 18.12.20.
//

#ifndef SKUNKWORKS_HELPERS_XSD_TYPES_SPLITTER_H_
#define SKUNKWORKS_HELPERS_XSD_TYPES_SPLITTER_H_

namespace xsd {

typedef struct {
  bool success;
  std::string first;
  std::string second;
} SplitResult;

typedef struct {
  bool success;
  std::string separator;
  std::string left;
} NextSeparator;

std::vector<std::string> split(const std::string &strval, const std::string &splitter);

SplitResult split_at(const std::string &strval, size_t pos, int len = 1);

SplitResult split_first(const std::string &strval, char splitter);

SplitResult split_first(const std::string &strval, const std::string &splitter);

}
#endif //SKUNKWORKS_HELPERS_XSD_TYPES_SPLITTER_H_
