#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"


using namespace std;
int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Mostrar Aps e seus clientes" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida){

    switch (selecao) {
        case 1:{
            grafo->mostrarNos(arquivo_saida);


            break;
        }

        case 3:{

            break;
        }
        case 9:{
            //grafo->desenharSolucao();

        }
    }
}


Grafo* leitura(ifstream& arquivo_entrada){

    int quantAps;
    int quantClientes;
    int x,y;

    arquivo_entrada >> quantAps >> quantClientes;
    Grafo* grafo = new Grafo(quantAps);

    //Inserindo aps
    for (int id = 0; id < quantAps; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirNo(id,x,y);
    }
    //Inserindo clientes
    for (int id = 0; id < quantClientes; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirCliente(id,x,y);
    }
    //Definindo potencia de cada ap
    grafo->definePotencia();

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
