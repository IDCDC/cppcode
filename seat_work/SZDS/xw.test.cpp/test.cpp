#include <iostream>
#include <cmath>
#include "algebra/Algebra_kernel.h"
#include "Constants.h"

using namespace std;
namespace plt = matplotlibcpp;

typedef typename WHYSC::Algebra_kernel<double, int> Kernel;
typedef typename Kernel::Matrix Matrix;
typedef typename Kernel::Vector Vector;
typedef typename Kernel::CSRMatrix CSRMatrix;

int main(int argc, char **argv)
{
    int n,N;
    double h;
    std::cout << "请输入你要选择的步长" << std::endl;
    std::cin >> h;    
    
    n = 1/h - 1;                    //n为一个x负轴上插入的节点个数
    N = 3*n*n+2*n;                  //N为插入的总节点个数
        
    CSRMatrix A;
    Kernel::laplace_2d1(N, n, A);
    
    Vector b(N);                    //b为右端项
    Vector u(N);                    //u为真解
    Vector x1(N),x2(N),x3(N);       //x1,x2,x3分别用于Jacobi、GS、CG迭代

    double pi = WHYSC::Constants::pi;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            //第二象限
            double x = (i-n)*h;
            double y = (j+1)*h;
            u[i*(2*n+1)+ n+1+ j] = std::sin(pi*x)*std::sin(pi*y);
            b[i*(2*n+1)+ n+1+ j] = 2*h*h*pi*pi*u[i*(2*n+1)+ n+1+ j];
            
            //第三象限
            x = (i-n)*h;
            y = (j-n)*h;
            u[i*(2*n+1) + j] = std::sin(pi*x)*std::sin(pi*y);
            b[i*(2*n+1) + j] = 2*h*h*pi*pi*u[i*(2*n+1) + j];
            
            //第四象限
            x = (i+1)*h;
            y = (j-n)*h;
            u[(2*n+2+i)*n+j] = std::sin(pi*x)*std::sin(pi*y);
            b[(2*n+2+i)*n+j] = 2*h*h*pi*pi*u[(2*n+2+i)*n+j];          
        }
     }
  
    A.jacobi(b, x1, u, 100000);      //Jacobi迭代
    A.GS(b, x2, u, 100000);          //GS
    A.CG(b, x3, u, 100);             //CG迭代

    plt::xlabel("steps");
    plt::ylabel("parameter");
    plt::show();

    return 0;
}
