#ifndef STUD_96_TESTARRUTILS_H
#define STUD_96_TESTARRUTILS_H

#include <bits/stdc++.h>

#include "ArrUtils.h"

class TestArrUtils {
public:
    static void all() {
        testShakerSort();
        testGnomeSort();
        testTreeSort();
    }
    static bool testShakerSort() {
        std::vector<int> arr(30);
        ArrUtils::fillRand(arr, 0, 1000);
        auto res = arr;
        sort(res.begin(), res.end());

        ArrUtils::shakerSort(arr);

        std::cout << ArrUtils::equals(arr, res) << "\n";
        return true;
    }

    static bool testGnomeSort() {
        std::vector<int> arr(30);
        ArrUtils::fillRand(arr, 0, 1000);
        auto res = arr;
        sort(res.begin(), res.end());

        ArrUtils::gnomeSort(arr);

        std::cout << ArrUtils::equals(arr, res) << "\n";
        return true;
    }

    static bool testTreeSort() {
        std::vector<int> sizes{10, 100, 300, 1000};
        for (const auto& size: sizes) {
            std::vector<int> arr(size);
            ArrUtils::fillRand(arr, 0, 1000);
            auto res = arr;
            sort(res.begin(), res.end());

            ArrUtils::treeSort(arr);
            std::cout << ArrUtils::equals(arr, res) << "\n";
        }

        return true;
    }
};

#endif //STUD_96_TESTARRUTILS_H
