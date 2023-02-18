#ifndef SerialDBScan_H
#define SerialDBScan_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

#define IN_SEED -3
#define UNVISITED -2
#define NOISE -1

struct Point
{
    double x, y;
    int clusterID;

    double dist(const shared_ptr<Point> p);
};

class SerialDBScan {
public:
    const vector<shared_ptr<Point>> points;
    vector<int> clusterIndexes;
    
    SerialDBScan(vector<shared_ptr<Point>> points, size_t minPointsInCluster, double eps, int threadCnt) :
        points(points), minPointsInCluster(minPointsInCluster), eps(eps) {
            for (size_t i = 0; i < points.size(); i++) {
                clusterIndexes.push_back(UNVISITED);
            }
        } 

    int run();
    
private:
    const size_t minPointsInCluster;
    const double eps;
    int curPointIndex;
    int curClusterID;
    vector<int> seeds;

    int expandCluster();
    vector<int> getNeighbors(const shared_ptr<Point> point);
};

#endif // SerialDBScan_H
