#include <iostream>

using namespace std;

struct node{
    int info;
    node *left;
    node *right;
};

class tlista{
    int maxSize;
    int listSize;
    int curr;
    node *ListArray;

    public:
        tlista(int max){
            maxSize = max;
            listSize = 0;
            curr = 0;
            ListArray = new node[maxSize];
        }

        void clear(){
            listSize = curr = 0;
        }

        void insert(node value){
            cout<<maxSize;
            if(listSize >= maxSize){
                return;
            }
            for(int i = listSize; i > curr; i--){
                ListArray[i] = ListArray[i-1];
            }

            ListArray[curr + 1] = value;
            
            listSize++;
        }

        int length(){
            return listSize;
        }

        node getValue(){
            return ListArray[curr];
        }

        node erase(){
            node item = getValue();

            for(int i = curr; i < listSize-1; i++){
                ListArray[i] = ListArray[i+1];
            }
            listSize--;
            return item;
        }

        int getCurr(){
            return curr;
        }

        void moveToPos(int pos){
            if(pos > listSize-1 || pos < 0){
                return;
            }
            curr = pos;
        }

        void MoveToStart(){
            curr = 0;
        }

        void MoveToEnd(){
            curr = (listSize > 0) ? listSize - 1 : 0;
        }
};

class tcola{
    tlista *lista;
    public:
        tcola(int MaxSize){
            lista = new tlista(MaxSize);
        }

        void clear(){
            lista->clear();
        }

        void enqueque(node value){
            lista->MoveToEnd();
            lista->insert(value);
        }

        node dequeque(){
            lista->MoveToStart();
            return lista->erase();
        }

        int length(){
            return lista->length();
        }

        node frontValue(){
            lista->MoveToStart();
            return lista->getValue();
        }
};