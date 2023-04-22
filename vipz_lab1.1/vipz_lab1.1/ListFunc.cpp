#include "CList.h"
#include "Func.h"

//-------------------------------------------------------------------------------

// Save the student table in a text file
void SaveListFile(CList* pHead) {
	FILE *pFile = fopen("savedtables.txt", "a");
	fprintf(pFile, "\n\n ");
	for (int i = 0; i < NUM_SYM_TABLE; i++) { fprintf(pFile, "="); }
	fprintf(pFile, "\n  || %-12.12s || %-12.12s || %-14.14s || %-8.8s||\n ",
		"Surname", "Name", "Birthday date", "Marks");
	for (int i = 0; i < NUM_SYM_TABLE; i++) { fprintf(pFile, "="); }
	for (; pHead != NULL; pHead= pHead->m_pnext)
	{
		
		fprintf(pFile, "\n  || %-12.12s || %-12.12s ||  %02d.%02d.%02d    || ",
			pHead->m_value.m_szSurname, pHead->m_value.m_czName,
			pHead->m_value.m_iBmonth, pHead->m_value.m_iBday, pHead->m_value.m_iByear);
		for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
			fprintf(pFile, "%d ", pHead->m_value.m_iaMark[idex_mark]);
		}
		fprintf(pFile, "||\n ");
		for (int i = 0; i < NUM_SYM_TABLE; i++) { fprintf(pFile, "="); }
	}
	fclose(pFile);
	printf("\nTable saved\n");
}

//-------------------------------------------------------------------------------

// Display the student table in the console
void PrintList(CList *pHead) {
	if (pHead == NULL) {
		printf("\nList is empty\n\n");
		return;
	}

	CList *pTemp = pHead;
	printf(" ");
	PR_LINE
	printf("\n  || %-12.12s || %-12.12s || %-14.14s || %-8.8s||",
		"Surname", "Name", "Birthday date", "Marks");
	printf("\n ");
	while (pTemp) {
		PR_LINE
		printf("\n  || %-12.12s || %-12.12s || %02d.%02d.%02d    ||",
			pTemp->m_value.m_szSurname, pTemp->m_value.m_czName,
			pTemp->m_value.m_iBday, pTemp->m_value.m_iBmonth, pTemp->m_value.m_iByear);
		for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
			printf(" %d", pTemp->m_value.m_iaMark[idex_mark]);
		}
		printf("  ||\n ");
		pTemp = pTemp->m_pnext;
	}
	PR_LINE
	printf("\n\n");
}

//-------------------------------------------------------------------------------

// Find the length of the list of students
int SizeList(CList* pHead) {
	int iCount = 0;
	while (pHead) {
		iCount++;
		pHead = pHead->m_pnext;
	}
	return iCount;
}

//-------------------------------------------------------------------------------