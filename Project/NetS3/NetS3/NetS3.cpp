#include "NetS3.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

void GenerateFrameByProb(char *a, int user, float p )
{

	if ( p < 0.0 || p > 1.0)
	{
		printf("p should be between 0.0 and 1.0\n");

		return;
	}

	srand((unsigned int)(time(NULL))+user);

	for ( UINT i=0; i<MAX_TIME_SLOT-MAX_FRAME_LEN;  i++)
	{

		if( *(a+user*MAX_TIME_SLOT+i)==2)
		{
			if ( rand() < ((RAND_MAX+1)*p))
			{		
				

				for( UINT j=i; j<i+MAX_FRAME_LEN; j++)
				{	
					*(a+user*MAX_TIME_SLOT+j)= 1;
				}
			}
			else
			{
				
				*(a+user*MAX_TIME_SLOT+i) = 0;
				
			}
		}
		
	}

	for(int i=MAX_TIME_SLOT-MAX_FRAME_LEN; i<MAX_TIME_SLOT; i++)
	{
		if( *(a+user*MAX_TIME_SLOT+i)==2)
		{
			*(a+user*MAX_TIME_SLOT+i) = 0;
		}
	}

}


int WaitForRandomTime(char *a, int user, UINT pos, int from_t)
{

	if ( pos <0  || pos >=MAX_TIME_SLOT )
	{
		printf("pos must be between 0 and %d \n",MAX_TIME_SLOT-1);

		exit(0);
	}

	srand((unsigned int)time(NULL)+user);

	UINT len =0;

	while(!len)
	{
		len = (UINT)rand()%MAX_WAIT_TIME+from_t;
	}

	if (len >= (MAX_TIME_SLOT-pos-1))
	{
		for (UINT i=pos; i< MAX_TIME_SLOT; i++)
		{
			*(a+user*MAX_TIME_SLOT+i) = 0;
		}
	}
	else
	{
		for (UINT i= MAX_TIME_SLOT-1; i >= pos+len; i--)
		{
			*(a+user*MAX_TIME_SLOT+i) = *(a+user*MAX_TIME_SLOT+i-len);
		}

		for (UINT j=pos; j< pos+len; j++)
		{
			*(a+user*MAX_TIME_SLOT+j) = 0;
		}
	}

	return len;
}

void WaitForFixTime( char *a, int user, UINT pos, UINT len)
{
	if ( pos < 0  || pos >= MAX_TIME_SLOT )
	{
		printf("pos must be between 0 and %d \n",MAX_TIME_SLOT-1);

		return;
	}

	if ( len < 0  || len >= MAX_TIME_SLOT )
	{
		printf("len must be between 0 and %d \n",MAX_TIME_SLOT-1);

		return;
	}

	for (UINT i= MAX_TIME_SLOT-1; i >= pos+len; i--)
	{
		*(a+user*MAX_TIME_SLOT+i) = *(a+user*MAX_TIME_SLOT+i-len);
	}

	for (UINT j=pos; j< pos+len; j++)
	{
		*(a+user*MAX_TIME_SLOT+j) = 0;
	}
}

void InitUser(char *a)
{
	for (UINT i=0; i<MAX_USER_NUMBER; i++)
	{
		for (UINT j=0; j<MAX_TIME_SLOT; j++)
		{
			*(a+i*MAX_TIME_SLOT+j) = 2;
		}
	}
}


NET_STATUS CheckConflict(char *a, UINT pos)
{
	if ( pos < 0  || pos >= MAX_TIME_SLOT )
	{
		printf("pos must be between 0 and %d \n",MAX_TIME_SLOT-1);

		return ARG_ERROR;
	}

	int k=0;

	int j=0;

	for(UINT i=0; i<MAX_USER_NUMBER; i++)
	{

		if ( 1==*(a+i*MAX_TIME_SLOT+pos) )
		{
			k++; 
		}
		else
		{
			j++;
		}

	}

	if ( k>1)
	{
		return CONFLICT_HAPPEN;
	}
	else if (j<MAX_USER_NUMBER )
	{
		return NO_CONFLICT;
	}
	else
	{
		return IDLE_TIME;
	}
}


void PureAloha(char *a, float p)
{

	int total = 0;
	int s = 0; //初始化s为0.0

	int *conllision = new int[MAX_USER_NUMBER]; //记录每个用户发生冲突的时刻
	int *pos  = new int[MAX_USER_NUMBER];   // 记录每个用户待发帧的开始位置
	for ( UINT i=0; i<MAX_USER_NUMBER; i++)
	{
		conllision[i] = -1;
		pos[i] = -1;
	}

	InitUser(a);

	//DisplayInfo(a);

	//printf("\n");

	

		for ( UINT k=0; k<MAX_USER_NUMBER; k++)
		{
			GenerateFrameByProb(a, k, p); //初始化各个独立站

		}

		for ( UINT t=0; t<MAX_TIME_SLOT-MAX_FRAME_LEN+1; t++)
		{

			//printf("t = %d\n" ,t);
			//DisplayInfo(a);

			for ( UINT n=0; n<MAX_USER_NUMBER; n++)
			{
				if ( (1== a[n*MAX_TIME_SLOT+t]) && (-1 == pos[n]))
				{
					pos[n] = t; // 记录每个主机新帧的开始位置
					total++;
				}

			}

			int status = CheckConflict(a, t); // 当前时刻是否有冲突发生

			if ( status == CONFLICT_HAPPEN )
			{
				for(UINT j=0; j<MAX_USER_NUMBER; j++)
				{
					if ( 1== a[j*MAX_TIME_SLOT+t] )
					{
						if ( conllision[j] == -1)	
						{
							conllision[j] = t; // 每个发生冲突的主机记录下发生冲突的时间							
						}

					} 
				}   		

			}

			for ( UINT n=0; n<MAX_USER_NUMBER; n++)
			{

				if ( -1 !=pos[n] && t == (pos[n]+MAX_FRAME_LEN-1))
				{
					if( -1 == conllision[n]) //在整个帧时内没有发生冲突
					{
						s++;
						//printf("success\n");
						pos[n] = -1; //等待新帧
					}
					else     // 发生冲突
					{
						// 经过一个帧时知道发生冲突，并重发
						int len = WaitForRandomTime(a, n, pos[n], MAX_FRAME_LEN);

						pos[n] = pos[n] + len;

						conllision[n] = -1; // 监测下一次冲突
					}
				}
			}
			//DisplayInfo(a);
		}
		
	printf("%d of %d\n", s, total);
	//s = s/MAX_SIMULATE_TIMES; 
}

void SlotAloha(char *a, float p)
{
	int s = 0; 

	int *pos = new int[MAX_USER_NUMBER];
	

	for(UINT n=0; n < MAX_USER_NUMBER; n++)
	{
		pos[n] = -1;
	}

	InitUser(a);

	

		//printf("初始化：\n");

		for ( UINT user=0; user<MAX_USER_NUMBER; user++)
		{
			GenerateFrameByProb(a, user, p); //初始化各个独立站

		}

		for ( UINT t=0; t<MAX_TIME_SLOT-MAX_FRAME_LEN+1; t++)
		{

			//printf("t=%d\n", t);

			//DisplayInfo(a);

			for( UINT user=0; user<MAX_USER_NUMBER; user++)
			{
				if (-1==pos[user] && a[user*MAX_TIME_SLOT+t])
				{
					pos[user] = t;

					if ( t%MAX_FRAME_LEN )
					{
						int waittime = MAX_FRAME_LEN-t%MAX_FRAME_LEN;

						WaitForFixTime(a, user, pos[user], waittime);
						pos[user] = -1;
					}
				}
				else if (pos[user]!=-1&& (pos[user]+MAX_FRAME_LEN-1)==t)
				{
					pos[user] = -1;
				}
			}

			if ( 0 == (t%MAX_FRAME_LEN) )
			{
				int status = CheckConflict(a, t);

				if (status == NO_CONFLICT)
				{
					//printf("success\n");

					s++;

				}
				if (status == CONFLICT_HAPPEN)
				{
					for( UINT user=0; user<MAX_USER_NUMBER; user++)
					{

						if( pos[user] == t )
						{
							WaitForRandomTime(a, user, pos[user], MAX_FRAME_LEN);

							pos[user] = -1;
						}

					}
				}
			}
		}

	
	//printf("s = %f\n", s);
}
void CSMA_0(char *a, float p)
{

	int s = 0;

	int startTime = -1;
	int busy = 0;
	int currentUser = -1;

	InitUser(a);

	

		for ( UINT user=0; user<MAX_USER_NUMBER; user++)
		{
			GenerateFrameByProb(a, user, p); //初始化各个独立站

		}	

		

			//printf("t=%d \n", t);
			//DisplayInfo(a);
	for( int t=0; t<MAX_TIME_SLOT-MAX_FRAME_LEN-1; t++)
	{	
			if(!busy)
			{
				int status = CheckConflict(a, t);

				if (status == NO_CONFLICT) //t时刻只有一个主机发送数据
				{
					startTime = t;
					busy =1;

					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if (a[n*MAX_TIME_SLOT+t])
						{
							currentUser = n;
						}
					}

				}

				if(status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if (a[n*MAX_TIME_SLOT+t])
						{
							WaitForRandomTime(a, n, t, 0);
						}
					}
				}
			}
			else
			{


				if(t==(startTime+MAX_FRAME_LEN-1))
				{
					s++;
					//printf("success\n");
					busy = 0;
				}

				int status = CheckConflict(a, t);
				if (status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if((n!=currentUser)&&a[n*MAX_TIME_SLOT+t])
						{
							WaitForRandomTime(a, n, t, 0);
						}
					}
				}
			}




		}



		//printf("s= %.3f", s / MAX_SIMULATE_TIMES);

	
}

void CSMA_1(char *a, float p)
{

	int s = 0;

	int startTime = -1;
	int busy = 0;
	int currentUser = -1;

	InitUser(a);

		

		for ( UINT user=0; user<MAX_USER_NUMBER; user++)
		{
			GenerateFrameByProb(a, user, p); //初始化各个独立站

		}	

		for ( int t=0; t<MAX_TIME_SLOT-MAX_FRAME_LEN+1; t++)
		{

			//printf("t=%d \n", t);
			//DisplayInfo(a);

			if(!busy)
			{
				int status = CheckConflict(a, t);

				if (status == NO_CONFLICT) //t时刻只有一个主机发送数据
				{
					startTime = t;
					busy =1;

					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if (a[n*MAX_TIME_SLOT+t])
						{
							currentUser = n;
						}
					}

				}
				if(status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if (a[n*MAX_TIME_SLOT+t])
						{
							WaitForRandomTime(a, n, t, 0);							
						}
					}
				}
			}
			else
			{


				if(t==(startTime+MAX_FRAME_LEN-1))
				{
					s++;
					//printf("success\n");
					busy = 0;
				}

				int status = CheckConflict(a, t);
				if (status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if((n!=currentUser)&&a[n*MAX_TIME_SLOT+t])
						{

							WaitForFixTime(a, n, t, 1);
						}
					}
				}
			}




		}



		//printf("s= %.3f", s / MAX_SIMULATE_TIMES);

	
}
void CSMA_P(char *a, float p)
{
	int s = 0;

	int startTime = -1;
	int busy = 0;
	int currentUser = -1;

	InitUser(a);

	for(int i=0; i<MAX_SIMULATE_TIMES; i++)
	{

		for ( UINT user=0; user<MAX_USER_NUMBER; user++)
		{
			GenerateFrameByProb(a, user, p); //初始化各个独立站

		}	

		for ( int t=0; t<MAX_TIME_SLOT-MAX_FRAME_LEN+1; t++)
		{

			//printf("t=%d \n", t);
			//DisplayInfo(a);

			if(!busy)
			{
				int status = CheckConflict(a, t);

				if (status == NO_CONFLICT) //t时刻只有一个主机发送数据
				{
					srand((unsigned int)time(NULL));

					if(rand() < (RAND_MAX+1) *1)
					{
						startTime = t;
						busy =1;

						for(int n=0; n<MAX_USER_NUMBER; n++)
						{
							if (a[n*MAX_TIME_SLOT+t])
							{
								currentUser = n;
							}
						}
					}
					else
					{
						for(int n=0; n<MAX_USER_NUMBER; n++)
						{
							if (a[n*MAX_TIME_SLOT+t])
							{
								WaitForFixTime(a, n, t, MAX_FRAME_LEN);
							}
						}
					}

				}
				if(status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if (a[n*MAX_TIME_SLOT+t])
						{
							WaitForRandomTime(a, n, t, 0);							
						}
					}
				}
			}
			else
			{

				if(t==(startTime+MAX_FRAME_LEN-1))
				{
					s = s + 1.0f;
					//printf("success\n");
					busy = 0;
				}

				int status = CheckConflict(a, t);
				if (status == CONFLICT_HAPPEN)
				{
					for(int n=0; n<MAX_USER_NUMBER; n++)
					{
						if((n!=currentUser)&&a[n*MAX_TIME_SLOT+t])
						{

							WaitForFixTime(a, n, t, startTime+MAX_FRAME_LEN-t);
						}
					}
				}
			}




		}



		//printf("s= %.3f", s / MAX_SIMULATE_TIMES);
	}
	
}
void DisplayInfo(char *a)
{
	for ( UINT i=0; i<MAX_USER_NUMBER; i++)
	{
		for (UINT j=0; j<MAX_TIME_SLOT; j++)
		{
			printf("%d ", *(a+i*MAX_TIME_SLOT+j));
		}
		printf("\n");
	}

	printf("\n");
}
