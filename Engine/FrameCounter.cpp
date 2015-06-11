#include "FrameCounter.h"

FrameCounter::FrameCounter()
{

}

FrameCounter::FrameCounter(const FrameCounter& other)
{

}

FrameCounter::~FrameCounter()
{

}

void FrameCounter::Initialize()
{
	m_FrameRate = 0;
	m_FrameCount = 0;

	m_InitTime = timeGetTime();

	return;
}

void FrameCounter::Frame()
{
	m_FrameCount++;

	if(timeGetTime() >= (m_InitTime + 1000))
	{
		m_FrameRate = m_FrameCount;
		m_FrameCount = 0;
		
		m_InitTime = timeGetTime();
	}
}

int FrameCounter::GetFrameRate()
{
	return m_FrameRate;
}