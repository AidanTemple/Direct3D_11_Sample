#pragma once

#include <windows.h>

class GameTime
{
public:
	GameTime();
	GameTime(const GameTime&);
	~GameTime();

	bool Initialize();
	void Frame();

	float GetTime();

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};