/* Copyright (c) 2009  罗 敏 中南大学
*  All right reserved
*  
*  NetS3.h   本文件定义了一组函数，用于实现Pure ALOHA, Slot ALOHA, CSMA协议的仿真
*            未经原始作者许可，不许用作商业用途。使用者可自由复制，传播，修改用于非盈利性活动。
*		     对于使用本文件造成的一切损失，原始作者不负任何形式的责任。 
* 作       者： 罗 敏
* 完成日期：2009-04-01  20：53 
*/
#ifndef NETS3_HEADER_INCLUDE
#define NETS3_HEADER_INCLUDE
#include<stdlib.h>
#ifndef _AFX_WIN
typedef unsigned int UINT;
typedef const unsigned int CUINT;
#endif 
CUINT MAX_USER_NUMBER = 10;      // 最大独立站数目
CUINT MAX_TIME_SLOT  = 1000;     // 最大时间片数目,必须为MAX_FRAME_LEN的整数倍
CUINT MAX_FRAME_LEN = 4 ;       // 最大帧长

CUINT MAX_SIMULATE_TIMES = 1000; // 采样次数
CUINT MAX_WAIT_TIME = RAND_MAX/2;

#define CONFLICT_HAPPEN    0     // 该时刻有冲突
#define NO_CONFLICT       1      // 该时刻没有冲突
#define ARG_ERROR         2 
#define IDLE_TIME         3      // 该时刻没有站需要发送

typedef int NET_STATUS;

#include <cstdio>

/**********************************************************
*
* 输入:     整数数组a[][],大小为MAX_TIME_SLOT*MAX_USER_NUMBER
*           user 表示用户的编号
*           p 表示概率 0.0 - 1.0之间的有效浮点数
* 输出:     重新赋值的a[]
* 返回值:   无
* 功能描述: a[user]的每个元素按p的概率赋值1，1-p的概率赋值为0
*
************************************************************/
void GenerateFrameByProb(char *a, int user, float p );

/*************************************************************
* 输入:     整数数组a[][], 大小为MAX_TIME_SLOT*MAX_USER_NUMBER
*           user 表示用户的编号
*           pos 表示a[user][]中某个元素的下标 0 - MAX_TIME_SLOT-1 之间
* 
* 输出:     重新赋值的a[]
* 返回值:   无
* 功能描述: a[user]从a[user][pos]起的各个元素的值向后移动一个随机长度
*
**************************************************************/
int WaitForRandomTime( char *a, int user, UINT pos, int from_t );


/*************************************************************
* 输入:     整数数组a[], 大小为MAX_TIME_SLOT*MAX_USER_NUMBER
*           user 表示用户的编号
*           pos 表示a[]中某个元素的下标 0 - MAX_TIME_SLOT-1 之间
* 输出:     重新赋值的a[]
* 返回值:   无
* 功能描述: a[user]从a[user][pos]起的各个元素的值向后移动len个元素
*
**************************************************************/
void WaitForFixTime( char *a, int user, UINT pos, UINT len );

/**************************************************************
*  输入:     整数数组a[],大小为MAX_TIME_SLOT*MAX_USER_NUMBER
*           pos 表示a[]中某个元素的下标 0 - MAX_TIME_SLOT-1 之间
*           len 表示等待的时长
*  输出:     重新赋值的a[]
* 返回值:    无
*  功能描述: 讲a[]中各个元素赋值为 0
***************************************************************/

void InitUser(char *a);

/****************************************************************
* 输入:      整数数组a[][],大小为MAX_TIME_SLOT*MAX_USER_NUMBER
*            pos 表示位置 0-MAX_TIME_SLOT之间
* 输出:      无
* 
* 功能描述:  在参数正确的条件下，判断各维a[][pos]是否至少有两个1，若有则返回CONFLICT_HAPPEN
*            否则若0的个数等于MAX_USER_NUMBER则返回IDLE_TIME,其他情况返回 NO_CONFLICT.
* 返回值:    CONFLICT_HAPPEN 或者 NO_CONFLICT、ARG_ERROR(参数错误)
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
