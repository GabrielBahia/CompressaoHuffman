#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <fstream>
#include "NodeQueue.h"
#include "PriorityQueue.h"
#include "NodeTree.h"
#include "HuffmanCoding.h"
#include <algorithm>

//#include <bits/stdc++.h>

typedef unsigned char byte;

/** Função que libera memória da árvore de huffman
 * @param: nó de uma (sub)árvore.
 */
void HuffmanCoding::freeHuffmanTree(NodeTree *n)
{
    // Caso base da recursão, enquanto o nó não for NULL
    if (!n)
        return;
    else
    {
        NodeTree *esquerda = n->getEsquerda();
        NodeTree *direita = n->getDireita();
        delete n;
        freeHuffmanTree(esquerda);
        freeHuffmanTree(direita);
    }
}

// Funcao que cria a frequencia de cada caractere utilizado da tabela ascii
void HuffmanCoding::getByteFrequency(FILE *entrada, unsigned int *listaBytes)
{
    byte c;
    while (fread(&c, 1, 1, entrada) >= 1)
    {
        listaBytes[(byte)c]++;
    }
    rewind(entrada); // "rebobina o arquivo"
}

/** Função que constrói a árvore de huffman
 * @param: a fila de prioridade.
 */
NodeTree *HuffmanCoding::buildHuffmanTree(unsigned *listaBytes, PriorityQueue *l2)
{
    PriorityQueue *l = new PriorityQueue(NULL); // Lista onde será pego os nodes para montar a árvore de huffman(Essa lista ficará vazia após montar a árvore)
    // Popula usando a array 'listaBytes' (que contém as frequências) uma lista encadeada de nós.
    // Cada nó contém uma árvore.
    for (int i = 0; i < 256; i++)
    {
        if (listaBytes[i]) // Se existe ocorrência do byte
        {
            // Insere na lista 'l' um nó referente ao byte i e sua respectiva frequência (guardada em listaBytes[i]).
            // Faz os nós esquerdo e direito das árvores apontarem para NULL;
            NodeTree *noT = new NodeTree(i, listaBytes[i], NULL, NULL);
            NodeQueue *noQ = new NodeQueue(noT);
            l->insertQueue(noQ); // Lista que sera usada para construir a arvore

            NodeTree *noTAux = new NodeTree(i, listaBytes[i], NULL, NULL);
            NodeQueue *noQAux = new NodeQueue(noTAux);
            l2->insertQueue(noQAux); // Lista auxiliar para consultas
        }
    }
    while (l->getNumElementos() > 1) // Enquanto o número de elementos da lista for maior que 1
    {
        // Nó esquerdo chama a função popMinLista() que vai na lista e pega a árvore fixada no primeiro nó
        // (que é a que contém a menor frequência)
        NodeTree *nodeEsquerdo = l->popMinLista();
        // Pega o outro nó que tem menor frequência
        NodeTree *nodeDireito = l->popMinLista();
        // Preenche com '#' o campo de caractere do nó da árvore.
        // Preenche o campo 'frequência' com a soma das frequências de 'nodeEsquerdo' e 'nodeDireito'.
        // Aponta o nó esquerdo para nodeEsquerdo e o nó direito para nodeDireito
        NodeTree *soma = new NodeTree('#', nodeEsquerdo->getFrequencia() + nodeDireito->getFrequencia(), nodeEsquerdo, nodeDireito);
        // Reinsere o nó 'soma' na lista l
        NodeQueue *noQ2 = new NodeQueue(soma);
        l->insertQueue(noQ2);
    }

    NodeTree *root = l->popMinLista();
    int *arr = new int;
    int top = 0;
    NodeTree::setCodes(root, arr, top); // Monta a codificação individual de cada palavra
    montaCodigo(root, listaBytes, l2);  // Monta a codificacao correta na Lista l2(Lista auxilar dos nodes da arvore)
    
    // retorna a raiz da arvore
    return root;
}

// Função auxiliar para percorrer a árvore que verifica se a node é folha(se for folha é um caractere)
int HuffmanCoding::isLeaf(NodeTree *root)
{
    return !(root->getEsquerda()) && !(root->getDireita());
}

// Função para percorrer a árvore de Huffman recursivamente para encontrar o node que possui a chave c e faz uma copia desse node(encontrado) para ser utilizado na L2(lista auxiliar)
void HuffmanCoding::percorreTree(NodeTree *root, char c, NodeTree *encontrado, bool *verifica)
{
    if (*verifica == false)
    {
        if (root->getEsquerda())
        {
            percorreTree(root->getEsquerda(), c, encontrado, verifica);
        }

        if (root->getDireita())
        {
            percorreTree(root->getDireita(), c, encontrado, verifica);
        }

        if (isLeaf(root))
        {
            if (root->getC() == c)
            {
                encontrado->setC(root->getC());
                encontrado->setCodigo(root->getCodigo());
                encontrado->setFrequencia(root->getFrequencia());
                encontrado->setDireita(root->getDireita());
                encontrado->setEsquerda(root->getEsquerda());
                encontrado->setTamCodigo(root->getTamCodigo());
                *verifica = true;
            }
        }
    }
}

// Função que monta a tabela de frequecia
/*void HuffmanCoding::montaTabelaFreq(unsigned listaBytes[])
{
    for (int i = 0; i < 256; i++)
    {
        if (listaBytes[i] != 0)
        {
            cout << char(i) << " : " << listaBytes[i] << endl;
        }
    }
}*/

// Função auxiliar do montaCodigo
void HuffmanCoding::montaCodigoAux(NodeTree *root, PriorityQueue *l2)
{
    for (NodeQueue *aux = l2->getHead(); aux != NULL; aux = aux->getProximo())
    {
        NodeTree *aux2 = aux->getN();
        if (aux2->getC() == root->getC())
        {
            aux2->setCodigo(root->getCodigo());
            aux2->setTamCodigo(root->getTamCodigo());
            return;
        }
    }
}
// Função que atualiza a lista auxiliar l2 com os valores da codificação de cada node
void HuffmanCoding::montaCodigo(NodeTree *root, unsigned listaBytes[], PriorityQueue *l2)
{
    for (int i = 0; i < 256; i++)
    {
        if (listaBytes[i] != 0)
        {
            byte c = (char)i;
            bool verifica = false;
            NodeTree *encontrado = new NodeTree();
            percorreTree(root, c, encontrado, &verifica);
            montaCodigoAux(encontrado, l2);
            delete encontrado;
        }
    }
}

// Função que faz a codificação da entrada inteira utilizando a lista auxiliar l2 para consultar o codigo de cada letra
string HuffmanCoding::codificacaoBinaria(FILE *entrada, PriorityQueue *l2)
{
    byte c;
    string codigoBin;
    while (fread(&c, 1, 1, entrada) >= 1)
    {
        for (NodeQueue *aux = l2->getHead(); aux != NULL; aux = aux->getProximo())
        {
            NodeTree *aux2 = aux->getN();
            if (aux2->getC() == c)
            {
                codigoBin = codigoBin + aux2->getCodigo();
            }
        }
    }

    return codigoBin;
}

// Função que escreve a codificação no arquivo binário
void HuffmanCoding::escrevendoArqBin(string *codigoBin, int tam, int *numberOfZerosAtTheEnd, bool *notDivisibleByEight)
{
    fstream file("ArqBin.bin", ios::binary | ios::out);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo";
        exit(1);
    }

    int cont = 0;
    string str_bin = "";
    int i_bin;

    if ((tam % 8) != 0)
    {
        *notDivisibleByEight = true;
    }

    while (cont < tam)
    {
        for (int i = cont; i < (cont + 8) && i < tam; i++)
        {
            str_bin = str_bin + (*codigoBin).at(i);
            if (i >= codigoBin->length() - 8)
            {
                if (notDivisibleByEight)
                {
                    if (i == cont)
                    {
                        if (str_bin[0] == '0')
                        {
                            (*numberOfZerosAtTheEnd)++;
                            bool flag = false;
                            if (i + 8 >= codigoBin->length())
                            {
                                while (i + 1 < codigoBin->length() && ((*codigoBin).at(i + 1) == '0'))
                                {
                                    i++;
                                    (*numberOfZerosAtTheEnd)++;
                                }
                            }
                            else
                            {
                                while ((i < (cont + 8)) && ((*codigoBin).at(i) == '0'))
                                {
                                    flag = true;
                                    i++;
                                    (*numberOfZerosAtTheEnd)++;
                                }
                            }
                        }
                    }
                }
            }
        }
        i_bin = stoi(str_bin, nullptr, 2);

        str_bin = "";
        file.write((char *)&i_bin, sizeof(char));
        cont += 8;
    }
}

// Função que transforma a codificação binária em texto novamente
string HuffmanCoding::binaryIntoWord(string binaryFull, NodeTree *root)
{
    string wordDecoded = "";
    NodeTree *aux = root;
    bool flag;
    int numberOfFlags = -1;
    for (int i = 0; i < binaryFull.length(); i++)
    {
        if (!NodeTree::isLeaf(aux))
        {
            if (binaryFull[i] == '0')
            {
                aux = aux->getEsquerda();
            }
            else
            {
                aux = aux->getDireita();
            }
        }
        if (NodeTree::isLeaf(aux))
        {
            wordDecoded += aux->getC();
            aux = root;
        }
    }

    return wordDecoded;
    //cout << "Palavra utilizada: " << wordDecoded << endl;
}

//
string HuffmanCoding::decompressFile(int numberOfZerosAtTheEnd, bool notDivisibleByEight)
{
    fstream file("ArqBin.bin", ios::in | ios::out | ios::binary);
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    file.seekg(0, file.end);         // posiciona o ponteiro no final do arquivo
    int fileSize = file.tellg() / 1; // pega o tamanho do arquivo e divide pelo tamanho de cada estudante para saber o total
    file.seekg(0, file.beg);         // posiciona o ponteiro no final do arquivo
    string binaryFull = "";
    for (int i = 0; i < fileSize; i++)
    {
        int integerCode;
        file.read((char *)&integerCode, sizeof(char));
        string integerAsBinary = "";
        if (integerCode == 0)
        {
            integerAsBinary = "0";
        }
        else
        {
            while (integerCode > 0)
            {
                integerAsBinary += to_string((integerCode % 2));
                integerCode = integerCode / 2;
            }
        }
        if (i < fileSize - 1)
        {
            if (integerAsBinary.length() < 8)
            {
                while (integerAsBinary.length() < 8)
                {
                    integerAsBinary += '0';
                }
            }
        }
        else
        {
            if (notDivisibleByEight)
            {
                for (int j = 0; j < numberOfZerosAtTheEnd; j++)
                {
                    integerAsBinary += '0';
                }
            }
        }
        reverse(integerAsBinary.begin(), integerAsBinary.end());
        binaryFull += integerAsBinary;
    }
    return binaryFull;
}

/** Função que comprime um arquivo utilizando a compressão de huffman
 * @param: arquivo a comprimir, arquivo resultado da compressão
 */
string HuffmanCoding::compressFile(char *entrada)
{
    string codigoBin;

    FILE *arq;
    // Abre um arquivo TEXTO para LEITURA
    arq = fopen(entrada, "r");
    if (arq == NULL) // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return nullptr;
    }

    unsigned listaBytes[256] = {0};    // Vetor que armazenará as frequencia de todas as letras usadas
    getByteFrequency(arq, listaBytes); // Monta a frequencia de cada palavra da entrada

    PriorityQueue *l2 = new PriorityQueue(NULL);       // Lista auxiliar para fazer consulta nos nodes (É menos custoso percorrer uma lista do que uma árvore)
    NodeTree *root = buildHuffmanTree(listaBytes, l2); // Populando a árvore com a lista de frequência de bytes
    codigoBin = codificacaoBinaria(arq, l2);           // Junta todos os codigos de todas as palavras para codificar o texto inteiro

    return codigoBin;
}


float HuffmanCoding::taxaDeCompressao(int lengthOfTheOriginalString, int lengthOfTheCompressedMessage)
{
    int parcial = lengthOfTheOriginalString - lengthOfTheCompressedMessage;
    float taxaDeCompressao = (parcial / lengthOfTheOriginalString) * 100;
    return taxaDeCompressao;
}