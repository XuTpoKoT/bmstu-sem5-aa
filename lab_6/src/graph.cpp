#include "graph.hpp"

#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

Graph::Graph(size_t cntVertices, double initVal)
		: adjacencyMatrix(cntVertices, std::vector<double>(cntVertices, initVal)) {}

std::vector<size_t> Graph::getAvailableVertices(size_t vertex, const std::vector<size_t> &visitedVertexes) const {
	std::vector<size_t > result;
	for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
		if (adjacencyMatrix.at(vertex).at(i) > 0 and std::find(visitedVertexes.begin(), visitedVertexes.end(), i) == visitedVertexes.end()) {
			result.push_back(i);
		}
	}
	return result;
}

void Graph::set(size_t i, size_t j, double value) {
	adjacencyMatrix.at(i).at(j) = value;
}

double Graph::get(size_t i, size_t j) const {
	return adjacencyMatrix.at(i).at(j);
}

size_t Graph::size() const {
	return adjacencyMatrix.size();
}

Graph Graph::genGraph(size_t size, int maxLen) {
	std::default_random_engine generator(static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> distribution(1, maxLen);

	Graph graph(size);
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			if (i != j) {
				graph.set(i, j, distribution(generator));
			} else {
				graph.set(i, j, 0);
			}	
		}
	}

	return graph;
}

Graph Graph::genGraph1() {

	Graph graph(4);
	graph.set(0, 1, 1);
	graph.set(0, 2, 1);
	graph.set(0, 3, 9);

	graph.set(1, 0, 9);
	graph.set(1, 2, 1);
	graph.set(1, 3, 9);

	graph.set(2, 0, 9);
	graph.set(2, 1, 1);
	graph.set(2, 3, 1);

	graph.set(3, 0, 1);
	graph.set(3, 1, 9);
	graph.set(3, 2, 9);

	return graph;
}

void Graph::print() {
	for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
		for (size_t j = 0; j < adjacencyMatrix.size(); ++j) {
			std::cout << adjacencyMatrix.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
}