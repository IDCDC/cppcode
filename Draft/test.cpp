
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

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

void minus_mat(vector<vector<double>> A)
{
	cout << "first show A: " << endl;
	show(A);
	A[0][0] -= 4;
	cout << "Second show A: " << endl;
	show(A);
}
int main()
{
	vector<vector<double>> M;
	M = {{8, 2, 0, 0},
		 {2, 5,-1, 0},
		 {0, 1, 4, 0},
		 {0, 0, 0, 6}};
	cout << "First show M: " << endl;
	show(M);
	
	minus_mat(M);
	cout << "Second show M: " << endl;
	show(M);
	return 0;
}


