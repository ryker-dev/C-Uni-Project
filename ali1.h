/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: ali1.h
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#ifndef ali1
#define ali1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "paaohjelma.h"
#include "debug.h"

#define FILENAME_LENGTH 20
#define LINE_LENGTH 80

#define _USE_XOPEN
#define _XOPEN_SOURCE
#define _GNU_SOURCE

/********************************************************************/


FILE* openFile(char mode[]);
EXERCISE *readfile(EXERCISE *pList);
void writeResults(TOTAL totals[]);
void writeToFile(TOTAL totals[]);

#endif
/*******************************************************************/
/* eof */
