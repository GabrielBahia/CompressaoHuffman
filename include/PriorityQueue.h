#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "NodeQueue.h"
#include "NodeTree.h"


using namespace std;

class PriorityQueue
{
    private:
    NodeQueue *head;
    int elementos;

    public:
        /**
         * Constructor of the class.
         *
         * @param head nodeQueue to be inserted as the head of the PriorityQueue(first NodeQueue)
         * @returns instance of a PriorityQueue
         */
        PriorityQueue(NodeQueue *head);

        /**
         * Destructor of the class. 
         */
        ~PriorityQueue();

        /**
         * Get the first NodeQueue of the PriorityQueue 
         * 
         * @returns first NodeQueue
         */
        NodeQueue* getHead();

        /** 
         * Get the number of elements of the PriorityQueue 
         * 
         * @returns the number of elements in the PriorityQueue
        */
        int getNumElementos();

        /**
         * Set the first element [0] of the PriorityQueue 
         * 
         * @param head nodeQueue to be inserted as the head of the PriorityQueue(first NodeQueue)
         */
        void setHead(NodeQueue *head);
        
        /**
         * Set the number of elements of the PriorityQueue
         * 
         * @param elements number of elements inside the PriorityQueue
         */
        void setNumElementos(int elementos);

        /**
         * Get the char we're searching. Example: 'a'
         * 
         * @param c byte to be searched in the PriorityQueue
         * @returns the NodeTree with the byte searched
         */
        NodeTree* getChar(byte c);
        
        /**
         * Insert a new NodeQueue in the PriorityQueue
         * 
         * @param n NodeQueue to be inserted in the PriorityQueue
         */
        void insertQueue(NodeQueue *n);

        /**
         * Remove the node with the less frequency in the PriorityQueue
         * 
         * @returns NodeTree
         */  
        NodeTree* popMinLista();
};

#endif