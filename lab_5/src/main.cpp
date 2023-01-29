#include <vector>

#include "Conveyor.h"

int main() {
    auto conveyor = make_shared<Conveyor>();
    vector<size_t> sizes{500, 1000, 2000, 4000};
    for (auto size : sizes) {
        conveyor->runParallel(size);
        conveyor->runСonsistently(size);
    }
    
    return 0;
}