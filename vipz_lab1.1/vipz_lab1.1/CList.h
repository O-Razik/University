#pragma once

#define NUM_MARK 4
#define NUM_SYM_TABLE 65
#define PR_LINE for (int i = 0; i < NUM_SYM_TABLE; i++) { printf("="); }
#define MAXLENG 50

struct CStudent
{
	char m_szSurname[MAXLENG];
	char m_czName[MAXLENG];
	int m_iBday;
	int m_iBmonth;
	int m_iByear;
	int m_iaMark[NUM_MARK];
};

typedef struct CNode {
	struct CStudent m_value;
	struct CNode *m_pnext;
} CList;