#include "NetS4.h"
#include <iterator>
#include <algorithm>
using namespace std;


void CHost::SetFrameLen(int len)
{
	m_frameLen = len;
}

void CHost::SetProbOfSend(float p)
{
	if ( p <0.0f ) 
	{
		m_pOfSend = 0.0f;
	}
	else if ( p>1.0f)
	{
		m_pOfSend = 1.0f;
	}
	else
	{
		m_pOfSend = p;
	}

}

bool CHost::IsTimeToSend(int t)
{
	if ( t == m_timeToSend)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CHost::NextTimeToSend(bool slot, int t) // t 当前时刻
{

	if (m_bHasSent) // 只有当前的数据发送成功了，才会产生新的数据包
	{

		if (rand() < ((RAND_MAX+1)*m_pOfSend)) // 按概率发送数据
		{
			
				if ( t>=m_timeOfSuccess+m_frameLen)
				{
					m_timeToSend = t;   //当前时刻将发送数据
				}
				else
				{
					m_timeToSend = m_timeOfSuccess+m_frameLen;
				}

				SetHasSent(false);    //通知有新数据发送
		}		
		else
		{
			m_timeToSend = 65535;
		}

	}


}


void CHost::WaitForFixTime(int t)
{
	
	m_timeToSend = m_timeToSend +  m_frameLen;
	
	m_timeToSend+= m_frameLen*(rand()%m_frameLen + 1);
}

void CHost::WaitForRandomTime(int maxWaitTime, int t)
{
	m_timeToSend = (rand()%maxWaitTime) + t + 1;
}

void CHost::SetHasSent(bool b)
{
	m_bHasSent = b;
}

void CHost::SetSuccessTime(int t)
{
	m_timeOfSuccess = t;
}
bool operator<(CHost &a, CHost &b)
{
	if ( a.m_timeToSend < b.m_timeToSend )
	{
		return true;
	}
	else
	{
		return false;
	}
}

CHost operator+(CHost a, int b)
{
	a.m_timeToSend = a.m_timeToSend + b;

	return a;
}



void CSimulator::SetFrameLen(int len)
{
	if ( len < 1)
	{
		m_frameLen = 1;
	}
	else 
	{
		m_frameLen = len;
	}
}


CHost& CHost::operator=(const CHost& a)
{
	m_bHasSent = a.m_bHasSent;
	m_frameLen = a.m_frameLen;
	m_pOfSend  = a.m_pOfSend;
	m_timeToSend = a.m_timeToSend;
	m_timeOfSuccess = a.m_timeOfSuccess;

	return *this;

}
void CSimulator::SetTime(int t)
{
	if ( t<1)
	{
		m_Time = 1;
	}
	else
	{
		m_Time = t;
	}
}

void CSimulator::SetSample(int sample)
{
	if ( sample < 1)
	{
		m_Sample = 1;
	}
	else
	{
		m_Sample = sample;
	}
}

void CSimulator::SetUserNum(int user)
{
	if ( user < 2)
	{
		m_User = 2;
	}
	else
	{
		m_User = user;
	}
}

void CSimulator::Reset()
{
	CHost *h = new CHost[m_User];

	if (HostVector.size() !=0)
	{
		HostVector.erase(HostVector.begin(), HostVector.end());
	}
	for (int i=0; i<m_User; i++)
	{
		HostVector.push_back(h[i]);
	}

	for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
	{
		(*IterHost).SetFrameLen(m_frameLen);
		(*IterHost).SetSuccessTime(-1*m_frameLen);
	}


}

int CSimulator::CheckConflict(int t)
{
	int k = 0;

	CHost min;
	CHost secondMin;

	for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
	{
		if ((*IterHost).IsTimeToSend(t))
		{
			k++;
		}
	}

	if ( k>1 )
	{
		return CONFLICT_HAPPEN;
	}
	else if ( k < 1)
	{
		return IDLE_TIME;
	}
	else
	{
		min = MinElement();

		secondMin = SecondMinElement();

		if ( secondMin < min+m_frameLen)
		{

			return CONFLICT_HAPPEN;
		}
		else
		{
			return NO_CONFLICT;
		}
	}
}

void CSimulator::SetPofSend(float p)
{

	for( IterHost= HostVector.begin(); IterHost!=HostVector.end(); IterHost++)
	{
		(*IterHost).SetProbOfSend(p);
	}

}

void CSimulator::ShowResult()
{
	for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
	{
		cout<< (*IterHost).m_timeToSend << " " ;
	}
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

CHost& CSimulator::MinElement()
{
	vector<CHost>::iterator iter;

	int min = 65535;

	int i = 0;
	int k = 0;

	for ( iter = HostVector.begin(); iter != HostVector.end(); iter++)
	{

		if( (*iter).m_timeToSend < min )
		{
			min = (*iter).m_timeToSend;

			k = i;
		}
		i++;
	}

	return HostVector.at(k);
}

CHost& CSimulator::SecondMinElement()
{
	CHost &min = MinElement();

	int secondMin = 65535; 

	int k=0;

	for(int i=0; i < (int)HostVector.size(); i++)
	{
		if ( (HostVector[i].m_timeToSend > min.m_timeToSend) && (HostVector[i].m_timeToSend <= secondMin))
		{
			secondMin = HostVector[i].m_timeToSend;

			k = i;
		}

	}

	return HostVector.at(k);
}

int CSimulator::PureAloha()
{	

	int s = 0;

	CHost min;
	CHost second;

	srand((unsigned int)time(NULL));


	int st = 0;


	for ( int t=0; t<m_Time; t++)
	{
		//printf("t = %d ", t);	

		if ( t==0)
		{
			for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
			{
				(*IterHost).NextTimeToSend(false,0);
			}
		}
		else
		{
			for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
			{
				(*IterHost).NextTimeToSend(false, t);
			}
		}

		//ShowResult();

		int status = CheckConflict(t);

		if ( status == NO_CONFLICT)
		{

			CHost& min1 = MinElement();

			min1.SetHasSent(true); //通知已发送成功



			//printf("Success!\n");

			min1.SetSuccessTime(t);

			s++;
		}
		if ( status == CONFLICT_HAPPEN)
		{
			min = MinElement();

			//printf("min = %d ", min.m_timeToSend);

			second = SecondMinElement();

			//printf("second = %d ", second.m_timeToSend);

			if ( second < (min+m_frameLen))
			{

				for( IterHost = HostVector.begin(); IterHost!=HostVector.end(); IterHost++)
				{
					if ( (*IterHost).m_timeToSend == min.m_pOfSend)
					{
						(*IterHost).WaitForRandomTime(m_frameLen*2, second.m_pOfSend);
					}
					if ( (*IterHost).m_timeToSend  < (min.m_timeToSend +m_frameLen) )
					{
						(*IterHost).WaitForRandomTime(m_frameLen*m_User, (*IterHost).m_timeToSend);
					}
				}
			}
			else
			{
				for( IterHost = HostVector.begin(); IterHost!=HostVector.end(); IterHost++)
				{
					if ( (*IterHost).m_timeToSend == min.m_timeToSend )
					{
						(*IterHost).WaitForRandomTime(m_frameLen*m_User, min.m_timeToSend);
					}
				}
			}
			//printf("Conflict\n");
		}

	}		
	//printf("%d \n", s);
	return s;
}







int CSimulator::SlotAloha()
{
	int s = 0;

	int st = 0; // 发送成功时的刻

	CHost min;
	CHost second;

	srand((unsigned int)time(NULL));

	for ( int t=0; t<m_Time; t++)
	{
		//printf("t = %d ", t);	


		if ( t==0)
		{
			for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
			{
				(*IterHost).NextTimeToSend(true,0);
			}
		}
		else
		{
			for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
			{
				(*IterHost).NextTimeToSend(true, t);
			}
		}

		//ShowResult();

		int status = CheckConflict(t);

		if ( status == NO_CONFLICT)
		{
			
			if ( t%m_frameLen )
			{
				for ( IterHost = HostVector.begin(); IterHost != HostVector.end(); IterHost++)
				{
					if((*IterHost) < (t  + m_frameLen - (t%m_frameLen)))
					{
						(*IterHost).m_timeToSend = t  + m_frameLen - (t%m_frameLen)
					}
				}

			}
			else
			{
				CHost& min1 = MinElement();

				min1.SetHasSent(true); //通知已发送成功

				///printf("Success!\n");

				min1.SetSuccessTime(t); // 成功的时刻

				s++;
			}
		}
		if ( status == CONFLICT_HAPPEN)
		{
			min = MinElement();

			//printf("min = %d ", min.m_timeToSend);


			second = SecondMinElement();
			//printf("second = %d ", second.m_timeToSend);


			if ( )
			{

				for( IterHost = HostVector.begin(); IterHost!=HostVector.end(); IterHost++)
				{
					if ( (*IterHost).m_timeToSend == second.m_pOfSend)
					{
						(*IterHost).WaitForRandomTime(m_frameLen*2, second.m_pOfSend);
					}
					if ( (*IterHost).m_timeToSend  < (min.m_timeToSend +m_frameLen) )
					{
						(*IterHost).WaitForRandomTime(m_frameLen*m_User, (*IterHost).m_timeToSend);
					}
				}
			}
			else
			{
				for( IterHost = HostVector.begin(); IterHost!=HostVector.end(); IterHost++)
				{
					if ( (*IterHost).m_timeToSend == min.m_timeToSend )
					{
						(*IterHost).WaitForRandomTime(m_frameLen*m_User, min.m_timeToSend);
					}
				}
			}

			//printf("Conflict\n");
		}		


	}

	//printf("%d \n", s);

	return s;
}