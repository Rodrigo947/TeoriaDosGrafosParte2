#ifndef TEORIADOSGRAFOS_ARESTA_H
#define TEORIADOSGRAFOS_ARESTA_H
class Aresta{
private:
    int id_origem;
    int id_destino;
    Aresta* proxima_aresta;
    float peso;

public:
    // Construtor e Destrutor
    Aresta();
    Aresta(int id_origem,int id_destino);
    ~Aresta();
    // Getters
    int getIdOrigem();
    int getIdDestino();
    Aresta* getProximaAresta();
    float getPeso();
    // Setters
    void setProximaAresta(Aresta* aresta);
    void setPeso(float peso);
    void setOrigem(int id_origem);
    void setDestino(int id_destino);

};
#endif //TEORIADOSGRAFOS_ARESTA_H
