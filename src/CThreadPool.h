/*
 * =====================================================================================
 *
 *       Filename:  CThreadPool.h
 *
 *    Description:  :`
 *
 *        Version:  1.0
 *        Created:  12/18/2015 09:35:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H
#include"CJob.h"
#include"CWorkerThread.h"
#include"Utility.h"
class CThreadPool
{
friend class CWorkerThread;
private:
    unsigned int m_MaxNum;
    unsigned int m_AvaliLow;
    unsigned int m_AvaliHigh;
    unsigned int m_AvaliNum;
    unsigned int m_InitNum;
    unsigned int m_Threadno;
    int m_busyTheashold;
protected:
    CWorkerThread *getIdleThread(void);
    void moveToBusyList(CWorkerThread*busywork);
    void moveToIdleList(CWorkerThread*idlework);
    void deleteIdleThread(int num);
    void createIdleThread(int num);
public:
    CThreadPool();
    CThreadPool(int initSize);
    virtual ~CThreadPool();
 //   pthread_mutex_t m_JobListMutex;
  //  pthread_mutex_t m_val_mutex;
    pthread_mutex_t m_busyListMutex;
    pthread_mutex_t m_idleListMutex;
    sem_t m_avaliThreads;
    sem_t m_avaliWork;
//    sem_t m_jobSem;
 //   vector<CJob*> m_JobQuere;
//    vector<void*> m_JobData;
    vector<CWorkerThread*> m_allTheads;
    vector<CWorkerThread*> m_busyList;
    vector<CWorkerThread*> m_idleList;
    int m_totThreadNum;
 //   void invoking(CJob *job,void*jobdata);
    unsigned int  getMaxNum()const;
    unsigned int  getAvaliLow()const;
    unsigned int  getAvaliHigh()const;
    unsigned int  getAvaliNum()const;
    unsigned int  getInitNum()const;
    void setMaxnum(unsigned int maxnum);
    void setAvaliLow(unsigned int avalilow);
    void setAvaliHigh(unsigned int avalihigh);
    void setbusyThreashold(int threashold);
    void printState();
    unsigned int getBusyNum();
    unsigned int getidleNum();
    unsigned int getAll();
    void terminateAll();
    void Run(CJob *job,void *jobdata);
//    void Adjust();
};
#endif
