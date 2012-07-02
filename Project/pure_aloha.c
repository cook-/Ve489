/* simulation of pure ALOHA */

#include <stdio.h>

main()
{
	unsigned frm_len, bit_rate;
	double X;
	unsigned G;
	float S;

	printf("Enter frame length(Mb): ");
	scanf("%d", &frm_len);
	printf("Enter transmission rate(Mb/s): ");
	scanf("%d", &bit_rate);
	X = frm_len / bit_rate;
	printf("Enter the load(attempts per frame time): ");
	scanf("%d", &G);





}
