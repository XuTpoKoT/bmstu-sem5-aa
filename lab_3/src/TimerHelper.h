#ifndef STUD_96_TIMERHELPER_H
#define STUD_96_TIMERHELPER_H

#include <functional>
#include "ArrUtils.h"

class TimerHelper {
private:
    std::vector<int> arr;

public:
    void init(int size) {
        arr = std::vector<int>(size);
        ArrUtils::fillRand(arr, 0, 1000);
    }

    void initAsc(int size) {
        arr = std::vector<int>(size);
        ArrUtils::fillAsc(arr);
    }

    void initDesc(int size) {
        arr = std::vector<int>(size);
        ArrUtils::fillDesc(arr);
    }

    void initForBalancedTree(int size) {
        arr = std::vector<int>(size);
        ArrUtils::fillForBalancedTree(arr);
    }

    void run(const std::function<void (std::vector<int> &arr)> f) {
        f(arr);
    }
};

#endif //STUD_96_TIMERHELPER_H

