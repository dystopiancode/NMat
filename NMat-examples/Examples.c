/*
 * examples.c
 *
 *  Created on: Aug 4, 2012
 *      Author: bogdan
 */
#include "Examples.h"

static void PrintMatrix(const NMatrix* mat)
{
	integer i, j;
	for (i = 0; i < mat->rows; ++i)
	{
		for (j = 0; j < mat->columns; ++j)
		{
			printf("%+lf ", mat->data[i][j]);
		}
		putchar('\n');
	}
}

void Examples_CreateCopyDestroy(void)
{
	NMatrix* mat = NULL;
	NMatrix* matCopy = NULL;
	/*Creating a 2x2 NMatrix structure*/
	mat = NMatrix_Create(2, 2);
	/*Assigning values to the structure*/
	mat->data[0][0] = 3.3;
	mat->data[0][1] = 2.1;
	mat->data[1][0] = 5.2;
	mat->data[1][1] = -6.3;
	/*Printing the matrix*/
	puts("The original matrix: ");
	PrintMatrix(mat);
	/*Creating a copy of the first matrix*/
	matCopy = NMatrix_Clone(mat);
	/*Destroying the first matrix*/
	mat = NMatrix_Destroy(mat);
	/*Printing the second matrix*/
	puts("The copy of the matrix: ");
	PrintMatrix(matCopy);
}
/*Output:
 The original matrix:
 +3.300000 +2.100000
 +5.200000 -6.300000
 The copy of the matrix:
 +3.300000 +2.100000
 +5.200000 -6.300000
 */
void Examples_SumProduct(void)
{
	NMatrix *mat1 = NULL;
	NMatrix *mat2 = NULL;
	NMatrix *res = NULL;
	integer i = 0, j = 0;
	/*Creating 2 matrices*/
	mat1 = NMatrix_Create(3, 3);
	mat2 = NMatrix_Create(3, 3);
	/*Assigning data to the elements of the matrices*/
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			mat1->data[i][j] = (real)(i + j);
			mat2->data[i][j] = (real)(i - j);
		}
	}
	/*Prints the matrices*/
	puts("A");
	PrintMatrix(mat1);
	puts("B");
	PrintMatrix(mat2);
	/*Scalar multiplication*/
	res = NMatrix_MultiplyWithScalar(mat1, 2.0f);
	puts("2*A");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
	/*Matrix addition*/
	res = NMatrix_Sum(mat1, mat2);
	puts("A+B");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
	/*Matrix subtraction*/
	res = NMatrix_Sum(mat1, NMatrix_MultiplyWithScalar(mat2, -1.0));
	puts("A-B");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
	/*Matrix multiplication*/
	res = NMatrix_Product(mat1, mat2);
	puts("A*B");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
	res = NMatrix_Product(mat2, mat1);
	puts("B*A");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
}
/*
A
+0.000000 +1.000000 +2.000000
+1.000000 +2.000000 +3.000000
+2.000000 +3.000000 +4.000000

B
+0.000000 -1.000000 -2.000000
+1.000000 +0.000000 -1.000000
+2.000000 +1.000000 +0.000000

2*A
+0.000000 +2.000000 +4.000000
+2.000000 +4.000000 +6.000000
+4.000000 +6.000000 +8.000000

A+B
+0.000000 +0.000000 +0.000000
+2.000000 +2.000000 +2.000000
+4.000000 +4.000000 +4.000000

A-B
+0.000000 +2.000000 +4.000000
+0.000000 +2.000000 +4.000000
+0.000000 +2.000000 +4.000000

A*B
+5.000000 +2.000000 -1.000000
+8.000000 +2.000000 -4.000000
+11.000000 +2.000000 -7.000000

B*A
-5.000000 -8.000000 -11.000000
-2.000000 -2.000000 -2.000000
+1.000000 +4.000000 +7.000000
 */

void Examples_Minor(void)
{
	integer i = 0, j = 0;
	NMatrix *mat = NULL;
	NMatrix *minor = NULL;
	/*Creating the matrix*/
	mat = NMatrix_Create(5, 5);
	/*Assigning values to the matrix*/
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			mat->data[i][j] = (real)(i + j);
		}
	}
	/*Computing the minor*/
	minor = NMatrix_Minor(mat, 1, 1, 3);
	/*Printing the matrices*/
	puts("Original matrix: ");
	PrintMatrix(mat);
	puts("Minor: ");
	PrintMatrix(minor);
}
/*:
 Original matrix:
 0.000000 1.000000 2.000000 3.000000 4.000000
 1.000000 2.000000 3.000000 4.000000 5.000000
 2.000000 3.000000 4.000000 5.000000 6.000000
 3.000000 4.000000 5.000000 6.000000 7.000000
 4.000000 5.000000 6.000000 7.000000 8.000000

 Minor:
 0.000000 2.000000 3.000000
 2.000000 4.000000 5.000000
 3.000000 5.000000 6.000000
 */

void Examples_Determinant(void)
{
	real det = 0;
	NMatrix *mat = NULL;
	/*Creates and initializes the matrix*/
	mat = NMatrix_Create(3, 3);
	mat->data[0][0]=-2;
	mat->data[0][1]=2;
	mat->data[0][2]=-3;
	mat->data[1][0]=-1;
	mat->data[1][1]=1;
	mat->data[1][2]=3;
	mat->data[2][0]=2;
	mat->data[2][1]=0;
	mat->data[2][2]=-1;
	/*Prints the matrix*/
	puts("Matrix: ");
	PrintMatrix(mat);
	/*Computes the determinant of the matrix*/
	puts("Determinant of the matrix: ");
	det = NMatrix_Determinant(mat, 3);
	printf("%2.1f\n", det);
	/*Computes the determinant of a minor*/
	puts("Determinant of a minor (M33): ");
	det = NMatrix_Determinant(mat, 2);
	printf("%2.1f", det);
}
/*:
Matrix:
-2.000000 2.000000 -3.000000
-1.000000 1.000000 3.000000
2.000000 0.000000 -1.000000

Determinant of the matrix:
18.0
Determinant of a minor (M33):
0.0
 */
void Examples_TransposeAdjutantInverse(void)
{
	integer i = 0, j = 0;
	NMatrix *mat = NULL;
	NMatrix *res = NULL;
	/*Creates and initializes the matrix*/
	mat = NMatrix_Create(3, 3);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			mat->data[i][j] = (real) (i + j);
		}
	}
	mat->data[0][0] = 32;

	puts("Original matrix: ");
	PrintMatrix(mat);

	res = NMatrix_Transpose(mat);
	puts("Transpose matrix: ");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);

	res = NMatrix_Adjugate(mat);
	puts("Adjugate matrix: ");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);

	res = NMatrix_Inverse(mat);
	puts("Inverse matrix: ");
	PrintMatrix(res);
	res = NMatrix_Destroy(res);
}
/*:
Original matrix:
32.000000 1.000000 2.000000
1.000000 2.000000 3.000000
2.000000 3.000000 4.000000

Transpose matrix:
32.000000 1.000000 2.000000
1.000000 2.000000 3.000000
2.000000 3.000000 4.000000

Adjugate matrix:
-1.000000 2.000000 -1.000000
2.000000 124.000000 -94.000000
-1.000000 -94.000000 63.000000

Inverse matrix:
0.031250 -0.062500 0.031250
-0.062500 -3.875000 2.937500
0.031250 2.937500 -1.968750
 */
void Examples_Others(void)
{
	NMatrix *mat = NULL;
	NMatrix *smat1 = NULL, *smat2=NULL;
	integer i,j;

	mat = NMatrix_Create(3,3);
	for(i=0; i<mat->rows; i++)
	{
		for(j=0; j<mat->columns; j++)
		{
			mat->data[i][j] = (real)(i+j+1);
		}
	}

	puts("The matrix: ");
	PrintMatrix(mat);

	printf("The smallest element is                :%f \n",
			NMatrix_MinElement(mat));
	printf("The largest element is                 :%f \n",
			NMatrix_MaxElement(mat));
	printf("The sum of all elements is             :%f \n",
			NMatrix_ElementSum(mat));
	printf("The product of all elements is         :%f \n",
			NMatrix_ElementProduct(mat));
	printf("The total number of elements is        :%d \n",
			NMatrix_ElementCount(mat));
	printf("The arithmetic mean of all elements is :%f \n",
			NMatrix_ArithmeticMean(mat));
	printf("The geometric mean of all elements is  :%f \n",
			NMatrix_GeometricMean(mat));
	printf("The harmonic mean of all elements is   :%f \n",
			NMatrix_HarmonicMean(mat));

	/*Will be a column vector containing column 1*/
	smat1 = NMatrix_Submatrix(mat,0,2,1,1);
	/*Will be a row vector containing only row 0*/
	smat2 = NMatrix_Submatrix(mat,0,0,0,2);

	puts("Submatrix 1: ");
	PrintMatrix(smat1);

	puts("Submatrix 2: ");
	PrintMatrix(smat2);
}
/*Output:
The matrix:
+1.000000 +2.000000 +3.000000
+2.000000 +3.000000 +4.000000
+3.000000 +4.000000 +5.000000
The smallest element is                :1.000000
The largest element is                 :5.000000
The sum of all elements is             :27.000000
The product of all elements is         :8640.000000
The total number of elements is        :9
The arithmetic mean of all elements is :3.000000
The geometric mean of all elements is  :2.432432
The harmonic mean of all elements is   :2.737729
The matrix:
+2.000000
+3.000000
+4.000000
The matrix:
+1.000000 +2.000000 +3.000000
 */
