#ifndef DBSCAN_H
#define DBSCAN_H

#include <stdio.h>
#include <vector>
#include <cmath>
#include <memory>

#define IN_SEED -3
#define UNVISITED -2
#define NOISE -1

struct Point
{
    double x, y, z;
    int clusterID;

    double dist(const std::shared_ptr<Point> p);
};

class DBSCAN {
public:
    const std::vector<std::shared_ptr<Point>> points;
    std::vector<int> clusterIndexes;
    std::size_t minPointsInCluster;
    double eps;
  
    DBSCAN(std::vector<std::shared_ptr<Point>> points, std::size_t minPointsInCluster, double eps) :
        points(points), minPointsInCluster(minPointsInCluster), eps(eps) {
            for (std::size_t i = 0; i < points.size(); i++) {
                clusterIndexes.push_back(UNVISITED);
            }
        } 

    int run();
    int runParallel();
    
private:
    int expandCluster(int curPointIndex, int curClusterID);
    int expandClusterParallel(int curPointIndex, int curClusterID);
    std::vector<int> getNeighbors(const std::shared_ptr<Point> point);
};

#endif // DBSCAN_H
