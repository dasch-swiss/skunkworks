#include <string>
#include <regex>
#include <iostream>
#include <locale>
#include <codecvt>


std::wstring s2ws(const std::string& str)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.to_bytes(wstr);
}

int main() {
  std::locale old = std::locale::global(std::locale("en_US.UTF-8"));
  
  //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter;

  std::wstring gaga = s2ws("ab:äöüцудовнымъ");
  std::wstring pattern = s2ws("^([\\w]+)(:)([\\w]+)$");
  std::wsmatch sm;
  std::cerr << "2) ---------------" << std::endl;
  if (std::regex_match(gaga, sm, std::wregex(pattern))) {
    std::cerr << "match!" << std::endl;
    for (auto &m: sm) {
      std::string hihi = ws2s(m);
      std::cerr << "-->" << hihi << std::endl;
    }
  } else {
    std::cerr << "no match!" << std::endl;
  }
}
