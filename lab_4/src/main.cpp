#include <stdio.h>
#include <iostream>
#include <memory>

#include "ParallelDBScan.h"

#define MIN_POINTS_IN_CLUSTER 3
#define EPSILON 3.5

int readTestData(vector<shared_ptr<Point>> &points, vector<int> &clusterIndexes) {
    FILE *stream = fopen("test1.txt","r");
    if (stream == NULL) {
        return -1;
    }

    size_t cntPoints;
    if (fscanf(stream, "%zu\n", &cntPoints) != 1) {
        fclose(stream);
        return -1;
    }

    int clusterIndex;
    for (size_t i = 0; i < cntPoints; i++) {
        auto p = make_shared<Point>(); 
        if (fscanf(stream, "%lf%lf%d\n", &(p->x), &(p->y), &clusterIndex) != 3) {
            fclose(stream);
            return -1;
        }
        p->clusterID = UNVISITED;
        points.push_back(p);
        clusterIndexes.push_back(clusterIndex);
    }

    fclose(stream);
    return 0;
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
    // if (readTestData(points, clusterIndexes)) {
    //     printf("read test data failed");
    //     return -1;
    // }
    //printResults(points);
    if (readPoints("data1.txt", points)) {
        printf("read data failed\n");
        return -1;
    }
    // for (auto p : points) {
    //     p->print();
    // }
    ParallelDBScan ds(points, MIN_POINTS_IN_CLUSTER, EPSILON, threadCnt);
    ds.run();

    //printResults(ds.points, ds.clusterIndexes);
    printf("\nEeend!\n");

    return 0;
}
