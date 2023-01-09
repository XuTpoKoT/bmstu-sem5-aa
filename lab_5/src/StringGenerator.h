#pragma once

#include <string>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

class StringGenerator {
public:
    static std::string genString(std::size_t size) {
        auto randchar = []() -> char
        {
            const char charset[] =
            //"0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(size,0);
        std::generate_n( str.begin(), size, randchar );
        return str;
    }
};