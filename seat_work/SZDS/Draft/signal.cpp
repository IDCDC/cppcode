#include <iostream>
using namespace std;
int signal(double a) 
{
	if (a > 0)
		a = 1;
	else if (a == 0)
		a = 0;
	else
		a = -1;
	return a;
}

int main() 
{
	double b = 3.64;
	double c = signal(-0.31);
	cout << 'b' << b << 'c' << c << endl;
	return 0;
}


//Jacobi迭代
    template<typename Vector>
    void jacobi(Vector & b, Vector & x, Vector & u,I maxit=1000, F tol=1e-8)
    {
        F d = 0.0;
        F bnorm = b.norm();
        F rnorm = 0.0;
        I m,steps;
        Vector x1(x.size);
        Vector step(maxit);
        Vector norm(maxit);
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
        std::cout << m << ": " << rnorm << std::endl;
        double e = (u - x).maxnorm();
        std::cout << "error: " << e << std::endl;
        
        vector<double> x_axis(steps),y_axis(steps);                           //画图
        for(int m = 0; m < steps; m++)
        {
            x_axis.at(m) = step[m];
            y_axis.at(m) = norm[m];
        }
        plt::plot(x_axis, y_axis, "r--");
    }
    
