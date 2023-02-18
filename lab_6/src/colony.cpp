#include "colony.hpp"

#include <algorithm>

Colony::Colony(Graph &graph)
		: graph(graph), pheromoneGraph(graph.size(), START_PHEROMONE) {}

SimulationResult Colony::simulation(Parameters parameters) {
	params = parameters;
	pheromoneGraph = Graph(graph.size(), START_PHEROMONE);
	std::vector<size_t> bestPath;
	double bestPathLen = -1;

	for (size_t i = 0; i < params.simulationDays; ++i) {
		std::vector<std::vector<size_t>> dayPaths(graph.size());
		for (size_t v = 0; v < graph.size(); ++v) {
			auto path = makePath(v);
			auto pathLen = getPathLen(path);
			dayPaths.at(v) = path;

			if (pathLen < bestPathLen || std::abs(bestPathLen + 1) < std::numeric_limits<double>::epsilon()) {
				bestPath = path;
				bestPathLen = pathLen;
			}
		}
		updatePheromone(dayPaths);
		addPheromone(bestPath); // elite ants
	}

	return { bestPath, bestPathLen };
}

std::vector<size_t> Colony::makePath(size_t startVert) {
	std::vector<size_t> visitedVertexes = {startVert};

	auto curVert = startVert;
	while (visitedVertexes.size() != graph.size()) {
		curVert = choseVert(curVert, visitedVertexes);
		visitedVertexes.push_back(curVert);
	}

	return visitedVertexes;
}

size_t Colony::choseVert(size_t vertex, const std::vector<size_t> &visitedVertexes) {
	auto probability = randomProbability();
	auto availableVertexes = graph.getAvailableVertices(vertex, visitedVertexes);

	auto probabilities = vertexesProbabilities(vertex, availableVertexes);
	auto denominator = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);

	double curProb = 0.0;
	for (auto &v: availableVertexes) {
		curProb += probabilities.at(v) / denominator;
		if (curProb >= probability) {
			return v;
		}
	}

	return availableVertexes[availableVertexes.size() - 1];
}

double Colony::randomProbability() {
	return distribution(generator);
}

std::vector<double> Colony::vertexesProbabilities(size_t curVert, const std::vector<size_t> &availableVertexes) {
	std::vector<double> probabilities(graph.size(), 0);

	for (auto &v: availableVertexes) {
		probabilities.at(v) = static_cast<double &&>(
			std::pow(pheromoneGraph.get(curVert, v), params.a)
				* std::pow(1. / graph.get(curVert, v), params.b)
		);
	}

	return probabilities;
}

double Colony::getPathLen(std::vector<size_t> path) {
	double len = 0;
	for (size_t i = 0; i < path.size(); ++i) {
		if (i < path.size() - 1) {
			len += graph.get(path.at(i), path.at(i + 1));
		}
		else {
			len += graph.get(path.at(i), path.at(0));
		}
	}
	return len;
}

void Colony::updatePheromone(const std::vector<std::vector<size_t>> &paths) {
	vaporizePheromone();
	addPheromone(paths);
}

void Colony::vaporizePheromone() {
	for (size_t i = 0; i < graph.size(); ++i) {
		for (size_t j = 0; j < graph.size(); ++j) {
			if (i == j) {
				continue;
			}

			pheromoneGraph.set(i, j, pheromoneGraph.get(i, j) * (1 - params.p));
			if (pheromoneGraph.get(i, j) <= 1e-5) {
				pheromoneGraph.set(i, j, START_PHEROMONE);
			}
		}
	}
}

void Colony::addPheromone(const std::vector<std::vector<size_t>> &paths) {
	for (auto &path: paths) {
		addPheromone(path);
	}
}

void Colony::addPheromone(const std::vector<size_t> &path) {
	for (size_t i = 0; i < path.size(); ++i) {
		size_t from = 0, to = 0;
		if (i != path.size() - 1) {
			from = path.at(i);
			to = path.at(i + 1);
		}
		else {
			from = path.at(i);
			to = path.at(0);
		}

		auto delta = params.q / graph.get(from, to);
		auto new_val = pheromoneGraph.get(from, to) + delta;
		pheromoneGraph.set(from, to, new_val);
		pheromoneGraph.set(to, from, new_val);
	}
}



