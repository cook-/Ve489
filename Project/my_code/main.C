#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const unsigned int USER_NUM = 5;
const unsigned int SIMULATE_TIME = 1000;
const unsigned int FRAME_LEN = 4;
const unsigned int MAX_WAIT_TIME = RAND_MAX;
const int COLLISION = -1;
const int NO_COLLISION = 1;
const int IDLE = 0;
//int total[1000];
//int success[1000];

void generate_frame(int a[][SIMULATE_TIME], float p);
int wait_for_random_time(int a[][SIMULATE_TIME], int userIndex, int curTime);
int check_collision(int a[][SIMULATE_TIME], int curTime);
void pure_aloha_simulate(int a[][SIMULATE_TIME], float p);
void slotted_aloha_simulate(int a[][SIMULATE_TIME], float p);


int
main()
{
	// using a two-dimentional array to represent all the states.
	int a[USER_NUM][SIMULATE_TIME];

	// the probability for a single user to generate a frame during 
	// a short time interval.
	double p = 0.1;

//	for (int i = 0; i != 1000; ++i)
		pure_aloha_simulate(a, p);

	double totalFrameNum = 0;
	double successFrameNum = 0;
//	for (int i = 0; i != 1000; ++i) {
//		totalFrameNum += total[i];
//		successFrameNum += success[i];
//	}
//	totalFrameNum /= 1000;
//	successFrameNum /= 1000;
//	cout << "G: " << totalFrameNum/250 << " S: " << successFrameNum/totalFrameNum << endl;

	return 0;
}


void 
generate_frame(int a[][SIMULATE_TIME], float p)
{
	srand((unsigned)time(NULL));
	for (unsigned int i = 0; i != USER_NUM; ++i) {
		for (unsigned int j = 0; j != SIMULATE_TIME; ++j) {
			if (rand() < RAND_MAX*p) {
				for (unsigned int k = 0; k != FRAME_LEN && j != SIMULATE_TIME; ++k) {
					a[i][j] = 1;
					j++;
				}
				j--;
			}
			else
				a[i][j] = 0;
		 }
	}

	for (unsigned int i = 0; i != USER_NUM; ++i) {
		for (unsigned int j = 0; j != SIMULATE_TIME; ++j)
			cout << a[i][j];
		cout << endl;
	}
}


int
wait_for_random_time(int a[][SIMULATE_TIME], int userIndex, int curTime)
{
	srand((unsigned int)time(NULL) + userIndex);
	int wait = rand()%(SIMULATE_TIME/2) + FRAME_LEN;

	if ((curTime + wait + 1) >= SIMULATE_TIME) {
		for (unsigned int i = curTime; i != SIMULATE_TIME; ++i)
			a[userIndex][i] = 0;
	}
	else {
		for (unsigned int i = SIMULATE_TIME - 1; i != curTime + wait -1; --i)
			a[userIndex][i] = a[userIndex][i - wait];
		for (unsigned int i = curTime; i != curTime + wait; ++i)
			a[userIndex][i] = 0;
	}

	return wait;
}


int
check_collision(int a[][SIMULATE_TIME], unsigned int curTime)
{
	int oneNum = 0;

	for (unsigned int i = 0; i != USER_NUM; ++i) {
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
pure_aloha_simulate(int a[][SIMULATE_TIME], float p)
{
	int totalFrameNum = 0;
	int successFrameNum = 0;
	int collisTime[USER_NUM];
	int beginTime[USER_NUM];

	for (unsigned int i = 0; i != USER_NUM; ++i) {
		collisTime[i] = -1;
		beginTime[i] = -1;
	}

	generate_frame(a, p);

	for (unsigned int t = 0; t != SIMULATE_TIME - FRAME_LEN + 1; ++t) {
		cout << "t = " << t << ": " << endl;
		for (int i = 0; i != USER_NUM; ++i) {
			for (int j = 0; j != SIMULATE_TIME; ++j)
				cout << a[i][j];
			cout << endl;
		}

		for (unsigned int i = 0; i != USER_NUM; ++i) {
			if (a[i][t] == 1 && beginTime[i] == -1) {
				beginTime[i] = t;
				totalFrameNum++;
			}
		}

		if ((check_collision(a, t)) == COLLISION) {
			for (unsigned int i = 0; i != USER_NUM; ++i) {
				if (a[i][t] == 1 && collisTime[i] == -1)
					collisTime[i] = t;
			}
		}

		for (unsigned int i = 0; i != USER_NUM; ++i) {
			if (beginTime[i] != -1 && t == beginTime[i] + FRAME_LEN -1) {
				if (collisTime[i] == -1) {
					successFrameNum++;
					beginTime[i] = -1;
				}
				else {
					int waitTime = wait_for_random_time(a, i, beginTime[i]);
					beginTime[i] += waitTime;
					collisTime[i] = -1;
				}
			}
		}
	}

	cout << successFrameNum << " of " << totalFrameNum
		 << " are transmitted successfully." << endl;

//	total[n] = totalFrameNum;
//	success[n] = successFrameNum;
}


