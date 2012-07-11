#include <iostream>
using namespace std;
int
main()
{
	int result = 0;
	for (int i = 0; i != 9; ++i) {
		result += i*(0.7^i)*(0.3^(10-i));
	}
	cout << result << endl;
	return 0;
}
