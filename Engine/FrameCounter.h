#pragma once

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class FrameCounter
{
public:
	FrameCounter();
	FrameCounter(const FrameCounter&);
	~FrameCounter();

	void Initialize();
	void Frame();

	int GetFrameRate();

private:
	int m_FrameRate;
	int m_FrameCount;
	unsigned long m_InitTime;
};