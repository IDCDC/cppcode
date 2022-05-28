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
    static void lu2(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu2<Matrix>(A, L, U);
    }

    static void lu3(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu3<Matrix>(A, L, U);
    }

    static void lu4(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu4<Matrix>(A, L, U);
    }


    static void lu5(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu5<Matrix>(A, L, U);
    }

    static void lu7(Matrix & A, Matrix & L, Matrix & U)
    {
        return AlgebraAlgrithom::lu7<Matrix>(A, L, U);
    }
};

} // end of namespace WHYSC
#endif // end of AlgebraKernel_h
