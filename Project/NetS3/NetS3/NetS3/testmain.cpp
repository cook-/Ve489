#include "NetS3.h"
#include <cmath>
using namespace std;
int main()
{
	char *Host = new char[MAX_TIME_SLOT*MAX_USER_NUMBER];
	
	float s =0.0f;
	
	FILE *f1,*f2,*f3;

	f1 = fopen("PureAloha.txt", "w");
	for(int i=0; i<7; i++)
	{
		for(float p1 = 0.0f; p1 < 1.0f; p1+=0.1f)
		{
			CSMA_P(Host, s, p1);

			printf("%4.3f ", s/MAX_SIMULATE_TIMES);

		fprintf(f1, "%.3f,", s/MAX_SIMULATE_TIMES);
		}
		printf("\n");

		int j=10000;
		while(j--);
	}

	
	fclose(f1);
	printf("\n");
	f2 = fopen("SlotAloha.txt", "w");
	float s1 = 0.0f;
	for(float p2 = 0.0f; p2 < 1.0f; p2+=0.01f)
	{
		SlotAloha(Host, s1, p2);

		printf("%.3f ", s1/MAX_SIMULATE_TIMES);
		fprintf(f2, "%.3f,", s1/MAX_SIMULATE_TIMES);
	}
	
	fclose(f2);
	printf("\n");

	f3 = fopen("CSMA_1.txt", "w");
	float s2 = 0.0f;
	for(float p3 = 0.0f; p3 < 1.0f; p3+=0.01f)
	{
		CSMA_1(Host, s2, p3);

		printf("%.3f ", s2/MAX_SIMULATE_TIMES);
		fprintf(f3, "%.3f,", s2/MAX_SIMULATE_TIMES);
	}
	
	fclose(f3);
	return 0;
}
