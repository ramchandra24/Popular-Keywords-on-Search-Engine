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
    fCounter.addItem("youtube", 71);
    fCounter.addItem("playing", 12);
    fCounter.printAllItems();
    return 0;
}


