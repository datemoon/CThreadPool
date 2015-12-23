/*
 * =====================================================================================
 *
 *       Filename:  Cjob.h
 *
 *    Description: The head of class Cjob
 *
 *        Version:  1.0
 *        Created:  12/18/2015 09:04:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CJOB_H
#define CJOB_H
#include"Utility.h"
class CJob
{
private:
    int m_JobNo;
    char *m_JobName;
//    Cthread *m_WorkerThread;
public:
    CJob();
    virtual ~CJob();
    void setJobNo(int no);
    int getJobNo(void)const;
    void setJobName(char *name);
    char *getJobName()const;
  //  Cthread *getWorkerThread()const;
   // void setWorkerThread(Cthread *workerThread);
    virtual  void run(void *ptr)=0;
};
#endif
