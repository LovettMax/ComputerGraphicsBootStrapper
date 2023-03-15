#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"


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
	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram  m_simpleShader;
	aie::ShaderProgram  m_colorShader;

	Mesh                m_quadMesh;
	glm::mat4           m_quadTransform;
	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;


};