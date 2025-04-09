#include "matrix.h"

int main() {
	matrix A(3,3);
	A.set(0,0, 4);
	A.set(0,1, 3);
	A.set(0,2, -1);

	A.set(1,0, -2);
	A.set(1,1, -4);
	A.set(1,2, 5);

	A.set(2,0, 1);
	A.set(2,1, 2);
	A.set(2,2, 6);

	matrix b(3,1);
	b.set(0,0, 8);
	b.set(1,0, 2);
	b.set(2,0, 9);

	matrix sol = solveMatrix::luDecomposition(A, b);

	std::cout << sol << std::endl;
	return 1;
}
