#ifndef LAB06_ALGS_COLONY_HPP_
#define LAB06_ALGS_COLONY_HPP_

#include <random>

#include "graph.hpp"

struct Parameters {
	double a;
	double b;
	double p; // vaporizing coef
	double q;
	int simulationDays;
};

struct SimulationResult {
	std::vector<size_t> path;
	double pathLen;
};

class Colony {
private:
	static constexpr const double START_PHEROMONE = 0.3;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0, 1);

	Graph graph;
	Graph pheromoneGraph;
	Parameters params;

public:
	explicit Colony(Graph &graph);
	SimulationResult simulation(Parameters parameters);

private:
	std::vector<size_t> makePath(size_t start_vert);
	double getPathLen(std::vector<size_t> path);
	void updatePheromone(const std::vector<std::vector<size_t>> &paths);
	void vaporizePheromone();
	void addPheromone(const std::vector<std::vector<size_t>> &paths);
	void addPheromone(const std::vector<size_t> &path);
	double randomProbability();
	std::vector<double> vertexesProbabilities(size_t curVert, const std::vector<size_t> &availableVertexes);
	size_t choseVert(size_t vertex, const std::vector<size_t> &visitedVertexes);
};

#endif  // LAB06_ALGS_COLONY_HPP_
