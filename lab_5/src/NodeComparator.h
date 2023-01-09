#include "Node.h"

class NodeComparator {
public:
	bool operator()(shared_ptr<Node> l, shared_ptr<Node> r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};