#pragma once

#include <d3dx10math.h>

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);

	void SetFrameTime(float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

	void MoveForward(bool);
	void MoveBack(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUp(bool);
	void LookDown(bool);

private:
	float m_PositionX, m_PositionY, m_PositionZ;
	float m_RotationX, m_RotationY, m_RotationZ;

	float m_FrameTime;

	float m_ForwardSpeed, m_BackSpeed;
	float m_LeftSpeed, m_RightSpeed;
	float m_LookUpSpeed, m_LookDownSpeed;

	D3DXMATRIX m_viewMatrix;
};