#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include <queue>

template <typename T>
class PQ_Fibonacci {
private:
    T data;
    unsigned int degree; // Number of nodes rooted at this node
    bool childCut;
    PQ_Fibonacci <T>* childNode; // Pointer to one of the child nodes
    PQ_Fibonacci <T>* parentNode; // Pointer to parent node

    // Pointers for next and previous nodes in doubly linked list
    PQ_Fibonacci <T>* next;
    PQ_Fibonacci <T>* prev;


/* Private function declarations */
    PQ_Fibonacci <T>* newNode(PQ_Fibonacci <T>* maxPQ, T data);

/* Public function declarations */
public:
    PQ_Fibonacci(T data);
    PQ_Fibonacci <T>* insertItem(T data);



    void dummy();
    void printNode(PQ_Fibonacci <T>* node);
    void printAllNodes();
    void printRecursive(PQ_Fibonacci <T> * curNode);
    void printBFS(PQ_Fibonacci <T> * curNode);
};


/* Function definitions */
template <typename T>
PQ_Fibonacci <T> :: PQ_Fibonacci(T data) {
    this->data = data;
    this->childCut = false;
    this->degree = 0;
    this->childNode = NULL;
    this->parentNode = NULL;
    // Point the next and prev pointers to the same node initially
    this->next = this;
    this->prev = this;
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: newNode(PQ_Fibonacci <T>* maxPQ, T data) {
    PQ_Fibonacci <T>* node = new PQ_Fibonacci <T>(data);
    if (NULL == maxPQ) {
        return node;
    }

    // Insert the newly added element next to max element
    node->prev = maxPQ;
    node->next = maxPQ->next;
    maxPQ->next = node;
    // Update max node
    if (maxPQ->data < node->data) {
        return node;
    }
    return maxPQ;
}


template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: insertItem(T data) {
    PQ_Fibonacci <T>* node = newNode(this, data);
    return node;
}

template <typename T>
void PQ_Fibonacci <T> :: dummy() {
    std::cout << "Dummy function" << std::endl;
}


template <typename T>
void PQ_Fibonacci <T> :: printNode(PQ_Fibonacci <T>* node) {
    std::cout << std::endl;
    std::cout << std::setw(10) << std::left << "Data" << ": " << node->data << std::endl;
    std::cout << std::setw(10) << std::left << "Degree" <<": " << node->degree << std::endl;
    std::cout << std::setw(10) << std::left << "ChildCut" << ": " << node->childCut << std::endl;
    std::cout << std::endl;
}

template <typename T>
void PQ_Fibonacci <T>:: printBFS(PQ_Fibonacci <T> * curNode) {
    std::queue <PQ_Fibonacci <T>*> fqueue;
    if (NULL == curNode) {
        return;
    }
    PQ_Fibonacci <T>* firstNode = curNode;
    // Push the root node
    fqueue.push(curNode);
    PQ_Fibonacci <T>* node = curNode;
    while(!fqueue.empty()) {
        printNode(node);
        if (NULL != node->childNode) {
            fqueue.push(node->childNode);
        }
        node = node->next;
        if (node == firstNode) {
            // Take out the topmost node in queue and print the lower levels
            node = fqueue.pop();
            firstNode = node;
        }
    }
}

template <typename T>
void PQ_Fibonacci <T>:: printRecursive(PQ_Fibonacci <T> * curNode) {
    if (NULL == curNode) {
        return;
    }
    printNode(curNode);
    printRecursive(curNode->childNode);
    printRecursive(curNode->next);
}

template <typename T>
void PQ_Fibonacci <T> :: printAllNodes() {
    PQ_Fibonacci <T>* node = this;
    PQ_Fibonacci <T>* firstNode = this;
    while (node) {
        printNode(node);
        if (NULL == node->childNode) {
            node = node->next;
            // A cycle has been completed in the DLL
            if (firstNode == node) {
                break;
            }
        }
        else {
            node = node->childNode;
        }
    }

}

#endif /* FIBONACCIHEAP_H_ */
