#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "FibonacciHeap.h"

using namespace std;

int main() {
    PQ_Fibonacci <int> * fibpq = new PQ_Fibonacci <int>(85);
    // Map to store (PQ node -> Keyword Frequency) mapping
    unordered_map <int, PQ_Fibonacci <int>> hmap;

    fibpq->dummy();
    return 0;
}


