#include <iostream>
#include "func.h"
using namespace std;

int main(){
	int result=0;
	double pro=0.0;
	srand((unsigned)time(NULL));
	for (; pro<=1; pro+=0.05){
		for(int round=0; round<100; round++){
			int result1 = calcul(pro);
			result += result1;
		}
		result = result/100;
		cout<<result<<endl;
	}
	/*int *x = new int[20];
	for (int m=0; m<20; m++){
		x[m]=0;
	}
	x[4]=1;
	x[5]=1;
	x[6]=1;
	x[7]=1;
	int rand_t = rand()%10;
	cout << rand_t<<endl;
	x = waitTime(x, 20, 0, 6-2+1, rand_t, 1, 2);
	for (int n=0; n<20; n++){
		cout << x[n] << " ";
	}
	cout <<endl;*/
	return 0;
}