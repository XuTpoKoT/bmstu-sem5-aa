#include "Conveyor.h"

int main() {
    auto r = Request::createRequest();
    auto conveyor = make_shared<Conveyor>();
    conveyor->runParallel(3);

    return 0;
}