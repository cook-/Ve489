#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

int
main()
{
	fstream iFile;
	istringstream iStream;
	string line;
	iFile.open("result");
	int num;
	int total = 0;
	for (int i = 0; i != 100; ++i) {
		getline(iFile, line);
		iStream.str(line);
		iStream >> num;
		total += num;
	}
	cout << total/100 << " " << ((float)total/100)/250 << endl;

	total = 0;
	for (int i = 0; i != 100; ++i) {
		getline(iFile, line);
		iStream.str(line);
		iStream >> num;
		total += num;
	}
	cout << total/100 << " " << ((float)total/100)/250 << endl;

	iFile.close();
	return 0;
}
