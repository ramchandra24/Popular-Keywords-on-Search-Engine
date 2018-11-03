#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_


template <typename T>
class PQ_Fibonacci {
private:
    T data;
    unsigned int degree; // Number of nodes rooted at this node
    bool childCut;
    PQ_Fibonacci* childNode; // Pointer to child node

    // Pointers for next and previous nodes in doubly linked list
    PQ_Fibonacci* next;
    PQ_Fibonacci* prev;

/* Function declarations */
public:
    PQ_Fibonacci(T data);
    void dummy();
    void printNode(PQ_Fibonacci* node);
};


/* Function definitions */
template <typename T>
void PQ_Fibonacci <T> :: dummy() {
    std::cout << "Dummy function" << std::endl;
}

template <typename T>
PQ_Fibonacci <T> :: PQ_Fibonacci(T data) {
    this->data = data;
    this->childCut = false;
    this->degree = 0;
    this->childNode = NULL;
    this->next = NULL;
    this->prev = NULL;
}

template <typename T>
void PQ_Fibonacci <T> :: printNode(PQ_Fibonacci* node) {
    std::cout << std::endl;
    std::cout << std::setw(10) << std::left << "Data" << ": " << node->data << std::endl;
    std::cout << std::setw(10) << std::left << "Degree" <<": " << node->degree << std::endl;
    std::cout << std::setw(10) << std::left << "ChildCut" << ": " << node->childCut << std::endl;
    std::cout << std::endl;
}



#endif /* FIBONACCIHEAP_H_ */
