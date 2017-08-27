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
#include <algorithm>
#define MAX 1000


using namespace std;

vector<double> P;
vector<double> Y;
vector<double> Ptest;
vector<double> Ytest;
double w[2][MAX];
double W[MAX];
double h[MAX][MAX];
double H[MAX][MAX];
double o[MAX];
double O[MAX];
double temp[2];
double Error[MAX];
double totalError;

double sigmoide(double c){
    return(1/(1+exp(-1*c)));
}
double gradientSigmoide(double c){
    return((1-sigmoide(c))*sigmoide(c));
}
void InitializeWeights(int J){
    for(int r=0;r<J;r++){
        w[0][r]=double(rand())/(RAND_MAX*100);
        w[1][r]=double(rand())/(RAND_MAX*100);
        W[r]=double(rand())/(RAND_MAX*100);
    }
}
void BP(int J){
    double alpha;
    double delta[100][100];
    double Delta[100];
    double DeltaW[100];
    double Deltaw[2][100];
    InitializeWeights(J);
    alpha = 0.9;
    while(true){
        for(int p=0;p<P.size();p++){
            for(int j=0;j<J;j++){
                h[j][p]=w[0][j]*P[p]+w[1][j]*P[p]*P[p];
                H[j][p]=sigmoide(h[j][p]);
            }
            o[p]=0;
             for(int j=0;j<J;j++){
                o[p]+=W[j]*H[j][p];
            }
            O[p]=o[p];
            Delta[p]=Y[p]-O[p];
            for(int j=0;j<J;j++){
                DeltaW[j]=alpha*Delta[p]*H[j][p];
                temp[j]=W[j];
                W[j]=W[j]+DeltaW[j];
            }
            for(int j=0;j<J;j++){
                delta[j][p]=gradientSigmoide(h[j][p])*temp[j]*Delta[p];


                Deltaw[0][j]=alpha*delta[j][p]*P[p];
                Deltaw[1][j]=alpha*delta[j][p]*(P[p]*P[p]);
                w[0][j]=w[0][j]+Deltaw[0][j];
                w[1][j]=w[1][j]+Deltaw[1][j];
            }
        }
        alpha=alpha*0.5;
        if(alpha<0.0000000000000001){
            break;
        }
    }
}
double MultipleInputPerceptron(int J){
    totalError=0;
    for(int p=0;p<P.size();p++){
            for(int j=0;j<J;j++){
                h[j][p]=w[0][j]*P[p]+w[1][j]*P[p]*P[p];
                H[j][p]=sigmoide(h[j][p]);
            }
            o[p]=0;
             for(int j=0;j<J;j++){
                o[p]+=W[j]*H[j][p];
            }
            O[p]=o[p];
            Error[p]=Y[p]-O[p];
            totalError+=(Y[p]-O[p])*(Y[p]-O[p]);
    }
    return(totalError);
}
double MultipleInputPerceptronTest(int J){
    totalError=0;
     double meanError=0;
    double sumError=0;
    double testError=0;
    for(int p=0;p<Ptest.size();p++){
            for(int j=0;j<J;j++){
                h[j][p]=w[0][j]*Ptest[p]+w[1][j]*Ptest[p]*Ptest[p];
                H[j][p]=sigmoide(h[j][p]);
            }
            o[p]=0;
            for(int j=0;j<J;j++){
                o[p]+=W[j]*H[j][p];
            }
            O[p]=o[p];
            Error[p]=Ytest[p]-O[p];
            totalError+=(Ytest[p]-O[p])*(Ytest[p]-O[p]);
    }
    meanError=totalError/Ptest.size();
    for(int i=0;i<Ptest.size();i++){
        testError=(meanError-Error[i]*Error[i])*(meanError-Error[i]*Error[i]);
    }
    cout<<"\t"<<"MSE TEST= "<<totalError/Ptest.size()<<"\t"<<"S^2 FOR TEST MSE= "<<testError/J-1<<endl;
    return(totalError/Ptest.size());
}
double euclideanDistance(double a1,double b1,double c1,double a2,double b2,double c2){
    return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2)+(c1-c2)*(c1-c2));
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
    P.push_back(temp[0]);
    Y.push_back(temp[1]);
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
    Ptest.push_back(temp[0]);
    Ytest.push_back(temp[1]);
}
}
void HiddenUnits(int initial){
    double temp=100000000;
    double newres=1000000;
    double hatatrain=0;
    while(newres<temp){
        temp=newres;
        BP(initial);
        hatatrain=MultipleInputPerceptron(initial);
        cout<<"J="<<initial<<"\t"<<"SSE TRAIN:="<<hatatrain;
        newres=MultipleInputPerceptronTest(initial);
        initial++;
    }
}
int main()
{   double a;
    srand(time(NULL));
    retrive_training();
    retrive_test();
    HiddenUnits(3);
    return 0;
}
