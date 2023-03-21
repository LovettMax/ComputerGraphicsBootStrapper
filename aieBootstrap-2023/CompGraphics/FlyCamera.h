#pragma once
#include "BaseCamera.h"
class FlyCamera : public BaseCamera
{

public:
	FlyCamera();
	~FlyCamera();

	void Update(float deltaTime);

	void SetSpeed(float speed);

private:

	float m_turnSpeed = glm::radians(180.f);

	float m_camSprintSpeed = 5.0f;

	float m_speed;
	glm::vec3 up;

};

