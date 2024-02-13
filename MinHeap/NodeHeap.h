using namespace std;
#include <iostream>

#ifndef NODEHEAP_H
#define NODEHEAP_H


template <class Clau, class Valor >
class NodeHeap {
    public:
        NodeHeap(const Clau& key); //O(1): Constructor base que entra amb una clau

        NodeHeap(const NodeHeap<Clau,Valor>& orig); //O(1): Constructor còpia a partir d'un node

    /* Modificadors */
        void setClau(const Clau& key); //O(1): Setter clau
        void setValue(const Valor& value); //O(1): setter valor

    /* Consultors */
        const Clau& getKey() const; //O(1): Retorna la key del node
        const Valor& getValue() const; //O(1): Retorna el valor del node

    /* Operacions */
        
        bool operator==(const NodeHeap<Clau,Valor >& node) const; //O(1): Comprova si dos nods són iguals (sobrecàrrega de ==)

    private:
        Clau key; //Clau del node
        Valor value; //Llista de valors
};


/*
    Constructors i destructos estàndards 
*/

//Constructor normal
template<class Clau, class Valor>
NodeHeap<Clau,Valor>:: NodeHeap(const Clau& key){
    this->setClau(key);
    //Faltaria el setValue()...
}

//Constructor còpia
template<class Clau, class Valor>
NodeHeap<Clau,Valor>:: NodeHeap(const NodeHeap<Clau,Valor>& orig){
    this->setClau(orig.getKey());
    this->setValue(orig.getValue());
}

/*
    Getters
*/

//Retorna la key
template<class Clau, class Valor>
const Clau& NodeHeap<Clau,Valor>:: getKey() const{
    return this->key;
}

//Retorna el valor
template<class Clau, class Valor>
const Valor& NodeHeap<Clau,Valor>:: getValue() const{
    return this->value;
}


/*
    Setters
*/
//Setter de la key
template<class Clau, class Valor>
void NodeHeap<Clau,Valor>:: setClau(const Clau& key){
    this->key=key;
}

template<class Clau, class Valor>
void NodeHeap<Clau,Valor>:: setValue(const Valor& value){
    this->value=value;
}

/*
    OPERACIONS
*/

//Sobrecàrrega de l'operador ==. Comprova que la key del node i el value del node passat per paràmetre sigui igual al nostre node
template<class Clau, class Valor>
bool NodeHeap<Clau,Valor>:: operator==(const NodeHeap<Clau,Valor >& node) const{
    return (this->key==node.getKey()) && (this->value==node.getValue());
}


#endif