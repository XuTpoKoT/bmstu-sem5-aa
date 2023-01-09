#ifndef STUD_96_TIMER_H
#define STUD_96_TIMER_H

#include <ctime>
#include <pthread.h>
#include <cstdio>
#include <array>
#include "Matrix.h"
#include "CSVWriter.h"
#include "TimerHelper.h"

class Timer {
private:
    TimerHelper timerHelper;
    CSVWriter ws{"../report/st.csv"};
    CSVWriter w0{"../report/v0.csv"};
    CSVWriter w1{"../report/v1.csv"};
    CSVWriter w2{"../report/v2.csv"};
    CSVWriter w3{"../report/v3.csv"};

    std::vector<int> sizes{100, 200, 300, 400, 500, 600, 700};

public:
    Timer() = default;

    void all() {
        w0 << "size" << "time" << endrow;
        w1 << "size" << "time" << endrow;
        w2 << "size" << "time" << endrow;
        w3 << "size" << "time" << endrow;
        ws << "size" << "time" << endrow;
        for (const auto& size: sizes) {
            timerHelper.init(size);
            standard(size);
            Vin0(size);
            Vin1(size);
            Vin2(size);
            Vin3(size);
        }
    }

private:
    void standard(int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(Matrix::mulStand);
        long long t2 = getThreadCpuTimeNs();
        ws << size << (t2 - t1) / 1000 << endrow;
        ws.flush();
    }

    void Vin0(int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(Matrix::mulVinograd0);
        long long t2 = getThreadCpuTimeNs();
        w0 << size << (t2 - t1) / 1000 << endrow;
        w0.flush();
    }

    void Vin1(int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(Matrix::mulVinograd1);
        long long t2 = getThreadCpuTimeNs();
        w1 << size << (t2 - t1) / 1000 << endrow;
        w1.flush();
    }

    void Vin2(int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(Matrix::mulVinograd2);
        long long t2 = getThreadCpuTimeNs();
        w2 << size << (t2 - t1) / 1000 << endrow;
        w2.flush();
    }

    void Vin3(int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(Matrix::mulVinograd3);
        long long t2 = getThreadCpuTimeNs();
        w3 << size << (t2 - t1) / 1000 << endrow;
        w3.flush();
    }

    long long getThreadCpuTimeNs() {
        struct timespec t;
        if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
            perror("clock_gettime");
            return 0;
        }
        return t.tv_sec * 1000000000LL + t.tv_nsec;
    }
};

#endif //STUD_96_TIMER_H
