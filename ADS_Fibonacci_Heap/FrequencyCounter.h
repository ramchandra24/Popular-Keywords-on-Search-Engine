#ifndef FREQUENCYCOUNTER_H_
#define FREQUENCYCOUNTER_H_

#include "FibonacciHeap.h"
#include <unordered_map>
#include <iostream>
#include <iomanip>

#define PAIR_KV        std::pair<std::string, PQ_Fibonacci<int>*>
#define HASH_TABLE     std::unordered_map<std::string, PQ_Fibonacci<int>*>



class FrequencyCounter{
private:
    PQ_Fibonacci<int>* fibpq;
    //std::unordered_map <std::string, PQ_Fibonacci<int>* > freqMap;
    HASH_TABLE freqMap;

public:
    FrequencyCounter();
    void addItem(std::string domain, int count);
    void printAllItems();
};




#endif /* FREQUENCYCOUNTER_H_ */
