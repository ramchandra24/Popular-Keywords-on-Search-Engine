#ifndef FREQUENCYCOUNTER_H_
#define FREQUENCYCOUNTER_H_

#include "FibonacciHeap.h"
#include <unordered_map>
#include <iostream>
#include <iomanip>


#define HASH_TABLE     std::unordered_map<std::string, int>



class FrequencyCounter{
private:
    PQ_Fibonacci<int> *fibpq;
    //std::unordered_map <std::string, PQ_Fibonacci<int>* > freqMap;
    HASH_TABLE freqMap;

public:
    FrequencyCounter();
    bool addItem(std::string domain, int count);
    void printAllItems();
};




#endif /* FREQUENCYCOUNTER_H_ */
