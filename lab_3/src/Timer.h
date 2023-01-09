#ifndef STUD_96_TIMER_H
#define STUD_96_TIMER_H

#include <ctime>
#include <pthread.h>
#include <cstdio>
#include <array>

#include "ArrUtils.h"
#include "CSVWriter.h"
#include "TimerHelper.h"

class Timer {
private:
    TimerHelper timerHelper;
    CSVWriter wShaker1{"../report/sh1.csv"};
    CSVWriter wShaker2{"../report/sh2.csv"};
    CSVWriter wShaker3{"../report/sh3.csv"};
    CSVWriter wGnome1{"../report/gn1.csv"};
    CSVWriter wGnome2{"../report/gn2.csv"};
    CSVWriter wGnome3{"../report/gn3.csv"};
    CSVWriter wTree1{"../report/tree1.csv"};
    CSVWriter wTree2{"../report/tree2.csv"};
    CSVWriter wTree3{"../report/tree3.csv"};

    std::vector<int> sizes{100, 300, 1000, 2500};

public:
    Timer() = default;

    void all() {
        writeCSVHeaders();

        for (const auto& size: sizes) {
            timerHelper.init(size);
            shaker(wShaker1, size);
            timerHelper.init(size);
            gnome(wGnome1, size);
            timerHelper.init(size);
            tree(wTree1, size);

            timerHelper.initAsc(size);
            shaker(wShaker2, size);
            timerHelper.initAsc(size);
            gnome(wGnome2, size);
            timerHelper.initForBalancedTree(size);
            tree(wTree2, size);

            timerHelper.initDesc(size);
            shaker(wShaker3, size);
            timerHelper.initDesc(size);
            gnome(wGnome3, size);
            timerHelper.initAsc(size);
            tree(wTree3, size);
        }
    }

private:
    void writeCSVHeaders() {
        wShaker1 << "size" << "time" << endrow;
        wShaker2 << "size" << "time" << endrow;
        wShaker3 << "size" << "time" << endrow;
        wGnome1  << "size" << "time" << endrow;
        wGnome2  << "size" << "time" << endrow;
        wGnome3  << "size" << "time" << endrow;
        wTree1   << "size" << "time" << endrow;
        wTree2   << "size" << "time" << endrow;
        wTree3   << "size" << "time" << endrow;
    }

    void shaker(CSVWriter &w, int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(ArrUtils::shakerSort);
        long long t2 = getThreadCpuTimeNs();
        w << size << (t2 - t1) / 1000 << endrow;
        w.flush();
    }

    void gnome(CSVWriter &w, int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(ArrUtils::gnomeSort);
        long long t2 = getThreadCpuTimeNs();
        w << size << (t2 - t1) / 1000 << endrow;
        w.flush();
    }

    void tree(CSVWriter &w, int size) {
        long long t1 = getThreadCpuTimeNs();
        timerHelper.run(ArrUtils::treeSort);
        long long t2 = getThreadCpuTimeNs();
        w << size << (t2 - t1) / 1000 << endrow;
        w.flush();
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
