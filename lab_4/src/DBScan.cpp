#include "DBScan.h"

#include <algorithm>

int DBScan::run() {
    curClusterID = 0;
    for (size_t i = 0, n = points.size(); i < n; i++) {
        if (clusterIndexes[i] == UNVISITED) {
            curPointIndex = i;
            if (expandCluster() != -1) {
                curClusterID++;
            }
        }
    }

    return 0;
}

int DBScan::runP() {
    curClusterID = 0;
    for (size_t i = 0, n = points.size(); i < n; i++) {
        if (clusterIndexes[i] == UNVISITED) {
            curPointIndex = i;
            if (expandClusterP() != -1) {
                curClusterID++;
            }
        }
    }

    return 0;
}

int DBScan::expandCluster() {
    vector<int> seeds = getNeighbors(points.at(curPointIndex));

    if (seeds.size() + 1 < minPointsInCluster) {
        clusterIndexes[curPointIndex] = NOISE;
        return -1;
    }
    clusterIndexes[curPointIndex] = curClusterID;
    for (size_t i = 0, cntSeeds = seeds.size(); i < cntSeeds; ++i) {
        clusterIndexes[seeds[i]] = curClusterID;
    }

    while (seeds.size() > 0) {
        int curSeed = seeds.back();
        seeds.pop_back();
        vector<int> seedNeighbors = getNeighbors(points.at(curSeed));

        size_t cntNeighbors = seedNeighbors.size();
        if (cntNeighbors + 1 >= minPointsInCluster) {
            for (size_t i = 0; i < cntNeighbors; ++i) {
                int curNeighbor = seedNeighbors[i];
                if (clusterIndexes[curNeighbor] == UNVISITED || clusterIndexes[curNeighbor] == NOISE) {
                    if (clusterIndexes[curNeighbor] == NOISE) {
                        seeds.push_back(curNeighbor);
                    }
                    clusterIndexes[curNeighbor] = curClusterID;
                }
            }
        }
    }

    return 0;
}

int DBScan::expandClusterP() {
    // printf("ExpandCL\n");
    vector<int> seeds = getNeighborsP(points.at(curPointIndex));

    // printf("ID = %d; neighbors: ", curClusterID);
    // for (size_t i = 0; i < seeds.size(); i++) {
    //     printf("%d ", seeds[i]);
    // }
    // printf("\n");

    if (seeds.size() + 1 < minPointsInCluster) {
        clusterIndexes[curPointIndex] = NOISE;
        return -1;
    }
    clusterIndexes[curPointIndex] = curClusterID;
    for (size_t i = 0, cntSeeds = seeds.size(); i < cntSeeds; ++i) {
        clusterIndexes[seeds[i]] = curClusterID;
    }

    while (seeds.size() > 0) {
        int curSeed = seeds.back();
        seeds.pop_back();
        vector<int> seedNeighbors = getNeighborsP(points.at(curSeed));

        // printf("    Inner neighbors: ");
        // for (size_t i = 0; i < seedNeighbors.size(); i++) {
        //     printf("%d ", seedNeighbors[i]);
        // }
        // printf("\n");

        size_t cntNeighbors = seedNeighbors.size();
        if (cntNeighbors + 1 >= minPointsInCluster) {
            for (size_t i = 0; i < cntNeighbors; ++i) {
                int curNeighbor = seedNeighbors[i];
                if (clusterIndexes[curNeighbor] == UNVISITED || clusterIndexes[curNeighbor] == NOISE) {
                    if (clusterIndexes[curNeighbor] == NOISE) {
                        seeds.push_back(curNeighbor);    
                    }
                    clusterIndexes[curNeighbor] = curClusterID;
                }
            }
        }
    }

    return 0;
}

vector<int> DBScan::getNeighbors(const shared_ptr<Point> point) {
    vector<int> neighborIndexes;
    for (size_t i = 0, n = points.size(); i < n; i++) {
        double distance = point->dist(points[i]);
        if (distance <= eps && distance >= 1e-8) {
            neighborIndexes.push_back(i);
        }
    }

    return neighborIndexes;
}

void DBScan::formThreadGroups() {
    for (size_t i = 0; i < cntThreads - 1; i++) {
        vector<int> threadGroup;
        for (size_t j = i * pointsInThreadGroup; j < pointsInThreadGroup * (i+1); j++) {
            threadGroup.push_back(j);
        }
        threadGroups.push_back(threadGroup);
    }

    vector<int> threadGroup;
    for (size_t j = (cntThreads - 1) * pointsInThreadGroup; j < points.size(); j++) {
        threadGroup.push_back(j);
    }
    threadGroups.push_back(threadGroup);
}

void DBScan::formNeighborGroups() {
    for (int i = 0; i < cntThreads; i++) {
        neighborGroups.push_back(vector<int>());
    }
}

void DBScan::getSomeNeighbors(const shared_ptr<Point> point, int threadNumber) {
    neighborGroups[threadNumber].clear();
    for (size_t i = 0, n = threadGroups[threadNumber].size(); i < n; i++) {
        double distance = point->dist(points[threadGroups[threadNumber][i]]);
        //printf("%lf\n", distance);
        if (distance <= eps && distance >= 1e-8) {
            neighborGroups[threadNumber].push_back(i);
        }
    }
}

// void DBScan::runThread() {
//     while(!)
// }

vector<int> DBScan::getNeighborsP(const shared_ptr<Point> point) {
    for (int i = 0; i < cntThreads; i++) {
        this->threads[i] = thread(&DBScan::getSomeNeighbors, this, point, i);
    }
    //printf()
    for (int i = 0; i < cntThreads; i++) {
        this->threads[i].join();
    }
    vector<int> neighborIndexes;
    for (int i = 0; i < cntThreads; i++) {
        neighborIndexes.insert(neighborIndexes.end(), neighborGroups[i].begin(), neighborGroups[i].end());
    }

    return neighborIndexes;
}
