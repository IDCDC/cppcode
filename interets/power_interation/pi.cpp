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
void power_interation(vector<vector<double>> &Mat);

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

void power_interation(vector<vector<double>> &Mat)
{// 幂迭代函数
	int n = (int)Mat.size();      // 矩阵大小
	vector<double> x0(n, 0);    // 迭代向量，最后存储误差向量
	vector<double> x1(n, 0);    // 迭代向量，最后存储特征向量
	vector<double> x2(n, 0);	// 迭代向量，最后存储特征值
	double er=1;				// 误差
	double mu;
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
				x1[i] += Mat[i][j] * x0[j];
			}
		}
		double norm=0;
		for (int i=0; i<n; i++)
		{
			norm += x1[i] * x1[i];
		}
		norm = pow(norm, 0.5);
		for (int i=0; i<n; i++)
		{
			x1[i] /= norm;  
		}  // 标准化
		
		for (int i=0; i<n; i++)
		{
			x0[i] = 0;
			for (int j=0; j<n; j++)
			{
				x0[i] += Mat[i][j] * x1[j]; 
			}
		}

		double mu0 = mu; // 存储上一步特征值
		mu = 0.0;        // 初始化
		for (int i=0; i<n; i++)
		{
			mu += x0[i] * x1[i];	
		} // 计算特征值

		iter++;
		if (iter > 1e4)
		{// 避免迭代次数过多
			cout << "迭代不收敛！" << endl;
			return ;
		}

		er = abs(mu-mu0);
	}
	
	cout << "迭代步数为：" << iter << endl;
	
	cout << "特征向量是：[";
	for (int i=0; i<n; i++)
	{
		cout << x1[i] << " ";
	}
	cout << "]" << endl;

	cout << "特征值是：" << mu << endl;
	
	cout << "误差向量 Ax-lambda*x：[";
	for (int i=0; i<n; i++)
	{
		cout << mu * x1[i] - x0[i] << " ";
	}
	cout << "]" << endl;

	cout << "lamb: [";
	for (int i=0; i<n; i++)
	{
		cout << x0[i] / x1[i] << " ";
	}
	cout << "]" << endl;

	return ;	
}
