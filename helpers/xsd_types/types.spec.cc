//
// Created by Lukas Rosenthaler on 26.11.20.
//

// c++ -stdlib=libc++ -std=c++17 -o types.spec date_time.cc  error.cc types.spec.cc -lc

#include <string>
#include <iostream>

#include "error.h"
#include "date_time.h"

int main(int argc, char *argv[]) {

    xsd::DateTime t1;
    std::cerr << t1 << std::endl;

    try {
        t1 = xsd::DateTime("2001-10-26T19:32:52+00:00");
        std::cerr << t1 << std::endl;
    } catch (const xsd::Error &err) {
        std::cerr << err << std::endl;
    }

    try {
        t1 = xsd::DateTime("2001-10-26T19:32:52.3456+00:00");
        std::cerr << t1 << std::endl;
    } catch (const xsd::Error &err) {
        std::cerr << err << std::endl;
    }

    try {
        t1 = xsd::DateTime("2001-10-26X19:32:52+00:00");
        std::cerr << t1 << std::endl;
    } catch (const xsd::Error &err) {
        std::cerr << err << std::endl;
    }

    try {
        t1 = xsd::DateTime(2000, 2, 10, 12, 0, 33, -1, 0);
        std::cerr << t1 << std::endl;
    } catch (const xsd::Error &err) {
        std::cerr << err << std::endl;
    }

    try {
        t1 = xsd::DateTime(2001, 2, 29, 12, 0, 33, 3, 0);
        std::cerr << t1 << std::endl;
    } catch (const xsd::Error &err) {
        std::cerr << err << std::endl;
    }


    return 0;
}


