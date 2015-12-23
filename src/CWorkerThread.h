/*
 * =====================================================================================
 *
 *       Filename:  CWorkerThread.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 10:27:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include"CThread.h"
#include"CJob.h"
//#include"CThreadPool.h"
#include"Utility.h"
class CThreadPool;
class CWorkerThread:public CThread
{
private:
    CThreadPool *m_ThreadPool;
    CJob *m_Job;
    void *m_JobData;
    bool m_Terminate;
    sem_t m_jobSem;
    int m_totJobs;
    unsigned long m_WorkerID;
public:
    pthread_mutex_t m_Job_mutex;
    pthread_cond_t  m_WakeUp;
    vector<CJob*> m_JobList;
    vector<void*> m_JobListData;
    CWorkerThread();
    CWorkerThread(unsigned long no);
    virtual ~CWorkerThread();
    void loadCJob(CJob *job,void* jobData);
    void run(void);
    void setCThreadPool(CThreadPool *threadpool);
    void lockJob();
    void unlockJob();
    void clearResources();
    unsigned long getWorkerID()const;
    void terminate();
};
#endif
