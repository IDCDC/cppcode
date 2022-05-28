#include <iostream>

#include "algebra/Algebra_kernel.h"

typedef typename WHYSC::Algebra_kernel<double, int> Kernel;
typedef typename Kernel::Matrix Matrix;


int main(int argc, char **argv)
{
//    Matrix M = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix M = {{12, -51, 4}, {6, 167, -68},{12, -51, 4}, {6, 167, -68}};
//    Matrix M = {{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}};
 
    int m = M.shape[0];
    int n = M.shape[1];
    
    Matrix Q(m, m);
    Matrix R(m, n);

    int number;
    std::cout << "请告诉我你想要的算法" << "\n" << "1代表Gram-schmidit的QR分解"<< "\n" 
    << "2代表修正的Gram-schmidt的QR分解" << "\n" << "3代表householder的QR分解" << "\n" 
    << "4代表Givens的QR分解" <<std::endl;
    std::cin >> number;
    
    switch(number)
    {
        case 1:
        {
            Kernel::qr_gs(M, Q, R);
            break;
        }
        case 2:
        {
            Kernel::qr_gs(M, Q, R);
            break;
        }
        case 3:
        {
            Kernel::qr_hh(M, Q, R);
            break;
        }
        case 4:
        {
            Kernel::qr_givens(M, Q, R);
            break;
        }
    }
    
    std::cout << "M:\n" << M << std::endl;
    std::cout << "Q:\n" << Q << std::endl;
    std::cout << "R:\n" << R << std::endl;
    std::cout << "QR:\n" << Q*R << std::endl;
    return 0;
}
