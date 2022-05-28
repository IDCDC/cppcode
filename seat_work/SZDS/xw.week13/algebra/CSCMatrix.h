#ifndef CSCMatrix_h
#define CSCMatrix_h

#include <iostream>
#include <cmath>
#include <initializer_list>
#include <cassert>

#endif // end of CSCMatrix_h

namespace WHYSC {
namespace AlgebraObject {


template<typename F=double, typename I=int>
struct CSCMatrix
{
    typedef F Float;
    typedef I Int;

    F *data; // 非零元数组
    I *indices; // 非零元对应行指标数组
    I *indptr; // 非零元起始位置数组
    I shape[2]; // 矩阵的阶数
    I nnz; // 非零元的个数

//初始化
    CSCMatrix()
    {
        data = NULL;
        indices = NULL;
        indptr = NULL;
        shape[0] = 0;
        shape[1] = 0;
        nnz = 0;
    }

    template<typename Vector> 
    CSCMatrix(Vector & d, Vector & idx, Vector & idxp, I nrow, I ncol)
    {
        shape[0] = nrow;
        shape[1] = ncol;
        nnz = d.size();

        data = new F[nnz];
        indices = new I[nnz];
        indptr = new I[nrow + 1];

        for(auto i=0; i < nnz; i++)
        {
            data[i] = d[i];
            indices[i] = idx[i];
        }

        for(auto i=0; i < nrow+1; i++)
        {
            indptr[i] = idxp[i];
        }
    }

//对矩阵进行存储
    template<typename Matrix> 
    CSCMatrix(Matrix & m)
    {
        shape[0] = m.shape[0];
        shape[1] = m.shape[1];
        nnz = 0;
        for(auto i=0; i < shape[1]; i++)
        {
            for(auto j=0; j < shape[0]; j++)
            {
                if( m[i][j] != 0)
                    nnz++;
            }
        }

        data = new F[nnz];
        indices = new I[nnz];
        indptr = new I[shape[0] + 1];
        indptr[shape[0]] = nnz;
        auto c = 0;
        for(auto i=0; i < shape[1]; i++)
        {
            indptr[i] = c;
            for(auto j=0; j < shape[0]; j++)
            {
                if( m[j][i] != 0)
                {
                    data[c] = m[j][i];
                    indices[c] = j;
                    c++;
                }
            }
        }
    }

    F operator() (const I j, const I i)
    {
        for(auto k = indptr[j]; k < indptr[j+1]; k++)
        {
            if(indices[k] == i)
            {
                return data[k];
            }
        }
        return 0.0;
    }

    ~CSCMatrix()
    {
        if(data != NULL)
            delete [] data;

        if(indices != NULL)
            delete [] indices;

        if(indptr != NULL)
            delete [] indptr;
    }
};

//矩阵乘向量
template<typename F, typename I, typename Vector>
inline Vector operator * (const CSCMatrix<F, I> & m, 
        const Vector & v0)
{
    assert( m.shape[1] == v0.size );
    Vector v1(m.shape[0], 0.0);
    for(auto i = 0; i < m.shape[0]; i++)
    {
     	for(auto j = 0;j <= m.shape[1];j++)
        {
              for(auto h = m.indptr[j]; h < m.indptr[j+1]; h++)
              {
                   if(i == m.indices[h])
        		v1[i] += m.data[h]*v0[j];
              }	
        }
    }
    return v1;
}

//向量乘矩阵
template<typename F, typename I, typename Vector>
inline Vector operator * (const Vector & v0, 
        const CSCMatrix<F, I> & m)
{
    assert( m.shape[0] == v0.size );
    Vector v1(m.shape[1], 0.0);
    for(auto i = 0; i < m.shape[1]; i++)
    {
        for(auto k = m.indptr[i]; k < m.indptr[i+1]; k++)
        {
            auto j = m.indices[k]; 
            v1[i] += v0[j]*m.data[k];
        }
    }
    return v1;
}

//输出矩阵中不为0的元素
template<typename F, typename I>
std::ostream& operator << (std::ostream & os, const CSCMatrix<F, I> & m)
{
    std::cout << "CSCMatrix("<< m.shape[0] << ","
        << m.shape[1] << "):" << std::endl;

    for(auto i = 0; i < m.shape[1]; i++)
    {
        for(auto j = m.indptr[i]; j < m.indptr[i+1]; j++)
        {
            os << "(" << m.indices[j] << ", " << i << 
                ") " << m.data[j] << std::endl;
        }
    }
    os << "\n";
    return os;
}

} // end of namespace AlgebraObject
} // end of namespace WHYSC
