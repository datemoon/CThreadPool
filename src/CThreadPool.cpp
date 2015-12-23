/*
 * =====================================================================================
 *
 *       Filename:  CThreadPool.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2015 09:38:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"CThreadPool.h"
CThreadPool::CThreadPool()
{
    int initSize = 10;
    m_InitNum   = initSize;
    m_AvaliNum  = initSize;
    m_totThreadNum = initSize;
    m_AvaliLow  = 3;
    m_AvaliHigh = initSize + 10;
    m_MaxNum    = initSize << 2;
    m_Threadno = 0;
    m_busyTheashold = 3;
    m_busyList.clear();
    m_idleList.clear();
    m_allTheads.clear();
    pthread_mutex_init(&m_busyListMutex,NULL);
    pthread_mutex_init(&m_idleListMutex,NULL);
    sem_init(&m_avaliWork,0,0);
    sem_init(&m_avaliThreads,0,m_InitNum);
    for(int i = 0; i < m_InitNum; ++i)
    {
        CWorkerThread *thr = new CWorkerThread(m_Threadno++);
        thr->setCThreadPool(this);
        m_idleList.push_back(thr);
        m_allTheads.push_back(thr);
        thr->start();
    }
    printState();
}

void CThreadPool::printState()
{
    printf("avalid threads:%d \t busy threads:%d\n",getidleNum(),getBusyNum());
}

CThreadPool::CThreadPool(int initSize)
{
    assert(initSize > 0 && initSize < 30);
    m_InitNum   = initSize;
    m_AvaliNum  = initSize;
    m_totThreadNum = initSize;
    m_AvaliLow  = 3;
    m_AvaliHigh = initSize + 10;
    m_MaxNum    = initSize << 2;
    m_Threadno = 0;
    m_busyTheashold = 3;
    m_busyList.clear();
    m_idleList.clear();
    m_allTheads.clear();
    pthread_mutex_init(&m_busyListMutex,NULL);
    pthread_mutex_init(&m_idleListMutex,NULL);
    sem_init(&m_avaliWork,0,0);
    sem_init(&m_avaliThreads,0,m_InitNum);
    printf("Creating %d idle threads\n",m_InitNum);

    for(int i = 0; i < m_InitNum; ++i)
    {
        CWorkerThread *thr = new CWorkerThread(m_Threadno++);
        thr->setCThreadPool(this);
        m_idleList.push_back(thr);
        m_allTheads.push_back(thr);
        thr->start();
    }
    printState();
}

CThreadPool::~CThreadPool()
{
    if(!m_allTheads.empty())
        terminateAll();
}

unsigned int CThreadPool::getMaxNum()const
{
    return m_MaxNum;
}
void CThreadPool::setMaxnum(unsigned int maxnum)
{
    m_MaxNum = maxnum;
}
unsigned int CThreadPool::getAvaliLow()const
{
    return m_AvaliLow;
}
void CThreadPool::setAvaliLow(unsigned int avalilow)
{
    m_AvaliLow =  avalilow; 
}
unsigned int CThreadPool::getAvaliHigh()const
{
    return m_AvaliHigh;
}
void CThreadPool::setAvaliHigh(unsigned int avalihigh)
{
    m_AvaliHigh = avalihigh;
}
unsigned int CThreadPool::getAvaliNum()const
{
    return m_AvaliNum;
}
unsigned int CThreadPool::getInitNum()const
{
    return m_InitNum;
}
unsigned int CThreadPool::getBusyNum()
{
    return m_busyList.size();
}
unsigned int CThreadPool::getidleNum()
{
    return m_idleList.size();
}
void CThreadPool::setbusyThreashold(int threashold)
{
    m_busyTheashold = threashold;
}
void CThreadPool::createIdleThread(int num)
{
    printf("Create idle thread...\n");
//    pthread_mutex_lock(&m_idleListMutex);
    for(int i=0;i<num;++i)
    {
        printf("Creating Worker %d...\n",m_Threadno);
        CWorkerThread *thr = new CWorkerThread(m_Threadno++);
        m_idleList.push_back(thr);
        m_allTheads.push_back(thr);
        thr->setCThreadPool(this);
        thr->start();
        m_AvaliNum++;
        m_totThreadNum++;
        sem_post(&m_avaliThreads);
    }
  //  pthread_mutex_unlock(&m_idleListMutex);
}

void CThreadPool::deleteIdleThread(int num)
{
 //   pthread_mutex_lock(&m_idleListMutex);
    printf("Delete idle thread...\n");
    sem_wait(&m_avaliThreads);
    CWorkerThread *thr;
    vector<CWorkerThread*>::iterator pos;
    for(int i=0;i<num && i<m_idleList.size();i++)
    {
        thr = m_idleList[i];

        pos = find(m_idleList.begin(),m_idleList.end(),thr);
        if(pos != m_idleList.end())
        {
            m_idleList.erase(pos);
        }

        pos = find(m_allTheads.begin(),m_allTheads.end(),thr);
        if(pos != m_allTheads.end())
        {
            m_allTheads.erase(pos);
        }
        printf("Deleting Worker %d...\n",thr->getWorkerID());
        thr->terminate();
        delete thr;
        m_AvaliNum--;
        m_totThreadNum--;
    }
 //   pthread_mutex_unlock(&m_idleListMutex);
}
void CThreadPool::terminateAll()
{
//    pthread_mutex_lock(&m_busyListMutex);
//    pthread_mutex_lock(&m_idleListMutex);
    CWorkerThread *thr;
    printState(); 
    printf("ThreadPool terminate all %d threads~~\n",m_allTheads.size());
    for(int i=0;i<m_allTheads.size();++i)
    {
       thr = m_allTheads[i];
       thr->terminate();
       delete thr;
    }

//    pthread_mutex_unlock(&m_idleListMutex);
//    pthread_mutex_unlock(&m_busyListMutex);

//    pthread_mutex_destroy(&m_val_mutex);
//    pthread_mutex_destroy(&m_JobListMutex);
    pthread_mutex_destroy(&m_busyListMutex);
    pthread_mutex_destroy(&m_idleListMutex);
    sem_destroy(&m_avaliThreads);
    sem_destroy(&m_avaliWork);
 //   sem_destroy(&m_jobSem);
}

void CThreadPool::moveToBusyList(CWorkerThread*thr)
{
    printf("move to busy list...\n");
    pthread_mutex_lock(&m_busyListMutex);
   
    m_busyList.push_back(thr);
    sem_post(&m_avaliWork);

    pthread_mutex_unlock(&m_busyListMutex);

    sem_wait(&m_avaliThreads);
 //   pthread_mutex_lock(&m_val_mutex);
    pthread_mutex_lock(&m_idleListMutex);

    m_AvaliNum--;
    vector<CWorkerThread*>::iterator pos;
    pos = find(m_idleList.begin(),m_idleList.end(),thr);
    if(pos != m_idleList.end())
        m_idleList.erase(pos);

    pthread_mutex_unlock(&m_idleListMutex);
  //  pthread_mutex_unlock(&m_val_mutex);
}
void CThreadPool::moveToIdleList(CWorkerThread*thr)
{
//    pthread_mutex_lock(&m_val_mutex);
    printf("move to dile list..\n");
    pthread_mutex_lock(&m_idleListMutex);
    printf("move thread %d to idle list\n",thr->getWorkerID());
    m_idleList.push_back(thr);
    m_AvaliNum++;
    sem_post(&m_avaliThreads);

    pthread_mutex_unlock(&m_idleListMutex);
 //   pthread_mutex_unlock(&m_val_mutex);

    sem_wait(&m_avaliWork);
    pthread_mutex_lock(&m_busyListMutex);

    vector<CWorkerThread*>::iterator pos;
    pos = find(m_busyList.begin(),m_busyList.end(),thr);
    if(pos != m_busyList.end())
        m_busyList.erase(pos);
    printf("move thread %d out of busy thread\n",thr->getWorkerID());
    pthread_mutex_unlock(&m_busyListMutex);
}
CWorkerThread*CThreadPool::getIdleThread(void)
{
    printf("get idle thread...\n");
    sem_wait(&m_avaliThreads);
    printf(".......................\n");
    pthread_mutex_lock(&m_idleListMutex);

    CWorkerThread *thr = m_idleList.front();   
//    m_idleList.erase(m_idleList.begin()); 
//    m_AvaliNum--;
    printf("Get an idle thread %d\n",thr->getWorkerID());
    sem_post(&m_avaliThreads);
    pthread_mutex_unlock(&m_idleListMutex);
    return thr;
}
void CThreadPool::Run(CJob *job,void* jobdata)
{
 //  pthread_mutex_lock(&m_val_mutex);
   int gap;
   CWorkerThread *thr;
   printf("tring to assign job...\n");
   pthread_mutex_lock(&m_idleListMutex);
   printf("TotThread %d \t maxThread %d...\n",m_totThreadNum,m_MaxNum);
   if(m_AvaliNum > 0)
   {
       printf("There are idle threads...\n");
        if(m_AvaliNum > m_AvaliHigh)
        {//too many idle threads
            printf("Too many idle thread delete some...\n");
            if(m_AvaliNum - m_InitNum > m_AvaliHigh)
             {
                gap = m_AvaliNum - m_InitNum;
            }
             else
            {
                gap = m_InitNum;
            }
           deleteIdleThread(gap);
        }
        else if(m_AvaliNum < m_AvaliLow)
        {//too busy
            printf("Too many busy threads create some...\n");
            gap =0;
            if(m_totThreadNum+ m_InitNum > m_MaxNum)
            {
                gap = m_MaxNum - m_totThreadNum;
            }
            else
            {
                gap = m_InitNum;
            }
            if(gap !=0 )
             createIdleThread(gap);
        }
        pthread_mutex_unlock(&m_idleListMutex);
        thr = getIdleThread();
        printf("assign job to an idle thread %d...\n",thr->getWorkerID());
    //    pthread_mutex_unlock(&m_idleListMutex);
        moveToBusyList(thr);
        thr->setCThreadPool(this);
        thr->loadCJob(job,jobdata);
    }
   else
    {
        pthread_mutex_unlock(&m_idleListMutex);
        printf("Opps no idle threads...\n");
        pthread_mutex_lock(&m_busyListMutex);
        //assign to the thread without heavy jobs
        gap = m_busyList[0]->m_JobList.size();
        thr = m_busyList[0];
        for(int i=1;i<m_busyList.size() && gap > m_busyTheashold;++i)
        {   
//           printf("busy thread %d with job %d\n",i,m_busyList[i]->m_JobList.size());
            // thr = m_busyList[i];
           if( gap > m_busyList[i]->m_JobList.size())
           {
                gap =  m_busyList[i]->m_JobList.size();
                thr = m_busyList[i];
           }
            
        }
        printf("assign job to thread %d with jobqueue %d...\n",thr->getWorkerID(),thr->m_JobList.size());
        thr->loadCJob(job,jobdata);

        pthread_mutex_unlock(&m_busyListMutex);
    }
   printf("job assign successful...\n");
    printState();

}
