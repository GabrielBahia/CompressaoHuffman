#include <iostream>
#include <sstream>
#include <string>
#include "math.h"
#include "PriorityQueue.h"
#include "NodeQueue.h"
#include "NodeTree.h"

using namespace std;

// Construtor of the PriorityQueue
PriorityQueue::PriorityQueue(NodeQueue *head)
{
    this->head = head;
    this->elementos = 0;
}

// Destrutor of the PriorityQueue
PriorityQueue::~PriorityQueue()
{
    
}

NodeQueue* PriorityQueue::getHead()
{
    return this->head;
}

int PriorityQueue::getNumElementos()
{
    return this->elementos;
}


void PriorityQueue::setHead(NodeQueue *head)
{
    this->head = head;
}

void PriorityQueue::setNumElementos(int elementos)
{
    this->elementos = elementos;
}

NodeTree* PriorityQueue::getChar(byte c)
{
    cout << "CHEGOU AQUI " << endl;
    for(NodeQueue *aux = this->head; aux->getProximo() != NULL; aux = aux->getProximo())
    {
        cout << "aux->getN()->getC() :" << aux->getN()->getC() << endl;
        if(aux->getN()->getC() == c)
        {   
            return aux->getN();
        }
    }

    return NULL;
}




/** Função que insere um novo nó na lista encadeada que representa a fila de prioridade.
* @param: um nó previamente criado
*/
void PriorityQueue::insertQueue(NodeQueue *n)
{
    // Se a lista passada como parâmetro não tem um nó no início (vazia), insira o nó no início
    if (!this->head)
    {
        this->head = n;
    }

    // Se o campo 'frequência' do 'nó' parâmetro for menor que o campo 'frequência' do primeiro item (head)
    // da lista, incluir o novo nó como head, e colocar o head antigo como next desse novo
    else if (n->getN()->getFrequencia() < this->head->getN()->getFrequencia())
    {
        n->setProximo(this->head);
        this->head = n;
    }
    else
    {
        // nó auxiliar que inicia apontando para o segundo nó da lista (head->proximo)
        NodeQueue *aux = this->head->getProximo();
        // nó auxiliar que inicia apontando para o primeiro nó da lista
        NodeQueue *aux2 = this->head;

        // Laço que percorre a lista e insere o nó na posição certa de acordo com sua frequência.
        //
        // Se sabe que aux começa apontando para o segundo item da lista e aux2 apontando para o primeiro.
        // Sendo assim, os ponteiros seguirão mudando de posição enquanto aux não for o fim da lista,
        // e enquanto a frequência do nó apontado por aux for menor ou igual a frequência do 'nó' parâmetro.
        while (aux && aux->getN()->getFrequencia() <= n->getN()->getFrequencia())
        {
            aux2 = aux;
            aux = aux2->getProximo();
        }

        // Se insere o nó na posição certa.
        aux2->setProximo(n);
        n->setProximo(aux);
    }

    // Incrementa quantidade de elementos
    this->elementos++;
}


/** Função que 'solta' o nó apontado por 'head' da lista (o de menor frequência)
* (faz backup do nó e o desconecta da lista)
*/
NodeTree* PriorityQueue::popMinLista()
{

    // Ponteiro auxilar que aponta para o primeiro nó da lista
    NodeQueue *aux = this->head;

    // Ponteiro auxiliar que aponta para a árvore contida em aux (árvore do primeiro nó da lista)
    NodeTree *aux2 = aux->getN();

    // Aponta o 'head' da lista para o segundo elemento dela
    this->head = aux->getProximo();

    // Libera o ponteiro aux
    free(aux);
    aux = NULL;

    // Decrementa a quantidade de elementos
    this->elementos--;

    return aux2;
}