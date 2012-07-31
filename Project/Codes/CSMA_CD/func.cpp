/*
 *  func.cpp
 *  ve489CSMA:CD
 *
 *  Created by Ye Feiyang on 12-7-11.
 *  Copyright 2012 Shanghai Jiaotong University. All rights reserved.
 *
 */
#include <math.h>
#include <ctime>
#include <iostream>
#include "func.h"
using namespace std;

int* initUser(int *a, int size, int userNum){
	for (int i=0; i<size*userNum; i++){
		a[i] = 9;
	}
	return a;
}


int* setFrame (int *a, double p, int size, int userNum, int frameTime){
	//srand((unsigned)time(NULL));
	for (int i=0; i<userNum*size; i++){
		if (a[i] != 1 && a[i] != 0){
			double div = size*p;
			double ran_num = rand()%size;
			if (ran_num < div){
				for (int g=0; g<frameTime; g++){
					a[i+g] = 1;
				}
			}
			else {
				for (int g=0; g<frameTime; g++){
					a[i+g] = 0;
				}
			}
		}
		else{}
	}
	//cout<<endl;
	return a;
}




int* waitTime (int *a,int size, int userName, int start, int wait, int userD, int frame){
	int check = start+wait;
	//cout << frame <<" "<<userD<<endl;
	if (check>=size){
		for (int i=userName*size+start; i<(userName+1)*size; i++) {
			a[i]=0;
		}
	}
	else{
		for (int i=(userName+1)*size-1-wait; i>=userName*size+start; i--){
			int temp = a[i];
			a[i+wait] = temp;
		}
		for(int j=0; j<wait; j++){
			int temp2 = userName*size+start+j;
			a[temp2] = 0;
		}
	}
	return a;
}


bool collCheck (int *a, int size){
	int m=0;
	bool check;
	for (int x=0; x<size; x++){
		if (a[x] > 0){
			m += 1;
		}
	}
	if (m>1){
		check = 1;
	}
	else {
		check = 0;
	}
	return check;
}




int calcul (double pro) {

	int size = 1000;
	int userNum = 10;
	int frameTime =4;
	bool busy = 0;
	bool collision = 0;
	bool busySet = 0;
	bool collSet = 0;
	bool idleSet = 0;
	bool busySet1 = 0;
	bool collSet1 = 0;
	bool idleSet1 = 0;
	
	int mediumDelay = 0;
	int *colliNum = new int[userNum];
	int *success = new int[userNum];
	int *userDelay = new int[userNum];
	int *frameFraction = new int[userNum];
	int *a = new int[userNum*size];
	a = initUser(a, size, userNum);
	a = setFrame (a, pro, size, userNum, frameTime);
//	for (int i=0; i<userNum; i++){
//		for (int j=0; j<size; j++){
//			cout << a[i*size + j]<<" ";
//		}
//		cout <<endl;
//	}
	for (int i=0; i<userNum; i++){
		colliNum[i]=0;
		success[i]=0;
		userDelay[i]=0;
		frameFraction[i]=0;
	}

	for (int timerTotal=0; timerTotal<size; timerTotal++){
		if (busySet1 == 1){
			busy = 1;
			busySet1=0;
//			cout<<"Medium is busy now!"<<endl;
		}
		if (idleSet1 == 1){
			busy = 0;
//			cout<<"Medium is idle again now!"<<endl;
			idleSet1=0;
		}
		if (collSet1 == 1){
			collision = 1;
//			cout<<"There is a collision!"<<endl;
//			cout <<"It's at time "<<timerTotal<<endl;
			collSet1=0;
		}
		
		if (mediumDelay==1){
			if (busySet==1){
				busySet1 = 1;
				
			}
			if (idleSet==1){
				idleSet1 = 1;
				
			}
			if (collSet==1){
				collSet1 = 1;
				//numOfCo += 1;
				
			}
		}
				
		busySet=0;
		idleSet=0;
		collSet=0;
		mediumDelay = 0;
		
		for (int j=0; j<userNum; j++){
			frameFraction[j] += userDelay[j];
			
			//testNum += userDelay[j];
			if (userDelay[j]==0 && collision==1){
				frameFraction[j]=0;
			}
			if (frameFraction[j] == frameTime && mediumDelay==0 && collSet==0){
				userDelay[j]=0;
				colliNum[j]=0;
				frameFraction[j]=0;
				idleSet = 1;
				mediumDelay=1;
				success[j] += 1;
//				cout <<"Frame "<<j+1<<" succeed "<< success[j] <<endl;
			}
			if (frameFraction[j]==frameTime && collSet ==1){
				colliNum[j] += 1;
				int power = pow(2,colliNum[j]);
				int rand_time = rand()%power;
				int rand = 2*rand_time+userDelay[j]+frameFraction[j]+1;
				//int rand_t = rand()%1024;
				//int rand = rand_t;
				a = waitTime(a, size, j, timerTotal-frameFraction[j], rand, userDelay[j], frameFraction[j]);
				
/*				for (int i=0; i<userNum; i++){
					for (int j=0; j<size; j++){
						cout << a[i*size + j]<<" ";
					}
					cout <<endl;
				}
*/				
				//	cout << "User "<<j+1<<" is waiting !!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
				userDelay[j]=0;
				frameFraction[j]=0;
			}
			
				
				
				
			if (userDelay[j]==0){
				frameFraction[j]=0;
			}
			
						 
			 
			
						
			if (busy==0 && a[j*size+timerTotal]==1){
				userDelay[j] = 1;
				if(frameFraction[j]==1){
					mediumDelay = 1;
					busySet = 1;
				}
				else{}
				
			}
			
			else if (busy==1 && a[j*size+timerTotal]==1 && frameFraction[j]==0){
			//	colliNum[j] += 1;
				int power = pow(2,colliNum[j]);
				int rand_time = rand()%power;
				int rand = 2*rand_time+userDelay[j]+1;
				//int rand_t = rand()%1024;
				//int rand = rand_t;
				a = waitTime(a, size, j, timerTotal, rand, userDelay[j], frameFraction[j]);
				
/*				for (int i=0; i<userNum; i++){
					for (int j=0; j<size; j++){
						cout << a[i*size + j]<<" ";
					}
					cout <<endl;
				}
*/				
			//	cout << "User "<<j+1<<" is waiting !!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
				userDelay[j] = 0;
			}
			else if (busy==1 && a[j*size+timerTotal]==1 && frameFraction[j]>0 && collision==0){
				userDelay[j] = 1;
			}
			else if (busy==1 && a[j*size+timerTotal]==1 && frameFraction[j]>0 && collision==1){
				colliNum[j] += 1;
				int power = pow(2,colliNum[j]);
				int rand_time = rand()%power;
				int rand = 2*rand_time+userDelay[j]+frameFraction[j]+1;
				//int rand_t = rand()%1024;
				//int rand = rand_t;
				a = waitTime(a, size, j, timerTotal-frameFraction[j], rand, userDelay[j], frameFraction[j]);
				
/*				for (int i=0; i<userNum; i++){
					for (int j=0; j<size; j++){
						cout << a[i*size + j]<<" ";
					}
					cout <<endl;
				}
*/				
			//	cout << "User "<<j+1<<" is waiting !!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
				userDelay[j]=0;
			}
			else if (a[j*size+timerTotal]==0){
				userDelay[j]=0;
			}
			
			else {}
			
			
		
/*			if (j==0){
				cout <<"frameF 1: "<< frameFraction[j]<<"   userDLay 1: "<<userDelay[j]<<endl;
			}
			if (j==1){
				cout <<"frameF 2: "<< frameFraction[j]<<"   userDLay 2: "<<userDelay[j]<<endl;
			}
			if (j==2){
				cout <<"frameF 3: "<< frameFraction[j]<<"   userDLay 3: "<<userDelay[j]<<endl;
			}
			if (j==3){
				cout <<"frameF 4: "<< frameFraction[j]<<"   userDLay 4: "<<userDelay[j]<<endl;
			}
			
*/			

			collSet = collCheck(frameFraction, userNum);
	
			
		}
		collSet = collCheck(frameFraction, userNum);
		//cout << "CollSet is "<<collSet<<endl;
		//cout << "BusySet is "<<busySet<<endl;
		if (collSet == 1){
			mediumDelay = 1;
		}
		int sum=0;
		for (int j=0; j<userNum; j++){
			sum += frameFraction[j];
		}
	//	cout <<"Sum is: "<<sum<<endl;
		if (sum == 0 && busy==1){
			idleSet = 1;
			mediumDelay=1;
		}
		if (sum==0 && collision==1){
			collision=0;
		}
		
	}
	int total=0;
	for (int x=0; x<userNum; x++) {
		total += success[x];
	//	cout << success[x]<<" ";
	}
	//cout << endl;
	//cout<<total<<endl;
	//cout << numOfCo<<endl;
	return total;
}

