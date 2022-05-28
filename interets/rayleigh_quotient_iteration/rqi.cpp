/*
 * 幂迭代算法
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

vector<vector<double>> input_matrix();
void show(vector<vector<double>> &V);
vector<vector<double>> inverse_matrix(vector<vector<double>> &V);
void inverse_iteration(vector<vector<double>> &Mat);

int main()
{
	vector<vector<double>> A;
	A = input_matrix();
	show(A);
	inverse_iteration(A);
	return 0;
}

vector<vector<double>> input_matrix()
{// 这个函数是用来生成矩阵
	int n;
	// system("chcp 65001");  解决中文输出为乱码
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
	}// 默认值
	else
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				cin >> M[i][j];
			}
		}
	}// 自定义矩阵
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


vector<vector<double>> inverse_matrix(vector<vector<double>> &V)
{// 这是一个生成逆矩阵的函数
	int n = (int)V.size();
	vector<vector<double>> V_inv(n, vector<double>(n,0));
	MatrixXd M(n, n);
	MatrixXd M_inv(n, n);

	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			M.row(i).col(j) << V[i][j];
		}
	}// 将 vector 转化为 Eigen 格式
	
	M_inv = M.inverse(); // 求逆
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			V_inv[i][j] = M_inv(i, j);
		}
	}// 将 Eigen 转化为 vector 格式
	return V_inv;
}

void inverse_iteration(vector<vector<double>> &Mat)
{// 反迭代算法
	int n = (int)Mat.size();    // 矩阵大小
	int iter = 0;				// 迭代步数
	double sigma;				// 位移
	double er=1;				// 误差
	double mu;					// 特征值
	vector<double> x0(n, 0);    // 迭代向量，最后存储误差向量
	vector<double> x1(n, 0);    // 迭代向量，最后存储特征向量
	vector<vector<double>> A_sig(n, vector<double>(n,0));
	vector<vector<double>> A_sig_inv(n, vector<double>(n,0));

	cout << "请输入合适的 sigma 的值：" << endl;
	cin >> sigma;

	
	double ele = sqrt(n);
	for (int i=0; i<n; i++)
	{// 初始化迭代向量
		x1[i] = ele;
	}
	
	while ( er > 1e-8)
	{
		for (int i=0; i<n; i++)
		{// 存储上一步结果
			x0[i] = x1[i];
		}
	
		for (int i=0; i<n; i++)
		{
			for (int j=0; j<n; j++)
			{
				A_sig[i][j] = Mat[i][j];
			}
			A_sig[i][i] -= sigma;
		}

		A_sig_inv = inverse_matrix(A_sig);
	
		for (int i=0; i<n; i++)
		{// A_sig_inv @ x1
			x1[i] = 0;
			for (int j=0; j<n; j++)
			{
				x1[i] += A_sig_inv[i][j] * x0[j];
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

		sigma = mu;
		cout << "sigma: " << sigma << endl;
		iter++;
		if (iter > 1e4)
		{// 避免迭代次数过多
			cout << "迭代不收敛！" << endl;
			return ;
		}
		cout << "sigma: " << sigma << endl;
		er = abs(mu-mu0);
		cout << "er: " << er << endl;
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
