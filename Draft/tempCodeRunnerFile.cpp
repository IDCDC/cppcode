#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int main()
{
    Matrix3d Mat1;
    Mat1 << 1, 2, 3,
        4, 6, 8,
        7, 9, 9;
    cout << "Mat1=\n" << Mat1 << endl;
    cout << "Mat1转置矩阵：\n" << Mat1.transpose() << endl;
    cout << "Mat1伴随矩阵：\n" << Mat1.adjoint() << endl;
    cout << "Mat1逆矩阵：\n" << Mat1.inverse() << endl;
    cout << "Mat1行列式：\n" << Mat1.determinant() << endl;
    SelfAdjointEigenSolver<Matrix3d>eigensover(Mat1);
    if (eigensover.info() != Success) abort();
    cout << "特征值：\n" << eigensover.eigenvalues() << endl;
    cout << "特征向量：\n" << eigensover.eigenvectors() << endl;
}
