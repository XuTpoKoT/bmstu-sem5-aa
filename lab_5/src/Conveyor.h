#pragma once

#include <thread>
#include <mutex>

#include "Huffman.h"
#include "CSVWriter.h"

#define THRD_CNT 3

class Conveyor {
public:
	Conveyor() {
		wParallel << "size" << "time" << endrow;
		wСonsistently << "size" << "time" << endrow;
	}

	void runParallel(size_t cntRequests) {
		processedRequests.clear();
		
		for (size_t i = 0; i < cntRequests; i++) {
			auto r = Request::createRequest();
			q1.push(r);
		}

		long long timeStart = getThreadCpuTimeNs();

		this->threads[0] = std::thread(&Conveyor::stage1, this);
		this->threads[1] = std::thread(&Conveyor::stage2, this);
		this->threads[2] = std::thread(&Conveyor::stage3, this);

		for (int i = 0; i < THRD_CNT; i++) {
			this->threads[i].join();
		}
		long long timeEnd = getThreadCpuTimeNs();

		for (size_t i = 0; i < cntRequests; i++) {
			auto r = processedRequests[i];
			Huffman::printInfo(r);
		}
		
		wParallel << cntRequests << (timeEnd - timeStart) / 1000 << endrow;
        wParallel.flush();
	}

	void runСonsistently(size_t cntRequests) {
		processedRequests.clear();

		for (size_t i = 0; i < cntRequests; i++) {
			auto r = Request::createRequest();
			q1.push(r);
		}
		long long timeStart = getThreadCpuTimeNs();

		while (!this->q1.empty()) {
			auto r = q1.front();
			q1.pop();
			Huffman::stage1(r);
			Huffman::stage2(r);
			Huffman::stage3(r);
			processedRequests.push_back(r);
		}
		long long timeEnd = getThreadCpuTimeNs();

		// for (size_t i = 0; i < cntRequests; i++) {
		// 	auto r = processedRequests[i];
		// 	Huffman::printInfo(r);
		// }

		wСonsistently << cntRequests << (timeEnd - timeStart) / 1000 << endrow;
        wСonsistently.flush();
	}

private:
	void stage1() {
		while (!this->q1.empty()) {
			auto r = q1.front();
			Huffman::stage1(r);

			m1.lock();
			q2.push(r);
			m1.unlock();
			q1.pop();
		}	
	}

	void stage2() {
		do {
			if (!this->q2.empty()) {
				auto r = q2.front();
				Huffman::stage2(r);

				m2.lock();
				q3.push(r);
				m2.unlock();
				m1.lock();
				q2.pop();
				m1.unlock();
			}
		} while(!q1.empty() || !q2.empty());
	}

	void stage3() {
		do {
			if (!this->q3.empty()) {
				auto r = q3.front();
				Huffman::stage3(r);

				processedRequests.push_back(r);
				m2.lock();
				q3.pop();
				m2.unlock();
			}
		} while(!q1.empty() || !q2.empty() || !q3.empty());
	}

private:
	CSVWriter wParallel{"../report/parallel.csv"};
	CSVWriter wСonsistently{"../report/consistently.csv"};
	std::thread threads[THRD_CNT];
	std::vector<std::shared_ptr<Request>> processedRequests;

    std::queue<std::shared_ptr<Request>> q1;
    std::queue<std::shared_ptr<Request>> q2;
    std::queue<std::shared_ptr<Request>> q3;
	std::mutex m1, m2;
};