#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int
main()
{
	fstream iFile;
	string line;
	iFile.open("result");
	int total = 0;
	for (int i = 0; i != 100; ++i) {
		getline(iFile, line);
		iStream.str(line);
		iStream >> num;
		total += num;
	}
	cout << total/100 << endl;


	return 0;
}
