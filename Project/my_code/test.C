#include <iostream>
#include <sys/wait>
using namespace std;

int
main()
{
	for (int i = 0; i != 5; ++i) {
		cout << "sleep for 1s..." << endl;
		sleep(1);
	}
	return 0;
}
