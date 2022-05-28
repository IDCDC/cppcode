#ifndef linalg_h
#define linalg_h

#include <iostream>
#include <initializer_list>
#include <math.h>

namespace WHYSC {
namespace AlgebraAlgrithom {

//算法2 一般的LU算法
template<typename Matrix>
	void lu_normal(Matrix & A, Matrix & L, Matrix & U)
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

//算法3 KIJ算法
template<typename Matrix>
	void lu_kij(Matrix & A, Matrix & L, Matrix & U)
	{
		typedef typename Matrix::Float  F;
	   	typedef typename Matrix::Int  I;
	    	I n = A.shape[0];
		for (int k = 0;k < n;k++)
		{
			for (int i = k+1;i < n;i++)
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

//算法4 IKJ算法
template<typename Matrix>
void lu_ikj(Matrix & A, Matrix & L, Matrix & U)
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


//算法5 待定系数法
template<typename Matrix>
void lu_uc(Matrix & A, Matrix & L, Matrix & U)
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


//算法7 部分主元LU分解
template<typename Matrix>
void lu_pp(Matrix & A, Matrix & L, Matrix & U)
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
			
			for (int i = k+1; i < n-1; i++)
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


//算法8：Cholesky 算法
template<typename Matrix>
void lu_cholesky(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
	for (I j = 0;j < n;j++)
	{
		double sum_1 = 0;
		double sum_2 = 0;
		for(I k = 0;k < j;k++)
			sum_1 = L[j][k]*L[j][k];
		sum_1 = A[j][j] - sum_1;
		L[j][j] = sqrt(sum_1);
		for (I i = j+1;i < n;i++)
		{
			for (I k = 0;k < j;k++)
				sum_2 = L[i][k]*L[j][k];
			L[i][j] = A[i][j] - sum_2;
			L[i][j] = L[i][j] / L[j][j];
		}
	
	}
	
	//给U赋值,U也就是L的转置
	for (int u_r = 0;u_r < n; u_r++)
		{for (int u_c = 0;u_c < n; u_c++)
			U[u_r][u_c] = L[u_c][u_r];
		}

		
    
    return;
}

//算法6：求解线性方程组
//求解ly=b
template<typename Matrix,typename Vector>

void ly_b(Matrix & L, Vector & y, Vector & b)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = L.shape[0];
    y[0] = b[0] / L[0][0];
	for (int i = 1;i < n;i++)
	{
		for (int j =0; j < i;j++)
			b[i] -= L[i][j]*y[j];
		y[i] = b[i] / L[i][i];
	}
		
    
    return;
}



//求解ux=y
template<typename Matrix,typename Vector>

void ux_y(Matrix & U, Vector & x, Vector & y)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = U.shape[0];
    int x_solve;
    x_solve = n - 1;
    x[x_solve]= y[x_solve]/U[x_solve][x_solve];
    for (int i = x_solve-1;i>=0;i--)
    {
	for (int j = x_solve;j >= 0;j--)
		y[i] = y[i]-U[i][j]*x[j];
	x[i] = y[i]/U[i][i];		
    }    
    return;
}



} // end of AlgebraAlgrithom
} // end of WHYSC
#endif // end of linalg_h
