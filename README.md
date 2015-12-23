src is the source file of my cpp threadpool

obj CThreadManager is the interface with user

obj CJob is the entrance of thread
    by implementing the interface run() in CJob, and invoke in CThreadManager. CThreadManager would invoke your thread in threadpool to the thread with least jobs or jobs queue below busyThreshold.

obj CThread is the pakage of thread

obj CWokerThread inherit CThread, adding features we wanted, becoming the worker of my thread pool

obj CThreadPool assigning jobs and scheduling the workers

