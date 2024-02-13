#include "NodeHeap.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

#ifndef MINHEAP_H
#define MINHEAP_H


template<class Clau, class Valor>
class MinHeap {
    public:
        MinHeap(); // O(1): constructor 
        MinHeap(const MinHeap<Clau,Valor>& c); //O(n):mida del vector data. constructor còpia 

        int tamany() const; // O(1): retorna el nombre d'elements que hi ha al heap 
        bool esBuit(); // O(1): retorna cert si és buit, fals en cas contrari 
        void inserir(const Clau& clau, const Valor& valor); // O(ln(n))

        Clau minim(); // O(1): retorna la clau mínima
        Valor valorMinim(); // O(1): retorna el valor de la clau mínima
        
        void eliminaMinim(); // O(ln(n)):alçada del heap. elimina el node amb valor minim
        void imprimir(); // O(n):mida del heap. Imprimeix per pantalla tot el Heap, una línia per a cada nivell de l'arbre
        
        Valor cerca(const Clau& clau); // O(1): crida auxiliar.
        int altura(); // O(1): retorna l'alçada del heap

    private:
        vector< NodeHeap<Clau, Valor> > data;
        int mida;
        Valor cercaAuxiliar(const Clau& clau, int index); //O(n): cerca al heap una clau donada
};


template<class Clau, class Valor>
MinHeap<Clau,Valor>::MinHeap(){
    mida=0;
}

template<class Clau, class Valor>
MinHeap<Clau,Valor>::MinHeap(const MinHeap<Clau,Valor>& c){
    mida= c.tamany();
    data= c.data;
}

template<class Clau, class Valor>
int MinHeap<Clau,Valor>::tamany() const{
    return mida;
}

template<class Clau, class Valor>
bool MinHeap<Clau,Valor>::esBuit(){
    return mida==0;
}

//Posem en el vector el nou nodeHeap.
//Després, anem resseguint l'arbre des de baix per tal de canvia el valor i restablir l'ordre del heap
template<class Clau, class Valor>
void MinHeap<Clau,Valor>::inserir(const Clau& clau, const Valor& valor){
    NodeHeap<Clau,Valor> e(clau);
    e.setValue(valor);
    data.push_back(e);
    mida++;

    if(mida>1){
        int iterador=tamany()-1;
        int aux;
        bool continuar=true;
        NodeHeap<Clau,Valor> aux2(0);
        while(iterador>0 && continuar){
            aux= (iterador-1)/2; //De fet seria: i parell: i-2/2, i senar: i-1/2 (però el int ja tho converteix)
            if(data[aux].getKey()>data[iterador].getKey()){
                aux2= data[aux];
                data[aux]=data[iterador];
                data[iterador]=aux2;
            }else{
                continuar=false;
            }
            iterador=aux;
        }
    }
}


template<class Clau, class Valor>
Clau MinHeap<Clau,Valor>::minim(){
    return data[0].getKey();
}

template<class Clau, class Valor>
Valor MinHeap<Clau,Valor>::valorMinim(){
    return data[0].getValue();
}

//Crec que hauria estat més fàcil fer-ho recursivament però bueno...
template<class Clau, class Valor>
void MinHeap<Clau,Valor>::eliminaMinim(){

    if(esBuit()){
        throw string("està buida");
    }

    data[0]=data[tamany()-1];
    data.pop_back(); // https://stackoverflow.com/questions/60413242/why-after-pop-back-operation-it-still-prints-the-complete-vector
    mida--;
    //Ara hem de ordenar el heap: hem d'anar movent el que hem introduit:
    //Si es mes petit que els dos, ja esta.
    //Si es mes petit que un dels dos, aleshores l'intercanviem per aquell
    //Si es mes petit que els dos, l'intercanviem pel més petit
    //Hem d'anar revisant que tingui dos fills (iterador*2+2<=tamany())

    int iterador=0;
    int aux;
    bool continuar=true;
    NodeHeap<Clau,Valor> aux2(0);
    /*
    cout << "__________________" << endl;
    cout << "Anem a capgirar" << endl;
    cout << "Tenim el heap: " << endl;
    imprimir();
    */
    while(continuar){
        /*
        cout << "Iterador: " << iterador << endl;
        cout << "Tamany: " << tamany() << endl;
        cout << "Pare: " << data[iterador].getKey() << endl;
        cout << "Fill esquerra: " << data[iterador*2+1].getKey() << endl;
        cout << "Fill dret: " << data[iterador*2+2].getKey() << endl;
        */
        if(iterador*2+2 <= tamany()-1){ //Comprovem que tingui dos fills
            if(data[iterador*2+1].getKey()<data[iterador*2+2].getKey()){ //Si el de l'esquerra és més petit que el de la dreta
                if(data[iterador*2+1].getKey() < data[iterador].getKey()){ //Si el de l'esquerra és més petit que el pare, el capgira
                    aux2= data[iterador*2+1];
                    data[iterador*2+1]=data[iterador];
                    data[iterador]=aux2;
                    iterador=iterador*2+1;
                }else{
                    continuar=false;
                }
            }else{ //Si el de la dreta és més petit que el de l'esquerra
                if(data[iterador*2+2].getKey() < data[iterador].getKey()){ //Si el de la dreta és més petit que el pare, el capgira
                    aux2= data[iterador*2+2];
                    data[iterador*2+2]=data[iterador];
                    data[iterador]=aux2;
                    iterador=iterador*2+2;
                }else{
                    continuar=false;
                }
            }
        }
        else if(iterador*2+1==tamany()-1){ //Si té només fill esquerra, aleshores entrarà aquí. Si no, vol dir que no té més fills!
            if(data[iterador*2+1].getKey() < data[iterador].getKey()){ //Si el fill és més petit que el pare, el capgirem
                aux2= data[iterador*2+1];
                data[iterador*2+1]=data[iterador];
                data[iterador]=aux2;
            }
            continuar=false; //Ja haurem acabat!
        }else{ //Si no té ni fill esquerra ni fill dret
            continuar=false; 
        }
    }
    /*
    cout << "Tenim el heap: " << endl;
    imprimir();
    cout << "__________________" << endl;
    */
}

//Senzillament anem iterant, amb la separació corresponent a cada línia
template<class Clau, class Valor>
void MinHeap<Clau,Valor>::imprimir(){
    int iterador=0;
    int n=1;
     for (NodeHeap<Clau,Valor> e: data) {
        iterador++;
        cout << "K: " << e.getKey() << ", V: " << e.getValue() << " | ";
        if((int)pow(2,n)-1==iterador){
            cout << endl;
            n++;
        }
    }
    cout << endl;
}

template<class Clau, class Valor>
Valor MinHeap<Clau,Valor>::cerca(const Clau& clau){
    //El cost és O(n) però el podem intentar optimitzar una mica
    if(esBuit()){
        throw string("Està buida");
    }
    Valor e = cercaAuxiliar(clau,0);
    if(e!=Valor()){
        return e;
    }else{
        throw string("No s'ha trobat");
    }
}

template<class Clau, class Valor>
Valor MinHeap<Clau,Valor>::cercaAuxiliar(const Clau& clau, int index){

    //Cas base: atura recursivitat
    if(index >= tamany()){ 
        return Valor();
    }

    //Si el trobem, retornem el valor
    if(clau==data[index].getKey()){
        return data[index].getValue();
    }

    //Aturem la cerca si la Clau ya és menor q el q tenim!
    if (clau < data[index].getKey()) { 
        return Valor();
    }

    //Busquem a la dreta, retornem si ho trobem (Drt)
    Valor dret= cercaAuxiliar(clau,index*2+2);
    if (dret != Valor()) {
        return dret;
    }
    //Busquem a l'esquerra, retornem si ho trobem (Esq)
    Valor esquerra= cercaAuxiliar(clau,index*2+1);
    if (esquerra != Valor()) {
        return esquerra;
    }
    
    return Valor(); //Retornem valor si no l'hem trobat a cap branca
}

template<class Clau, class Valor>
int MinHeap<Clau,Valor>::altura(){
    //Podem recorre el vector i anar sumant +1. Tanmateix, sabem que l'altura és ln(n):
    int altura = floor(log2(tamany()));
    return altura+1;
}

#endif