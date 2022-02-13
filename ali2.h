/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: ali2.h
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#ifndef ali2
#define ali2
#define MAX_EXERCISES 60

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "paaohjelma.h"
#include "debug.h"

#define _USE_XOPEN
#define _XOPEN_SOURCE
#define _GNU_SOURCE

/********************************************************************/


EXERCISE *createExerciseList();
EXERCISE *getLastLink(EXERCISE *ptr);
EXERCISE *appendToList(EXERCISE *pList, EXERCISE *pNew);
void printList(EXERCISE *pList);
EXERCISE *allocMemory (int reqMem);
void deleteList(EXERCISE *pStart);

void analyseData(TOTAL totals[], EXERCISE* pStart);
int searchFor(TOTAL totals[], char name[]);
int findEmptyIndex(TOTAL totals[]);
void fillArray(TOTAL totals[]);
void printArray(TOTAL totals[]);

#endif
/*******************************************************************/
/* eof */
