#include <iostream>
#include <math.h>

#define MAX 50
#define N 4
#define NSL 80
#define LINE(x, l) { printf("\n"); for (int i = 0; i < l; i++) { printf("%c", x);} printf("\n");}

// Зчитування інформації з файлу інформації
void ScanfMatrix(const char* filename, float A[N][N], float B[N]);
// Вивід СЛАР та матриць А і В
void PrinfSLAE(float A[N][N], float B[N]);
// Знаходження матриць Alpha i Beta
void AlphaBetaFind(float A[N][N], float B[N], float alpha[N][N], float beta[N]);
// Перевірка на збіжність
bool CheckConvergency(float alpha[N][N]);
// Множення матриць Alpha і X попередньої ітеріції
void MatrixMultiplAlphaX(float alpha[N][N], float x[N], float Result[N]);
// Метод простої ітерації (Якобі)
int Simple_Iteration_Method(float alpha[N][N], float beta[N]);
// Метод Зейделя
int Seidel_Method(float alpha[N][N], float beta[N]);

// Похибка
float ep = 0.001;

int main() {

	float A[N][N], B[N];
	// зчитування інформації з файлу інформації
	ScanfMatrix("matrix.txt", A, B);
	// Вивід СЛАР та матриць А і В
	PrinfSLAE(A, B);
	float alpha[N][N], beta[N];
	// Знаходження матриць Alpha i Beta
	AlphaBetaFind(A, B, alpha, beta);
	int k_SIM, k_SM;
	LINE('-', NSL)
	
	// Перевірка на збіжність
	if (CheckConvergency(alpha)) {
		LINE('-', NSL)
		// Метод простої ітерації (Якобі)
		k_SIM = Simple_Iteration_Method(alpha,beta);
		LINE('-', NSL)
		// Метод Зейделя
		k_SM = Seidel_Method(alpha, beta);
		LINE('-', NSL)

		// Порівняння методів
		printf("\nSimple iteration method: %d iterations\n", k_SIM);
		printf("Seidel's method: %d iterations\n", k_SM);
		printf("%s has %d less iterations then %s\n",
			(k_SIM < k_SM)?("Simple iteration method"):("Seidel's method"),
			((k_SIM - k_SM)*((k_SIM < k_SM)?(-1):(1))),
			(k_SIM > k_SM) ? ("simple iteration method") : ("Seidel's method"));
	}
	LINE('-', NSL)
	return 0;
}

// Зчитування інформації з файлу інформації
void ScanfMatrix(const char* filename, float A[N][N], float B[N]) {


	FILE* values = fopen(filename, "r");
	char string[MAX];
	for (int i = 0; i < N; i++)
	{
		fscanf(values, "%f %f %f %f %f", &A[i][0], &A[i][1], &A[i][2], &A[i][3], &B[i]);
	}

}

// Вивід СЛАР та матриць А і В
void PrinfSLAE(float A[N][N], float B[N]) {

	printf(" .-\n");
	printf(" | %-4.2f*x1%+-4.2f*x2%+-4.2f*x3%+-4.2f*x4 = %+-4.2f\n",
		A[0][0], A[0][1], A[0][2], A[0][3], B[0]);
	printf(" { %-4.2f*x1%+-4.2f*x2%+-4.2f*x3%+-4.2f*x4 = %+-4.2f\n",
		A[1][0], A[1][1], A[1][2], A[1][3], B[1]);
	printf(" | %-4.2f*x1%+-4.2f*x2%+-4.2f*x3%+-4.2f*x4 = %+-4.2f\n",
		A[2][0], A[2][1], A[2][2], A[2][3], B[2]);
	printf(" | %-4.2f*x1%+-4.2f*x2%+-4.2f*x3%+-4.2f*x4 = %+-4.2f\n",
		A[3][0], A[3][1], A[3][2], A[3][3], B[3]);
	printf(" `-\n");

	for (int i = 0; i < N; i++) {
		printf(" ||  %+-6.2f %+-6.2f %+-6.2f %+-6.2f  ||\t|| %+-6.2f ||\n",
			A[i][0], A[i][1], A[i][2], A[i][3], B[i]);
	}
}

// Знаходження матриць Alpha i Beta
void AlphaBetaFind(float A[N][N], float B[N], float alpha[N][N], float beta[N]) {

	printf("\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == i) {
				alpha[i][j] = 0;
			}
			else {
				alpha[i][j] = (-1) * A[i][j] / A[i][i];
			}
		}
		beta[i] = B[i] / A[i][i];
	}

	printf(" .-\n");
	printf(" | x1 = %-5.3f%-6.3f*x2%+-6.3f*x3%+-6.3f*x4\n",
		beta[0], alpha[0][1], alpha[0][2], alpha[0][3]);
	printf(" { x2 = %-5.3f%+-6.3f*x1%+-6.3f*x3%+-6.3f*x4\n",
		beta[1], alpha[1][0], alpha[1][2], alpha[1][3]);
	printf(" | x3 = %-5.3f%+-6.3f*x1%+-6.3f*x2%+-6.3f*x4\n",
		beta[2], alpha[2][0], alpha[2][1], alpha[2][3]);
	printf(" | x4 = %-5.3f%+-6.3f*x1%+-6.3f*x2%+-6.3f*x3\n",
		beta[3], alpha[3][0], alpha[3][1], alpha[3][2]);
	printf(" `-\n");

	for (int i = 0; i < N; i++) {
		printf(" ||  %+-6.3f %+-6.3f %+-6.3f %+-6.3f  ||\t|| %+-6.3f ||\n",
			alpha[i][0], alpha[i][1], alpha[i][2], alpha[i][3], beta[i]);
	}

}

// Перевірка на збіжність
bool CheckConvergency(float alpha[N][N]) {
	bool check = 1;
	float sum = 0;
	printf("\n max{ ");
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += fabsf(alpha[i][j]);
		}
		if (!(sum < 1)) {
			check = 0;
		}
		printf("%.3f", sum);
		if (i + 1 != N) {
			printf(", ");
		}
	}
	printf(" } %c 1", check ? ('<') : ('>'));
	printf("\n The sufficient condition of convergence is%s satisfied\n", check ? ("") : ("not"));
	return check;
}

// Множення матриць Alpha і X попередньої ітеріції
void MatrixMultiplAlphaX(float alpha[N][N], float x[N], float Result[N]) {
	for (int i = 0; i < N; i++) {
		Result[i] = 0;
		for (int j = 0; j < N; j++) {
			Result[i] += alpha[i][j] * x[j];
		}
	}
}
// Метод простої ітерації (Якобі)
int Simple_Iteration_Method(float alpha[N][N], float beta[N]) {
	float X[N]{}, Xbefore[N]{}, alphaX[N], max_modX = 0;
	int k = 0;

	printf("\nSimple iteration method:\n");
	LINE('-', 66)
	printf("|  k  |  x1\t|  x2\t  |  x3\t    |  x4     | |X^(k)-X^(k-1)|  |");
	LINE('-', 66)

	for (int i = 0; i < N; i++) {
		X[i] = beta[i];
		Xbefore[i] = beta[i];
	}

	printf("|  %2d | %+-5.4f | %+-5.4f | %+-5.4f | %+-5.4f | %5c\t\t | ",
		k, X[0], X[1], X[2], X[3], '-'); LINE('-', 66)

	k++;
	while (1) {
		MatrixMultiplAlphaX(alpha, X, alphaX);
		
		for (int i = 0; i < N; i++) {
			X[i] = beta[i] + alphaX[i];
			if ( i == 0 || max_modX < fabs(X[i]-Xbefore[i]))
				max_modX = fabs(X[i] - Xbefore[i]);
		}

		// вивід ітерації
		printf("|  %2d | %+-5.4f | %+-5.4f | %+-5.4f | %+-5.4f | %+-7.4f\t\t |",
			k, X[0], X[1], X[2], X[3], max_modX); LINE('-', 66)
		
		
		if (max_modX < ep) break; // припинення ітераційного процесу
		k++;
		for (int i = 0; i < N; i++) {
			Xbefore[i] = X[i];
		}
	}

	// Вивід матриці X
	printf("\nMatrix X:\n");
	for (int i = 0; i < N; i++) {
		printf(" || %+.3f ||\n", X[i]);
	}

	// Вивід відповіді
	printf("\n");
	for (int i = 0; i < N; i++) {
		printf("x%d = %.3f", i+1, X[i]);
		if (i+1 != N) {
			printf(", ");
		}
		else {
			printf(".\n");
		}
	}
	return k;
}
// Метод Зейделя
int Seidel_Method(float alpha[N][N], float beta[N]) {
	float X[N]{}, Xbefore[N]{}, max_modX = 0;
	int k = 0;

	printf("\nSeidel's method:\n");
	LINE('-', 66)
		printf("|  k  |  x1\t|  x2\t  |  x3\t    |  x4     | |X^(k)-X^(k-1)|  |");
	LINE('-', 66)

	for (int i = 0; i < N; i++) {
		X[i] = beta[i];
		Xbefore[i] = beta[i];
	}

	printf("|  %2d | %+-5.4f | %+-5.4f | %+-5.4f | %+-5.4f | %5c\t\t | ",
		k, X[0], X[1], X[2], X[3], '-'); LINE('-', 66)

	k++;

	while (1) {
		for (int i = 0; i < N; i++) {
			X[i] = beta[i];
			for (int j = 0; j < N; j++)
			{
				if (j != i) {
					X[i] += alpha[i][j] * X[j];
				}
			}
			if (i == 0 || max_modX < fabs(X[i] - Xbefore[i]))
				max_modX = fabs(X[i] - Xbefore[i]);
		}

		// вивід ітерації
		printf("|  %2d | %+-5.4f | %+-5.4f | %+-5.4f | %+-5.4f | %+-7.4f\t\t |", 
			k, X[0], X[1], X[2], X[3], max_modX); LINE('-', 66)

		if (max_modX < ep) break; // припинення ітераційного процесу
		k++;	
		for (int i = 0; i < N; i++) {
			Xbefore[i] = X[i];
		}
	}

	// Вивід матриці X
	printf("\nMatrix X:\n");
	for (int i = 0; i < N; i++) {
		printf(" || %+.3f ||\n", X[i]);
	}

	// Вивід відповіді
	printf("\n");
	for (int i = 0; i < N; i++) {
		printf("x%d = %.3f", i + 1, X[i]);
		if (i + 1 != N) {
			printf(", ");
		}
		else {
			printf(".\n");
		}
	}
	return k;
}