using namespace std;
#include <iostream>

#ifndef NODEBINARI_H
#define NODEBINARI_H


template <class Clau, class Valor >
class NodeBinari {
    public:
        
        NodeBinari(const Clau& key); //Constructor base que entra amb una clau: O(1)

        NodeBinari(const NodeBinari<Clau,Valor>& orig); //Constructor còpia a partir d'un node: O(n), on n són els fills del node
        virtual ~NodeBinari(); //Destructor: O(n), on n són els fills del node

    /* Modificadors */
        void setClau(const Clau& key); //Setter clau: O(1)
        void setValue(const Valor& value); //setter valor: O(1)
        void setPare(NodeBinari<Clau,Valor>* pare); //setter pare: O(1)
        void setfillD(NodeBinari<Clau,Valor>* fillD); //setter fillD: O(1)
        void setfillE(NodeBinari<Clau,Valor>* fillE); //setter fillE: O(1)


    /* Consultors */
        const Clau& getKey() const; //Retorna la key del node: O(1)
        const Valor& getValue() const; //Retorna el valor del node: O(1)

        NodeBinari<Clau,Valor>* getPare(); //Retorna el pare: O(1)
        NodeBinari<Clau,Valor>* getFillE(); //Retorna fill esquerra: O(1)
        NodeBinari<Clau,Valor>* getFillD(); //Retorna fill dret: O(1)

        const NodeBinari<Clau,Valor>* getFillE() const; //Retorna fill esquerra: const (pel constructor copia): O(1)
        const NodeBinari<Clau,Valor>* getFillD() const; //Retorna fill dret: const (pel constructor copia): O(1)


    /* Operacions */
        bool isRoot() const; //Retorna boolean per saber si es root o no: O(1)
        bool hasLeft() const; //Retorna si té un fill esquerra: O(1)
        bool hasRight() const; //Retorna si té un fill dret: O(1)
        
        bool isExternal() const; //Retorna si és una fulla: O(1)
        void insertValue(const Valor & v); //Afegeix un valor a la llista de valors: O(1)
        int height() const; //Alçada del node: O(n), on n són els fills del node

        bool operator==(const NodeBinari<Clau,Valor >& node) const; //Comprova si dos nods són iguals (sobrecàrrega de ==): O(1)

    private:
        Clau key; //Clau del node
        Valor value; //Llista de valors
        NodeBinari<Clau,Valor>* _pare; //Pare del node
        NodeBinari<Clau,Valor>* _fill_Esquerra; //Fill esquerra del node
        NodeBinari<Clau,Valor>* _fill_Dreta; //Fill dret del node

};


/*
    Constructors i destructos estàndards 
*/

//Constructor normal
template<class Clau, class Valor>
NodeBinari<Clau,Valor>:: NodeBinari(const Clau& key){
    //Inicialitza tot a 0, i amb la key donada.
    this->setClau(key);
    this->_pare=nullptr;
    this->_fill_Dreta=nullptr;
    this->_fill_Esquerra=nullptr;
}
//Constructor còpia
template<class Clau, class Valor>
NodeBinari<Clau,Valor>:: NodeBinari(const NodeBinari<Clau,Valor>& orig){
    //Recursivament ha de copiar els nodes fills!

    this->setClau(orig.getKey());
    this->setValue(orig.getValue());
    this->_pare=nullptr;
    this->_fill_Dreta=nullptr;
    this->_fill_Esquerra=nullptr;

    if(orig.hasLeft()){
        this->_fill_Esquerra= new NodeBinari<Clau,Valor>(*(orig.getFillE()));
        this->_fill_Esquerra->setPare(this);
    }
    if(orig.hasRight()){
        this->_fill_Dreta= new NodeBinari<Clau,Valor>(*(orig.getFillD()));
        this->_fill_Dreta->setPare(this);
    }
}

//Destructor
template<class Clau, class Valor>
NodeBinari<Clau,Valor>:: ~NodeBinari(){
    //Destrueix els nodes fills, si en té, recursivament

    cout << "Sesta destruint el node amb clau:" << this->getKey() << endl;
    if(this->hasLeft()){
        delete _fill_Esquerra;
    }
    if(this->hasRight()){
        delete _fill_Dreta;
    }
}

/*
    Getters
*/

//Retorna la key
template<class Clau, class Valor>
const Clau& NodeBinari<Clau,Valor>:: getKey() const{
    return this->key;
}

//Retorna el valor
template<class Clau, class Valor>
const Valor& NodeBinari<Clau,Valor>:: getValue() const{
    return this->value;
}

//Retorna el node pare
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* NodeBinari<Clau,Valor>:: getPare(){
    return this->_pare;
}

//Retorna el fill Dret
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* NodeBinari<Clau,Valor>:: getFillD(){
    return this->_fill_Dreta;
}

//Retorna el fill esquerre
template<class Clau, class Valor>
NodeBinari<Clau,Valor>* NodeBinari<Clau,Valor>:: getFillE(){
    return this->_fill_Esquerra;
}

//Retorna el fill Dret CONST
template<class Clau, class Valor>
const NodeBinari<Clau,Valor>* NodeBinari<Clau,Valor>:: getFillD() const{
    return this->_fill_Dreta;
}

//Retorna el fill esquerre CONST
template<class Clau, class Valor>
const NodeBinari<Clau,Valor>* NodeBinari<Clau,Valor>:: getFillE() const{
    return this->_fill_Esquerra;
}

/*
    Setters
*/
//Setter de la key
template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: setClau(const Clau& key){
    this->key=key;
}

template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: setValue(const Valor& value){
    this->value=value;
}

//Setter dels fills i els pares
template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: setPare(NodeBinari<Clau,Valor>* pare){
    this->_pare= pare;
}

template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: setfillD(NodeBinari<Clau,Valor>* fillD){
    this->_fill_Dreta= fillD;
    if(fillD!=nullptr){
        fillD->setPare(this); //Hem de posar el seu pare!
    }
}

template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: setfillE(NodeBinari<Clau,Valor>* fillE){
    this->_fill_Esquerra= fillE;
    if(fillE!=nullptr){
        fillE->setPare(this); //Hem de posar el seu pare!
    }
}

/*
    OPERACIONS
*/

//Comprova que el node no té pare. Si no en té, aleshores es el root.
template<class Clau, class Valor>
bool NodeBinari<Clau,Valor>:: isRoot() const{
    return this->_pare==nullptr;
}

//Comprova que no tingui fill esquerra
template<class Clau, class Valor>
bool NodeBinari<Clau,Valor>:: hasLeft() const{
    return this->_fill_Esquerra!=nullptr;
}

//Comprova que no tingui fill dret
template<class Clau, class Valor>
bool NodeBinari<Clau,Valor>:: hasRight() const{
    return this->_fill_Dreta!=nullptr;
}

//Comprova que sigui un extern: mirem si té un fill dret o esquerra
template<class Clau, class Valor>
bool NodeBinari<Clau,Valor>:: isExternal() const{
    return !(hasRight()) && !(hasLeft());
}

//Diu la alçada d'un node; acordem que alçada d'una fulla és 1
template<class Clau, class Valor>
int NodeBinari<Clau,Valor>:: height() const{
    //Hem d'anar fer recursivament. Hem d'agafar max(esquerra, dreta), i retornem.
    
    int h=0;
    if(hasLeft()){
        h=_fill_Esquerra->height();
    }
    if(hasRight()){
        h=max(h,_fill_Dreta->height()); //També: a=fillD->h(), i dsp: return max(a,h) +1
    }
    return h+1;
}

//Afegeir un valor al node; he posat setClau a dalt perquè em quedava més clar i coherent
template<class Clau, class Valor>
void NodeBinari<Clau,Valor>:: insertValue(const Valor & v){
    setClau(v);
}

//Sobrecàrrega de l'operador ==. Comprova que la key del node i el value del node passat per paràmetre sigui igual al nostre node
template<class Clau, class Valor>
bool NodeBinari<Clau,Valor>:: operator==(const NodeBinari<Clau,Valor >& node) const{
    return (this->key==node.getKey()) && (this->value==node.getValue());
}

//Deixo això aquí: això seria per si volem separar'ho en .h i .cpp
    //template class NodeBinari<int,int>;
    //template class NodeBinari<int,Movie>;

#endif