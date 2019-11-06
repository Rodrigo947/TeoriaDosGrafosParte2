#ifndef TEORIADOSGRAFOS_GRAFO_H
#define TEORIADOSGRAFOS_GRAFO_H

#include <iostream>
#include <fstream>
#include "No.h"
#include "Pilha.h"

using namespace std;

class Grafo{
private:
    int ordem;
    int quantClientes;
    int quant_aresta;
    bool direcionado;
    bool ponderado_aresta;
    bool ponderado_no;
    No* primeiro_no;
    No* ultimo_no;
    float inteferenciaTotal;
    float tabelaInterferencia[11][11];

public:

    //Contrutor e Destrutor
    Grafo();
    Grafo(int ordem, int quantClientes);
    ~Grafo();

    //Getters
    int getOrdem();
    int getQuantAresta();
    No* getPrimeiroNo();
    No* getPrimeiroCliente();
    No* getUltimoNo();
    No* getUltimoCliente();
    No *getNo(int id);
    float interferencia(int canal1,int canal2);

    //Setters
    void setQuantAresta(int val);
    //Outros Metodos
    bool procurarNo(int id);
    No *retornaNo(int id);
    void inserirNo(int id,int x, int y);
    void criarGrafoConflito();
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarArestas(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    float distanciaEuclidiana(int x1, int y1, int x2, int y2);
    void inserirCliente(int id,int x, int y);
    void definePotencia(); //define a potencia para cada ap

    //FUNCIONALIDADES
    int* baseCanais1611();
    void defineInterferencias(int idsNosInteferencia[]);
    bool estaNaInterseccao(No *cliente, No *ap, No*ap2);
    void guloso(ofstream& arquivo_saida);
    void gulosoRandomizado(ofstream& arquivo_saida);
    void gulosoRandomizadoReativo(ofstream& arquivo_saida);


    //void desenharSolucao();



};
#endif //TEORIADOSGRAFOS_GRAFO_H
