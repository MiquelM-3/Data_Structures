#ifndef CUAESTATICA_H
#define CUAESTATICA_H

#include <iostream>

class CuaEstatica{
    private:
        enum{DEFAULT_MAX_SIZE=30};
        int _size; //mida de la cua
        int _rear; //darrere element on insertar a la cua
        int _data [DEFAULT_MAX_SIZE]; //estàtic;

    public:
        CuaEstatica();
        CuaEstatica(const CuaEstatica& origen);
        virtual ~CuaEstatica();

        void enqueue(const int key); //const al mig: el paràmetre és constant, no canvia el valor del paràmetre
        void dequeue(); 

        bool isFull() const;
        bool isEmpty() const;

        void print() const;
        const int getFront() const; //const al davant: el paràmetre integer (el que retornem) no es pot canviar (pero si llegir) 
                                    //const al final:la funció és consultora, els atributs no canviaran.
        int size() const;
};

#endif //CUAESTATICA_H
