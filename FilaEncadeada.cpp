#include"FilaEncadeada.h"

FilaEncadeada::FilaEncadeada(){
    NoInicio=nullptr;
    NoFim=nullptr;
    tamanho=0;
}

FilaEncadeada::~FilaEncadeada(){
 NoFila *p=NoInicio;
    while(p!=nullptr)
    {

        if(p->getProx()!=nullptr)
        {
            p=p->getProx();
        }
        else
          p=nullptr;
        delete NoInicio;
        NoInicio = p;
    }

}

int FilaEncadeada::getInicio() // retorna No do inicio
{

    if(!vazia())
    {
        return NoInicio->getInfo();
    }
    else
    {
        cout<<"Lista vazia\n";
        exit(1);
    }

}

void FilaEncadeada::enfileira(int val) // insere No no fim
{
NoFila *p = new NoFila();
p->setInfo(val);
p->setProx(nullptr);

if(NoFim == nullptr)
NoInicio = p; // insere o primeiro No
else
NoFim->setProx(p); // liga No p na fila
NoFim = p; // No p passa a ser o ultimo
}

int FilaEncadeada::desenfileira() // elimina No do inicio
{
NoFila *p;
if(NoInicio != NULL)
{
p = NoInicio;
NoInicio = p->getProx();
if(NoInicio == nullptr)
NoFim = nullptr; // a fila esvaziou
int val = p->getInfo();
delete p; // exclui o No do inicio
return val;
}
cout << "ERRO: Fila vazia" << endl;
exit(1);
}

bool FilaEncadeada::vazia() // verifica se esta vazia
{

    if(NoInicio==nullptr)
        return true;

    else
        return false;

}

int FilaEncadeada::numeroNos()
{

    return tamanho;

}
