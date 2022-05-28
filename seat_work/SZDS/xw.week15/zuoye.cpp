#include <iostream>
#include <cmath>
#include <fstream>//ofstream类的头文件
#include "algebra/Algebra_kernel.h"
#include "Constants.h"

typedef typename WHYSC::Algebra_kernel<double, int> Kernel;
typedef typename Kernel::Matrix Matrix;
typedef typename Kernel::Vector Vector;
typedef typename Kernel::CSRMatrix CSRMatrix;

using namespace std;

int main(int argc, char **argv)
{
    int n;
    std::cin >> n;
    int N = n*n;
    double h = 1.0/(n+1);

    CSRMatrix A;
    Kernel::laplace_2d(N, A);

    Vector b(N);
    Vector x(N);
    Vector u(N);

    double pi = WHYSC::Constants::pi;
    double w;
    w = 2/(1 + std::sin(pi/(n+1)));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            double x = (i+1)*h;
            double y = (j+1)*h;
            u[i*n+j] = (x*x+y*y)/4;
            b[i*n+j] = -1*h*h;
        }
    
    //加一个边界处理
    for(int j = 0; j < n; j++)
    {
    	double y = (j+1)*h;
    	b[j] += y*y/4;
    }
    for(int j = 0; j < n; j++)
    {
    	double y = (j+1)*h;
    	b[N-n+j] += (1+y*y)/4;
    }
    for(int i = 0; i < n; i++)
    {
    	double x = (i+1)*h;
    	b[i*n] += x*x/4;
    }
    for(int i = 0; i < n; i++)
    {
    	double x = (i+1)*h;
    	double y = (n-1)*h;
    	b[(i+1)*n-1] += (x*x+1)/4;
    }


    std::cout << b << std::endl;
    std::cout << "请输入数字,1:Jacobi;2:Gauss-Seidel;3:SOR" << std::endl;
    int number;
    std::cin >> number;
    if(number == 1)
        A.jacobi(b, x, 100000);//Jacobi迭代
    else if(number == 2) 
        A.GS(b, x, 100000);//GS
    else
        A.SOR(b, x, w, 100000);//SOR迭代
    

    double e = (u - x).maxnorm();
    std::cout << "error: " << e << std::endl;
    
    ofstream mycout("Empirical data.txt");
    mycout << "x" << x <<endl;
    mycout << "u" << u <<endl;
    mycout << "b" << b <<endl;
    mycout << "e" << e <<endl;
    mycout.close();


    return 0;
}
