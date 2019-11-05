#ifndef TEORIADOSGRAFOS_ARESTA_H
#define TEORIADOSGRAFOS_ARESTA_H
class Aresta{
private:
    int id;
    Aresta* proxima_aresta;
    float peso;

public:
    // Construtor e Destrutor
    Aresta();
    Aresta(int id);
    ~Aresta();
    // Getters
    int getId();
    Aresta* getProximaAresta();
    float getPeso();
    // Setters
    void setProximaAresta(Aresta* aresta);
    void setPeso(float peso);
    void setId(int id);

};
#endif //TEORIADOSGRAFOS_ARESTA_H
