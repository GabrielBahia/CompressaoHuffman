#include <iostream>
#include <sstream>
#include <string>
#include "math.h"
#include "NodeQueue.h"
#include "NodeTree.h"



using namespace std;

// Construtor of the NodeQueue
NodeQueue::NodeQueue(NodeTree *n)
{
    this->n = n;
    this->proximo = NULL;
}

// Destrutor of the NodeQueue
NodeQueue::~NodeQueue()
{
    
}

NodeTree* NodeQueue::getN()
{
    return this->n;
}

NodeQueue* NodeQueue::getProximo()
{
    return this->proximo;
}

void NodeQueue::setN(NodeTree *n)
{
    this->n = n;
}
        
void NodeQueue::setProximo(NodeQueue *proximo)
{
    this->proximo = proximo;
}









