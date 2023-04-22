#include "CList.h"
#include "Func.h"

//-------------------------------------------------------------------------------

// Creat/open a new list of students from a text file
CList* AddElemListFile() {
	FILE* pFile = fopen("marks.txt", "r");

	if (pFile == NULL) {
		printf("\nError opening file\n\n");
		return NULL;
	}
	fseek(pFile, 0, SEEK_END);
	if (ftell(pFile) == 0) {
		printf("\nFile is empty\n\n");
		return NULL;
	}

	pFile = fopen("marks.txt", "r");
	CList* pTemp = NULL;
	pTemp = (CList*)malloc(sizeof(CList));
	CList* pHead = NULL;
	CList* pNextStud = pTemp;

	char* pw;
	char string[MAXLENG];
	int index = 0;
	while (!feof(pFile))
	{
		pTemp = pNextStud;
		fgets(string, MAXLENG, pFile);
		pw = strtok(string, ".\t\n");
		strcpy(pTemp->m_value.m_szSurname, pw);
		pw = strtok(NULL, ".\t\n");
		strcpy(pTemp->m_value.m_czName, pw);
		pw = strtok(NULL, ".\t\n");
		pTemp->m_value.m_iBday = atoi(pw);
		pw = strtok(NULL, ".\t\n");
		pTemp->m_value.m_iBmonth = atoi(pw);
		pw = strtok(NULL, ".\t\n");
		pTemp->m_value.m_iByear = atoi(pw);

		for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
			pw = strtok(NULL, "\t\n");
			pTemp->m_value.m_iaMark[idex_mark] = atoi(pw);
		}
		if (!pHead) {
			pHead = pTemp;
			strcpy(pHead->m_value.m_szSurname, pTemp->m_value.m_szSurname);
			strcpy(pHead->m_value.m_czName, pTemp->m_value.m_czName);
			pHead->m_value.m_iBday = pTemp->m_value.m_iBday;
			pHead->m_value.m_iBmonth = pTemp->m_value.m_iBmonth;
			pHead->m_value.m_iByear = pTemp->m_value.m_iByear;
			for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
				pHead->m_value.m_iaMark[idex_mark] = pTemp->m_value.m_iaMark[idex_mark];
			}
			pNextStud = (struct CNode*)malloc(sizeof(struct CNode));
			pHead->m_pnext = pNextStud;

		}
		if (pHead) {
			pNextStud = (struct CNode*)malloc(sizeof(struct CNode));
		}
		pTemp->m_pnext = pNextStud;
	}
	pTemp->m_pnext = NULL;
	pNextStud = NULL;
	pTemp = pHead;

	fclose(pFile);
	return pHead;
}

//-------------------------------------------------------------------------------

// Function to check if surname contains only letters
int is_valid_surname(char* name) {
	int res = 1;
	if (!isupper(name[0])) 
	{
		printf("Incorrect student`s surname. Student`s surname must begin with a capital letter.");
		res = 0;
	}
	for (int i = 0; name[i] != '\0'; i++) {
		if (!isalpha(name[i])) {
			printf("Incorrect student`s surname. Student`s surname cannot have numbers."
				" Student`s surname cannot have symbols (+, - , =, @, etc.)");
			res = 0;
		}
	}
	return res;
}

//-------------------------------------------------------------------------------

// Function to check if name contains only letters
int is_valid_name(char* name) {
	int res = 1;
	if (!isupper(name[0]))
	{
		printf("Incorrect student`s name. Student`s name must begin with a capital letter.");
		res = 0;
	}
	for (int i = 0; name[i] != '\0'; i++) {
		if (!isalpha(name[i])) {
			printf("Incorrect student`s name. Student`s name cannot have numbers."
				" Student`s name cannot have symbols (+, - , =, @, etc.)");
			res = 0;
		}
	}
	return res;
}


//-------------------------------------------------------------------------------

// Function to check if a date is valid
int is_valid_date(int day, int month, int year) {
	int is_valid = 1;
	int max_day;

	// Check year
	if (year < 1900 || year > 2020) {
		is_valid = 0;
		printf("\nInvalid year entered. Please enter a year between 1900 and 2020.");
	}

	// Check month
	if (month < 1 || month > 12) {
		is_valid = 0;
		printf("\nInvalid month entered. Please enter a month between 1 and 12.");
	}

	// Check day
	
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			max_day = 29;
		}
		else {
			max_day = 28;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		max_day = 30;
	}
	else {
		max_day = 31;
	}

	if (day < 1 || day > max_day) {
		is_valid = 0;
		printf("\nInvalid day entered. Please enter a day between 1 and %d.", max_day);
	}

	return is_valid;
}

//-------------------------------------------------------------------------------

// Creat a new list of students from the console
CList* AddElemListConsole() {
	CList* pHead = NULL;
	CList* pnext = NULL;
	CList* pTemp = NULL;
	int iAmount = 0;
	bool check = 0;
	do {
		printf("Amount of students: ");
		std::cin >> iAmount;
		if (std::cin.fail())
		{
			printf("Amount must be a number. Try again.\n\n");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if(iAmount <= 0) printf("Amount cannot be negative and equal to 0. Try again.\n\n");
	} while (iAmount <= 0);
	if ((iAmount > 290) && (iAmount < 300)) {
		printf("\nMaximum amount will be nearly reached.\n"
			"Maximum amount is 300\n\n");
	}
	if (iAmount == 300) {
		printf("\nMaximum amount will be reached.\n"
			"Last student of the list will be last student possible.\n\n");
	}
	if (iAmount > 300) {
		printf("\nMaximum amount will be reached.\n"
			"You cannot add more students then 300 to the list.\n"
			"300th student of the list will be last student possible.\n\n");
		iAmount = 300;
	}
	for (int i = 0; i < iAmount; i++)
	{
		pTemp = (CList*)malloc(sizeof(CList));
		if (!pTemp) {
			fprintf(stderr, "Memory allocation failed.\n");
			exit(EXIT_FAILURE);
		}

		int valid_input = 0;
		printf("\nEnter student information:\n");
		while (!valid_input) {
			printf("\n_(Surname) _(Name):\n");

			// Read input and check validity of name
			if (scanf("%s %s", pTemp->m_value.m_szSurname, pTemp->m_value.m_czName) != 2
				|| !is_valid_surname(pTemp->m_value.m_szSurname) || !is_valid_name(pTemp->m_value.m_czName)) {
				printf("\nInvalid input for surname/name. It should only contain letters.\n");
				while (getchar() != '\n') {} // Clear input buffer
				continue;
			}
			valid_input = 1;
		}
		valid_input = 0;
		while (!valid_input) {
			printf("\n_._._ (Birthday_date, DD.MM.YYYY):\n");
			// Read input and check validity of date of birth
			if (scanf("%d.%d.%d", &pTemp->m_value.m_iBday, &pTemp->m_value.m_iBmonth, &pTemp->m_value.m_iByear) != 3
				|| !is_valid_date(pTemp->m_value.m_iBday, pTemp->m_value.m_iBmonth, pTemp->m_value.m_iByear)) {
				printf("\nInvalid input for date of birth. Date should be in the format dd.mm.yyyy and should be a valid date between 1900 and 2020.\n");
				while (getchar() != '\n') {} // Clear input buffer
				continue;
			}
			valid_input = 1;
		}
		valid_input = 0;
		while (!valid_input) {
			printf("\nMarks (four marks from 1 to 5)):\n");
			// Read input and check validity of marks
			int mark;
			for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
				if (scanf("%d", &mark) != 1 || mark < 1 || mark > 5) {
					printf("Invalid input for mark %d. Marks should be integers between 1 and 5.\n", idex_mark + 1);
					while (getchar() != '\n') {} // Clear input buffer
					break;
				}
				pTemp->m_value.m_iaMark[idex_mark] = mark;
				valid_input = 1;
			}
		}
		pTemp->m_pnext = NULL;

		if (!pHead) {
			pHead = pTemp;
			pnext = pTemp;
		}
		else {
			pnext->m_pnext = pTemp;
			pnext = pTemp;
		}
	}
	return pHead;
}

//-------------------------------------------------------------------------------

// Add student from the console
CList* AddElem(CList** pHead) {

	if (SizeList(*pHead) > 300) {
		printf("\nMaximum amount is already reach.\n"
			"You cannot add new student to the list.\n\n");
	}
	else
	{
		if ((SizeList(*pHead) > 290) && (SizeList(*pHead) < 300)) {
			printf("\nMaximum amount is nearly reached.\n"
				"Maximum amount is 300\n\n");
		}
		if (SizeList(*pHead) == 300) {
			printf("\nMaximum amount is nearly reached.\n"
				"This student will be last student possible.\n\n");
		}
		CList* pTemp = NULL;
		pTemp = (CList*)malloc(sizeof(CList));
		if (!pTemp) {
			fprintf(stderr, "\nMemory allocation failed.\n\n");
			exit(EXIT_FAILURE);
		}

		int valid_input = 0;
		printf("\nEnter student information:\n");
		while (!valid_input) {
			printf("\n_(Surname) _(Name):\n");

			// Read input and check validity of name
			if (scanf("%s %s", pTemp->m_value.m_szSurname, pTemp->m_value.m_czName) != 2
				|| !is_valid_name(pTemp->m_value.m_szSurname) || !is_valid_name(pTemp->m_value.m_czName)) {
				printf("\nInvalid input for surname/name. It should only contain letters.\n");
				while (getchar() != '\n') {} // Clear input buffer
				continue;
			}
			valid_input = 1;
		}
		valid_input = 0;
		while (!valid_input) {
			printf("\n_._._ (Birthday_date, DD.MM.YYYY):\n");
			// Read input and check validity of date of birth
			if (scanf("%d.%d.%d", &pTemp->m_value.m_iBday, &pTemp->m_value.m_iBmonth, &pTemp->m_value.m_iByear) != 3
				|| !is_valid_date(pTemp->m_value.m_iBday, pTemp->m_value.m_iBmonth, pTemp->m_value.m_iByear)) {
				printf("\nInvalid input for date of birth. Date should be in the format dd.mm.yyyy and should be a valid date between 1900 and 2020.\n");
				while (getchar() != '\n') {} // Clear input buffer
				continue;
			}
			valid_input = 1;
		}
		valid_input = 0;
		while (!valid_input) {
			printf("\nMarks (four marks from 1 to 5)):\n");
			// Read input and check validity of marks
			int mark;
			for (int idex_mark = 0; idex_mark < NUM_MARK; idex_mark++) {
				if (scanf("%d", &mark) != 1 || mark < 1 || mark > 5) {
					printf("\nInvalid input for mark %d. Marks should be integers between 1 and 5.\n", idex_mark + 1);
					while (getchar() != '\n') {} // Clear input buffer
					break;
				}
				pTemp->m_value.m_iaMark[idex_mark] = mark;
				valid_input = 1;
			}
		}
		pTemp->m_pnext = NULL;

		if (*pHead == NULL) {
			*pHead = pTemp;
		}
		else {
			CList* pNow = *pHead;
			while (pNow->m_pnext != NULL) {
				pNow = pNow->m_pnext;
			}
			pNow->m_pnext = pTemp;
			pNow->m_pnext->m_pnext = NULL;
		}
		printf("\n");
	}
	return *pHead;
}

//-------------------------------------------------------------------------------