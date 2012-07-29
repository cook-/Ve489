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

void generate_frame(char a[][MAX_SIMULATE_TIME], float p);
void wait_for_random_time(char a[][MAX_SIMULATE_TIME], int userIndex, int curTime);
int check_conflict(char a[][MAX_SIMULATE_TIME], int curTime);
void pure_aloha_simulate(char a[][MAX_SIMULATE_TIME], float p);
void slotted_aloha_simulate(char a[][MAX_SIMULATE_TIME], float p);


int
main()
{
	// using a two-dimentional array to represent all the states.
	int a[MAX_USER_NUM][MAX_SIMULATE_TIME];

	// the probability for a single user to generate a frame during 
	// a short time interval.
	double p = 0.03;

	return 0;
}


void 
generate_frame(char a[][MAX_SIMULATE_TIME], float p)
{
	srand((unsigned)time(NULL));
	for (unsigned int i = 0; i != MAX_USER_NUM; ++i) {
		for (unsigned int j = 0; j != MAX_SIMULATE_TIME; ++j) {
			if (rand() < RAND_MAX*p) {
				for (unsigned int k = 0; k != FRAME_LEN && j != MAX_SIMULATE_TIME; ++k) {
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


void
wait_for_random_time(char a[][MAX_SIMULATE_TIME],
							unsigned int userIndex, unsigned int curTime)
{
	srand((unsigned int)time(NULL));
	int wait = rand()%MAX_WAIT_TIME + FRAME_LEN;

	if ((curTime + wait + 1) >= MAX_SIMULATE_TIME) {
		for (unsigned int i = curTime; i != MAX_SIMULATE_TIME; ++i)
			a[userIndex][i] = 0;
	}
	else {
		for (unsigned int i = MAX_SIMULATE_TIME - 1; i != curTime + wait -1; --i)
			a[userIndex][i] = a[userIndex][i - wait];
		for (unsigned int i = curTime; i != curTime + wait; ++i)
			a[userIndex][i] = 0;
	}
}


int
check_conflict(char a[][MAX_SIMULATE_TIME], unsigned int curTime)
{
	int oneNum = 0;

	for (unsigned int i = 0; i != MAX_SIMULATE_TIME; ++i) {
		if (a[i][curTime] == 1)
			oneNum++;
	}

	if (oneNum > 1)
		return COLLISION;
	else if (oneNum == 1)
		return NO_COLLISION;
	else
		return IDLE;
}


void
pure_aloha_simulate(char a[][MAX_SIMULATE_TIME], float p)
{
	
}


void
slotted_aloha_simulate(char a[][MAX_SIMULATE_TIME], float p)
{

}
