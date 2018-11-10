#include "FrequencyCounter.h"

FrequencyCounter :: FrequencyCounter() {
#if 0
    PQ_Fibonacci <int>* fibpq = new PQ_Fibonacci <int>(85);

    fibpq->insertItem(50);
    fibpq->insertItem(65);
    fibpq->insertItem(60);
    PQ_Fibonacci <int>* it = fibpq->insertItem(50);
    //it->increaseKey(it, 155);
/*    fibpq->insertItem(35);
    fibpq->insertItem(20);
    fibpq->insertItem(960);
    fibpq->insertItem(95);
    fibpq->insertItem(10);*/
    //fibpq->printAllNodes();

    //fibpq->insertItem(90);
    //fibpq->printAllNodes();

    fibpq->extractMax();
    fibpq->printAllNodes();
    std::cout << "increase key start " << std::endl;
    fibpq->increaseKey(it, 155);
    std::cout << "after increase key " << std::endl;
    fibpq->printAllNodes();
    // Map to store (PQ node -> Keyword Frequency) mapping
    //unordered_map <int, PQ_Fibonacci <T>*> hmap;
#endif

}

void FrequencyCounter :: printAllItems() {
    HASH_TABLE :: iterator it;
    std::cout << "Number of items in table : " << freqMap.size() << std::endl;
    for(it = freqMap.begin(); it != freqMap.end(); ++it) {
        std::cout << std::setw(16) << std::left << it->first << " : " << it->second << std::endl;
    }
}

bool FrequencyCounter :: addItem(std::string domain, int count) {
    freqMap.insert(std::pair<std::string, int>(domain, count));
}

