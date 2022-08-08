#ifndef NODEQUEUE_H
#define NODEQUEUE_H

#include <iostream>
#include "NodeTree.h"

using namespace std;

class NodeQueue
{
    private:
        NodeTree *n;
        NodeQueue *proximo;

    public:
        /**
         * Constructor of the class.
         * @param n NodeTree to be inserted as the first element of the NodeQueue
         */
        NodeQueue(NodeTree *n);

        /**
         * Destructor of the class. 
         */
        ~NodeQueue();

        /**
         * Returns the currently NodeTree.
         * 
         * @returns NodeTree
         */
        NodeTree* getN();

        /**
         * Returns the next NodeTree.
         * 
         * @returns NodeQueue
         */
        NodeQueue* getProximo();

        /**
         * Set the currently NodeTree
         * 
         * @param n NodeTree 
         */
        void setN(NodeTree *n);

        /**
         * Set the next NodeQueue
         * 
         * @param proximo NodeQueue
         */
        void setProximo(NodeQueue *proximo);

};

#endif