/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: paaohjelma.h
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */ /*
 A file with common or shared structs and variables
*******************************************************************/

#include "ali1.h"
#include "ali2.h"
#include "debug.h"

#ifndef paaohjelma
#define paaohjelma
#define STRING_LENGTH 30

#define DEFAULT_NAME "Tyhjä"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define _USE_XOPEN
#define _XOPEN_SOURCE
#define _GNU_SOURCE

char *strptime(const char *s, const char *format, struct tm *tm);

/********************************************************************/


/* Holds an individuals returned exercise for a linked list */
typedef struct EXERCISE{
	struct tm *date;
	int exID;
	long userID;
	struct EXERCISE* pNext;
	char name[STRING_LENGTH];
} EXERCISE;

/* Holds the total amount of returns for an exercise */
typedef struct total{
	char name[STRING_LENGTH];
	int exReturns;
	struct TOTAL* pNext;
} TOTAL;

#endif
/*******************************************************************/
/* eof */


