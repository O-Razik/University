#include <iostream>
#include <fstream>
#include <iomanip>

#define TAB 6
#define NSL 80
#define LINE(x, l) { printf("\n"); for (int i = 0; i < l; i++) { printf("%c", x);} printf("\n");}


void Scanf_SLAE(double A[5][3], double B[5][1], int n) {
    FILE* file = fopen("slae.txt", "r");
   
    for (int i = 0; i < n; i++) {
        fscanf(file, " %lf %lf %lf %lf", &A[i][0], &A[i][1], &A[i][2], &B[i][0]);
    }
    
    fclose(file);
}

// Функція для транспонування матриці A
void transpose_A(double A[5][3], double At[3][5], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            At[j][i] = A[i][j];
        }
    }
}

// Функція для транспонування матриці L
void transpose_L(double L[3][3], double Lt[3][3], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Lt[j][i] = L[i][j];
        }
    }
}

// Функція для знаходження матриці N
void computeN(double A[][3], double N[][3], int m, int n, int p) {
    double At[3][5];
    transpose_A(A, At, m, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            N[i][j] = 0;
            for (int k = 0; k < m; k++) {
                N[i][j] += At[i][k] * A[k][j];
            }
        }
    }
}

// Функція для знаходження матриці C
void computeC(double A[5][3], double B[5][1], double C[3][1], int m, int n, int p) {
    double At[3][5];
    transpose_A(A, At, m, n);
    for (int i = 0; i < 3; i++) {
        C[i][0] = At[i][0] * B[0][0] + At[i][1] * B[1][0] +
            At[i][2] * B[2][0] + At[i][3] * B[3][0] +
            At[i][4] * B[4][0];
    }
}

// Функція для знаходження матриці L
void computeL(double N[][3], double L[][3], int n) {
    for (int i = 0; i < n; i++)
    {
       for (int j = 0; j < n; j++)
       {
           L[i][j] = 0;
       }
    }
    L[0][0] = sqrt(N[0][0]);
    for (int i = 1; i < n; i++)
    {
        L[i][0] = N[i][0] / L[0][0];
    }
    L[1][1] = sqrt(N[1][1]-pow(L[1][0],2));
    L[2][1] = (N[2][1] - L[2][0] * L[1][0]) / L[1][1];
    L[2][2] = sqrt(N[2][2] - pow(L[2][0], 2) -pow(L[2][1], 2));
}

// Функція для знаходження матриці Y
void computeY(double L[][3], double C[][1], double Y[][1], int n) {
    for (int i = 0; i < n; i++) {
        Y[i][0] = C[i][0];
        for (int j = 0; j < i; j++) {
            Y[i][0] -= L[i][j] * Y[j][0];
        }
        Y[i][0] /= L[i][i];
    }
}

// Функція для знаходження матриці X
void computeX(double L[][3], double Y[][1], double X[][1], int n) {
    for (int i = n - 1; i >= 0; i--) {
        X[i][0] = Y[i][0];
        for (int j = i + 1; j < n; j++) {
            X[i][0] -= L[j][i] * X[j][0];
        }
        X[i][0] /= L[i][i];
    }
}

// Функція для знаходження похибки ε для кожного x, NX=C
void computeError_NXC(double N[][3], double C[][1], double X[][1], int m, int n, int p) {
    double NX[3][1], E[3][1];
    for (int i = 0; i < 3; i++) {
    	NX[i][0] = 0;
    	for (int k = 0; k < n; k++) {
    		NX[i][0] += N[i][k] * X[k][0];
    	}
    }
    std::cout << "\nMatrix NX:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << NX[i][0];
        std::cout << " || " << "\n";
    }
    std::cout << "\nMatrix C:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << C[i][0];
        std::cout << " || " << "\n";
    }
        
	for (int i = 0; i < m; i++) {
	    E[i][0] = C[i][0] - NX[i][0];
	}

    std::cout << "\nError matrix X in the equation NX=C :\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << E[i][0];
        std::cout << " || " << "\n";
    }
    
}

// Функція для знаходження похибки ε для кожного x, AX=C
void computeError(double A[][3], double B[][1], double X[][1], int m, int n, int p) {
    double AX[5][1], E[5][1];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            AX[i][j] = 0;
            for (int k = 0; k < n; k++) {
                AX[i][j] += A[i][k] * X[k][j];
            }
        }
    }

    std::cout << "\nMatrix AX:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << AX[i][0];
        std::cout << " || " << "\n";
    }
    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << B[i][0];
        std::cout << " || " << "\n";
    }

    for (int i = 0; i < m; i++) {
        E[i][0] = B[i][0] - AX[i][0];
    }
    std::cout << "\nError matrix X in the equation AX=B :\n";
    for (int i = 0; i < 5; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << E[i][0];
        std::cout << " || " << "\n";
    }
}

int main() {

    std::cout.precision(2);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout.setf(std::ios_base::showpoint);

    double A[5][3], B[5][1], X[5][1];
    Scanf_SLAE(A, B, 5);

	double N[3][3], C[3][1], L[3][3], Y[3][1];

    std::cout << "\nAX=B\n";
    std::cout << "\nMatrix A:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << " ||";
        for (int j = 0; j < 3; j++) {
            std::cout << std::setw(TAB) << A[i][j] << " ";
        }
        std::cout << " || " << "\n";
    }

    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << B[i][0];
        std::cout << " || " << "\n";
    }

    LINE('-', NSL)

    std::cout << "\nAX=B -> NX=C\n";
    std::cout << "\nN=A^(T)*A\n";

    // Обчислення матриці N
    computeN(A, N, 5, 3, 3);

    std::cout << "\nMatrix N:\n";
    for (int i = 0; i < 3; i++) {
		std::cout << " ||";
        for (int j = 0; j < 3; j++) {
            std::cout << std::setw(TAB) << N[i][j] << " ";
        }
        std::cout << " || " << "\n";
    }

    std::cout << "\nC=A^(T)*B\n";

    // Обчислення матриці C
    computeC(A, B, C, 5, 3, 1);

    std::cout << "\nMatrix C:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << C[i][0];
        std::cout << " || " << "\n";
    }

    LINE('-', NSL)

    std::cout << "\nNX=C -> LY=C\n";
    std::cout << "\nN=L^(T)*L\n";

    // Обчислення матриці L
    computeL(N, L, 3);

    std::cout << "\nMatrix L:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
    	for (int j = 0; j < 3; j++) {
            std::cout << std::setw(TAB) << L[i][j] << " ";
        }
        std::cout << " || " << "\n";
    }

    // Обчислення матриці Y
    computeY(L, C, Y, 3);
       
    std::cout << "\nMatrix Y:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << Y[i][0];
        std::cout << " || "<< "\n";
    }

    LINE('-', NSL)

	std::cout << "\nLY=C -> L^(T)*X=Y\n";

    // Обчислення матриці X
    computeX(L, Y, X, 3);

    std::cout << "\nMatrix X:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << " ||";
        std::cout << std::setw(TAB) << X[i][0];
        std::cout << " || " << "\n";
    }

    LINE('-', NSL)

    // Обчислення похибки ε для кожного x NX=C
    computeError_NXC(N, C, X, 5, 3, 3);

    LINE('-', NSL)

	// Обчислення похибки ε для кожного x AX=B
    computeError(A, B, X, 5, 3, 1);

    return 0;
}
