/*
 * =====================================================================================
 *
 *       Filename:  CThreadManager.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 04:37:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CTHREADMANAGER_H
#define CTHREADMANAGER_H
#include"CJob.h"
#include"CThreadPool.h"
#include"Utility.h"
class CThreadManager{
private:
    CThreadPool *m_pool;
    unsigned int m_NumOfThread;
public:
    CThreadManager();
    CThreadManager(int num);
    virtual ~CThreadManager();
    void run(CJob *job,void* jobdata);
    int terminateAll();
};
#endif
