#include "thirdparty/matplotlibcpp.h"
#include <cmath>
#include "Constants.h"
using namespace std;
namespace plt = matplotlibcpp;

int main()
{
    vector<double> x(20), y(20), hlist(20);
    for (int i = 0; i < 20;  i++)
    { 
        double h = pow(10,-i-1);
	double e = WHYSC::Constants::e; 
	   
        x.at(i) = i+1;
        y.at(i) = ((pow(e,h)-1)/h-1);
	hlist.at(i) = h;
        cout << x.at(i) << "," << hlist.at(i) << "," <<y.at(i) <<endl;      
    }

    plt::xlabel("i");
    plt::ylabel("g(h)");
    plt::plot(x, y,"bo--");
    plt::show();
}
