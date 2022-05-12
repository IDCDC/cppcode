/*
 * 幂迭代算法
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

vector<vector<double>> input_matrix();
void show(vector<vector<double>> &V);
void power_interation(vector<vector<double>> &A);

int main()
{
	vector<vector<double>> A;
	A = input_matrix();
	show(A);
	power_interation(A);
	return 0;
}

vector<vector<double>> input_matrix()
{// 这个函数是用来生成矩阵
	int n;
	
	char choice;
	cout << "是否输入矩阵，y 代表用户输入矩阵，n 代表使用默认矩阵!" <<endl;
	cin >> choice;
	if(choice == 'n')
	{
		n = 4;	
	}
	else
	{
		cout << "请输入矩阵维数：" << endl;
		cin >> n;
	}

	vector<vector<double>> M(n, vector<double>(n,0));
	if(choice == 'n')
	{
		M = {{8, 2, 0, 0},
			 {2, 5,-1, 0},
			 {0, 1, 4, 0},
			 {0, 0, 0, 6}};
	}
	else
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				cin >> M[i][j];
			}
		}
	}
	return M;
}


void show(vector<vector<double>> &V)
{// 这是一个输出矩阵元素的函数
	for (int i=0; i<(int)V.size(); i++)
	{
		for (int j=0; j<(int)V[0].size(); j++)
		{
			cout << V[i][j] << " ";
		}
		cout << endl;
	}	
}

void power_interation(vector<vector<double>> &A)
{// 幂迭代函数
	int n = (int)A.size();      // 矩阵大小
	vector<double> x0(n, 0);    // 迭代向量，最后存储误差向量
	vector<double> x1(n, 0);    // 迭代向量，最后存储特征向量
	vector<double> x2(n, 0);	// 迭代向量，最后存储特征值
	double er=1;				// 误差
	int iter = 0;				// 迭代步数

	for (int i=0; i<n; i++)
	{// 初始化迭代向量
		x0[i] = i;
		x1[i] = 1;
	}
	
	while ( er > 1e-10)
	{
		for (int i=0; i<n; i++)
		{// 寄存上一步迭代向量结果
			x2[i] = x1[i];
		}
		
		for (int i=0; i<n; i++)
		{// A @ x1
			x1[i] = 0;
			for (int j=0; j<n; j++)
			{
				x1[i] += A[i][j] * x0[j];
			}
		}
		double max = *max_element(x1.begin(), x1.end());
		for (int i=0; i<n; i++)
		{
			x1[i] /= max;  // 标准化
			x0[i] = x2[i]; 
		}
		er = 0; // 误差初始化
		for (int i=0; i<n; i++)
		{
			er += (x1[i]-x0[i]) * (x1[i]-x0[i]);
		}
		er = abs(er);
		er = sqrt(er);

		iter++;
		if (iter > 10000)
		{// 避免迭代次数过多
			cout << "迭代不收敛！" << endl;
			return ;
		}
	}
	
	cout << "迭代步数为：" << iter << endl;
	
	cout << "特征向量是：[";
	for (int i=0; i<n; i++)
	{
		cout << x1[i] << " ";
	}
	cout << "]" << endl;

	cout << "lambda: [";
	for (int i=0; i<n; i++)
	{
		x2[i] = 0;
		for (int j=0; j<n; j++)
		{
			x2[i] += A[i][j] * x1[j];
		}
		x0[i] = x2[i] / x1[i];
		cout << x0[i] << " ";
	}
	cout << "]" << endl;

	double lamb = *max_element(x0.begin(), x0.end());
	cout << "特征值是：" << lamb << endl;
	
	cout << "误差向量 Ax-lambda*x：[";
	for (int i=0; i<n; i++)
	{
		cout << lamb * x1[i] - x2[i] << " ";
	}
	cout << "]" << endl;
	
	return ;
}
