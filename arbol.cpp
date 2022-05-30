#include <iostream>

using namespace std;
typedef int tElem;

struct tNodo{
    tElem info;
    int contadorMenor;
    int contador;
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
        int rank(tElem x);
        int rank(tElem x,tNodo *&tNodo, int contador);
        int setContadorMenor(tNodo *nodo);
        int setContador(tNodo *nodo);
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

    if(izq != -1){
        nodo->contadorMenor = izq+1;
        cout<<nodo->contadorMenor<<endl;
    }

    nodo->contador = izq + der + 2;
    return nodo->contador;
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

int RankedABB::rank(tElem x){
    return rank(x,raiz,0);
}

int RankedABB::rank(tElem x,tNodo *&nodo, int contador){ // in order
    if(nodo != NULL){
        contador = rank(x,nodo->izq,contador); 

        if(nodo->info < x) contador++; 
        else if(nodo->info == x) return ++contador; //es inecesario seguir 
        else  return contador; //se detiene la busqueda, ya que encontró todos los menores que x

        contador = rank(x,nodo->der,contador);
    }
    return contador;
}


int main(){
    
    RankedABB a;

    a.insert(101);
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
    a.insert(5);
    //a.mostrar();

    cout<<endl<<endl<<a.setContador(a.getRoot())<<endl;

    cout<< a.find(567)<<endl;
    cout<< a.rank(590);

    return 0;
}