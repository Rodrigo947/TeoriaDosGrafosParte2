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
    int quant_aresta;
    bool direcionado;
    bool ponderado_aresta;
    bool ponderado_no;
    No* primeiro_no;
    No* ultimo_no;

public:

    //Contrutor e Destrutor
    Grafo();
    Grafo(int ordem);
    ~Grafo();

    //Getters
    int getOrdem();
    int getQuantAresta();
    bool getDirecionado();
    bool getPonderadoAresta();
    bool getPonderadoNo();
    No* getPrimeiroNo();
    No* getPrimeiroCliente();
    No* getUltimoNo();
    No* getUltimoCliente();
    No *getNo(int id);

    //Setters
    void setQuantAresta(int val);

    //Outros Metodos
    bool procurarNo(int id);
    No *retornaNo(int id);
    void inserirNo(int id,int x, int y);
    void inserirAresta(int id, int id_destino, float peso);
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarArestas(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    void defineClientes();
    float distanciaEuclidiana(int x1, int y1, int x2, int y2);
    void inserirCliente(int id,int x, int y);
    void definePotencia(); //define a potencia para cada ap

    //FUNCIONALIDADES
    void guloso(ofstream& arquivo_saida);
    void gulosoRandomizado(ofstream& arquivo_saida);
    void gulosoRandomizadoReativo(ofstream& arquivo_saida);


};
#endif //TEORIADOSGRAFOS_GRAFO_H
