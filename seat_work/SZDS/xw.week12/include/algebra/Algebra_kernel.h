#ifndef AlgebraKernel_h
#define AlgebraKernel_h

#include "Matrix.h"
#include "Vector.h"
#include "linalg.h"

namespace WHYSC {

template<typename F=double, typename I=int>
class Algebra_kernel
{
public:
    typedef typename AlgebraObject::Matrix<F, I> Matrix;
    typedef typename AlgebraObject::Vector<F, I> Vector;
    
public:
    
    //算法2 一般的LU算法
    static void lu_normal(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_normal<Matrix>(A, L, U);
    }

    //算法3 KIJ算法
    static void lu_kij(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_kij<Matrix>(A, L, U);
    }

    //算法4 IKJ算法
    static void lu_ikj(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_ikj<Matrix>(A, L, U);
    }

    //算法5 待定系数法
    static void lu_uc(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_uc<Matrix>(A, L, U);
    }

    //算法7 部分主元LU分解
    static void lu_pp(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_pp<Matrix>(A, L, U);
    }
    
    //算法8：Cholesky 算法
    static void lu_cholesky(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu_cholesky<Matrix>(A, L, U);
    }
    
    //算法6：求解线性方程组ly=b,ux=y
    static void ly_b(Matrix & L, Vector & y, Vector & b)
    {
        return AlgebraAlgrithom::ly_b(L, y, b);
    }
    static void ux_y(Matrix & U, Vector & x, Vector & y)
    {
        return AlgebraAlgrithom::ux_y( U, x, y);
    }
};

} // end of namespace WHYSC
#endif // end of AlgebraKernel_h
