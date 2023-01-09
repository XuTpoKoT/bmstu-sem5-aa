#ifndef STUD_96_ARRUTILS_H
#define STUD_96_ARRUTILS_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <limits>
#include <vector>

#include "BSTree.h"

class ArrUtils {
public:
    static void print(std::vector<int> &arr) {
        for (int &i : arr) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    static bool equals(std::vector<int> &a, std::vector<int> &b) {
        if (a.size() != b.size()) {
            return false;
        }
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    static void fillRand(std::vector<int> &arr, int min, int max) {
        for (int & x : arr) {
            x = min + (rand() % static_cast<int>(max - min + 1));
        }
    }

    static void fillAsc(std::vector<int> &arr) {
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = i;
        }
    }

    static void fillDesc(std::vector<int> &arr) {
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = arr.size() - i;
        }
    }

    static void fillForBalancedTree(std::vector<int> &arr) {
        for (int & x : arr) {
            x = (rand() % static_cast<int>(1000));
        }
    }

    static void shakerSort(std::vector<int> &a) {
        int left = 0;
        int right = a.size() - 1;
        int newBorder = left;

        while (right > left) {
            for (int i = left; i < right; i++) {
                if (a[i] > a[i+1]) {
                    int tmp = a[i];
                    a[i] = a[i+1];
                    a[i+1] = tmp;
                    newBorder = i;
                }
            }
            right = newBorder;

            for (int i = right; i > left; i--) {
                if (a[i-1] > a[i]) {
                    int tmp = a[i];
                    a[i] = a[i-1];
                    a[i-1] = tmp;
                    newBorder = i;
                }
            }
            left = newBorder;
        }
    }

    static void gnomeSort(std::vector<int> &a) {
        int n =  a.size();

        for (int i = 0; i < n;) {
            if (i == 0 || a[i-1] <= a[i]) {
                i++;
            } else {
                int tmp = a[i];
                a[i] = a[i-1];
                a[i-1] = tmp;
                i--;
            }
        }
    }

    static void treeSort(std::vector<int> &arr) {
        auto tree = std::make_unique<BSTree>();

        for (int &el : arr) {
            tree->insert(el);
        }

        tree->traverse(arr);
    }
};

#endif //STUD_96_ARRUTILS_H
