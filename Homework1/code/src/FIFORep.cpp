/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 22/10/2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->setHead(NULL);
    this->setTail(NULL);
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->setHead(head);
    this->setTail(head);
}

FIFORep::~FIFORep()
{
}

void FIFORep::setHead(ProcessRep* head)
{
    this->mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this->mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the queue.
    */

    // If there is a process
    if(p != NULL)
    {
        // If queue is empty, set head and tail
        if(this->mpHead == NULL)
        {
            this->setHead(p);
            this->setTail(p);
            this->getTail()->setNext(NULL);
        }
        // If queue is not empty, set tail
        else
        {
            this->getTail()->setNext(p);
            this->setTail(p);
            this->getTail()->setNext(NULL);
        }
    }
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function remove a process from the tail of the queue and returns it.
    */   

    // If head is not NULL
    if(this->getHead() != NULL)
    {
        // Transfer head to next one in the queue and delete the first one 
        ProcessRep* temp = this->getHead();
        this->setHead(this->getHead()->getNext());
        // If head is NULL which means head goes in front of the tail, set tail also NULL
        if(this->getHead() == NULL)
        {
            this->setTail(NULL);
        }
        temp->setNext(NULL);
        return temp;
    }
    return NULL;
}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 

    // If head is NULL return immidiately
    if(this->getHead() == NULL)
    {
        return NULL;
    }
    // Else search
    else
    {
        // Start from the head and iterate up to tail and if there is a match return it, otherwise return NULL
        ProcessRep* current = this->getHead();
        while(current != NULL)
        {
            if(current->getProcessID() == id)
            {
                return current;
            }
            current = current->getNext();
        }
        return NULL;
    }
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */

    // If head is NULL return immidiately
    if(this->getHead() == NULL)
    {
        return;
    }
    // Else print
    else
    {
        // Start from the head and iterate up to tail and print
        ProcessRep* current = this->getHead();
        while(current != NULL)
        {
            std::cout << current->getProcessType() << current->getProcessID() << " " << current->startTime << " " << current->endTime << " ";
            current = current->getNext();
        }
    }
}