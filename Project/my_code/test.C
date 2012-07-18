#include <iostream>
#include "unistd.h"
using namespace std;

int
main()
{
	for (int i = 0; i != 5; ++i) {
		cout << "sleep for 10s..." << endl;
		sleep(1);
	}
	return 0;
}
