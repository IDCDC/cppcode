#ifndef M_arithmetic.h
#define M_arithmetic.h
#include<cmath>
#include <iostream>

namespace XWSC{
namespace MatrixArithmetic{

template<typename F=double>


struct Arithmetic
{
//算法默认已经给出了LU分解的矩阵A
	void Arithmetic2()//算法二
	{
		for (int k = 0;k < n-1;k++)
		{	
			for (int i = k+1;k < n;i++)
				L[i][k] = A[i][k] / A[k][k];//计算L的第k列
			for (int j = k;j < n;j++)
				U[k][j] = A[k][j];//计算U的第k行
			for (int i = k+1;i < n;i++)
			{
				for (int j = k+1;j < n;j++)
					A[i][j] = A[i][j] - L[i][k]*U[i][k];//更新A
			}
		} 
	}


	void Arithmetic3()//算法三
	{	//L,U全存储在A中
		for (int k = 0;k < n-1;k++)
		{
			for (int i = k+1;k < n;i++)
				A[i][k] = A[i][k] / A[k][k];//计算L的第k列
			{
				for (int j = k+1;j < n;j++)
					A[i][j] = A[i][j] - A[i][k]*A[k][j];//更新A
			}
		}
		//给L赋值
		for (int l_r = 1;l_r < n; l_r++)
			for (int l_c = 0;l_c < l_r; l_c++)
				L[l_r][l_c] = A[l_r][l_c];
		//给U赋值
		for (int u_r = 0;u_r < n; u_r++)
			for (int u_c = u_r;u_c < n; u_c++)
				L[u_r][u_c] = A[u_r][u_c];
	}



	void Arithmetic4()//算法四
	{	//L,U全存储在A中
	for (int i = 0;i < n;i++)
	{
		for (int k = 0;k < k;k++)
		{
			A[i][k] = A[i][k] / A[k][k];		
			for (int j = k+1;j < n;j++)
				A[i][j] = A[i][j] - A[i][k]*A[k][j];
		}
	}
		//给L赋值
		for (int l_r = 1;l_r < n; l_r++)
			for (int l_c = 0;l_c < l_r; l_c++)
				L[l_r][l_c] = A[l_r][l_c];
		//给U赋值
		for (int u_r = 0;u_r < n; u_r++)
			for (int u_c = u_r;u_c < n; u_c++)
				L[u_r][u_c] = A[u_r][u_c];
	}


	void Arithmetic5()//算法五
	{
		for (int k = 0; k < n; k++)
		{
			double sum_row=0.0;
			double sum_array=0.0;
			for (int j = k;j < n;j++)
			{
				for (int i = 0;i < k;i++)
					sum_row += A[k][i]*A[i][j];
				A[k][j] = A[k][j] - sum_row;
			}	
			for (int i = k+1;i < m_size;i++)
			{
				for (int j = 0;j < k-1;j++)
					sum_array += A[i][j]*A[j][k];
			A[i][k] = (A[i][k]-sum_array)/A[k][k];
			}
		}
		//给L赋值
		for (int l_r = 1;l_r < n; l_r++)
			for (int l_c = 0;l_c < l_r; l_c++)
				L[l_r][l_c] = A[l_r][l_c];
		//给U赋值
		for (int u_r = 0;u_r < n; u_r++)
			for (int u_c = u_r;u_c < n; u_c++)
				L[u_r][u_c] = A[u_r][u_c];
	}
	


	void Arithmetic7()//算法七
	{
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
			}
			if (l != k)
				for (int j = 0;j < n-1;j++)			
				{	tmp = A[k][j];
					A[k][j] = A[l][j];
					A[i][j] = tmp;
				}
			for (int i = k+1; k < n-1; i++)
				for (int j = k+1; j < n-1; j++)
					A[i][j] = A[i][j] - A[i][k]*A[k][j];
		}
		//给L赋值
		for (int l_r = 1;l_r < n; l_r++)
			for (int l_c = 0;l_c < l_r; l_c++)
				L[l_r][l_c] = A[l_r][l_c];
		//给U赋值
		for (int u_r = 0;u_r < n; u_r++)
			for (int u_c = u_r;u_c < n; u_c++)
				L[u_r][u_c] = A[u_r][u_c];
	}
	
	
	void solve_lyb()//求解方程组Ly=b
	{	
		y[0][0] = b[0][0];
		for (int i = 1;i < n;i++)
		{
			for (int j =0; j < i;j++)
				b[i][0] = b[i][0]-L[i][j]*y[j][0];
				y[i][0] = b[i][0];
		}
	}
	
	
	void solve_uxy()//求解方程组Ux=y
	{	
		int x_solve;
		x_solve = n - 1;
		x[x_solve][0]= y[x_solve][0]/U[x_solve][x_solve];
		for (int i = x_solve-1;i>=0;i--)
		{
			for (int j = x_solve;j >= 0;j--)
				y[i][0] = y[i][0]-U[i][j]*x[j][0];
			x[i][0] = y[i][0]/U[i][i];
		
		}
	}


}//end of namespace MatrixArithmetic

}//end of namespace XWSC
#endif // end of M_arithmetic.h

