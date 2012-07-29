/* Copyright (c) 2009  �� �� ���ϴ�ѧ
*  All right reserved
*  
*  NetS3.h   ���ļ�������һ�麯��������ʵ��Pure ALOHA, Slot ALOHA, CSMAЭ��ķ���
*            δ��ԭʼ������ɣ�����������ҵ��;��ʹ���߿����ɸ��ƣ��������޸����ڷ�ӯ���Ի��
*		     ����ʹ�ñ��ļ���ɵ�һ����ʧ��ԭʼ���߲����κ���ʽ�����Ρ� 
* ��       �ߣ� �� ��
* ������ڣ�2009-04-01  20��53 
*/
#ifndef NETS3_HEADER_INCLUDE
#define NETS3_HEADER_INCLUDE
#include<stdlib.h>
#ifndef _AFX_WIN
typedef unsigned int UINT;
typedef const unsigned int CUINT;
#endif 
CUINT MAX_USER_NUMBER = 10;      // ������վ��Ŀ
CUINT MAX_TIME_SLOT  = 1000;     // ���ʱ��Ƭ��Ŀ,����ΪMAX_FRAME_LEN��������
CUINT MAX_FRAME_LEN = 4 ;       // ���֡��

CUINT MAX_SIMULATE_TIMES = 1000; // ��������
CUINT MAX_WAIT_TIME = RAND_MAX/2;

#define CONFLICT_HAPPEN    0     // ��ʱ���г�ͻ
#define NO_CONFLICT       1      // ��ʱ��û�г�ͻ
#define ARG_ERROR         2 
#define IDLE_TIME         3      // ��ʱ��û��վ��Ҫ����

typedef int NET_STATUS;

#include <cstdio>

/**********************************************************
*
* ����:     ��������a[][],��СΪMAX_TIME_SLOT*MAX_USER_NUMBER
*           user ��ʾ�û��ı��
*           p ��ʾ���� 0.0 - 1.0֮�����Ч������
* ���:     ���¸�ֵ��a[]
* ����ֵ:   ��
* ��������: a[user]��ÿ��Ԫ�ذ�p�ĸ��ʸ�ֵ1��1-p�ĸ��ʸ�ֵΪ0
*
************************************************************/
void GenerateFrameByProb(char *a, int user, float p );

/*************************************************************
* ����:     ��������a[][], ��СΪMAX_TIME_SLOT*MAX_USER_NUMBER
*           user ��ʾ�û��ı��
*           pos ��ʾa[user][]��ĳ��Ԫ�ص��±� 0 - MAX_TIME_SLOT-1 ֮��
* 
* ���:     ���¸�ֵ��a[]
* ����ֵ:   ��
* ��������: a[user]��a[user][pos]��ĸ���Ԫ�ص�ֵ����ƶ�һ���������
*
**************************************************************/
int WaitForRandomTime( char *a, int user, UINT pos, int from_t );


/*************************************************************
* ����:     ��������a[], ��СΪMAX_TIME_SLOT*MAX_USER_NUMBER
*           user ��ʾ�û��ı��
*           pos ��ʾa[]��ĳ��Ԫ�ص��±� 0 - MAX_TIME_SLOT-1 ֮��
* ���:     ���¸�ֵ��a[]
* ����ֵ:   ��
* ��������: a[user]��a[user][pos]��ĸ���Ԫ�ص�ֵ����ƶ�len��Ԫ��
*
**************************************************************/
void WaitForFixTime( char *a, int user, UINT pos, UINT len );

/**************************************************************
*  ����:     ��������a[],��СΪMAX_TIME_SLOT*MAX_USER_NUMBER
*           pos ��ʾa[]��ĳ��Ԫ�ص��±� 0 - MAX_TIME_SLOT-1 ֮��
*           len ��ʾ�ȴ���ʱ��
*  ���:     ���¸�ֵ��a[]
* ����ֵ:    ��
*  ��������: ��a[]�и���Ԫ�ظ�ֵΪ 0
***************************************************************/

void InitUser(char *a);

/****************************************************************
* ����:      ��������a[][],��СΪMAX_TIME_SLOT*MAX_USER_NUMBER
*            pos ��ʾλ�� 0-MAX_TIME_SLOT֮��
* ���:      ��
* 
* ��������:  �ڲ�����ȷ�������£��жϸ�άa[][pos]�Ƿ�����������1�������򷵻�CONFLICT_HAPPEN
*            ������0�ĸ�������MAX_USER_NUMBER�򷵻�IDLE_TIME,����������� NO_CONFLICT.
* ����ֵ:    CONFLICT_HAPPEN ���� NO_CONFLICT��ARG_ERROR(��������)
******************************************************************/

NET_STATUS CheckConflict(char *a, UINT pos);


NET_STATUS CarrierSense(char *a, UINT pos);

void PureAloha(char *a, float p);

void SlotAloha(char *a, float p);

void CSMA_0(char *a, float& s, float p);
void CSMA_1(char *a, float& s, float p);
void CSMA_P(char *a, float&s, float p);
void DisplayInfo(char *a);

#endif
