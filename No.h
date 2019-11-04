#ifndef TEORIADOSGRAFOS_NO_H
#define TEORIADOSGRAFOS_NO_H
#include "Aresta.h"
#include <iostream>
#include <fstream>
using namespace std;

class No{
private:
    Aresta* primeira_aresta;
    Aresta* ultima_aresta;
    int id;
    int grau_entrada;
    int grau_saida;
    float peso;
    float potencia;
    No* proximo_no;
    No* primeiro_cliente;
    No* ultimo_cliente;
    int x;
    int y;

public:
    //Contrutor e Destrutor
    No(int id, int x, int y);
    No();
    ~No();

    //Getters
    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    int getId();
    int getGrauEntrada();
    int getGrauSaida();
    float getPeso();
    float getPotencia();
    No *getProximoNo();
    No *getPrimeiroCliente();
    int getX();
    int getY();

    //Setters
    void setProximoNo(No* proximo_no);
    void setPeso(float peso);
    void setPotencia(float potencia);

    //Outros metodos
    void inserirCliente(int id, int x, int y, float dist);
    void mostrarClientes(ofstream& arquivo_saida);
    void inserirAresta(int id_destino, float peso);
    void removerTodasArestas();
    bool procurarAresta(int id_destino); //Verifica se o no possui uma aresta para o no de destino
    int removerAresta(int id, bool direcionado, No* no_destino);
    void atribuirPotenciaTransmissao(); //Verifica qual a distancia do cliente mais longe, essa distancia será a potencia do AP


    //Aumentar e diminuir o grau do no
    void aumentarGrauEntrada();
    void aumentarGrauSaida();
    void diminuirGrauEntrada();
    void diminuirGrauSaida();



};
#endif //TEORIADOSGRAFOS_NO_H
