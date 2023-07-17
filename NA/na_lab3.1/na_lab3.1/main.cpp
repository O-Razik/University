#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50
#define N 3

// Матриці
double A[N][N], B[N];

void ScanfMatrix(const char* filename);
void PrinfSLAE(double matrixA[N][N], double matrixB[N]);
double det(double matrix[N][N]);
void CramerMethod();
void MatrixMethod();
void GaussianMetod();
void LU_Method();
void inv_A(double inverseA[N][N]);
void LU_Matrixs(float L[N][N], float U[N][N]);

int main() {
	ScanfMatrix("matrix1.txt"); //зчитування інформації з файлу інформації
	PrinfSLAE(A,B);

	//Перевірка на невиродженість матриці A 
	if (det(A) != 0) {
		printf("\n detA = %lf \n detA != 0 \n\n", det(A));
		MatrixMethod(); //Метод оберненої матриці
		printf("\n=====================================================================\n");
		CramerMethod(); //метод Крамера
	} else if (!det(A)) {
		printf("\n det(A) = 0.\n Methods can't be used. \n");
	}

	LU_Method();
	GaussianMetod();
	return 0;
}

// зчитування інформації з файлу інформації
void ScanfMatrix(const char* filename) {
	FILE* values = fopen(filename, "r");
	char string[MAX];
	for (int i = 0; i < N; i++)
	{
		fscanf(values, "%lf %lf %lf %lf", &A[i][0], &A[i][1], &A[i][2], &B[i]);
	}
}

// Вивід СЛАР та матриць А і В
void PrinfSLAE(double matrixA[N][N], double matrixB[N]) {
	printf(" .-\n");
	printf(" | %+.2lf*x1%+.2lf*x2%+.2lf*x3 = %+.2lf\n", matrixA[0][0], matrixA[0][1], matrixA[0][2], matrixB[0]);
	printf(" { %+.2lf*x1%+.2lf*x2%+.2lf*x3 = %+.2lf\n", matrixA[1][0], matrixA[1][1], matrixA[1][2], matrixB[1]);
	printf(" | %+.2lf*x1%+.2lf*x2%+.2lf*x3 = %+.2lf\n", matrixA[2][0], matrixA[2][1], matrixA[2][2], matrixB[2]);
	printf(" `-\n");

	for (int i = 0; i < N; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\t|| %+.3lf ||\n", matrixA[i][0], matrixA[i][1], matrixA[i][2], matrixB[i]);
	}
}

// Визначник матриці
double det(double matrix[N][N]) {
	double det = (matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][0] * matrix[1][2] * matrix[2][1]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]);
	return det;
}

//Метод Крамера
void CramerMethod() {

	double detA, detAi[N], X[N], Ai[N][N][N];

	printf(" Cramer's method: \n");
	printf("\n Original matrix A: \n");
	for (int i = 0; i < N; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", A[i][0], A[i][1], A[i][2]);
	}

	for (int k = 0; k < N; k++)
	{
		printf("\nMatrix A%d: \n", k+1);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == k) Ai[k][i][j] = B[i];
				else Ai[k][i][j] = A[i][j];
			}
			printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", Ai[k][i][0], Ai[k][i][1], Ai[k][i][2]);
		}
		printf("\n |A%d| = %lf \n", k + 1, det(Ai[k]));
		X[k] = det(Ai[k]) / det(A);
		printf("  X%d = %lf \n", k + 1, X[k]);
	}

	// Вивід відповіді
	printf("\n X1 = %lf,  X2 = %lf,  X3 = %lf \n", X[0], X[1], X[2]);

}

void inv_A(double inverseA[N][N]) {
	double adj_A[N][N];
	int i, j, ii, jj;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			// Знаходимо мінор елемента матриці
			int sign = ((i + j) % 2 == 0) ? 1 : -1;
			double M[N - 1][N - 1];
			for (ii = 0; ii < N - 1; ii++) {
				for (jj = 0; jj < N - 1; jj++) {
					int row = (ii < i) ? ii : ii + 1;
					int col = (jj < j) ? jj : jj + 1;
					M[ii][jj] = A[row][col];
				}
			}
			double M_det = M[0][0]*M[1][1] - M[0][1] * M[1][0];
			adj_A[i][j] = sign * M_det; // Заповнюємо елемент матриці алгебраїчних доповнень
			printf("\n A%d%d = (-1)^(%d+%d) * | %+lf  %+lf |\n\t\t    | %+lf  %+lf | = %+lf\n",
				i+1, j+1, i+1, j+1, M[0][0], M[0][1], M[1][0], M[1][1], adj_A[i][j]);
			
		}
	}

	printf("\n Matrix of arithmetic additions of matrix A: \n");
	for (int i = 0; i < N; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", adj_A[i][0], adj_A[i][1], adj_A[i][2]);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			inverseA[i][j] = adj_A[j][i]/det(A); // Заповнюємо елемент оберненої матриці
		}
	}

	printf("\n Matrix A^(-1): \n");
	for (int i = 0; i < N; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", inverseA[i][0], inverseA[i][1], inverseA[i][2]);
	}

}

// Метод оберненої матриці
void MatrixMethod() {
	printf(" Matrix method: \n");
	printf("\n Original matrix A: \n");
	for (int i = 0; i < N; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", A[i][0], A[i][1], A[i][2]);
	}

	double invA[N][N], X[N] = { 0 };
	inv_A(invA);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			X[i] += invA[i][j]*B[j];
		}		
	}
	
	// Вивід відповіді
	printf("\n ||  %+.3lf %+.3lf %+.3lf  ||     ||  %+.3lf  ||   ||  %+.3lf  ||\n", invA[0][0], invA[0][1], invA[0][2], B[0], X[0]);
	printf(" ||  %+.3lf %+.3lf %+.3lf  ||  *  ||  %+.3lf  || = ||  %+.3lf  ||\n", invA[1][0], invA[1][1], invA[1][2], B[1], X[1]);
	printf(" ||  %+.3lf %+.3lf %+.3lf  ||     ||  %+.3lf  ||   ||  %+.3lf  ||\n", invA[2][0], invA[2][1], invA[2][2], B[2], X[2]);

	printf("\n X1 = %lf,  X2 = %lf,  X3 = %lf \n", X[0], X[1], X[2]);

}

void GaussianMetod() {
	float A1[N][N + 1], max = 0.0, Am[N][N+1], x[N];
	int index_max = 0;
	float ratio, error, sum;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A1[i][j] = A[i][j];
		}
		A1[i][N] = B[i];
	}

	// Прямий хід методу Гауса з вибором головного елемента
	for (int i = 0; i < N - 1; i++)
	{
		// Знаходження максимального за модулем елемента у стовпці i
		index_max = i;
		for (int j = i + 1; j < N; j++)
		{
			if (fabs(A1[j][i]) > fabs(A1[index_max][i]))
			{
				max = j;
			}
		}

		// Перестановка рядків i та max
		if (max != i)
		{
			for (int k = 0; k <= N; k++)
			{
				double temp = A1[i][k];
				A1[i][k] = A1[index_max][k];
				A1[index_max][k] = temp;
			}
		}

		// Виконання елімінації Гауса
		for (int j = i + 1; j < N; j++)
		{
			ratio = A1[j][i] / A1[i][i];
			for (int k = i; k <= N; k++)
			{
				A1[j][k] -= ratio * A1[i][k];
			}
		}

		// Виведення матриці A після кожної ітерації
		printf("Матриця A після %d-ої ітерації:\n", i + 1);
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k <= N; k++)
			{
				printf("%.2f ", A1[j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	// Обернений хід методу Гауса
	for (int i = N - 1; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < N; j++)
		{
			sum += A1[i][j] * x[j];
		}
		x[i] = (A1[i][N] - sum) / A1[i][i];
	}
	// Вивід відповіді
	printf("\n X1 = %lf,  X2 = %lf,  X3 = %lf \n", x[0], x[1], x[2]);

}


void LU_Matrixs(float L[N][N], float U[N][N]) {
	float sum = 0.0;
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == 0) {
				L[i][j] = A[i][j];
				printf("L%d%d = A%d%d = %+f\n", i + 1, j + 1, i + 1, j + 1, A[i][j]);
			}
			else if (j > i) {
				L[i][j] = 0;
				printf("L%d%d = %f\n", i + 1, j + 1, L[i][j]);
			}
			else {
				sum = 0.0;
				printf("L%d%d = A%d%d - (", i + 1, j + 1, i + 1, j + 1);
				for (int k = 0; k < j; k++) {
					printf("(L%d%d * U%d%d)", i + 1, k + 1, k + 1, j + 1);
					if (k + 1 != j) {
						printf("+");
					}
					sum += L[i][k] * U[k][j];
				}
				L[i][j] = A[i][j] - sum;
				printf(") = %f - %c%f%c = %f\n", A[i][j], (sum < 0) ? ('(') : ('\ '), sum, (sum < 0) ? (')') : ('\ '), L[i][j]);
			}

			if (j < i) {
				U[i][j] = 0;
				printf("U%d%d = 0\n", i + 1, j + 1);
			}
			else {
				sum = 0.0;
				printf("U%d%d =%sA%d%d%s", i + 1, j + 1, (i != 0) ? (" (") : (" "), i + 1, j + 1, (i != 0) ? (" - (") : (" "));
				for (int k = 0; k < i; k++) {
					 printf("(L%d%d * U%d%d)", i + 1, k + 1, k + 1, j + 1);
					if (k + 1 != i) {
						printf("+");
					}
					sum += L[i][k] * U[k][j];
				}
				printf("%s/ L%d%d = ", (i != 0) ? (") ") : (""), i+1, i+1);
				U[i][j] = (A[i][j] - sum) / L[i][i];
				if (i != 0) printf("(%f - %s%f%s) / %s%f%s = %f\n",
					A[i][j], (sum < 0) ? ("(") : (""), sum, (sum < 0) ? (")") : (""),
					(L[i][i] < 0) ? ("(") : (""), L[i][i], (L[i][i] < 0) ? (")") : (""), U[i][j]);
				else printf("%f / %s%f%s = %f\n",
					A[i][j], (L[i][i] < 0) ? ("(") : (""), L[i][i], (L[i][i] < 0) ? (")") : (""), U[i][j]);
			}
		}
		printf("\n");
	}

	printf("\nMatrix L:\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%f\t", L[i][j]);
		}
		printf("\n");
	}

	printf("\nMatrix U:\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%f\t", U[i][j]);
		}
		printf("\n");
	}
}

void LU_Method() {
	float L[N][N], U[N][N], Y[N], X[N], sum = 0.0;
	printf("\nAX=B\nA = LU\nLUX=B\n");
	LU_Matrixs(L, U);
	printf("\nUX->Y\nLY=B\n");

	for (int i = 0; i < N; i++) {
		printf("\nY%d = %sB%d%s", i + 1, (i != 0) ? (" (") : (" "), i + 1, (i != 0) ? (" - (") : (" "));
		sum = 0.0;
		for (int k = 0; k < i; k++) {
			printf("(L%d%d * Y%d)", i + 1, k + 1, k + 1);
			if (k + 1 != i) {
				printf("+");
			}
			sum += L[i][k] * Y[k];
		}
		printf("%s/ L%d%d = ", (i != 0) ? (") ") : (""), i + 1, i + 1);
		Y[i] = (B[i] - sum) / L[i][i];
		if (i != 0) printf("(%f - %s%f%s) / %s%f%s = %f",
			B[i], (sum < 0) ? ("(") : (""), sum, (sum < 0) ? (")") : (""),
			(L[i][i] < 0) ? ("(") : (""), L[i][i], (L[i][i] < 0) ? (")") : (""), Y[i]);
		else printf("%f / %s%f%s = %f",
			B[i], (L[i][i] < 0) ? ("(") : (""), L[i][i], (L[i][i] < 0) ? (")") : (""), Y[i]);
	}

	printf("\n\nMatrix Y:\n");
	for (int i = 0; i < N; i++) {
		printf("%f\n", Y[i]);
	}
	printf("\nUX=Y\n");

	X[N - 1] = Y[N - 1];
	printf("X%d = Y%d = %+f\n", N, N, X[N-1]);
	for (int i = N - 1; i >= 0; i--) {
		printf("\nX%d = %sY%d%s", i + 1, (i != N - 1) ? (" (") : (" "), i + 1, (i != N - 1) ? (" - (") : (" "));
		sum = 0.0;
		for (int k = i + 1; k < N; k++) {
			printf("(U%d%d * X%d)", i + 1, k + 1, k + 1);
			if (k + 1 != N) {
				printf("+");
			}
			sum += U[i][k] * X[k];
		}
		printf("%s) / U%d%d = ", (i != N - 1) ? (") ") : (""), i + 1, i + 1);
		X[i] = (Y[i] - sum) / U[i][i];
		printf("(%f - %s%f%s) / %s%f%s = %f\n",
			Y[i], (sum < 0) ? ("(") : (""), sum, (sum < 0) ? (")") : (""),
			(L[i][i] < 0) ? ("(") : (""), L[i][i], (L[i][i] < 0) ? (")") : (""), X[i]);
	}

	printf("\n\nMatrix X:\n");
	for (int i = 0; i < N; i++) {
		printf("%f\n", X[i]);
	}

	// Вивід відповіді
	printf("\n X1 = %lf,  X2 = %lf,  X3 = %lf \n", X[0], X[1], X[2]);
}