#ifndef AlgebraKernel_h
#define AlgebraKernel_h

#include "Matrix.h"
#include "CSRMatrix.h"
#include "CSCMatrix.h"
#include "COOMatrix.h"
#include "Vector.h"
#include "linalg.h"
#include "MatrixFactory.h"

namespace WHYSC {

template<typename F=double, typename I=int>
class Algebra_kernel
{
public:
    typedef typename AlgebraObject::Matrix<F, I> Matrix;
    typedef typename AlgebraObject::Vector<F, I> Vector;

    typedef typename AlgebraObject::CSRMatrix<F, I> CSRMatrix;
    typedef typename AlgebraObject::CSCMatrix<F, I> CSCMatrix;
    typedef typename AlgebraObject::COOMatrix<F, I> COOMatrix;
    //typedef AlgebraAlgrithom::lu<Matrix> lu;
public:
    static void lu(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu<Matrix>(A, L, U);
    }

    static void laplace_1d(const I n, CSRMatrix & m)
    {
        return AlgebraObject::laplace_1d(n, m);
    }

};

} // end of namespace WHYSC
#endif // end of AlgebraKernel_h
