//
// Created by Lukas Rosenthaler on 01.12.20.
//

#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>

#include "xsd_error.h"
#include "xsd_any_uri.h"

static const char file_[] = __FILE__;

namespace xsd {

std::unordered_map<std::string, std::string> AnyUri::protocol_schemes = {
    {"afp", "host|/|path"}, // [user@]host[:port]/][/path]
    {"ark", "X|\n"},
    {"doi:", "X|\n"},
    {"file", "?host|/|path|\n"},
    {"geo", "X|\n"},
    {"git", "X|\n"},
    {"http", "host|/|?path|#|?fragment|?|?options|\n"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"https", "host|/|path|#|fragment|?|options|\n"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"mailto", "host|?|?options|\n"},
    {"rsync", "host|/|path|\n"},
    {"s3", "path|\n"},
    {"svn", "host|/|path|\n"},
    {"svn+ssh", "host|/|path|\n"},
    {"urn", "X|\n"},
    {"ws", "path|\n"},
    {"wss", "path|\n"},
    {"xri", "host|/|?path|?|?options|#|?fragment|\n"},

};

typedef struct {
  bool success;
  std::string first;
  std::string second;
} SplitResult;

typedef struct {
  size_t pos;
  std::string separator;
} NextSeparator;

static std::vector<std::string> split(const std::string &strval, char splitter) {
  size_t old_pos = 0;
  size_t pos;
  std::vector<std::string> result;
  while ((pos = strval.find(splitter, old_pos)) != std::string::npos) {
    result.push_back(strval.substr(old_pos, pos - old_pos));
    old_pos = pos + 1;
  }
  result.push_back(strval.substr(old_pos, std::string::npos));
  return result;
}

static std::vector<std::string> split(const std::string &strval, const std::string &splitter) {
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

static SplitResult split_at(const std::string &strval, size_t pos, int len = 1) {
  std::string s1 = strval.substr(0, pos);
  std::string s2 = (pos == std::string::npos) ? "" : strval.substr(pos + len, std::string::npos);
  SplitResult result = {(pos != std::string::npos), s1, s2};
  return result;
}


static SplitResult split_first(const std::string &strval, char splitter) {
  size_t pos = strval.find(splitter);
  return split_at(strval, pos);
}

static SplitResult split_first(const std::string &strval, const std::string &splitter) {
  size_t pos = strval.find(splitter);
  return split_at(strval, pos, splitter.length());
}

NextSeparator next_sep_pos(const std::string &strval, std::vector<std::string> &separators) {
  size_t pos = std::string ::npos;
  std::string sc;
  for (auto s: separators) {
    size_t tmp_pos = strval.find(s, 0);
    if ((tmp_pos != std::string::npos) && (tmp_pos < pos)) {
      pos = tmp_pos;
      sc = s;
    }
  }
  NextSeparator next_separator = {pos,  sc};
  return next_separator;
}

void AnyUri::parse_host_part(const std::string &rest, char user_passwd_separator, char user_host_separator) {
  //
  // let's see if there is some user info separated by a '@'
  //
  SplitResult tmp = split_first(host_, user_host_separator);
  if (tmp.success) {
    user_ = tmp.first;
    has_user_ = true;
    host_ = tmp.second;
    //
    // let's see if the user has a password...
    //
    tmp = split_first(user_, ':');
    if (tmp.success) {
      user_ = tmp.first;
      password_ = tmp.second;
      has_password_ = true;
    }
    tmp = split_first(host_, ':');
    if (tmp.success) {
      host_ = tmp.first;
      for (auto cc: tmp.second) {
        if (cc < '0' || cc > '9') throw Error(file_, __LINE__, "Port number is not numeric!");
      }
      port_ = std::atoi(tmp.second.c_str());
      has_port_ = true;
    }
  }
}

void AnyUri::parse(const std::string &strval) {
  abspath_ = false;
  std::string rest;

  std::cerr << "======================" << std::endl;
  //
  // first get the protocol if it's an absolute IRI with protocol etc.
  //
  auto tmp = split_first(strval, "://");
  if (tmp.success) {
    protocol_ = tmp.first;
    has_protocol_ = true;
    rest = tmp.second;
  } else {
    protocol_ = "";
    has_protocol_ = false;
    rest = tmp.first;
  }

  std::cerr << "REST=" << rest << std::endl;

  std::vector<std::string> parts;
  if (has_protocol_) {
    std::cerr << "PROTOCOL=" << protocol_ << std::endl;
    try {
      std::string schema = protocol_schemes.at(protocol_);
      parts = split(schema, '|');
    } catch (const std::out_of_range &err) {
      throw Error(file_, __LINE__, "URI-schema not supported");
    }
    if ((parts.size() % 2) != 0) throw Error(file_, __LINE__, "Internal error in URI schema data!");

    for (int i = 0; i < parts.size(); i += 2) {
      if (parts[i][0] == '?') {
        std::vector<std::string> splitters;
        for (int ii = i; ii < parts.size(); ii += 2) {
          if ((parts[ii][0] == '?') && (parts[ii + 1] != "\n")) splitters.push_back(parts[ii + 1]);
        }
        NextSeparator next_separator = next_sep_pos(rest, splitters);
        tmp = split_at(rest, next_separator.pos);
        std::cerr << "* 1 * splitters=" << std::endl;
        for (auto s: splitters) std::cerr << "   " << s << std::endl;
      } else {
        std::cerr << "* 2 * splitter=" << parts[i + 1] << std::endl;
        tmp = split_first(rest, parts[i + 1]);
      }

      if ((parts[i] == "host") || (parts[i] == "?host")) {
        // extracting the host part
        host_ = tmp.first;
        has_host_ = true;
        parse_host_part(host_);
        std::cerr << "host: " << host_ << std::endl;
        if (tmp.success || (parts[i + 1] == "\n")) rest = tmp.second;
      } else if ((parts[i] == "path") || (parts[i] == "?path")) {
        std::string tmp_path = tmp.first;
        has_path_ = true;
        path_ = split(tmp_path, '/');
        for (auto p: path_) std::cerr << "path: " << p << std::endl;
        if (tmp.success || (parts[i + 1] == "\n")) rest = tmp.second;
      } else if ((parts[i] == "fragment") || (parts[i] == "?fragment")) {
        fragment_ = tmp.first;
        has_fragment_ = true;
        rest = tmp.second;
        std::cerr << "fragment: " << fragment_ << std::endl;
      } else if ((parts[i] == "options") || (parts[i] == "?options")) {
        std::string tmp_options = tmp.first;
        has_options_ = true;
        options_ = split(tmp_options, '&');
        for (auto o: options_) std::cerr << "option: " << o << std::endl;
        if (tmp.success || (parts[i + 1] == "\n")) rest = tmp.second;
      }
      if (!tmp.success && (parts[i + 1] != "\n")) break;
    }
  } else {
    path_ = split(rest, "/");
    has_path_ = true;
  }
}


std::ostream &AnyUri::print_to_stream(std::ostream &out_stream) const {
  if (has_protocol_) out_stream << protocol_;
  if (has_host_) out_stream << "://" << host_;
  if (has_port_) out_stream << ":" << port_;
  if (has_path_) {
    int i = 0;
    for (const auto &p: path_) {
      if (i == 0) {
        if (abspath_ || has_protocol_) out_stream << "/";
        out_stream << p;
      } else {
        out_stream << "/" << p;
      }
      ++i;
    }
  }
  if (has_fragment_) {
    out_stream << "#" << fragment_;
  }
  if (has_options_) {
    int i = 0;
    for (const auto &o: options_) {
      out_stream << ((i == 0) ? "?" : "&") << o;
      ++i;
    }
  }
  return out_stream;
}

AnyUri::AnyUri(const std::string &strval) {
  xsd_type_ = "anyUri";
  has_protocol_ = false;
  has_port_ = false;
  has_host_ = false;
  has_path_ = false;
  abspath_ = false;
  has_fragment_ = false;
  has_options_ = false;
  port_ = -1;
  parse(strval);
}

AnyUri::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

}