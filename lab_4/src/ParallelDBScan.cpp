#include "ParallelDBScan.h"

#include <algorithm>

int ParallelDBScan::run() {
    makeStrips();

    return 0;
}

bool ParallelDBScan::cmpX(int p1, int p2) {
    return points[p1]->x < points[p2]->x;
}

void ParallelDBScan::makeStrips() {
    strips.clear();
    sort(points.begin(), points.end(), Point::cmpX);
    double minX = points[0]->x;
    int curStripId = 0;
    for (auto p : points) {
        if (p->x >= minX + curStripId * eps) {
            curStripId++;
            strips.push_back({});
        }
        strips.back().points.push_back(p);
    }

    // FILE *f = fopen("log.txt","w");
    // for (size_t i = 0; i < strips.size(); i++) {
    //     fprintf(f, "Strip %zu\n", i);
    //     for (auto p : strips[i].points) {
    //         fprintf(f, "%lf\n", p->x);
    //     }
    // }
    // fclose(f);
}