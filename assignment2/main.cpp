#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

//define a struct type to represent node of the AVL tree
typedef struct nodeStruct {
    int data;
    int diff;
    //each node has two child, can be null
    struct nodeStruct *child[2];
} nodeObj;//nodeObj is the name of the data type now


void rotate(nodeObj **node, int rightOrLeft) {
    int l = rightOrLeft ? 0 : 1;
    int r = rightOrLeft ? 1 : 0;
    int sign = rightOrLeft ? 1 : -1;
    if((*node)->child[l] == NULL){  //terminate program if there is no required child
      exit(1);
    }
    if((*node)->child[l] != NULL) {
        nodeObj* left = (*node)->child[l];
        int a = (*node)->diff * sign, b = left->diff * sign, na, nb;
        //update depth
        if(b >= 0) {
            if (a - 1 - b >= 0) {
                nb = b - 1;
            }
            else {
                nb = a - 2;
            }
            na = a - 1 - b;
        }
        else {
            if (a - 1 >= 0) {
                nb = b - 1;
            }
            else {
                nb = a + b - 2;
            }
            na = a - 1;
        }
        (*node)->diff = na * sign;
        left->diff = nb * sign;
        //do the rotation
        (*node)->child[l] = (*node)->child[l]->child[r];
        left->child[r] = *node;
        *node = left;
    }
}

//this function returns the change of depth after adding or deleting a node
//addOrDelete = 1:0 (add:delete)
int modifyTree(nodeObj **node, int data, int addOrDelete) {
    if(*node == NULL) {
        if(addOrDelete) {
            //adding a new node
            *node = new nodeObj();
            if(*node == NULL){
              exit(1);
            }
            if(*node != NULL) {
                //initialize the node
                (*node)->data = data;
                (*node)->diff = 0; //since this is the first, there are no child, so no difference
                (*node)->child[0] = NULL;
                (*node)->child[1] = NULL;
            }
            return *node != NULL;
        }
        else {
            //there are nothing to be deleted
            return 0;
        }
    }
    else {
        int l, delta, deltaSign;
        nodeObj *nextNode;
        if(data == (*node)->data) {
            //if the value == current node data
            if(addOrDelete) {
                //do not add to the tree, ignor it
                return 0;
            }
            else {
                //delete this node
                if((*node)->child[1] == NULL) {
                    //if not having right child, then bring left child to this position
                    nextNode = (*node)->child[0];
                    delete(*node);
                    *node = nextNode;
                    //depth - 1
                    return -1;
                }
                else if((*node)->child[0] == NULL) {
                    //if not having left child, then bring right child to this position
                    nextNode = (*node)->child[1];
                    delete(*node);
                    *node = nextNode;
                    //depth - 1
                    return -1;
                }
                else{
                    //having child on both side
                    //find the rightmost node on the left child as told in lecture
                    for (nextNode = (*node)->child[0]; nextNode->child[1] != NULL; nextNode = nextNode->child[1]);
                    //bring the data of the rightmost node to the current node
                    (*node)->data = nextNode->data;
                    //delete the rightmost node
                    l = 0;
                    deltaSign = 1;
                    delta = modifyTree(&(*node)->child[l], nextNode->data, addOrDelete);
                }
            }
        }
        else {
            //the current node is not the node we want
            //check the value with the current data and decide which way to go
            if (data < (*node)->data) {
                //if smaller than current then go left
                l = 0;
                deltaSign = 1; //will change diff later
            }
            else {
                //if bigger than current then go right
                l = 1;
                deltaSign = -1;
            }
            delta = modifyTree(&(*node)->child[l], data, addOrDelete);
        }
        if (delta != 0) {
            //if changes happened to the child
            int tempDiff = (*node)->diff; //the original depth
            //make some variables to store the rotation info
            int doRotate = 0, rotate_l, diffSign, isRightRotation;
            (*node)->diff += delta * deltaSign; //update the diff
            if ((*node)->diff > 1) {
                //left is too high, do a right rotation
                doRotate = 1;
                rotate_l = 0;
                diffSign = 1;
                isRightRotation = 1;
            }
            else if((*node)->diff < -1) {
                //right is too high, do a left rotation
                doRotate = 1;
                rotate_l = 1;
                diffSign = -1;
                isRightRotation = 0;
            }
            if (doRotate) {
                int childDiff = (*node)->child[rotate_l]->diff;
                //do the rotation
                if((*node)->child[rotate_l]->diff * diffSign < 0) {
                    //rotate the child first, direction is opposite to the main rotation
                    rotate(&(*node)->child[rotate_l], !isRightRotation);
                }
                //rotate the current node
                rotate(node, isRightRotation);
                if(delta < 0 && childDiff != 0){
                  return -1;
                }
                else{
                  return 0;
                }
            }
            //return the changes to the depth
            if (delta > 0 && tempDiff == 0) {
                return 1;
            }
            else if (delta < 0 && tempDiff != 0) {
                return -1;
            }
            else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

void printPost(const nodeObj *node)
{
    if (node == NULL){
       return;
    }
    printPost(node->child[0]);

    printPost(node->child[1]);

    printf("%d ", node->data);
}

void printIn(const nodeObj *node)
{
    if (node == NULL){
       return;
    }
    printIn(node->child[0]);

    printf("%d ", node->data);

    printIn(node->child[1]);
}

void printPre(const nodeObj *node)
{
    if (node == NULL){
      return;
    }
    printf("%d ", node->data);

    printPre(node->child[0]);

    printPre(node->child[1]);
}

//delete tree recursively
void deleteTree(nodeObj *node) {
    if (node != NULL) {
        deleteTree(node->child[0]);
        deleteTree(node->child[1]);
        delete(node);
    }
}

int main(void) {
    //collect input in one line and put in vectors
    string input;
    getline( std::cin, input );
    istringstream is( input );
    vector<string> L( ( istream_iterator<string>( is ) ), istream_iterator<string>() );

    //make a node start with null as the root
    nodeObj *root = NULL;

    for(int i = 0; i < L.size(); i++){
        //cout << L[i] << " ";
        string temp = L[i];
        if(temp == "IN"){
            if(root == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printIn(root);
            cout << endl;
        }
        else if (temp == "POST"){
            if(root == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printPost(root);
            cout << endl;
        }
        else if(temp == "PRE"){
            if(root == NULL){
                cout << "EMPTY" << endl;
                return 0;
            }
            printPre(root);
            cout << endl;
        }
        else{
            char first = temp[0];
            int isAdd;
            if(first == 'A'){
              isAdd = 1;
            }
            else{
              isAdd = 0;
            }

            int value = 0;
            temp.erase(0,1);
            stringstream geek(temp);
            geek >> value;
            modifyTree(&root, value, isAdd);
            }
        }
    deleteTree(root);
    return 0;
}
