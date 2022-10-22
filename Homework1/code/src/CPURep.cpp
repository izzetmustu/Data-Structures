/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 22/10/2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    // Create ne FIFO
    this->setFinishedProcess(new FIFORep);
}

CPURep::~CPURep()
{
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    // If there is a process decrease it's remaining time
    if(p != NULL)
    {
        p->remainingTime = p->remainingTime - 1;
        // If remaining time of the process is 0, add it to finished queue and return NULL else return the coming process
        if(p->remainingTime == 0)
        {
            p->endTime = time+1;
            this->getFinishedProcess()->queue(p);
            return NULL;
        }
        return p;
    }
    return NULL;
}

FIFORep* CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}