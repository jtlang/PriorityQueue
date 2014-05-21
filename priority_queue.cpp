#include "priority_queue.h"
#include <vector>

template <class T>
PriorityQueue<T>::PriorityQueue():root(NULL){}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue & other):
    root(copy(other.root)) {}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    clear();
}

template <class T>
const PriorityQueue<T> & PriorityQueue<T>::operator=(const PriorityQueue<T> & rhs)
{
    if(this != &rhs)
    {
        clear();
        root = copy(rhs.root);
    }
    return *this;
}

template <class T>
typename PriorityQueue<T>:: Node* PriorityQueue<T>::copy(const Node* subRoot)
{
    if(subRoot == NULL)
        return NULL;

    // Copy node's element
    Node * newNode = new Node(subRoot->elem);
    
    // Copy children of node
    newNode->child = copy(subRoot->child);
    if(newNode->child != NULL)
        newNode->child->prev = newNode;

    // Copy node's sibilngs    
    newNode->next = copy(subRoot->next);
    if(newNode->next != NULL)
        newNode->next->prev = newNode;
    
    return newNode;
}

template <class T>
void PriorityQueue<T>::clear()
{
    clear(root);
    root = NULL;
}

template <class T>
void PriorityQueue<T>::clear(Node* subRoot)
{
    if(subRoot != NULL)
    {
        clear(subRoot->child);
        clear(subRoot->next);
        delete subRoot;
    }
}

template <class T>
void PriorityQueue<T>::insert(const T & value)
{
    Node* newNode = new Node(value);

    if(isEmpty())
        root = newNode;
    else
        meld(root, newNode);

    //return newNode;
}

template <class T>
T PriorityQueue<T>::pop()
{
    if(isEmpty())
        return T();
    
    // Hold the value to be returned
    T retVal = top();

    // Restructure heap
    Node* oldRoot = root;
    if(root->child == NULL)
        root = NULL;
    else
        root = meldSiblings(root->child);
    delete oldRoot;
    
    return retVal;
}

template <class T>
const T & PriorityQueue<T>::top() const
{
    return root->elem;
}

template <class T>
bool PriorityQueue<T>::isEmpty() const
{
    return root == NULL;
}

template <class T>
void PriorityQueue<T>::meld(Node* & first, Node* second)
{
    if(second != NULL) 
    {
        //
        if(first->elem > second->elem)
        {
            second->prev = first;
            first->next = second->next;
            if(first->next != NULL)
                first->next->prev = first;
            second->next = first->child;
            if(second->next != NULL)
                second->next->prev = second;
            first->child = second;            
        }
        else
        {
            second->prev = first->prev;
            first->prev = second;
            first->next = second->child;
            if(first->next != NULL)
                first->next->prev = first;
            second->child = first;
            first = second;
        }
    }
}

template <class T>
typename PriorityQueue<T>::Node* PriorityQueue<T>::meldSiblings(Node* first)
{
    if(first->next == NULL)
        return first;

    static std::vector< Node* > heapArray(4);

    int numSibs = 0;
    while(first != NULL)
    {
        if(numSibs == heapArray.size())
            heapArray.resize(numSibs * 2);
        heapArray[numSibs] = first;
        first->prev->next = NULL;
        first = first->next;
        numSibs++;
    }
    if(numSibs == heapArray.size())
        heapArray.resize(numSibs + 1);
    heapArray[numSibs] = NULL;

    int i = 0;
    for( ; i < numSibs - 1; i += 2)
        meld(heapArray[i], heapArray[i + 1]);

    int j = i - 2;

    if(j == numSibs - 3)
        meld(heapArray[j], heapArray[j + 2]);

    for( ; j >= 2; j -= 2)
        meld(heapArray[j - 2], heapArray[j]);

    return heapArray[0];

}
