#include "CuaEstatica.h"
#include <iostream>

int main (int argc,char **argv){
    CuaEstatica q;
    q.enqueue(20);
    q.enqueue(10);
    q.enqueue(30);
    q.print();

    q.dequeue();
    q.print();

    std::cout << q.getFront() << std::endl;

    q.dequeue();
    q.dequeue();

    try{
        q.dequeue();
    }catch(std::string e){
        std::cout << e << std::endl;
    }
    
    q.print();

}
