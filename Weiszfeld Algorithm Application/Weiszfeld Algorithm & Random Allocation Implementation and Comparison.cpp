#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <time.h>
#define MAX 1000
using namespace std;
int a[MAX][2];
int c[MAX][5];
int h[MAX];
int allocation[MAX][5][MAX];
double squaredEuclidean(double f1, double f2, double p1, double p2){
    double dist;
    dist = (f1-p1)*(f1-p1) + (f2-p2)*(f2-p2);
    return dist;
}
int counter(){
    int i;
    int coun;
    coun = 0;
    for(i=0;i<sizeof(h);i++){
        if(h[i]){
            coun ++;
        }
    }
    return coun;
}
double euclidean(double f1, double f2, double p1, double p2){
    double dist;
    dist = sqrt((f1-p1)*(f1-p1) + (f2-p2)*(f2-p2));
    return dist;
}
int randomIntegerGeneration(){
    int output;
    output = 0 + (rand() % (int)(4 - 0 + 1));
    return output;
}
void retrive_coordinates(){
int i=0;
std::ifstream infile("coordinate 10 .txt");
int q, z;
while (infile >> q >> z)
{
    a[i][0]=q;
    a[i][1]=z;
    i++;
}
}
void retrive_cost(){
int i=0;
std::ifstream infile("cost 10 .txt");
int q, w, z, x, e;
while (infile >> q >> w >> z >> x >> e)
{
    c[i][0]=q;
    c[i][1]=w;
    c[i][2]=z;
    c[i][3]=x;
    c[i][4]=e;
    i++;
}
}
void retrive_demand(){
int i=0;
std::ifstream infile("demand 10 .txt");
int q, w, z, x, e;
while (infile >> q)
{
    h[i]=q;
    i++;
}
}

void Weiszfeld(int facility){
    int facilityIndex;
    int i;
    double x[5][MAX][2];
    double nominator = 0;
    double denominator = 0;
    int n;
    double epsilon;
    double cost[MAX];
    n = counter();

    for (facilityIndex=0;facilityIndex<facility;facilityIndex++){
        //initialization
        nominator=0;
        for(i=0;i<n;i++){
            nominator+=c[i][facilityIndex]*h[i]*a[i][0];
        }
        denominator=0;
        for(i=0;i<n;i++){
            denominator+=c[i][facilityIndex]*h[i];
        }
        x[facilityIndex][0][0]=double(nominator/denominator);

        nominator=0;
        for(i=0;i<n;i++){
            nominator+=c[i][facilityIndex]*h[i]*a[i][1];
        }
        denominator=0;
        for(i=0;i<n;i++){
            denominator+=c[i][facilityIndex]*h[i];
        }
        x[facilityIndex][0][1]=double(nominator/denominator);

        //iterations
        epsilon = 1;
        x[facilityIndex][1][0]=10000;
        x[facilityIndex][1][1]=10000;
        while(euclidean(x[facilityIndex][1][0],x[facilityIndex][1][1],x[facilityIndex][0][0],x[facilityIndex][0][1])>epsilon){
        x[facilityIndex][0][0]=x[facilityIndex][1][0];
        x[facilityIndex][0][1]=x[facilityIndex][1][1];

        nominator=0;
        for(i=0;i<n;i++){
            nominator+=c[i][facilityIndex]*h[i]*a[i][0]/euclidean(x[facilityIndex][0][0],x[facilityIndex][0][1],a[i][0],a[i][1]);
        }
        denominator=0;
        for(i=0;i<n;i++){
            denominator+=c[i][facilityIndex]*h[i]/euclidean(x[facilityIndex][0][0],x[facilityIndex][0][1],a[i][0],a[i][1]);
        }
        x[facilityIndex][1][0]=double(nominator/denominator);
        nominator=0;
        for(i=0;i<n;i++){
            nominator+=c[i][facilityIndex]*h[i]*a[i][1]/euclidean(x[facilityIndex][0][0],x[facilityIndex][0][1],a[i][0],a[i][1]);
        }
        denominator=0;
        for(i=0;i<n;i++){
            denominator+=c[i][facilityIndex]*h[i]/euclidean(x[facilityIndex][0][0],x[facilityIndex][0][1],a[i][0],a[i][1]);
        }
        x[facilityIndex][1][1]=double(nominator/denominator);

        }

    }
    for(facilityIndex=0;facilityIndex<facility;facilityIndex++){
        cost[facilityIndex]=0;
        for(i=0;i<n;i++){
            cost[facilityIndex]+=c[i][facilityIndex]*h[i]*euclidean(x[facilityIndex][1][0],x[facilityIndex][1][1],a[i][0],a[i][1]);
        }
    }
    for(i = 0;i<facility;i++){
        cout<<setprecision(8)<<x[i][1][0]<<"  "<<x[i][1][1]<<"  "<<cost[i]<<endl;
    }
}
void singleFacilitySquaredEuclidean(int facility){
    int i;
    int index;
    double sumNominator;
    double sumDenominator;
    int n;
    int j;
    double xsfsq[MAX][2];
    double costsfsq[MAX];
    for (i=0;i<facility;i++){
    sumNominator=0;
    sumDenominator=0;
    n = counter();
    for(index=0;index<n;index++){
        sumNominator +=c[index][i]*h[index]*a[index][0];
        sumDenominator +=c[index][i]*h[index];
    }
    xsfsq[i][0] = double(sumNominator)/sumDenominator;
    sumNominator=0;
    sumDenominator=0;
    for(index=0;index<n;index++){
        sumNominator +=c[index][i]* h[index]*a[index][1];
        sumDenominator +=c[index][i]*h[index];
    }

    xsfsq[i][1] = double(sumNominator)/sumDenominator;

    costsfsq[i]= 0;
    for (j=0;j<=n;j++){
        costsfsq[i] += h[j]*c[j][i]*squaredEuclidean(xsfsq[i][0],xsfsq[i][1],a[j][0],a[j][1]);
    }
    cout<<endl;
    cout<<" Facility Id : "<<i<<endl;
    cout<<" X-Coordinate : "<<xsfsq[i][0]<<endl;
    cout<<" Y-Coordinate : "<<xsfsq[i][1]<<endl;
    cout<<setprecision(15)<<" Cost : "<<costsfsq[i]<<endl;
    }
}
void randomAllocation(int trial){
    int n;
    int f;
    int i;
    int j;
    int k;
    int index;
    double temp;
    double sum[MAX];
    double sumcost[MAX];
    double avg;
    double tempsum;
    int Id;
    double cost[MAX];
    double x[trial][5][2];
    f=5;
    n = counter();
    for(index = 0; index<trial;index++){
        for(i=0;i<f;i++){
            for(j=0;j<n;j++){
                allocation[index][i][j]=0;
            }
        }
        for(j=0;j<n;j++){
            k = randomIntegerGeneration();
            allocation[index][k][j] = 1;
        }


    sumcost[index] = 0;
    for(i=0;i<f;i++){
        int ind;
        double sumNominator;
        double sumDenominator;
        int n;
        sumNominator=0;
        sumDenominator=0;
        n = counter();
        for(ind=0;ind<n;ind++){
            sumNominator +=c[ind][i]*h[ind]*a[ind][0]*allocation[index][i][ind];
            sumDenominator +=c[ind][i]*h[ind]*allocation[index][i][ind];
        }
        x[index][i][0] = double(sumNominator)/sumDenominator;
        sumNominator=0;
        sumDenominator=0;
        for(ind=0;ind<n;ind++){
            sumNominator +=c[ind][i]* h[ind]*a[ind][1]*allocation[index][i][ind];
            sumDenominator +=c[ind][i]*h[ind]*allocation[index][i][ind];
    }

        x[index][i][1] = double(sumNominator)/sumDenominator;

        cost[i]= 0;
        for (j=0;j<n;j++){
        cost[i] += h[j]*c[j][i]*squaredEuclidean(x[index][i][0],x[index][i][1],a[j][0],a[j][1])*allocation[index][i][j];
        }
    }
        for(i=0;i<f;i++){
            sumcost[index]+=cost[i];
        }


    }
    temp=100000000;
    avg=0;
    tempsum=0;
    for(i=0;i<trial;i++){
        tempsum +=sumcost[i];
        if(temp>sumcost[i]){
            temp=sumcost[i];
            Id=i;
        }
    }
    avg = double(tempsum/trial);
    cout<<endl;
    cout<<" "<<"Trial number of the best result : "<<Id<<endl;
    cout<<setprecision(15)<<" "<<"The cost of the best result : "<<temp<<endl;
    cout<<endl;
    for(i=0;i<f;i++){
            cout<<" "<<"Facility Id : "<<i<<endl;
            cout<<" "<<"X-coordinate : "<<x[Id][i][0]<<endl;
            cout<<" "<<"Y-coordinate : "<<x[Id][i][1]<<endl;
            cout<<endl;
    }
    cout<<"\t"<<"\t"<<"F0"<<"\t"<<"F1"<<"\t"<<"F2"<<"\t"<<"F3"<<"\t"<<"F4"<<endl;
    for(i=0;i<n;i++){
        cout<<" Customer "<<i;
        for(j=0;j<f;j++){
                cout<<"\t"<<allocation[Id][j][i];
        }
        cout<<endl;
    }
    cout<<endl<<" Average cost of the trials: "<<avg<<endl;
}
void randomAllocationWeiszfeld(int trial){

        double tempsum;
        int Id;
        double temp;
        double x[trial][5][2];
        int f=5;
        int n = counter();
        double cost[MAX][5];
        double totalcost[MAX];
        int i;
        int facilityIndex;
        double nominator;
        double denominator;
        double epsilon;
        int j;
        int k;
        int trialNumber;
        double avg;
        double xold[2];

    for(trialNumber=0;trialNumber<trial;trialNumber++){
        //ALLOCATION
        for(i=0;i<f;i++){
            for(j=0;j<n;j++){
                allocation[trialNumber][i][j]=0;
            }
        }
        for(j=0;j<n;j++){
            k = randomIntegerGeneration();
            allocation[trialNumber][k][j] = 1;
        }
        //WEISZFELD

        for (facilityIndex=0;facilityIndex<f;facilityIndex++){

            nominator=0;
            for(i=0;i<n;i++){
                nominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]*a[i][0];
            }
            denominator=0;
            for(i=0;i<n;i++){
                denominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i];
            }
            xold[0]=double(nominator/denominator);

            nominator=0;
            for(i=0;i<n;i++){
                nominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]*a[i][1];
            }
            denominator=0;
            for(i=0;i<n;i++){
                denominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i];
            }
            xold[1]=double(nominator/denominator);

            //iterations
            epsilon = 1;
            x[trialNumber][facilityIndex][0]=10000;
            x[trialNumber][facilityIndex][1]=10000;
            while(euclidean(x[trialNumber][facilityIndex][0],x[trialNumber][facilityIndex][1],xold[0],xold[1])>epsilon){
            xold[0]=x[trialNumber][facilityIndex][0];
            xold[1]=x[trialNumber][facilityIndex][1];

            nominator=0;
            for(i=0;i<n;i++){
                nominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]*a[i][0]/euclidean(xold[0],xold[1],a[i][0],a[i][1]);
            }
            denominator=0;
            for(i=0;i<n;i++){
                denominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]/euclidean(xold[0],xold[1],a[i][0],a[i][1]);
            }
            x[trialNumber][facilityIndex][0]=double(nominator/denominator);
            nominator=0;
            for(i=0;i<n;i++){
                nominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]*a[i][1]/euclidean(xold[0],xold[1],a[i][0],a[i][1]);
            }
            denominator=0;
            for(i=0;i<n;i++){
                denominator+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]/euclidean(xold[0],xold[1],a[i][0],a[i][1]);
            }
            x[trialNumber][facilityIndex][1]=double(nominator/denominator);

            }

        }
        totalcost[trialNumber]=0;
        for(facilityIndex=0;facilityIndex<f;facilityIndex++){
            cost[trialNumber][facilityIndex]=0;
            for(i=0;i<n;i++){
                cost[trialNumber][facilityIndex]+=allocation[trialNumber][facilityIndex][i]*c[i][facilityIndex]*h[i]*euclidean(x[trialNumber][facilityIndex][0],x[trialNumber][facilityIndex][1],a[i][0],a[i][1]);
            }
        }
        for(facilityIndex=0;facilityIndex<f;facilityIndex++){
            totalcost[trialNumber]+=cost[trialNumber][facilityIndex];
        }
/////////////////////////////////////////////////

    }
    temp=10000000000;
    avg=0;
    tempsum=0;
    for(i=0;i<trial;i++){
        tempsum +=totalcost[i];
        if(temp>totalcost[i]){
            temp=totalcost[i];
            Id=i;
        }
    }
    avg = double(tempsum/trial);

    cout<<endl;
    cout<<" "<<"Trial number of the best result : "<<Id<<endl;
    cout<<setprecision(15)<<" "<<"The cost of the best result : "<<temp<<endl;
    cout<<endl;
    for(i=0;i<f;i++){
            cout<<" "<<"Facility Id : "<<i<<endl;
            cout<<" "<<"X-coordinate : "<<x[Id][i][0]<<endl;
            cout<<" "<<"Y-coordinate : "<<x[Id][i][1]<<endl;
            cout<<endl;
    }
    cout<<"\t"<<"\t"<<"F0"<<"\t"<<"F1"<<"\t"<<"F2"<<"\t"<<"F3"<<"\t"<<"F4"<<endl;
    for(i=0;i<n;i++){
        cout<<" Customer "<<i;
        for(j=0;j<f;j++){
                cout<<"\t"<<allocation[Id][j][i];
        }
        cout<<endl;
    }
    cout<<endl<<" Average cost of the trials: "<<avg<<endl;
}

int main () {
    srand ( time(NULL) );
    int a;
    retrive_coordinates();
    retrive_cost();
    retrive_demand();
    randomAllocationWeiszfeld(1000);
    Weiszfeld(5);
  return 0;
}






