#include <iostream>
#include "include/algebra/Matrix.h"
using namespace std;

typedef WHYSC::AlgebraObject::Matrix<double> Matrix;



int main(int argc, char **argv)
{
	Matrix A(2, 2,0.0);
	const int m_row = 2;
	const int m_array = 2;
	//矩阵必为方阵,所以可以定义矩阵的行列都为一相等的数.
	const int m_size=2;
	Matrix b(2, 1,0.0);
	double A_zd[m_row][m_array] = {{0.02,61.3},{3.43,-8.5}};
	double b_zd[m_size][1] = {61.5,25.8};
	
	for (int i = 0;i < m_row;i++)
	{
		for (int j = 0;j < m_array;j++)
			A[i][j] = A[i][j] + A_zd[i][j];
	}
	
	for (int i = 0;i < m_size;i++)
		b[i][0] = b[i][0]+b_zd[i][0];
	

	for (int k = 0; k < m_size; k++)
	{
		double sum_row=0.0;
		double sum_array=0.0;
		for (int j = k;j < m_size;j++)
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
	
	cout << "输出LU分解后的矩阵A" <<endl;
	A.print();
	
	
	//求解方程组Ly=b.
	Matrix y(2,1,0.0);
	y[0][0] = b[0][0];
	for (int i = 1;i < m_size;i++)
	{
		for (int j =0; j < i;j++)
			b[i][0] = b[i][0]-A[i][j]*y[j][0];
			y[i][0] = b[i][0];
	}
		
	cout << "输出Ly=b的解y：" <<endl;
	y.print();
	
	
	//求解方程组Ux=y.
	Matrix x(2,1,0.0);
	int x_solve;
	x_solve = m_size - 1;
	x[x_solve][0]= y[x_solve][0]/A[x_solve][x_solve];
	for (int i = x_solve-1;i>=0;i--)
	{
		for (int j = x_solve;j >= 0;j--)
			y[i][0] = y[i][0]-A[i][j]*x[j][0];
		x[i][0] = y[i][0]/A[i][i];
		
	}
	
	cout << "此方程组的答案为:" <<endl;	
	x.print();
	
	
	
	return 0;
}
