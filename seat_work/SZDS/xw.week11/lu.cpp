#include <iostream>

#include "include/algebra/Algebra_kernel.h"
using namespace std;
typedef typename WHYSC::Algebra_kernel<double, int> Kernel;
typedef typename Kernel::Matrix Matrix;
typedef typename Kernel::Vector Vector;

int main(int argc, char **argv)
{
    Matrix M{{1,2,3},{2,5,2},{3,1,5}};

    std::cout << "M:\n" << M << std::endl;

    auto n = M.shape[0];
    Matrix L(n, n);
    Matrix U(n, n);


    //为了提高效率，我们只选择一个算法来进行演示。
  
    int number;
    std::cout << "请告诉我你想选用的算法编号,例如算法2" << std::endl;
    std::cin >> number;
    
    if (number == 2)
    	Kernel::lu2(M, L, U);
    else if (number == 3)
   	Kernel::lu3(M, L, U);//此算法显示段错误（核心已转储）
    else if (number == 4)
        Kernel::lu4(M, L, U);
    else if (number == 5)
    	Kernel::lu5(M, L, U);
    else
    	Kernel::lu7(M, L, U);//此算法显示段错误（核心已转储）  	
    std::cout << "M:\n" << M << std::endl;
    std::cout << "L:\n" << L << std::endl;
    std::cout << "U:\n" << U << std::endl;

    Matrix C = L*U;

    std::cout << C << std::endl;

    Matrix A{{1,2,3},{2,5,2},{3,1,5}};
    Matrix E = C - A;
    std::cout << "E.norm:" << E.norm() << std::endl;

    Vector v = {1, 1, 1};
    v.print();
    std::cout << v.norm() << std::endl;

    return 0;
}
