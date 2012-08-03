/*
 * examples.c
 *
 *  Created on: Aug 4, 2012
 *      Author: bogdan
 */
#include "Examples.h"

static void PrintMatrix(const NMatrix* mat)
{
	integer i,j;
	for(i=0; i<mat->rows; ++i)
	{
		for(j=0; j<mat->columns; ++j)
		{
			printf("%+lf ",mat->data[i][j]);
		}
		putchar('\n');
	}
}

void Examples_BasicNMat(void)
{
	NMatrix* mat = NULL;
	NMatrix* matCopy = NULL;
	/*Creating a 2x2 NMatrix structure*/
	mat = NMatrix_Create(2,2);
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
