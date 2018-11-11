#include "FrequencyCounter.h"

FrequencyCounter :: FrequencyCounter() {
    fibpq = NULL;
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
    HASH_TABLE::iterator it;
    std::cout << "Number of items in table : " << freqMap.size() << std::endl;
    /*for(it = freqMap.begin(); it != freqMap.end(); ++it) {
        std::cout << std::setw(16) << std::left << it->first << " : " << it->second << std::endl;
    }*/
    for(it = freqMap.begin(); it != freqMap.end(); ++it) {
        std::cout << std::setw(16) << std::left << it->first << " : " << it->second->getValue() << std::endl;
    }
}

void FrequencyCounter :: addItem(std::string domain, int count) {

    if (freqMap.end() != freqMap.find(domain)) {
        freqMap[domain]->addToKey(freqMap[domain], count);
    }
    else {
        PQ_Fibonacci <int>* node;

        if (NULL == fibpq) {
            node = new PQ_Fibonacci <int>(count);
            fibpq = node;
        }
        else {
            node = fibpq->insertItem(count);
        }
        freqMap[domain] = node;
    }
}

void FrequencyCounter :: printPQ() {
    if (fibpq) {
        fibpq->printAllNodes();
    }
}

void FrequencyCounter :: printTopItems(int count) {
    PQ_Fibonacci <int>** mNodes = new PQ_Fibonacci <int>* [count];
    std::cout << "Top " << count << " entries : " << std::endl;
    for (int i=0; i<count; ++i) {
        mNodes[i] = fibpq->extractMax();
        if (NULL == mNodes[i] && (i < count - 1)) {
            std::cout << "Empty heap" << std::endl;
        }
        std::cout << mNodes[i]->getValue() << std::endl;
        //fibpq->printAllNodes();
    }
#if 0
    std::cout << "Top " << count << " nodes : " << std::endl;
    for(int i=0; i<count; ++i) {
        mNodes[i]->printNode(mNodes[i]);
    }
#endif
    std::cout << "Top " << count << " nodes : " << std::endl;
    for(int i=0; i<count; ++i) {
        mNodes[i]->printNode(mNodes[i]);
    }

    std::cout << "printing heap" << std::endl;
    printPQ();
}
