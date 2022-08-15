#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "HuffmanCoding.h"
#include "NodeQueue.h"
#include "NodeTree.h"
#include "PriorityQueue.h"

class HuffmanTest : public ::testing::Test
{
protected:
    HuffmanTest()
    {
        // Abre um arquivo TEXTO para LEITURA
        this->arq = fopen("ArquivoTeste.txt", "r");
        if (arq == NULL) // Se houve erro na abertura
        {
            printf("Problemas na abertura do arquivo\n");
            return;
        }

        listaFrequencia[256] = {0};
        this->l2 = new PriorityQueue(NULL);
    }

    ~HuffmanTest() override
    {
    }

    void criaFrequencias()
    {
        // Cria lista de frequência para a entrada: ABRACADABRA!
        unsigned listaFrequenciaCorreta[256] = {0};
        listaFrequenciaCorreta[65] = 5; // A : Freq = 5
        listaFrequenciaCorreta[66] = 2; // B : Freq = 2
        listaFrequenciaCorreta[67] = 1; // C : Freq = 1
        listaFrequenciaCorreta[68] = 1; // D : Freq = 1
        listaFrequenciaCorreta[82] = 2; // R : Freq = 2
        listaFrequenciaCorreta[33] = 1; // '!' : Freq = 1

        // Criar lista de frequências usando o algoritmo do código
        HuffmanCoding::getByteFrequency(arq, this->listaFrequencia); // Chama a função que cria a lista de frequências

        // Teste
        for (int i = 0; i < 256; i++)
        {
            EXPECT_EQ(this->listaFrequencia[i], listaFrequenciaCorreta[i]);
        }
    }

    // Funcao auxiliar para os testes de montaArvore e gereCodificao. Percorre a arvore e retorna o node que possui o caractere enviado como parametro
    void percorreArvore(char c, NodeTree *encontrado)
    {
        bool verifica = false;
        HuffmanCoding::percorreTree(this->root, c, encontrado, &verifica);
    }

    void montaArvore()
    {
        // Montando a arvore de Huffman para a entrada: ABRACADABRA!
        // Folhas
        NodeTree *folhaA = new NodeTree('A', 5, NULL, NULL);
        NodeTree *folhaB = new NodeTree('B', 2, NULL, NULL);
        NodeTree *folhaC = new NodeTree('C', 1, NULL, NULL);
        NodeTree *folhaD = new NodeTree('D', 1, NULL, NULL);
        NodeTree *folhaR = new NodeTree('R', 2, NULL, NULL);
        NodeTree *folhaExcla = new NodeTree('!', 1, NULL, NULL);
        // Pais
        NodeTree *nodeP = new NodeTree('#', 2, folhaExcla, folhaC);
        NodeTree *nodeP2 = new NodeTree('#', 4, folhaR, nodeP);
        NodeTree *nodeP3 = new NodeTree('#', 3, folhaD, folhaB);
        NodeTree *nodeP4 = new NodeTree('#', 7, nodeP3, nodeP2);
        NodeTree *nodeP5 = new NodeTree('#', 12, folhaA, nodeP4); // Raiz

        // Criando árvore com o código
        this->root = HuffmanCoding::buildHuffmanTree(this->listaFrequencia, this->l2); // Populando a árvore com a lista de frequência de bytes

        // Testes
        NodeTree *encontrado = new NodeTree();
        EXPECT_EQ(this->root->getC(), nodeP5->getC());
        percorreArvore('A', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaA->getC());
        percorreArvore('B', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaB->getC());
        percorreArvore('C', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaC->getC());
        percorreArvore('D', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaD->getC());
        percorreArvore('R', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaR->getC());
        percorreArvore('!', encontrado);
        EXPECT_EQ(encontrado->getC(), folhaExcla->getC());
        /*
                    ABRACADABRA!
                        (12)
                       0/   \1
                      (A)   (7)
                          0/   \1
                         (3)    (4)
                       0/ \1   0/  \1
                      (D) (B) (R)  (2)
                                  0/  \1
                                 (!)  (C)
        */
        delete folhaA;
        delete folhaB;
        delete folhaC;
        delete folhaD;
        delete folhaR;
        delete folhaExcla;
        delete nodeP;
        delete nodeP2;
        delete nodeP3;
        delete nodeP4;
        delete nodeP5;
        delete encontrado;
    }

    void geraCodificacao()
    {
        /*
                   ABRACADABRA!
                       (12)
                      0/   \1
                     (A)   (7)
                         0/   \1
                        (3)    (4)
                      0/ \1   0/  \1
                     (D) (B) (R)  (2)
                                 0/  \1
                                (!)  (C)
       */
        // l2 = (!) -> (C) -> (D) -> (B) -> (R) -> (A)
        string codigoA = "0";
        string codigoB = "101";
        string codigoC = "1111";
        string codigoD = "100";
        string codigoR = "110";
        string codigoExcla = "1110";
        this->root = HuffmanCoding::buildHuffmanTree(this->listaFrequencia, this->l2);

        NodeTree *encontrado = new NodeTree();
        percorreArvore('A', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoA);
        percorreArvore('B', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoB);
        percorreArvore('C', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoC);
        percorreArvore('D', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoD);
        percorreArvore('R', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoR);
        percorreArvore('!', encontrado);
        EXPECT_EQ(encontrado->getCodigo(), codigoExcla);

        delete encontrado;
    }

    void compressao()
    {
        string codigoComprimidoCorreto = "0101110011110100010111001110";
        string compressaoCodigo = HuffmanCoding::compressFile("ArquivoTeste.txt");

        EXPECT_EQ(codigoComprimidoCorreto, compressaoCodigo);
    }

    void descompressao()
    {
        string codigoDescomprimidoCorreto = "ABRACADABRA!";
        this->root = HuffmanCoding::buildHuffmanTree(this->listaFrequencia, this->l2);
        string codigoBin = HuffmanCoding::compressFile("ArquivoTeste.txt");

        int numberOfZerosAtTheEnd = 0;
        bool notDivisibleByEight = false;
        HuffmanCoding::escrevendoArqBin(&codigoBin, codigoBin.length(), &numberOfZerosAtTheEnd, &notDivisibleByEight);
        string codigoDescomprimidoCodigo = HuffmanCoding::binaryIntoWord(HuffmanCoding::decompressFile(numberOfZerosAtTheEnd, notDivisibleByEight), this->root);

        EXPECT_EQ(codigoDescomprimidoCorreto, codigoDescomprimidoCodigo);
    }

    void calculaTaxaDeCompressao()
    {
        // Entrada:                   ABRACADABRA!
        // Codificacao:             0101110011110100010111001110
        // Pegar de 8 em 8:         01011100 11110100 01011100 1110
        // Transformar em decimal:     92      244       92     14

        int tamanhoArqOriginal = 12;
        int tamanhoArqComprimido = 4;
        float taxaDeCompressaoCerta = ((12 - 4) / 12) * 100;
        float taxaCompressaoCodigo;

        this->root = HuffmanCoding::buildHuffmanTree(this->listaFrequencia, this->l2);
        string codigoBin = HuffmanCoding::compressFile("ArquivoTeste.txt");
        int numberOfZerosAtTheEnd = 0;
        bool notDivisibleByEight = false;
        HuffmanCoding::escrevendoArqBin(&codigoBin, codigoBin.length(), &numberOfZerosAtTheEnd, &notDivisibleByEight);
        string codigoDescomprimidoCodigo = HuffmanCoding::binaryIntoWord(HuffmanCoding::decompressFile(numberOfZerosAtTheEnd, notDivisibleByEight), this->root);

        // Calculando o numero de caracteres do arquivo original
        fstream file("ArquivoTeste.txt", ios::in | ios::out | ios::binary);
        if (!file.is_open())
        {
            cout << "Erro ao abrir o arquivo" << endl;
            exit(1);
        }
        file.seekg(0, file.end);     
        int fileSize = file.tellg(); 
        file.seekg(0, file.beg);

        // Calculando o numero de caracteres do arquivo comprimido
        fstream file2("ArqBin.bin", ios::in | ios::out | ios::binary);
        if (!file2.is_open())
        {
            cout << "Erro ao abrir o arquivo" << endl;
            exit(1);
        }
        file2.seekg(0, file2.end);     
        int fileSize2 = file2.tellg(); 
        file2.seekg(0, file2.beg);

        taxaCompressaoCodigo = HuffmanCoding::taxaDeCompressao(fileSize, fileSize2);

        EXPECT_EQ(taxaDeCompressaoCerta, taxaCompressaoCodigo);
    }

    unsigned listaFrequencia[256]; // Lista de frequencia de cada letra
    NodeTree *root;                // Árvore gerada do algoritmo de Huffman
    FILE *arq;                     // Arquivo de entrada
    PriorityQueue *l2;             // Lista auxiliar de nodes da arvore para consultas
};

TEST_F(HuffmanTest, criarFrequencias)
{
    // Entrada: ABRACADABRA!
    criaFrequencias();
}

TEST_F(HuffmanTest, montarArvore)
{
    // Entrada: ABRACADABRA!
    montaArvore();
}

TEST_F(HuffmanTest, criarCodificacao)
{
    // Entrada: ABRACADABRA!
    geraCodificacao();
}

TEST_F(HuffmanTest, criarCompressao)
{
    // Entrada: ABRACADABRA!
    compressao();
}

TEST_F(HuffmanTest, criarDescompressao)
{
    // Entrada: ABRACADABRA!
    descompressao();
}

TEST_F(HuffmanTest, calcularTaxaDeDescompressao)
{
    // Entrada: ABRACADABRA!
    calculaTaxaDeCompressao();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}