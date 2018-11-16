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
    //std::cout << domain << " : " << count << std::endl;
    if (freqMap.end() != freqMap.find(domain)) {
        std::cout << "found " << domain << std::endl;
        fibpq = freqMap[domain]->addToKey(freqMap[domain], count);
    }
    else {
        PQ_Fibonacci<int>* node;
        std::cout << "new node " << domain << std::endl;
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
    if (NULL != fibpq) {
        fibpq->printAllNodes();
    }
}

void FrequencyCounter :: printTopItems(int count) {
    printAllItems();
    std::cout << "Get top : " << count << std::endl;
    PQ_Fibonacci <int>** mNodes = new PQ_Fibonacci <int>* [count];
    for (int i=0; i<count; ++i) {
        mNodes[i] = NULL;
    }
    // Extract 'count' number of nodes from the heap
    for (int i=0; i<count; ++i) {
        std::cout << "Before extract max" << std::endl;
        //fibpq->printAllNodes();
        //fibpq->printAllNodeDescs();
        if (NULL != fibpq) {
            //std::cout << fibpq->getDesc() << std::endl;
            fibpq = fibpq->extractMax(&mNodes[i]);
        }
        std::cout << "After extract max : " << mNodes[i]->getDesc() << std::endl;
        //std::cout << fibpq << std::endl;
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
            if (NULL != fibpq) {
                fibpq->insertNode(mNodes[i]);
            }
            else {
                 fibpq = mNodes[i];
                 fibpq->makeMax();
            }
        }
    }
    outputToFile(oss.str());
}

void FrequencyCounter :: outputToFile(std::string opString) {
    opFile << opString << std::endl;
}


void FrequencyCounter :: analyze() {
    std::string line;
    // Getline from input file until the delimiter - \n
    while (std::getline(ipFile, line, '\n'))
    {
        std::cout << line << std::endl;
        std::stringstream iss(line);
        int count;
        std::string countstr;
        std::string domain;
        // breaking condition
        if (0 == line.compare(0, 4, "stop")) {
            break;
        }
        if ('$' == line[0]) {
            iss >> domain;
            //getline(iss, domain, ' ');
            iss >> countstr;
            count = std::stoi(countstr);
            addItem(&domain[1], count);
        }
        else {
            iss >> countstr;
            count = std::stoi(countstr);
            printTopItems(count);
        }
    }
}
