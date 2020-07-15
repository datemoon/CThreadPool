
pybind_inc=-I/usr/include/python3.6m -I/usr/local/lib/python3.6/site-packages/pybind11/include

pybind_suffix=.cpython-36m-x86_64-linux-gnu.so

CC=g++

CXXFLAG+=-O3 -Wall -fPIC -std=c++11 $(pybind_inc)

lib=example$(pybind_suffix)

all:$(lib) 

$(lib):example.o
	$(CC) -shared -o $@ $^

%.o:%.c
	$(CC)  $(CXXFLAG)  -c -o $@ $<

%.o:%.cpp
	$(CC) $(CXXFLAG) -c -o $@ $<

.PHONY:clean
	
clean:
	rm -f $(lib) *.o
