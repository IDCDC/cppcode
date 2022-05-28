#ifndef linalg_h
#define linalg_h

#include <iostream>
#include <initializer_list>

namespace WHYSC {
namespace AlgebraAlgrithom {

template<typename Matrix>
	void lu2(Matrix & A, Matrix & L, Matrix & U)
	{
	    typedef typename Matrix::Float  F;
	    typedef typename Matrix::Int  I;
	    I n = A.shape[0];
	    for(I k=0; k<n; k++)
		{
			for (I i=k+1; i<n; i++)
			{
				L[i][k] = A[i][k]/A[k][k];
			}
	
			for(I j=k; j<n; j++)
			{
				U[k][j] = A[k][j];
			}

			for(I i=k+1; i<n ;i++)
			{
				for(I j=k+1;j<n;j++)
				{
					A[i][j] -= L[i][k]*U[k][j];
				}
			}
	
		}

		for(I i=0;i<n;i++)
	        	L[i][i] =1 ;
	
		return;
	}


template<typename Matrix>
	void lu3(Matrix & A, Matrix & L, Matrix & U)
	{
		typedef typename Matrix::Float  F;
	   	typedef typename Matrix::Int  I;
	    	I n = A.shape[0];
		for (int k = 0;k < n;k++)
		{
			for (int i = k+1;k < n;i++)
			{
				A[i][k] = A[i][k] / A[k][k];//计算L的第k列			
				for (int j = k+1;j < n;j++)
				{
					A[i][j] -= A[i][k]*A[k][j];//更新A
				}
			}
		}
	//给L赋值
	for(I i=0;i<n;i++)
	
       	L[i][i] = 1;
       
	for (int l_r = 1;l_r < n; l_r++)
	{
		for (int l_c = 0;l_c < l_r; l_c++)
		
			L[l_r][l_c] = A[l_r][l_c];
		
	}		
	//给U赋值
	for (int u_r = 0;u_r < n; u_r++)
		{for (int u_c = u_r;u_c < n; u_c++)
			U[u_r][u_c] = A[u_r][u_c];
		}

    		return;
	}


template<typename Matrix>
void lu4(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    for (int i = 1;i < n;i++)
	{
		for (int k = 0;k < i;k++)
		{
			A[i][k] = A[i][k] / A[k][k];		
			for (int j = k+1;j < n;j++)
				A[i][j] -= A[i][k]*A[k][j];
		}
	}
	//给L赋值
	for(I i=0;i<n;i++)
       	L[i][i] = 1;
	for (int l_r = 1;l_r < n; l_r++)
		for (int l_c = 0;l_c < l_r; l_c++)
			L[l_r][l_c] = A[l_r][l_c];		
	//给U赋值
	for (int u_r = 0;u_r < n; u_r++)
		{for (int u_c = u_r;u_c < n; u_c++)
			U[u_r][u_c] = A[u_r][u_c];
		}

    return;
}



template<typename Matrix>
void lu5(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
	for (int k = 0; k < n; k++)
		{
			for (int j = k;j < n;j++)
			{
				for (int i = 0;i < k;i++)
					A[k][j] -= A[k][i]*A[i][j];
			}	
			for (int h = k+1;h < n;h++)
			{
				for (int j = 0;j < k;j++)
					A[h][k] -= A[h][j]*A[j][k];
			A[h][k] = A[h][k]/A[k][k];
			}
		}
	//给L赋值
	for(I i=0;i<n;i++)
       	L[i][i] = 1;
	for (int l_r = 1;l_r < n; l_r++)
		for (int l_c = 0;l_c < l_r; l_c++)
			L[l_r][l_c] = A[l_r][l_c];		
	//给U赋值
	for (int u_r = 0;u_r < n; u_r++)
		{for (int u_c = u_r;u_c < n; u_c++)
			U[u_r][u_c] = A[u_r][u_c];
		}

    
    return;
}


template<typename Matrix>
void lu7(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    double tmp;
		for (int k = 0;k < n-2;k++)
		{	//先找出主元
			double a_max = 0;
			int l = 0;
			for (int h = k;h < n;h++)
			{
				if (fabs(A[h][k]) > fabs(a_max))
				{	a_max = A[h][k];
					l = h;
				}
			if (l != k)
				for (int j = 0;j < n-1;j++)			
				{	tmp = A[k][j];
					A[k][j] = A[l][j];
					A[h][j] = tmp;
				}
			}
			
			for (int i = k+1; k < n-1; i++)
				for (int j = k+1; j < n-1; j++)
					A[i][j] = A[i][j] - A[i][k]*A[k][j];
		}
	//给L赋值
	for(I i=0;i<n;i++)
       	L[i][i] = 1;
	for (int l_r = 1;l_r < n; l_r++)
		for (int l_c = 0;l_c < l_r; l_c++)
			L[l_r][l_c] = A[l_r][l_c];		
	//给U赋值
	for (int u_r = 0;u_r < n; u_r++)
		{for (int u_c = u_r;u_c < n; u_c++)
			U[u_r][u_c] = A[u_r][u_c];
		}

    
    return;
}




} // end of AlgebraAlgrithom
} // end of WHYSC
#endif // end of linalg_h
