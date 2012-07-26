#include "limits.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const unsigned int MAX_USER_NUM = 5;
const unsigned int MAX_SIMULATE_TIME = 50;
const unsigned int FRAME_LEN = 4;
const unsigned int MAX_WAIT_TIME = RAND_MAX;
const int COLLISION = -1;
const int NO_COLLISION = 1;
const int IDLE = 0;

void generate_frame(char a[][], float p);
void wait_for_random_time(char a[][], int userIndex, int curTime);
int check_conflict(char a[][], int curTime);
void pure_aloha_simulate(char a[][], float p);
void slotted_aloha_simulate(char a[][], float p);

int
main()
{
	// using a two-dimentional array to represent all the states.
	int a[MAX_USER_NUM][MAX_SLOT_NUM];

	// the probability for a single user to generate a frame during \
	// a short time interval.
	double p = 0.03;

/*	// generate frames by probability p.
	srand((unsigned)time(NULL));
	for (int i = 0; i != MAX_USER_NUM; ++i) {
		for (int j = 0; j != MAX_SLOT_NUM; ++j) {
			if (rand() < RAND_MAX*p) {
				for (int k = 0; k != FRAME_LEN && j != MAX_SLOT_NUM; ++k) {
					a[i][j] = 1;
					++j;
				}
				--j;
			}
			else
				a[i][j] = 0;
		 }
	}


	for (int i = 0; i != MAX_USER_NUM; ++i) {
		cout << "user " << i + 1 << ":\t";
		for (int j = 0; j != MAX_SLOT_NUM; ++j) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	
	// check for collision.
	// arrays storing COLLISION/SUCCESS/IDLE for each user.
	
	for (int i = 0; i != MAX_SLOT_NUM; ++i) {
		int cnt = 0;
		for (int j = 0; j != MAX_USER_NUM; ++j) {
			if (a[i][j] == 1)
				++cnt;
		}
		if (cnt > 1) {
		// wait for random time.
			for (int j = 0; )
		}
	}
*/

	return 0;
}


void generate_frame(char a[][], float p)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i != MAX_USER_NUM; ++i) {
		for (int j = 0; j != MAX_SLOT_NUM; ++j) {
			if (rand() < RAND_MAX*p) {
				for (int k = 0; k != FRAME_LEN && j != MAX_SLOT_NUM; ++k) {
					a[i][j] = 1;
					++j;
				}
				--j;
			}
			else
				a[i][j] = 0;
		 }
	}
}


void wait_for_random_time(char a[][], int userIndex, int curTime)
{
	srand((unsigned int)time(NULL));
	int wait = rand()%MAX_WAIT_TIME + FRAME_LEN;

	if ((curTime + wait + 1) >= MAX_SIMULATE_TIME) {
		for (int i = curTime; i != MAX_SIMULATE_TIME; ++i)
			a[userIndex][i] = 0;
	}
	else {
		for (int i = MAX_SIMULATE_TIME - 1; i != curTime + wait -1; --i)
			a[userIndex][i] = a[userIndex][i - wait];
		for (int i = curTime; i != curTime + wait; ++i)
			a[userIndex][i] = 0;
	}
}


int check_conflict(char a[][], int curTime)
{
	int oneNum = 0;

	for (int i = 0; i != MAX_SIMULATE_TIME; ++i) {
		if (a[i][curTime] == 1)
			oneNum++;
	}

	if (oneNum > 1)
		return CONFLICT;
	else if (oneNum = 1)
		return NO_CONFLICT;
	else
		return IDLE;
}
