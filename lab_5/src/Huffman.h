#pragma once

#include <iostream>

#include "Request.h"

class Huffman {
public:
    Huffman(){}
    static void run(shared_ptr<Request> r) {
        stage1(r);
        stage2(r);
        stage3(r);
        stage4(r);
    }

    static void stage1(shared_ptr<Request> r) {
        for (char ch: r->srcData) {
            r->freq[ch]++;
        }

        for (auto pair: r->freq) {
            r->pq.push(make_shared<Node>(pair.first, pair.second, nullptr, nullptr));
        }
    }

    static void stage2(shared_ptr<Request> r) {
        while (r->pq.size() > 1) {
            shared_ptr<Node> left = r->pq.top(); r->pq.pop();
            shared_ptr<Node> right = r->pq.top(); r->pq.pop();

            int sum = left->freq + right->freq;
            r->pq.push(make_shared<Node>('\0', sum, left, right));
        }
    }

    static void stage3(shared_ptr<Request> r) {
        encode(r->pq.top(), "", r->huffmanCode);

        for (char ch: r->srcData) {
            r->result += r->huffmanCode[ch];
        }
    }

    static void stage4(shared_ptr<Request> r) {
        size_t index = 0;
        cout << "\nDecoded string is:\n";
        while (index < r->result.size()) {
            decode(r->pq.top(), index, r->result);
        }
        cout << '\n';
    }

    static void printInfo(shared_ptr<Request> r) {
        cout << "Huffman Codes are :\n";
        for (auto pair: r->huffmanCode) {
            cout << pair.first << " " << pair.second << '\n';
        }

        cout << "\nOriginal string was:\n" << r->srcData << '\n';
        cout << "\nEncoded string is:\n" << r->result << '\n';
    }

private:
    static void encode(shared_ptr<Node> root, string str, unordered_map<char, string> &huffmanCode) {
        if (root == nullptr)
            return;

        // found a leaf node
        if (!root->left && !root->right) {
            huffmanCode[root->ch] = str;
        }

        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
    }

    static void decode(shared_ptr<Node> root, size_t &index, string str) {
        if (root == nullptr) {
            return;
        }

        if (!root->left && !root->right)
        {
            cout << root->ch;
            return;
        }

        if (str[index++] =='0')
            decode(root->left, index, str);
        else
            decode(root->right, index, str);
    }

};


