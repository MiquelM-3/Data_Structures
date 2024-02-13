#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

//https://www.codewhoop.com/stack/stack-using-linked-list.html

template <class Element>
class LinkedStack{
    private: 
        Node<Element> *front;
        int num_elements; //Està perque size() tingui un cost O(1). Sino, hauriem d'iterar-ho
    
    public:
        LinkedStack();
        ~LinkedStack();

        int size() const;
        bool empty() const;
        const Element& top() const;
        void print();

        void push(const Element & e);
        void pop();
        
};
//Constructor i dstructor
template <class Element>
LinkedStack<Element>::LinkedStack(){
    this->front=nullptr;
    num_elements=0;
}
template <class Element>
LinkedStack<Element>::~LinkedStack(){
    Node<Element> *auxiliar;
    auxiliar=front;

    while(auxiliar!=nullptr){
        cout << "hola";
        Node<Element>* seguent= auxiliar->getNext();
        delete auxiliar;
        auxiliar=seguent;
    }
    cout << "Destruit correctament";
}

//Consultores
template <class Element>
void LinkedStack<Element>::print(){

    if(!empty()){
        Node<Element> *auxiliar;
        auxiliar=front;
        while(auxiliar!=nullptr){
            cout << auxiliar -> getElement() << endl;
            auxiliar = auxiliar -> getNext();
        }
    }else{
        cout << "Buida" << endl;
    }
}

template <class Element>
bool LinkedStack<Element>::empty() const{
    return num_elements==0;
}

template <class Element>
const Element& LinkedStack<Element>::top() const{
    if(!empty()){
        return front -> getElement();
    }else{
        throw std::string ("Cua plena");
    }
}

template <class Element>
int LinkedStack<Element>::size() const{
    return num_elements;
}

//Modificadores
template <class Element>
void LinkedStack<Element>::push(const Element & e){
    Node<Element> *ptr= new Node<Element>(e);
    ptr->setNext(front);
    front=ptr;
    num_elements++;

}

template <class Element>
void LinkedStack<Element>::pop(){
    if(!empty()){ //Si no tinguéssim empty: num_elements==0 o front==nullptr
        Node<Element> *ptr= front;
        front= front->getNext();
        delete ptr;
        num_elements--;
    }else{
        cout << "Buida!" << endl;
        //Throw out_of_range("Pila buida");
    }
}