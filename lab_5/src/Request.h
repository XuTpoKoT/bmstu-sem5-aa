#pragma once

#include <string>
#include <queue>
#include <unordered_map>

#include "NodeComparator.h"
#include "StringGenerator.h"

class Request {
public:
    Request(string srcData) : srcData{srcData} {}

public:
    string srcData;
    string result;
    unordered_map<char, int> freq;
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, NodeComparator> pq;
    unordered_map<char, string> huffmanCode;
    long long timeStart, timeEnd;

    static shared_ptr<Request> createRequest() {
        return make_shared<Request>(StringGenerator::genString(10));
    }
};