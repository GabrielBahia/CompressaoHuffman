#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <iostream>
#include "NodeTree.h"
#include "NodeQueue.h"
#include "PriorityQueue.h"

using namespace std;

class HuffmanCoding
{
    private:
        
    public:

    void FreeHuffmanTree(NodeTree *n);
    float calculaTaxaCompressao(int qtdCharAntigo, int qtdCharNovo);
    void getByteFrequency(FILE *entrada, unsigned int *listaBytes, int *contChar);
    NodeTree *BuildHuffmanTree(unsigned *listaBytes, PriorityQueue *l, PriorityQueue *l2, int *tamL);
    int isLeaf(NodeTree* root);
    void PercorreTree(NodeTree *root, char c, NodeTree *encontrado, bool *verifica);
    void montaTabelaFreq(unsigned listaBytes[]);
    void montaCodigos(NodeTree *root, PriorityQueue *l2);
    int calculaTamanhoCod(NodeTree *root, unsigned listaBytes[], PriorityQueue *l2);
    void codificacaoBinaria(FILE *entrada, string *codigoBin, int tam, PriorityQueue *l2);
    void codificacaoAscii(string *codigoBin, int tam, string *codigoAscii, int *binaryStartWithZero);
    NodeTree *CompressFile(int *binaryStartWithZero);
    string Decode(); 
    void binaryIntoWord(string binaryFull, NodeTree *root);
};

#endif