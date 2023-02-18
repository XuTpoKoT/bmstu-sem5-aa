#include "exhaustive_search.hpp"

#include <algorithm>
#include <queue>
#include <numeric>
#include <limits>

double pathLen(const Graph &graph, const std::vector<int> &path) {
	double len = 0;
	for (size_t i = 0; i < path.size() - 1; ++i) {
		len += graph.get(path[i], path[i+1]);
	}
	len += graph.get(path[path.size()-1], path[0]);
	return len;
}

std::pair<std::vector<int>, double> exhaustiveSearch(const Graph &graph) {
	std::vector<int> bestPath(graph.size());
	std::vector<int> curPath(graph.size());
	for (int i = 0; i < graph.size(); i++) {
		curPath[i] = i;
	}
	double bestPathLen = pathLen(graph, curPath);

	while(std::next_permutation(curPath.begin(), curPath.end())) {
		auto len = pathLen(graph, curPath);
		if (len < bestPathLen) {
			bestPathLen = len;
			bestPath = curPath;
		}
	}

	return std::make_pair(bestPath, bestPathLen);
}
