#pragma once
#include "BaseCamera.h"

class StationaryCamera : public BaseCamera
{
public:
	StationaryCamera();
	~StationaryCamera();

	void SetRotation(glm::vec3 rot);

	bool m_isActive = false;

private:


};

