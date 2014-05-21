/**
 * @file priority_queue.h
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

/**
 * Implements the max priority queue ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */
template <class T>
class PriorityQueue
{
    private:
    struct Node
    {
        T elem;
        Node* child;
        Node* prev;
        Node* next;

        Node(const T & element):
            elem(element), child(NULL), prev(NULL), next(NULL) {}
    };

    public:
        /**
         * Constructor: creates an empty priority queue.
         */
        PriorityQueue();

        /**
         * Copy constructor
         */
        PriorityQueue(const PriorityQueue & other);
        
        /**
         * Destructor
         */
        ~PriorityQueue();

        /**
         * Assignment operator
         */
        const PriorityQueue & operator=(const PriorityQueue & rhs);

        /**
         * Frees all memory and sets Queue to be empty 
         */
        void clear();

        /**
         * Inserts the given value into the queue.
         *
         * @param value The value to be inserted.
         */
        void insert(const T & value);

        /**
         * Removes the highest value (and its associated data) from the
         *  queue.
         *
         * @return A copy of the removed (maximum) element
         */
        T pop();

        /**
         * Returns the highest value from the queue. Does NOT remove it.
         *
         * @return A copy of the maximum element
         */
        const T & top() const;

        /**
         * Determines if the queue is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the queue is
         *  empty.
         */
        bool isEmpty() const;

    private:
        Node* root;

        /*
         * Copies the pairing heap rooted at subRoot.
         *  @return The root of the new heap.
         */
        Node* copy(const Node* subRoot);
        
        /*
         * Frees memory of the pairing heap rooted at subRoot
         */
        void clear(Node* subRoot);

        /* 
         * Combines two pairing heaps rooted at first and second into
         *  a larger pairing heap rooted at first.
         *  @param first cannot be NULL
         */
        void meld(Node* & first, Node* second);

        /*
         * Two-pass merges siblings
         * @param first is the leftmost child
         */
        Node* meldSiblings(Node* first);
};

#include "priority_queue.cpp"
#endif
