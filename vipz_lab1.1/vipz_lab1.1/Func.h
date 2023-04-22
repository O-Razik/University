#pragma once
#include"CList.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<iostream>

//-------------------------------------------------------------------------------

// Choose action the next action on the list of students
int Choose(CList **pHead);

//-------------------------------------------------------------------------------

// Creat/open a new list of students from a text file
CList* AddElemListFile();

// Creat a new list of students from the console
CList* AddElemListConsole();

// Add student from the console
CList* AddElem(CList **pHead);

//-------------------------------------------------------------------------------

// Save the student table in a text file
void SaveListFile(CList *pHead);
// Display the student table in the console
void PrintList(CList *pHead);
// Find the length of the list of students
int SizeList(CList* pHead);

//-------------------------------------------------------------------------------

// Compare two students by age
int CompAge(CList *pStud, CList *pNextStud);

// Swap of 2 students' placed on the list
void SwitchPos(CList** pBefore, CList** pTemp, CList** pNext, CList** pHead);

// Sort the list of students in descending order by age.
void SortElemList(CList **pHead);

// Find the two youngest students among all students
void TwoYoungest(CList **pHead);

// Removal of students from the list who do not have a grade 2 (bad grade)
void NoTwos(CList **pHead);

// Removal of students from the list who do not have grades 1,2,3
// Students who have grades 4,5 (good grades) stay
void OnlyFiveFour(CList **pHead);

//-------------------------------------------------------------------------------