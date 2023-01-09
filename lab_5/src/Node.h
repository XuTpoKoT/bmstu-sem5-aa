#include <memory>
using namespace std;

class Node {
public:
	char ch;
	int freq;
	shared_ptr<Node> left;
    shared_ptr<Node> right;

	Node(char ch, int freq, shared_ptr<Node> left, shared_ptr<Node> right) : 
		ch{ch}, freq{freq}, left{left}, right{right} {}
};