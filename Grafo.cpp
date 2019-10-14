#include <iostream>
#include <fstream>
#include "Grafo.h"
#include "No.h"
#include "FilaEncadeada.h"
#include "Pilha.h"


using namespace std;

//Construtor
Grafo::Grafo(int ordem, bool direcionado, bool ponderado_aresta, bool ponderado_no){
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->ponderado_aresta = ponderado_aresta;
    this->ponderado_no = ponderado_no;
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

bool Grafo::getDirecionado()
{
    return this->direcionado;
}

bool Grafo::getPonderadoAresta()
{
    return this->ponderado_aresta;
}

bool Grafo::getPonderadoNo()
{
    return this->ponderado_no;
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

void Grafo::inserirNo(int id){
    //Verifica se existe pelo menos um No, caso negativo, o primeiro No sera setado
    if(this->primeiro_no != nullptr){
        No* no = new No(id);
        this->ultimo_no -> setProximoNo(no);
        this->ultimo_no = no;
    }
    else{
        this->primeiro_no = new No(id);
        this->ultimo_no = this->primeiro_no;
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



void Grafo::inserirAresta(int id, int id_destino, float peso){

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

}


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
    arquivo_saida<<"-----------NOS------------"<<endl;
    arquivo_saida<<"No - Grau de Entrada - Grau de saida - Peso"<<endl;
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ".";
        arquivo_saida << " - E:" << no->getGrauEntrada();
        arquivo_saida << " - S:" << no->getGrauSaida();
        arquivo_saida << " - P:" << no->getPeso();
        arquivo_saida << endl;
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

int Grafo::mapeamento(int* mapa, int id) {
    for(int i=0; i < this->getOrdem(); i++) {
        if(mapa[i] == id)
            return i;
    }
}

Grafo* Grafo::getSubjacente(){
    Grafo* grafo = new Grafo(this->getOrdem(),false,this->getPonderadoAresta(),this->getPonderadoNo());
    if(this->getDirecionado()) {
        for(No* no = this->getPrimeiroNo(); no != nullptr; no = no->getProximoNo()){
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()){
                grafo->inserirAresta(no->getId(), aresta->getIdDestino(), aresta->getPeso());
                grafo->getNo(no->getId())->setPeso(no->getPeso());
                grafo->getNo(aresta->getIdDestino())->setPeso(this->getNo(aresta->getIdDestino())->getPeso());
            }
        }
        return grafo;
    }
    return nullptr;
}

//------------FUNCIONALIDADES---------------

//CAMINHAMENTO EM LARGURA-------------------
//a função deve receber como parâmetro o Id de um nó e imprimir o conjunto de arestas visitadas a
//partir do mesmo em um percurso em largura indicando, para cada uma, se trata-se ou não de uma aresta
//de retorno
//Responsável:Wiliam

void Grafo::caminhamentoLargura(int id_no, ofstream& arquivo_saida){
    int* mapa = new int[this->getOrdem()];
    No* inic = this->getPrimeiroNo();
    bool* verificavisitado=new bool[this->ordem];
    int indice;

    //preenche o vetor com 0
    for(int i = 0; i < this->ordem; i++, inic = inic->getProximoNo()){
        mapa[i] = inic->getId();
        verificavisitado[i]=false;
    }

    //Fila e ja coloca o no alvo como visitado
    FilaEncadeada* fila = new FilaEncadeada();
    indice = mapeamento(mapa, id_no);
    verificavisitado[indice]=true;

    //começa a fila com o primeiro vertice visitado
    fila->enfileira(id_no);

    //repetição até a fila ficar vazia
    No* noAux;
    while(fila->vazia()==false){
        noAux = this->getNo(fila->desenfileira());
        Aresta* auxiliar = noAux->getPrimeiraAresta();
        while(auxiliar!=nullptr){
            //quando ele visita um nó, ele marca no vetor de bool no indice tal como "1" ou "0", se o destino da aresta ja for
            //um indice com 1(true) é porque é de retorno, caso contrario 0(false)nao é retorno.
            indice = mapeamento(mapa, auxiliar->getIdDestino());
            if(verificavisitado[indice] == false) {
                arquivo_saida<<"["<<noAux->getId()<<","<<auxiliar->getIdDestino()<<"] nao é retorno"<<endl;
                verificavisitado[indice] = true;
                fila->enfileira(auxiliar->getIdDestino());
            } else {
                arquivo_saida<<"["<<noAux->getId()<<" , "<<auxiliar->getIdDestino()<<"] é retorno"<<endl;
            }
            auxiliar = auxiliar->getProximaAresta();
        }
    }
}

//-----------------------------------------

//CAMINHAMENTO EM PROFUNDIDADE-------------
//a função deve receber como parâmetro o Id de um nó e imprimir o conjunto de arestas visitadas a
//partir do mesmo em um percurso em profundidade indicando, para cada uma, se trata-se ou não de uma
//aresta de retorno
//Responsável:Wiliam

void Grafo::auxBuscaEmProfundidade(int id_no, bool* aux, ofstream& arquivo_saida){
    aux[id_no] = true;
    No* noAux= getNo(id_no);
    for(Aresta* arestaAux= noAux->getPrimeiraAresta();arestaAux!=nullptr;arestaAux=arestaAux->getProximaAresta()){
            if(aux[arestaAux->getIdDestino()]==false){
                arquivo_saida<<"["<<id_no<<" , "<<arestaAux->getIdDestino()<<"] nao é retorno"<<endl;
                auxBuscaEmProfundidade(arestaAux->getIdDestino(),aux,arquivo_saida);
            }
            else{
                arquivo_saida<<"["<<id_no<<","<<arestaAux->getIdDestino()<<"] é uma aresta de retorno"<<endl;
            }
    }
}

void Grafo::caminhamentoProfundidade(int id_no, ofstream& arquivo_saida){
    bool *aux=new bool[this->ordem];
    for (int i=0;i<this->ordem;i++){
        aux[i]=false;
    }
    auxBuscaEmProfundidade(id_no,aux,arquivo_saida);
}

//-----------------------------------------

//FECHO TRANSITIVO DIRETO DE UM DADO NÓ (PARA GRAFO ORIENTADO)
//para um dado nó v do grafo, a função deve imprimir o Id de todo nó u alcançável por um caminho
//direcionado com origem em v
//Responsável: Lucas

void Grafo::fechoTransitivoDireto(No* no, ofstream& arquivo_saida){
    if(this->getDirecionado()) {
        int* percorrido = new int[this->getOrdem()];
        int* mapa = new int[this->getOrdem()];
        int* acessivel = new int[this->getOrdem()];

        No* aux = this->getPrimeiroNo();
        for(int i=0; i < this->getOrdem(); i++, aux = aux->getProximoNo()) {
            mapa[i] = aux->getId();
            if(aux->getId() == no->getId())
                percorrido[i] = 1;
            else
                percorrido[i] = 0;
            acessivel[i] = 0;
        }

        aux = no;
        for(int flag=1; flag==1;){
            Aresta* aresta = aux->getPrimeiraAresta();
            percorrido[mapeamento(mapa, aux->getId())] = 1;
            int indiceDestino;
            while(aresta != nullptr) {
                indiceDestino = mapeamento(mapa, aresta->getIdDestino());
                if(!percorrido[indiceDestino]) {
                    acessivel[indiceDestino] = 1;
                }
                aresta = aresta->getProximaAresta();
            }
            flag=0;
            for(int i=0; i < this->getOrdem() && flag == 0; i++) {
                if(acessivel[i] && !percorrido[i]) {
                    aux = this->getNo(mapa[i]);
                    flag = 1;
                } else
                    flag = 0;
            }
        }

        arquivo_saida<<"---Fecho Transitivo Direto---"<<endl;
        arquivo_saida<<"[Conjunto de nos acessiveis com origem em v]"<<endl;
        arquivo_saida << "[";
        int priImpresao=1;
        for(int i=0; i < this->getOrdem(); i++) {
            if(acessivel[i] && priImpresao) {
                arquivo_saida << mapa[i];
                priImpresao = 0;
            } else if(acessivel[i])
                arquivo_saida << ", " << mapa[i];
        }
        arquivo_saida << "]" << endl;
        arquivo_saida << endl << endl;

        delete[] percorrido;
        delete[] mapa;
        delete[] acessivel;
    }
}

//-----------------------------------------

//FECHO TRANSITIVO INDIRETO DE UM DADO NÓ (PARA GRAFO ORIENTADO)
//para um dado nó v do grafo, a função deve imprimir o Id de todo nó u que pode alcançar o nó v por
//um caminho direcionado com origem em u
//Responsável: Lucas

void Grafo::fechoTransitivoIndireto(No* no, ofstream& arquivo_saida){
    if(this->getDirecionado()) {
        int* mapa = new int[this->getOrdem()];
        int* acessivel = new int[this->getOrdem()];

        No* aux = this->getPrimeiroNo();
        for(int i=0; i < this->getOrdem(); i++, aux = aux->getProximoNo()) {
            mapa[i] = aux->getId();
            if(aux->getId() == no->getId())
                acessivel[i] = 1;
            else
                acessivel[i] = 0;
        }
        //Continuar

        for(int flag=1; flag==1; ){
            flag = 0;
            aux = this->getPrimeiroNo();
            while(aux !=nullptr) {
                int indiceAtual = mapeamento(mapa, aux->getId());
                Aresta* aresta = aux->getPrimeiraAresta();
                while(aresta != nullptr) {
                    int indiceDestino = mapeamento(mapa, aresta->getIdDestino());
                    if(acessivel[indiceDestino] && !acessivel[indiceAtual]) {
                        acessivel[indiceAtual] = 1;
                        flag = 1;
                    }
                    aresta = aresta->getProximaAresta();
                }
                aux = aux->getProximoNo();
            }
        }

        arquivo_saida<<"---Fecho Transitivo Indireto---"<<endl;
        arquivo_saida<<"[Conjunto de nos que acessam v com origem em u]"<<endl;
        arquivo_saida << "[";
        int priImpresao=1;
        for(int i=0; i < this->getOrdem(); i++) {
            if(mapa[i] != no->getId()) {
                if(acessivel[i] && priImpresao) {
                    arquivo_saida << mapa[i];
                    priImpresao = 0;
                } else if(acessivel[i])
                    arquivo_saida << ", " << mapa[i];
            }
        }
        arquivo_saida << "]" << endl;
        arquivo_saida << endl << endl;

        delete[] mapa;
        delete[] acessivel;
    }
}

//-----------------------------------------

//DIJKSTRA: CAMINHO MÍNIMO (PARA GRAFOS ORIENTADOS OU NÃO ORIENTADOS)
//para um dado grafo (orientado ou não, ponderado ou não), a função deve receber o Id de dois
//vértices u e v e mostrar um caminho mínimo entre u e v, bem como o custo deste caminho calculado a
//partir do algoritmo de Dijkstra. O caminho a ser mostrado consiste na sequência de vértices entre u e v tal
//que o somatório dos pesos das arestas entre vértices consecutivos na sequência seja mínima. Note que,
//para grafos não ponderados, um caminho mínimo entre dois vértices consiste numa sequência de vértices
//entre os mesmos com o menor número de arestas
//Responsável: Lucas

void Grafo::dijkstra(No* noU, No* noV, ofstream& arquivo_saida){
    float* distancia = new float[this->getOrdem()];
    int* mapa = new int[this->getOrdem()];
    int* aPercorrer = new int[this->getOrdem()];
    int* noAnterior = new int[this->getOrdem()];

    No* no = this->getPrimeiroNo();
    for(int i=0; i < this->getOrdem(); i++, no = no->getProximoNo()) {
        mapa[i] = no->getId();
        if(no->getId() == noU->getId()) {
            distancia[i] = 0;
            aPercorrer[i] = 0;
        } else {
            distancia[i] = -1;
            aPercorrer[i] = 1;
        }
        noAnterior[i] = -1;
    }

    auxDijkstra(distancia, aPercorrer, noAnterior, mapa, noU->getId());

    arquivo_saida<<"---------DIJKSTRA---------"<<endl;
    arquivo_saida<<"[Caminho entre noU e noV] - custo de caminho minimo"<<endl;
    if(distancia[mapeamento(mapa, noV->getId())] != -1) {
        arquivo_saida << "[" << noV->getId();
        int caminho = noAnterior[mapeamento(mapa, noV->getId())];
        while(caminho != -1) {
            arquivo_saida << ", " << caminho;
            caminho = noAnterior[mapeamento(mapa, caminho)];
        }
        arquivo_saida << "] - " << distancia[mapeamento(mapa, noV->getId())] << endl;
        arquivo_saida << endl << endl;
    } else {
        arquivo_saida << "[" << noU->getId() << ", " << noV->getId() << "] - -1";
        arquivo_saida << endl << endl;
    }
    delete[] aPercorrer;
    delete[] noAnterior;
    delete[] distancia;
    delete[] mapa;
}
void Grafo::auxDijkstra(float* distancia, int* aPercorrer, int* noAnterior, int* mapa, int atual){
    No* no = this->getNo(atual);
    Aresta* aresta = no->getPrimeiraAresta();
    int indiceAtual = mapeamento(mapa, atual);
    int indiceAresta;
    while(aresta != nullptr) {
        indiceAresta = mapeamento(mapa, aresta->getIdDestino());
        if(distancia[indiceAresta] != -1) {
            if(this->getPonderadoAresta()) {
                if(distancia[indiceAresta] > distancia[indiceAtual] + aresta->getPeso()) {
                    distancia[indiceAresta] = distancia[indiceAtual] + aresta->getPeso();
                    noAnterior[indiceAresta] = atual;
                }
            } else {
                if(distancia[indiceAresta] > distancia[indiceAtual] + 1) {
                    distancia[indiceAresta] = distancia[indiceAtual] + 1;
                    noAnterior[indiceAresta] = atual;
                }
            }
        } else {
            if(this->getPonderadoAresta()) {
                distancia[indiceAresta] = distancia[indiceAtual] + aresta->getPeso();
                noAnterior[indiceAresta] = atual;
            } else {
                distancia[indiceAresta] = distancia[indiceAtual] + 1;
                noAnterior[indiceAresta] = atual;
            }
        }
        aresta = aresta->getProximaAresta();
    }
    int menor = -1;
    for(int i=0; i < this->getOrdem() && menor == -1; i++){
        if(aPercorrer[i]) {
            if(distancia[i] != -1) {
                menor = distancia[i];
                atual = mapa[i];
            }
        }
    }
    if(menor != -1) {
        for(int i=0; i < this->getOrdem(); i++) {
            if(aPercorrer[i])
                if(distancia[i] != -1)
                    if(distancia[i] < menor){
                        menor = distancia[i];
                        atual = mapa[i];
                    }
        }
        aPercorrer[indiceAtual] = 0;
        auxDijkstra(distancia, aPercorrer, noAnterior, mapa, atual);
    }
}

//-----------------------------------------

//FLOYD: CAMINHO MÍNIMO (PARA GRAFOS ORIENTADOS OU NÃO ORIENTADOS)
//para um dado grafo (orientado ou não, ponderado ou não), a função deve receber o Id de dois
//vértices u e v e mostrar um caminho mínimo entre u e v, bem como o custo deste caminho calculado a
//partir do algoritmo de Floyd. O caminho a ser mostrado consiste na sequência de vértices entre u e v tal
//que o somatório dos pesos das arestas entre vértices consecutivos na sequência seja mínima. Note que,
//para grafos não ponderados, um caminho mínimo entre dois vértices consiste numa sequência de vértices
//entre os mesmos com o menor número de arestas
//Responsável: Augusto

void Grafo::floyd(No* noU, No* noV, ofstream& arquivo_saida){
    int* mapa = new int[this->getOrdem()];
    int* aPercorrer = new int[this->getOrdem()];
    No* no=this->getPrimeiroNo();
    for(int i=0; i < this->getOrdem(); no = no->getProximoNo(), i++) {
        mapa[i] = no->getId();
        if(mapa[i] == noU->getId())
            aPercorrer[i] = 0;
        else
            aPercorrer[i] = 1;
    }
    float** matriz = new float *[this->getOrdem()];
    int* noAterior = new int[this->getOrdem()];
    for(int i=0; i<this->getOrdem(); i++) {
        matriz[i] = new float[this->getOrdem()];
        //noAterior[i] = new int[this->getOrdem()];
    }
	criaMatriz(matriz, noAterior, mapa);
    auxFloyd(matriz, aPercorrer, noAterior, mapa, noU->getId(), noU->getId());

	arquivo_saida << "---------FLOYD---------" << endl;
	arquivo_saida << "[Caminho entre noU e noV] - custo de caminho minimo" << endl;
	if(matriz[mapeamento(mapa, noU->getId())][mapeamento(mapa, noV->getId())] != -1) {
        arquivo_saida << "[" << noV->getId();
        int caminho = noAterior[mapeamento(mapa, noV->getId())];
        while(caminho != -1) {
            arquivo_saida << ", " << caminho;
            caminho = noAterior[mapeamento(mapa, caminho)];
        }
        arquivo_saida << "] - " << matriz[mapeamento(mapa, noU->getId())][mapeamento(mapa, noV->getId())] << endl;
        arquivo_saida << endl << endl;
    } else {
        arquivo_saida << "[" << noU->getId() << ", " << noV->getId() << "] - -1";
        arquivo_saida << endl << endl;
    }
}

void Grafo::auxFloyd(float** matriz, int* aPercorrer, int* noAnterior, int* mapa, int atual, int idNoU) {
    No* no = this->getNo(atual);
    Aresta* aresta = no->getPrimeiraAresta();
    int indiceNoU = mapeamento(mapa, idNoU);
    int indiceAtual = mapeamento(mapa, atual);
    int indiceAresta;
    while(aresta != nullptr) {
        indiceAresta = mapeamento(mapa, aresta->getIdDestino());

            if(matriz[indiceNoU][indiceAresta] != -1) {
                if(this->getPonderadoAresta()) {
                    if(matriz[indiceNoU][indiceAresta] > matriz[indiceNoU][indiceAtual] + aresta->getPeso()) {
                        matriz[indiceNoU][indiceAresta] = matriz[indiceNoU][indiceAtual] + aresta->getPeso();
                        noAnterior[indiceAresta] = atual;
                    }
                } else {
                    if(matriz[indiceNoU][indiceAresta] > matriz[indiceNoU][indiceAtual] + 1) {
                        matriz[indiceNoU][indiceAresta] > matriz[indiceNoU][indiceAtual] + 1;
                        noAnterior[indiceAresta] = atual;
                    }
                }
            } else {
                if(this->getPonderadoAresta()) {
                    matriz[indiceNoU][indiceAresta] = matriz[indiceNoU][indiceAtual] + aresta->getPeso();
                    noAnterior[indiceAresta] = atual;
                } else {
                    matriz[indiceNoU][indiceAresta] > matriz[indiceNoU][indiceAtual] + 1;
                    noAnterior[indiceAresta] = atual;
                }
            }

        aresta = aresta->getProximaAresta();
    }
    int menor = -1;
    for(int i=0; i < this->getOrdem() && menor == -1; i++){
        if(aPercorrer[i]) {
            if(matriz[indiceNoU][i] != -1) {
                menor = matriz[indiceNoU][i];
                atual = mapa[i];
            }
        }
    }
    if(menor != -1) {
        for(int i=0; i < this->getOrdem(); i++) {
            if(aPercorrer[i])
                if(matriz[indiceNoU][i] != -1)
                    if(matriz[indiceNoU][i] < menor){
                        menor = matriz[indiceNoU][i];
                        atual = mapa[i];
                    }
        }
        for(int i=0; i < this->getOrdem(); i++) {
            if(aPercorrer[i])
                if(matriz[i][indiceNoU] != -1)
                    if(matriz[i][indiceNoU] < menor){
                        menor = matriz[i][indiceNoU];
                        atual = mapa[i];
                    }
        }
        aPercorrer[indiceAtual] = 0;
        auxFloyd(matriz, aPercorrer, noAnterior, mapa, atual, idNoU);
    }
}

void Grafo::criaMatriz(float** matriz, int* noAnterior, int* mapa) {
	for (int i=0; i<this->getOrdem(); i++) {
		for (int j = 0; j < this->getOrdem(); j++) {
            if(i == j)
                matriz[i][j] = 0;
            else
                matriz[i][j] = -1;
		}
		noAnterior[i] = -1;
	}

	No* no = this->getPrimeiroNo();
	int indiceAtual;
	int indiceAresta;
	if(this->getDirecionado()) {
        while(no != nullptr) {
            indiceAtual = mapeamento(mapa, no->getId());
            Aresta* aresta = no->getPrimeiraAresta();
            while(aresta != nullptr) {
                indiceAresta = mapeamento(mapa, aresta->getIdDestino());
                if(indiceAtual > indiceAresta) {
                    if(this->getPonderadoAresta())
                        matriz[indiceAtual][indiceAresta] = aresta->getPeso();
                    else
                        matriz[indiceAtual][indiceAresta] = 1;
                } else {
                    if(this->getPonderadoAresta())
                        matriz[indiceAresta][indiceAtual] = aresta->getPeso();
                    else
                        matriz[indiceAresta][indiceAtual] = 1;
                }
                aresta = aresta->getProximaAresta();
            }
            no = no->getProximoNo();
        }
	} else {
	    while(no != nullptr) {
            indiceAtual = mapeamento(mapa, no->getId());
            Aresta* aresta = no->getPrimeiraAresta();
            while(aresta != nullptr) {
                indiceAresta = mapeamento(mapa, aresta->getIdDestino());
                if(this->getPonderadoAresta()) {
                    matriz[indiceAtual][indiceAresta] = aresta->getPeso();
                    matriz[indiceAresta][indiceAtual] = aresta->getPeso();
                    cout <<"["<< matriz[indiceAresta][indiceAtual] << " " <<"]";
                } else {
                    matriz[indiceAtual][indiceAresta] = 1;
                    matriz[indiceAresta][indiceAtual] = 1;
                }
                aresta = aresta->getProximaAresta();
            }
            no = no->getProximoNo();
        }
	}
}

//-----------------------------------------

//ÁRVORE GERADORA MÍNIMA (PARA GRAFOS NÃO ORIENTADOS PONDERADOS OU NÃO) - PRIM
//para um dado grafo não orientado (ponderado ou não), utilizando o algoritmo de Prim, a função
//deve retornar um conjunto com n-1 arestas que conecte todos os nós do grafo e cujo somatório dos pesos
//das arestas seja mínimo. No caso de grafos não ponderados, qualquer conjunto com n-1 arestas que
//conecte o grafo é solução do problema
//Responsável: Ian
class arestaSimples {
public:
    int origem;
    int destino;
    int peso;
};

void Grafo::AGMPrim(ofstream& arquivo_saida){

    int quantNos=0, i, quantArestasSolucao=0;
    float somatorioPesos = 0;
    int nosJaVisitados[this->getOrdem()];
    No * n = primeiro_no;
    arestaSimples *listaAresta = new arestaSimples[quant_aresta];
    arestaSimples *listaArestasSolucao = new arestaSimples[quant_aresta];

    //Executar até que ache um no nulo
    while (n!=nullptr){
        i=-1;
        nosJaVisitados[quantNos] = n->getId();
        quantNos++;
        for(Aresta* a = n->getPrimeiraAresta(); a != nullptr; a = a->getProximaAresta()) {
            //só adiciona arestas caso o no de destino ainda nao foi explorado
            if(!verificaId(nosJaVisitados,a->getIdDestino(),this->getOrdem())) {
                i++;
                listaAresta[i].origem = a->getIdOrigem();
                listaAresta[i].destino = a->getIdDestino();
                listaAresta[i].peso = a->getPeso();

            }
        }

        //ordena a lista de aresta por peso em ordem crescente
        arestaSimples aux;
        for (int j = 0; j < i; j++) {
            for (int k = j+1; k < i ; k++) {
                if (listaAresta[j].peso > listaAresta[k].peso) {
                    aux = listaAresta[j];
                    listaAresta[j] = listaAresta[k];
                    listaAresta[k] = aux;
                }
            }
        }

        //Caso a lista de Arestas possiveis for vazio chegou no ultimo no da solução
        if(i==-1){
            break;
        }
        listaArestasSolucao[quantArestasSolucao] = listaAresta[0];
        quantArestasSolucao++;
        n = getNo(listaAresta[0].destino);

    }


    arquivo_saida <<"---------AGM PRIM---------"<< endl;
    arquivo_saida <<"[No_Origem -> No_Destino] - Peso"<< endl;
    for (int l = 0; l < quantArestasSolucao; l++) {
        arquivo_saida <<"[" << listaArestasSolucao[l].origem << " -> " << listaArestasSolucao[l].destino << "] - "<< listaArestasSolucao[l].peso << endl;
        somatorioPesos += listaArestasSolucao[l].peso;
    }
    arquivo_saida <<"Somatorio dos Pesos: " << somatorioPesos << endl;

}

//-----------------------------------------

//ÁRVORE GERADORA MÍNIMA (PARA GRAFOS NÃO ORIENTADOS PONDERADOS OU NÃO) - KRUSKAL
//para um dado grafo não orientado (ponderado ou não), utilizando o algoritmo de Kruskal, a função
//deve retornar um conjunto com n-1 arestas que conecte todos os nós do grafo e cujo somatório dos pesos
//das arestas seja mínimo. No caso de grafos não ponderados, qualquer conjunto com n-1 arestas que
//conecte o grafo é solução do problema
//Responsável: Rodrigo



void Grafo::AGMKruskal(ofstream& arquivo_saida){
    int i=0,quantNos=0;

    arestaSimples *listaAresta = new arestaSimples[quant_aresta];
    int nosJaVisitados[this->getOrdem()];

    //Adiciona todas as arestas do grafo em uma lista de arestas
    for (No* n = this->getPrimeiroNo(); n != nullptr; n = n->getProximoNo()) {
        nosJaVisitados[quantNos] = n->getId();
        quantNos++;
        for(Aresta* a = n->getPrimeiraAresta(); a != nullptr; a = a->getProximaAresta()) {
            if(direcionado){
                listaAresta[i].origem = a->getIdOrigem();
                listaAresta[i].destino = a->getIdDestino();
                listaAresta[i].peso = a->getPeso();
                i++;
            }
            //em um grafo não direcionado, só adiciona arestas caso o no de destino ainda nao foi explorado
            else if(!verificaId(nosJaVisitados,a->getIdDestino(),this->getOrdem())) {
                listaAresta[i].origem = a->getIdOrigem();
                listaAresta[i].destino = a->getIdDestino();
                listaAresta[i].peso = a->getPeso();
                i++;
            }
        }
    }

    //ordena a lista de aresta por peso em ordem crescente
    arestaSimples aux;
    for (int j = 0; j < quant_aresta; j++) {
        for (int k = j+1; k < quant_aresta ; k++) {
            if (listaAresta[j].peso > listaAresta[k].peso) {
                aux = listaAresta[j];
                listaAresta[j] = listaAresta[k];
                listaAresta[k] = aux;
            }
        }
    }

    //Cria um grafo de teste para verifica se possui ciclo ao adicionar uma aresta
    Grafo* teste = new Grafo(ordem,direcionado,ponderado_aresta,ponderado_no);
    arestaSimples *listaArestasSolucao = new arestaSimples[quant_aresta];

    //pecorre toda a lista de arestas colocando cada uma no grafo para verificação de ciclos
    //caso o grafo possua ciclo, a aresta é removida e não será colocada na solução
    int quantArestasSolucao = 0;
    for (int j = 0; j < quant_aresta; j++) {
        teste->inserirAresta(listaAresta[j].origem,listaAresta[j].destino,listaAresta[j].peso);
        if(!teste->possuiCiclo()) {
            listaArestasSolucao[quantArestasSolucao] = listaAresta[j];
            quantArestasSolucao++;
        }
        else{
            No *noOrigem = teste->getNo(listaAresta[j].origem);
            No *noDestino = teste->getNo(listaAresta[j].destino);
            noOrigem->removerAresta(noDestino->getId(),direcionado,noDestino);
            noDestino->removerAresta(noOrigem->getId(),direcionado,noOrigem);
        }
    }


    //Imprime Solução
    float somatorioPesos = 0;
    arquivo_saida <<"---------AGM KRUSKAL---------"<< endl;
    arquivo_saida <<"[No_Origem -> No_Destino] - Peso"<< endl;
    for (int l = 0; l < quantArestasSolucao; l++) {
        arquivo_saida <<"[" << listaArestasSolucao[l].origem << " -> " << listaArestasSolucao[l].destino << "] - "<< listaArestasSolucao[l].peso << endl;
        somatorioPesos += listaArestasSolucao[l].peso;
    }
    arquivo_saida <<"Somatorio dos Pesos: " << somatorioPesos << endl;

    delete [] listaAresta;
}

//verifica se o No já está no vetor de visitados, portando não será necessário colocar a aresta
bool Grafo::verificaId(int nosJaVisitados[], int id_no, int tam){
    for (int i = 0; i < tam; i++) {
        if(nosJaVisitados[i] == id_no)
            return true;
    }
    return false;
}
//verifica se um Grafo direcionado ou nao possui ciclos
bool Grafo::possuiCiclo(){
    int *vetor = new int[ordem];
    int nosJaVisitados[this->getOrdem()];
    int quantNo=0;
    No* no = primeiro_no;

    for (int i = 0; i < ordem; ++i)
        vetor[i] = -1;

    if(direcionado){
        Pilha *nosEmExploracao = new Pilha(ordem);
        nosEmExploracao->empilha(no->getId());
        for (Aresta *a = no->getPrimeiraAresta(); a != nullptr; a = a->getProximaAresta()) {
            cout<<a->getIdDestino()<<endl;
            if (nosEmExploracao->contemNaPilha(a->getIdDestino()))
                return true;
            else
                if(auxPossuiCicloDirecionado(a->getIdDestino(), nosEmExploracao)) return true;
        }
        return false;
    }

    else{

        for(; no!= nullptr ; no = no -> getProximoNo()) {
            nosJaVisitados[quantNo] = no->getId();
            quantNo++;
            for (Aresta *a = no->getPrimeiraAresta(); a != nullptr; a = a->getProximaAresta()) {
                if(!verificaId(nosJaVisitados,a->getIdDestino(),quantNo)) {
                    int v1 = auxPossuiCiclo(vetor, no->getId());
                    int v2 = auxPossuiCiclo(vetor, a->getIdDestino());
                    if (v1 == v2) return true;
                    else {
                        int v1_set = auxPossuiCiclo(vetor, v1);
                        int v2_set = auxPossuiCiclo(vetor, v2);
                        vetor[v1_set] = v2_set;
                    }
                }
            }
        }
        return false;
    }

}

int Grafo::auxPossuiCiclo(int vetor[],int id) {
    if(vetor[id] == -1)
        return id;
    else
        auxPossuiCiclo(vetor,vetor[id]);
}

bool Grafo::auxPossuiCicloDirecionado(int idDestino,Pilha nosEmExploracao[]){
    No *no = getNo(idDestino);
    nosEmExploracao->empilha(no->getId());
    for (Aresta *a = no->getPrimeiraAresta(); a != nullptr; a = a->getProximaAresta()) {
        if(nosEmExploracao->contemNaPilha(a->getIdDestino()))
            return true;
        else
            if(auxPossuiCicloDirecionado(a->getIdDestino(),nosEmExploracao)) return true;
    }

    nosEmExploracao->desempilha();
    return false;

}
//-----------------------------------------

//FECHO TRIÁDICO---------------------------
//Um fecho triádico ocorre em uma rede social se duas pessoas que tem um amigo em comum
//também são amigas entre si. O coeficiente de agrupamento (clustering coefficient) de uma rede é uma
//métrica que indica a frequência com este fenômeno ocorre na rede.
//Dado um grafo G, chamamos de tríade um par de vértices {u,v} com um vizinho em comum w. Se
//os vértices u e v são vizinhos, dizemos que a tríade é fechada (este é um caso onde há um fecho triádico).
//Caso contrário, dizemos que a tríade é aberta. Note que para cada três vértices u, v e w mutuamente
//adjacentes, existem três tríades fechadas. O coeficiente de agrupamento de um grafo é dado pelo número
//de tríades fechadas divido pelo total de tríades (incluindo tríades abertas e fechadas). Convencionamos que
//o coeficiente de agrupamento de um grafo sem tríades é zero.
//Responsável: Lucas

void Grafo::fechoTriadico(ofstream& arquivo_saida){
    Grafo* grafo;
    if(this->getDirecionado())
        grafo = this->getSubjacente();
    else
        grafo = this;
    No* no = grafo->getPrimeiroNo();
    int triadeFechada = 0;
    int triadeAberta = 0;

    Aresta* anterior;
    Aresta* proxima;
    while(no != nullptr) {
        anterior = no->getPrimeiraAresta();
        if(anterior != nullptr) {
            proxima = anterior->getProximaAresta();
        } else {
            proxima = nullptr;
        }
        while(proxima != nullptr) {
            if(ehVizinho(grafo->getNo(anterior->getIdDestino()), grafo->getNo(proxima->getIdDestino())))
                triadeFechada++;
            else
                triadeAberta++;
            anterior = proxima;
            proxima = proxima->getProximaAresta();
        }
        no = no->getProximoNo();
    }

    double coefTriad;
    if(triadeFechada == 0 && triadeAberta == 0)
        coefTriad = 0;
    coefTriad = (double)(triadeFechada)/(triadeFechada + triadeAberta);

    arquivo_saida<<"------Fecho Triadico------"<<endl;
    arquivo_saida<<"Triades Fechadas: " << triadeFechada << endl;
    arquivo_saida<<"Triades Abertas: " << triadeAberta << endl;
    arquivo_saida<<"Coeficiente de Agrupamento: " << coefTriad << endl;
    arquivo_saida<<endl<<endl;

    if(this->getDirecionado())
        delete grafo;
}

bool Grafo::ehVizinho(No* noU, No* noV) {
    if(this->getDirecionado()) {
        Aresta* aux = noU->getPrimeiraAresta();
        while(aux != nullptr){
            if(aux->getIdDestino() == noV->getId())
                return true;
            aux = aux->getProximaAresta();
        }
        aux = noV->getPrimeiraAresta();
        while(aux != nullptr) {
            if(aux->getIdDestino() == noU->getId())
                return true;
            aux = aux->getProximaAresta();
        }
        return false;
    } else {
        Aresta* aux = noU->getPrimeiraAresta();
        while(aux != nullptr){
            if(aux->getIdDestino() == noV->getId())
                return true;
            aux = aux->getProximaAresta();
        }
        return false;
    }
}

//-----------------------------------------
