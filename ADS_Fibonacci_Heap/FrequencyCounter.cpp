#include "FrequencyCounter.h"

FrequencyCounter :: FrequencyCounter(std::string ipPath, std::string opPath) {
    fibpq = NULL;
    this->ipFile.open(ipPath);
    this->opFile.open(opPath);
    if ((!this->ipFile.good()) || (!this->opFile.good())) {
        std::cout << "Error opening file" << std::endl;
    }
}

FrequencyCounter :: ~FrequencyCounter() {
    this->ipFile.close();
    this->opFile.close();
}

void FrequencyCounter :: printAllItems() {
    HASH_TABLE::iterator it;
    std::cout << "Number of items in table : " << freqMap.size() << std::endl;
    for(it = freqMap.begin(); it != freqMap.end(); ++it) {
        std::cout << std::setw(16) << std::left << it->first << " : " << it->second->getValue() << std::endl;
    }
}

void FrequencyCounter :: addItem(std::string domain, int count) {

    if (freqMap.end() != freqMap.find(domain)) {
        std::cout << "before inc key" << std::endl;
        fibpq->printAllNodes();
        freqMap[domain]->addToKey(freqMap[domain], count);
        std::cout << "after inc key" << std::endl;
        fibpq->printAllNodes();
    }
    else {
        PQ_Fibonacci<int>* node;

        if (NULL == fibpq) {
            node = new PQ_Fibonacci<int>(count, domain);
            fibpq = node;
        }
        else {
            node = fibpq->insertItem(count, domain);
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
    for (int i=0; i<count; ++i) {
        mNodes[i] = NULL;
    }
    // Extract 'count' number of nodes from the heap
    //fibpq->printAllNodes();
    for (int i=0; i<count; ++i) {
        std::cout << "Before extract max" << std::endl;
        fibpq->printAllNodes();
        fibpq = fibpq->extractMax(&mNodes[i]);
        std::cout << "After extract max" << std::endl;
        fibpq->printAllNodes();
    }
    std::stringstream oss;
    bool firstString = true;
    for(int i=0; i<count; ++i) {

        if (NULL != mNodes[i]) {
            //std::cout << mNodes[i]->getDesc() << std::endl;
            if (!firstString) {
                oss << ",";
            }
            firstString = false;
            oss << mNodes[i]->getDesc();
            // Re-insert the nodes extracted earlier into the heap
            fibpq->insertNode(mNodes[i]);
        }
    }
    outputToFile(oss.str());
}

void FrequencyCounter :: outputToFile(std::string opString) {
    opFile << opString << std::endl;
}


void FrequencyCounter :: analyze() {
    std::string line;

    while (std::getline(ipFile, line))
    {
        std::stringstream iss(line);
        int count;
        std::string domain;
        // breaking condition
        if ("stop" == line) {
            break;
        }
        if ('$' == line[0]) {
            iss >> domain;
            iss >> count;
            addItem(&domain[1], count);
        }
        else {
            iss >> count;
            printTopItems(count);
        }
    }
}
