/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: ali2.c
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include "ali2.h"

/********************************************************************/

/*********************** EXERCISE LIST HANDLING ***********************/

/* Creates an empty exercise pointer for a linked list */
EXERCISE *createExerciseList() {
	EXERCISE *pStart = NULL;
	return pStart;
}

/* Returns the last link in an exercise linked list */
EXERCISE *getLastLink(EXERCISE *pStart) {
	if (pStart == NULL) {
		return pStart;
	}
	
	EXERCISE *ptr = pStart;
	while (ptr->pNext != NULL) {
		ptr = ptr->pNext;
	}

	return ptr;
}

/* Opens a file in the requested mode 
	INPUT: EXERCISE* - a pointer to the start of the list
	OUTPUT EXERCISE* - a pointer to the new link to be appended */
EXERCISE *appendToList(EXERCISE *pStart, EXERCISE *pNew) {
	EXERCISE *pLast = getLastLink(pStart);
	
	/* If empty */
	if (pStart == NULL) {
		pStart = pNew;
	} else {
		pLast->pNext = pNew;
	}	
	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: struct appended to the list\n");}
	#endif
	
	return pNew;
}

/* Takes a pointer to the start of the list */
void printList(EXERCISE *pList) {
	EXERCISE *ptr = pList;
	
	#if DEBUG
	if (DEBUG) {printf("\nDEBUG:Printing list\n");}
	#endif
	
	while (ptr != NULL) {
		char date[50];
		strftime(date, sizeof(date), "%d/%m/%Y, %H:%M", ptr->date);
		printf("%s;%s;%d;%ld\n", date, ptr->name, ptr->exID, ptr->userID);
		ptr = ptr->pNext;
	}
	#if DEBUG
	printf("-----------------------------\n");
	#endif
}

/* Allocates EXERCISE memory
	INPUT: int - required memory in bytes
	OUTPUT: EXERCISE* - a pointer to the allocated memory */
EXERCISE *allocMemory (int reqMem) {
	EXERCISE *ptr = NULL;
	
	if ((ptr = (EXERCISE*)malloc(reqMem)) == NULL) {printf("Muistinvaraus epäonnistui.\n");}
	memset(ptr, 0, reqMem);
	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: %d bytes of memory successfully allocated\n", reqMem);}
	#endif
	
	return ptr;
}
/*
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind.txt" ./ohjelma
*/
void deleteList(EXERCISE *pStart) {
	EXERCISE *ptr = pStart;
	int amount = 0;
	
	do {
		ptr = pStart;
		pStart = ptr->pNext;
		amount += sizeof((ptr->date));
		free(ptr->date);
		amount += sizeof(*ptr);
		free(ptr);
	} while (ptr->pNext != NULL);
	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: Deleted list. Released %d bytes of memory\n", amount);}
	#endif

}


/*********************** DATA ANALYSIS AND TOTALS ***********************/

void printArray(TOTAL totals[]) {
	printf("Tehtävä;Lkm\n");
	for (int i = 0; i < MAX_EXERCISES; i++) {
		printf("%s;%d\n", totals[i].name, totals[i].exReturns);
		/*
		if (strcmp(totals[i].name, DEFAULT_NAME)) {
			printf("%s;%d\n", totals[i].name, totals[i].exReturns);
		}
		*/
	}
}

int searchFor(TOTAL totals[], char name[]) {
	for (int i = 0; i < MAX_EXERCISES; i++) {
		if (!strcmp(totals[i].name, name)) {
			return i;
		}
	}
	return -1;
}

int findEmptyIndex(TOTAL totals[]) {
	for (int i = 0; i < MAX_EXERCISES; i++) {
		if (!strcmp(totals[i].name, DEFAULT_NAME)) {
			return i;
		}
	}
	
	return -1;
}

void analyseData(TOTAL totals[], EXERCISE* pStart) {

	if (pStart == NULL) {
		printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
		return;
	}
	
	
	/* Clear the array in case of reanalysis */
	fillArray(totals);
	
	EXERCISE *ptr = pStart;
	int index;
	int returnedExercises = 0;
	int uniqueExercises = 0;

	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: Analysing data\n");}
	#endif
	
	while (1) {
		if (ptr == NULL) {break;}
		
		index = ptr->exID - 1;
		
		/* If the index was previously empty */
		if (!strcmp(totals[index].name, DEFAULT_NAME)) {
			uniqueExercises++;
		}
		
		/* Replace data */
		strcpy(totals[index].name, ptr->name);
		totals[index].exReturns = totals[index].exReturns + 1;
		
		returnedExercises++;
		ptr = ptr->pNext;
	}
	
	#if DEBUG
	if (DEBUG) {printf("\nDEBUG: Data analysed\n");}
	#endif
	
	printf("Palautuksia oli yhteensä %d, %d eri tehtävässä, keskimäärin %d per tehtävä.\n",
	returnedExercises, uniqueExercises, returnedExercises / uniqueExercises);
}


void fillArray(TOTAL totals[]) {
	for (int i = 0; i < MAX_EXERCISES; i++) {
		TOTAL new;
		strcpy(new.name, DEFAULT_NAME);
		new.exReturns = 0;
		
		totals[i] = new;
	}
}
/*

void analyseData(TOTAL totals[], EXERCISE* pStart) {

	if (pStart == NULL) {
		printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
		return;
	}
	
	EXERCISE *ptr = pStart;
	int index;
	int returnedExercises = 0;
	int uniqueExercises = 0;

	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: Analysing data\n");}
	#endif
	
	while (1) {;
		if (ptr == NULL) {break;}
		
		index = searchFor(totals, ptr->name);
		
		if (index == -1) {
			//TOTAL *pTotal = NULL;
			//if ((pTotal = (TOTAL*)malloc(sizeof(TOTAL))) == NULL) {printf("Muistinvaraus epäonnistui.\n");}
			//memset(pTotal, 0, sizeof(TOTAL));
		
			index = findEmptyIndex(totals);
			
			strcpy(totals[index].name, ptr->name);
			totals[index].exReturns = 1;
			

			returnedExercises++;
			uniqueExercises++;
			
			#if DEBUG
			if (DEBUG) {printf("DEBUG: Exercise not in list. Adding\n");}
			#endif
		} else {
			totals[index].exReturns++;
			returnedExercises++;
			#if DEBUG
			if (DEBUG) {printf("DEBUG: Exercise found. Updated returns\n");}
			#endif
		}
		ptr = ptr->pNext;
	}
	
	#if DEBUG
	if (DEBUG) {printf("\nDEBUG: Data analysed\n");}
	#endif
	
	printf("Palautuksia oli yhteensä %d, %d eri tehtävässä, keskimäärin %d per tehtävä.\n",
	returnedExercises, uniqueExercises, returnedExercises / uniqueExercises);
}

void sortArray(TOTAL totals[]) {
	int pivotIndex = MAX_EXERCISES / 2;
	int lecture = strtok(line, ";");

	return;
}


void deleteArray(TOTAL totals[]) {
	int amount = 0;
	
	for (int i = 0; i < MAX_EXERCISES; i++) {
		amount += sizeof(totals[i]);
		free(totals[i]);
	}
	
	if (DEBUG) {printf("DEBUG: Deleted list. Released %d bytes of memory\n", amount);}
};*/



/*******************************************************************/
/* eof */
