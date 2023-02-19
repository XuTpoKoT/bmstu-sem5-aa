#include <stdio.h>
#include <iostream>
#include <memory>

#include "DBScan.h"

#define MIN_POINTS_IN_CLUSTER 3
#define EPSILON 10

long long getThreadCpuTimeNs() {
        struct timespec t;
        if (clock_gettime(CLOCK_REALTIME, &t)) {
            perror("clock_gettime");
            return 0;
        }
        return t.tv_sec * 1000000000LL + t.tv_nsec;
}

void printResults(const vector<shared_ptr<Point>>& points, const vector<int> &indexes) {
    size_t cntPoints = points.size(); 
    printf("Number of points: %zu\n"
        " x     y     z     cluster_id\n"
        "-----------------------------\n"
        , cntPoints);
    for (size_t i = 0; i < cntPoints; i++) {
        printf("%5.2lf %5.2lf: %d\n",
                points[i]->x,
                points[i]->y, 
                indexes[i]);
    }
}

int readPoints(const char *filename, vector<shared_ptr<Point>> &points) {
    FILE *f = fopen(filename,"r");
    if (f == NULL) {
        return -1;
    }

    size_t cntPoints;
    if (fscanf(f, "%zu\n", &cntPoints) != 1) {
        fclose(f);
        return -1;
    }

    for (size_t i = 0; i < cntPoints; i++) {
        auto p = make_shared<Point>();
        if (fscanf(f, "%lf,%lf\n", &(p->x), &(p->y)) != 2) {
            fclose(f);
            return -1;
        }
        points.push_back(p);
    }

    fclose(f);
    return 0;
}

int main() {
    vector<shared_ptr<Point>> points;
    vector<int> clusterIndexes;
    int threadCnt = 2;

    if (readPoints("data2.txt", points)) {
        printf("read data failed\n");
        return -1;
    }

    DBScan ds(points, MIN_POINTS_IN_CLUSTER, EPSILON, threadCnt);
    auto t1 = getThreadCpuTimeNs();
    ds.run();
    auto t2 = getThreadCpuTimeNs();
    printf("%lld \n", (t2 - t1) / 1000);

    FILE *f = fopen("clusters.txt","w");
    for (size_t i = 0; i < ds.clusterIndexes.size(); i++) {
        fprintf(f, "%.2lf %.2lf %d\n", points[i]->x, points[i]->y, ds.clusterIndexes[i]);
    }
    fclose(f);

    printf("\nEeend!\n");
    return 0;
}
