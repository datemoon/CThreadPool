/*
 * =====================================================================================
 *
 *       Filename:  CJob.cpp
 *
 *    Description:  The implementation of CJob
 *
 *        Version:  1.0
 *        Created:  12/18/2015 09:11:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"CJob.h"
CJob::CJob(void):m_JobNo(0),m_JobName(NULL)//,m_WorkerThread(NULL)
{
}
CJob::~CJob()
{
    if(m_JobName != NULL)
    {
        free(m_JobName);
    }
}

void CJob::setJobNo(int no)
{
    m_JobNo = no;
}
int CJob::getJobNo()const
{
    return m_JobNo;
}

void CJob::setJobName(char *name)
{
    if(m_JobName != NULL)
    {
        free(m_JobName);
        m_JobName = NULL;
    }
    m_JobName = (char*)malloc(strlen(name)+1);
    strcpy(m_JobName,name);
}
char *CJob::getJobName()const
{
    return m_JobName;
}
//void CJob::setWorkerThread(CThread *workerThread)
//{
//    m_WorkerThread = workerThread;
//}
//CThread *CJob::getWorkerThread()const
//{
 //   return m_WorkerThread;
//}
