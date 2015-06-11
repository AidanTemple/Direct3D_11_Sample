#include "Camera.h"

Camera::Camera()
{
	m_PositionX = 0.0f;
	m_PositionY = 0.0f;
	m_PositionZ = 0.0f;

	m_RotationX = 0.0f;
	m_RotationY = 0.0f;
	m_RotationZ = 0.0f;

	m_FrameTime = 0;

	m_ForwardSpeed = 0;
	m_BackSpeed = 0;
	m_LeftSpeed = 0;
	m_RightSpeed = 0;
	m_LookUpSpeed = 0;
	m_LookDownSpeed = 0;
}

Camera::Camera(const Camera& other)
{

}

Camera::~Camera()
{

}

void Camera::SetFrameTime(float delta)
{
	m_FrameTime = delta;

	return;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_PositionX = x;
	m_PositionY = y;
	m_PositionZ = z;

	return;
}

void Camera::SetRotation(float x, float y, float z)
{
	m_RotationX = x;
	m_RotationY = y;
	m_RotationZ = z;

	return;
}

void Camera::GetPosition(float& x, float& y, float& z)
{
	x = m_PositionX;
	y = m_PositionY;
	z = m_PositionZ;

	return;
}

void Camera::GetRotation(float& x, float& y, float& z)
{
	x = m_RotationX;
	y = m_RotationY;
	z = m_RotationZ;

	return;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(m_PositionX, m_PositionY, m_PositionZ);
}

D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(m_RotationX, m_RotationY, m_RotationZ);
}

void Camera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_PositionX;
	position.y = m_PositionY;
	position.z = m_PositionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_RotationX * 0.0174532925f;
	yaw   = m_RotationY * 0.0174532925f;
	roll  = m_RotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}

void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void Camera::MoveForward(bool keydown)
{
	float radians;

	// Update the forward speed movement based on the frame time 
	// and whether the user is holding the key down or not.
	if(keydown)
	{
		m_ForwardSpeed += m_FrameTime * 0.01f;

		if(m_ForwardSpeed > (m_FrameTime * 0.07f))
		{
			m_ForwardSpeed = m_FrameTime * 0.07f;
		}
	}

	// Convert degrees to radians.
	radians = m_RotationY * 0.0174532925f;

	// Update the position.
	m_PositionX += sinf(radians) * m_ForwardSpeed;
	m_PositionZ += cosf(radians) * m_ForwardSpeed;

	return;
}

void Camera::MoveBack(bool keydown)
{
	float radians;

	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_BackSpeed += m_FrameTime * 0.01f;

		if(m_BackSpeed > (m_FrameTime * 0.07f))
		{
			m_BackSpeed = m_FrameTime * 0.07f;
		}
	}
	else
	{
		m_BackSpeed = 0;
	}

	// Convert degrees to radians.
	radians = m_RotationY * 0.0174532925f;

	// Update the position.
	m_PositionX -= sinf(radians) * m_BackSpeed;
	m_PositionZ -= cosf(radians) * m_BackSpeed;

	return;
}

void Camera::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_LeftSpeed += m_FrameTime * 0.01f;

		if(m_LeftSpeed > (m_FrameTime * 0.15f))
		{
			m_LeftSpeed = m_FrameTime * 0.15f;
		}
	}
	else
	{
		m_LeftSpeed = 0.0f;
	}

	// Update the rotation.
	m_RotationY -= m_LeftSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_RotationY < 0.0f)
	{
		m_RotationY += 360.0f;
	}

	return;
}

void Camera::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_RightSpeed += m_FrameTime * 0.01f;

		if(m_RightSpeed > (m_FrameTime * 0.15f))
		{
			m_RightSpeed = m_FrameTime * 0.15f;
		}
	}
	else
	{
		m_RightSpeed = 0.0f;
	}

	// Update the rotation.
	m_RotationY += m_RightSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_RotationY > 360.0f)
	{
		m_RotationY -= 360.0f;
	}

	return;
}

void Camera::LookUp(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_LookUpSpeed += m_FrameTime * 0.01f;

		if(m_LookUpSpeed > (m_FrameTime * 0.15f))
		{
			m_LookUpSpeed = m_FrameTime * 0.15f;
		}
	}
	else
	{
		m_LookUpSpeed = 0.0f;
	}

	// Update the rotation.
	m_RotationX -= m_LookUpSpeed;

	if(m_RotationX > 89.0f)
	{
		m_RotationX = 89.0f;
	}

	return;
}

void Camera::LookDown(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_LookDownSpeed += m_FrameTime * 0.01f;

		if(m_LookDownSpeed > (m_FrameTime * 0.15f))
		{
			m_LookDownSpeed = m_FrameTime * 0.15f;
		}
	}
	else
	{
		m_LookDownSpeed = 0.0f;
	}

	// Update the rotation.
	m_RotationX += m_LookDownSpeed;

	if(m_RotationX < -45.0f)
	{
		m_RotationX = -45.0f;
	}

	return;
}