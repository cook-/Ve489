#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define CONFLICT_HAPPEN    0     // ��ʱ���г�ͻ
#define NO_CONFLICT       1      // ��ʱ��û�г�ͻ
#define ARG_ERROR         2 
#define IDLE_TIME         3      // ��ʱ��û��վ��Ҫ����

class CHost
{

public:	
	CHost()
	{	
		//������Ա������ʼ��Ϊ�Ƿ���ֵ
		m_pOfSend = 1.0f;         
		m_timeToSend = 0;
		m_frameLen = 0;
		m_bHasSent = true;
	}

	CHost(const CHost& a)
	{
		m_pOfSend = a.m_pOfSend;
		m_timeToSend = a.m_timeToSend;
		m_frameLen = a.m_frameLen;
		m_bHasSent = a.m_bHasSent;
		m_timeOfSuccess = a.m_timeOfSuccess;
	}

	bool IsTimeToSend(int t);   // �ж�tʱ���Ƿ�Ҫ��������
	void WaitForRandomTime(int maxWaitTime, int t);      // �ȴ�һ���������ʱ�����ط�����
	void WaitForFixTime(int t); // �ȴ�ʱ��t�����ط�����
	void NextTimeToSend(bool slot, int t);  // ��һ��Ҫ���͵������ݵķ���ʱ��
	void SetProbOfSend(float p);   // ���ø�����ÿ��ʱ��Ҫ�������ݵĸ���
	void SetFrameLen(int len); // ���ø�����ÿ������֡�ĳ���
	void SetHasSent(bool b);    // �����Ƿ��Ѿ����ͳɹ�
	void SetSuccessTime(int t);
	CHost& operator=(const CHost& a);
	friend bool   operator<(CHost &a, CHost &b);
	friend CHost  operator+(CHost a, int b);

public:
	
	int m_timeToSend;      //�������������ݵ�ʱ��

	int m_frameLen; //��������֡�ĳ���

	float m_pOfSend;         // ���͸���

	bool m_bHasSent;        //�Ƿ��Ѿ����ͳɹ�

	int m_timeOfSuccess;
};

class CSimulator
{
public:

	
	void Reset();                 // �ָ���ʼ���ݣ��Ա㿪ʼ�µ�ģ��
	int PureAloha();             // ��ALOHA
	int SlotAloha();             // �ֲ�ALOHA
	int CSMA_1();                // ���CSMA
	int CSMA_P();                // P���CSMA
	int CSMA_0();                // �Ǽ��CSMA
	void ShowResult();            // ��ʾģ����
	int CheckConflict(int t); // �ж�tʱ���Ƿ�����ͻ
	int CarrierSense(int t);  // �ز�����
	void SetTime(int t);
	void SetSample( int sample);
	void SetUserNum( int user);
	void SetFrameLen( int len);
	void SetPofSend(float p);
	

	CHost& MinElement();
	CHost& SecondMinElement();

	int m_Sample;  //��������
	int m_frameLen; // ֡��
	int m_Time;           //ģ�ⵥλʱ������

private:

	
	
	int m_User;    //  �û���
	
	float m_pOfSend;         // ���͸���

	vector<CHost> HostVector;
	vector<CHost>::iterator IterHost;

};