#pragma once

#include "Direct3D.h"
#include "GameTime.H"
#include "Input.h"
#include "Camera.h"
#include "Model.h"
#include "BumpMapShader.h"
#include "SpecularMapShader.h"
#include "AlphaMapShader.h"
#include "LightShader.h"
#include "Light.h"
#include "SkyDome.h"
#include "SkyDomeShader.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 5000.0f;
const float SCREEN_NEAR = 1.0f;

class GameScene
{
public:
	GameScene();
	GameScene(const GameScene&);
	~GameScene();

	bool Initialize(HINSTANCE, int, int, HWND);
	void Shutdown();
	bool Frame(float, int);
	bool UpdateInput(float);
	bool Render();

private:
	Direct3D* m_D3D;

	Camera* m_Camera;
	BumpMapShader* m_BumpMapShader;
	SpecularMapShader* m_SpecularShader;
	AlphaMapShader* m_AlphaMapShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	Input* m_Input;
	GameTime* m_GameTime;
	SkyDome* m_SkyDome;
	SkyDomeShader* m_SkyDomeShader;

	ModelClass* m_Grass;
	ModelClass* m_Floor;
	ModelClass* m_Coloumns;
	ModelClass* m_IvyExterior;
	ModelClass* m_IvyInterior;
	ModelClass* m_Rock;
	ModelClass* m_Planks;
	ModelClass* m_Wall;
	ModelClass* m_WallsLower;
	ModelClass* m_WallsUpper;
	ModelClass* m_Beams;
	ModelClass* m_Table;
	ModelClass* m_Tree;
	ModelClass* m_Roof;
	ModelClass* m_RoofSupports;
	ModelClass* m_HangingCauldron;

	float m_Counter;
};