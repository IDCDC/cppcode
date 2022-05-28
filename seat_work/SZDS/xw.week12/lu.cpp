#include <iostream>

#include "include/algebra/Algebra_kernel.h"
using namespace std;
typedef typename WHYSC::Algebra_kernel<double, int> Kernel;
typedef typename Kernel::Matrix Matrix;
typedef typename Kernel::Vector Vector;

int main(int argc, char **argv)
{
    Matrix M{{16,4,4},{4,17,5},{4,5,18}};
//    Matrix M{{1,0,0},{0,1,0},{0,0,1}};
//	Matrix M{{1,0},{0,1}};
//	Matrix M{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    Vector b{24,26,27};

    std::cout << "M:\n" << M << std::endl;
    std::cout << "b:\n" << b << std::endl;

    auto n = M.shape[0];
    Matrix L(n, n);
    Matrix U(n, n);
    Vector y(n);
    Vector x(n);

    //为了提高效率，我们只选择一个算法来进行演示。

    std::cout << "算法2为一般的LU算法" << std::endl; 
    std::cout << "算法3为KIJ型LU算法" << std::endl;  
    std::cout << "算法4为IKJ型LU算法" << std::endl;
    std::cout << "算法5为待定系数法的LU算法" << std::endl;
    std::cout << "算法6为求解线性方程组ly=b,ux=y" << std::endl;  
    std::cout << "算法7为部分主元的LU算法" << std::endl;  
    std::cout << "算法8为cholesky的LU算法" << std::endl; 
    
    int number;
    std::cout << "请告诉我你想选用的算法编号,例如2" << std::endl;
    std::cin >> number;
    
    if (number == 2)
    	Kernel::lu_normal(M, L, U);
    else if (number == 3)
   	Kernel::lu_kij(M, L, U);
    else if (number == 4)
        Kernel::lu_ikj(M, L, U);
    else if (number == 5)
    	Kernel::lu_uc(M, L, U);
    else if (number == 7)
    	Kernel::lu_pp(M, L, U);
    else
    	Kernel::lu_cholesky(M, L, U);  

    Kernel::ly_b(L, y ,b);
    Kernel::ux_y(U, x ,y);
//在输出矩阵时，算法8输出的U矩阵为L矩阵的转置
    std::cout << "M:\n" << M << std::endl;
    std::cout << "L:\n" << L << std::endl;
    std::cout << "U:\n" << U << std::endl;
    std::cout << "y:\n" << y << std::endl;
    std::cout << "x:\n" << x << std::endl;


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
