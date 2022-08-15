#include <iostream>
#include <sstream>
#include <string>
#include "math.h"
#include "NodeTree.h"


using namespace std;


// Construtor of the NodeTree
NodeTree::NodeTree(byte c, int frequencia, NodeTree *esquerda, NodeTree *direita)
{
    this->c = c;
    this->frequencia = frequencia;
    this->esquerda = esquerda;
    this->direita = direita;
    this->codigo = "";
    this->tamCodigo = 0;
}

// Construtor of the NodeTree
NodeTree::NodeTree()
{   
    this->c = '!';
    this->frequencia = 0;
    this->esquerda = NULL;
    this->direita = NULL;
    this->codigo = "";
    this->tamCodigo = 0;
}




// Destrutor of the NodeTree
NodeTree::~NodeTree()
{
   
}

int NodeTree::getFrequencia()
{
    return this->frequencia;
}

byte NodeTree::getC()
{
    return this->c;
}

NodeTree* NodeTree::getEsquerda()
{
    return this->esquerda;
}

NodeTree* NodeTree::getDireita()
{
    return this->direita;
}

string NodeTree::getCodigo()
{
    return this->codigo;
}

int NodeTree::getTamCodigo()
{
    return this->tamCodigo;
}

void NodeTree::setFrequencia(int frequencia)
{
    this->frequencia = frequencia;
}

void NodeTree::setC(byte c)
{
    this->c = c;
}

void NodeTree::setEsquerda(NodeTree *esquerda)
{
    this->esquerda = esquerda;
}

void NodeTree::setDireita(NodeTree *direita)
{
    this->direita = direita;
}

void NodeTree::setCodigo(string s)
{
    this->codigo = s;
    int tam = s.length() * getFrequencia();
    setTamCodigo(tam);
}

void NodeTree::setTamCodigo(int tam)
{
    this->tamCodigo = tam;
}


//  Obtem o código começando no nó n, utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket 'tamanho'

/**
/ Função recursiva que percorre uma árvore de huffman e para ao encontrar o byte procurado (c)
/ @param: nó para iniciar a busca, byte a ser buscado, buffer para salvar os nós percorridos, posição para escrever
**/


// Utility function to check if this node is leaf
int NodeTree::isLeaf(NodeTree* root)
{
    return !(root->getEsquerda()) && !(root->getDireita());
}

void NodeTree::setCodesAux(NodeTree *root, int *arr, int n)
{
    int i;
    string aux = "";
    for (i = 0; i < n; ++i)
    {
        aux = aux + to_string(arr[i]);
        //cout<< arr[i];
    }
  
    //cout<<"\n";
    root->setCodigo(aux);
}


void NodeTree::setCodes(NodeTree* root, int *arr, int top)
{
    // Assign 0 to left edge and recur
    if (root->getEsquerda()) 
    {
        arr[top] = 0;
        setCodes(root->getEsquerda(), arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->getDireita()) 
    {
        arr[top] = 1;
        setCodes(root->getDireita(), arr, top + 1);
    }
 
    if (isLeaf(root)) {
        //cout<< root->getC()<<": ";
        setCodesAux(root, arr, top);
    }
}


bool NodeTree::pegaCodigo(NodeTree *n, byte c, char *buffer, int tamanho)
{

    // Caso base da recursão:
    // Se o nó for folha e o seu valor for o buscado, colocar o caractere terminal no buffer e encerrar

    if (!(n->getEsquerda() || n->getDireita()) && n->getC() == c)
    {
        buffer[tamanho] = '\0';
        return true;
    }
    else
    {
        bool encontrado = false;

        // Se existir um nó à esquerda
        if (n->getEsquerda())
        {
            // Adicione '0' no bucket do buffer correspondente ao 'tamanho' nodeAtual
            buffer[tamanho] = '0';

            // fazer recursão no nó esquerdo
            encontrado = pegaCodigo(n->getEsquerda(), c, buffer, tamanho + 1);
        }

        if (!encontrado && n->getDireita())
        {
            buffer[tamanho] = '1';
            encontrado = pegaCodigo(n->getDireita(), c, buffer, tamanho + 1);
        }
        if (!encontrado)
        {
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }

}







