#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"


class CompGraphicsApp : public aie::Application {
public:

	CompGraphicsApp();
	virtual ~CompGraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);

	virtual void draw();

	void Planetary();

protected:

	bool LaunchShaders();

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram  m_simpleShader;
	Mesh                m_quadMesh;
	glm::mat4           m_quadTransform;

};