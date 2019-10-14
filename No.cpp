#include "No.h"

//Construtor
No::No(int id){

    this->id = id;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;

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

No *No::getProximoNo() {
    return this->proximo_no;
}

//Setters
void No::setProximoNo(No *proximo_no) {
    this->proximo_no = proximo_no;
}

void No::setPeso(float peso) {
    this->peso = peso;
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




