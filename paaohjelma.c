/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: paaohjelma.c
 * Tekijä: Emilio Pizzuti
 * Opiskelijanumero: 0561487
 * Päivämäärä: 4.3.2021
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 **********
 Ohjelmiston tiedostonimet ovat suomeksi yhteensopivuuden ylläpitämiseksi Viopen kanssa.
 Muu koodi on englanniksi ymmärrettävyyden sekä selkeyden takia.
*******************************************************************/

#include "paaohjelma.h"

/********************************************************************/


/* Handles the text menu. Returns a negative integer on error.
	INPUT: - -
	OUTPUT int - integer parsed from the user's input */
int menu(){
	int selection = -1;
	
	printf("1) Lue tiedosto\n");
	printf("2) Analysoi tiedot\n");
	printf("3) Tulosta tulokset\n");
	printf("0) Lopeta\n");
	printf("Valintasi: ");
	
	char input[5];
	fgets(input, 4, stdin);
	input[strlen(input) - 1] = '\0';
	
	/* Count for atoi and its inability to recognise a zero */
	if (!strcmp(input, "0")) {
		return 0;
	}
	
	selection = atoi(input);
	
	if (selection == 0) {
		return -1;
	}

	#if DEBUG
	printf("DEBUG: selection was %d\n", selection);
	#endif
	return selection;
}


int main(){
	
	int selection = -1;
	EXERCISE *pStart = createExerciseList();
	/*
	EXERCISE *pEnd = pStart;
	EXERCISE *pCur;**/
	
	TOTAL totals[MAX_EXERCISES];
	fillArray(totals);
	
	//TOTAL *pTotalStart = createTotalList();
	
	while (1) {
		selection = menu();
		//printf("%d", selection);
		
		switch(selection) {
			case 0:
				printf("Kiitos ohjelman käytöstä.\n\n");
				deleteList(pStart);
				exit(0);
			case 1:
				if (pStart != NULL) {
					deleteList(pStart);
					pStart = createExerciseList();
				}
				pStart = readfile(pStart);
				#if DEBUG
				printList(pStart);
				#endif
				
				break;
			case 2:
				analyseData(totals, pStart);
				break;
			case 3:
				writeResults(totals);
				break;
			default:
				printf("Tuntematon valinta, yritä uudestaan.\n");
				break;
		}
		printf("\n");
	}
	return 0;
}

/*******************************************************************/
/* eof */
