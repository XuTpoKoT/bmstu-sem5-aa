#include <iostream>
#include <limits>
#include <memory>

#include "Timer.h"
#include "TestArrUtils.h"

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    setbuf(stdout, NULL);
    Timer timer;

    timer.all();

    return 0;
}
