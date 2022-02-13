# Makefile
HT: paaohjelma.o ali1.o ali2.o
	gcc paaohjelma.o ali1.o ali2.o -o HT -g
paaohjelma.o: paaohjelma.c paaohjelma.h ali1.h ali2.h debug.h
	gcc paaohjelma.c -c -Wall -std=c99 -pedantic -g
ali1.o: ali1.c ali1.h debug.h
	gcc ali1.c -c -Wall -std=c99 -pedantic -g
ali2.o: ali2.c ali2.h debug.h
	gcc ali2.c -c -Wall -std=c99 -pedantic -g
