#ifndef LAB06_ALGS_exhaustive_search_HPP_
#define LAB06_ALGS_exhaustive_search_HPP_

#include <vector>
#include "graph.hpp"

double pathLen(const Graph &graph, const std::vector<int> &path);
std::pair<std::vector<int>, double> exhaustiveSearch(const Graph &graph);

#endif  // LAB06_ALGS_exhaustiveSearch_HPP_
