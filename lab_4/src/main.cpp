#include <stdio.h>
#include <iostream>
#include <memory>

#include "dbscan.h"

#define MIN_POINTS_IN_CLUSTER 3
#define EPSILON 3.5

int readTestData(std::vector<std::shared_ptr<Point>> &points, std::vector<int> &clusterIndexes) {
    FILE *stream = fopen("test1.txt","r");
    if (stream == NULL) {
        return -1;
    }

    std::size_t cntPoints;
    if (fscanf(stream, "%zu\n", &cntPoints) != 1) {
        fclose(stream);
    }

    int clusterIndex;
    for (std::size_t i = 0; i < cntPoints; i++) {
        auto p = std::make_shared<Point>(); 
        if (fscanf(stream, "%lf%lf%d\n", &(p->x), &(p->y), &clusterIndex) != 3) {
            fclose(stream);
            return -1;
        }
        p->clusterID = UNVISITED;
        p->z = 0.0;
        points.push_back(p);
        clusterIndexes.push_back(clusterIndex);
    }

    fclose(stream);
    return 0;
}

void printResults(const std::vector<std::shared_ptr<Point>>& points, const std::vector<int> &indexes) {
    std::size_t cntPoints = points.size(); 
    printf("Number of points: %zu\n"
        " x     y     z     cluster_id\n"
        "-----------------------------\n"
        , cntPoints);
    for (std::size_t i = 0; i < cntPoints; i++) {
        printf("%5.2lf %5.2lf %5.2lf: %d\n",
                points[i]->x,
                points[i]->y, 
                points[i]->z,
                indexes[i]);
    }
}

int main() {
    std::vector<std::shared_ptr<Point>> points;
    std::vector<int> clusterIndexes;
    if (readTestData(points, clusterIndexes)) {
        printf("read test data failed");
        return -1;
    }
    //printResults(points);
    DBSCAN ds(points, MIN_POINTS_IN_CLUSTER, EPSILON);
    ds.run();

    printResults(ds.points, ds.clusterIndexes);
    printf("\nEeend!\n");

    return 0;
}
