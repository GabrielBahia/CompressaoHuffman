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
#include <algorithm>

//#include <bits/stdc++.h>

typedef unsigned char byte;

/** Função que libera memória da árvore de huffman
 * @param: nó de uma (sub)árvore.
 */
void FreeHuffmanTree(NodeTree *n)
{
    // Caso base da recursão, enquanto o nó não for NULL
    if (!n)
        return;
    else
    {
        NodeTree *esquerda = n->getEsquerda();
        NodeTree *direita = n->getDireita();
        delete n;
        FreeHuffmanTree(esquerda);
        FreeHuffmanTree(direita);
    }
}

void getByteFrequency(FILE *entrada, unsigned int *listaBytes)
{

    byte c;

    /***
     *
     * fread( array/bloco de memoria , tamanho de cada elemento, quantos elementos, arquivo de entrada )
     * fread retorna a quantidade de blocos lidos com sucesso
     *
     * Faz a leitura de 1 bloco de tamanho 1 byte a partir do arquivo 'entrada'
     * e salva no espaco de memoria de 'c'.
     *
     * Converte esse byte num valor decimal, acessa o bucket correspondente e incrementa o valor (frequência).
     *
     ***/

    while (fread(&c, 1, 1, entrada) >= 1)
    {
        listaBytes[(byte)c]++;
    }
    rewind(entrada); // "rebobina o arquivo"
}

/** Função que faz bitmasking no byte lido e retorna um valor booleano confirmando sua existência
 * Ideia do bitmasking surgiu da leitura de http://ellard.org/dan/www/CS50-95/s10.html
 * @param: arquivo para ler o byte, posição que se deseja mascarar o byte, byte a ser feita a checagem
 */
int geraBit(FILE *entrada, int posicao, byte *aux)
{
    // É hora de ler um bit?
    (posicao % 8 == 0) ? fread(aux, 1, 1, entrada) : NULL == NULL;

    // Exclamação dupla converte para '1' (inteiro) se não for 0. Caso contrário, deixa como está (0)
    // Joga '1' na casa binária 'posicao' e vê se "bate" com o byte salvo em *aux do momento
    // Isso é usado para percorrer a árvore (esquerda e direita)
    return !!((*aux) & (1 << (posicao % 8)));
}

/** Função para notificar ausência do arquivo. Encerra o programa em seguida.
 */
void erroArquivo()
{
    printf("Arquivo nao encontrado\n");
    exit(0);
}

/** Função que constrói a árvore de huffman
 * @param: a fila de prioridade.
 */
NodeTree *BuildHuffmanTree(unsigned *listaBytes, PriorityQueue *l, PriorityQueue *l2, int *tamL)
{

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
    *tamL = l->getNumElementos();
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

    return l->popMinLista();
}

// Função auxiliar para percorrer a árvore
int isLeaf(NodeTree* root)
{
    return !(root->getEsquerda()) && !(root->getDireita());
}

// Função para percorrer a árvore de Huffman recursivamente para encontrar o node que possui a chave c
void PercorreTree(NodeTree *root, char c, NodeTree *encontrado, bool *verifica)
{
    if (*verifica == false)
    {
        if (root->getEsquerda())
        {
            PercorreTree(root->getEsquerda(), c, encontrado, verifica);
        }

        if (root->getDireita())
        {
            PercorreTree(root->getDireita(), c, encontrado, verifica);
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

void montaTabelaFreq(unsigned listaBytes[])
{
    for(int i = 0; i < 256; i++)
    {
        if(listaBytes[i] != 0)
        {
            cout << char(i) << " : " << listaBytes[i] << endl;
        }
    }
}


void montaCodigos(NodeTree *root, PriorityQueue *l2)
{

    for(NodeQueue *aux = l2->getHead(); aux != NULL; aux = aux->getProximo())
    {
        NodeTree *aux2 = aux->getN();
        if(aux2->getC() == root->getC())
        {
            aux2->setCodigo(root->getCodigo());
            aux2->setTamCodigo(root->getTamCodigo());
            return;
        }
    }
}

int calculaTamanhoCod(NodeTree *root, unsigned listaBytes[], PriorityQueue *l2) 
{
    int tam = 0;

    for(int i = 0; i < 256; i++)
    {
        if(listaBytes[i] != 0)
        {

            byte c = (char)i;
            bool verifica = false;
            NodeTree *encontrado = new NodeTree();
            PercorreTree(root, c, encontrado, &verifica);
            tam = tam + encontrado->getTamCodigo();

            montaCodigos(encontrado,l2);

            delete encontrado;
        }
    }

    return tam;
}

void codificacaoBinaria(FILE *entrada, string *codigoBin, int tam, PriorityQueue *l2)
{
    byte c;
    while (fread(&c, 1, 1, entrada) >= 1)
    {
       for(NodeQueue *aux = l2->getHead(); aux != NULL; aux = aux->getProximo())
       {    
           NodeTree *aux2 = aux->getN();
           if(aux2->getC() == c)
           {    
                *codigoBin = *codigoBin + aux2->getCodigo();
           }
       }
    }
}

void codificacaoAscii(string *codigoBin, int tam, string *codigoAscii, int *binaryStartWithZero)
{

    fstream file("ArqBin.bin", ios::binary | ios::out);
    if(!file.is_open()) {
        cout << "Erro ao abrir o arquivo";
        exit(1);
    }
    //00100101 string
    // 139  int
    // 139 escrever no binario

    int cont = 0;
    int cont2 = 0;
    int contNumberOfBinarys = 0;
    string str_bin = "";
    string binaryFull = "";
    int i_bin; 
    int numberOfBinarys = 0;
    ((tam % 8) != 0) ? numberOfBinarys = (tam / 8) + 1 : numberOfBinarys = tam / 8; 
    cout << "Quarta vez: " << binaryStartWithZero << endl;
    binaryStartWithZero = new int[numberOfBinarys];
    cout << "Quinta vez: " << binaryStartWithZero << endl;
    //cout << "CodigoBin :" << codigoBin[2] << endl;
    while(cont < tam)
    {
        for(int i = cont; i < (cont+8) && i < tam; i++)
        {
            str_bin = str_bin + (*codigoBin).at(i);
        }
        cout << str_bin << endl;
        //cout << str_bin[0] << endl;
        binaryStartWithZero[contNumberOfBinarys] = 0;
        //cout << "contaNumberOfBinarys: " << contNumberOfBinarys << endl;
        if(str_bin[0] == '0') {
            cout << "ISSO AQUI É 0 NÉ, OU EU TO MUITO DOIDO???" << endl;
            binaryStartWithZero[contNumberOfBinarys] = 1;
            if(binaryStartWithZero[contNumberOfBinarys]) {
                cout << "Cout nos valores" << binaryStartWithZero[contNumberOfBinarys] << endl;
                cout << "Entrou porra" << endl;
            }
        }
        //(str_bin[0] == '0') ? binaryStartWithZero[contNumberOfBinarys] = true : binaryStartWithZero[contNumberOfBinarys] = false; 
        i_bin = stoi(str_bin,nullptr,2);

        //
        //binaryFull += str_bin;
        //
        str_bin = "";
        cout << "i_bin : " << i_bin << endl;

        file.write((char*)&i_bin, sizeof(int));
        cont+=8;
        contNumberOfBinarys++;
    }
    /*size_t size = binaryFull.size();
    file.write(&size, sizeof(size));
    file.write(&binaryFull[0], size);*/
    
}


/* 
Decodificação : 
- Percorrer o vetor de bits e a arvore ao msm tempo
- caso o bit seja 0, percorre pra esquerda da arvore, caso seja 1, vai pra direita
- caso o node seja folha, achou a letra
*/


/** Função que comprime um arquivo utilizando a compressão de huffman
 * @param: arquivo a comprimir, arquivo resultado da compressão
 */
NodeTree *CompressFile(int *binaryStartWithZero)
{

    FILE *arq;
    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("ArqTeste2.txt", "r");
    if (arq == NULL) // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return nullptr;
    }

    unsigned listaBytes[256] = {0};
    int *arr = new int;
    int top = 0;

    getByteFrequency(arq, listaBytes);

    PriorityQueue *l = new PriorityQueue(NULL);
    PriorityQueue *l2 = new PriorityQueue(NULL);

    // Populando a árvore com a lista de frequência de bytes
    int tamL;
    NodeTree *root = BuildHuffmanTree(listaBytes, l, l2, &tamL);
    byte b = 'f';
    bool verifica = false;
    NodeTree *encontrado = new NodeTree();
    NodeTree::printCodes(root,arr,top);

    //PercorreTree(root, b, encontrado, &verifica);
    //montaTabelaFreq(listaBytes);

    int tamanhoCodificacaoBin = calculaTamanhoCod(root, listaBytes, l2);

    string codigoBin = "";
    string codigoAscii = "";

    codificacaoBinaria(arq, &codigoBin, tamanhoCodificacaoBin, l2);
    cout << "Terceira vez: " << binaryStartWithZero << endl;
    codificacaoAscii(&codigoBin, tamanhoCodificacaoBin, &codigoAscii, binaryStartWithZero);
    cout << "Sexta vez: " << binaryStartWithZero << endl;
    cout << "Valor dps de colocar os 1: " << binaryStartWithZero[0] << endl;

    return root;
    //FreeHuffmanTree(root);
}

string Decode() 
{
    
    fstream file("ArqBin.bin", ios::in | ios::out | ios::binary);
    if(!file.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    file.seekg(0, file.end); // posiciona o ponteiro no final do arquivo
    int fileSize = file.tellg() / 4; // pega o tamanho do arquivo e divide pelo tamanho de cada estudante para saber o total
    file.seekg(0, file.beg); // posiciona o ponteiro no final do arquivo
    cout << "Tamanho do arquivo: " << fileSize << endl;
    string binaryFull = "";
    for(int i = 0; i < fileSize; i++) 
    {
        int integerCode;
        file.read((char*)&integerCode, sizeof(int));
        cout << integerCode << endl;
        string integerAsBinary = "";
        while(integerCode > 0) {
            integerAsBinary += to_string((integerCode % 2));
            integerCode = integerCode / 2;
        }
        reverse(integerAsBinary.begin(), integerAsBinary.end());
        binaryFull += integerAsBinary;
        cout << "Integer as binary: " << integerAsBinary << endl;
    }

    return binaryFull;
    /*
    fstream file("ArqBin.bin", ios::in | ios::out | ios::binary);
    if(!file.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }
    string binaryFull = "";
    size_t size;
    file.read(&size, sizeof(size));
    binaryFull.resize(size);
    file.read(&binaryFull[0], size);
    return binaryFull;
    */

}

void binaryIntoWord(string binaryFull, NodeTree *root) {
    cout << "Testando se foi: " << binaryFull << endl;
    string wordDecoded = "";
    cout << "Testando essa porra: " << root->getEsquerda()->getC() << endl;
    NodeTree *aux = root;
    cout << "Tamanho da string: " << binaryFull.length() << endl;
    bool flag;
    int numberOfFlags = 0;
    for(int i = 0; i < binaryFull.length(); i++)
    {
        flag = false;
        if(i == 0 || i == 15) {
            if(numberOfFlags == 0 && i == 0) {
                aux = aux->getEsquerda();
                flag = true;
            }
            if(numberOfFlags == 1 && i == 15) {
                aux = aux->getEsquerda();
                flag = true;
            }
        }
        if(!NodeTree::isLeaf(aux)) {
            //cout << "i: " << i << endl;
            if(binaryFull[i] == '0') {
                aux = aux->getEsquerda();
                cout << "I pra esquerda: " << i << endl;
            } else {
                aux = aux->getDireita();
                cout << "I pra direita: " << i << endl;
            }
        } //else {
        if(NodeTree::isLeaf(aux)) {
            cout << "i: " << i << endl;
            wordDecoded += aux->getC();
            cout << "Pegou a letra: " << aux->getC() << endl;
            aux = root;
            //i--;
            if(flag) {
                numberOfFlags++;
                i--;
            }
        }
    }
    cout << "Palavra utilizada: " << wordDecoded << endl;
}

int main()
{
    int binaryStartWithZero[1000]; //= new int[];//nullptr; //= new bool; 
    cout << "Primeira vez: " << binaryStartWithZero << endl;
    NodeTree *nodeTree = CompressFile(binaryStartWithZero);
    cout << "Segunda vez: " << binaryStartWithZero << endl;
    cout << "Letra dessa porra é: " << nodeTree->getDireita()->getEsquerda()->getEsquerda()->getC() << endl;

    for(int i = 0; i < 4; i++) {
        cout << "Entrou aqui????" << endl;
        if(binaryStartWithZero[i]) {
            cout << "Essa porra começa com 0: " << i << endl;
        }
    }

    //cout << nodeTree->getC();
    
    //binaryIntoWord(Decode(), nodeTree);
    
    /*

    fstream file("ArqBin.bin", ios::in | ios::out | ios::binary);
    if(!file.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(1);
    }

    file.seekg(0, file.end); // posiciona o ponteiro no final do arquivo
    int teste = file.tellg() / 4; // pega o tamanho do arquivo e divide pelo tamanho de cada estudante para saber o total
    file.seekg(0, file.beg);

    cout << "Número de elementos no arquivo: " << teste << endl;

    file.read((char*)&teste, sizeof(int));

    cout << "Teste vale: " << teste << endl;
    */

    /*for(int i=0;i<220;i++)
    cout << "a";
    for(int i=0;i<78;i++)
    cout << "c";
    for(int i=0;i<112;i++)
    cout << "e";
    for(int i=0;i<50;i++)
    cout << "d";
    for(int i=0;i<12;i++)
    cout << "t";
    for(int i=0;i<66;i++)
    cout << "o";
    for(int i=0;i<180;i++)
    cout << "b";
    for(int i=0;i<95;i++)
    cout << "f";
    for(int i=0;i<34;i++)
    cout << "g";*/

    // 1 - Armazenar todas as codificacoes em um vetor
    // 2- Percorrer o vetor de 8 em
    // 3- Pegar 8 caracters(binario) transformar em decimal
    // 4 - Pegar todos os valores e salvar em um arquivo binario
    //  Descobrir pq o head esta dando segmentation



    return 0;
}
