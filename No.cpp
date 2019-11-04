#include "No.h"
#include <iostream>
#include <fstream>
using namespace std;

//Construtor
No::No(int id, int x, int y){

    this->id = id;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->potencia = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;
    this->primeiro_cliente = this->ultimo_cliente = nullptr;
    this->x = x;
    this->y = y;

};

No::No(){}

// Destrutor
No::~No(){

    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr){

        Aresta* aux_aresta = proxima_aresta->getProximaAresta();
        delete proxima_aresta;
        proxima_aresta = aux_aresta;

    }

    No *proximo_cliente = this->primeiro_cliente;

    while (proximo_cliente != nullptr)
    {
        proximo_cliente->removerTodasArestas();
        No *aux_no = proximo_cliente->getProximoNo();
        delete proximo_cliente;
        proximo_cliente = aux_no;
    }

}

//Getters
Aresta *No::getPrimeiraAresta() {
    return this->primeira_aresta;
}

Aresta *No::getUltimaAresta() {
    return this->ultima_aresta;
}

int No::getGrauEntrada() {
    return this->grau_entrada;
}

int No::getGrauSaida() {
    return this->grau_saida;
}

int No::getId() {
    return this->id;
}

float No::getPeso() {
    return this->peso;
}

float No::getPotencia() {
    return this->potencia;
}

No *No::getProximoNo() {
    return this->proximo_no;
}

No *No::getPrimeiroCliente() {
    return this->primeiro_cliente;
}

int No::getX() {
    return this->x;
}

int No::getY() {
    return this->y;
}




//Setters
void No::setProximoNo(No *proximo_no) {
    this->proximo_no = proximo_no;
}

void No::setPeso(float peso) {
    this->peso = peso;
}

void No::setPotencia(float potencia) {
    this->potencia = potencia;
}

void No::inserirCliente(int id, int x, int y, float dist){
    //Verifica se existe pelo menos um Cliente, caso negativo, o primeiro Cliente sera setado
    if(this->primeiro_cliente != nullptr){
        No* no = new No(id,x,y);
        no->setPotencia(dist);
        this->ultimo_cliente -> setProximoNo(no);
        this->ultimo_cliente = no;
    }
    else{
        this->primeiro_cliente = new No(id,x,y);
        this->primeiro_cliente->setPotencia(dist);
        this->ultimo_cliente = this->primeiro_cliente;
    }
}

void No::mostrarClientes(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------CLIENTES------------"<<endl;
    arquivo_saida<<"ID. X - Y / Dist ate o ap"<<endl;
    for(No* no = primeiro_cliente; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ". ";
        arquivo_saida << no->getX() << " - ";
        arquivo_saida << no->getY() << " / ";
        arquivo_saida << no->getPotencia();
        arquivo_saida << endl;
    }
    arquivo_saida<<endl<<endl;
}

void No::atribuirPotenciaTransmissao() {
    No* cliente = primeiro_cliente;
    float maiorDistancia = cliente->getPotencia();
    for(cliente = cliente->getProximoNo(); cliente != nullptr; cliente = cliente->getProximoNo()){
        if(maiorDistancia<cliente->getPotencia()){
            maiorDistancia = cliente->getPotencia();
        }
    }
    this->potencia = maiorDistancia;
}

void No::inserirAresta(int id_destino, float peso) {
    //Verifica se existe pelo menos uma aresta no No, caso negativo, a primeira aresta sera setada
    if(this->primeira_aresta != nullptr){
        Aresta* aresta = new Aresta(this->id,id_destino);
        aresta->setPeso(peso);
        this->ultima_aresta -> setProximaAresta(aresta);
        this->ultima_aresta = aresta;
    }
    else{
        this->primeira_aresta = new Aresta(this->id,id_destino);
        this->primeira_aresta -> setPeso(peso);
        this->ultima_aresta = this->primeira_aresta;
    }

}

void No::removerTodasArestas() {
    //Verifica se existe pelo menos uma aresta no No
    if(this->primeira_aresta != nullptr){
        Aresta* prox = nullptr;
        Aresta* aux = this->primeira_aresta;

        while (aux != nullptr) {
            prox = aux->getProximaAresta();
            delete aux;
            aux=prox;
        }
    }

    this->primeira_aresta = this->ultima_aresta = nullptr;
}

//Verifica se o no possui uma aresta para o no de destino
bool No::procurarAresta(int id_destino) {
    if(this->primeira_aresta != nullptr){
        for(Aresta* aux = this->primeira_aresta; aux!= nullptr; aux = aux->getProximaAresta()){
            if(aux->getIdDestino() == id_destino)
                return true;
        }
    }
        return false;
}

int No::removerAresta(int id, bool direcionado, No *no_destino) {
    //Verifica se existe a aresta
    if(this->procurarAresta(id)){
        Aresta* aux = this->primeira_aresta;
        Aresta* anterior = nullptr;

        //Procurando a aresta a ser removida
        while (aux->getIdDestino() != id){
            anterior = aux;
            aux = aux->getProximaAresta();
        }

        //Garantindo a integridade da lista de arestas
        if(anterior != nullptr)
            anterior->setProximaAresta(aux->getProximaAresta());
        else
            this->primeira_aresta = aux->getProximaAresta();

        if(aux == this->ultima_aresta)
            this->ultima_aresta = anterior;

        if(aux->getProximaAresta() == this->ultima_aresta)
            this->ultima_aresta = aux-> getProximaAresta();

        delete aux;

        //Grafo direcionado ou nao
        if(direcionado){
            this->diminuirGrauSaida();
            no_destino->diminuirGrauEntrada();
        }
        else{
            this->diminuirGrauEntrada();
            no_destino->diminuirGrauEntrada();
        }

        return 1;

    }

    return 0;
}

void No::aumentarGrauEntrada() {
    this->grau_entrada++;
}

void No::aumentarGrauSaida() {
    this->grau_saida++;
}

void No::diminuirGrauEntrada() {
    this->grau_entrada--;
}

void No::diminuirGrauSaida() {
    this->grau_saida--;
}









