#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "No.h"
#include "FilaEncadeada.h"
#include "Pilha.h"
#include <math.h>
//#include <SFML/Graphics.hpp>
//#include <cstdlib>

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
    int idMenor=0,x1=x,y1=y,x2,y2;
    float menorDistancia;

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

float Grafo::distanciaEuclidiana(int x1,int y1,int x2, int y2){
    return sqrt( (float) (pow(x1-x2,2) + pow(y1-y2,2)) );
}

//Verifica qual cliente possui a maior distancia para o ap
void Grafo::definePotencia(){
    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo())
        ap->atribuirPotenciaTransmissao();
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

void Grafo::criarGrafoConflito(){
    float distancia, somaRaio;

    //Se algum No nao estiver no grafo
    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()) {

        for(No* ap2 = ap->getProximoNo(); ap2 != nullptr; ap2 = ap2->getProximoNo()) {
            distancia = distanciaEuclidiana(ap->getX(),ap->getY(),ap2->getX(),ap2->getY());
            somaRaio = ap->getPotencia()+ap2->getPotencia();

            if(somaRaio >= distancia){
                ap->inserirAresta(ap2->getId());
                ap2->inserirAresta(ap->getId());
                this->quant_aresta++;
            }

        }

    }

}


void Grafo::mostrarGrafo(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------GRAFO------------"<<endl;
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ".";
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()){
            No* aux = getNo(aresta->getId());
            if(aresta == no->getPrimeiraAresta() )
                arquivo_saida << aux->getId();
            else
                arquivo_saida << "," << aux->getId();
        }
        arquivo_saida<<" Canal: "<<no->getCanal()<<endl;
    }
    arquivo_saida<<endl<<endl;
}

void Grafo::mostrarNos(ofstream& arquivo_saida) {
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida<<"-----------AP------------"<<endl;
        arquivo_saida<<"ID. X - Y / Potencia de Transmissao"<<endl;
        arquivo_saida << no->getId() << ". ";
        arquivo_saida << no->getX() << " - ";
        arquivo_saida << no->getY() << " / ";
        arquivo_saida << no->getPotencia();
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
            arquivo_saida << "[" << no->getId() << "," << aresta->getId() << "] - P: " << aresta->getPeso() << endl;
        }
    }
    arquivo_saida<<endl<<endl;
}






//FUNCIONALIDADES

int* Grafo::baseCanais1611(){
    //Definindo todos os aps possiveis com os canais 1,6 e 11
    int vetorDeCanais[ordem],cont=0,contId=0;
    int* vetorIdsSemCanais = new int[ordem];
    bool canal1,canal6,canal11;

    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()) {
        canal1=false;canal6=false,canal11=false;
        cont=0;
        for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
            No *ap2 = getNo(aresta->getId());
            vetorDeCanais[cont] = ap2->getCanal();
            cont++;
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==1){
                canal1=true;
                break;
            }
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==6){
                canal6=true;
                break;
            }
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==11){
                canal11=true;
                break;
            }
        }
        if(!canal1) ap->setCanal(1);
        else if(!canal6) ap->setCanal(6);
        else if(!canal11) ap->setCanal(11);
        else{
            vetorIdsSemCanais[contId] = ap->getId();
            contId++;
        }
    }
    vetorIdsSemCanais[contId]=-1;
    return vetorIdsSemCanais;
}


void Grafo::guloso(ofstream &arquivo_saida) {
    int *vetorIdsSemCanais = baseCanais1611();
    for (int i = 0;  ; i++) {
        if(vetorIdsSemCanais[i]==-1) break;
        No* ap = getNo(vetorIdsSemCanais[i]);

    }

}

void Grafo::gulosoRandomizado(ofstream &arquivo_saida) {
    baseCanais1611();
}

void Grafo::gulosoRandomizadoReativo(ofstream &arquivo_saida) {

}

/*void Grafo::desenharSolucao(){

    using namespace sf;
    RenderWindow window(VideoMode(650, 600), "APS e Ranges");

    CircleShape *vetorDeAps = new CircleShape[ordem];
    RectangleShape vetorDeClientes[200];
    Text *vetorDeIds = new Text[240];
    Font fonte;
    fonte.loadFromFile("arial.ttf");

    int quantAps = 0,quantClientes = 0, quantIds=0,x=0,y=0,potencia=0;

    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()){
        //AP
        x = ap->getX();
        y = ap->getY();
        potencia = ap->getPotencia();
        vetorDeAps[quantAps].setRadius(potencia);
        vetorDeAps[quantAps].setOrigin(potencia,potencia);
        vetorDeAps[quantAps].setPosition(x,y);
        Color cor(rand()%200,rand()%254,rand()%254);
        vetorDeAps[quantAps].setFillColor(Color::Transparent);
        vetorDeAps[quantAps].setOutlineThickness(3);
        vetorDeAps[quantAps].setOutlineColor(cor);
        window.draw(vetorDeAps[quantAps]);
        quantAps++;


        //Id do AP

        //Text texto(to_string(ap->getId()),fonte,15);
        vetorDeIds[quantIds].setFont(fonte);
        vetorDeIds[quantIds].setString(to_string(ap->getId()));
        vetorDeIds[quantIds].setCharacterSize(15);
        vetorDeIds[quantIds].setOrigin(15,15);
        vetorDeIds[quantIds].setPosition(x,y);
        //vetorDeIds[quantIds] = texto;
        //window.draw(vetorDeIds[quantIds]);
        quantIds++;

        //Clientes
        for(No* cliente = ap->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()){
            x = cliente->getX();
            y = cliente->getY();
            /*RectangleShape rect(Vector2f(10,10));
            rect.setOrigin(10,10);
            rect.setFillColor(Color::Red);
            rect.setPosition(x*2,y*2);
            vetorDeClientes[quantClientes] = rect;
            window.draw(rect);
            quantClientes++;*/

            //Id do Cliente

            /*vetorDeIds[quantIds].setFont(fonte);
            vetorDeIds[quantIds].setString(to_string(cliente->getId()));
            vetorDeIds[quantIds].setCharacterSize(15);
            vetorDeIds[quantIds].setOrigin(15,15);
            vetorDeIds[quantIds].setPosition(x,y);
            vetorDeIds[quantIds].setFillColor(Color::Red);
            quantIds++;

        }
    }
    for (int i = 0; i < quantIds; i++) {
        window.draw(vetorDeIds[i]);
    }
    window.display();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

    }
}*/


