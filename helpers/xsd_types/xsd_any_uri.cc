//
// Created by Lukas Rosenthaler on 01.12.20.
//

#include <string>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include <regex>

#include "xsd_error.h"
#include "xsd_any_uri.h"

static const char file_[] = __FILE__;

namespace xsd {

std::unordered_map<std::string, std::string> AnyUri::protocol_schemes = {
    {"ark", "(ark:)/?([\\d]{5})/(.*)"},
    {"doi", "(doi:)(\\d{2}.\\d{4})/(.*)"},
    {"file", "(file://|file:)([^:]+:)?([^@]+@)?([^/]+)?(/.*)?"},
    {"geo", "(geo:)([\\d]*\\.[\\d]*),([\\d]*\\.[\\d]*)(;u=[\\d]+)?"},
    {"git", "(git://)([^:]+:)?([^@]+@)?([^/]+[/])?(.*)?"},
    {"http", R"((http://)([\w]+:)?([\w]+@)?([\w\.]+)(:[0-9]{1,6})?([\w/\.]+)?(#[\w]*)?(\?[\w&=]+)?(.*)?)"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"https", R"((https://)([\w]+:)?([\w]+@)?([\w\.]+)(:[0-9]{1,6})?([\w/\.]+)?(#[\w]*)?(\?[\w&=]+)?(.*)?)"}, // [user[:password]@]host[:port][/path][#fragment][?key=[val][&key[=val]]
    {"mailto", "(mailto:)([^@]+@)([^\?]+\?)(.*)?"},
    {"s3", "(s3://)([^/]+/)(.*)"},
    {"urn", "protocol||path:|\n"},
    {"ws", "(ws://)([^:]+:)?([^@]+@)?([^/]+/)?(.*)?"},
    {"wss", "(wss://)([^:]+:)?([^@]+@)?([^/]+/)?(.*)?"},
    {"xri", "(xri://)([^/]+/)(.*)"},

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


void AnyUri::parse_host_part(const std::string &rest, char user_passwd_separator, char user_host_separator) {
  //
  // let's see if there is some user info separated by a '@'
  //
  SplitResult tmp = split_first(rest, user_host_separator);
  if (tmp.success) {
    user_ = tmp.first;
    has_user_ = true;
    host_ = tmp.second;
    has_host_ = true;
    //
    // let's see if the user has a password...
    //
    if (!user_.empty()) {
      tmp = split_first(user_, user_passwd_separator);
      if (tmp.success) {
        user_ = tmp.first;
        password_ = tmp.second;
        if (!password_.empty()) has_password_ = true;
      }
    }
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

void dellast( std::string &str, char last) {
  if (str[str.length() - 1] == last) {
    str.pop_back();
  } else {
    throw Error(file_, __LINE__, "Expected different separator!");
  }
}

void AnyUri::parse(const std::string &strval) {
  std::locale old;
  std::locale::global(std::locale("en_US.UTF-8"));

  size_t pos = strval.find(':');
  if (pos != std::string::npos) {
    protocol_ = strval.substr(0, pos);
    has_protocol_ = true;
    std::string pattern = protocol_schemes.at(protocol_);
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

std::ostream &AnyUri::print_to_stream(std::ostream &out_stream) const {
  if (has_protocol_) std::cerr << "protocol=\"" << protocol_ << "\"" << std::endl;
  if (has_user_) std::cerr << "user=\"" << user_ << "\"" << std::endl;
  if (has_password_) std::cerr << "password=\"" << password_ << "\"" << std::endl;
  if (has_host_) std::cerr << "host=\"" << host_ << "\"" << std::endl;
  if (has_port_) std::cerr << "port=\"" << port_ << "\"" << std::endl;
  if (has_path_) {
    std::cerr << "path:" << std::endl;
    for (auto p: path_) std::cerr << "  " << p << std::endl;
  }
  if (has_fragment_) std::cerr << "fragment=\"" << fragment_ << "\"" << std::endl;
  if (has_options_) {
    std::cerr << "options:" << std::endl;
    for (auto o: options_) std::cerr << "  " << o << std::endl;
  }


  if (has_protocol_) {
    if (protocol_ == "http") out_stream << "http://";
    if (protocol_ == "https") out_stream << "https://";
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
        if (has_host_) out_stream << "/";
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
  if (has_host_ && check_illegal_characters(host_, " ,;?^+*%&/()=!$<>")) {
    std::cerr << "Illegal character in hostname: " + host_ + "!" << std::endl;
    throw Error(file_, __LINE__, "Illegal character in hostname: " + host_ + "!");
  }
  if (has_path_) {
    for (auto p: path_) {
      if (check_illegal_characters(p, " <>?")) {
        std::cerr << "Illegal character in path component: " + p + "!" << std::endl;
        throw Error(file_, __LINE__, "Illegal character in path component: " + p + "!");
      }
    }
  }
}

AnyUri::AnyUri(const std::string &protocol, const std::string &host, const std::string &path) : protocol_(protocol) {
  has_protocol_ = true;
  parse_host_part(host, ':', '@');
  path_ = split(path, '/');
  has_path_ = true;
  path_sep_ = "/";
}

AnyUri::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

}