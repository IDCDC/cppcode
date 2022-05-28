#ifndef linalg_h
#define linalg_h

#include <iostream>
#include <initializer_list>
#include <math.h>
#include <cmath>

namespace WHYSC {
namespace AlgebraAlgrithom {


template<typename Matrix>
void lu(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    for(I k=0; k<n; k++)
	{
		for (I i=k+1; i<n; i++)
		{
			L[i][k] = A[i][k]/A[k][k];
		}

		for(I j=k; j<n; j++)
		{
			U[k][j] = A[k][j];
		}

		for(I i=k+1; i<n ;i++)
		{
			for(I j=k+1;j<n;j++)
			{
				A[i][j] -= L[i][k]*U[k][j];
			}
		}

	}

    for(I i=0;i<n;i++)
        L[i][i] = 1;

    return;
}

template<typename Matrix>
void lu_kij(Matrix & A)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    for(I k=0; k<n; k++)
	{
		for (I i=k+1; i<n; i++)
		{
			A[i][k] = A[i][k]/A[k][k];
		}

		for(I i=k+1; i<n ;i++)
		{
			for(I j=k+1;j<n;j++)
			{
				A[i][j] -= A[i][k]*A[k][j];
			}
		}

	}

    return;
}

template<typename Matrix>
void lu_ikj(Matrix & A)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    for(I i = 0;i < n; i++)
    	{
   		for(I k = 0;k < i; k++)
   		{
   			A[i][k]=A[i][k]/A[k][k];
   			for(I j = k + 1; j < n; j++)
   			{
   				A[i][j] -= A[i][k]*A[k][j];
   			}
   		}
    	}
    return;
}

template<typename Matrix>
void lu_kij(Matrix & A, Matrix & L, Matrix & U)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I n = A.shape[0];
    for(I k=0; k<n; k++)
	{
		for (I i=k+1; i<n; i++)
		{
			L[i][k] = A[i][k]/A[k][k];
		}

		for(I j=k; j<n; j++)
		{
			U[k][j] = A[k][j];
		}

		for(I i=k+1; i<n ;i++)
		{
			for(I j=k+1;j<n;j++)
			{
				A[i][j] -= L[i][k]*U[k][j];
			}
		}

	}

    for(I i=0;i<n;i++)
        L[i][i] =1 ;

    return;
}


//GS的qr分解 不修改传入的矩阵A
template<typename Matrix>
void qr_gs(Matrix & A, Matrix & Q, Matrix & R)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I m = A.shape[0];
    I n = A.shape[1];

    R[0][0] = A.col_norm_l2(0);

    for(I i = 0; i < m; i++)
        Q[i][0] = A[i][0]/R[0][0];

    for(I j = 1; j < n; j++)
    {
        for(I i = 0; i < m; i++)
            Q[i][j] = A[i][j];

        for(I k =0; k < j; k++)
        {
            for(I i = 0; i < m; i++)
            {
                R[k][j] += Q[i][k]*Q[i][j];
            }

            for(I i = 0; i < m; i++)
                Q[i][j] -= Q[i][k]*R[k][j]; 
        }

        R[j][j] = Q.col_norm_l2(j);

        for(I i = 0; i < m; i++)
            Q[i][j] /= R[j][j];
    }
}

//GS的qr分解 修改传入的矩阵A, R储存在矩阵A中
template<typename Matrix>
void qr_gs(Matrix & A)
{

}

//修正的GS的qr分解 不修改传入的矩阵A
template<typename Matrix>
void qr_mgs(Matrix & A, Matrix & Q, Matrix & R)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    I m = A.shape[0];
    I n = A.shape[1];

    R[0][0] = A.col_norm_l2(0);
    if (R[0][0] == 0)
    {
    	for(I i = 0; i < m; i++)
        Q[i][0] = 0;
    }
    else 
    {
    	for(I i = 0; i < m; i++)
           Q[i][0] = A[i][0]/R[0][0];
    }
    
    for(I j = 1; j < n; j++)
    {
        for(I i = 0; i < m; i++)
            Q[i][j] = A[i][j];

        for(I k =0; k < j; k++)
        {
            for(I i = 0; i < m; i++)
            {
                R[k][j] += Q[i][k]*Q[i][j];
            }

            for(I i = 0; i < m; i++)
                Q[i][j] -= Q[i][k]*R[k][j]; 
        }
        
        R[j][j] = Q.col_norm_l2(j);
        if (R[j][j] != 0)
        {
            for(I i = 0; i < m; i++)
                Q[i][j] /= R[j][j];
        }
    }
}

//修正的GS的qr分解 修改传入的矩阵A, R储存在矩阵A中
template<typename Matrix>
void qr_mgs(Matrix & A)
{

}

//householder的qr分解
template<typename Matrix,typename Vector>
void qr_hh(Matrix & A, Matrix & Q, Matrix & R)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;

    I m = A.shape[0];
    I n = A.shape[1];
    
    Q.fill_diag(1);
    for(I i = 0; i < m; i++)
    {
        for(I j = 0; j < n; j++)
            R[i][j] = A[i][j];
    }
    
    for(I k = 0; k < n; k++)
    {   
        //x = A(k:m,k) 
        Vector x(m-k);
        for(I i = 0; i < m-k; i++)
            x[i] = R[k+i][k];
        
      //[b,v] = House(x)  
        Vector v(m-k);  
        for(I i = 0; i < m-k; i++)
            v[i] = x[i];                          
        F sigma = 0.0;
        F a = 0.0;
        F b = 0.0;
        for(I i = 1; i < m-k; i++)
            sigma += x[i]*x[i];
        if(sigma == 0)
        {    
            if(x[0] < 0)
            {
                v[0] = 2*x[0];
                b = 2/(v[0]*v[0]);
            }
            else
            {
                v[0] = 0;
            }
        }
        else
        {
            a = x.norm();
            if(x[0] < 0)
                v[0] = x[0] - a;
            else
                v[0] = (-1)*sigma/(x[0]+a);
            b = 2/(v[0]*v[0]+sigma);
        }
        
        //R(k:m,k:n)
        Vector tp(n-k);
        for(I l = 0; l < n-k; l++)
        {
            for(I l1 = 0; l1 < m-k; l1++)
            {
                tp[l] += v[l1]*R[l1+k][l+k];
            }	
        }
        for(I i = k; i < m; i++)
        {            
            for(I j = k; j < n; j++)
                R[i][j] -= b*v[i-k]*tp[j-k];
        }   
        
        //Q(:,k:m)
        Vector tpq(m);
        for(I l = 0; l < m; l++)
        {
            for(I l1 = 0; l1 < m-k; l1++)
            {
                tpq[l] += Q[l][l1+k]*v[l1];
            }
        }
        for(I i = 0; i < m; i++)
        {            
            for(I j = k; j < m; j++)
            {  
                Q[i][j] -= b*tpq[i]*v[j-k];
            }
        }
    }  
    
    //将R矩阵化化为上三角形式
    for(I i = 0; i < m; i++)
    {
        for(I j = 0; j < i; j++)
            R[i][j] = 0;
    }             
}


//Givens的qr分解
template<typename Matrix,typename Vector>
void qr_givens(Matrix & A, Matrix & Q, Matrix & R)
{
    typedef typename Matrix::Float  F;
    typedef typename Matrix::Int  I;
    
    I m = A.shape[0];
    I n = A.shape[1];
     
    Q.fill_diag(1);
    for(I i = 0; i < m; i++)
    {
        for(I j = 0; j < n; j++)
            R[i][j] = A[i][j];
    }
    for(I k = 0; k < n; k++)
    {
        for(I i = k+1; i < m; i++)
        {
            //[c,s]=givens(Akk,Aik)
            F a = 0.0;
            F b = 0.0;
            F c = 0.0;
            F s = 0.0;
            F t = 0.0;
            if(R[i][k] == 0)
            {
                if(R[k][k] >= 0)
                    c = 1;
                else 
                    c = -1;
            }
            else 
            {
                if (R[k][k] > 0)
		     a = 1;
	        else if (R[k][k] == 0)
		     a = 0;
		else
		     a = -1;
                if (R[i][k] > 0)
		     b = 1;
	        else if (R[i][k] == 0)
		     b = 0;
		else
		     b = -1;             
                if(fabs(R[i][k]) > fabs(R[k][k]))
                {
                    t = R[k][k] / R[i][k];
                    s = b/sqrt(1+t*t);
                    c = s*t;
                }
                else
                {
                    t = R[i][k] / R[k][k];
                    c = a/sqrt(1+t*t);
                    s = c*t;
                }
            }
            
            Vector tp1(n-k);
            Vector tp2(n-k);
            for(I l = 0; l < n-k; l++)
                tp1[l] = c*R[k][l+k]+s*R[i][l+k];
            for(I l = 0; l < n-k; l++)
                tp2[l] = -s*R[k][l+k]+c*R[i][l+k];
            for(I l = 0; l < n-k; l++)
            {
                R[k][l+k] = tp1[l];
                R[i][l+k] = tp2[l];
            }   

            for(I l = 0; l < m; l++)
            {
                F c1,c2;
                c1 = c*Q[l][k]+s*Q[l][i];
                c2 = -s*Q[l][k]+c*Q[l][i];
                Q[l][k] = c1;
                Q[l][i] = c2;        
            }                
        }              
    }
    
    //将R矩阵化化为上三角形式
    for(I i = 0; i < m; i++)
    {
        for(I j = 0; j < i; j++)
            R[i][j] = 0;
    }   
}


} // end of AlgebraAlgrithom
} // end of WHYSC
#endif // end of linalg_h
