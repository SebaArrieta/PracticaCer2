# include <iostream>
# include <cstring>
#include "tail.h"

using namespace std;

class BinaryNode{
    public:
        node *Root;
        int nElem;

        BinaryNode(){
            Root = new node;
            nElem = 0;
        }

        void increment(){
            nElem++;
        }
};

node *createNode(int value, BinaryNode *Root){
    node *NewNode = new node;
    NewNode->info = value;
    NewNode->right = NULL;
    NewNode->left = NULL;
    Root->increment();
    return NewNode;
}

int maxDepth(node* node)
{
    if (node == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        cout<<rDepth<<endl;
        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

void wideSearch(node* Node, BinaryNode Root){
    cout<<Root.nElem;
    tcola Nodes(Root.nElem);

    Nodes.enqueque(*Root.Root);
    cout<<Nodes.length();
    while(Nodes.length() != 0){
        node visited = Nodes.dequeque();
        Nodes.enqueque(*visited.left);
        Nodes.enqueque(*visited.right);

        cout<<visited.info;
    }

}

int main(){

    BinaryNode Root;
    Root.Root->info = 4;
    Root.Root->left = createNode(4, &Root);
    Root.Root->right = createNode(5, &Root);
    Root.Root->right->right = createNode(8, &Root);

    wideSearch(Root.Root, Root);

    
    return 0;
}