#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#define MAX 1000

using namespace std;

double f(double x1, double x2) {
return ((5 * x1 - x2)*(5 * x1 - x2)*(5 * x1 - x2)*(5 * x1 - x2) + (x1
- 2)*(x1 - 2) + x1 - 2 * x2 + 12);
}
double g(double x1, double x2){
    return (100*(x2-x1*x1)*(x2-x1*x1)+(1-x1)*(1-x1));
}
double f_gradient_1(double x1, double x2){
    return (20*(5*x1-x2)*(5*x1-x2)*(5*x1-x2)+2*(x1-2)+1);
}
double f_gradient_2(double x1, double x2){
    return (-4*(5*x1-x2)*(5*x1-x2)*(5*x1-x2)-2);
}
double g_gradient_1(double x1, double x2){
    return (-400*x2*x1+400*x1*x1*x1-2+2*x1);
}
double g_gradient_2(double x1, double x2){
    return (200*x2-200*x1*x1);
}

double Bisection_f(double x0, double x1, double d1, double d2){
    double a = -100;
    double b = 100;
    double error = 0.00005;
    double m;
        while ((b-a)>error){
        m=(a+b)/2;
            if(f(x0+d1*(m+error),x1+d2*(m+error))>=f(x0+d1*m,x1+d2*m)){
                b=m;
            }
            else{
                a=m;
            }
        }
    return m;
}
double Bisection_g(double x0, double x1, double d1, double d2){
    double a = -100;
    double b = 100;
    double error = 0.00005;
    double m;
        while ((b-a)>error){
        m=(a+b)/2;
            if(g(x0+d1*(m+error),x1+d2*(m+error))>=g(x0+d1*m,x1+d2*m)){
                b=m;
            }
            else{
                a=m;
            }
        }
    return m;
}
double dist(double x1, double y1, double x2, double y2) {
return(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

double norm(double x1, double x2)
{
    return sqrt(x1*x1+x2*x2);
}

int main()
{
    int functionId = 2;//FunctionId = 1 for the first function and 2 for the second function
    if(functionId==1){
    double d[MAX][2];
    int k=0;
    double Epsilon=0.05;
    double x[MAX][2];
    double alpha[MAX];
    double Hessian[2][2];
    double HesInv[2][2];
    double detHes;
    x[0][0]=3;
    x[0][1]=20;
    cout<< "k     x(k)             f(x(k))        d(k)       alpha(k)         x(k+1)\n";
    while(true)
    {
        Hessian[0][0]=300*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1])+2;
        Hessian[0][1]=-60*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);
        Hessian[1][0]=-60*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);
        Hessian[1][1]=12*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);


        detHes=Hessian[0][0]*Hessian[1][1]-Hessian[0][1]*Hessian[1][0];

        HesInv[0][0]=Hessian[1][1]/detHes;
        HesInv[0][1]=(-1*Hessian[0][1])/detHes;
        HesInv[1][0]=(-1*Hessian[1][0])/detHes;
        HesInv[1][1]=Hessian[0][0]/detHes;

        d[k][0]=-1*HesInv[0][0]*f_gradient_1(x[k][0],x[k][1])-HesInv[0][1]*f_gradient_2(x[k][0],x[k][1]);
        d[k][1]=-1*HesInv[1][0]*f_gradient_1(x[k][0],x[k][1])-HesInv[1][1]*f_gradient_2(x[k][0],x[k][1]);
        alpha[k]=Bisection_f(x[k][0],x[k][1],d[k][0],d[k][1]);
        x[k+1][0]=x[k][0]+alpha[k]*d[k][0];
        x[k+1][1]=x[k][1]+alpha[k]*d[k][1];
        cout <<fixed<<setprecision(3)<<k<<"    ("<<x[k][0]<<","<<x[k][1]<<")    "<<f(x[k][0],x[k][1])<<"      ("<<d[k][0]<<","<<d[k][1]<<")    "<<alpha[k]<<"    ("<<x[k+1][0]<<","<<x[k+1][1]<<")\n";
        k++;
        if(dist(x[k][0],x[k][1],x[k-1][0],x[k-1][1])<Epsilon)
            break;
    }
    cout <<"x*= ("<<x[k][0]<<","<<x[k][1]<<")\n";
    cout <<"f(x*)= "<< f(x[k][0],x[k][1]);

    cin >> d[k][0];

    }
    else{
        double d[MAX][2];
        int k=0;
        double Epsilon=0.005;
        double x[MAX][2];
        double alpha[MAX];
        double Hessian[2][2];
        double HesInv[2][2];
        double detHes;
        x[0][0]=0.8;
        x[0][1]=0.8;
        cout<< "k     x(k)             f(x(k))        d(k)       alpha(k)         x(k+1)\n";
        while(true)
        {
            Hessian[0][0]=300*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1])+2;
            Hessian[0][1]=-60*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);
            Hessian[1][0]=-60*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);
            Hessian[1][1]=12*(5*x[k][0]-x[k][1])*(5*x[k][0]-x[k][1]);


            detHes=Hessian[0][0]*Hessian[1][1]-Hessian[0][1]*Hessian[1][0];

            HesInv[0][0]=Hessian[1][1]/detHes;
            HesInv[0][1]=(-1*Hessian[0][1])/detHes;
            HesInv[1][0]=(-1*Hessian[1][0])/detHes;
            HesInv[1][1]=Hessian[0][0]/detHes;

            d[k][0]=-1*HesInv[0][0]*g_gradient_1(x[k][0],x[k][1])-HesInv[0][1]*g_gradient_2(x[k][0],x[k][1]);
            d[k][1]=-1*HesInv[1][0]*g_gradient_1(x[k][0],x[k][1])-HesInv[1][1]*g_gradient_2(x[k][0],x[k][1]);
            alpha[k]=Bisection_g(x[k][0],x[k][1],d[k][0],d[k][1]);
            x[k+1][0]=x[k][0]+alpha[k]*d[k][0];
            x[k+1][1]=x[k][1]+alpha[k]*d[k][1];
            cout <<fixed<<setprecision(3)<<k<<"    ("<<x[k][0]<<","<<x[k][1]<<")    "<<g(x[k][0],x[k][1])<<"      ("<<d[k][0]<<","<<d[k][1]<<")    "<<alpha[k]<<"    ("<<x[k+1][0]<<","<<x[k+1][1]<<")\n";
            k++;
            if(dist(x[k][0],x[k][1],x[k-1][0],x[k-1][1])<Epsilon)
                break;
        }
        cout<< "k     x(k)             f(x(k))        d(k)       alpha(k)         x(k+1)\n"<<endl;
        cout <<"x*= ("<<x[k][0]<<","<<x[k][1]<<")\n";
        cout <<"f(x*)= "<< g(x[k][0],x[k][1]);

        cin >> d[k][0];
    }
}
