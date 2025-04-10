#include "matrix.h"
#include <cstdlib>
#include <utility>

using namespace std;

matrix solveMatrix::gaussElimination(const matrix& lhsOrigin, const matrix& rhsOrigin){
	// catching error
	if (lhsOrigin.height != lhsOrigin.width) throw std::runtime_error("left hand side matrix is not square");
	if (lhsOrigin.height != rhsOrigin.height) throw std::runtime_error("left hand side rows and right hand side rows are different");
	if (rhsOrigin.width != 1) throw std::runtime_error("right hand side has more than 1 column");
	// copy the matrix to perform arithmatic
	matrix lhs(lhsOrigin);
	matrix rhs(rhsOrigin);
	// the index of rows will purely be followed this array
	int rowIndex[lhs.height];
	for(int i = 0; i < rhs.height; i++) rowIndex[i] = i;
	// perform arithmatic on the copy
	for	(int diagonal = 0; diagonal < lhs.height - 1; diagonal++){
		// case when the diagonal is 0
		if (std::abs(lhs.get(diagonal, diagonal)) < EPS) {
			for (int i = lhs.height - 1; i > diagonal; i--){
				if (lhs.get(i, diagonal) > EPS) {
					int temp = rowIndex[i];
					rowIndex[i] = rowIndex[diagonal];
					rowIndex[diagonal] = temp;
					break;
				}
			}
		}
		double divider = lhs.get(rowIndex[diagonal], diagonal);
		for (int row = diagonal + 1; row < lhs.height; row++){
			double multiplicator = lhs.get(rowIndex[row], diagonal);
			for (int col = diagonal; col < lhs.width; col++){
				double newCoef = lhs.get(rowIndex[row], col) - lhs.get(rowIndex[diagonal], col) / divider * multiplicator;
				lhs.set(rowIndex[row], col, newCoef);
			}
			double newCoef = rhs.get(rowIndex[row], 0) - rhs.get(rowIndex[diagonal], 0) / divider * multiplicator;
			rhs.set(rowIndex[row], 0, newCoef);
		}
	}
	// perform bottom to top subsitution
	for (int diagonal = lhs.height - 1; diagonal >=0; diagonal--){
		for (int col = lhs.width-1; col > diagonal; col--) {
			double newCoef = rhs.get(rowIndex[diagonal], 0) - lhs.get(rowIndex[diagonal], col) * rhs.get(rowIndex[col], 0);
			rhs.set(rowIndex[diagonal], 0, newCoef);
		}
		double newCoef = rhs.get(rowIndex[diagonal], 0) / lhs.get(rowIndex[diagonal], diagonal);
		rhs.set(rowIndex[diagonal], 0, newCoef);	
	}
	return rhs;
}

matrix solveMatrix::luDecomposition(const matrix& lhsOrigin, const matrix& rhsOrigin){
	// catching error:
	if (lhsOrigin.height != lhsOrigin.width) throw std::runtime_error("left hand side matrix is not square");
	if (lhsOrigin.height != rhsOrigin.height) throw std::runtime_error("left hand side rows and right hand side rows are different");
	if (rhsOrigin.width != 1) throw std::runtime_error("right hand side has more than 1 column");
	// copy the matrix to perform arithmatic
	matrix rhs(rhsOrigin);
	matrix lhs(lhsOrigin);
	// the index of rows will purely be followed this array
	int rowIndex[lhs.height];
	for(int i = 0; i < rhs.height; i++) rowIndex[i] = i;
	// perform arithmatic to split matrix A = LU
	for (int diagonal = 0; diagonal < lhs.height - 1; diagonal++){
		if (std::abs(lhs.get(diagonal, diagonal)) < EPS){
			bool swapped = false;
			for (int i = lhs.height - 1; i > diagonal; i--){
				if(std::abs(lhs.get(rowIndex[i], diagonal)) > EPS) {
					std::swap(rowIndex[i], rowIndex[diagonal]);
					swapped = true;
					break;
				}
			}
			if (!swapped) throw std::runtime_error("0 diagonal matrix");
		}
		for (int row = diagonal + 1; row < lhs.height; row++){
			double lowerMatrixCoef = lhs.get(rowIndex[row],diagonal) / lhs.get(rowIndex[diagonal], diagonal);
			lhs.set(rowIndex[row], diagonal, lowerMatrixCoef);
			for (int col = diagonal + 1; col < lhs.width; col++){
				double newCoef = - lhs.get(rowIndex[diagonal], col) * lowerMatrixCoef + lhs.get(rowIndex[row], col);
				lhs.set(rowIndex[row], col, newCoef);
			}
		}
	}
	// perform forward subsitution
	for (int row = 1; row < lhs.height; row++){
		for (int col = 0; col < row; col++){
			double newCoef = rhs.get(rowIndex[row], 0) - lhs.get(rowIndex[row], col) * rhs.get(rowIndex[col], 0);
			rhs.set(rowIndex[row], 0, newCoef);
		}
	}
	// perform backward subsitution
	for (int row = lhs.height-1; row >= 0; row--){
		for (int col = lhs.width-1; col > row; col--) {
			double newCoef = rhs.get(rowIndex[row], 0) - rhs.get(rowIndex[col], 0) * lhs.get(rowIndex[row], col);
			rhs.set(rowIndex[row], 0, newCoef);
		}
		double newCoef = rhs.get(rowIndex[row], 0) / lhs.get(rowIndex[row], row);
		rhs.set(rowIndex[row], 0, newCoef);
	}
	return rhs;
}

matrix::matrix(int row, int col): height(row), width(col) {
	this->arr = new double[row * col];
}

matrix::matrix(const matrix& other): height(other.height), width(other.width) {
	this->arr = new double[width * height];
	for(int i = 0; i < width * height; i++){
		arr[i] = other.arr[i];
	}
}

matrix::~matrix(){
	delete[] arr;
}

const int matrix::convertIndex(int row, int col) const {
	if (row >= this->height || col >= this->width)
		throw std::range_error("index out of bound");
	return row * this -> width + col;
}

const double matrix::get(int row, int col) const {
	return arr[convertIndex(row, col)];
}

void matrix::set(int row, int col, double value) {
	arr[this->convertIndex(row, col)] = value;
}

std::ostream& operator<< (std::ostream& os, const matrix& matrix){
	os << std::fixed << std::setprecision(2);
	for (int row = 0; row < matrix.height; row++){
		for (int col = 0; col < matrix.width; col++) {
			os << std::setw(7) << matrix.get(row, col) << " ";
		}
		os << "\n";
	}
	return os;
}
