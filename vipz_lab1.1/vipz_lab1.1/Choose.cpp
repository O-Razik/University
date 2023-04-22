#include "CList.h"
#include "Func.h"

//-------------------------------------------------------------------------------

// Choose action the next action on the list of students
int Choose(CList** pHead) {
	char cInput[MAXLENG];
	if (*pHead == NULL) {
		while (1) {
			printf("Where do you want to read the list from?\n"
				"For console - press 1\nFor textfile - press 2\n"
				"---------------------------------------\n"
				"Exit - press 0\n\n");
			scanf(" %s", &cInput);
			if (!strcmp(cInput, "1")) {
				*pHead = AddElemListConsole();
				PrintList(*pHead);
				break;
			}
			else if (!strcmp(cInput, "2")) {
				*pHead = AddElemListFile();
				PrintList(*pHead);
				break;
			}
			else if (!strcmp(cInput, "0")) {
				return 1;
			}
			else {
				printf("\nIncorrect input. Try again.\n");
			}
		}
		return 0;
	}
	else if (*pHead != NULL) {
		while (1) {
			if (*pHead == NULL) {
				printf("\nList is empty. Program will close\n");
				return 1;
			}

			printf("\n What do you want to do next?"
				" Press the corresponding button.\n"
				" 1)Add element\n 2)Two youngest\n"
				" 3)Have no 2\n 4)Top graders\n");
			printf(" 5)Save \n 6)Info\n 7)Exit\n");
			scanf(" %s", &cInput);
			if (!strcmp(cInput, "1"))
			{
				AddElem(pHead);
				PrintList(*pHead);
			}
			else if (!strcmp(cInput, "2")) TwoYoungest(pHead);
			else if (!strcmp(cInput, "3")) NoTwos(pHead);
			else if (!strcmp(cInput, "4")) OnlyFiveFour(pHead);
			else if (!strcmp(cInput, "5")) SaveListFile(*pHead);
			else if (!strcmp(cInput, "6"))
			{
				printf("\nInformation:\n"
					" 1) Addes new element to student list from console;"
					"\n 2) Shows the two youngest students;\n"
					" 3) Sortes in descending order by age,"
					" deletes from the list students with twos;\n"
					" 4) Sortes in descending order by age,"
					" deletes from the list students with ones, twos and threes, "
					"leaves students with fours and fives;\n"
					" 5) Saves table in textfile;\n 7)Closes the program.\n");
			}
			else if (!strcmp(cInput, "7")) break;
			else {
				printf("\nIncorrect input. Try again.\n");
			}
		}
		return 1;
	}
}

//-------------------------------------------------------------------------------