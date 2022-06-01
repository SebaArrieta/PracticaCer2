#include <iostream>

using namespace std;
typedef int tElem;

struct tNodo{
    tElem info;
    int contador = 0;
    int contadorMenor = 0;
    tNodo* izq;
    tNodo* der;
};

class RankedABB{
    public:
        RankedABB();
        ~RankedABB();
        void insert(tElem x);
        void insert(tElem x, tNodo *&nodo);
        tNodo *getRoot();
        bool find(tElem x,tNodo *&tNodo);
        bool find(tElem x);
        int rank(tElem x,tNodo *tNodo);
        int setContador(tNodo *nodo);
        void setContadorMenor(tNodo *nodo);
        tNodo* nuevoNodo(tElem x);
        void mostrar();
        void clear(tNodo *&nodo);
    private:
        tNodo *raiz; // se crea la raiz como un puntero a nodos
        int numEle;
};

RankedABB::RankedABB(){
    raiz = NULL;
    numEle = 0;
}

RankedABB::~RankedABB(){ //elimina mediante el clear y luego elimina la raiz
    clear(raiz);
    delete raiz;
}

void RankedABB::clear(tNodo *&nodo){ //va eliminando mediante busqueda in order
    if(nodo != NULL){
        clear(nodo->izq); 
        delete nodo->izq;
        clear(nodo->der);
        delete nodo->der;
    }
}

tNodo *RankedABB::getRoot(){
    return raiz;
}

tNodo* RankedABB::nuevoNodo(tElem x){
    tNodo* nodo = new tNodo;
    nodo->der = NULL;
    nodo->izq = NULL;
    nodo->info = x;
    numEle++;
    return nodo;
}

void RankedABB::insert(tElem x){
    insert(x,raiz);
}

void RankedABB::insert(tElem x, tNodo *&nodo){ //se crea una sobrecarga de la funcion, para que al acceder a este funcion desde el main no sea necesario dar un nodo
    if(nodo == NULL){
        nodo = nuevoNodo(x); //le asignamos este nuevo nodo para quitarle el valor de NULL
        numEle++;
    }
    else{
        if(nodo->info > x) insert(x,nodo->izq);
        else if(nodo->info < x) insert(x,nodo->der);
        else return;
    }
}

int RankedABB::setContador(tNodo *nodo){
    if(nodo == NULL){
        return -1;
    }

    int izq = setContador(nodo->izq);
    int der = setContador(nodo->der);

    /*if(izq > 0 && der != -1){
        nodo->der->contadorMenor += izq + 2;
    }*/
    
    if(izq != -1){
        nodo->contadorMenor += izq + 1;
    }
    
    nodo->contador += izq+der+2;

    return nodo->contador;
}

void RankedABB::setContadorMenor(tNodo *nodo){
    if(nodo == NULL){
        return;
    }
    if(nodo->der != NULL){
        nodo->der->contadorMenor += nodo->contadorMenor+1;

        if(nodo->der->izq != NULL){
            nodo->der->izq->contadorMenor += nodo->contadorMenor+1;
        }
    }
    
    setContadorMenor(nodo->izq);
    setContadorMenor(nodo->der);
}

void RankedABB::mostrar(){
    cout<<raiz->info;
    cout<<raiz->izq->info;
}

bool RankedABB::find(tElem x){ 
    return find(x,raiz);
}
bool RankedABB::find(tElem x,tNodo *&nodo){
    if(nodo != NULL){   
        if(nodo->info > x) return find(x, nodo->izq); 
        else if(nodo->info < x) return find(x, nodo->der); 
        else if(nodo->info == x) return true; 
    }
    return false;
}

int RankedABB::rank(tElem x,tNodo *nodo){ // in order
    if(nodo != NULL){   
        if(x > nodo->info){
            if(nodo->der != NULL){
                rank(x, nodo->der);
            }else{
                return nodo->contadorMenor + 1;
            }
        }else if(x < nodo->info){
            if(nodo->izq != NULL){
                rank(x, nodo->izq);
            }else{
                return nodo->contadorMenor + 1;
            }
        }else{
            return nodo->contadorMenor;
        }
    }
}


int main(){
    
    RankedABB a;

    /*a.insert(101);
    a.insert(567);
    a.insert(102);
    a.insert(1);
    a.insert(2);
    a.insert(6);
    a.insert(5);
    a.insert(13);
    a.insert(9);
    a.insert(8);
    a.insert(7);
    a.insert(5);*/

    a.insert(25);
    a.insert(50);
    a.insert(30);
    a.insert(28);
    a.insert(40);
    a.insert(70);
    a.insert(27);
    a.insert(45);
    a.insert(55);
    a.insert(75);
    //a.mostrar();

    a.setContador(a.getRoot());
    cout<<endl;
    a.setContadorMenor(a.getRoot());

    cout<< a.find(567)<<endl;
    cout<< a.rank(10, a.getRoot());

    return 0;
}