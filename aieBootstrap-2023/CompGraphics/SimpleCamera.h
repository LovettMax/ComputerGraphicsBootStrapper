#pragma once
#include <glm/glm.hpp>

class SimpleCamera
{
public:
	SimpleCamera();
	~SimpleCamera();

	void Update(float deltaTime);
	glm::vec3 GetPosition() 
	    { return m_position; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float width, 
		float height);
	glm::mat4 GetTransform(glm::vec3 position, 
		glm::vec3 eularAngles, glm::vec3 scale);

private:
	float m_theta;
	float m_phi;

	float m_turnSpeed = glm::radians(180.f);

	float m_camSprintSpeed = 5.0f;

	glm::vec3 m_position;

	// Last position  of the mouse
	glm::vec2 m_lastMouse;
};

