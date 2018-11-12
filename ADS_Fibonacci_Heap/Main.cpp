#include <iostream>
#include <iomanip>
#include <unordered_map>

#include "FibonacciHeap.h"
#include "FrequencyCounter.h"

using namespace std;

int main() {
    FrequencyCounter fCounter;
    fCounter.addItem("facebook", 5);

    fCounter.addItem("google", 3);

    fCounter.addItem("amazon", 10);
#if 0
    fCounter.addItem("yahoo", 2);
    fCounter.addItem("gmail", 4);

    fCounter.addItem("youtube", 2);
    fCounter.addItem("playing", 6);
    fCounter.addItem("news", 8);
    fCounter.addItem("ufl", 12);
    fCounter.printAllItems();
#endif
    //fCounter.printPQ();
    //fCounter.addItem("google", 71);
    //fCounter.printAllItems();

    //fCounter.printAllItems();
    //fCounter.printPQ();
    fCounter.printTopItems(3);
    //fCounter.printPQ();
    //fCounter.printPQ();
    //fCounter.addItem("youtube", 23);
    //fCounter.printTopItems(15);
    //fCounter.printAllItems();
    //fCounter.printPQ();


#if 0
    PQ_Fibonacci <int>* fibpq = new PQ_Fibonacci <int>(12);

    PQ_Fibonacci <int>* it1 = fibpq->insertItem(3);
    fibpq->insertItem(10);
    fibpq->insertItem(2);


    PQ_Fibonacci <int>* it = fibpq->insertItem(4);
    PQ_Fibonacci <int>* it2 = fibpq->insertItem(2);
    fibpq->insertItem(6);
    fibpq->insertItem(8);
    fibpq->insertItem(12);
    cout << "first print " << endl;
    fibpq->printAllNodes();

    fibpq->extractMax();
    cout << "max extracted " << endl;
    fibpq->printAllNodes();
    std::cout << "increase key start " << std::endl;
    fibpq->increaseKey(it, 16);
    fibpq->increaseKey(it1, 18);
    fibpq->increaseKey(it2, 28);
    //fibpq->increaseKey(it, 155);
    //std::cout << "after increase key " << std::endl;



    fibpq->printAllNodes();
    //fibpq->increaseKey(fibpq, 23);
    fibpq->extractMax();
    fibpq->printAllNodes();
#endif
    return 0;
}


