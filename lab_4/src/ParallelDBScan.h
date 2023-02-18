#ifndef SerialDBScan_H
#define SerialDBScan_H

#include <stdio.h>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

#include "Point.h"

#define IN_SEED -3
#define UNVISITED -2
#define NOISE -1

using namespace std;

struct Strip {
    vector<shared_ptr<Point>> points;
};

class ParallelDBScan {
public:
    vector<shared_ptr<Point>> points;
    vector<int> clusterIndexes;
    
    ParallelDBScan(vector<shared_ptr<Point>> points, size_t minPointsInCluster, double eps, int threadCnt) :
        points(points), minPointsInCluster(minPointsInCluster), eps(eps), threadCnt(threadCnt) {
            for (size_t i = 0; i < points.size(); i++) {
                clusterIndexes.push_back(UNVISITED);
                // sortedX.push_back(i);
                // sortedY.push_back(i);
            }
        } 

    int run();
    
private:
    const size_t minPointsInCluster;
    const double eps;
    const int threadCnt;
    //vector<int> sortedX;
    //vector<int> sortedY;
    vector<Strip> strips;

    void makeStrips();
    bool cmpX(int p1, int p2);





    int curPointIndex;
    int curClusterID;
    vector<int> seeds;
    queue<int> q;
	mutex mutQ, mutS;
    bool endParallel;
    int expandCluster();
    vector<int> getNeighbors(const shared_ptr<Point> point);
    int runThread();
};

#endif
