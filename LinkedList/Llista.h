#include "NodeLlista.h"
#include "Posicio.h"
#include <initializer_list>
#include <iostream>
#include <typeinfo>

using namespace std;

#ifndef LLISTA_H
#define LLISTA_H

template <class Element>
class Llista
{
    public:

        Llista();
        Llista(initializer_list<Element> elements);
        Llista(const Llista<Element>& origen);
        
        virtual ~Llista();
        
        int tamany() const;
        bool esBuida() const;
        
        Posicio<Element> principi() const; // return first position, després del sentinella inicial
        Posicio<Element> final() const; // return last position, el sentinella últim
        void print() const;
        
        // NO ENTENC BEN BÉ QUE FA AIXO; SI JA HO TENIM DEFINIT A DALT!! NO S'HA IMPLEMENTAT
        Posicio<Element> rprincipi() const; // return first position
        Posicio<Element> rfinal() const; // return last position
        
        void inserirDespres(Posicio<Element>& position, const Element& element);
        void inserirAbans(Posicio<Element>& position, const Element& element);
        void inserirPrincipi(const Element& element);
        void inserirFinal(const Element& element);

        void elimina(Posicio<Element>& position);
    
    private:
        NodeLlista<Element>* _cap;
        NodeLlista<Element>* _cua;
        int _tamany;
};
/*
    CONSTRUCTOR I DESTRUCTOR
*/

template <class Element>
Llista<Element>::Llista(){
    _tamany=0;
    //Per defecte, cap i cua apuntaran a nullptr a les bandes de l'esquerra i la dreta respectivament (Constructor en NodeLLista)
    //Inicialitzem els dos sentinelles:
    _cap= new NodeLlista<Element>(Element()); 
    _cua= new NodeLlista<Element>(Element());
    (*_cap).fixarSeguent(_cua);
    (*_cua).fixarAnterior(_cap);

    //DEBUGGING
    //cout << "Hem entrat al constructor. Estem construint una llista del tipus:" << endl;
    //cout << typeid(Element).name() << '\n';
}


template <class Element>
Llista<Element>::Llista(initializer_list<Element> elements){
    _tamany=0;
    _cap= new NodeLlista<Element>(Element());
    _cua= new NodeLlista<Element>(Element());
    (*_cap).fixarSeguent(_cua);
    (*_cua).fixarAnterior(_cap);

    for(typename initializer_list<Element>::iterator it=elements.begin(); it!=elements.end(); it++){ //El typename s'ha dutilitzar quan templates perque ho pilli bé
        inserirFinal(*it); //Retorna l'element de l'iterador
    }

}

template <class Element>
Llista<Element>::Llista(const Llista<Element>& origen){
    _tamany=0;
    _cap= new NodeLlista<Element>(Element());
    _cua= new NodeLlista<Element>(Element());
    (*_cap).fixarSeguent(_cua);
    (*_cua).fixarAnterior(_cap);

    //Mateix que amb l'inicializer list però amb els nostres iteradors (Posicio). Anem recorrent la lista i n'extreiem l'element.
    //Com que cada cop creem un nou node (inserirFinal), la nova llista està totalment desvinculada de la primera
    for(Posicio<Element> it=origen.principi(); it!=origen.final(); it=++it){ 
        inserirFinal(*it); 
    }
}

template <class Element>
Llista<Element>::~Llista(){

    //Destructor: destrueix els nodes.
    //DEBUGGING
    //cout << "Hem entrat al destructor. Es una llista amb element:" << endl;
    //cout << typeid(Element).name() << '\n';
    if(!esBuida()){
        Posicio<Element> it=principi();
        while(it!=final()){
            Posicio<Element> aux=++it;
            elimina(it);
            it=aux;
        }
    }
    //Aixo pot donar error en les llistes de cliniques (NO ENTENC PERQUÈ NO PUC BORRAR SENTINELLES)
        //delete _cap;
        //delete _cua;
        //cout << typeid(*_cap).name() << '\n';
        //cout << typeid(*_cua).name() << '\n';

    //DEBUGGING
    //cout << "Comprovar tots eliminats:" << endl;
    //print();
}

/*
    CONSULTORES
*/
template <class Element>
Posicio<Element> Llista<Element>::principi() const{
    return Posicio(_cap->accedirSeguent());
}
template <class Element>
Posicio<Element> Llista<Element>::final() const{
    return Posicio(_cua);
}
template <class Element>
int Llista<Element>::tamany() const{
    return _tamany;
}

template <class Element>
bool Llista<Element>::esBuida() const{
    return _tamany==0;
}

/*
    MODIFICADORES
*/

template <class Element>
void Llista<Element>::inserirFinal(const Element& element){
    //Es crea un node. Primer fem que el node apunti a on toqui
    NodeLlista<Element>* nouNode= new NodeLlista<Element>(element);
    Posicio<Element> novaP= Posicio<Element>(nouNode);
    novaP.fixarAnterior(_cua->accedirAnterior());
    novaP.fixarSeguent(_cua);

    _tamany++;
    //print();
}

template <class Element>
void Llista<Element>::inserirPrincipi(const Element& element){
    //Es crea un node. Primer fem que el node apunti a on toqui
    NodeLlista<Element>* nouNode= new NodeLlista<Element>(element);
    Posicio<Element> novaP= Posicio<Element>(nouNode);
    novaP.fixarSeguent(_cap->accedirSeguent());
    novaP.fixarAnterior(_cap);

    //print();

    _tamany++;
}

template <class Element>
void Llista<Element>::inserirDespres(Posicio<Element>& position, const Element& element){
    /*
        PRIMER: CREAR UN NOU NODE. DESPRES: 
            LINKEJAR EL NODE A L'ESQUERRA I A LA DRETA
            LINKEJAR ELS DOS NODES
    */
   NodeLlista<Element>* nouNode= new NodeLlista<Element>(element);
   position.next().fixarAnterior(nouNode);
   position.fixarSeguent(nouNode);

   _tamany++;
}

template <class Element>
void Llista<Element>::inserirAbans(Posicio<Element>& position, const Element& element){
    /*
        PRIMER: CREAR UN NOU NODE. DESPRES: 
            LINKEJAR EL NODE A L'ESQUERRA I A LA DRETA
            LINKEJAR ELS DOS NODES
    */
   NodeLlista<Element>* nouNode= new NodeLlista<Element>(element);
   position.anterior().fixarSeguent(nouNode);
   position.fixarAnterior(nouNode);

   _tamany++;
}

template <class Element>
void Llista<Element>::elimina(Posicio<Element>& position){

    NodeLlista<Element>* actual = position.elimina();
    delete actual;
    _tamany--;
    //DEBUGGING
    //cout << "Estem eliminant un objecte del tipus:" << typeid(*_cap).name() <<  endl;
    
}

/*
    PRINT (UTILITZADA PER FER DEBUGGING, LA DEIXO AQUÍ)
*/
template <class Element>
void Llista<Element>::print() const {
     
    for (Posicio<Element> it2=principi(); it2!=final(); it2=++it2) {
        cout <<"A dins del for: ";
        cout << *it2 << endl;
    }
    cout << "Es buida: " << esBuida() << " Tamany:" << tamany() << endl;
}


#endif