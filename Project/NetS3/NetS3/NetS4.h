#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

#define CONFLICT_HAPPEN    0     // 该时刻有冲突
#define NO_CONFLICT       1      // 该时刻没有冲突
#define ARG_ERROR         2 
#define IDLE_TIME         3      // 该时刻没有站需要发送

class CHost
{

public:	
	CHost()
	{	
		//将个成员变量初始化为非法的值
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

	bool IsTimeToSend(int t);   // 判断t时刻是否要发送数据
	void WaitForRandomTime(int maxWaitTime, int t);      // 等待一个随机长的时间再重发数据
	void WaitForFixTime(int t); // 等待时间t后再重发数据
	void NextTimeToSend(bool slot, int t);  // 下一个要发送的新数据的发送时刻
	void SetProbOfSend(float p);   // 设置该主机每个时刻要发送数据的概率
	void SetFrameLen(int len); // 设置该主机每个数据帧的长度
	void SetHasSent(bool b);    // 设置是否已经发送成功
	void SetSuccessTime(int t);
	CHost& operator=(const CHost& a);
	friend bool   operator<(CHost &a, CHost &b);
	friend CHost  operator+(CHost a, int b);

public:
	
	int m_timeToSend;      //该主机发送数据的时刻

	int m_frameLen; //该主机上帧的长度

	float m_pOfSend;         // 发送概率

	bool m_bHasSent;        //是否已经发送成功

	int m_timeOfSuccess;
};

class CSimulator
{
public:

	
	void Reset();                 // 恢复初始数据，以便开始新的模拟
	int PureAloha();             // 纯ALOHA
	int SlotAloha();             // 分槽ALOHA
	int CSMA_1();                // 坚持CSMA
	int CSMA_P();                // P坚持CSMA
	int CSMA_0();                // 非坚持CSMA
	void ShowResult();            // 显示模拟结果
	int CheckConflict(int t); // 判断t时刻是否发生冲突
	int CarrierSense(int t);  // 载波侦听
	void SetTime(int t);
	void SetSample( int sample);
	void SetUserNum( int user);
	void SetFrameLen( int len);
	void SetPofSend(float p);
	

	CHost& MinElement();
	CHost& SecondMinElement();

	int m_Sample;  //采样次数
	int m_frameLen; // 帧长
	int m_Time;           //模拟单位时间总数

private:

	
	
	int m_User;    //  用户数
	
	float m_pOfSend;         // 发送概率

	vector<CHost> HostVector;
	vector<CHost>::iterator IterHost;

};