#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"
#include <math.h>

using namespace std;
int menu(){

    int selecao;
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Mostrar Aps e seus clientes" << endl;
    cout << "[2] Mostrar Grafo de conflito" << endl;
    cout << "[3] Guloso" << endl;
    cout << "[4] Guloso Randomizado" << endl;
    cout << "[5] Guloso Randomizado Reativo" << endl;
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

        case 2:{
            grafo->mostrarGrafo(arquivo_saida);
            break;
        }

        case 3:{
            arquivo_saida << "-----------GULOSO------------" << endl;
            arquivo_saida << "Interferencia Total: " << grafo->guloso() << endl;
            break;
        }

        case 4:{
            arquivo_saida << "-----------GULOSO RANDOMIZADO------------" << endl;
            float melhorExecucao=99999,piorExecucao=0,media=0,execucaoAtual;


            arquivo_saida << ">>>>>>>>>>ALFA 0.2<<<<<<<<<<" << endl;
            arquivo_saida << "Execucao: Interferencia Total" << endl;
            for (int i = 0; i < 30; i++){
                execucaoAtual=grafo->gulosoRandomizado(0.2,1000);
                media += execucaoAtual;
                if(execucaoAtual<melhorExecucao) melhorExecucao = execucaoAtual;
                if(execucaoAtual>piorExecucao) piorExecucao = execucaoAtual;

                arquivo_saida << i+1 << ": " << execucaoAtual << endl;
            }
            arquivo_saida << "Melhor Execucao: " << melhorExecucao << endl;
            arquivo_saida << "Pior Execucao: " << piorExecucao << endl;
            arquivo_saida << "Media: " << media/30 << endl;
            arquivo_saida << endl;

            arquivo_saida << ">>>>>>>>>>ALFA 0.4<<<<<<<<<<" << endl;
            arquivo_saida << "Execucao: Interferencia Total" << endl;
            for (int i = 0; i < 30; i++){
                execucaoAtual = grafo->gulosoRandomizado(0.4,1000);
                media += execucaoAtual;
                if(execucaoAtual<melhorExecucao) melhorExecucao = execucaoAtual;
                if(execucaoAtual>piorExecucao) piorExecucao = execucaoAtual;

                arquivo_saida << i+1 << ": "<< execucaoAtual << endl;
            }
            arquivo_saida << "Melhor Execucao: "<< melhorExecucao << endl;
            arquivo_saida << "Pior Execucao: "<< piorExecucao << endl;
            arquivo_saida << "Media: " << media/30 << endl;
            arquivo_saida << endl;

            arquivo_saida << ">>>>>>>>>>ALFA 0.5<<<<<<<<<<" << endl;
            arquivo_saida << "Execucao: Interferencia Total" << endl;
            for (int i = 0; i < 30; i++){
                execucaoAtual = grafo->gulosoRandomizado(0.5,1000);
                media += execucaoAtual;
                if(execucaoAtual<melhorExecucao) melhorExecucao = execucaoAtual;
                if(execucaoAtual>piorExecucao) piorExecucao = execucaoAtual;

                arquivo_saida << i+1 << ": " << execucaoAtual << endl;
            }
            arquivo_saida << "Melhor Execucao: " << melhorExecucao << endl;
            arquivo_saida << "Pior Execucao: " << piorExecucao << endl;
            arquivo_saida << "Media: " << media/30 << endl;
            arquivo_saida << endl;
            break;
        }

        case 5:{

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
    Grafo* grafo = new Grafo(quantAps,quantClientes);

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

    //Criar grafo de conflito
    grafo->criarGrafoConflito();

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
