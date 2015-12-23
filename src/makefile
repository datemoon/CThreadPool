all: myThreadPool

CC = g++


OBJ= CJob.o CThread.o CWorkerThread.o CThreadPool.o CThreadManager.o main.o


myThreadPool:$(OBJ) 
	$(CC) -o myThreadPool $(OBJ) -lpthread

CJob.o: CJob.cpp CJob.h Utility.h CThreadPool.o
	$(CC) -c  CJob.cpp

CWorkerThread.o: CWorkerThread.cpp CWorkerThread.h CThread.o  Utility.h CThreadPool.o  
	$(CC) -c  CWorkerThread.cpp 

CThread.o: CThread.cpp CThread.h Utility.h
	$(CC) -c CThread.cpp

CThreadPool.o: CThreadPool.cpp CThreadPool.h Utility.h CJob.o  CWorkerThread.o 
	$(CC) -c CThreadPool.cpp

CThreadManager.o: CThreadManager.cpp CThreadManager.h CJob.o CThreadPool.o
	$(CC) -c CThreadManager.cpp

main.o: main.cpp CJob.o CThreadManager.o   
	$(CC) -c main.cpp


clean:
	-rm $(OBJ)
