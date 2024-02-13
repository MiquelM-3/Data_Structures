using namespace std;

template <class Element>
class Node{
    private:
        Element element;
        Node<Element>* next;
    public:
        Node(Element e);

        const Element& getElement() const;
        Node<Element>* getNext() const;

        void setNext(Node<Element>* elem);
};

//Constructor
template <class Element>
Node<Element>::Node(Element e){
    element=e;
}

//Consultores
template <class Element>
const Element& Node<Element>::getElement() const{
    return element;
}

template <class Element>
Node<Element>* Node<Element>::getNext() const{
    return next;
}

//Modificador
template <class Element>
void Node<Element>::setNext(Node<Element>* elem){
    next=elem;
}

