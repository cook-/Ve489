#include "limits.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int
main()
{
	char *a[MAX_USER_NUM][MAX_TIME_SLOT];
	double p = 0.3;
	srand(time(NULL));
	for (int i = 0; i != MAX_USER_NUM; ++i) {
		for (int j = 0; j != MAX_TIME_SLOT; ++j) {
			if (rand() < (RAND_MAX + 1)*p) {
				for (int k = 0; k != MAX_FRAME_LEN && j != MAX_TIME_SLOT; ++k) {
					*(a+i*(MAX_TIME_SLOT)+j) = 1;
					++j;
				}
			}
			else
				*(a+i*(MAX_TIME_SLOT)+j) = 0;
		 }
	}

	for (int i = 0; i != MAX_USER_NUM; ++i) {
		for (int j = 0; j != MAX_TIME_SLOT; ++j) {
			cout << *(a+i*(MAX_TIME_SLOT)+j) << " ";
		}
		cout << endl;
	}
	
	return 0;
}
