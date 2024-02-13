#include "CuaEstatica.h"
#include <iostream>
#include <stdexcept>

//Constructors
CuaEstatica:: CuaEstatica() //_size(0),_rear(0) tambe seria valid
{
    std::cout << "Estructura creada"<<std::endl;
    
    this->_size=0;
    this->_rear=0;
}
CuaEstatica:: CuaEstatica(const CuaEstatica& origen){ 

    for(int i=0;i< origen.size();i++){ //podem accedir als atributs privats perquè l'objecte continua sent de la mateixa classe
        this->_data[i]= origen._data[i];
    }   
    //Si fos un array dinàmic, a més a més hauriem de demanarhi memòria! Perque si ens carreguem el primer, aleshores perdriem l'objecte copiat!
    
    this->_rear=origen._rear;
    this->_size=origen._size;
}
CuaEstatica::~CuaEstatica(){
    std::cout << "Es destrueix" << std::endl;
    //Si fos dinàmic l'array, aqui l'hauriem de destruir
}

void CuaEstatica::enqueue(const int key){
    //Comprovar si està plena:
        //throw excep
    if(isFull()){
        throw std::string ("Cua plena");
    }else{
        //Pas1:assignem key
        _data[_rear]=key;
        //Pas2:augmentem rear
        _rear++;
        //Pas3:augmentem size
        _size++;
    }
}
void CuaEstatica::dequeue(){
    if(isEmpty()){
            throw std::string ("Cua buida");
    }else{
        //Pas1: shift a l'esquerra
        for(int i=1;i<_size;i++){
            _data[i-1]=_data[i];
        }
        //Pas2:desminuim rear
        _rear--;
        //Pas3:desminuim size
        _size--;
    }
}

bool CuaEstatica::isFull() const{
    return _size==DEFAULT_MAX_SIZE;
}
bool CuaEstatica::isEmpty() const{
    return _size==0;
}

void CuaEstatica::print() const{
    std::cout << "( "; 
    for(int i=0; i<_size;i++){
        std::cout << _data[i] << ", ";
    }
    std:: cout << ")" << std::endl;
}

const int CuaEstatica::getFront() const{
    if(!isEmpty()){
        return _data[0];
    }else{
        throw std::string ("Cua buida");
    }

}
int CuaEstatica::size() const{
    return _size;
}


