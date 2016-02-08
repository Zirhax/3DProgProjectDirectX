#ifndef _TIMER_H_
#define _TIMER_H_
#include <windows.h>


class Timer
{
private:	//Variables
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
public:
	Timer();
	virtual ~Timer();
private:	//Functions

};

#endif