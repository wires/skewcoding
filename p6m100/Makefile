SHELL  =/bin/sh
#CFLAGS = -flibrary-level 0
#CC     = ~/workspace/bsplib/bin/bspcc
CC     = mpcc
LDFLAGS = -lbsponmpi

all: bspfactor2

bspfactor2: finitefield.o

clean: 
	rm -f STAT.bsp PROF.bsp *.tab bspfactor bspfactor2 *.o
