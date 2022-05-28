#ifndef CSRMatrix_h
#define CSRMatrix_h

#include <iostream>
#include <cmath>
#include <initializer_list>
#include <cassert>
#include <string>
#include <algorithm>
#include "Vector.h"
#include "thirdparty/matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

namespace WHYSC {
namespace AlgebraObject {

template<typename F=double, typename I=int>
struct CSRMatrix
{
    typedef F Float;
    typedef I Int;

    F * data; // 非零元数组
    I * indices; // 非零元对应列指标数组
    I * indptr; // 非零元行起始位置数组
    I shape[2]; // 矩阵的阶数
    I nnz; // 非零元的个数

    static std::string format; // format = "csr"

    /*
     *
     * Notes
     * -----
     *  生成一个空稀疏矩阵.
     *
     */
    CSRMatrix()
    {
        data = NULL;
        indices = NULL;
        indptr = NULL;
        shape[0] = 0;
        shape[1] = 0;
        nnz = 0;
    }

    /*
     *
     * Notes
     * -----
     *  生成一个有 n 个非零元的稀疏矩阵, 形状为 (nrow, ncol)
     *  
     */

    CSRMatrix(
            const I nrow, 
            const I ncol, 
            const I nnz_, 
            const I row[], 
            const I col[], 
            const F data_[])
    {
        from_coo(nrow, ncol, nnz_, row, col, data_);
    }

    void from_coo(
            const I nrow,
            const I ncol,
            const I nnz_,
            const I row[],
            const I col[],
            const F data_[])
    {
        clear();
        nnz = nnz_;
        shape[0] = nrow;
        shape[1] = ncol;

        // 分配内存空间
        data = new F[nnz];
        indices = new I[nnz];
        indptr = new I[shape[0] + 1];

        std::fill(indptr, indptr + shape[0], 0);

        // 计算每一行非零元的个数 
        for(I n = 0; n < nnz; n++)
        {
            indptr[row[n]]++;
        }


        for(I i=0, cumsum =0; i < shape[0]; i++)
        {
            I temp = indptr[i];
            indptr[i] = cumsum;
            cumsum += temp;
        }
        indptr[shape[0]] = nnz;

        for(I n = 0; n < nnz; n++)
        {
            I i = row[n];
            I k = indptr[i];

            indices[k] = col[n];
            data[k] = data_[n];

            indptr[i]++;
        }

        for(I i = 0, last = 0; i <= shape[0]; i++)
        {
            I temp = indptr[i];
            indptr[i] = last;
            last = temp;
        }
    }


    template<typename Matrix> 
    CSRMatrix(Matrix & m)
    {
        shape[0] = m.shape[0];
        shape[1] = m.shape[1];
        nnz = 0;
        for(auto i=0; i < shape[0]; i++)
        {
            for(auto j=0; j < shape[1]; j++)
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
        for(auto i=0; i < shape[0]; i++)
        {
            indptr[i] = c;
            for(auto j=0; j < shape[1]; j++)
            {
                if( m[i][j] != 0)
                {
                    data[c] = m[i][j];
                    indices[c] = j;
                    c++;
                }
            }
        }
    }

    const F operator() (const I i, const I j) const
    {
        for(auto k = indptr[i]; k < indptr[i+1]; k++)
        {
            if(indices[k] == j)
            {
                return data[k];
            }
        }
        return 0.0;
    }

    void clear()
    {
        shape[0] = 0;
        shape[1] = 0;
        nnz = 0;
        if(data != NULL)
            delete [] data;

        if(indices != NULL)
            delete [] indices;

        if(indptr != NULL)
            delete [] indptr;
    }

    ~CSRMatrix()
    {
        if(data != NULL)
            delete [] data;

        if(indices != NULL)
            delete [] indices;

        if(indptr != NULL)
            delete [] indptr;
    }
    
    //Jacobi迭代
    template<typename Vector>
    void jacobi(Vector & b, Vector & x, Vector & u,I maxit=1000, F tol=1e-8)
    {
        F d = 0.0;                                   //定义所需变量与向量
        F bnorm = b.norm();                          //r = b-Ax  残量
        F rnorm = 0.0;                               //rnorm取其二范数
        I m,steps;                                   //m为迭代次数,steps为最终迭代次数
        Vector x1(x.size);                           //x1为转换向量
        Vector step(maxit),norm(maxit);              //step，norm代表迭代次数与r范数的两个数组
        for(m=0; m < maxit; m++)
        {
            for(I i=0; i < x.size; i++)
            {
                x1[i] = b[i];
                for(I k=indptr[i]; k < indptr[i+1]; k++)
                {
                    if(indices[k] == i)
                        d = data[k];
                    else
                        x1[i] -= data[k]*x[indices[k]];
                }
                x1[i] /= d;
            }

            for(I i=0; i< x.size; i++)
            {
                x[i] = x1[i];
            }

            Vector r = b - (*this)*x;
            rnorm = r.norm();
            step[m] = m;
            norm[m] = rnorm;
            if( rnorm < tol*bnorm)
                break;
            steps = m; 
        }
        std::cout << "Jacobi最大迭代次数与b-Ax的范数" << m+1 << ": " << rnorm << std::endl;
        double e = (u - x).maxnorm();
        std::cout << "error: " << e << std::endl;
        
        vector<double> x_axis(steps),y_axis(steps);      //残量与迭代次数的画图
        for(int m = 0; m < steps; m++)
        {
            x_axis.at(m) = step[m];
            y_axis.at(m) = norm[m];
        }
        plt::plot(x_axis, y_axis, "r--");
    }
    
    //Gauss-Seidel迭代
    template<typename Vector>
    void GS(Vector & b, Vector & x, Vector & u, I maxit=10000, F tol=1e-8)
    {
        F d = 0.0;                                //定义所需变量与向量
        I m,steps;                                //m为迭代次数,steps为最终迭代次数
        F rnorm = 0.0;                            //rnorm取其二范数
        F bnorm = b.norm();                       //r = b-Ax  残量
        Vector step(maxit),norm(maxit);           //step,norm代表迭代次数与r范数的两个数组        
        Vector x1(x.size);
        for(m=0; m < maxit; m++)
        {   
            for(I i=0; i < x.size; i++)
            {
                x1[i] = b[i];
                for(I k=indptr[i]; k < indptr[i+1]; k++)
                {
                    if(indices[k] == i)
                        d = data[k];
                    else
                        x1[i] -= data[k]*x[indices[k]];
                }
                x1[i] /= d;
                x[i] = x1[i];
            }

            Vector r = b - (*this)*x;
            rnorm = r.norm();
            step[m] = m;
            norm[m] = rnorm;
            
            if( rnorm < tol*bnorm)
                break;
            steps = m;

        }
        std::cout << "GS最大迭代次数与b-Ax的范数"<< m+1 << ": " << rnorm << std::endl;
        double e = (u - x).maxnorm();
        std::cout << "error: " << e << std::endl;
        
        vector<double> x_axis(steps),y_axis(steps);      //残量与迭代次数的画图                  
        for(int m = 0; m < steps; m++)
        {
            x_axis.at(m) = step[m];
            y_axis.at(m) = norm[m];
        }
        plt::plot(x_axis, y_axis, "y--");
    }  

    //CG迭代    
    template<typename Vector>
    void CG(Vector & b, Vector & x, Vector & u, I maxit=100, F tol=1e-8)
    {
        Vector r0 = b - (*this)*x;                    //r = b-Ax  残量
        F beta = r0.norm();                                  
        F bnorm = b.norm();
        if(beta < tol*bnorm)
            return;
               
        F rho, rho0, mu, kaxi, rnorm;                 //定义所需变量与向量
        I m,steps;
        Vector r(x.size);                                    
        Vector x1(x.size);        
        Vector p(x.size),p1(x.size);      
        Vector step(maxit),norm(maxit);               //step,norm代表迭代次数与r范数的两个数组    
       
        for(m=0; m < maxit; m++)
        {
            rho = 0;                                  //初始化
            kaxi = 0;
            rho = r0*r0;    
            if(m > 0)
            {
                mu = rho/rho0;
                for(I i=0; i < x.size; i++)
                    p1[i] = r0[i] + mu*p[i];
            }
            else
            {
                for(I i=0; i < x.size; i++)
                    p1[i] = r0[i];
            }
            
            Vector q = (*this)*p1;
            // kaxi = p1 * q;                        //Vector.h文件中写了一个向量的乘法,但是运行结果不稳定          
            for(I i=0; i < x.size; i++)
            {
                kaxi += p1[i] * q[i];
            }
            
            kaxi = rho/kaxi;
            
            for(I i=0; i < x.size; i++)
            {
                x1[i] = x[i] + kaxi*p1[i];
                r[i] = r0[i] - kaxi*q[i];
            }
            
            steps = m;                                               
            step[m] = m;                                            
            rnorm = r.norm();
            norm[m] = rnorm;                                        
            rho0 = rho; 
            
            for(I i=0; i < x.size; i++)                          
            {
                p[i] = p1[i];
                x[i] = x1[i];
                r0[i] = r[i];               
            }
            if(rnorm < tol*bnorm)                                
                break;                      
        }

        std::cout << "CG最大迭代次数与b-Ax的范数" << m+1 << ": " << rnorm << std::endl;
        double e = (u - x).maxnorm();
        std::cout << "error: " << e << std::endl;
 
        vector<double> x_axis(steps),y_axis(steps);             //残量与迭代次数的画图
        for(m = 0; m < steps; m++)
        {
            x_axis.at(m) = step[m];
            y_axis.at(m) = norm[m];
        }
        plt::plot(x_axis, y_axis, "b--");
    } 
    
    template<typename Vector>
    void gauss_seidel_forward(Vector & b, Vector & x, I maxit=100, F tol=1e-8)
    {
        F d = 0.0;
        F bnorm = b.norm();
        for(I m=0; m < maxit; m++)
        {
             for(I i=0; i < x.size; i++)
             {
                x[i] = b[i];
                for(I k = indptr[i]; k < indptr[i+1]; k++)
                {
                    if (indices[k]==i)
                        d = data[k];
                    else
                       x[i] -= data[k]*x[indices[k]];
                }

                x[i] /= d;
            }


            Vector r = b - (*this)*x;
            F rnorm = r.norm();
            std::cout << m << ": " << rnorm << std::endl;
            if( rnorm < tol*bnorm)
                break;
        }
    }  

    template<typename Vector>
    void gauss_seidel_backward(Vector & b, Vector & x, I maxit=100, F tol=1e-8)
    {
        F d = 0.0;
        F bnorm = b.norm();
        for(I m=0; m < maxit; m++)
        {
             for(I i = x.size-1; i > -1; i--)
             {
                x[i] = b[i];
                for(I k = indptr[i]; k < indptr[i+1]; k++)
                {
                    if (indices[k]==i)
                        d = data[k];
                    else
                       x[i] -= data[k]*x[indices[k]];
                }

                x[i] /= d;
            }


            Vector r = b - (*this)*x;
            F rnorm = r.norm();
            std::cout << m << ": " << rnorm << std::endl;
            if( rnorm < tol*bnorm)
                break;
        }
    }
         
};

//矩阵乘向量
template<typename F, typename I, typename Vector>
inline Vector operator * (const CSRMatrix<F, I> & m, 
        const Vector & v0)
{
    assert( m.shape[1] == v0.size );
    Vector v1(m.shape[0], 0.0);
    for(auto i = 0; i < m.shape[0]; i++)
    {
        for(auto k = m.indptr[i]; k < m.indptr[i+1]; k++)
        {
            auto j = m.indices[k]; 
            v1[i] += m.data[k]*v0[j];
        }
    }
    return v1;
}

//向量乘矩阵
template<typename F, typename I, typename Vector>
inline Vector operator * (const Vector & v0, 
        const CSRMatrix<F, I> & m)
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


template<typename F, typename I>
std::string CSRMatrix<F, I>::format = "csr";


template<typename F, typename I>
std::ostream& operator << (std::ostream & os, 
        const CSRMatrix<F, I> & m)
{
    std::cout << "CSRMatrix("<< m.shape[0] << ","
        << m.shape[1] << "):" << std::endl;

    for(auto i = 0; i < m.shape[0]; i++)
    {
        for(auto j = m.indptr[i]; j < m.indptr[i+1]; j++)
        {
            os << "(" << i << ", " << m.indices[j] << 
                ") " << m.data[j] << std::endl;
        }
    }
    os << "\n";
    return os;
}

} // end of namespace AlgebraObject
} // end of namespace WHYSC

#endif // end of CSRMatrix_h
