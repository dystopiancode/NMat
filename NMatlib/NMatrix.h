/*
 * NMatrix.h
 *
 *  Created on: Jun 13, 2012
 *      Author: bogdan
 */

#ifndef NMATRIX_H_
#define NMATRIX_H_

#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<limits.h>

typedef double real;
typedef int integer;

#define REAL_MIN 		DBL_MIN
#define REAL_MAX 		DBL_MAX
#define INTEGER_MIN		INT_MIN
#define INTEGER_MAX		INT_MAX


typedef struct
{
   real** data;
   integer rows;
   integer columns;
}NMatrix;

/*
 * Description:
 * 	Alocates spaces for a NMatrix structure according to the parameters
 * @rows si @columns.
 * Parameters:
 * 	rows - the number of rows
 * 	columns - the number of columns
 * Returns:
 *  A pointer to the allocated matrix structure.
 */
NMatrix* NMatrix_Create(integer rows, integer columns);
/*
 * Description:
 * 	Free the space hold by a NMatrix structure
 * Parameters:
 * 	matrix - a pointer to the NMatrix structure
 * Returns:
 *  NULL
 * Preconditions:
 *  @matrix must not be NULL
 */
NMatrix* NMatrix_Destroy(NMatrix *matrix);
/*
 * Description:
 * 	Creates a hard copy of the matrix @source
 * Parameters:
 * 	source - the matrix who shall be copied
 * 	destination - the matrix where the copy
 * 				  will be stored
 * Returns:
 * 	A pointer to the clone matrix
 * Preconditions:
 *  @matrix must not be NULL
 */
NMatrix* NMatrix_Clone(const NMatrix *source);
/*
 * Description:
 * 	Sums up two matrices
 * Parameters:
 * 	mat1 - a pointer to the first matrix
 * 	mat2 - a pointer to the second matrix
 * Returns:
 *  A pointer to the result matrix.
 *  If the rows/columns of mat1 and mat2 are not
 * equal, the result will be NULL
 * Preconditions:
 *  @mat1 and @mat2 must not be NULL
 */
NMatrix* NMatrix_Sum(const NMatrix* mat1,const NMatrix* mat2);
/*
 * Description:
 * 	Multiplies a NMatrix with a scalar
 * Parameters:
 * 	mat - a pointer to NMatrix who shall be multiplied
 * Returns:
 *  A pointer to the result matrix.
 * Preconditions:
 *  @mat must not be NULL
 */
NMatrix* NMatrix_MultiplyWithScalar(const NMatrix* mat, real value);
/*
 * Description:
 * 	Returns the product of two matrices
 * Parameters:
 * 	mat1 - a pointer to the first matrix
 * 	mat2 - a pointer to the second matrix
 * Returns:
 *  A pointer to the result matrix.
 * Preconditions:
 *  @mat must not be NULL
 */
NMatrix* NMatrix_Product(const NMatrix* mat1,const NMatrix* mat2);
/*
 * Description:
 * 	Returns the primary diagonal of a square
 * 	matrix as an NArray
 * Parameters:
 * 	mat1 - a pointer to the matrix
 * Returns:
 *  A pointer to the NArray holding the values
 * situated on the primary diagonal
 * Preconditions:
 *  @mat must not be NULL
 *  @may must be a square matrix
 */
NMatrix* NMatrix_GetSecondaryDiagonal(NMatrix* mat);
/*
 * Description:
 * 	Returns the secondary diagonal of a square
 * 	matrix as an NArray
 * Parameters:
 * 	mat1 - a pointer to the matrix
 * Returns:
 *  A pointer to the NArray holding the values
 * situated on the secondary diagonal
 * Preconditions:
 *  @mat must not be NULL
 *  @may must be a square matrix
 */
NMatrix* NMatrix_GetPrimaryDiagonal(NMatrix *mat);
/*
 * Description:
 * 	Computes the minor of a given matrix according to
 * a predefined @row, @column and @order.
 * Parameters:
 * 	mat1 - a pointer to the matrix
 * 	row - the starting row
 * 	column - the starting column
 * 	order - the size of the minor
 * Returns:
 *  A pointer to the minor matrix if the conditions are valid.
 * Otherwise returns NULL.
 * Preconditions:
 *  @mat must not be NULL
 *  @may must be a square matrix
 *  @column and @row must be smaller than @order
 *  @order must be greater than 1 but smaller than
 *  the size of the matrix
 */
NMatrix* NMatrix_Minor(const NMatrix *mat,
						 integer row, integer column,
						 integer order);
/*
 * Description:
 * 	Computes the determinant of a given matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * 	order - usually the size of square matrix, but it can be used
 * 		    if you want to compute a determinant of a minor
 * Returns:
 *  The value of the determinant if the input is correct.
 * Otherwise returns NaN.
 * Preconditions:
 *  @mat must not be NULL
 *  @mat must be a square matrix
 *  @column and @row must be smaller than @order
 *  @order must be greater than 1 but smaller or equal when
 *  compared to the size of the matrix
 */
real NMatrix_Determinant(const NMatrix *mat, integer order);
/*
 * Description:
 * 	Computes the transpose matrix of a given matrix
 * Parameters:
 * 	mat   - a pointer to the original matrix
 * Returns:
 *  A pointer to the transpose matrix of the original matrix.
 * Preconditions:
 *  @mat must not be NULL
 */
NMatrix* NMatrix_Transpose(const NMatrix* mat);
/*
 * Description:
 * 	Computes the adjugate matrix of a given matrix
 * Parameters:
 * 	mat   - a pointer to the original matrix
 * Returns:
 *  A pointer to the adjugate matrix of the original matrix.
 * Preconditions:
 *  @mat must not be NULL
 */
NMatrix* NMatrix_Adjugate(const NMatrix* mat);
/*
 * Description:
 * 	Computes the inverse matrix of a given matrix
 * Parameters:
 * 	mat   - a pointer to the original matrix
 * Returns:
 *  A pointer to the inverse matrix of the original matrix.
 * Preconditions:
 *  @mat must not be NULL
 *  @mat must not be singular (det(@mat)!=0)
 */
NMatrix* NMatrix_Inverse(const NMatrix* mat);
/*
 * Description:
 * 	Finds the minimum element of the matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The minimum element. If an error happened it will return REAL_MAX
 */
real NMatrix_MinElement(const NMatrix* mat);
/*
 * Description:
 * 	Finds the maximum element of the matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The maximum element. If an error happened it will return REAL_MIN
 */
real NMatrix_MaxElement(const NMatrix* mat);
/*
 * Description:
 * 	Sums up all the elements of the matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The sum of all the elements. If an error happened it will return NAN
 */
real NMatrix_ElementSum(const NMatrix* mat);
/*
 * Description:
 * 	Computes the product of all elements in the matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The product of all elements in the matrix. If an error happened it will
 *  return NAN.
 */
real NMatrix_ElementProduct(const NMatrix* mat);
/*
 * Description:
 * 	Computes the number of elements in the matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The number of elements in the matrix. If an error happened it will
 *  return -1.
 */
integer NMatrix_ElementCount(const NMatrix* mat);

/*
 * Description:
 * 	Creates a submatrix of the current matrix
 * Parameters:
 * 	mat   - a pointer to the matrix
 * 	startRow,endRow - the row delimiters
 * 	startColumn, endColumn - the column delimiters
 * Returns:
 *  The specified submatrix. If an error happened it will return NULL.
 */
NMatrix* NMatrix_Submatrix(const NMatrix* mat,
						  	 integer startRow, integer endRow,
						  	 integer startColumn, integer endColumn);
/*
 * Description:
 * 	Computes the arithmetic mean of all elements
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The arithmetic mean. If an error happened it will return NAN.
 */
real NMatrix_ArithmeticMean(const NMatrix* mat);
/*
 * Description:
 * 	Computes the harmonic mean of all elements
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The harmonic mean. If an error happened it will return NAN.
 */
real NMatrix_HarmonicMean(const NMatrix* mat);
/*
 * Description:
 * 	Computes the geometric mean of all elements
 * Parameters:
 * 	mat   - a pointer to the matrix
 * Returns:
 *  The geometric mean. If an error happened it will return NAN.
 */
real NMatrix_GeometricMean(const NMatrix* mat);

#endif /* NMATRIX_H_ */
