#include "limits.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int
main()
{
	int a[MAX_USER_NUM][MAX_SLOT_NUM];
	double p = 0.03;
	srand((unsigned)time(NULL));
	for (int i = 0; i != MAX_USER_NUM; ++i) {
		for (int j = 0; j != MAX_SLOT_NUM; ++j) {
			if (rand() < RAND_MAX*p) {
				for (int k = 0; k != MAX_FRAME_LEN && j != MAX_SLOT_NUM; ++k) {
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
	
	
	for (int i = 0; i != MAX_SLOT_NUM; ++i) {
		int cnt = 0;
		for (int j = 0; j != MAX_USER_NUM; ++j) {
			if (a[i][j] == 1)
				++cnt;
		}
		if (cnt > 1) {
		// wait for random time.
			}
		}
	}


	return 0;
}
