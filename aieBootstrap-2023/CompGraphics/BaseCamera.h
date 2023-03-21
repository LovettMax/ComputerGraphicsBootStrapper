#pragma once
#include <glm/glm.hpp>


class BaseCamera
{
public:
	BaseCamera();
	~BaseCamera();

	void Update(float deltaTime);

	// Getters
	glm::vec3 GetPosition()
	{
		return m_position;
	}
	glm::mat4 GetWorldTransform(glm::vec3 position,
		glm::vec3 eularAngles, glm::vec3 scale);
	glm::mat4 GetProjectionViewMatrix()
	{
		return m_projectionViewTransform;
	};

	glm::mat4 GetProjectionMatrix(float width,
		float height);
	glm::mat4 GetViewMatrix();
	
	float GetAspectRatio()
	{
		return m_aspectRatio;
	};

	// Setters
	void SetPosition(glm::vec3);
	void SetAspectRatio(float width, float height);
	void SetViewMatrix(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetProjectionMatrix(float fieldOfView, float aspectRatio, 
		float near, float far);
		void SetProjectionMatrix(float fieldOfView, float width,
		float height, float near, float far);

	bool m_isActive = false;

protected:
	
	glm::mat4   m_projectionViewTransform;
	glm::mat4   m_worldTransform;
	glm::mat4   m_viewTransform;
			    
	glm::vec3   m_position;
			    
	float       m_aspectRatio;
	float       m_theta;
	float       m_phi;
			    
	glm::vec2   m_lastMouse;

};

