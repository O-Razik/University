#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// A, B - ���; a, b, c, d - ����������� �-��; eps - �������
double A, B, a, b, c, d, Xn, eps; 

#define MAX 50
// ��� �������
#define PR_LINE printf("\n ============================================================\n");
#define PR_L2 printf("\n ===================================\n");
#define PR_L3 printf("\n ========================================================================\n");

// ������� ��� ��������� �-��
#define X3(x) (x*x*x)
#define X2(x) (x*x)
#define F(x) ((a)*X3(x)+(b)*X2(x)+(c)*(x)+(d))
#define d1F(x) (3*(a)*X2(x)+2*(b)*(x)+(c))
#define d2F(x) (6*(a)*(x)+2*(b)) // 2-�� �������
#define Phi(x) (1/(a))*pow(((-(b)*X2(x)-(c)*(x)-(d))),(1.0/3.0))
#define d1Phi(x) (1.0/(a)) * (1.0/3) * pow((-(b)*X2(x)-(c)*(x)-(d)),(-2.0/3.0)) * (-2.0*(b)*(x) - (c))

// ������� ��� ������
#define XnMeth1(A,B) (((A)+(B))/2) // ����������� ��������
#define FMeth2X0(Xn,A,B) (-(F(Xn)*(B-A))/(F(B)-F(A)))
#define FormulaMeth2(Xn,B) (-((F(Xn)*(B-Xn))/(F(B)-F(Xn))))
#define FormulaMethNewt(Xn) (-(F(Xn)/d1F(Xn)))


int main() {
	// ���������� ���������� � ����� ����������
	FILE* values = fopen("values.txt", "r");
	char string[MAX], * lim = "abcdABeps= ";
	fgets(string, MAX, values);
	fgets(string, MAX, values);
	a = atof(strtok(string, lim));
	b = atof(strtok(NULL, lim));
	c = atof(strtok(NULL, lim));
	d = atof(strtok(NULL, lim));
	fgets(string, MAX, values);
	A = atof(strtok(string, lim));
	B = atof(strtok(NULL, lim));
	fgets(string, MAX, values);
	eps = atof(strtok(string, lim));
	fclose(values);

	if (((F(A)) * (F(B))) < 0) { // �������� �� ��������� ������� �������� � ����
		// ���� ����������
		printf("\n %0.1lf*x^3%c%0.1lf*x^2%c%0.1lf*x%c%0.1lf=0\n",
			a,(b<0)?'-':'+', fabs(b), (c < 0) ? '-' : '+', fabs(c), (d < 0) ? '-' : '+', fabs(d));
		printf("\n A = %.1lf \n B = %.1lf \n eps = %.3lf", A, B, eps);

		int i = 1;
		double A1 = A, B1 = B;
		// ����� ������쳿
		printf("\n\n 1)Dichotomy method: \n"); PR_LINE
			printf("  || n  ||     A     ||    B     ||   Xn     ||   F(Xn)  ||"); PR_LINE

			while (1) {
				Xn = XnMeth1(A, B); // ����������� ��������
				printf("  || %2d || %2lf || %lf || %lf || %lf ||", i, A, B, Xn, F(Xn)); PR_LINE
					if ((F(A)) * (F(Xn)) > 0) { // ������� �� ���� ���� ��������� �
						if (fabs(Xn - B) < eps) break; // �������� �� ���������� ���������
						A = Xn; // ���� ���� ��������� �

					}
					else if ((F(B)) * (F(Xn)) > 0) { // ������� �� ���� ���� ��������� �
						if (fabs(Xn - B) < eps) break; // �������� �� ���������� ���������
						B = Xn; // ���� ���� ��������� B
					}
				i++;
			}
		printf("  X* ~ %lf", Xn); // ���������� ����� �-��

		// ����� ����
		A = A1, B = B1, i = 1;
		printf("\n\n\n 2)Secant method: \n\n");
		printf("  C = -((F(Xn)*(B-Xn))/(F(B)-F(Xn)))\n");
		PR_L2
		printf("  || n  ||   Xn     ||    C      ||"); PR_L2

		// ����������� �0 ��� ������ ����
		if ((F(A)) * (d2F(A)) > 0) Xn = B;
		else if ((F(B)) * (d2F(B)) > 0)	Xn = A;


		printf("  || %2d || %lf || %lf ||", i, Xn, FMeth2X0(Xn, A, B)); PR_L2
		Xn += FMeth2X0(Xn, A, B); // ����������� �1 ��� ������ ����

		while (1) {
			printf("  || %2d || %lf || %lf ||", i, Xn, FormulaMeth2(Xn, B)); PR_L2
			if (fabs(Xn + FormulaMeth2(Xn, B) - Xn) < eps) break; // �������� �� ���������� ���������
			Xn += FormulaMeth2(Xn, B); // ����������� �n ��� ������ ����
			i++;
		}
		printf("  X* ~ %lf\n\n", Xn); // ���������� ����� �-��

		
		// ����� ������� (����� ��������)
		A = A1, B = B1, i = 1;
		printf("\n\n Newton's method: \n"); PR_L3
		printf("  || n  ||   Xn      ||   F(Xn)    ||   F'(Xn)   || -(F(Xn))/(F'(Xn)) ||"); PR_L3
		
		// ����������� �0 ��� ������ �������
		if ((F(A)) * (d2F(A)) > 0) Xn = A;
		else if ((F(B)) * (d2F(B)) > 0)	Xn = B;
		while (1)
		{
			printf("  || %2d || %-6lf  || %-10lf ||  %-9lf ||    %+-9lf      ||", i, Xn, F(Xn), d1F(Xn), FormulaMethNewt(Xn)); PR_L3
			if(fabs(FormulaMethNewt(Xn)) < eps) break; // �������� �� ���������� ���������
			Xn += FormulaMethNewt(Xn); // ����������� �n ��� ������ ��������
			i++;
		}
		printf("  X* ~ %lf, Number of iterations: %i \n\n", Xn, i); // ���������� ����� �-��

		// ����� ������ ��������
		A = A1, B = B1, i = 1;
		double Max = 0.0;
		
		for (double j = A; j < B; j = j + 0.00001) //����� ������������� �������� Գ(�)
		{
			if (fabs(d1Phi(j)) > Max)
				Max = d1Phi(j);
		}
		printf("\n Fixed-point iteration method: \n\n"); 
		//�������� �� �������
		if (Max > 1) { //�� ����� �(�)
			printf(" max|Phi'(x)| = %.2lf > 1 - ", Max);
			printf("Process is NOT convergent \n");
		}
		else if (Max < 1) { // ����� �(�)
			printf(" max|Phi'(x)| = %.2lf < 1 - ", Max);
			printf("Process is convergent \n"); PR_L2
			printf("  || n  ||   Xn     ||  Phi(Xn) ||"); PR_L2

			Xn = A; // X0
			while (1) {
				printf("  || %2d || %6lf || %6lf ||", i, Xn, Phi(Xn));  PR_L2
				if (fabs(Phi(Xn)-Xn) < eps) break; // �������� �� ���������� ���������
				Xn = Phi(Xn); // ����������� �n ��� ������ ������ ��������
				i++;
			}
			printf("  X* ~ %lf, Number of iterations: %i \n\n", Xn, i); // ���������� ����� �-��
		}
	}
	else printf("\n Error. The indicated limits are incorrect. \n"); // ����������� ��� ���������� ������ �������

	return 0;
}