#include <cmath>
#include <iostream>
#include <algorithm>

#include "colony.hpp"
#include "exhaustive_search.hpp"
#include "CSVWriter.h"

void runParameterization(Graph &graph, double pathLen, CSVWriter &writer) {
	writer << "a" << "p" << "tmax" << "delta" << endrow;
	static const double A_B_CONST = 1.0;
	static const int SIMULATION_TIMES = 5;
	std::vector<double> aArr{0.1, 0.25, 0.5, 0.75, 0.9};
	std::vector<int> tmaxArr{50, 100, 200, 400};

	Colony colony(graph);
	Parameters curParams{.q = pathLen};
	for (auto a : aArr) {
		curParams.a = a;
		curParams.b = A_B_CONST - a;
		for (auto p = 0.0; p <= 1.0; p += 0.2) {		
			curParams.p = p;
			for (auto tmax : tmaxArr) {
				curParams.simulationDays = tmax;
				SimulationResult res{.pathLen = 0};
				for (int i = 0; i < SIMULATION_TIMES; i++) {
					auto curRes = colony.simulation(curParams);
					res.pathLen += curRes.pathLen;
				}
				res.pathLen /= SIMULATION_TIMES;
				double lenDelta = std::fabs(res.pathLen - pathLen);

				writer << a << p << tmax << lenDelta<< endrow;
			}			
		}
	}
	writer.flush();
}

long long getThreadCpuTimeNs() {
	struct timespec t;
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t)) {
		perror("clock_gettime");
		return 0;
	}
	return t.tv_sec * 1000000000LL + t.tv_nsec;
}

void timeMes() {
	CSVWriter w1{"../report/t_ex1.csv"}, w2{"../report/t_ant1.csv"}, w3{"../report/t_ex2.csv"}, w4{"../report/t_ant2.csv"};
	w1 << "size" << "time" << endrow;
	w2 << "size" << "time" << endrow;
	w3 << "size" << "time" << endrow;
	w4 << "size" << "time" << endrow;
	size_t cntCities = 9;
	Parameters bestParams1{.a = 0.9, .b = 0.1, .p = 0.8, .q = 10, .simulationDays = 200};
	Parameters bestParams2{.a = 0.1, .b = 0.9, .p = 0.2, .q = 900, .simulationDays = 50};

	for (int cntCities = 3; cntCities < 11; cntCities++) {
		auto graph = Graph::genGraph(cntCities, 5);
		long long t1 = getThreadCpuTimeNs();
		auto exRes = exhaustiveSearch(graph);
		long long t2 = getThreadCpuTimeNs();
		w1 << cntCities << (t2 - t1) / 1000 << endrow;
        w1.flush();
		//std::cout << (t2 - t1) / 1000 << std::endl;

		Colony colony(graph);
		t1 = getThreadCpuTimeNs();
		auto antRes = colony.simulation(bestParams1);
		t2 = getThreadCpuTimeNs();
		w2 << cntCities << (t2 - t1) / 1000 << endrow;
        w2.flush();
		//std::cout << (t2 - t1) / 1000 << std::endl;

		graph = Graph::genGraph(cntCities, 1000);
		t1 = getThreadCpuTimeNs();
		exRes = exhaustiveSearch(graph);
		t2 = getThreadCpuTimeNs();
		w3 << cntCities << (t2 - t1) / 1000 << endrow;
        w3.flush();
		//std::cout << (t2 - t1) / 1000 << std::endl;
		
		Colony colony2(graph);
		t1 = getThreadCpuTimeNs();
		antRes = colony2.simulation(bestParams2);
		t2 = getThreadCpuTimeNs();
		w4 << cntCities << (t2 - t1) / 1000 << endrow;
        w4.flush();
		//std::cout << (t2 - t1) / 1000 << std::endl;
	}	
}

int main() {
	//timeMes();
	CSVWriter w1{"../report/graph11.csv"}, w2{"../report/graph22.csv"};
	size_t cntCities = 3;
	Parameters bestParams1{.a = 0.9, .b = 0.1, .p = 0.8, .q = 10, .simulationDays = 200};
	Parameters bestParams2{.a = 0.1, .b = 0.9, .p = 0.2, .q = 900, .simulationDays = 50};

	auto graph = Graph::genGraph(cntCities, 5);
	auto exRes = exhaustiveSearch(graph);
	//std::cout << "Real best len: " << exRes.second << std::endl;
	// for (auto e : exRes.first) {
	// 	std::cout << e << " ";
	// }
	std::cout << "\n";
	//runParameterization(graph, exRes.second, w1);
	Colony colony(graph);
	auto antRes = colony.simulation(bestParams1);
	std::cout << "Ant best len: " << antRes.pathLen << std::endl;
	for (auto e : antRes.path) {
		std::cout << e << " ";
	}
	std::cout << "\n";

	graph = Graph::genGraph(cntCities, 1000);
	exRes = exhaustiveSearch(graph);
	std::cout << "\nReal best len: " << exRes.second  << std::endl;
	//runParameterization(graph, exRes.second, w2);
	Colony colony2(graph);
	antRes = colony2.simulation(bestParams2);
	std::cout << "Ant best len: " << antRes.pathLen << std::endl;

	return 0;
}
