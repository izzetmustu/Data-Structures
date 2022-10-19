/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 23/10/2022
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
    this->mFinishedProcess = NULL;
}

CPURep::~CPURep()
{
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    /*
        YOUR CODE HEAR
    */
}

FIFORep* CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this->mFinishedProcess = finishedProcess;
}