#include "CList.h"
#include "Func.h"

//-------------------------------------------------------------------------------

// Compare two students by age
int CompAge(CList* pTemp, CList* pnext) {
	if (pTemp->m_value.m_iByear < pnext->m_value.m_iByear) {
		return 1;
	}
	else if (pTemp->m_value.m_iByear > pnext->m_value.m_iByear) {
		return -1;
	}
	else {
		if (pTemp->m_value.m_iBmonth < pnext->m_value.m_iBmonth) {
			return 1;
		}
		else if (pTemp->m_value.m_iBmonth > pnext->m_value.m_iBmonth) {
			return -1;
		}
		else {
			if (pTemp->m_value.m_iBday < pnext->m_value.m_iBday) {
				return 1;
			}
			else if (pTemp->m_value.m_iBday > pnext->m_value.m_iBday) {
				return -1;
			}
			else {
				return 0;
			}
		}
	}
}

//-------------------------------------------------------------------------------

// Swap of 2 students' placed on the list
void SwitchPos(CList** pBefore, CList** pTemp, CList** pNext, CList** pHead) {
	if ((*pTemp) == (*pHead)) {
		(*pTemp)->m_pnext = (*pNext)->m_pnext;
		(*pHead) = (*pNext);
		(*pNext)->m_pnext = (*pTemp);
	}
	else {
		(*pTemp)->m_pnext = (*pNext)->m_pnext;
		(*pBefore)->m_pnext = (*pNext);
		(*pNext)->m_pnext = (*pTemp);
	}
}

//-------------------------------------------------------------------------------

//	Sort the list of students in descending order by age.
void SortElemList(CList** pHead) {
	if (*pHead == NULL)
	{
		printf("List is empty");
		return;
	}
	CList* pTemp1 = (*pHead), * pTemp2 = pTemp1->m_pnext, * pTemp0 = pTemp1;
	int iSize = SizeList(*pHead), iOne = 0;

	for (int i = 0; i < iSize - 1; i++) {
		pTemp1 = (*pHead);
		pTemp0 = pTemp1;
		iOne = 1;
		while (pTemp1->m_pnext)
		{
			pTemp2 = pTemp1->m_pnext;
			if (CompAge(pTemp1, pTemp2) == -1) {
				SwitchPos(&pTemp0, &pTemp1, &pTemp2, pHead);
				pTemp0 = pTemp2;
			}
			else {
				pTemp0 = pTemp1;
				pTemp1 = pTemp1->m_pnext;
			}
		}
	}
}

//-------------------------------------------------------------------------------

// Find the two youngest students among all students
void TwoYoungest(CList** pHead) {
	if (*pHead == NULL)
	{
		printf("List is empty");
		return;
	}
	CList* pHeadTemp = NULL;
	SortElemList(pHead);
	PrintList(*pHead);
	printf("\nTwo youngest:\n");
	for (pHeadTemp = *pHead; pHeadTemp->m_pnext->m_pnext != NULL; pHeadTemp = pHeadTemp->m_pnext) {}
	printf("\n ");
	PR_LINE
		printf("\n  || %-12.12s || %-12.12s || %-14.14s || %-8.8s|| \n ",
			"Surname", "Name", "Birthday date", "Marks");
	PR_LINE
		printf("\n  || %-12.12s || %-12.12s || %2.2d.%2.2d.%2.2d     ||",
			pHeadTemp->m_value.m_szSurname, pHeadTemp->m_value.m_czName,
			pHeadTemp->m_value.m_iBday, pHeadTemp->m_value.m_iBmonth,
			pHeadTemp->m_value.m_iByear);
	for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
		printf(" %d", pHeadTemp->m_value.m_iaMark[idex_mark]);
	}
	printf(" ||\n  "); PR_LINE
		printf("\n  || %-12.12s || %-12.12s || %2.2d.%2.2d.%2.2d     ||",
			pHeadTemp->m_pnext->m_value.m_szSurname,
			pHeadTemp->m_pnext->m_value.m_czName,
			pHeadTemp->m_pnext->m_value.m_iBday,
			pHeadTemp->m_pnext->m_value.m_iBmonth, pHeadTemp->m_pnext->m_value.m_iByear);
	for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
		printf(" %d", pHeadTemp->m_pnext->m_value.m_iaMark[idex_mark]);
	}
	printf(" ||\n ");
	PR_LINE
		printf("\n");
}

//-------------------------------------------------------------------------------

// Removal of students from the list who do not have a grade 2 (bad grade)
void NoTwos(CList** pHead) {
	SortElemList(pHead);
	CList* pBefore = (*pHead), * pTemp = (*pHead), * pNext;
	int iCheck, iOne = 1;
	while (pTemp) {
		iCheck = 0;
		for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
			if (pTemp->m_value.m_iaMark[idex_mark] == 2) {
				iCheck++;
			}
		}
		if (iCheck > 0) {
			if (pTemp == (*pHead)) {
				(*pHead) = pTemp->m_pnext;
				free(pTemp);
				pTemp = NULL;
				pTemp = (*pHead);
				pNext = pTemp->m_pnext;
			}
			else {
				pBefore->m_pnext = pTemp->m_pnext;
				pNext = pTemp->m_pnext;
				free(pTemp);
				pTemp = NULL;
				pTemp = pNext;

			}
		}
		else if (iCheck == 0) {
			pBefore = pTemp;
			pTemp = pTemp->m_pnext;
			if (pTemp != NULL) pNext = pTemp->m_pnext;
		}
		iCheck = 0;
	}
	PrintList(*pHead);
}

//-------------------------------------------------------------------------------

// Removal of students from the list who do not have grades 1,2,3
// Students who have grades 4,5 (good grades) stay
void OnlyFiveFour(CList** pHead) {
	if (pHead == NULL)
	{
		printf("List is empty");
		return;
	}
	SortElemList(pHead);
	CList* pBefore = (*pHead), * pTemp = (*pHead), * pNext;
	int iCheck, iOne = 1;
	while (pTemp) {
		iCheck = 0;
		for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
			if (pTemp->m_value.m_iaMark[idex_mark] == 4 ||
				pTemp->m_value.m_iaMark[idex_mark] == 5) {
				iCheck++;
			}
		}
		if (iCheck != NUM_MARK) {
			if (pTemp == (*pHead)) {
				(*pHead) = pTemp->m_pnext;
				free(pTemp);
				pTemp = NULL;
				pTemp = (*pHead);
				pNext = pTemp->m_pnext;
			}
			else {
				pBefore->m_pnext = pTemp->m_pnext;
				pNext = pTemp->m_pnext;
				free(pTemp);
				pTemp = NULL;
				pTemp = pNext;

			}
		}
		else if (iCheck == NUM_MARK) {
			pBefore = pTemp;
			pTemp = pTemp->m_pnext;
			if(pTemp) pNext = pTemp->m_pnext;
		}
		iCheck = 0;
	}
	PrintList(*pHead);
}

//-------------------------------------------------------------------------------