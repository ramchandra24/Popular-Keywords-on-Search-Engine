#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include <queue>
#include <unordered_map>
#include <iostream>
#include <iomanip>

template <typename T>
class PQ_Fibonacci {
private:
    T data;
    std::string desc; // Description of data - Domain name to be stored here
    unsigned int degree; // Number of nodes rooted at this node
    bool childCut;
    PQ_Fibonacci <T>* childNode; // Pointer to one of the child nodes
    PQ_Fibonacci <T>* parentNode; // Pointer to parent node

    // Pointers for next and previous nodes in doubly linked list
    PQ_Fibonacci <T>* next;
    PQ_Fibonacci <T>* prev;


/* Private function declarations */
    PQ_Fibonacci <T>* newNode(PQ_Fibonacci <T>* maxPQ, T data, std::string desc);
    void combine();

    PQ_Fibonacci <T>* insertNextToMax(PQ_Fibonacci <T>* node);
    PQ_Fibonacci <T>* insertNextToNode(PQ_Fibonacci <T>* node, PQ_Fibonacci <T>* insertNode);
    void removeNodeDLL(PQ_Fibonacci <T>** pNode, PQ_Fibonacci <T>** pChild);
    PQ_Fibonacci <T>* oustNode(PQ_Fibonacci <T>* node);
    void removeNode(PQ_Fibonacci <T>** pNode, PQ_Fibonacci <T>** pChild);
    PQ_Fibonacci <T>* removeMaxNode();

    void updateParentPointers(PQ_Fibonacci <T>* firstChild);
    PQ_Fibonacci <T>* makeSubtree(PQ_Fibonacci <T>* n1, PQ_Fibonacci <T>* n2);
    void printRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode);
    void printNodeDescRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode);
    void updateMaxNode();

/* Public function declarations */
public:
    static PQ_Fibonacci <T>* maxNode; // Pointer to max node in the heap
    PQ_Fibonacci(T data, std::string desc);
    PQ_Fibonacci();
    void insertNode(PQ_Fibonacci <T>* node);
    PQ_Fibonacci <T>* insertItem(T data, std::string desc);
    PQ_Fibonacci <T>* extractMax(PQ_Fibonacci <T>** mNode);

    void printNode(PQ_Fibonacci <T>* node);
    void printNodeDesc(PQ_Fibonacci <T>* node);
    void printAllNodes();
    void printAllNodeDescs();
    void printBFS(PQ_Fibonacci <T> * curNode);
    PQ_Fibonacci <T>* increaseKey(PQ_Fibonacci <T>* node, T newVal);
    PQ_Fibonacci <T>* addToKey(PQ_Fibonacci <T>* node, T addVal);
    T getValue();
    std::string getDesc();
    void setDefaultValues(PQ_Fibonacci <T>** pNode);
    void makeMax();
};

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: maxNode = NULL;

/* Function definitions */
template <typename T>
PQ_Fibonacci <T> :: PQ_Fibonacci() {
    this->data = 0;
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
PQ_Fibonacci <T> :: PQ_Fibonacci(T data, std::string desc) {
    this->data = data;
    this->desc = desc;
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
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: newNode(PQ_Fibonacci <T>* maxPQ, T data, std::string desc) {
    PQ_Fibonacci <T>* node = new PQ_Fibonacci <T>(data, desc);

    // Insert the newly added element next to max element
    node = insertNextToMax(node);
    // Update max node
    if (maxNode->data < node->data) {
        maxNode = node;
    }
    return node;
}


template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: insertItem(T data, std::string desc) {
    PQ_Fibonacci <T>* node = newNode(this, data, desc);
    return node;
}

template <typename T>
void PQ_Fibonacci <T> :: makeMax() {
    maxNode = this;
}

template <typename T>
void PQ_Fibonacci <T> :: printNodeDesc(PQ_Fibonacci <T>* node) {
    if (maxNode == node) {
        std::cout << "**Max node**"<< std::endl;
    }
    std::cout << std::setw(20) << std::left << node->getDesc() << std::endl;
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
    if (node->parentNode) {
        std::cout << std::setw(10) << std::left << "Parent" << ": " << node->parentNode->data << std::endl;
    }
    if (node->childNode) {
        std::cout << std::setw(10) << std::left << "Child-1" << ": " << node->childNode->data << std::endl;
    }
    std::cout << std::setw(10) << std::left << "Next" << ": " << node->next->data << std::endl;
    std::cout << std::setw(10) << std::left << "Prev" << ": " << node->prev->data << std::endl;
    std::cout << std::endl;
}


template <typename T>
void PQ_Fibonacci <T>:: printRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode) {
    if (NULL == curNode) {
        return;
    }
    printNode(curNode);
    printRecursive(curNode->childNode, curNode->childNode);
    // If all nodes in the current level DLL have been printed, return to previous level
    if (firstNode == curNode->next) {
        return;
    }
    printRecursive(firstNode, curNode->next);
}

template <typename T>
void PQ_Fibonacci <T>:: printNodeDescRecursive(PQ_Fibonacci <T>* firstNode, PQ_Fibonacci <T> * curNode) {
    if (NULL == curNode) {
        return;
    }
    printNodeDesc(curNode);
    printNodeDescRecursive(curNode->childNode, curNode->childNode);
    // If all nodes in the current level DLL have been printed, return to previous level
    if (firstNode == curNode->next) {
        return;
    }
    printNodeDescRecursive(firstNode, curNode->next);
}

template <typename T>
void PQ_Fibonacci <T> :: printAllNodeDescs() {
    std::cout << std::endl << "=====Nodes in Fib heap=====" << std::endl;
    if (NULL == maxNode) {
        std::cout << "Heap is empty" << std::endl;
    }
    printNodeDescRecursive(maxNode, maxNode);
}

template <typename T>
void PQ_Fibonacci <T> :: printAllNodes() {
    if (NULL == maxNode) {
        std::cout << "Heap is empty" << std::endl;
    }
    printRecursive(maxNode, maxNode);
}


template <typename T>
void PQ_Fibonacci <T> :: insertNode(PQ_Fibonacci <T>* node) {
    node = insertNextToMax(node);
    // Update maxNode
    if ((NULL == maxNode) || (node->data > maxNode->data)) {
        maxNode = node;
    }
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: insertNextToMax(PQ_Fibonacci <T>* node) {
    // No max
    if (NULL == maxNode) {
        maxNode = node;
        return node;
    }
    // Nothing to insert
    if (NULL == node) {
        return NULL;
    }
    PQ_Fibonacci <T>* maxNext = maxNode->next;
    PQ_Fibonacci <T>* lastInList = node->prev;

    node->parentNode = NULL;
    maxNode->next = node;
    node->prev = maxNode;
    lastInList->next = maxNext;
    maxNext->prev = lastInList;
    return node;
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: insertNextToNode(PQ_Fibonacci <T>* node, PQ_Fibonacci <T>* insertNode) {
    if (NULL == node) {
        return insertNode;
    }
    // Nothing to insert
    if (NULL == insertNode) {
        return node;
    }
    PQ_Fibonacci <T>* nodeNext = node->next;
    PQ_Fibonacci <T>* lastInList = insertNode->prev;

    node->next = insertNode;
    insertNode->prev = node;
    lastInList->next = nodeNext;
    nodeNext->prev = lastInList;

    return node;
}

template <typename T>
void PQ_Fibonacci <T> :: removeNodeDLL(PQ_Fibonacci <T>** pNode, PQ_Fibonacci <T>** pChild) {
    PQ_Fibonacci <T>* tempPrev = (*pNode)->prev;
    PQ_Fibonacci <T>* tempNext = (*pNode)->next;
    tempPrev->next = tempNext;
    tempNext->prev = tempPrev;

    // Update child pointer of parent if necessary
    if ((*pNode)->parentNode) {
        if ((*pNode)->parentNode->childNode == (*pNode)) {
            if (tempNext != (*pNode)) {
                (*pNode)->parentNode->childNode = tempNext;
            }
            // Only child
            else {
                (*pNode)->parentNode->childNode = NULL;
            }
        }
    }
    // Store and return the pointer of childnode of node removed
    *pChild = (*pNode)->childNode;

    // Update data members of node being removed
    setDefaultValues(pNode);
    (*pNode)->childNode = NULL;

    //PQ_Fibonacci <T>* child = node->childNode;
    //delete node;
    //return child;
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
void PQ_Fibonacci <T> :: removeNode(PQ_Fibonacci <T>** pNode, PQ_Fibonacci <T>** pChild) {
    // Remove node from DLL and get pointer to first child node
    //PQ_Fibonacci <T>* child;
    removeNodeDLL(pNode, pChild);
    updateParentPointers(*pChild);
    insertNextToMax(*pChild);
    //return *child;
}

/*
 * Updates max node in the top level list
 * Call after pointing maxNode to one of the top nodes
 */
template <typename T>
void PQ_Fibonacci <T> :: updateMaxNode() {
    PQ_Fibonacci <T>* node = maxNode;
    PQ_Fibonacci <T>* firstNode = maxNode;
    if (NULL == maxNode) {
        return;
    }
    // Only one node present in the heap
    if (maxNode->next == maxNode) {
        maxNode = node;
        return;
    }
    do {
        if (maxNode->data < node->data) {
            maxNode = node;
        }
        node = node->next;
    } while (node != firstNode); // All nodes to be covered once
}

template <typename T>
void PQ_Fibonacci <T> :: setDefaultValues(PQ_Fibonacci <T>** pNode) {
    // Update data members of node being removed
    (*pNode)->childCut = false;
    //(*pNode)->childNode = NULL;
    (*pNode)->parentNode = NULL;
    (*pNode)->degree = 0;
    (*pNode)->next = (*pNode)->prev = *pNode;
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: removeMaxNode() {
    // If node being deleted is max node
    PQ_Fibonacci <T>* maxNextNode = maxNode->next;
    PQ_Fibonacci <T>* dnode = maxNode;
    if (NULL == maxNode) {
        return NULL;
    }

    if (maxNextNode != maxNode) {
        // Update the max node pointer to point to some node
        maxNode = maxNextNode;
    }
    // Only node/tree in heap
    else {
        /* As there are no nodes in the top DLL, there's no need to
         * remove child nodes and plug them in the top DLL.
         * Just make the first level DLL as the main DLL and update max node
         */
        maxNode = maxNode->childNode;
        // Removing only node present in the heap
        if (NULL == maxNode) {
            return dnode;
        }
        // Update parent of new child max node to NULL
        maxNode->parentNode = NULL;
        updateParentPointers(maxNode->next);
        setDefaultValues(&dnode);

        return dnode;
    }
    PQ_Fibonacci <T>* child;
    removeNode(&dnode, &child);
    updateParentPointers(child);
    insertNextToMax(child);
    setDefaultValues(&dnode);
    return dnode;
}



template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: makeSubtree(PQ_Fibonacci <T>* n1, PQ_Fibonacci <T>* n2) {
    PQ_Fibonacci <T>* parentN;
    PQ_Fibonacci <T>* childN;

    //std::cout << "makesubtree : " << n1->data << " " << n2->data << std::endl;
    if (n1->data > n2->data) {
        parentN = n1;
        childN = n2;
    }
    else {
        parentN = n2;
        childN = n1;
    }
    childN = oustNode(childN);
    //printAllNodes();
    parentN->degree = 1 + parentN->degree;//n1->degree + n2->degree;
    PQ_Fibonacci <T>* firstChild = parentN->childNode;
    parentN->childNode = insertNextToNode(childN, firstChild);
    childN->parentNode = parentN;
    //parentN->childNode = childN;
    return parentN;
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: oustNode(PQ_Fibonacci <T>* node) {
    PQ_Fibonacci <T>* tempPrev = node->prev;
    PQ_Fibonacci <T>* tempNext = node->next;
    tempPrev->next = tempNext;
    tempNext->prev = tempPrev;
    if (node->parentNode) {
        if (node->parentNode->childNode == node) {
            if (node != tempNext) {
                node->parentNode->childNode = tempNext;
            }
            // No child left
            else {
                node->parentNode->childNode = NULL;
            }
        }
    }
    node->parentNode = NULL;
    node->childCut = false;
    node->next = node->prev = node;
    return node;
}

template <typename T>
void PQ_Fibonacci <T> :: combine() {
    std::unordered_map<int, PQ_Fibonacci <T>*> degreeMap;

    if (NULL == maxNode) {
        return;
    }
    PQ_Fibonacci <T>* node = maxNode;
    PQ_Fibonacci <T>* exNode;
    PQ_Fibonacci <T>* firstNode = maxNode;
    bool endFlag = true;
    do {
        if (degreeMap.end() != degreeMap.find(node->degree)) {
            std::cout << "found degree : " << node->degree << " " << node->data << std::endl;
            exNode = degreeMap.at(node->degree);
            if (node == exNode) {
                break;
            }
            degreeMap.erase(node->degree);
            node = makeSubtree(node, exNode);
            firstNode = node;
            endFlag = false;
        }
        else {
            degreeMap[node->degree] = node;
            std::cout << "finding degree : " << node->degree << " " << node->data << std::endl;
            //firstNode = node;
            node = node->next;
            //if (firstNode == node) {
            //   break;
            //}
            endFlag = true;
        }
    } while ( (node != firstNode) || (!endFlag) );
}


template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: extractMax(PQ_Fibonacci <T>** mNode) {
    if (NULL == maxNode) {
        *mNode = NULL;
        return NULL;
    }

    std::cout << "before removemax" << std::endl;
    *mNode = removeMaxNode();
    std::cout << "after removemax" << std::endl;
    updateMaxNode();
    std::cout << "after updatemax" << std::endl;
    combine();
    std::cout << "after combine" << std::endl;
    // maxNode will be pointing to the new max in the heap by now
    return maxNode;
}


template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: increaseKey(PQ_Fibonacci <T>* node, T newVal) {

    PQ_Fibonacci <T>* pnode = node->parentNode;
    if (NULL != pnode) {
        node->data = newVal;
        // Parent smaller, possible childcut now
        if (pnode->data < node->data) {
            node = oustNode(node);
            insertNextToMax(node);
            // Update maxNode if necessary
            if (maxNode->data < node->data) {
                maxNode = node;
            }

            // Time for ChildCut action
            while (pnode->childCut) {
                /* Find grandparent and move up until root level
                 * adding all the below subtrees to root level tree
                 */
                PQ_Fibonacci <T>* ppnode = pnode->parentNode;
                pnode = oustNode(pnode);
                pnode->degree -= 1 ;//+ node->degree;
                // No update to max node needed as these values are definitely less
                insertNextToMax(pnode);
                node = pnode;
                pnode = ppnode;
            }
            // Update childCut of the parent
            // If we have reached root level tree, no need to update childCut
            if (NULL != pnode->parentNode) {
                pnode->childCut = true;
            }
            pnode->degree -= 1;
        }
        // else - Nothing to be done
    }
    // Top level node, just update value and max pointer if necessary
    else {
        node->data = newVal;
        if ((maxNode == NULL) || (maxNode->data < node->data)) {
            maxNode = node;
        }
    }
    return maxNode;
}

template <typename T>
PQ_Fibonacci <T>* PQ_Fibonacci <T> :: addToKey(PQ_Fibonacci <T>* node, T addVal) {

    T curVal = node->data;
    return (node->increaseKey(node, curVal+addVal));
}

template <typename T>
T PQ_Fibonacci <T> :: getValue() {
    return this->data;
}

template <typename T>
std::string PQ_Fibonacci <T> :: getDesc() {
    return this->desc;
}

#endif /* FIBONACCIHEAP_H_ */
