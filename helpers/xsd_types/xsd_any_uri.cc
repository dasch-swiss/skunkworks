//
// Created by Lukas Rosenthaler on 01.12.20.
//

#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include <regex>
#include <sstream>

#include "xsd_error.h"
#include "xsd_any_uri.h"

static const char file_[] = __FILE__;

namespace xsd {

std::unordered_map<std::string, std::string> AnyUri::protocol_schemes = {
    {"ark", R"((ark:)/?([\d]{5})/(.*))"},
    {"doi", R"((doi:)(\d{2}.\d{4})/(.*))"},
    {"file", R"((file://|file:)([\w]+:)?([\w]+@)?([\w\.]+)?([\w/\-\.]+)?)"},
    {"geo", R"((geo:)([\d]*\.[\d]*),([\d]*\\.[\d]*)(;u=[\d]+)?)"},
    {"git", R"((git://)([\w\.]+)([\w/\-\.]+)?)"},
    {"http", R"((http://)([\w]+:)?([\w]+@)?([\w\.]+)(:[0-9]{1,6})?([\w/\-\.]+)?(#[\w]*)?(\?[\w&=]+)?(.*)?)"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"https", R"((https://)([\w]+:)?([\w]+@)?([\w\.]+)(:[0-9]{1,6})?([\w/\-\.]+)?(#[\w]*)?(\?[\w&=]+)?(.*)?)"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"mailto", "(mailto:)([^@]+@)([^\?]+\?)(.*)?"},
    {"s3", R"((s3://)([a-z0-9\-]{3,63})/([\w/\-\.\*\(\)!']+)?)"},
    {"urn", R"((urn:)([\w]+):(.*))"},
    {"ws", R"((ws://)([\w\.]+)(:[0-9]{1,6})?([\w/\-\.]+)?(\?[\w&=]+)?(.*)?)"},
    {"wss", R"((wss://)([\w\.]+)(:[0-9]{1,6})?([\w/\-\.]+)?(\?[\w&=]+)?(.*)?)"},
};

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

static bool check_illegal_characters(const std::string  &strval, const std::string &illegal) {
  for (auto const c: illegal) {
    if (strval.find(c) != std::string ::npos) return true;
  }
  return false;
}

void dellast( std::string &str, char last) {
  if (str[str.length() - 1] == last) {
    str.pop_back();
  } else {
    throw Error(file_, __LINE__, "Expected different separator!");
  }
}

void AnyUri::parse(const std::string &strval) {
  std::locale old = std::locale::global(std::locale("en_US.UTF-8"));

  size_t pos = strval.find(':');
  if (pos != std::string::npos) {
    protocol_ = strval.substr(0, pos);
    has_protocol_ = true;
    std::string pattern;
    try {
      pattern = protocol_schemes.at(protocol_);
    } catch (const std::out_of_range &err) {
      throw Error(file_, __LINE__, "Unknown protocol!");
    }
    std::regex re(pattern, std::regex::ECMAScript);
    std::cmatch match;
    if (std::regex_match(strval.c_str(), match, re)) {
      if ((protocol_ == "http") || (protocol_ == "https")) {
        if (match[2].matched && match[3].matched) {
          user_ = match[2].str();
          dellast(user_, ':');
          has_user_ = true;
          password_ = match[2].str();
          dellast(password_, '@');
          has_password_ = true;
        } else if (match[3].matched) {
          user_ = match[2].str();
          dellast(user_, '@');
          has_user_ = true;
        }

        if (match[4].matched) {
          has_host_ = true;
          host_ = match[4].str();
        }
        if (match[5].matched) {
          has_port_ = true;
          std::string port = match[5].str();
          port.erase(0, 1);
          port_ = std::atoi(port.c_str());
        }
        if (match[6].matched) {
          has_path_ = true;
          std::string path = match[6].str();
          path = path.erase(0, 1);
          path_ = split(path, '/');
          path_sep_ = '/';
        }
        if (match[7].matched) {
          has_fragment_ = true;
          fragment_ = match[7].str();
          fragment_.erase(0, 1);
        }
        if (match[8].matched) {
          has_options_ = true;
          std::string options = match[8].str();
          options.erase(0, 1);
          options_ = split(options, '?');
        }
      } else if (protocol_ == "doi") {
        if (match[2].matched) {
          host_ = match[2].str();
          has_host_ = true;
        }
        if (match[3].matched) {
          path_.push_back(match[3].str());
          has_path_ = true;
          path_sep_ = '/';
        }
      } else if (protocol_ == "git") {
        if (match[2].matched) {
          host_ = match[2].str();
          has_host_ = true;
        }
        if (match[3].matched) {
          has_path_ = true;
          std::string path = match[3].str();
          path = path.erase(0, 1);
          path_ = split(path, '/');
          path_sep_ = '/';
        }
      } else if (protocol_ == "ark") {
        if (match[2].matched) {
          host_ = match[2].str();
          has_host_ = true;
        }
        if (match[3].matched) {
          path_.push_back(match[3].str());
          has_path_ = true;
          path_sep_ = '/';
        }
      } else if (protocol_ == "s3") {
        if (match[2].matched) {
          host_ = match[2].str();
          has_host_ = true;
        }
        if (match[3].matched) {
          path_.push_back(match[3].str());
          has_path_ = true;
          path_sep_ = '/';
        }
      } else if (protocol_ == "urn") {
        if (match[2].matched) {
          host_ = match[2].str();
          has_host_ = true;
        }
        if (match[3].matched) {
          path_.push_back(match[3].str());
          has_path_ = true;
          path_sep_ = ':';
        }
      } else if ((protocol_ == "ws") || (protocol_ == "wss")) {
        if (match[2].matched) {
          has_host_ = true;
          host_ = match[2].str();
        }
        if (match[3].matched) {
          has_port_ = true;
          std::string port = match[3].str();
          port.erase(0, 1);
          port_ = std::atoi(port.c_str());
        }
        if (match[4].matched) {
          has_path_ = true;
          std::string path = match[4].str();
          path = path.erase(0, 1);
          path_ = split(path, '/');
          path_sep_ = '/';
        }
        if (match[5].matched) {
          has_options_ = true;
          std::string options = match[5].str();
          options.erase(0, 1);
          options_ = split(options, '?');
        }
      } else if (protocol_ == "file") {
        if (match[2].matched && match[3].matched) {
          user_ = match[2].str();
          dellast(user_, ':');
          has_user_ = true;
          password_ = match[2].str();
          dellast(password_, '@');
          has_password_ = true;
        } else if (match[3].matched) {
          user_ = match[2].str();
          dellast(user_, '@');
          has_user_ = true;
        }

        if (match[4].matched) {
          has_host_ = true;
          host_ = match[4].str();
        }
        if (match[5].matched) {
          has_path_ = true;
          std::string path = match[5].str();
          path = path.erase(0, 1);
          path_ = split(path, '/');
          path_sep_ = '/';
        }
      }
    } else {
      throw Error(file_, __LINE__, "anyIR does not match any pattern!");
    }
  } else {
    protocol_ = "";
    has_protocol_ = false;
    path_ = split(strval, '/');
    has_path_ = true;
    path_sep_ = '/';
  }

  std::locale::global(old);
}

void AnyUri::validate() {
  if (has_host_ && check_illegal_characters(host_, " ,;?^+*%&/()=!$<>")) {
    throw Error(file_, __LINE__, "Illegal character in hostname: " + host_ + "!");
  }
  if (has_path_) {
    for (auto p: path_) {
      if (check_illegal_characters(p, " <>?")) {
        throw Error(file_, __LINE__, "Illegal character in path component: " + p + "!");
      }
    }
  }

}

std::ostream &AnyUri::print_to_stream(std::ostream &out_stream) const {
  if (has_protocol_) {
    if (protocol_ == "http") out_stream << "http://";
    if (protocol_ == "https") out_stream << "https://";
    if (protocol_ == "doi") out_stream << "doi:";
    if (protocol_ == "git") out_stream << "git://";
    if (protocol_ == "ark") out_stream << "ark:/";
    if (protocol_ == "s3") out_stream << "s3://";
    if (protocol_ == "urn") out_stream << "urn:";
    if (protocol_ == "ws") out_stream << "ws://";
    if (protocol_ == "wss") out_stream << "wss://";
    if (protocol_ == "file") out_stream << ((has_host_) ? "file://" : "file:");
  }
  if (has_user_) out_stream << user_;
  if (has_password_) out_stream << ':' << password_;
  if (has_user_) out_stream << '@';
  if (has_host_) out_stream << host_;
  if (has_port_) out_stream << ':' << port_;
  if (has_path_) {
    int i = 0;
    for (const auto &p: path_) {
      if (i == 0) {
        if (has_host_) out_stream << path_sep_;
        out_stream << p;
      } else {
        out_stream << path_sep_ << p;
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
  has_password_ = false;
  has_user_ = false;
  has_port_ = false;
  has_host_ = false;
  has_path_ = false;
  has_fragment_ = false;
  has_options_ = false;
  port_ = -1;
  parse(strval);
  validate();
}

AnyUri::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

void AnyUri::set(const std::string &strval) {
  parse(strval);
  validate();
}


}