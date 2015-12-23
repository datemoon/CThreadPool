/*
 * =====================================================================================
 *
 *       Filename:  CWorkerThread.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 10:27:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"CWorkerThread.h"
#include"CThreadPool.h"
CWorkerThread::CWorkerThread()
{
    m_ThreadPool = NULL;
    m_Job = NULL;
    m_JobData = NULL;
    m_Terminate = false;
    m_Job_mutex = PTHREAD_MUTEX_INITIALIZER;
    m_WakeUp = PTHREAD_COND_INITIALIZER;
    m_totJobs = 0;
    sem_init(&m_jobSem,0,0);
}
CWorkerThread::CWorkerThread(unsigned long no)
{
    m_ThreadPool = NULL;
    m_Job = NULL;
    m_JobData = NULL;
    m_Terminate = false;
    m_Job_mutex = PTHREAD_MUTEX_INITIALIZER;
    m_WakeUp = PTHREAD_COND_INITIALIZER;
    m_WorkerID = no;
    m_totJobs = 0;
    sem_init(&m_jobSem,0,0);
    printf("Woker %d created...\n",no);
}
CWorkerThread::~CWorkerThread()
{
   clearResources();
}
unsigned long CWorkerThread::getWorkerID()const
{
    return m_WorkerID;
}

void CWorkerThread::clearResources()
{
    pthread_mutex_destroy(&m_Job_mutex);
    pthread_cond_destroy(&m_WakeUp);
    sem_destroy(&m_jobSem);
}

void CWorkerThread::loadCJob(CJob *job, void *jobData)
{
    lockJob();
    printf("Worker %d loading job...\n",m_WorkerID);
    m_JobList.push_back(job);
    m_JobListData.push_back(jobData);
    sem_post(&m_jobSem);
//    pthread_cond_signal(&m_WakeUp);
    unlockJob();
}

void CWorkerThread::setCThreadPool(CThreadPool *threadpool)
{
    m_ThreadPool = threadpool;
}

void CWorkerThread::run(void)
{
    while(1)
    {
        printf("Woker %d waitting for job...\n",m_WorkerID);
        sem_wait(&m_jobSem);
        lockJob();
        if(!m_JobList.empty())
        {
            m_Job = m_JobList.front();
            m_JobData = m_JobListData.front();
            m_JobList.erase(m_JobList.begin());
            m_JobListData.erase(m_JobListData.begin());
            printf("Worker %d hutting job!!\n",m_WorkerID);
        }
        else if(m_Terminate)
        {
            printf("Worker %d terminate...\n",m_WorkerID);
            unlockJob();
            pthread_exit(0);
        }
        unlockJob(); 
        
        printf("Worker %d is running...\n",m_WorkerID);
        m_Job->run(m_JobData);
        printf("Worker %d finished job...\n",m_WorkerID);

        delete m_Job;
//        delete m_JobData;

        lockJob();
        if(m_JobList.empty())
            m_ThreadPool->moveToIdleList(this);
        unlockJob();
        m_Job = NULL;
    }
}
void CWorkerThread::terminate()
{
   // join();
    //lockJob();
    printf("Worker %d join...\n",m_WorkerID);
    m_Terminate = true;
    sem_post(&m_jobSem);
  //  unlockJob();
    int err =  join();
    if(err != 0)
    {
        printf("Can't join worker %d...\n",m_WorkerID);
    }
    else
    {
        printf("Worker %d join success...\n",m_WorkerID);
    }
}
void CWorkerThread::lockJob()
{
    pthread_mutex_lock(&m_Job_mutex);
}

void CWorkerThread::unlockJob()
{
    pthread_mutex_unlock(&m_Job_mutex);
}
