#include "Llista.h"
#include "Posicio.h"
#include <iostream>
using namespace std;

main(){

    std:: cout << "Introdueix quantes paraules vols inserir" << endl;
    int opcio; int posicio; string opcio2; string paraula;
    cin >> opcio;
    cout << endl;
    Llista<string> llista;

    for(int i=0; i<opcio;i++){
        cout << "Introdueix una paraula:" << endl;
        cin >> paraula;
        cout << "Vols inserir-la al principi? (s/n)" << endl;
        cin >> opcio2;
        if (opcio2.compare("s")==0){
            llista.inserirPrincipi(paraula);
        }else{
            cout << "Vols inserir-la al final? (s/n)" << endl;
            cin >> opcio2;

            if(opcio2.compare("s")==0){
                llista.inserirFinal(paraula);
            }else{
                cout << "A quina posició la vols inserir (numero)" << endl; //La linked list comença des de la posició 0
                cin >> posicio;
                cout << "Abans (A) o després (D)?" << endl;
                cin >> opcio2;
                //Creem l'iterador:
                Posicio<string> iterador=llista.principi();
                for(int i=0; i<posicio;i++){
                    iterador=++iterador;
                }
                if(opcio2.compare("A")==0){
                    llista.inserirAbans(iterador, paraula);
                }else{
                    llista.inserirDespres(iterador, paraula);
                }
            }
        }
    }
    llista.print();
};