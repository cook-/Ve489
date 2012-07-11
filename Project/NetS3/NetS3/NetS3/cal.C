#include <iostream>
#include <math.h>
using namespace std;

int
fac(double base, int exp)
{
	double result;
	for (int i = 0)
}

int
main()
{
	double result = 0;
	for (int i = 0; i != 9; ++i) {
		result += i*pow(0.7, i)*(pow(0.3, (10-i)));
	}
	cout << result << endl;
	return 0;
}
