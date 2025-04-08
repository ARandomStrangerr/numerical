#ifndef MATRIX
#define MATRIX

#include <ostream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <iomanip>

#define EPS 1e-8

class matrix;

namespace solveMatrix {
	/**
	 * solving matrix using Gaussian Elimination
	 * @params:
	 * 	const matrix* - left hand side
	 * 	const matrix* - right hand side
	 * @return:
	 * 	matrix* - x in Ax=b
	 */
	matrix gaussElimination(const matrix&, const matrix&);
	/**
	 * solving matrix using LU Decompostion
	 * @params:
	 * 	const matrix* - left hand side
	 * 	const maitrx* - right hand side
	 * @return:
	 * 	matrix* - x in Ax=b
	 */
	matrix* luDecom(const matrix*, const matrix*);
}



class matrix{
	friend matrix solveMatrix::gaussElimination(const matrix &, const matrix &);
	private:
		int width;
		int height;
		double* arr;
		
		/**
		 * convert a 2D index into 1D index
		 * @params:
		 * 	int - row
		 * 	int - col
		 * @return:
		 * 	int - index of 1D array
		 * @error:
		 * 	std::range_error - when the given index is out of the matrix
		 */
		const int convertIndex(int, int) const;

	public:
		/**
		 * default constructor, create an empty array of float values
		 * @params:
		 * 	int - number of row
		 * 	int - number of col
		 */
		matrix(int, int);
		/**
		 * copy constructor.
		 * copy another matrix;
		 * @params:
		 * 	matrix* - the matrix to copy
		 */
		matrix(const matrix&);
		/**
		 * destructor.
		 */
		~matrix();
		/**
		 * get an element with 2D index
		 * @params:
		 * 	int - row
		 * 	int - col
		 * @return:
		 * 	double - index at the given palce
		 * @error:
		 * 	std::range_error - when the given index is out of the matrix
		 */
		const double get(int, int) const;
		/**
		 * set an element with 3D index
		 * @params:
		 * 	int - row
		 * 	int - col
		 * 	double - value to be set at the position
		 * @error:
		 * 	std::range_error - when the givne index is out of the matrix
		 */
		void set(int, int, double);

		// overloading operator
		friend matrix operator+(const matrix&, const matrix&);
		friend bool operator>(const matrix&, const matrix&);
		friend bool operator<(const matrix&, const matrix&);
		friend std::ostream& operator<<(std::ostream&, const matrix&);
};

#endif
