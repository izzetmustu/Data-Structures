//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Mustafa Izzet Mustu
//---Student Number: 504211564
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS

    // I the string is not empty
    if(!(this->sortedKey.empty()))
    {
        // Hold the current char and count it while iterating throug the string
        int counter = 0;
        char curr = this->sortedKey[0];
        for(int i = 0; i < int(sortedKey.size()); i++)
        {
            // If current char is the same then increment counter
            if(curr == this->sortedKey[i])
            {
                counter += 1;
            }
            else
            {
                // Create new node and add it to queue
                Node* tmp = new Node;
                tmp->next = NULL;
                tmp->left = NULL;
                tmp->right = NULL;
                tmp->token.symbol = string(1, curr);
                tmp->token.val = counter;
                this->queue.enque(tmp);
                // Change symbol and reset counter
                curr = this->sortedKey[i];
                counter = 1;
            }
        }
        // Add the last value
        // Create new node and add it to queue
        Node* tmp = new Node;
        tmp->next = NULL;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->token.symbol = string(1, curr);
        tmp->token.val = counter;
        this->queue.enque(tmp);
    }
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    // Create priority queue
    this->findFrequency();
    // Create parent from the first 2 node in the priority queue
    while(this->queue.head->next != NULL)
    {
        // Left child
        Node* left = queue.dequeue();
        // Right child
        Node* right = queue.dequeue();
        // Merge and enqueue the merged node
        this->queue.enque(this->huffmanTree.mergeNodes(left, right));
    }
    // Dequeue the root (last remaining in the queue)
    this->huffmanTree.root = this->queue.dequeue(); 
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    // Traverse the tree iteratively
    // If current node is empty return empty string
    if(traverse == NULL)
    {
        return "";
    }
    // If we are on a leaf node, check if we find the token
    if(!traverse->left && !traverse->right)
    {   
        // If we found, return the binary
        if(string(1, tokenChar) == traverse->token.symbol)
        {
            return tokenBinary;
        }
        // Else return empty string
        else
        {
            return "";
        }
    }
    // If we are not on a leaf node, iterate
    else
    {
        // Iterate left subtree first while adding a "0" to token
        string left = this->getTokenBinary(tokenChar, traverse->left, tokenBinary+string("0"));
        // If we have not found the tokenchar yet, continue to iterate
        if(left == "")
        {
            // Iterate right subtree while adding a "1" to token
            string right = this->getTokenBinary(tokenChar, traverse->right, tokenBinary+string("1"));
            return right;
        }
        // If we have found the tokenchar just return the found tokenbinary
        else
        {
            return left;
        }
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    // Reset encoded strings
    this->encodedBinaryPassword = "";
    this->encodedValPassword = "";
    string tok;
    // Iterate through the password
    for(int i = 0; i<int(password.size()); i++)
    {
        // Find the binary token of the current char and add it to encodedbinary string, also add the length to encodedvalue
        tok = getTokenBinary(password[i], this->huffmanTree.root, "");
        this->encodedBinaryPassword += tok;
        this->encodedValPassword += to_string(tok.size());
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedValPassword, string encodedBinaryPassword){
    // Hold an index as starting index of a subarray
    int index = 0;
    // This is used to merge all the decoded string 
    string decoded = "";
    // Iterate encodedval
    for(int i = 0; i<int(encodedValPassword.size()); i++)
    {
        // The value itself is the depth
        int depth = stoi(string(1,encodedValPassword[i]));
        string encoded = "";
        // ıterate encodedbinary starting from index and upto index+depth
        for(int j = index; j<(index+depth); j++)
        {
            encoded += string(1,encodedBinaryPassword[j]);
        }
        // Decoded the encoded binary
        decodeToken(encoded);
        // Add the decoded binary to final result
        decoded += this->decodedPassword;
        // Increase the depth
        index += depth;
    }
    // Update the decoded password as merged decoded
    this->decodedPassword = decoded;
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    // Start iterating the tree from the root
    Node* tmp = this->huffmanTree.root;
    // Iterate the the encoded the binary
    for(int i = 0; i<int(encodedToken.size()); i++)
    {
        // If the binary is 0, go left child
        if(string(1,encodedToken[i]) == "0")
        {
            tmp = tmp->left;
        }
        // If the binary is 1, go right child
        else
        {
            tmp = tmp->right;
        }
    }
    // Update decoded password
    this->decodedPassword = tmp->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};