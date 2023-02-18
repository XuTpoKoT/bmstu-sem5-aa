#include "SerialDBScan.h"

#include <algorithm>

double Point::dist(const shared_ptr<Point> p) {
    return sqrt(pow(x - p->x, 2) + pow(y - p->y, 2));
}

int SerialDBScan::run() {
    int nextClusterID = 0;
    size_t size = points.size();
    for(size_t i = 0; i < size; i++) {
        if (clusterIndexes[i] == UNVISITED) {
            curPointIndex = i;
            curClusterID = nextClusterID;
            if (expandCluster() != -1) {
                nextClusterID++;
            }
        }
    }

    return 0;
}

int SerialDBScan::expandCluster() {
    vector<int> seeds = getNeighbors(points.at(curPointIndex));

    printf("ID = %d; neighbors: ", curClusterID);
    for (size_t i = 0; i < seeds.size(); i++) {
        printf("%d ", seeds[i]);
    }
    printf("\n");

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
        vector<int> seedNeighbors = getNeighbors(points.at(curSeed));

        printf("    Inner neighbors: ");
        for (size_t i = 0; i < seedNeighbors.size(); i++) {
            printf("%d ", seedNeighbors[i]);
        }
        printf("\n");

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
        seeds.erase(remove(seeds.begin(), seeds.end(), curSeed), seeds.end());
    }

    return 0;
}

vector<int> SerialDBScan::getNeighbors(const shared_ptr<Point> point) {
    vector<int> clusterIndexes;
    for (size_t i = 0, n = points.size(); i < n; i++) {
        double distance = point->dist(points[i]);
        if (distance <= eps && distance >= 1e-8) {
            clusterIndexes.push_back(i);
        }
    }

    return clusterIndexes;
}

// int SerialDBScan::runParallel() {
//     endParallel = false;
//     thread threads[threadCnt];
//     for (int i = 0; i < threadCnt; i++) {
//         threads[i] = thread(&SerialDBScan::runThread, this);
//     }

//     int nextClusterID = 0;
//     size_t size = points.size();
//     for(size_t i = 0; i < size; i++) {
//         if (clusterIndexes[i] == UNVISITED) {
//             curPointIndex = i;
//             curClusterID = nextClusterID;
//             if (expandClusterParallel() != -1) {
//                 nextClusterID++;
//             }
//         }
//     }
//     endParallel = true;

//     for (int i = 0; i < threadCnt; i++) {
//         threads[i].join();
//     }

//     return 0;
// }


// int SerialDBScan::expandClusterParallel() {
//     seeds = getNeighbors(points.at(curPointIndex));

//     if (seeds.size() + 1 < minPointsInCluster) {
//         clusterIndexes[curPointIndex] = NOISE;
//         return -1;
//     }
//     clusterIndexes[curPointIndex] = curClusterID;
//     for (size_t i = 0, cntSeeds = seeds.size(); i < cntSeeds; ++i) {
//         clusterIndexes[seeds[i]] = curClusterID;
//     }

//     while (seeds.size() > 0) {
//         mutS.lock();
//         int curSeed = seeds.back();
//         mutS.unlock();

//         mutQ.lock();
//         q.push(curSeed);
//         mutQ.unlock();

//         mutS.lock();
//         seeds.erase(remove(seeds.begin(), seeds.end(), curSeed), seeds.end());
//         mutS.unlock();
//     }

//     return 0;
// }



