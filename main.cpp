#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"
#include "Gerador de numeros randomicos/util.h"

using namespace std;
int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Mostrar Grafo" << endl;
    cout << "[2] Mostrar Aps e suas coordenadas" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida){

    switch (selecao) {
        case 1:{
            break;
        }
        case 2:{
            grafo->mostrarNos(arquivo_saida);
            break;
        }
        case 3:{

            break;
        }
    }
}


Grafo* leitura(ifstream& arquivo_entrada){

    int quantAps;
    int quantClientes;
    int x,y;

    arquivo_entrada >> quantAps >> quantClientes;
    Grafo* grafo = new Grafo(quantAps);

    for (int id = 0; id < quantAps; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirNo(id,x,y);
    }

    for (int id = 0; id < quantClientes; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirCliente(id,x,y);
    }

    return grafo;

}

int main(int argc, char* argv[]) {

    //Verificação se todos os parâmetros do programa foram encontrados
    if (argc != 3) {

        cout << "ERRO: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;

    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);

	Grafo* grafo = new Grafo();

    if(arquivo_entrada.is_open())
        grafo = leitura(arquivo_entrada);
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
