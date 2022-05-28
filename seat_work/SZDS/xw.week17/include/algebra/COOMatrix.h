#ifndef COOMatrix_h
#define COOMatrix_h

#include <iostream>
#include <cmath>
#include <initializer_list>
#include <cassert>

#endif // end of COOMatrix_h

namespace WHYSC {
namespace AlgebraObject {


template<typename F=double, typename I=int>
struct COOMatrix
{
    typedef F Float;
    typedef I Int;

    F *data; // 非零元数组
    I *row; // 非零元对应行指标数组
    I *col; // 非零元起始位置数组
    I shape[2]; // 矩阵的阶数
    I nnz; // 非零元的个数

//初始化
    COOMatrix()
    {
        data = NULL;
        row = NULL;
        col = NULL;
        shape[0] = 0;
        shape[1] = 0;
        nnz = 0;
    }

    template<typename Vector> 
    COOMatrix(Vector & d, Vector & row1, Vector & col1, I nrow, I ncol)
    {
        shape[0] = nrow;
        shape[1] = ncol;
        nnz = d.size();

        data = new F[nnz];
        row = new I[nnz];
        col = new I[nnz];

        for(auto i=0; i < nnz; i++)
        {
            data[i] = d[i];
            row[i] = row1[i];
            col[i] = col1[i];
        }
    }

//对矩阵进行存储
    template<typename Matrix> 
    COOMatrix(Matrix & m)
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
        row = new I[nnz];
        col = new I[nnz];
        auto c = 0;
        for(auto i=0; i < shape[0]; i++)
        {
            for(auto j=0; j < shape[1]; j++)
            {
                if( m[i][j] != 0)
                    data[c] = m[i][j];
                    row[c] = i;
                    col[c] = j;
            }
        }
    }

//判断第i行第j列元素是否为0
    F operator() (const I i, const I j)
    {
        for(auto k = 0; k < data.size(); k++)
        {     
            if(row[k] == i && col[k] = j)
                return data[k];
        }
        return 0.0;
    }

    ~COOMatrix()
    {
        if(data != NULL)
            delete [] data;

        if(row != NULL)
            delete [] row;

        if(col != NULL)
            delete [] col;
    }
};

//矩阵乘向量
template<typename F, typename I, typename Vector>
inline Vector operator * (const COOMatrix<F, I> & m, 
        const Vector & v0)
{
    assert( m.shape[1] == v0.size );
    Vector v1(m.shape[0], 0.0);
    auto c = 0;
    for(auto k = 0; k < m.nnz; k++)
    {
        for(auto i = 0; i < m.shape[0]; i++)
        {
            if(m.row[k] = i)
            {
                c = m.col[k];
                v1[i] += m.data[k]*v0[c];
            }
        }
    }
    return v1;
}

//向量乘矩阵
template<typename F, typename I, typename Vector>
inline Vector operator * (const Vector & v0, 
        const COOMatrix<F, I> & m)
{
    assert( m.shape[0] == v0.size );
    Vector v1(m.shape[1], 0.0);
    auto c = 0;
    for(auto k = 0; k < m.nnz; k++)
    {
        for(auto j = 0; j < m.shape[1]; j++)
        {
            if(m.col[k] = j)
            {
                c = m.row[k];
                v1[j] += v0[c]*m.data[k];
            }
        }
    }
    return v1;
}

//输出矩阵中不为0的元素
template<typename F, typename I>
std::ostream& operator << (std::ostream & os, const COOMatrix<F, I> & m)
{
    std::cout << "COOMatrix("<< m.shape[0] << ","
        << m.shape[1] << "):" << std::endl;

    for(auto k = 0; k < m.nnz; k++)
    {
        os << "(" << m.row[k] << ", " << m.col[k] << 
                ") " << m.data[k] << std::endl;
    }
    os << "\n";
    return os;
}

} // end of namespace AlgebraObject
} // end of namespace WHYSC
