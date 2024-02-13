#ifndef NODELLISTA_H
#define NODELLISTA_H
using namespace std;

template <class Element>
class NodeLlista
{
    public:
        NodeLlista(Element element){
            this->_element=element;
            this->_anterior=nullptr;
            this->_seguent=nullptr;
        }

        const Element& accedirElement(){
            return _element;
        }
        NodeLlista<Element>* accedirSeguent(){
            return _seguent;
        }
        void fixarSeguent(NodeLlista<Element>* adresa){
            this->_seguent=adresa;
        }
        NodeLlista<Element>* accedirAnterior(){
            return _anterior;
        }
        void fixarAnterior(NodeLlista<Element>* adresa){
            this->_anterior=adresa;
        }

    private:
        Element _element;
        NodeLlista<Element>* _anterior;
        NodeLlista<Element>* _seguent;
};

#endif