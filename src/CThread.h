/*
 * =====================================================================================
 *
 *       Filename:  CThread.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 04:48:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CTHREAD_H
#define CTHREAD_H
//#include"CThreadPool.h"
#include"Utility.h"
class CThread{
private:
    pthread_t m_thread;
    unsigned long  m_threadNo;
   // CThreadPool *m_ThreadPool;
public:
    CThread();
    CThread(int no);
    virtual ~CThread();
    static void*Func(void*para);
    virtual void run(void) = 0;
    void terminate();
    int  join();
    unsigned long  getThreadNo()const;
    int start();
};
#endif
