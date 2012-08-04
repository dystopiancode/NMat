/*
 * NMatrix.c
 *
 *  Created on: Jun 13, 2012
 *      Author: bogdan
 */
#include"NMatrix.h"


NMatrix* NMatrix_Create(integer rows, integer columns)
{
	integer i = 0;
	NMatrix* matrix = NULL;
	matrix = (NMatrix*)malloc(sizeof(NMatrix));
	if(matrix!=NULL)
	{
		matrix->rows = rows;
		matrix->columns = columns;
		matrix->data = (real**)malloc(rows * sizeof(real*));
		for(i=0; i<rows; i++)
		{
			matrix->data[i] = (real *)malloc(columns*sizeof(real));
		}
	}
	return matrix;
}

NMatrix* NMatrix_Destroy(NMatrix *matrix)
{
	integer i = 0;
	if(matrix!=NULL)
	{
		for(i=0 ; i<matrix->rows; i++)
		{
			free(matrix->data[i]);
		}
		free(matrix->data);
	}
	matrix->columns = 0;
	matrix->rows = 0;
	free(matrix);
	return NULL;
}

NMatrix* NMatrix_Clone(const NMatrix *source)
{
	integer i,j;
	NMatrix *dest = NULL;
	dest = NMatrix_Create(source->rows, source->columns);
	if(dest!=NULL)
	{
		for(i=0;i<source->rows;i++)
		{
			for(j=0;j<source->columns;j++)
			{
				dest->data[i][j] = source->data[i][j];
			}
		}
	}
	return dest;
}

NMatrix* NMatrix_Sum(const NMatrix* mat1,const NMatrix* mat2)
{
    integer i = 0, j = 0;
    NMatrix *result = NULL;
    if((mat1->rows==mat2->rows) && (mat1->columns==mat2->columns))
    {
        result = NMatrix_Create(mat1->rows, mat1->columns);
        for(i=0;i<mat1->rows;i++)
        {
            for(j=0;j<mat1->columns;j++)
            {
                result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
            }
        }
    }
    return result;
}

NMatrix* NMatrix_MultiplyWithScalar(const NMatrix* mat, real value)
{
    integer i = 0, j = 0;
    NMatrix *smat = NULL;
    smat = NMatrix_Clone(mat);
    for(i=0;i<mat->rows;i++)
    {
        for(j=0;j<mat->columns;j++)
        {
            smat->data[i][j]*=value;
        }
    }
    return smat;
}

NMatrix* NMatrix_Product(const NMatrix* mat1,const NMatrix* mat2)
{
    integer i = 0 ,j = 0 ,k = 0, p = 0;
    NMatrix *result = NULL;
    if(mat1->rows==mat2->columns)
    {
        result = NMatrix_Create(mat1->rows, mat2->columns);
        for(i=0;i<mat1->rows;i++)
        {
            for(j=0;j<mat2->columns;j++)
            {
                p=0;
                for(k=0;k<mat1->columns;k++)
                {
                    p+=mat1->data[i][k]*mat2->data[k][j];
                }
                result->data[i][j]=p;
            }
        }
    }
    return result;
}

NMatrix* NMatrix_GetPrimaryDiagonal(NMatrix *mat)
{
    integer i = 0;
    NMatrix *diagonal = NULL;
    if(mat->rows==mat->columns)
    {
        diagonal = NMatrix_Create(1,mat->columns);
        for(i=0;i<mat->rows;i++)
        {
          diagonal->data[0][i] = mat->data[i][i];
        }
    }
    return diagonal;
}

NMatrix* NMatrix_GetSecondaryDiagonal(NMatrix* mat)
{
    integer i = 0;
    NMatrix *diagonal = NULL;
    if(mat->rows==mat->columns)
    {
    	diagonal = NMatrix_Create(1,mat->columns);
		for(i=0;i<mat->rows;i++)
		{
			diagonal->data[0][i] = mat->data[i][mat->rows-1-i];
		}
    }
    return diagonal;
}

NMatrix* NMatrix_Minor(const NMatrix *mat, integer row,
					   integer column, integer order)
{
   integer i=0, j=0;
   integer rowCount = 0, colCount = 0;
   NMatrix *minor = NULL;

   if((mat->rows==mat->columns) && ((row-1)<order) && ((column-1)< order) &&
	   (order>=1) && (order<mat->rows) )
   {
	   if(order==1)
	   {
		   minor = NMatrix_Create(1,1);
		   minor->data[0][0] = mat->data[row][column];
	   }
	   else
	   {
		   minor = NMatrix_Create(order, order);
		   for(i=0; i<=order; i++)
		   {
			   if(i!=row)
			   {
				   colCount = 0;
				   for(j=0;j<=order;j++)
				   {
					   if(j!=column)
					   {
						   minor->data[rowCount][colCount] = mat->data[i][j];
						   colCount++;
					   }
					}
					rowCount++;
				}
		   }
	   }
   }
   return minor;
}

real NMatrix_Determinant(const NMatrix *mat, integer order)
{
   integer i = 0 ,j = 0 ,k = 0 ,l = 0;
   real det = 0.0;
   NMatrix *minor = NULL;
   if((mat->rows == mat->columns) && (order>=1) && (order<=mat->rows))
   {
	   if(order==1)
	   {
		   det = mat->data[0][0];
	   }
	   else if(order==2)
	   {
		   det = (mat->data[0][0] * mat->data[1][1]) -
				 (mat->data[0][1] * mat->data[1][0]);
	   }
	   else
	   {
		   for (k=0 ; k<order ; k++)
		   {
			   minor = NMatrix_Create(order,order);
		       for(i=1 ; i<order ; i++)
		       {
		    	   l = 0;
				   for (j=0;j<order;j++)
				   {
					  if (j != k)
					  {
						  minor->data[i-1][l] = mat->data[i][j];
						  l++;
					  }
				   }
		       }
			   det += pow(-1.0,k) * mat->data[0][k]
					 * NMatrix_Determinant(minor,order-1);
			   minor = NMatrix_Destroy(minor);
		   }
	   }
   }
   else
   {
	   det = NAN;
   }
   return det;
}

NMatrix* NMatrix_Transpose(const NMatrix* mat)
{
   integer i = 0, j = 0;
   NMatrix* transpose = NULL;
   transpose = NMatrix_Create(mat->columns,mat->rows);
   for(i=0;i<transpose->rows;i++)
   {
	   for(j=0;j<transpose->columns;j++)
	   {
		   transpose->data[i][j] = mat->data[j][i];
	   }
   }
   return transpose;
}

NMatrix* NMatrix_Adjugate(const NMatrix* mat)
{
   integer i = 0, j = 0, dim = 0;
   real det = 0.0;
   NMatrix* minor = NULL;
   NMatrix* adjugate = NULL;
   if(mat->columns == mat->rows)
   {
       dim = mat->columns;
       adjugate = NMatrix_Create(dim,dim);
       for(j=0;j<dim;j++)
       {
		   for(i=0;i<dim;i++)
		   {
			   minor = NMatrix_Minor(mat,i,j,dim-1);
			   det = NMatrix_Determinant(minor,dim-1);
			   adjugate->data[i][j] = pow(-1.0f,i+j+2.0f) * det;
		   }
      }
   }
   return adjugate;
}

NMatrix* NMatrix_Inverse(const NMatrix* mat)
{
    NMatrix* inv = NULL;
    real det = 0.0f;
    real coeficent = 0.0f;
    if(mat->rows==mat->columns)
    {
        det = NMatrix_Determinant(mat,mat->rows);
        if(det != 0.0f)
        {
        	inv = NMatrix_Create(mat->rows,mat->columns);
        	coeficent = 1.0f/NMatrix_Determinant(mat,mat->rows);
            inv = NMatrix_Adjugate(mat);
            inv = NMatrix_MultiplyWithScalar(inv,coeficent);
        }
    }
    return inv;
}

real NMatrix_MinElement(const NMatrix* mat)
{
	real minElement = REAL_MAX;
	integer i, j;
	if(mat!=NULL)
	{
		for(i=0; i<mat->rows; i++)
		{
			for(j=0; j<mat->columns; j++)
			{
				if(mat->data[i][j]<minElement)
				{
					minElement = mat->data[i][j];
				}
			}
		}
	}
	return minElement;
}

real NMatrix_MaxElement(const NMatrix* mat)
{
	real maxElement = REAL_MIN;
	integer i, j;
	if(mat!=NULL)
	{
		for(i=0; i<mat->rows; i++)
		{
			for(j=0; j<mat->columns; j++)
			{
				if(mat->data[i][j]>maxElement)
				{
					maxElement = mat->data[i][j];
				}
			}
		}
	}
	return maxElement;
}

real NMatrix_ElementSum(const NMatrix* mat)
{
	real sum = 0.0;
	integer i, j;
	if(mat!=NULL)
	{
		for(i=0; i<mat->rows; i++)
		{
			for(j=0; j<mat->columns; j++)
			{
				sum += mat->data[i][j];
			}
		}
	}
	else
	{
		sum = NAN;
	}
	return sum;
}

real NMatrix_ElementProduct(const NMatrix* mat)
{
	real product = 1.0;
	integer i, j;
	if(mat!=NULL)
	{
		for(i=0; i<mat->rows; i++)
		{
			for(j=0; j<mat->columns; j++)
			{
				product *= mat->data[i][j];
			}
		}
	}
	else
	{
		product=NAN;
	}
	return product;
}

integer NMatrix_ElementCount(const NMatrix* mat)
{
	integer total = -1;
	if(mat!=NULL)
	{
		total = mat->rows*mat->columns;
	}
	return total;
}

NMatrix* NMatrix_Submatrix(const NMatrix* mat,
						     integer startRow, integer endRow,
						     integer startColumn, integer endColumn)
{
	NMatrix* minor = NULL;
	integer i,j;
	integer rows, columns;
	if( (startRow>=0) && (endRow<mat->rows) && (startRow<=endRow) &&
		(startColumn>=0) && (endColumn<mat->columns) && (startColumn<=endColumn) )
	{
		rows = endRow - startRow + 1;
		columns = endColumn - startColumn +1;
		minor = NMatrix_Create(rows,columns);
		if(minor!=NULL)
		{
			for(i=0; i<rows; i++)
			{
				for(j=0; j<columns; j++)
				{
					minor->data[i][j] = mat->data[i+startRow][j+startColumn];
				}
			}
		}
	}
	return minor;
}

real NMatrix_ArithmeticMean(const NMatrix* mat)
{
	real result = NAN;
	if(mat!=NULL)
	{
		result = NMatrix_ElementSum(mat)/(real)(NMatrix_ElementCount(mat));
	}
	return result;
}

real NMatrix_HarmonicMean(const NMatrix* mat)
{
	real result = NAN;
	if(mat!=NULL)
	{
		result = pow(NMatrix_ElementProduct(mat),
				     ( 1.0/ ((real)( NMatrix_ElementCount(mat))) ) );
	}
	return result;
}

real NMatrix_GeometricMean(const NMatrix* mat)
{
	real result = NAN;
	integer i, j;
	if(mat!=NULL)
	{
		result = 0.0;
		for(i = 0; i<mat->rows; i++)
		{
			for(j = 0; j<mat->columns; j++)
			{
				result+=1.0/(mat->data[i][j]);
			}
		}
		result = (real)(NMatrix_ElementCount(mat))*pow(result,-1.0);
	}
	return result;
}
