#ifndef NODETREE_H
#define NODETREE_H

#include <iostream>
#include <string>


/** Definição do tipo de dados 'byte'
* 'unsigned char': É o tipo que consegue gravar no intervalo que vai de 0 a 255 bytes
*/
typedef unsigned char byte;


using namespace std;

class NodeTree
{
    private:
        int frequencia; 
        byte c;
        string codigo; 
        NodeTree *esquerda;
        NodeTree *direita;
        int tamCodigo; 

    public:
        /**
         * Constructor of the class.
         *
         * @param c byte that will represent the NodeTree.
         * @param frequencia Frequency that this byte happens in the string.
         * @param esquerda NodeTree on the left of the NodeTree been created.
         * @param direita NodeTree on the Right of the NodeTree been created.
         * @returns an instance of a new NodeTree.
         */
        NodeTree(byte c, int frequencia, NodeTree *esquerda, NodeTree *direita);
        
        /**
         * 
         * @returns an instance of a new NodeTree.
         */ 
        NodeTree();

        /**
         * Destructor of the class. 
         */
        ~NodeTree();

        /**
         * Get the frequency the NodeTree happened in the string.
         * 
         * @returns the frequency of the NodeTree.
         */
        int getFrequencia();

        /**
         * Return the byte that represents the NodeTree. Example 'a'.
         * 
         * @returns byte that represents the NodeTree.
         */
        byte getC();

        /**
         * Return the NodeTree on the left of the currently NodeTree.
         * 
         * @returns NodeTree on the left of the currently NodeTree.
         */
        NodeTree* getEsquerda();

        /**
         * Return the NodeTree on the right of the currently NodeTree.
         * 
         * @returns NodeTree on the right of the currently NodeTree.
         */
        NodeTree* getDireita();

        /**
         * Return the code of the NodeTree. For example '0010'.
         * 
         * @return the code of the NodeTree.
         */
        string getCodigo();

        /**
         * Return the lenght of the code. For example 4 in '0010'.
         * 
         * @return lenght of the code.
         */
        int getTamCodigo();

        /**
         * Set the frequency of the NodeTree.
         * 
         * @param frequencia number of times the NodeTree happened in the string.
         */
        void setFrequencia(int frequencia);

        /**
         * Set the char of the NodeTree. For example 'a'.
         * 
         * @param c char of the NodeTree.
         */
        void setC(byte c);

        /**
         * Set the NodeTree on the left of the currently NodeTree.
         * 
         * @param esquerda NodeTree on the left of the currently NodeTree.
         */
        void setEsquerda(NodeTree *esquerda);

        /**
         * Set the NodeTree on the right of the currently NodeTree.
         * 
         * @param direita NodeTree on the right of the currently NodeTree.
         */
        void setDireita(NodeTree *direita);

        /**
         * Set the code of the NodeTree. For example '0010'.
         * 
         * @param s code of the NodeTree.
         */
        void setCodigo(string s);

        /**
         * Set the lenght of the code. For example '4' for '0010'.
         * 
         * @param tam lenght of the code.
         */
        void setTamCodigo(int tam);

        /**
         * Search for the byte wanted inside the currently NodeTree.
         * 
         * @param n NodeTree to start searching for the byte wanted.
         * @param c byte to search for
         * @param buffer 
         * @param tamanho lenght of the code of the NodeTree wanted.
         * @returns true if the 
         */
        bool pegaCodigo(NodeTree *n, byte c, char *buffer, int tamanho);
        
        /**
         * Returns if a NodeTree is a leaf.
         * 
         * @param root NodeTree to look if its a leaf
         * @returns 1 if its a leaf and 0 otherwise
         */
        static int isLeaf(NodeTree* root);

        /**
         * 
         */
        static void printArr(NodeTree* root, int *arr, int n);
        
        /**
         * 
         */
        static void printCodes(NodeTree* root, int *arr, int top);

};

#endif