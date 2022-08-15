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
        static float taxaDeCompressao(int lengthOfTheOriginalString, int lengthOfTheCompressedMessage);
        static string codificacaoBinaria(FILE *entrada, PriorityQueue *l2);
        static string binaryIntoWord(string binaryFull, NodeTree *root);
        static void escrevendoArqBin(string *codigoBin, int tam, int *numberOfZerosAtTheEnd, bool *notDivisibleByEight);
        static void montaCodigo(NodeTree *root, unsigned listaBytes[], PriorityQueue *l2);
        static void montaCodigoAux(NodeTree *root, PriorityQueue *l2);
        //static void montaTabelaFreq(unsigned listaBytes[]);
        static void percorreTree(NodeTree *root, char c, NodeTree *encontrado, bool *verifica);
        static int isLeaf(NodeTree *root);
        static NodeTree* buildHuffmanTree(unsigned *listaBytes, PriorityQueue *l2);
        static void freeHuffmanTree(NodeTree *n);
        static void getByteFrequency(FILE *entrada, unsigned listaBytes[]);
        static void montaTabelaFreq(unsigned listaBytes[]);
        static string decompressFile(int numberOfZerosAtTheEnd, bool notDivisibleByEight);
        static string compressFile(char *entrada);
};

#endif