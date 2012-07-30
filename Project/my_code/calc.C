#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int
main()
{
	fstream iFile;
	stringstream iStream;
	string line;
	iFile.open("result");
	int total = 0;
	int num;
	for (int i = 0; i != 100; ++i) {
		getline(iFile, line);
		iStream.str(line);
		iStream >> num;
		total += num;
	}
	cout << total/100 << (total/100)/250 << endl;

	total = 0;
	for (int i = 0; i != 100; ++i) {
		getline(iFile, line);
		iStream.str(line);
		iStream >> num;
		total += num;
	}
	cout << total/100 << (total/100)/250 << endl;

	return 0;
}
