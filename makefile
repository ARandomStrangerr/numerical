compiler = g++
flag = -std=c++20

inpFile = main.cpp matrix.cpp
objFile = $(inpFile:.cpp=.o)
outFile = a.out

all:
	$(compiler) $(flag) $(inpFile) -o $(outFile)
