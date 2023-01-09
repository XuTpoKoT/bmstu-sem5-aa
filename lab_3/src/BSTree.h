#ifndef STUD_96_BSTREE_H
#define STUD_96_BSTREE_H

#include <iostream>

struct BinTreeNode {
    int data;
    BinTreeNode *left;
    BinTreeNode *right;
};

class BSTree {
    BinTreeNode *root;
public:
    BSTree() {
        root = nullptr;
    }

    virtual ~BSTree() {
        destroyTree();
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    void inOrderPrint() {
        inOrderPrint(root);
        std::cout << "\n";
    };

    void destroyTree() {
        destroyTree(root);
    }

    void traverse(std::vector<int> &arr) {
        int index = 0;
        traverse(root, arr, index);
    }

private:
    BinTreeNode* insert(BinTreeNode *node, int data) {
        if (node == nullptr) {
            node = new BinTreeNode{data, nullptr, nullptr};
        } else if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    void inOrderPrint(BinTreeNode *node) {
        if (node != nullptr) {
            inOrderPrint(node->left);
            std::cout << node->data << ", ";
            inOrderPrint(node->right);
        }
    }

    void destroyTree(BinTreeNode *node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void traverse(BinTreeNode *node, std::vector<int> &arr, int &index) {
        if (node->left != nullptr) {
            traverse(node->left,arr, index);
        }

        arr[index] = node->data;
        index++;

        if (node->right != nullptr) {
            traverse(node->right,arr, index);
        }
    }
};

#endif //STUD_96_BSTREE_H
