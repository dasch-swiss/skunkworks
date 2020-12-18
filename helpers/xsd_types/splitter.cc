//
// Created by Lukas Rosenthaler on 18.12.20.
//

#include <string>
#include <vector>
#include "splitter.h"

namespace xsd {

/*!
 * Split a string into a vector of parts at the locations where the split string fits
 * @param strval String to be splitted
 * @param splitter The token that is used to split
 * @return Vector of strings
 */
std::vector<std::string> split(const std::string &strval, const std::string &splitter) {
  size_t old_pos = 0;
  size_t pos;
  int len = splitter.length();
  std::vector<std::string> result;
  while ((pos = strval.find(splitter, old_pos)) != std::string::npos) {
    result.push_back(strval.substr(old_pos, pos - old_pos));
    old_pos = pos + len;
  }
  result.push_back(strval.substr(old_pos, std::string::npos));
  return result;
}

/*!
 * Split a string at a given position
 * @param strval  String to be splitted
 * @param pos Position where to split
 * @param len Number of characters to remove at the split position
 * @return Split result struct
 */
SplitResult split_at(const std::string &strval, size_t pos, int len) {
  std::string s1 = strval.substr(0, pos);
  std::string s2 = (pos == std::string::npos) ? "" : strval.substr(pos + len, std::string::npos);
  SplitResult result = {(pos != std::string::npos), s1, s2};
  return result;
}

/*!
 * Split a string at the first occurence of the split character
 * @param strval String to be splitted
 * @param splitter Split character
 * @return Split result struct
 */
SplitResult split_first(const std::string &strval, char splitter) {
  size_t pos = strval.find(splitter);
  return split_at(strval, pos);
}

/*!
 * Split a string at the split token
 * @param strval String to be splitted
 * @param splitter Split token
 * @return Split result struct
 */
SplitResult split_first(const std::string &strval, const std::string &splitter) {
  size_t pos = strval.find(splitter);
  return split_at(strval, pos, splitter.length());
}



}