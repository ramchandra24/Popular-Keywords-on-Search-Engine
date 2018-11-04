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
    void combine();

    PQ_Fibonacci <T>* insertNextToMax(PQ_Fibonacci <T>* node);
    PQ_Fibonacci <T>* removeNodeDLL(PQ_Fibonacci <T>* node);
    PQ_Fibonacci <T>* removeNode(PQ_Fibonacci <T>* node);
    PQ_Fibonacci <T>* removeMaxNode();
    void updateMaxNode();
    void updateParentPointers(PQ_Fibonacci <T>* firstChild);

/* Public function declarations */
public:
    static PQ_Fibonacci <T>* maxNode; // Pointer to max node in the heap
    PQ_Fibonacci(T data);
    PQ_Fibonacci <T>* insertItem(T data);
    PQ_Fibonacci <T>* extractMax();


    void dummy();
    void printNode(PQ_Fibonacci <T>* node);
    void printAllNodes();
    void printRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode);
    void printBFS(PQ_Fibonacci <T> * curNode);
};

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: maxNode = NULL;

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

    // Update maxNode on first item insert
    if (NULL == maxNode) {
        maxNode = this;
    }
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: newNode(PQ_Fibonacci <T>* maxPQ, T data) {
    PQ_Fibonacci <T>* node = new PQ_Fibonacci <T>(data);

    // Insert the newly added element next to max element
    node = insertNextToMax(node);
    // Update max node
    if (maxNode->data < node->data) {
        maxNode = node;
    }
    return node;
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
    if (maxNode == node) {
        std::cout << "**Max node**"<< std::endl;
    }
    std::cout << std::setw(10) << std::left << "Data" << ": " << node->data << std::endl;
    std::cout << std::setw(10) << std::left << "Degree" <<": " << node->degree << std::endl;
    std::cout << std::setw(10) << std::left << "ChildCut" << ": " << node->childCut << std::endl;
    std::cout << std::setw(10) << std::left << "Next" << ": " << node->next->data << std::endl;
    std::cout << std::setw(10) << std::left << "Prev" << ": " << node->prev->data << std::endl;
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
void PQ_Fibonacci <T>:: printRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode) {
    if (NULL == curNode) {
        return;
    }
    printNode(curNode);
    // If all nodes in the current level DLL have been printed, return to previous level
    if (firstNode == curNode->next) {
        return;
    }
    printRecursive(curNode->childNode, curNode->childNode);
    printRecursive(firstNode, curNode->next);
}

template <typename T>
void PQ_Fibonacci <T> :: printAllNodes() {
    printRecursive(maxNode, maxNode);
}

template <typename T>
void PQ_Fibonacci <T> :: combine() {
    printRecursive(this, this);
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: insertNextToMax(PQ_Fibonacci <T>* node) {
    // Nothing to insert
    if (NULL == node) {
        return NULL;
    }
    PQ_Fibonacci <T>* maxNext = maxNode->next;
    PQ_Fibonacci <T>* lastInList = node->prev;

    maxNode->next = node;
    node->prev = maxNode;
    lastInList->next = maxNext;
    maxNext->prev = lastInList;
    return node;
}



template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: removeNodeDLL(PQ_Fibonacci <T>* node) {
    PQ_Fibonacci <T>* tempPrev = node->prev;
    PQ_Fibonacci <T>* tempNext = node->next;
    tempPrev->next = tempNext;
    tempNext->prev = tempPrev;

    // Update child pointer of parent if necessary
    if (node->parentNode) {
        if (node->parentNode->childNode == node) {
            if (tempNext != node) {
                node->parentNode->childNode = tempNext;
            }
            // Only child
            else {
                node->parentNode->childNode = NULL;
            }
        }
    }
    PQ_Fibonacci <T>* child = node->childNode;
    delete node;
    return child;
}



template <typename T>
void PQ_Fibonacci <T> :: updateParentPointers(PQ_Fibonacci <T>* firstChild) {
    PQ_Fibonacci <T>* node = firstChild;
    // No child nodes
    if (NULL == firstChild) {
        return;
    }
    do {
        node->parentNode = NULL;
        node = node->next;
    } while (node != firstChild);
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: removeNode(PQ_Fibonacci <T>* node) {
    // Remove node from DLL and get pointer to first child node
    PQ_Fibonacci <T>* child = removeNodeDLL(node);
    updateParentPointers(child);
    insertNextToMax(child);
    return child;
}

/*
 * Updates max node in the top level list
 * Call after pointing maxNode to one of the top nodes
 */
template <typename T>
void PQ_Fibonacci <T> :: updateMaxNode() {
    PQ_Fibonacci <T>* node = maxNode;
    PQ_Fibonacci <T>* firstNode = maxNode;
    do {
        if (maxNode->data < node->data) {
            maxNode = node;
        }
        node = node->next;
    } while (node != firstNode); // All nodes to be covered once
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: removeMaxNode() {
    // If node being deleted is max node
    PQ_Fibonacci <T>* maxNextNode = maxNode->next;
    PQ_Fibonacci <T>* dnode = maxNode;
    if (maxNextNode != maxNode) {
        maxNode = maxNextNode;
    }
    // Only node in heap
    else {
        maxNode = NULL;
    }
    PQ_Fibonacci <T>* child = removeNode(dnode);
    updateParentPointers(child);
    insertNextToMax(child);
    return child;
}


template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: extractMax() {
    removeMaxNode();
    std::cout << "printing extra" ;
    printAllNodes();
    updateMaxNode();
//    combine();
    return NULL;
}



#endif /* FIBONACCIHEAP_H_ */
