#include "NodeBinari.h"
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

#ifndef ARBREBINARI_H
#define ARBREBINARI_H

template <class Clau, class Valor>
class ArbreBinari {
    public:
        ArbreBinari(); // O(1): Construeix l’arbre buit.
        ArbreBinari(const ArbreBinari<Clau, Valor>& orig); // O(n): n tamany de l'arbre. Construeix una còpia de l'arbre partir del node original rebut per paràmetre
        virtual ~ArbreBinari(); // O(n): n tamany de l'arbre. Destrueix els nodes de l’arbre binari, començant pel root.

        bool isEmpty() const; // O(1): Retorna cert si l’arbre binari està buit, fals en cas contrari
        int height() const; // O(n): tamany de l'arbre. Retorna un enter amb l’alçada de l’arbre binari de cerca, és a dir, l'alçada del root.

        NodeBinari<Clau,Valor>* insert(const Clau& clau, const Valor& value); //O(1): crida a auxiliar. Afegeix un nou node a l’arbre binari de cerca
        const Valor& valueOf(const Clau& clau) const; //O(1): cridem la funció de search().  Retorna el valor (atribut value) d'un node de l'arbre amb una certa key passada per paràmetre

        void imprimirPreordre(const NodeBinari<Clau,Valor>* n=nullptr) const; // O(1): crida a l'auxiliar. Mostra per consola les claus seguint un recorregut en preordre
        void imprimirInordre(const NodeBinari<Clau,Valor>* n=nullptr) const; //O(1): crida a l'auxiliar. Mostra per consola les claus seguint un recorregut en inordre
        void imprimirPostordre(const NodeBinari<Clau,Valor>* n=nullptr) const; //O(1): crida a l'auxiliar. Mostra per consola les claus seguint un recorregut en postordre
        void imprimirCami(Clau key) const; //O(1): crida a l'axuiliar. Mostra per consola totes les claus des de l’arrel fins a arribar a la clau donada per paràmetre. En el cas que no existeixi la clau, el camí fins a on s’ha arribat per cercar la clau. 

        vector<NodeBinari<Clau,Valor>*> obteValorsRang(int k1, int k2) const; //O(1): crida auxiliar. Retorna un vector amb tots els nodes que són igual o estan entre els dos rangs donats. Si no hi ha elements, el vector retornarà buit.
        void eliminaMinim(); //O(n): serà l'alçada de l'arbre. En el pitjor dels casos, en un arbre degenerat, serà la mida total. Elimina el node que conté la clau més petita a tot l’arbre. Si l’arbre està buit, no fa res. 
    
    protected:
        NodeBinari<Clau,Valor>* root; //Root de l'arbre
        NodeBinari<Clau,Valor>* search(const Clau& k) const; // O(1): cridem l'auxiliar. Troba un element (indexat per la clau) de l’arbre binari de cerca i retorna el node si el troba, en cas contrari retorna nullptr.
    private:
        int _size; //Size de l'arbre
        int getSize() const; //O(1): retorna el size. 
        NodeBinari<Clau,Valor>* insertAuxiliar(NodeBinari<Clau,Valor>* node,const Clau& clau, const Valor& value); //O(n): alçada de l'arbre; en el pitjor dels casos, si és un arbre binari degenerat, sera la mida de l'arbre.
        NodeBinari<Clau,Valor>* searchAuxiliar(NodeBinari<Clau,Valor>* node,const Clau& clau) const; //O(n): en el pitjor dels casos, en cas degenerat, és la mida.
        void obteValorsRangAuxiliar(NodeBinari<Clau,Valor>* node,int& k1,int& k2, vector<NodeBinari<Clau,Valor>*>& v) const; //O(n): pot passar que k1 i k2 siguin mes petits i mes grans que valors min i max. En aquest cas, ha de ser la mida.
    
        //Auxiliars per imprimir:
        void imprimirPreordreAuxiliar(const NodeBinari<Clau,Valor>* n = nullptr) const; ////O(n): tamany de l'arbre. Mostra per consola les claus seguint un recorregut en preordre
        void imprimirInordreAuxiliar(const NodeBinari<Clau,Valor>* n = nullptr) const; ////O(n): tamany de l'arbre. Mostra per consola les claus seguint un recorregut en inordre
        void imprimirPostordreAuxiliar(const NodeBinari<Clau,Valor>* n = nullptr) const; ////O(n): tamany de l'arbre. Mostra per consola les claus seguint un recorregut en postordre
        void imprimirCamiAuxiliar(NodeBinari<Clau,Valor>* node,Clau key) const; //O(n): en el pitjor dels casos, en cas degenerat, és la mida. Mostra per consola totes les claus des de l’arrel fins a arribar a la clau donada per paràmetre. En el cas que no existeixi la clau, el camí fins a on s’ha arribat per cercar la clau. 
};


/*
    Constructors i destructos estàndards 

*/

//Constructor normal
template<class Clau, class Valor>
ArbreBinari<Clau,Valor>:: ArbreBinari(){
    cout << "Arbre binari creat" << endl;
    this->root=nullptr;
    this->_size=0;
}
//Constructor copia
template<class Clau, class Valor>
ArbreBinari<Clau,Valor>:: ArbreBinari(const ArbreBinari<Clau, Valor>& orig){
    cout << "Arbre binari copiat" << endl;
    this->root= new NodeBinari<Clau,Valor>(*(orig.root)); 
    this->_size=orig.getSize();
}

//Destructor
template<class Clau, class Valor>
ArbreBinari<Clau,Valor>:: ~ArbreBinari(){
    cout << "Arbre binari destruit" << endl;
    _size=0;
    delete this->root;
}

/*
    GETTERS I CONSULTORES
*/
//Ens retorna el size de l'arbre
template<class Clau, class Valor>
int ArbreBinari<Clau,Valor>:: getSize() const{
    return this->_size;
}

//Ens diu si l'arbre està buit o no
template<class Clau, class Valor>
bool ArbreBinari<Clau,Valor>:: isEmpty() const{
    return this->root==nullptr;
}

//Ens dona l'alçada de l'arbre
template<class Clau, class Valor>
int ArbreBinari<Clau,Valor>:: height() const{
    //Aixo s'ha de fer recursivament. Senzillament cridem la funció high del node Root
    if(root==nullptr){
        return 0;
    }
    
    return this->root->height();
}

/*
    MODIFICADORES: insert, insert auxiliar, eliminaminim
*/
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* ArbreBinari<Clau,Valor>:: insert(const Clau& clau, const Valor& value) {
    //Fem els casos de nullptr i root->getKey()==clau, i després fem el cas general
    if(root==nullptr){
        NodeBinari<Clau,Valor>* e= new NodeBinari<Clau,Valor>(clau);
        e->setValue(value);
        root=e;
        _size++;
        return root;
    }
    else if(root->getKey()==clau){
        return root;
    } else{
        return insertAuxiliar(root,clau,value);
    }
}

//Auxiliar dinserir
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* ArbreBinari<Clau,Valor>:: insertAuxiliar(NodeBinari<Clau,Valor>* node,const Clau& clau, const Valor& value){
    //Anem mirant la key si és més gran o més petita que el node en qüestió.
    //Anem travessant fins que arribem un punt on podem inserir el nou node

    //Debugging:
    //cout << "Clau: " << clau <<"Valor: " << value <<endl;
    //cout << "Clau del node: " << node->getKey() << "Valor del node:" << node->getValue() << endl;
    if(clau< node->getKey()){
        if (!node->hasLeft()){
            NodeBinari<Clau,Valor>* e= new NodeBinari<Clau,Valor>(clau);
            e->setValue(value);
            node->setfillE(e);
            //cout << "Estem posant un fill a l'esquerra" << endl;
            _size++;
            return node->getFillE();
        }else{
            //cout <<"Recursivitat esquerra" << endl;
            return insertAuxiliar(node->getFillE(),clau,value);
        }
    } else if(clau> node->getKey()){
       if (!node->hasRight()){
            NodeBinari<Clau,Valor>* e= new NodeBinari<Clau,Valor>(clau);
            e->setValue(value);
            node->setfillD(e);
            //cout << "Estem posant un fill a la dreta" << endl;
            _size++;
            return node->getFillD();
        }else{
            //cout <<"Recursivitat dreta" << endl;
            return insertAuxiliar(node->getFillD(),clau,value);
        } 
    } else{
        //cout << "Retornem perquè key==key.node";
        return node; //Això vol dir que key==node.key!
    }
}

//Busca el valor mínim (aquell que té la clau més petita) i després l'elimina, això és, aquell que està al màxim a l'esquerra possible!
template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>:: eliminaMinim() {
    NodeBinari<Clau,Valor>* n= root;
    if(isEmpty()){
        throw std::string("Esta buit");
    }

    while(n->hasLeft()){
        n=n->getFillE();
    }
    //Ara hem d'arreglar els parents i els fills dels nodes afectats
    if(n!=root){
        if(n->hasRight()){
            n->getPare()->setfillE(n->getFillD());
            n->setfillD(nullptr);
        }else{
            n->getPare()->setfillE(nullptr);
        }
    }else{ //Si és la root, aleshores capgirem i ja està
        root=n->getFillD();
        n->setfillD(nullptr);
    }
    _size--;
    delete n;
}

/*
    CONSULTORES: search, search auxiliar, valueOf, obtevalorsRang, obtevalorsRangAuxiliar
*/

//Retorna el valor donada una clau. Si no troba, throw excepció
template<class Clau, class Valor>
const Valor& ArbreBinari<Clau,Valor>::valueOf(const Clau& clau) const{
    NodeBinari<Clau,Valor>* n = search(clau);
    if (n==nullptr){
        throw std::string("No hi ha cap node amb clau donada");
    }else{
        return n->getValue();
    }
}
//Retorna el node donada una clau. Si no troba, retorna null.
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* ArbreBinari<Clau,Valor>::search(const Clau& k) const{
    if(root->getKey()==k){
        return root;
    } else{
        return searchAuxiliar(root,k);
    }
}

template<class Clau, class Valor>
NodeBinari<Clau,Valor>* ArbreBinari<Clau,Valor>::searchAuxiliar(NodeBinari<Clau,Valor>* node,const Clau& k) const{

    //Mentre l'arbre tingui fill esquerra o dret,
        //Si el node té una clau més gran, i claus no iguals, aleshores agafem l'esquerra. 
        //Mateix raonament amb el dret
        //Si la clau és igual, aleshores parem
        
    while(node!=nullptr){
        if(k< node->getKey()){
            node=node->getFillE();
        } else if(k> node->getKey()){
            node=node->getFillD();
        } else{
            return node; //Això vol dir que key==node.key!
        }
    }
    
    return nullptr;

}


//Podem fer una funcio auxiliar que passa el vector com a paràmetre i afegeix tots els nodes candidats
template<class Clau, class Valor>
vector<NodeBinari<Clau,Valor>*> ArbreBinari<Clau,Valor>::obteValorsRang(int k1, int k2) const{
    
    if(isEmpty()){
        throw std::string("Arbre buit");
    }

    vector<NodeBinari<Clau,Valor>*> resultat;
    this->obteValorsRangAuxiliar(root,k1,k2,resultat);
    return resultat;
}

//Aquesta funció es va cridant recursivament per anar trobant tots els nodes que estiguin entre k1 i k2
//En el cas que un node estigui entre k1 i k2, s'afegeix el node
template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::obteValorsRangAuxiliar(NodeBinari<Clau,Valor>* node,int& k1, int& k2, vector<NodeBinari<Clau,Valor>*>& v) const{

    //Si el node està entre k1 i k2, s'afegeix i es continua la cerca (DES DE LES DUES BANDES)
    //Si el node és més gran que k1 i té esquerra, es busca el esquerra
    //Si el node és més petit que k1 i té dret, es busca el dret

    
    if(node->getKey() > k1 && node->hasLeft()) {
        obteValorsRangAuxiliar(node->getFillE(), k1, k2, v);
    }
    
    if(node->getKey() >= k1 && node->getKey() <= k2) {
        v.push_back(node);
    }

    if(node->getKey() < k2 && node->hasRight()) {
        obteValorsRangAuxiliar(node->getFillD(), k1, k2, v);
    }
}

/*
    CONSULTORES (IMPRIMEIXEN): imprimirPreordre,imprimirInordre,imprimirPostOrdre,imprimirCami
*/

//Fer com un search() però bàsicament anar imprimint el valor. Fer imprimirCamiAuxiliar
template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirCami(Clau key) const{
    cout << endl;
    if(root->getKey()==key){
        cout << root->getKey();
    } else{
        imprimirCamiAuxiliar(root,key);
    }
    cout << endl;
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirCamiAuxiliar(NodeBinari<Clau,Valor>* node,Clau key) const{
    
    if(key< node->getKey()){
            if (!node->hasLeft()){
                //NO FA RES!!! (ho deixem per claredat)
            }else{
                cout << node->getKey() << ", ";
                imprimirCamiAuxiliar(node->getFillE(),key);
            }
    } else if(key> node->getKey()){
            if (!node->hasRight()){
                //NO FA RES!! (ho deixem per claredat)
            }else{
                cout << node->getKey() << ", ";
                imprimirCamiAuxiliar(node->getFillD(),key);
            } 
    } else{
            cout << node->getKey() << ", "; //Hem arribat al final
    }
}

//Les següents implementacions són implementacions estàndards (estàn en pseucododi als apunts de teoria)

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirPreordre(const NodeBinari<Clau,Valor>* n) const{
    cout << endl;
    if(!this->isEmpty()){
        imprimirPreordreAuxiliar(root);
    }
    cout << endl;
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirInordre(const NodeBinari<Clau,Valor>* n) const{
    cout << endl;
    if(!this->isEmpty()){
        imprimirInordreAuxiliar(root);
    }
    cout << endl;
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirPostordre(const NodeBinari<Clau,Valor>* n) const{
    cout << endl;
    if(!this->isEmpty()){
        imprimirPostordreAuxiliar(root);
    }
    cout << endl;
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirPreordreAuxiliar(const NodeBinari<Clau,Valor>* n) const{
    //cout << n->getValue() << ", ";
    cout << n->getKey() << ", ";
    if (n->hasLeft()){
        imprimirPreordreAuxiliar(n->getFillE());
    }
    if (n->hasRight()){
        imprimirPreordreAuxiliar(n->getFillD());
    }
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirInordreAuxiliar(const NodeBinari<Clau,Valor>* n) const{
    if (n->hasLeft()){
        imprimirInordreAuxiliar(n->getFillE());
    }
    cout << n->getKey() << ", ";
    if (n->hasRight()){
        imprimirInordreAuxiliar(n->getFillD());
    }
    //cout << n->getValue() << ", ";
}

template<class Clau, class Valor>
void ArbreBinari<Clau,Valor>::imprimirPostordreAuxiliar(const NodeBinari<Clau,Valor>* n) const{
    if (n->hasLeft()){
        imprimirPostordreAuxiliar(n->getFillE());
    }
    if (n->hasRight()){
        imprimirPostordreAuxiliar(n->getFillD());
    }
    //cout << n->getValue() << ", ";
    cout << n->getKey() << ", ";
}

//template class ArbreBinari<int,int>;
//template class ArbreBinari<int,Movie>;

#endif