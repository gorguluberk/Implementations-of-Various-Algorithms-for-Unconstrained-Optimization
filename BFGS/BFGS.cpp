#include <iostream>
#include <iomanip>
#include <math.h>
#define MAX 10000
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

double dist(double x1, double y1, double x2, double y2) {
return(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
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
void BFGS(){
    int k=0,i;
    double H[2][2];
    double p[2];
    double q[2];
    double A[2][2];
    double B[2][2];
    double d[2];
    double x[2];
    double x_temp[2];
    double alpha;
    double eps=0.0005;
    double temp1[2];
    double mtemp[2][2];
    double denom;
    double temp2;
    double hmulttemp1[2][2];
    double hmulttemp2[2][2];
    double htemp1[2][2];
    double htemp2[2][2];

    H[0][0]=1;
    H[0][1]=0;
    H[1][0]=0;
    H[1][1]=1;
    x[0]=3;
    x[1]=4;
    x_temp[0]=0;
    x_temp[1]=0;
    cout<<endl;
    cout<<"\t"<<"BFGS"<<endl<<endl;
    cout<<"\t"<<"Iter"<<"\t"<<"\t"<<"X"<<"\t"<<"\t  "<<"f(x)"<<"\t"<<"\t"<<"\t"<<"d"<<"\t"<<"\t   "<<"alpha"<<"\t"<<"     "<<"X-new"<<"\t"<<endl;
    while(1){
        d[0]=-H[0][0]*f_gradient_1(x[0], x[1])-H[0][1]*f_gradient_2(x[0], x[1]);
        d[1]=-H[1][0]*f_gradient_1(x[0], x[1])-H[1][1]*f_gradient_2(x[0], x[1]);
        //cout<<"direction: "<<d[0]<<"\t"<<d[1]<<endl;
        alpha=Bisection_f(x[0], x[1], d[0], d[1]);
        //cout<<alpha<<endl;
        x_temp[0]=x[0]+alpha*d[0];
        x_temp[1]=x[1]+alpha*d[1];
        p[0]=x_temp[0]-x[0];
        p[1]=x_temp[1]-x[1];
        q[0]=f_gradient_1(x_temp[0], x_temp[1])-f_gradient_1(x[0], x[1]);
        q[1]=f_gradient_2(x_temp[0], x_temp[1])-f_gradient_2(x[0], x[1]);
        temp1[0]=q[0]*H[0][0]+q[1]*H[1][0];
        temp1[1]=q[0]*H[0][1]+q[1]*H[1][1];
        temp2=(temp1[0]*q[0]+temp1[1]*q[1]+1)/(q[0]*p[0]+q[1]*p[1]);
        A[0][0]=(p[0]*p[0]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[0][1]=(p[0]*p[1]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[1][0]=(p[1]*p[0]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[1][1]=(p[1]*p[1]/(p[0]*q[0]+p[1]*q[1]))*temp2;

        hmulttemp1[0][0]=p[0]*q[0];
        hmulttemp1[0][1]=p[0]*q[1];
        hmulttemp1[1][0]=p[1]*q[0];
        hmulttemp1[1][1]=p[1]*q[1];
        htemp1[0][0]=hmulttemp1[0][0]*H[0][0]+hmulttemp1[0][1]*H[1][0];
        htemp1[0][1]=hmulttemp1[0][0]*H[0][1]+hmulttemp1[0][1]*H[1][1];
        htemp1[1][0]=hmulttemp1[1][0]*H[0][0]+hmulttemp1[1][1]*H[1][0];
        htemp1[1][1]=hmulttemp1[1][0]*H[0][1]+hmulttemp1[1][1]*H[1][1];

        hmulttemp2[0][0]=q[0]*p[0];
        hmulttemp2[0][1]=q[0]*p[1];
        hmulttemp2[1][0]=q[1]*p[0];
        hmulttemp2[1][1]=q[1]*p[1];
        htemp2[0][0]=H[0][0]*hmulttemp2[0][0]+H[0][1]*hmulttemp2[1][0];
        htemp2[0][1]=H[0][0]*hmulttemp2[0][1]+H[0][1]*hmulttemp2[1][1];
        htemp2[1][0]=H[1][0]*hmulttemp2[0][0]+H[1][1]*hmulttemp2[1][0];
        htemp2[1][1]=H[1][0]*hmulttemp2[0][1]+H[1][1]*hmulttemp2[1][1];



        mtemp[0][0]=htemp1[0][0]+htemp2[0][0];
        mtemp[0][1]=htemp1[0][1]+htemp2[0][1];
        mtemp[1][0]=htemp1[1][0]+htemp2[1][0];
        mtemp[1][1]=htemp1[1][1]+htemp2[1][1];

        denom=(q[0]*p[0]+q[1]*p[1]);

        B[0][0]=mtemp[0][0]/denom;
        B[0][1]=mtemp[0][1]/denom;
        B[1][0]=mtemp[1][0]/denom;
        B[1][1]=mtemp[1][1]/denom;

        H[0][0]=H[0][0]+A[0][0]-B[0][0];
        H[0][1]=H[0][1]+A[0][1]-B[0][1];
        H[1][0]=H[1][0]+A[1][0]-B[1][0];
        H[1][1]=H[1][1]+A[1][1]-B[1][1];

        cout<<setprecision(4)<<fixed<<"\t"<<k<<"\t"<<"("<<x[0]<<","<<x[1]<<")"<<"         "<<f(x[0],x[1])<<"       "<<"("<<d[0]<<","<<d[1]<<")"<<"           "<<alpha<<"         "<<"("<<x_temp[0]<<","<<x_temp[1]<<")"<<endl;

        if(dist(x[0], x[1], x_temp[0], x_temp[1])<eps)
            break;
        x[0]=x_temp[0];
        x[1]=x_temp[1];
        k=k+1;
    }
    cout<<endl;
    cout<<"\t"<<"x*="<<" ("<<x[0]<<","<<x[1]<<")"<<"\t"<<"f(x*)= "<<f(x[0],x[1])<<endl;
}
void BFGS2(){
    int k=0,i;
    double H[2][2];
    double p[2];
    double q[2];
    double A[2][2];
    double B[2][2];
    double d[2];
    double x[2];
    double x_temp[2];
    double alpha;
    double eps=0.0005;
    double temp1[2];
    double mtemp[2][2];
    double denom;
    double temp2;
    double hmulttemp1[2][2];
    double hmulttemp2[2][2];
    double htemp1[2][2];
    double htemp2[2][2];

    H[0][0]=1;
    H[0][1]=0;
    H[1][0]=0;
    H[1][1]=1;
    x[0]=0.5;
    x[1]=0.4;
    x_temp[0]=0;
    x_temp[1]=0;
    cout<<endl;
    cout<<"\t"<<"BFGS"<<endl<<endl;
    cout<<"\t"<<"Iter"<<"\t"<<"\t"<<"X"<<"\t"<<"\t  "<<"f(x)"<<"\t"<<"\t"<<"\t"<<"d"<<"\t"<<"\t   "<<"alpha"<<"\t"<<"     "<<"X-new"<<"\t"<<endl;
    while(1){
        d[0]=-H[0][0]*g_gradient_1(x[0], x[1])-H[0][1]*g_gradient_2(x[0], x[1]);
        d[1]=-H[1][0]*g_gradient_1(x[0], x[1])-H[1][1]*g_gradient_2(x[0], x[1]);
        //cout<<"direction: "<<d[0]<<"\t"<<d[1]<<endl;
        alpha=Bisection_g(x[0], x[1], d[0], d[1]);
        //cout<<alpha<<endl;
        x_temp[0]=x[0]+alpha*d[0];
        x_temp[1]=x[1]+alpha*d[1];
        p[0]=x_temp[0]-x[0];
        p[1]=x_temp[1]-x[1];
        q[0]=g_gradient_1(x_temp[0], x_temp[1])-g_gradient_1(x[0], x[1]);
        q[1]=g_gradient_2(x_temp[0], x_temp[1])-g_gradient_2(x[0], x[1]);
        temp1[0]=q[0]*H[0][0]+q[1]*H[1][0];
        temp1[1]=q[0]*H[0][1]+q[1]*H[1][1];
        temp2=(temp1[0]*q[0]+temp1[1]*q[1]+1)/(q[0]*p[0]+q[1]*p[1]);
        A[0][0]=(p[0]*p[0]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[0][1]=(p[0]*p[1]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[1][0]=(p[1]*p[0]/(p[0]*q[0]+p[1]*q[1]))*temp2;
        A[1][1]=(p[1]*p[1]/(p[0]*q[0]+p[1]*q[1]))*temp2;

        hmulttemp1[0][0]=p[0]*q[0];
        hmulttemp1[0][1]=p[0]*q[1];
        hmulttemp1[1][0]=p[1]*q[0];
        hmulttemp1[1][1]=p[1]*q[1];
        htemp1[0][0]=hmulttemp1[0][0]*H[0][0]+hmulttemp1[0][1]*H[1][0];
        htemp1[0][1]=hmulttemp1[0][0]*H[0][1]+hmulttemp1[0][1]*H[1][1];
        htemp1[1][0]=hmulttemp1[1][0]*H[0][0]+hmulttemp1[1][1]*H[1][0];
        htemp1[1][1]=hmulttemp1[1][0]*H[0][1]+hmulttemp1[1][1]*H[1][1];

        hmulttemp2[0][0]=q[0]*p[0];
        hmulttemp2[0][1]=q[0]*p[1];
        hmulttemp2[1][0]=q[1]*p[0];
        hmulttemp2[1][1]=q[1]*p[1];
        htemp2[0][0]=H[0][0]*hmulttemp2[0][0]+H[0][1]*hmulttemp2[1][0];
        htemp2[0][1]=H[0][0]*hmulttemp2[0][1]+H[0][1]*hmulttemp2[1][1];
        htemp2[1][0]=H[1][0]*hmulttemp2[0][0]+H[1][1]*hmulttemp2[1][0];
        htemp2[1][1]=H[1][0]*hmulttemp2[0][1]+H[1][1]*hmulttemp2[1][1];



        mtemp[0][0]=htemp1[0][0]+htemp2[0][0];
        mtemp[0][1]=htemp1[0][1]+htemp2[0][1];
        mtemp[1][0]=htemp1[1][0]+htemp2[1][0];
        mtemp[1][1]=htemp1[1][1]+htemp2[1][1];

        denom=(q[0]*p[0]+q[1]*p[1]);

        B[0][0]=mtemp[0][0]/denom;
        B[0][1]=mtemp[0][1]/denom;
        B[1][0]=mtemp[1][0]/denom;
        B[1][1]=mtemp[1][1]/denom;

        H[0][0]=H[0][0]+A[0][0]-B[0][0];
        H[0][1]=H[0][1]+A[0][1]-B[0][1];
        H[1][0]=H[1][0]+A[1][0]-B[1][0];
        H[1][1]=H[1][1]+A[1][1]-B[1][1];

        cout<<setprecision(4)<<fixed<<"\t"<<k<<"\t"<<"("<<x[0]<<","<<x[1]<<")"<<"         "<<g(x[0],x[1])<<"       "<<"("<<d[0]<<","<<d[1]<<")"<<"           "<<alpha<<"         "<<"("<<x_temp[0]<<","<<x_temp[1]<<")"<<endl;

        if(dist(x[0], x[1], x_temp[0], x_temp[1])<eps)
            break;
        x[0]=x_temp[0];
        x[1]=x_temp[1];
        k=k+1;

    }
    cout<<endl;
    cout<<"\t"<<"x*="<<" ("<<x[0]<<","<<x[1]<<")"<<"\t"<<"g(x*)= "<<g(x[0],x[1])<<endl;
}
int main(){
//BFGS();
BFGS2();
return 0;
}
