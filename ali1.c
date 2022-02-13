/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: ali1.c
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#include "ali1.h"

/********************************************************************/


/* Opens a file in the requested mode 
	INPUT: mode - string
	OUTPUT FILE* - file pointer */
FILE* openFile(char mode[]) {
	char filename[FILENAME_LENGTH];
	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: Opening a file with a name length of %d\n", FILENAME_LENGTH);}
	#endif
	
	printf("Anna tiedoston nimi: ");
	fgets(filename, FILENAME_LENGTH, stdin);
	filename[strlen(filename) - 1] = '\0';
	
	#if DEBUG
	if (DEBUG) {printf("DEBUG: Parsed filename %s\n", filename);}
	#endif
	
	FILE *file;
	
	/* Error handling for read and write scenarios */
	if (!(strcmp(mode, "r")) && (file = fopen(filename, mode)) == NULL) {
		printf("Tiedoston lukeminen epäonnistui.\n");
		return NULL;
	} else if (!(strcmp(mode, "w")) && (file = fopen(filename, mode)) == NULL) {
		printf("Tiedostoon kirjoittaminen epäonnistui.\n");
		return NULL;
	}
	
	return file;
}

void writeResults(TOTAL totals[]) {

	if (!strcmp(totals[0].name, DEFAULT_NAME)) {
		printf("Ei tulostettavaa, analysoi ensin palautustiedsto.\n");
		return;
	}
	
	char action[4];
	printf("Tulosta tiedostoon (k/e): ");
	fgets(action, 4, stdin);
	action[strlen(action) - 1] = '\0';
	
	if (!strcmp(action, "k") || !strcmp(action, "K")) {
		writeToFile(totals);
	} else if (!strcmp(action, "e") || !strcmp(action, "E")) {
		printArray(totals);
	} else {
		printf("Tuntematon valinta, yritä uudestaan.\n");
	}
}

void writeToFile(TOTAL totals[]) {
	
	FILE *file = openFile("w");
	
	fprintf(file, "Tehtävä;Lkm\n");
	
	for (int i = 0; i < MAX_EXERCISES; i++) {
		fprintf(file, "%s;%d\n", totals[i].name, totals[i].exReturns);
		/*
		if(strcmp(totals[i].name, DEFAULT_NAME)) {
			fprintf(file, "%s;%d\n", totals[i].name, totals[i].exReturns);
		}*/
	}
	
	fclose(file);
}

/*
int debugHandler (char text[], int action) {
	if (!DEBUG) {return -1;}

	If a value of 1 was passed initialise
	if (action) {
		FILE* dFile;
		struct tm *tm;
		char logName[];
		
		time_t currentTime;
		tm = localtime(&currentTime);
		
		stftime(logName, sizeof(logName), "%d.%m.%Y_%H%M", tm);
		
		if ((dFile = fopen(logName, mode)) == NULL) {
			printf("!!FAILED TO CREATE A DEBUG LOG!!\n\n");
			return NULL;
		}
		debugInitialised = 1;
		return action;
	} else if (!action && (strlen(text) > 0)) {
		fprintf(file, text);
		return action;
	} else if (action < 0) {
		fclose(dFile);
		return action;
	}
	
	return -1;
}

int fdebug(char text[]) {
	return debugHandler(text, 0);
} */


/* Reads a .csv file and parses the data
	INPUT: EXERCISE* - pointer to the start of an empty linked list
	OUTPUT EXERCISE* - pointer to the start of the linked list */
EXERCISE *readfile(EXERCISE *pStart) {
	FILE* file;
	/*EXERCISE *pEnd = NULL;*/
	file = openFile("r");
	
	if (file == NULL) {exit(0);}
	
	char buf[255];
	char line[LINE_LENGTH];
	char *p1, *p2, *p3, *p4;
	
	int totalReturns = 0;
	
	time_t now = time(NULL);
	struct tm earliest = *localtime(&now);
	struct tm latest;
	
	
	fgets(line, LINE_LENGTH, file); //remove first line
	while (fgets(line, LINE_LENGTH, file) != NULL) {
		p1 = strtok(line, ";");
		p2 = strtok(NULL, ";");
		p3 = strtok(NULL, ";");
		p4 = strtok(NULL, "\n");
		
		EXERCISE *new = allocMemory(sizeof(EXERCISE));
		
		struct tm *ptr = NULL;
		if ((ptr = (struct tm*)malloc(sizeof(struct tm))) == NULL) {printf("Muistinvaraus epäonnistui.\n");}
		memset(ptr, 0, sizeof(struct tm));
		
		strcpy(new->name, p2);
		new->exID = atoi(p3);
		new->userID = atol(p4);
		new->pNext = NULL;
		
		strptime(p1, "%d/%m/%y, %H:%M", ptr);
		new->date = ptr;

		#if DEBUG
		strftime(buf, sizeof(buf), "%d/%m/%y, %H:%M", new->date);
		printf("%s;%s;%d;%d \n", buf, new->name, new->exID, new->userID);
		#endif
			
		/* Determine if the new return is the new latest or earliest */
		if (difftime(mktime(ptr), mktime(&latest)) > 0) {latest = *ptr;}
		if (difftime(mktime(ptr), mktime(&earliest)) < 0) {earliest = *ptr;}	
		
		if (pStart == NULL) {
			pStart = new;
		} else {
			new = appendToList(pStart, new);
		}
		totalReturns++;
	
		#if DEBUG
		if (DEBUG) {printf("-----------------------------\n");}
		#endif
	}
	
	char buf2[50];
	strftime(buf, sizeof(buf), "%d.%m.%Y", &earliest);
	strftime(buf2, sizeof(buf2), "%d.%m.%Y", &latest);
	
	printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.\n", totalReturns, buf, buf2);
	
	fclose(file);
	return pStart;
}



/*******************************************************************/
/* eof */
