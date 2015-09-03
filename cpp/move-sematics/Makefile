CXXFLAGS=-Wall -Wextra -O0 -g -std=c++11

all: main

main: main.cpp matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -o main main.cpp matrix.cpp

clean:
	@rm -fr *.o main
