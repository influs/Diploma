#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<fstream>
#define SIZE 3
#define hx 0.01
#define hy 0.01
#define eps 1e-4

using namespace std;
double** matrixAGen(int );
double** initAFromFile(double**, int);
double* solveSystem(double**,double*,double*,int);
void changeLines(double**, int,int,int);
void changeLines(double** a, int i,int j,int n){
	double temp = 0.;
	for(int iter = 0; iter < n + 1; ++iter){
		temp = a[i][iter];
		a[i][iter] = a[j][iter];
		a[j][iter] = temp;
		}	
	}

double** initAFromFile(double** a, int n){
ifstream in;
in.open("A.txt");
 for(int i = 0;i < n;++i)
     for(int j = 0;j < n + 1;++j)
         in >> a[i][j];   
 in.close();
 return a;
}
 
double** matrixAGen(int n){
 double **a;
 a = new double*[n];
 for(int i = 0;i < n;++i)
     a[i] = new double[n + 1];
 return a;
}
double* solveSystem(double** a,double *x,int n){
double temp;
// Loop for direct flow Gauss 
for(int iter = 0; iter < n - 1; ++iter){	
	//changing lines if it need
	if(a[iter+1][iter] == 0){
		for(int j = iter + 1;j < n;++j)
		    if(a[j][iter] != 0)  {
				changeLines(a,iter+1,j,SIZE);
				break;
				}	
		}	
	if(a[iter+1][iter] == 0) continue;
	//Loops for Gauss after temporary line 
	for(int itery = iter + 1;itery < n;++itery){
		temp = a[itery][iter];
		for(int iterx = iter; iterx < n + 1; ++iterx){
			a[itery][iterx] = a[itery][iterx] - (a[iter][iterx]/a[iter][iter]) * temp;		    
		}
	}
}
 /*for(int i = 0; i < SIZE; ++i){
       for(int j = 0; j < SIZE+1; ++j){
		   printf("%2.2lf ",a[i][j]);
		   
	   }
	   cout<<"\n";
	}*/
	
//reverse flow Gauss
int i = n-2;
temp = 0;
x[n-1] = a[n-1][n]/a[n-1][n-1];
cout<<"\n"<<x[n-1];
while(i >= 0){
	temp = a[i][n];
    for(int iter = n - 1;iter > i; iter--)
        temp -= a[i][iter] * x[iter];     
    x[i] = temp / a[i][i];
    cout<<"\n"<<x[i];
    --i;
 }     
return x;
}

int main(void)
{
 double **a,*x;
 x = new double[SIZE];
 a = matrixAGen(SIZE);
 a = initAFromFile(a, SIZE);
 x = solveSystem(a, x, SIZE); 
 return 0;
}
