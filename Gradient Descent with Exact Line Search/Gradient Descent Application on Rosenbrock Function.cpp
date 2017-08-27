#include <iostream>
#include <cmath>
#include <iomanip>
#define MAX 10000

using namespace std;
double euclideanDistance(double x[2],double y[2]){
    return sqrt((x[0]-y[0])*(x[0]-y[0])+(x[1]-y[1])*(x[1]-y[1]));
}
double F(double x[2]){
    return (((5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1]))+((x[0]-2)*(x[0]-2))+x[0]-2*x[1]+12);
}
double gradientF1(double x[2]){
    double y[2];
    y[0]= 20*(5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1])+2*(x[0]-2)+1;
    y[1]=-4*(5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1])-2;
    return(y[0]);
}
double gradientF2(double x[2]){
    double y[2];
    y[0]= 20*(5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1])+2*(x[0]-2)+1;
    y[1]=-4*(5*x[0]-x[1])*(5*x[0]-x[1])*(5*x[0]-x[1])-2;
    return y[1];
}
double Rosenbrocks(double x[2]){
    return 100*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(1-x[0])*(1-x[0]);
}
double gradientRosenbrocks1(double x[2]){
    double y[2];
    y[0]=-400*x[0]*(x[1]-x[0]*x[0])-2*(1-x[0]);
    y[1]=200*(x[1]-x[0]*x[0]);
    return y[0];
}
double gradientRosenbrocks2(double x[2]){
    double y[2];
    y[0]=-400*x[0]*(x[1]-x[0]*x[0])-2*(1-x[0]);
    y[1]=200*(x[1]-x[0]*x[0]);
    return y[1];
}
double g_gradient_1(double x1, double x2){
    return (-400*x2*x1+400*x1*x1*x1-2+2*x1);
}
double g_gradient_2(double x1, double x2){
    return (200*x2-200*x1*x1);
}

double Bisection(double x[2],double d[2]){
    double a=-100;
    double b=100;
    double e=0.0005;
    double alpha;
    double xtemp[2];
    double xerr[2];
    while(b-a>e){
        alpha=(a+b)/2;
        xtemp[0]=x[0]+alpha*d[0];
        xtemp[1]=x[1]+alpha*d[1];
        xerr[0]=xtemp[0]+e*d[0];
        xerr[1]=xtemp[1]+e*d[1];
        if(F(xtemp)<F(xerr)){
            b=alpha;
        }
        else{
            a=alpha;
        }
    }
    return alpha;
}

double Bisection2(double x[2],double d[2]){
    double a=-100;
    double b=100;
    double e=0.00005;
    double alpha;
    double xtemp[2];
    double xerr[2];
    while(b-a>e){
        alpha=(a+b)/2;
        xtemp[0]=x[0]+alpha*d[0];
        xtemp[1]=x[1]+alpha*d[1];
        xerr[0]=xtemp[0]+e*d[0];
        xerr[1]=xtemp[1]+e*d[1];
        if(Rosenbrocks(xtemp)<Rosenbrocks(xerr)){
            b=alpha;
        }
        else{
            a=alpha;
        }
    }
    return alpha;
}
int main()
{
    int controller=2;
    if(controller == 1){
    double initial0=1;
    double initial1=1;
    double error = 0.0005;
    double x[MAX][2];
    int iterationId;
    double d[2];
    double a;
    double xtemp[2];

    x[0][0]=initial0;
    x[0][1]=initial1;
    x[1][0]=100000;
    x[1][1]=100000;

    iterationId = 0;

    while(euclideanDistance(x[iterationId],x[iterationId-1])>error || iterationId==0){
        d[0]= -1*gradientF1(x[iterationId]);
        d[1]= -1*gradientF2(x[iterationId]);
        a=Bisection(x[iterationId],d);
        x[iterationId+1][0]=x[iterationId][0]+a*d[0];
        x[iterationId+1][1]=x[iterationId][1]+a*d[1];
        iterationId++;
        cout<<setprecision(6)<<fixed<<"\t"<<iterationId-1<<"\t"<<"("<<x[iterationId-1][0]<<","<<x[iterationId-1][1]<<")"<<"\t"<<F(x[iterationId-1])<<"\t"<<"("<<d[0]<<","<<d[1]<<")"<<"           "<<a<<"\t"<<"("<<x[iterationId][0]<<","<<x[iterationId][1]<<")"<<endl;
    }
    cout<<"\t"<<"Iter"<<"\t"<<"\t"<<"X"<<"\t"<<"\t  "<<"f(x)"<<"\t"<<"\t"<<"\t"<<"d"<<"\t"<<"\t   "<<"alpha"<<"\t"<<"     "<<"X-new"<<"\t"<<endl;
    cout<<endl;
    cout<<"\t"<<"x*="<<" ("<<x[iterationId][0]<<","<<x[iterationId][1]<<")"<<"\t"<<"f(x*)= "<<F(x[iterationId])<<endl;
    }
    else{
    double initial0=-5;
    double initial1=-8;
    double error = 0.00000005;
    double x[MAX][2];
    int iterationId;
    double d[2];
    double a;
    int p;
    double xtemp[2];

    x[0][0]=initial0;
    x[0][1]=initial1;
    x[1][0]=100000;
    x[1][1]=100000;
    //Buraya initial yazdýrýlacak//
    iterationId = 0;

    while(euclideanDistance(x[iterationId],x[iterationId-1])>error || iterationId==0){
        d[0]= -1*gradientRosenbrocks1(x[iterationId]);
        d[1]= -1*gradientRosenbrocks2(x[iterationId]);
        a=Bisection2(x[iterationId],d);
        x[iterationId+1][0]=x[iterationId][0]+a*d[0];
        x[iterationId+1][1]=x[iterationId][1]+a*d[1];
        iterationId++;
        cout<<setprecision(4)<<fixed<<"\t"<<iterationId-1<<"\t"<<"("<<x[iterationId-1][0]<<","<<x[iterationId-1][1]<<")"<<"    "<<Rosenbrocks(x[iterationId-1])<<"\t"<<"("<<d[0]<<","<<d[1]<<")"<<"           "<<a<<"\t"<<"("<<x[iterationId][0]<<","<<x[iterationId][1]<<")"<<endl;
    }
    cout<<"\t"<<"Iter"<<"\t"<<"\t"<<"X"<<"\t"<<"\t  "<<"f(x)"<<"\t"<<"\t"<<"\t"<<"d"<<"\t"<<"\t   "<<"alpha"<<"\t"<<"     "<<"X-new"<<"\t"<<endl;
    cout<<endl;
    cout<<"\t"<<"x*="<<" ("<<x[iterationId][0]<<","<<x[iterationId][1]<<")"<<"\t"<<"f(x*)= "<<Rosenbrocks(x[iterationId])<<endl;
    }
    return 0;
}
