#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#define N 4
#define N1 8
#define N2 4
#define A(i) double A##i[(i+1)]
#define X(i) double X##i[(i+1)][(i+1)]
#define Y(i) double Y##i[(i+1)]

// зчитування інформації з файлу інформації
std::vector<std::pair<double, double>> fillPointsFromFile(const std::string& filename) {
	std::vector<std::pair<double, double>> points;
	std::ifstream file(filename);

	if (file.is_open()) {
		double x, y;
		while (file >> x >> y) {
			points.emplace_back(x, y);
		}

		file.close();
	}
	else {
		std::cout << "Failed to open file: " << filename << std::endl;
	}

	return points;
}

// Вивід таблиці x та y
void Print_TF(const std::vector<std::pair<double, double>>& points)
{
	std::cout << std::endl << " x |";
	for (int i = 0; i < points.size(); i++)
	{
		printf(" %+.3lf |", points[i].first);
	}
	std::cout << std::endl << " y |";
	for (int i = 0; i < points.size(); i++)
	{
		printf(" %+.3lf |", points[i].second);
	}
	std::cout << std::endl << std::endl;
}

// Сума n-порядку x
double sum_x (const std::vector<std::pair<double, double>>& points, int step)
{
	double sum = 0;
	for (int i = 0; i < points.size(); i++)
	{
		sum += pow(points[i].first, step);
	}
	return sum;
}

double sum_y_x(const std::vector<std::pair<double, double>>& points, int step)
{
	double sum = 0;
	for (int i = 0; i < points.size(); i++)
	{
		sum += pow(points[i].first, step) * points[i].second;
	}
	return sum;
}

// Лінійний апроксимаційний поліном
void Polynomial_1(const std::vector<std::pair<double, double>>& points){

	int n = points.size() - 1;

	double SumX[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		SumX[i] = sum_x(points, i + 1);
	}

	double SumY[4] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		SumY[i] = sum_y_x(points, i);
	}
	int m = -1;
	A(1); X(1); Y(1);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if ((i == 0.0) && (j == 0.0)) X1[i][j] = n+1;
			else
			{
				X1[i][j] = SumX[m+j];
			}
		
		}
		Y1[i] = SumY[i];
		m++;
	}

	printf(" / %+.3lf*a0%+.3lf*a1=%+.3lf\n", X1[0][0], X1[0][1], Y1[0]);
	printf(" \\ %+.3lf*a0%+.3lf*a1=%+.3lf\n", X1[1][0], X1[1][1], Y1[1]);
	double detX, detXi[2], X[2], Xi[2][2][2];

	printf("\nCramer's method: \n");
	printf("\nOriginal matrix X: \n");
	for (int i = 0; i < 2; i++) {
		printf(" ||  %+.3lf %+.3lf  ||\n", X1[i][0], X1[i][1]);
	}

	for (int k = 0; k < 2; k++)
	{
		printf("\nMatrix X%d: \n", k + 1);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (j == k) Xi[k][i][j] = Y1[i];
				else Xi[k][i][j] = X1[i][j];
			}
			printf(" ||  %+.3lf %+.3lf  ||\n", Xi[k][i][0], Xi[k][i][1]);
		}
		printf("\n |X%d| = %+lf \n", k + 1, (Xi[k][0][0]*Xi[k][1][1] - Xi[k][0][1] * Xi[k][1][0]));
		A1[k] = (Xi[k][0][0] * Xi[k][1][1] - Xi[k][0][1] * Xi[k][1][0]) / (X1[0][0] * X1[1][1] - X1[0][1] * X1[1][0]);
		printf("  a%d = %+.3lf \n", k, A1[k]);
	}

	// Вивід відповіді
	printf("\n a0 = %+.3lf,  a1 = %+.3lf \n", A1[0], A1[1]);

	printf("\n P1=%.3lf%+.3lfx\n\n", A1[0], A1[1]);
	printf(" %+.3lf%+.3lf*(%+.3lf)=%+.3lf\n", A1[0], A1[1], points[1].first, (A1[0] + points[1].first * A1[1]));
	printf(" %+.3lf%+.3lf*(%+.3lf)=%+.3lf\n\n", A1[0], A1[1], points[5].first, (A1[0] + points[5].first * A1[1]));
}

// Квадратичний апроксимаційний поліном
void Polynomial_2(const std::vector<std::pair<double, double>>& points) {

	int n = points.size() - 1;

	double SumX[6] = { 0 };
	for (int i = 0; i < 6; i++)
	{
		SumX[i] = sum_x(points, i + 1);
	}

	double SumY[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		SumY[i] = sum_y_x(points, i);
	}
	int m = -1;
	A(2); X(2); Y(2);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i == 0.0) && (j == 0.0)) X2[i][j] = n + 1;
			else
			{
				X2[i][j] = SumX[m + j];
			}

		}
		Y2[i] = SumY[i];
		m++;
	}

	printf(" / %+.3lf*a0%+.3lf*a1%+.3lf*a2=%+.3lf\n", X2[0][0], X2[0][1], X2[0][2], Y2[0]);
	printf(" | %+.3lf*a0%+.3lf*a1%+.3lf*a2=%+.3lf\n", X2[1][0], X2[1][1], X2[1][2], Y2[1]);
	printf(" \\ %+.3lf*a0%+.3lf*a1%+.3lf*a2=%+.3lf\n", X2[2][0], X2[2][1], X2[2][2], Y2[2]);

	double detX, detXi[3], X[3], Xi[3][3][3];

	printf("\nCramer's method: \n");
	printf("\nOriginal matrix X: \n");
	for (int i = 0; i < 3; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", X2[i][0], X2[i][1], X2[i][2]);
	}

	for (int k = 0; k < 3; k++)
	{
		printf("\nMatrix X%d: \n", k + 1);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j == k) Xi[k][i][j] = Y2[i];
				else Xi[k][i][j] = X2[i][j];
			}
			printf(" ||  %+.3lf %+.3lf %+.3lf  ||\n", Xi[k][i][0], Xi[k][i][1], Xi[k][i][2]);
		}

		detXi[k] = (Xi[k][0][0] * Xi[k][1][1] * Xi[k][2][2]
			+ Xi[k][0][1] * Xi[k][1][2] * Xi[k][2][0]
			+ Xi[k][0][2] * Xi[k][1][0] * Xi[k][2][1]
			- Xi[k][0][2] * Xi[k][1][1] * Xi[k][2][0]
			- Xi[k][0][0] * Xi[k][1][2] * Xi[k][2][1]
			- Xi[k][0][1] * Xi[k][1][0] * Xi[k][2][2]);

		detX = (X2[0][0] * X2[1][1] * X2[2][2]
			+ X2[0][1] * X2[1][2] * X2[2][0]
			+ X2[0][2] * X2[1][0] * X2[2][1]
			- X2[0][2] * X2[1][1] * X2[2][0]
			- X2[0][0] * X2[1][2] * X2[2][1]
			- X2[0][1] * X2[1][0] * X2[2][2]);

		printf("\n |X%d| = %+lf \n", k + 1, detXi[k]);
		A2[k] = detXi[k] / detX;
		printf("  a%d = %+.3lf \n", k, A2[k]);
	}

	// Вивід відповіді
	printf("\n a0 = %+.3lf,  a1 = %+.3lf,  a2 = %+.3lf \n", A2[0], A2[1], A2[2]);

	printf("\n P2=%.3lf%+.3lfx%+.3lfx^2\n\n", A2[0], A2[1], A2[2]);
	printf(" %+.3lf%+.3lf*(%+.3lf)%+.3lf*(%+.3lf)^2=%+.3lf\n", A2[0], A2[1], points[1].first, A2[2], points[1].first,
		(A2[0] + points[1].first * A2[1] + A2[2]*pow(points[1].first, 2)));
	printf(" %+.3lf%+.3lf*(%+.3lf)%+.3lf*(%+.3lf)^2=%+.3lf\n\n", A2[0], A2[1], points[5].first, A2[2], points[5].first,
		(A2[0] + points[5].first * A2[1] + A2[2] * pow(points[1].first, 2)));
}

// Кубічний апроксимаційний поліном
void Polynomial_3(const std::vector<std::pair<double, double>>& points){

	int n = points.size() - 1;

	double SumX[N1] = { 0 };
	for (int i = 0; i < N1; i++)
	{
		SumX[i] = sum_x(points, i + 1);
	}

	double SumY[4] = { 0 };
	for (int i = 0; i < N2; i++)
	{
		SumY[i] = sum_y_x(points, i);
	}

	A(3); X(3); Y(3);
	int m = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((i == 0.0) && (j == 0.0)) X3[i][j] = n + 1;
			else
			{
				X3[i][j] = SumX[m + j];
			}
		}
		Y3[i] = SumY[i];
		m++;
	}

	printf(" / %+.3lf*a0%+.3lf*a1%+.3lf*a2%+.3lf*a3=%+.3lf\n", X3[0][0], X3[0][1], X3[0][2], X3[0][3], Y3[0]);
	printf(" | %+.3lf*a0%+.3lf*a1%+.3lf*a2%+.3lf*a3=%+.3lf\n", X3[1][0], X3[1][1], X3[1][2], X3[1][3], Y3[1]);
	printf(" | %+.3lf*a0%+.3lf*a1%+.3lf*a2%+.3lf*a3=%+.3lf\n", X3[2][0], X3[2][1], X3[2][2], X3[2][3], Y3[2]);
	printf(" \\ %+.3lf*a0%+.3lf*a1%+.3lf*a2%+.3lf*a3=%+.3lf\n", X3[3][0], X3[3][1], X3[3][2], X3[3][3], Y3[3]);

	float X3_1[N][N + 1], max = 0.0, Xm[N][N + 1];
	int index_max = 0;
	float ratio, error, sum;


	printf("\nGaussian's method: \n");
	printf("\nOriginal matrix X`: \n");
	for (int i = 0; i < 4; i++) {
		printf(" ||  %+.3lf %+.3lf %+.3lf %+.3lf %+.3lf ||\n", X3[i][0], X3[i][1], X3[i][2], X3[i][3], Y3[i]);
	}
	printf("\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			X3_1[i][j] = X3[i][j];
		}
		X3_1[i][N] = Y3[i];
	}

	for (int i = 0; i < N - 1; i++) {
		index_max = i;
		for (int j = i + 1; j < N; j++) {
			if (fabs(X3_1[j][i]) > fabs(X3_1[index_max][i])) {
				index_max = j;
			}
		}

		if (index_max != i) {
			for (int k = 0; k <= N; k++) {
				double temp = X3_1[i][k];
				X3_1[i][k] = X3_1[index_max][k];
				X3_1[index_max][k] = temp;
			}
		}

		for (int j = i + 1; j < N; j++) {
			ratio = X3_1[j][i] / X3_1[i][i];
			for (int k = i; k <= N; k++) {
				X3_1[j][k] -= ratio * X3_1[i][k];
			}
		}

		printf("Matrix X after iteration %d:\n", i + 1);
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= N; k++) {
				printf(" %+.3lf", X3_1[j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (int i = N - 1; i >= 0; i--) {
		sum = 0;
		for (int j = i + 1; j < N; j++) {
			sum += X3_1[i][j] * A3[j];
		}
		A3[i] = (X3_1[i][N] - sum) / X3_1[i][i];
	}

	// Вивід відповіді
	printf(" a0 = %+.3lf, a1 = %+.3lf, a2 = %+.3lf, a3 = %+.3lf\n", A3[0], A3[1], A3[2], A3[3]);
	printf("\n P3=%.3lf%+.3lfx%+.3lfx^2%+.3lfx^3\n\n", A3[0], A3[1], A3[2], A3[3]);

	printf(" %+.3lf%+.3lf*(%+.3lf)%+.3lf*(%+.3lf)^2%+.3lf*(%+.3lf)^3=%+.3lf\n",
		A3[0], A3[1], points[1].first, A3[2], points[1].first, A3[3], points[1].first,
		(A3[0] + points[1].first * A3[1] + A3[2] * pow(points[1].first, 2) + A3[3] * pow(points[1].first, 3)));
	printf(" %+.3lf%+.3lf*(%+.3lf)%+.3lf*(%+.3lf)^2%+.3lf*(%+.3lf)^3=%+.3lf\n\n",
		A3[0], A3[1], points[5].first, A3[2], points[5].first, A3[3], points[5].first,
		(A3[0] + points[5].first * A3[1] + A3[2] * pow(points[5].first, 2) + A3[3] * pow(points[5].first, 3)));
}


int main()
{
	std::vector<std::pair<double, double>> points = fillPointsFromFile("points.txt");
	Print_TF(points);

	std::cout << "-------------------------------------------------------------------\n\n";
	Polynomial_1(points);
	std::cout << "-------------------------------------------------------------------\n\n";
	Polynomial_2(points);
	std::cout << "\n-------------------------------------------------------------------\n\n";
	Polynomial_3(points);
	std::cout << "-------------------------------------------------------------------\n\n";

	return 0;

}