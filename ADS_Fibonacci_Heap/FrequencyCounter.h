#ifndef FREQUENCYCOUNTER_H_
#define FREQUENCYCOUNTER_H_

#include "FibonacciHeap.h"
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#define PAIR_KV        std::make_pair<std::string, PQ_Fibonacci<int>*>
#define HASH_TABLE     std::unordered_map<std::string, PQ_Fibonacci<int>*>
#define PQ             PQ_Fibonacci<int>


class FrequencyCounter{
private:
    PQ_Fibonacci<int>* fibpq;
    //std::unordered_map <std::string, PQ_Fibonacci<int>* > freqMap;
    HASH_TABLE freqMap;
    std::ifstream ipFile;
    std::ofstream opFile;

public:
    FrequencyCounter(std::string ipPath, std::string opPath);
    ~FrequencyCounter();
    void addItem(std::string domain, int count);
    void printAllItems();
    void printPQ();
    void printTopItems(int count);
    void analyze();
    void outputToFile(std::string opString);
};




#endif /* FREQUENCYCOUNTER_H_ */
