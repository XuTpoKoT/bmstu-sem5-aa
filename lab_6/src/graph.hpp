#ifndef LAB06_graphgraphHPP_
#define LAB06_graphgraphHPP_

#include <vector>

using namespace std;

class Graph {
private:
	std::vector<std::vector<double>> adjacencyMatrix;
public:
	static Graph genGraph(size_t size, int maxLen);
	explicit Graph(size_t cntVertices, double initVal = -1);

	std::vector<size_t> getAvailableVertices(size_t vertex, const std::vector<size_t> &visitedVertexes) const;
	void set(size_t i, size_t j, double value);
	double get(size_t i, size_t j) const;
	size_t size() const;
	void print();
	static Graph genGraph1();
};

#endif  // LAB06_graphgraphHPP_
