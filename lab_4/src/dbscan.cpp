#include "dbscan.h"

#include <algorithm>

double Point::dist(const std::shared_ptr<Point> p) {
    return sqrt(pow(x - p->x, 2) + pow(y - p->y, 2) + pow(z - p->z, 2));
}

int DBSCAN::run() {
    int nextClusterID = 0;
    std::size_t size = points.size();
    for(std::size_t i = 0; i < size; i++) {
        if (clusterIndexes[i] == UNVISITED) {
            if (expandCluster(i, nextClusterID) != -1) {
                nextClusterID++;
            }
        }
    }

    return 0;
}

int DBSCAN::expandCluster(int curPointIndex, int curClusterID) {
    std::vector<int> seeds = getNeighbors(points.at(curPointIndex));

    printf("ID = %d; neighbors: ", curClusterID);
    for (std::size_t i = 0; i < seeds.size(); i++) {
        printf("%d ", seeds[i]);
    }
    printf("\n");

    if (seeds.size() + 1 < minPointsInCluster) {
        clusterIndexes[curPointIndex] = NOISE;
        return -1;
    }
    clusterIndexes[curPointIndex] = curClusterID;
    for (std::size_t i = 0, cntSeeds = seeds.size(); i < cntSeeds; ++i) {
        clusterIndexes[seeds[i]] = curClusterID;
    }

    while (seeds.size() > 0) {
        int curSeed = seeds.back();
        std::vector<int> seedNeighbors = getNeighbors(points.at(curSeed));

        printf("    Inner neighbors: ");
        for (std::size_t i = 0; i < seedNeighbors.size(); i++) {
            printf("%d ", seedNeighbors[i]);
        }
        printf("\n");

        std::size_t cntNeighbors = seedNeighbors.size();
        if (cntNeighbors + 1 >= minPointsInCluster) {
            for (std::size_t i = 0; i < cntNeighbors; ++i) {
                int curNeighbor = seedNeighbors[i];
                if (clusterIndexes[curNeighbor] == UNVISITED || clusterIndexes[curNeighbor] == NOISE) {
                    if (clusterIndexes[curNeighbor] == NOISE) {
                        seeds.push_back(curNeighbor);    
                    }
                    clusterIndexes[curNeighbor] = curClusterID;
                }
            }
        }
        seeds.erase(std::remove(seeds.begin(), seeds.end(), curSeed), seeds.end());
    }

    return 0;
}

std::vector<int> DBSCAN::getNeighbors(const std::shared_ptr<Point> point) {
    std::vector<int> clusterIndexes;
    for (std::size_t i = 0, n = points.size(); i < n; i++) {
        double distance = point->dist(points[i]);
        if (distance <= eps && distance >= 1e-8) {
            clusterIndexes.push_back(i);
        }
    }

    return clusterIndexes;
}

int DBSCAN::runParallel() {
    int nextClusterID = 0;
    std::size_t size = points.size();
    for(std::size_t i = 0; i < size; i++) {
        if (clusterIndexes[i] == UNVISITED) {
            if (expandCluster(i, nextClusterID) != -1) {
                nextClusterID++;
            }
        }
    }

    return 0;
}

int DBSCAN::expandClusterParallel(int curPointIndex, int curClusterID) {
    std::vector<int> seeds = getNeighbors(points.at(curPointIndex));

    if (seeds.size() + 1 < minPointsInCluster) {
        clusterIndexes[curPointIndex] = NOISE;
        return -1;
    }
    clusterIndexes[curPointIndex] = curClusterID;
    for (std::size_t i = 0, cntSeeds = seeds.size(); i < cntSeeds; ++i) {
        clusterIndexes[seeds[i]] = curClusterID;
    }

    while (seeds.size() > 0) {
        int curSeed = seeds.back();
        std::vector<int> seedNeighbors = getNeighbors(points.at(curSeed));
        std::size_t cntNeighbors = seedNeighbors.size();
        if (cntNeighbors + 1 >= minPointsInCluster) {
            for (std::size_t i = 0; i < cntNeighbors; ++i) {
                int curNeighbor = seedNeighbors[i];
                if (clusterIndexes[curNeighbor] == UNVISITED || clusterIndexes[curNeighbor] == NOISE) {
                    if (clusterIndexes[curNeighbor] == NOISE) {
                        seeds.push_back(curNeighbor);    
                    }
                    clusterIndexes[curNeighbor] = curClusterID;
                }
            }
        }
        seeds.erase(std::remove(seeds.begin(), seeds.end(), curSeed), seeds.end());
    }

    return 0;
}



