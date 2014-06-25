#Makefile 

ALL = topsort

all: topsort 

topsort: 
	gcc topsort.c -o topsort

clean:
	rm $(ALL)
