
#pragma once

#include <thread>

#include "Huffman.h"

#define THRD_CNT 3

class Conveyor {
public:
	Conveyor(){}

	void runParallel(size_t cntRequests) {
		for (size_t i = 0; i < cntRequests; i++) {
			auto r = Request::createRequest();
			q1.push(r);
		}

		this->threads[0] = std::thread(&Conveyor::stage1, this);
		this->threads[1] = std::thread(&Conveyor::stage2, this);
		this->threads[2] = std::thread(&Conveyor::stage3, this);

		for (int i = 0; i < THRD_CNT; i++) {
			this->threads[i].join();
		}

		for (size_t i = 0; i < cntRequests; i++) {
			auto r = processedRequests[i];
			Huffman::printInfo(r);
		}
	}

private:
	void stage1() {
		while (!this->q1.empty()) {
			auto r = q1.front();
			Huffman::stage1(r);

			q2.push(r);
			q1.pop();
		}	
	}

	void stage2() {
		do {
			if (!this->q2.empty()) {
				auto r = q2.front();
				Huffman::stage2(r);

				q3.push(r);
				q2.pop();
			}
		} while(!q1.empty() || !q2.empty());
	}

	void stage3() {
		do {
			if (!this->q3.empty()) {
				auto r = q3.front();
				Huffman::stage3(r);

				processedRequests.push_back(r);
				q3.pop();
			}
		} while(!q1.empty() || !q2.empty() || !q3.empty());
	}

private:
	std::thread threads[THRD_CNT];
	std::vector<std::shared_ptr<Request>> processedRequests;

    std::queue<std::shared_ptr<Request>> q1;
    std::queue<std::shared_ptr<Request>> q2;
    std::queue<std::shared_ptr<Request>> q3;
};