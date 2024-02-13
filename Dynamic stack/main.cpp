using namespace std;
#include "LinkedStack.h"


bool checkPalindrome(LinkedStack<class Element> p){
    /*
        Podem implementar-ho de diferents maneres.
        (1)
        La manera més fàcil seria implementar una funció a linked stack que travessi amb ->Next() 
            la pila i crear una nova pila idèndica però al revés
        Després comparar element a element (el cost seria 2n, ja que l'hauriem de atravessar dues vegades).

        (2)
    */
    return true;
}

main(){
    LinkedStack<int> p;

    //Elements bàsics:
    p.push(3);
    p.push(4);
    p.pop();
    p.push(5);
    p.print();
    cout << "size:" << p.size() << endl;
    cout << "Pila:" << endl;
    p.print(); 
    cout << "empty:" << p.empty() << " top:" <<p.top()<< endl;
    p.pop();p.pop();
    cout << "empty:" << p.empty() << " size:" << p.size() << endl;

    //Excepcio del top(la llista està buida!); print() quan buit;
    try{
        p.top();
    }catch(string e){
        cout << e << endl;
    }
    p.print();

    //Pel destructor (comprovar que funciona):
    p.push(3);
    p.push(4);
    if(checkPalindrome){
        cout << "L'és" << endl;
    }else{
        cout << "No l'és" << endl;
    }


}