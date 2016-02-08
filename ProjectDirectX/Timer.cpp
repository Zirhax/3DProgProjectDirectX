#include "Timer.h"



Timer::Timer()
{
	this->m_frequency = 0;
	this->m_ticksPerMs = 0;
	this->m_startTime = 0;
	this->m_frameTime = 0;
}


Timer::~Timer()
{
}
