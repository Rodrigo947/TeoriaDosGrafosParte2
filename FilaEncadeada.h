#ifndef FILAENCADEADA_H_INCLUDED
#define FILAENCADEADA_H_INCLUDED
#include "NoFila.h"
#include "Grafo.h"
#include "No.h"

class FilaEncadeada
{
private:
NoFila *NoInicio; // ponteiro para No do comeco
NoFila *NoFim; // ponteiro para No do fim
int tamanho;

public:
FilaEncadeada();
~FilaEncadeada();
int getInicio(); // retorna No do inicio
void enfileira(int val); // insere No no fim
int desenfileira(); // elimina No do inicio
bool vazia(); // verifica se esta vazia
int numeroNos();
bool verificaElemento(int tamanho);
};

#endif // FILAENCADEADA_H_INCLUDED
