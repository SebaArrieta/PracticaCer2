#include <iostream>

using namespace std;

struct tLetra{
    char info;
    tLetra *next;
};

class tLista{
    private:
        tLetra *tail;
        tLetra *head;
        tLetra *curr; //posicion actual
        int pos; //posicion
        int size; //tamaño de la lista
    public:
        tLista(){
            tail = head = curr = new tLetra;
            size = 0;
            pos = 0;
        }

        void Insert(){

        }

        void Delete(){

        }

        void MoveToStart(){

        }

        void MoveToEnd(){

        }

        void getLength(){

        }

        void MoveToPos(){

        }
};

int main(){
    int j;
    return 0;
}