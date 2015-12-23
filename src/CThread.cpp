/*
 * =====================================================================================
 *
 *       Filename:  CThread.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 04:49:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"CThread.h"
CThread::CThread()
{
}
CThread::CThread(int no)
{
    m_threadNo = no;
}
CThread::~CThread()
{
    terminate();
}

void*CThread::Func(void*para)
{
    CThread *tp = (CThread*)para;
//    printf("Thread %d ready!\n",(unsigned long)(tp->m_thread));
    tp->run();
}

void CThread::terminate()
{
    join();
}
int CThread::join()
{
    void *tret;
    int err;
   // printf("Thread %d join!!\n",(unsigned long)m_thread);
    err =  pthread_join(m_thread,&tret);
  //  if(err !=0 )
  //  {
    //    printf("Can't join thread %d\n",(unsigned long)m_thread);
    //    return -1;
   // }
   // return 0;
   return err;
}
int CThread::start()
{
    int err;
    err = pthread_create(&m_thread,NULL,&CThread::Func,(void*)this);
    if(err != 0)
    {
        printf("Can't create thread!\n");
        return -1;
    }
    //m_threadNo = (unsigned long)m_thread;
    return 0;
}

unsigned long CThread::getThreadNo()const
{
    return m_threadNo;
}
