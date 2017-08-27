#include <iostream>
#include <cmath>
using namespace std;
double x[4];
double xold[4];
double l[4];
double u[4];
double xb[2];
double xn[2];
int B[2];
int N[2];
double j[2][4];
double jB[2][2];
double jN[2][2];
double jBinv[2][2];
double xgrad[4];
double gradB[2];
double gradN[2];
double rN[2];
double dN[2];
double dB[2];
double d[4];
double temp[2][2];
double alphamax;
double alpha;
double error=0.001;

double objective(double y[4]){
    return(3*y[0]*y[0]+2*y[1]*y[1]-2*y[0]*y[1]-4*y[0]+2*y[1]+3);
}
double gradientObjective1(double y[4]){
    return(6*y[0]-2*y[1]-4);
}
double gradientObjective2(double y[4]){
    return(4*y[1]-2*y[0]+2);
}
double dist(double k[4],double l[4]){
    return(sqrt((k[0]-l[0])*(k[0]-l[0])+(k[1]-l[1])*(k[1]-l[1])+(k[2]-l[2])*(k[2]-l[2])+(k[3]-l[3])*(k[3]-l[3])));
}
double goldenSection(double y[4], double k[4],double alpha){
    double a = 0;
    double b = alpha;
    double e = 0.00005;
    double s;
    double t;
    double q;
    double fs;
    double ft;
    double t2[4];
    s=b-0.618*(b-a);
    t=a+0.618*(b-a);
    t2[0]=y[0]+s*k[0];
    t2[1]=y[1]+s*k[1];
    t2[2]=y[2]+s*k[2];
    t2[3]=y[3]+s*k[3];
    fs=objective(t2);
    t2[0]=y[0]+t*k[0];
    t2[1]=y[1]+t*k[1];
    t2[2]=y[2]+t*k[2];
    t2[3]=y[3]+t*k[3];
    ft=objective(t2);
    while(b-a>e){
        if(fs>ft){
            a=s;
            s=t;
            t=a+0.618*(b-a);
            fs=ft;
            t2[0]=y[0]+t*k[0];
            t2[1]=y[1]+t*k[1];
            t2[2]=y[2]+t*k[2];
            t2[3]=y[3]+t*k[3];
            ft=objective(t2);
        }
        else{
            b=t;
            t=s;
            s=b-0.618*(b-a);
            ft=fs;
            t2[0]=y[0]+s*k[0];
            t2[1]=y[1]+s*k[1];
            t2[2]=y[2]+s*k[2];
            t2[3]=y[3]+s*k[3];
            fs=objective(t2);
        }
    }
    return (a+b)/2;
}
void decideBasic(){
    int i=0;
    int j=0;
    int k=0;
    for(i=0;i<4;i++){
        if(l[i]<x[i] && x[i]<u[i]){
            xb[j]=x[i];
            B[j]=i;
            j++;
        }
        if(j==3){
            break;
        }
    }
    for(i=0;i<4;i++){
        if(B[0]!=i && B[1]!=i){
            xn[k]=x[i];
            N[k]=i;
            k++;
        }
    }
}
void getInverse(){
    double det;
    det = jB[0][0]*jB[1][1]-jB[1][0]*jB[0][1];
    jBinv[0][0]=jB[1][1]/det;
    jBinv[1][1]=jB[0][0]/det;
    jBinv[1][0]=-1*jB[1][0]/det;
    jBinv[0][1]=-1*jB[0][1]/det;
}
void determineDirection(){
    int i = 0;
    for(i=0;i<2;i++){
        if(xn[i]==l[N[i]]){
            if(gradN[i]<=0){
                dN[i]=-1*rN[i];
            }
            else{
                dN[i]=0;
            }
        }
        else if(xn[i]==u[N[i]]){
            if(gradN[i]>=0){
                dN[i]=-1*rN[i];
            }
            else{
                dN[i]=0;
            }
        }
        else{
            dN[i]=-1*rN[i];

        }
    }
}
double checkConstraints(){
    double ll[4];
    double uu[4];
    double chosed[4];
    double chosedReal;
    double tempAlpha;
    int i;
    for(i=0;i<4;i++){
        uu[i]=u[i]-x[i];
        ll[i]=l[i]-x[i];
        uu[i]=uu[i]/d[i];
        ll[i]=ll[i]/d[i];
        chosed[i]=max(uu[i],ll[i]);
    }
    tempAlpha = 1000000;
    for(i=0;i<4;i++){
        if(chosed[i]<tempAlpha){
            tempAlpha=chosed[i];
        }
    }
    return(tempAlpha);
}
void ReducedGradient(){
    double iteration=0;
    x[0]=2;
    x[1]=-1;
    x[2]=1;
    x[3]=4;

    u[0]=5;
    u[1]=6;
    u[2]=4;
    u[3]=10;
    l[0]=2;
    l[1]=-1;
    l[2]=0;
    l[3]=0;

    j[0][0]=1;
    j[1][0]=1;
    j[0][1]=1;
    j[1][1]=1;
    j[0][2]=1;
    j[1][2]=0;
    j[0][3]=0;
    j[1][3]=1;

    while(dist(xold,x)>error||iteration==0){

        decideBasic();
        jB[0][0]=j[0][B[0]];
        jB[1][0]=j[1][B[0]];
        jB[0][1]=j[0][B[1]];
        jB[1][1]=j[1][B[1]];
        getInverse();
        jN[0][0]=j[0][N[0]];
        jN[1][0]=j[1][N[0]];
        jN[0][1]=j[0][N[1]];
        jN[1][1]=j[1][N[1]];

        xgrad[0]=gradientObjective1(x);
        xgrad[1]=gradientObjective2(x);
        xgrad[2]=0;
        xgrad[3]=0;
        gradB[0]=xgrad[B[0]];
        gradB[1]=xgrad[B[1]];
        gradN[0]=xgrad[N[0]];
        gradN[1]=xgrad[N[1]];

        temp[0][0]=jBinv[0][0]*jN[0][0]+jBinv[0][1]*jN[1][0];
        temp[0][1]=jBinv[0][0]*jN[0][1]+jBinv[0][1]*jN[1][1];
        temp[1][0]=jBinv[1][0]*jN[0][0]+jBinv[1][1]*jN[1][0];
        temp[1][1]=jBinv[1][0]*jN[0][1]+jBinv[1][1]*jN[1][1];


        rN[0]=gradN[0]-(gradB[0]*temp[0][0]+gradB[1]*temp[1][0]);
        rN[1]=gradN[1]-(gradB[0]*temp[0][1]+gradB[1]*temp[1][1]);

        determineDirection();

        dB[0]=-1*(dN[0]*temp[0][0]+dN[1]*temp[0][1]);
        dB[1]=-1*(dN[0]*temp[1][0]+dN[1]*temp[1][1]);


        d[N[0]]=dN[0];
        d[N[1]]=dN[1];
        d[B[0]]=dB[0];
        d[B[1]]=dB[1];
        alphamax = checkConstraints();
        alpha = goldenSection(x,d,alphamax);


        xold[0]=x[0];
        xold[1]=x[1];
        xold[2]=x[2];
        xold[3]=x[3];


        x[0]=x[0]+alpha*d[0];
        x[1]=x[1]+alpha*d[1];
        x[2]=x[2]+alpha*d[2];
        x[3]=x[3]+alpha*d[3];

        iteration++;
        cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<" "<<xold[1]<<" "<<xold[2]<<" "<<xold[3]<<" "<<d[0]<<" "<<d[1]<<" "<<d[2]<<" "<<d[3]<<" "<<objective(x)<<endl;
    }

}
int main()
{
    ReducedGradient();
    return 0;
}
