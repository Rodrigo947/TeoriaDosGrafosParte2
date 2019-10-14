#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"

using namespace std;
int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Mostrar Grafo" << endl;
    cout << "[2] Mostrar Nos e suas informacoes" << endl;
    cout << "[3] Mostrar Arestas e suas informacoes" << endl;
    cout << "[4] Caminhamento em largura" << endl;
    cout << "[5] Caminhamento em profundidade" << endl;
    cout << "[6] Fecho transitivo direto de um dado no" << endl;
    cout << "[7] Fecho transitivo indireto de um dado no" << endl;
    cout << "[8] Dijkstra: caminho minimo" << endl;
    cout << "[9] Floyd: caminho minimo" << endl;
    cout << "[10] Arvore Geradora Minima - Prim" << endl;
    cout << "[11] Arvore Geradora Minima - Kruskal" << endl;
    cout << "[12] Fecho triadico" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida){

    switch (selecao) {

        case 1:{
            grafo->mostrarGrafo(arquivo_saida);
            break;
        }

        case 2:{
            grafo->mostrarNos(arquivo_saida);
            break;
        }

        case 3:{
            grafo->mostrarArestas(arquivo_saida);
            break;
        }
        //Caminhamento em largura
        case 4:{
            int idOrigem;
            cout << "Digite o id do no inicial: ";
            cin >> idOrigem;
            grafo->caminhamentoLargura(idOrigem, arquivo_saida);
            break;
        }
        //Caminhamento em profundidade
        case 5:{
            int idOrigem;
            cout << "Digite o id do no inicial: ";
            cin >> idOrigem;
            grafo->caminhamentoProfundidade(idOrigem, arquivo_saida);
            break;
        }
        //Fecho transitivo direto de um dado no
        case 6:{
            int id;
            cout << "Digite o id do no: ";
            cin >> id;
            if(grafo->procurarNo(id)) {
                grafo->fechoTransitivoDireto(grafo->getNo(id), arquivo_saida);
            } else
                cout << endl << "Id inexistente!" << endl;
            break;
        }
        //Fecho transitivo indireto de um dado no
        case 7:{
            int id;
            cout << "Digite o id do no: ";
            cin >> id;
            if(grafo->procurarNo(id)) {
                grafo->fechoTransitivoIndireto(grafo->getNo(id), arquivo_saida);
            } else
                cout << endl << "Id inexistente!" << endl;
            break;
        }
        //Dijkstra: caminho minimo
        case 8:{
            int idOrigem, idDestino;
            cout << "Digite o id do no inicial: ";
            cin >> idOrigem;
            cout << "Digite o id do no de destino: ";
            cin >> idDestino;
            if(grafo->procurarNo(idOrigem) && grafo->procurarNo(idDestino)) {
                grafo->dijkstra(grafo->getNo(idOrigem), grafo->getNo(idDestino), arquivo_saida);
            } else
                cout << endl << "Id inexistente!" << endl;
            break;
        }
        //Floyd: caminho minimo
        case 9:{
		int idOrigem, idDestino;
		cout << "Digite o id do no inicial: ";
		cin >> idOrigem;
		cout << "Digite o id do no de destino: ";
		cin >> idDestino;
		if (grafo->procurarNo(idOrigem) && grafo->procurarNo(idDestino)) {
			grafo->floyd(grafo->getNo(idOrigem), grafo->getNo(idDestino), arquivo_saida);
		}
		else
			cout << endl << "Id inexistente!" << endl;
            	break;
        }
        //Arvore Geradora Minima - Prim
        case 10:{
            grafo->AGMPrim(arquivo_saida);
            break;
        }
        //Arvore Geradora Minima - Kruskal
        case 11:{
            grafo->AGMKruskal(arquivo_saida);
            break;
        }
        //Fecho triádico
        case 12:{
            grafo->fechoTriadico(arquivo_saida);
            break;
        }

    }
}


Grafo* leitura(ifstream& arquivo_entrada, int direcionado, int ponderadoAresta, int ponderadoNo){

    int ordem;
    int idNoOrigem;
    int idNoDestino;

    arquivo_entrada >> ordem;

    Grafo* grafo = new Grafo(ordem,direcionado,ponderadoAresta,ponderadoNo);

    //Leitura do arquivo

    //Quando grafo não é ponderado na aresta e nem no nó
    if( !grafo->getPonderadoAresta() && !grafo->getPonderadoNo() ){
        while (arquivo_entrada >> idNoOrigem >> idNoDestino)
            grafo->inserirAresta(idNoOrigem,idNoDestino,0);
    }
    //Quando grafo é ponderado na aresta e não no nó
    else if(grafo->getPonderadoAresta() && !grafo->getPonderadoNo() ){
        float pesoAresta;

        while (arquivo_entrada >> idNoOrigem >> idNoDestino >> pesoAresta)
            grafo->inserirAresta(idNoOrigem,idNoDestino,pesoAresta);
    }
    //Quando grafo não é ponderado na aresta e é no nó
    else if(!grafo->getPonderadoAresta() && grafo->getPonderadoNo() ) {
        float pesoNoOrigem, pesoNoDestino;

        while (arquivo_entrada >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino){
            grafo->inserirAresta(idNoOrigem,idNoDestino,0);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }
    //Quando grafo é ponderado na aresta e no nó
    else if(grafo->getPonderadoAresta() && grafo->getPonderadoNo() ){
        float pesoNoOrigem, pesoNoDestino, pesoAresta;
        while (arquivo_entrada >> idNoOrigem >> pesoNoOrigem >> idNoDestino >> pesoNoDestino >> pesoAresta){
            grafo->inserirAresta(idNoOrigem,idNoDestino,pesoAresta);
            grafo->getNo(idNoOrigem)->setPeso(pesoNoOrigem);
            grafo->getNo(idNoDestino)->setPeso(pesoNoDestino);
        }
    }

    return grafo;
}

int main(int argc, char* argv[]) {

    //Verificação se todos os parâmetros do programa foram encontrados
    if (argc != 6) {

        cout << "ERRO: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida> <direcionado> <ponderado_arestas> <ponderado_no> " << endl;
        return 1;

    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);

	Grafo* grafo = new Grafo();

    if(arquivo_entrada.is_open())
        grafo = leitura(arquivo_entrada, atoi(argv[3]), atoi(argv[4]), atoi(argv[5])); //atoi = converte string para int
    else
        cout << "Nao foi possivel abrir o arquivo " << argv[1] << endl;

    int selecao = menu();
    while (selecao!=0){
        selecionar(selecao,grafo,arquivo_saida);
        selecao = menu();
    }

    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de saída
    arquivo_saida.close();

    return 0;
}
