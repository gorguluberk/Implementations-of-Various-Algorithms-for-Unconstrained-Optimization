#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <vector>
#define MAXIMUM 1000;

using namespace std;

vector<double> p;
vector<double> y;
vector<double> ptest;
vector<double> ytest;

double temp[2];
double euclideanDistance(double a1,double b1,double a2,double b2){
    return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));
}
double LSELR(double a, double b){
    double tempt=0;
    for(int i=0;i<p.size();i++){
        tempt+=((y[i]-a)-(b*p[i]))*((y[i]-a)-(b*p[i]));
    }
    return tempt;
}
double gradientLSELRa(double a, double b){
    double tempt=0;
    for(int i=0;i<p.size();i++){
        tempt=tempt-2*((y[i]-a)-(b*p[i]));
    }
    return tempt;
}
double gradientLSELRb(double a, double b){
    double tempt=0;
    for(int i=0;i<p.size();i++){
        tempt=tempt-2*p[i]*(y[i]-a-b*p[i]);
    }
    return tempt;
}
double Bisectiona(double a,double b,double d[2]){
    double l=-1000;
    double r=1000;
    double e=0.0000000000005;
    double alpha;
    double atemp;
    double btemp;
    double aerr;
    double berr;
    while(r-l>e){
        alpha=(r+l)/2;
        atemp=a+alpha*d[0];
        btemp=b;
        aerr=atemp+e*d[0];
        berr=btemp;
        if(LSELR(atemp,btemp)<LSELR(aerr,berr)){
            r=alpha;
        }
        else{
            l=alpha;
        }
    }
    return alpha;
}
double Bisectionb(double a,double b,double d[2]){
    double l=-1000;
    double r=1000;
    double e=0.0000000000005;
    double alpha;
    double atemp;
    double btemp;
    double aerr;
    double berr;
    while(r-l>e){
        alpha=(r+l)/2;
        atemp=a;
        btemp=b+alpha*d[1];
        aerr=atemp;
        berr=btemp+e*d[1];
        if(LSELR(atemp,btemp)<LSELR(aerr,berr)){
            r=alpha;
        }
        else{
            l=alpha;
        }
    }
    return alpha;
}
void retrive_training(){
int i=0;
std::ifstream infile("training.dat");
std::string line;
int q, z;
while (getline(infile,line))
{
    if (!line.length() || line[0] == '#')
         continue;
    std::istringstream iss(line);
    iss>>temp[0]>>temp[1];
    p.push_back(temp[0]);
    y.push_back(temp[1]);
}
}
void retrive_test(){
int i=0;
std::ifstream infile("test.dat");
std::string line;
int q, z;
while (getline(infile,line))
{
    if (!line.length() || line[0] == '#')
         continue;
    std::istringstream iss(line);
    iss>>temp[0]>>temp[1];
    ptest.push_back(temp[0]);
    ytest.push_back(temp[1]);
}
}
void LinearRegression(){
    double initial0=1;
    double initial1=1;
    double error = 0.000005;
    double a[10000];
    double b[10000];
    int iterationId;
    double d[2];
    double alpha;
    double atemp;
    double btemp;

    a[0]=initial0;
    b[0]=initial1;
    a[1]=100000;
    b[1]=100000;

    iterationId = 0;

    while(euclideanDistance(a[iterationId],b[iterationId],a[iterationId-1],b[iterationId-1])>error || iterationId==0){
        d[0]= -1*gradientLSELRa(a[iterationId],b[iterationId]);
        d[1]= -1*gradientLSELRb(a[iterationId],b[iterationId]);
        a[iterationId+1]=a[iterationId]+Bisectiona(a[iterationId],b[iterationId],d)*d[0];
        b[iterationId+1]=b[iterationId]+Bisectionb(a[iterationId+1],b[iterationId],d)*d[1];
        iterationId++;
        cout<<a[iterationId]<<"   "<<b[iterationId]<<endl;
    }
    cout<<a[iterationId]<<"   "<<b[iterationId]<<endl;

    double hata=0;
    for(int i=0;i<p.size();i++){
        hata=hata+(y[i]-a[iterationId]-b[iterationId]*p[i])*(y[i]-a[iterationId]-b[iterationId]*p[i]);
    }
    double testhata[1000];
    double testtoplam=0;
    for(int i=0;i<ptest.size();i++){
        testhata[i]=(ytest[i]-a[iterationId]-b[iterationId]*ptest[i])*(ytest[i]-a[iterationId]-b[iterationId]*ptest[i]);
        testtoplam=testtoplam+(ytest[i]-a[iterationId]-b[iterationId]*ptest[i])*(ytest[i]-a[iterationId]-b[iterationId]*ptest[i]);
    }
    for(int i=0;i<ptest.size();i++){
        testhata[i]=(ytest[i]-a[iterationId]-b[iterationId]*ptest[i])*(ytest[i]-a[iterationId]-b[iterationId]*ptest[i]);
        testtoplam=testtoplam+(ytest[i]-a[iterationId]-b[iterationId]*ptest[i])*(ytest[i]-a[iterationId]-b[iterationId]*ptest[i]);
    }
    double stest=0;
    for(int i=0;i<ptest.size();i++){
        stest=stest+(testtoplam/ptest.size()-testhata[i])*(testtoplam/ptest.size()-testhata[i]);
    }
    cout<<endl;
    cout<<"SSE TRAIN="<<hata<<"\t"<<"MSE TEST="<<testtoplam/ptest.size()<<"\t"<<"\t"<<"S^2 FOR TEST MSE="<<stest/(ptest.size()-1)<<endl;

}
int main()
{
    retrive_training();
    retrive_test();
    LinearRegression();


    return 0;
}
