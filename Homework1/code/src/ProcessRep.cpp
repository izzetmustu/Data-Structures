/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 23/10/2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    // Private attributes
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->mpNext = NULL;

    // Public attributes
    this->remainingTime = processTime;
    this->startTime = -1;
    this->endTime = -1;
}

ProcessRep::~ProcessRep()
{
}

ProcessRep* ProcessRep::getNext()
{
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    this->mProcessTime = ProcessTime;
}