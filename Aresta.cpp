#include "Aresta.h"

Aresta::Aresta(){}

Aresta::Aresta(int id_origem,int id_destino) {
    this->id_origem = id_origem;
    this->id_destino = id_destino;
    this->proxima_aresta = nullptr;
    this->peso = 0;
}

Aresta::~Aresta() {
    if(this->proxima_aresta != nullptr){
        delete this->proxima_aresta;
        this->proxima_aresta = nullptr;
    }
}
int Aresta::getIdOrigem() {
    return this->id_origem;
}

int Aresta::getIdDestino() {
    return this->id_destino;
}

//Getters
Aresta *Aresta::getProximaAresta() {
    return this->proxima_aresta;
}

float Aresta::getPeso() {
    return this->peso;
}

//Setters
void Aresta::setProximaAresta(Aresta *aresta) {
    this->proxima_aresta = aresta;
}

void Aresta::setPeso(float peso) {
    this->peso = peso;
}

void Aresta::setOrigem(int id_origem) {
    this->id_origem = id_origem;
}

void Aresta::setDestino(int id_destino) {
    this->id_destino = id_destino;
}






