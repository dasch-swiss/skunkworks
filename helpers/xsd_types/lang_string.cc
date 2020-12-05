//
// Created by Lukas Rosenthaler on 27.11.20.
//
#include <stdexcept>

#include "lang_string.h"

namespace xsd {

    LangString::LangString(Language lang, const std::string text) {
        lang_string_[lang] = text;
    }

//    std::string LangString::operator[](Language lang) {
//        std::string result;
//        try {
//            result = lang_string_.at(lang);
//        } catch (const std::out_of_range &err) {
//            if (lang_string_.empty()) return result; //empty string!
//            for (auto s: lang_string_.) { // return first available string...
//                return s;
//            }
//        }
//    }

    void LangString::remove(Language lang) {
        lang_string_.erase(lang);
    }
}