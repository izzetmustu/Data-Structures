/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 23/10/2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    this->mpHead = head;
    this->mpHead = head;
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
    if(p != NULL)
    {
        this->mpTail->setNext(p);
        this->mpTail = p;
    }
}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function remove a process from the tail of the queue and returns it.
    */   
    if(this->mpHead != NULL)
    {
        ProcessRep* temp = this->mpHead;
        this->mpHead = this->mpHead->getNext();
        return temp;
    }
    return NULL;
}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 
    if(this->mpHead == NULL)
    {
        return NULL;
    }
    else
    {
        ProcessRep* current = this->mpHead;
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
    if(this->mpHead == NULL)
    {
        return;
    }
    else
    {
        ProcessRep* current = this->mpHead;
        while(current != NULL)
        {
            std::cout << current->getProcessType() << current->getProcessID() << " " << current->startTime << " " << current->endTime;
            current = current->getNext();
        }
    }
}