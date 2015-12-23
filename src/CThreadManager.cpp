/*
 * =====================================================================================
 *
 *       Filename:  CThreadManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2015 04:38:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"CThreadManager.h"
CThreadManager::CThreadManager()
{
    m_NumOfThread = 10;
    printf("Creating CThreadPool with avalid thread num %d\n",m_NumOfThread);
    m_pool = new CThreadPool(m_NumOfThread);
    printf("CThreadPool created!\n");
}
CThreadManager::CThreadManager(int num)
{
    m_NumOfThread = num;
    printf("Creating CThreadPool with avalid thread num %d\n",m_NumOfThread);
    m_pool = new CThreadPool(m_NumOfThread);
    printf("CThreadPool created!\n");
}
CThreadManager::~CThreadManager()
{
//    printf("Delete m_NumOfThread\n");
    if(m_pool != NULL)
    {
        delete m_pool;
        printf("Delete m_NumOfThread\n");
    }
}

int CThreadManager::terminateAll()
{
    printf("Start terminating Allthreads in pool manager\n");
    m_pool->terminateAll();
}

void CThreadManager::run(CJob *job,void *jobdata)
{
    printf("pool manager load job...\n");
    m_pool->Run(job,jobdata);
}
