/*
 *  func.h
 *  ve489CSMA:CD
 *
 *  Created by Ye Feiyang on 12-7-11.
 *  Copyright 2012 Shanghai Jiaotong University. All rights reserved.
 *
 */


using namespace std;

int* initUser(int *a, int size, int userNum);


int* setFrame (int *a, double p, int size, int userNum, int frameTime);


int* waitTime (int *a,int size, int userName, int start, int wait, int userD, int frame);

bool collCheck (int *a, int size);

int calcul (double pro);

