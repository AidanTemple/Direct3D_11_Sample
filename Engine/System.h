#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "Input.h"
#include "FrameCounter.h"
#include "GameTime.h"
#include "GameScene.h"

class System
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Input* m_Input;
	FrameCounter* m_FrameCounter;
	GameTime* m_GameTime;
	GameScene* m_GameScene;
};

// Function Prototypes
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Globals
static System* ApplicationHandle = 0;