/* @Author
Student Name: Mustafa Izzet Mustu
Student ID : 504211564
Date: 22/10/2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    // Create FIFOs
    this->setProcessFIFO(new FIFORep, 0);
    this->setProcessFIFO(new FIFORep, 1);
    this->setProcessFIFO(new FIFORep, 2);

    // Set running process NULL
    this->setRunningProcess(NULL);

    // Create CPU object
    this->pCpuObj = new CPURep;
    
    // Assign time variables
    this->timeSliceCount = 0;
    this->totalTime = 0;
}
SchedulerRep::~SchedulerRep()
{
    delete this->mpProcessFIFO[0];
    delete this->mpProcessFIFO[1];
    delete this->mpProcessFIFO[2];
    delete this->pCpuObj;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return this->mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this->mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    // If it is not NULL and has not started yet, assign start time and running process attribute
    if(p != NULL)
    {   
        if(p->startTime == -1)
        {
            p->startTime = this->totalTime;
        }
        this->mpRunningProcess = p;
    }
    else
    {
        this->mpRunningProcess = NULL;
    }
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    // Push the process the FIFO according to it's type
    std::string type = p->getProcessType();
    if(type == std::string("A"))
    {
        this->getProcessFIFO(0)->queue(p);
    }
    else if (type == std::string("B"))
    {
        this->getProcessFIFO(1)->queue(p);
    }
    else
    {
        this->getProcessFIFO(2)->queue(p);
    }
}

ProcessRep* SchedulerRep::popProcess()
{
    // If there is no running process, check FIFOs starting from the one that has highest priority
    if(this->getRunningProcess() == NULL)
    {
        for(int i = 0; i < 3; i++)
        {
            if(this->getProcessFIFO(i)->getHead() != NULL)
            {
                this->timeSliceCount = 0;
                return this->getProcessFIFO(i)->dequeue();
            }
        }
        // Queues are empty
        return NULL;
    }
    // If there is already a running process, find if it should continue
    else
    {
        // Learn level of current running process
        // Since the max index of the levels is 2, we can assign max as 3
        int level = 3;
        int runningLevel;
        std::string runningType = this->getRunningProcess()->getProcessType();
        if(runningType == std::string("A"))
        {
            runningLevel = 0;
        }
        else if(runningType == std::string("B"))
        {
            runningLevel = 1;
        }
        else
        {
            runningLevel = 2;
        }
        
        // Check the queues if there should be a change for running process
        for(int i = 0; i < 3; i++)
        {
            if(this->getProcessFIFO(i)->getHead() != NULL && i < level)
            {
                level = i;
            }
        }

        // If there is a higher level process in the queue, push the running and pop the higher one  
        if(level < runningLevel)
        {
            // Reset time slice count
            this->timeSliceCount = 0;
            this->pushProcess(this->getRunningProcess());
            return this->getProcessFIFO(level)->dequeue();
        }
        // If current process should continue
        else if(level > runningLevel)
        {
            // If it should continue, check time slice
            if(this->checkTimeSlice())
            {
                this->timeSliceCount = 0;
            }
            return this->getRunningProcess();
        }
        else
        {
            // If there is a process in the same level queue, check time slice
            // If running process has reached it's quantum, push it the queue and pop from the head of the queue
            if(this->checkTimeSlice())
            {
                this->pushProcess(this->getRunningProcess());
                this->timeSliceCount = 0;
                return this->getProcessFIFO(level)->dequeue();
            }
            // If quantum is not reached, continue to run
            else
            {

                return this->getRunningProcess();
            }
        }
    }
}

bool SchedulerRep::checkTimeSlice()
{   
    if(this->getRunningProcess() != NULL)
    {
        // Q = 2^L
        // Assign quantum according to the type and compare
        std::string type = this->getRunningProcess()->getProcessType();
        int quantum = 0;
        if(type == std::string("A"))
        {
            quantum = 2;
        }
        else if(type == std::string("B"))
        {
            quantum = 4;
        }
        else
        {
            quantum = 8;
        }
        return quantum == this->timeSliceCount;
    }
    else
    {
        return false;
    }
}

ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p)
{
    // If process is not NULL increase timeSliceCount
    if(p != NULL)
    {
        this->timeSliceCount++;
    }
    // Increase total time and send it to CPU for both cases
    p = this->pCpuObj->runCPU(p, totalTime);
    this->totalTime++;
    return p;
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */

    // Push the newcoming
    ProcessRep* newComing = new ProcessRep(type, id, arrivalTime, processTime);
    this->pushProcess(newComing);
    // Pop process
    ProcessRep* goingtoCPU = this->popProcess();
    // Set running process
    this->setRunningProcess(goingtoCPU);
    // Run CPU
    goingtoCPU = this->sendProcessToCPU(goingtoCPU);
    // If the process which is sent is finished, reassign running process 
    if(goingtoCPU == NULL)
    {
        // First set it NULL then pop again
        this->setRunningProcess(NULL);
        ProcessRep* goingtoCPU = this->popProcess();
        this->setRunningProcess(goingtoCPU);
    }
}

void SchedulerRep::schedule(ProcessRep* p)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */
    if(p != NULL)
    {
        // Push the newcoming
        ProcessRep* newComing = p;
        this->pushProcess(newComing);
        // Pop process
        ProcessRep* goingtoCPU = this->popProcess();
        // Set running process
        this->setRunningProcess(goingtoCPU);
        // Run CPU
        goingtoCPU = this->sendProcessToCPU(goingtoCPU);
        // If the process which is sent is finished, reassign running process 
        if(goingtoCPU == NULL)
        {
            // First set it NULL then pop again
            this->setRunningProcess(NULL);
            ProcessRep* goingtoCPU = this->popProcess();
            this->setRunningProcess(goingtoCPU);
            
        }
    }
    else
    {
        // Pop process
        ProcessRep* goingtoCPU = this->popProcess();
        // Set running process
        this->setRunningProcess(goingtoCPU);
        // Run CPU
        goingtoCPU = this->sendProcessToCPU(goingtoCPU);
        // If the process which is sent is finished, reassign running process 
        if(goingtoCPU == NULL)
        {
            // First set it NULL then pop again
            this->setRunningProcess(NULL);
            ProcessRep* goingtoCPU = this->popProcess();
            this->setRunningProcess(goingtoCPU);
        }
    }
}
