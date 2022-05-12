#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

MatrixXf input_matrix();

int main()
{
	MatrixXf A;
	A.cast<double>();
	A = input_matrix();
	cout << "A: \n" << A << endl;
	return 0;
}

MatrixXf input_matrix()
{
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

	MatrixXf M(n, n);
	M.cast<double>();

	if(choice == 'n')
	{
		M << 8, 2, 0, 0,
			 2, 5,-1, 0,
			 0,-1, 4, 0,
		     0, 0, 0, 6;
	}
	else
	{
		double elem;
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				cin >>  elem;
				M(i,j) << elem;
			}
		}
	}
	return M;
}
