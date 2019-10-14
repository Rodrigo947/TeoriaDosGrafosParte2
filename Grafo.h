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

    int mapeamento(int* mapa, int id);
	void auxDijkstra(float* distancia, int* aPercorrer, int* noAnterior, int* mapa, int atual);
	bool ehVizinho(No* noU, No* noV);
	void auxFloyd(float** matriz, int* aPercorrer, int* noAnterior, int* mapa, int atual, int idNoU);

public:

    //Contrutor e Destrutor
    Grafo();
    Grafo(int ordem, bool direcionado, bool ponderadoAresta, bool ponderadoNo);
    ~Grafo();

    //Getters
    int getOrdem();
    int getQuantAresta();
    bool getDirecionado();
    bool getPonderadoAresta();
    bool getPonderadoNo();
    No* getPrimeiroNo();
    No* getUltimoNo();
    No *getNo(int id);

    //Setters
    void setQuantAresta(int val);

    //Outros Metodos
    bool procurarNo(int id);
    No *retornaNo(int id);
    void inserirNo(int id);
    void inserirAresta(int id, int id_destino, float peso);
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarArestas(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    Grafo* getSubjacente();

    //FUNCIONALIDADES

    void caminhamentoLargura(int id_no, ofstream& arquivo_saida);
    void auxBuscaEmProfundidade(int id_no, bool* aux,ofstream &arquivo_saida);
    void caminhamentoProfundidade(int id_no, ofstream &arquivo_saida);
    void fechoTransitivoDireto(No* no, ofstream &arquivo_saida);
    void fechoTransitivoIndireto(No* no, ofstream &arquivo_saida);
    void dijkstra(No* noU, No* noV, ofstream& arquivo_saida);
    void floyd(No* noU, No* noV, ofstream &arquivo_saida);
    void AGMPrim(ofstream &arquivo_saida);
    void AGMKruskal(ofstream &arquivo_saida);
    void fechoTriadico(ofstream &arquivo_saida);

   //AUXILIARES DAS FUNCIONALIDADES
   //AGMKruskal
   bool verificaId(int nosJaVisitados[], int id_no,int tam);
   bool possuiCiclo();
   int auxPossuiCiclo(int *vetor, int id);
   bool auxPossuiCicloDirecionado(int idDestino, Pilha *nosEmExploracao);
   //Floyd
   void criaMatriz(float** matriz, int* noAnterior, int* mapa);
};
#endif //TEORIADOSGRAFOS_GRAFO_H
