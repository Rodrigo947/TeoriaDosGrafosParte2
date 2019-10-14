#ifndef TEORIADOSGRAFOS_NO_H
#define TEORIADOSGRAFOS_NO_H
#include "Aresta.h"

class No{
private:
    Aresta* primeira_aresta;
    Aresta* ultima_aresta;
    int id;
    int grau_entrada;
    int grau_saida;
    float peso;
    No* proximo_no;

public:
    //Contrutor e Destrutor
    No(int id);
    No();
    ~No();

    //Getters
    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    int getId();
    int getGrauEntrada();
    int getGrauSaida();
    float getPeso();
    No *getProximoNo();


    //Setters
    void setProximoNo(No* proximo_no);
    void setPeso(float peso);

    //Outros metodos
    void inserirAresta(int id_destino, float peso);
    void removerTodasArestas();
    bool procurarAresta(int id_destino); //Verifica se o no possui uma aresta para o no de destino
    int removerAresta(int id, bool direcionado, No* no_destino);


    //Aumentar e diminuir o grau do no
    void aumentarGrauEntrada();
    void aumentarGrauSaida();
    void diminuirGrauEntrada();
    void diminuirGrauSaida();



};
#endif //TEORIADOSGRAFOS_NO_H
