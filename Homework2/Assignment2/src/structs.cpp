//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Izzet Mustu
//---Student Number: 504211564
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    this->head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    // If queue empty, add new node
    if(this->head == NULL)
    {
        this->head = newnode;
    }
    else
    {
        Node* curr = this->head;
        int key = newnode->token.val;
        // If the key to be added is smaller than the value of the head, add it becomes head
        if(curr->token.val > key)
        {
            newnode->next = this->head;
            this->head = newnode;
        }
        // Iterate through queue to find the place where node should be added
        else
        {
            while(curr->next != NULL && key >= curr->next->token.val)
            {
                curr = curr->next;
            }
            newnode->next = curr->next;
            curr->next = newnode;
        }
    }
};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    // Remove the head if there is head, and assign next of the head as head
    if(this->head != NULL)
    {
        Node* tmp = this->head;
        this->head = this->head->next;
        tmp->next = NULL;
        return tmp;
    }    
    return NULL;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    this->root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    deleteTree(this->root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    // If null, return
    if(node == NULL)
    {
        return;
    }
    // Delete left subtree
    deleteTree(node->left);
    // Delete right subtree
    deleteTree(node->right);

    // Delete node
    delete node;

    return;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    // Create new node, merge 2 and return the parent
    Node* newnode = new Node;
    newnode->left = temp1;
    newnode->right = temp2;
    newnode->token.symbol = temp1->token.symbol + temp2->token.symbol;
    newnode->token.val = temp1->token.val + temp2->token.val;
    return newnode;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};