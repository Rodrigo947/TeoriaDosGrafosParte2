#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "No.h"
#include "FilaEncadeada.h"
#include "Pilha.h"
#include <math.h>


using namespace std;

//Construtor
Grafo::Grafo(int ordem){
    this->ordem = ordem;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->quant_aresta = 0;
}
Grafo::Grafo(){

}


// Destrutor
Grafo::~Grafo()
{

    No *proximo_no = this->primeiro_no;

    while (proximo_no != nullptr)
    {
        proximo_no->removerTodasArestas();
        No *aux_no = proximo_no->getProximoNo();
        delete proximo_no;
        proximo_no = aux_no;
    }


}

//Getters

int Grafo::getOrdem()
{
    return this->ordem;
}
int Grafo::getQuantAresta()
{
    return this->quant_aresta;
}

No *Grafo::getPrimeiroNo()
{
    return this->primeiro_no;
}

No *Grafo::getUltimoNo()
{
    return this->ultimo_no;
}



//Setters

void Grafo::setQuantAresta(int val){
    this->quant_aresta++;
}

//Retorna um No com o determinado id, caso negativo retorna null
No *Grafo::getNo(int id){
    if(this->primeiro_no != nullptr){
        for(No* aux = primeiro_no; aux != nullptr; aux = aux->getProximoNo())
            if(aux->getId() == id)
                return aux;
    }

    return nullptr;
}

//Outros metodos

void Grafo::inserirNo(int id, int x, int y){
    //Verifica se existe pelo menos um No, caso negativo, o primeiro No sera setado
    if(this->primeiro_no != nullptr){
        No* no = new No(id,x,y);
        this->ultimo_no -> setProximoNo(no);
        this->ultimo_no = no;
    }
    else{
        this->primeiro_no = new No(id,x,y);
        this->ultimo_no = this->primeiro_no;
    }
}

//Add o cliente no ap que possui a menor distancia até ele
void Grafo::inserirCliente(int id, int x, int y){

    int menorDistancia,idMenor=0,x1=x,y1=y,x2,y2;

    No* ap = primeiro_no;
    x2 = ap->getX();
    y2 = ap->getY();

    menorDistancia = distanciaEuclidiana(x1,y1,x2,y2);

    for(ap = ap->getProximoNo(); ap != nullptr; ap = ap->getProximoNo()) {
        x2 = ap->getX();
        y2 = ap->getY();
        if (distanciaEuclidiana(x1, y1, x2, y2) < menorDistancia) {
            menorDistancia = distanciaEuclidiana(x1, y1, x2, y2);
            idMenor = ap->getId();
        }
    }
    getNo(idMenor)->inserirCliente(id, x, y, menorDistancia);
}

//Verifica qual cliente possui a maior distancia para o ap
void Grafo::definePotencia(){
    float maior = 0;
    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()){

        for(No* cliente = ap->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()){

        }
    }
}

//Verifica se o No esta no Grafo
bool Grafo::procurarNo(int id){

    if(this->primeiro_no != nullptr){
        for(No* aux = primeiro_no; aux != nullptr; aux = aux->getProximoNo())
            if(aux->getId() == id)
                return true;
    }

    return false;

}

/*void Grafo::inserirAresta(int id, int id_destino, float peso){

    //Se algum No nao estiver no grafo
    if( !procurarNo(id) )
        inserirNo(id);

    if( !procurarNo(id_destino) )
        inserirNo(id_destino);

    No* noOrigem = getNo(id);
    No* noDestino = getNo(id_destino);

    if(!getDirecionado()){
        noOrigem->inserirAresta(id_destino,peso);
        noDestino->inserirAresta(id,peso);

        noOrigem->aumentarGrauEntrada();
        noDestino->aumentarGrauEntrada();
    }
    else{
        noOrigem->inserirAresta(id_destino,peso);

        noOrigem->aumentarGrauSaida();
        noDestino->aumentarGrauEntrada();
    }

    this->quant_aresta++;

}*/


void Grafo::mostrarGrafo(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------GRAFO------------"<<endl;
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ".";
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()){
            No* aux = getNo(aresta->getIdDestino());
            if(aresta == no->getPrimeiraAresta() )
                arquivo_saida << aux->getId();
            else
                arquivo_saida << "," << aux->getId();
        }
        arquivo_saida<<endl;
    }
    arquivo_saida<<endl<<endl;
}

void Grafo::mostrarNos(ofstream& arquivo_saida) {
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida<<"-----------AP------------"<<endl;
        arquivo_saida<<"ID. X - Y"<<endl;
        arquivo_saida << no->getId() << ". ";
        arquivo_saida << no->getX() << " - ";
        arquivo_saida << no->getY();
        arquivo_saida << endl;
        no->mostrarClientes(arquivo_saida);
    }
    arquivo_saida<<endl<<endl;
}



void Grafo::mostrarArestas(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------ARESTAS------------"<<endl;
    arquivo_saida<<"[No de Origem , No de Destino] - Peso "<< endl;
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
            arquivo_saida << "[" << no->getId() << "," << aresta->getIdDestino() << "] - P: " << aresta->getPeso() << endl;
        }
    }
    arquivo_saida<<endl<<endl;
}



float Grafo::distanciaEuclidiana(int x1,int y1,int x2, int y2){
    return sqrt( pow(x1-x2,2) + pow(y1-y2,2) );
}


//FUNCIONALIDADES

void Grafo::guloso(ofstream &arquivo_saida) {

}

void Grafo::gulosoRandomizado(ofstream &arquivo_saida) {

}

void Grafo::gulosoRandomizadoReativo(ofstream &arquivo_saida) {

}




