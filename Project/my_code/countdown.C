#include <iostream>
#include "unistd.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

int
main()
{
    int m,s;
    cout << "\n\n\n\t\t\t A COUNTDOWN TIMER \n";
    cout << "enter time in MINUTES here \t = \t";
    cin >> m;
    cout << "enter time in SECONDS here \t = \t";
    cin >> s;
    cout << "\n\n\n\n\t press any key to start...!!!";
    getch();
    clrscr();
    cout << "\n\n\n\t\t\t A COUNTDOWN TIMER \n";
    cout << "\n\n\n\t\t TIME REMAINIG \n\n";
    cout << "\t mins: \t\t seconds: ";
    for(int min = m; min > 0; min--) {
	    for(int sec = 59; sec >= 0; sec--) {
		    sleep(1);
	    	cout << "\r" << min << "\t" << sec;
		}
    }
	for(int rem = s; rem >= 0; rem--) {
		cout << "\r" << min << "\t" << rem;
	}

	cout << "\n\n ENDED ";
	return 0;
	} 
