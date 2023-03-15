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
	void ImGUIRefresher();

	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool CubeLoader();
	void CubeDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::ShaderProgram  m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;

	Mesh                m_quadMesh;
	glm::mat4           m_quadTransform;

	Mesh                m_cubeMesh;
	glm::mat4           m_cubeTransform;

	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	struct Light {
		glm::vec3 direction;
		glm::vec3 color;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

};