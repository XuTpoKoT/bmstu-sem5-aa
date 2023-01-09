#ifndef STUD_96_TIMERHELPER_H
#define STUD_96_TIMERHELPER_H

#include <functional>
#include "Matrix.h"

class TimerHelper {
private:
    Matrix m1, m2, res;

public:
    void init(int size) {
        m1 = Matrix(size, size);
        m1.fillRand(0, 1000);
        m2 = Matrix(size, size);
        m2.fillRand(0, 1000);
        res = Matrix(size, size);
    }

    void run(const std::function<void (const Matrix&, const Matrix&, Matrix&)> f) {
        f(m1, m2, res);
    }
};

#endif //STUD_96_TIMERHELPER_H

