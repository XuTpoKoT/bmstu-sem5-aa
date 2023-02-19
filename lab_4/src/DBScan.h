#ifndef DBScan_H
#define DBScan_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>

#include "Point.h"
#include <thread>

using namespace std;

#define IN_SEED -3
#define UNVISITED -2
#define NOISE -1

class DBScan {
public:
    const vector<shared_ptr<Point>> points;
    vector<int> clusterIndexes;
    
    DBScan(vector<shared_ptr<Point>> points, size_t minPointsInCluster, double eps, int cntThreads) :
        points(points), minPointsInCluster(minPointsInCluster), eps(eps), threads(cntThreads) {
            this->cntThreads = cntThreads;
            pointsInThreadGroup = points.size() / cntThreads;
            formThreadGroups();
            formNeighborGroups();
            
            for (size_t i = 0; i < points.size(); i++) {
                clusterIndexes.push_back(UNVISITED);
            }
        } 

    int run();
    int runP();
    void getSomeNeighbors(const shared_ptr<Point> point, int threadNumber);
    
private:
    const size_t minPointsInCluster;
    const double eps;
    int cntThreads;
    int pointsInThreadGroup;
    int curPointIndex;
    int curClusterID;
    vector<int> seeds;
    vector<thread> threads;
    vector<vector<int>> threadGroups;
    vector<vector<int>> neighborGroups;
    mutex m;

    int expandCluster();
    vector<int> getNeighbors(const shared_ptr<Point> point);

    void formThreadGroups();
    void formNeighborGroups();
    int expandClusterP();
    vector<int> getNeighborsP(const shared_ptr<Point> point);
};

#endif // DBScan_H
