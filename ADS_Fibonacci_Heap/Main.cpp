#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "FibonacciHeap.h"
#include "FrequencyCounter.h"

using namespace std;

int main() {
    FrequencyCounter fCounter;
    fCounter.addItem("facebook", 1);
    fCounter.addItem("google", 11);

    fCounter.addItem("amazon", 5);
    fCounter.addItem("yahoo", 16);
    fCounter.addItem("gmail", 7);
#if 0
    fCounter.addItem("youtube", 71);
    fCounter.addItem("playing", 12);
    fCounter.addItem("google", 11);
    fCounter.printAllItems();
    fCounter.printPQ();
    fCounter.addItem("google", 71);
    fCounter.printAllItems();
#endif
    fCounter.printAllItems();
    fCounter.printPQ();
    fCounter.printTopItems(2);
    return 0;
}


