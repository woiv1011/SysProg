# use this compiler
#CC = $(shell which gcc)
#CXX= $(shell which g++)
#CFLAGS = -w -O2 -g -fstack-arrays -pipe -ip -m64 -fexceptions -fbuiltin -ffast-math -fp-model fast=2 -funroll-loops -fnoprefetch-loop-arrays -fno-math-errno -std=c11

#CXX = $(shell which g++)
#CXXFLAGS = -w -O2 -g -fstack-arrays -pipe -ip -m64 -fexceptions -fbuiltin -ffast-math -fp-model fast=2 -funroll-loops -fnoprefetch-loop-arrays -fno-math-errno -std=c11
#CXXFLAGS += $(INCLUDES)


BASE=.

CXX = $(shell which g++)
CXXFLAGS = -Wall -O2 -g -m64
#-Wall -fstack-arrays -pipe -m64 -fexceptions -fbuiltin -ffast-math -funroll-loops -fno-math-errno -std=c11
#CXXFLAGS += $(INCLUDES)

all: main.cpp
#rm main
	@$(CXX) $(CXXFLAGS) main.c -o main.out

#hellomake: hellomake.c hellofunc.c
#	gcc -o hellomake hellomake.c hellofunc.c -I.

clean:
#	@echo -------------------------------------------------------------
#	@echo clean
#	@echo -------------------------------------------------------------
#-rm -f *.i
	@rm main.out


