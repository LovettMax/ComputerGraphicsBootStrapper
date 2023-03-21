#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "SimpleCamera.h"
#include "BaseCamera.h"
#include "StationaryCamera.h"
#include "FlyCamera.h"


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
	void ImGUIShapeSelection();

	bool cubeChecked = false;

	void SetStationaryCameraMatrix(StationaryCamera* cam);

	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool CubeLoader();
	void CubeDraw(glm::mat4 pvm);
	
	bool Cylinder();
	void CylinderDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	bool SpearLoader();
	void ObjDraw(glm::mat4 pv, glm::mat4 transform, aie::OBJMesh* objMesh);

	void QuadTextureDraw(glm::mat4 pvm);
	bool QuadTextureLoader();

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	aie::ShaderProgram  m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;
	aie::ShaderProgram  m_texturedShader;
	aie::ShaderProgram  m_normalLitShader;

	Mesh                m_quadMesh;
	glm::mat4           m_quadTransform;

	Mesh                m_cubeMesh;
	glm::mat4           m_cubeTransform;

	Mesh                m_cylinderMesh;
	glm::mat4           m_cylinderTransform;

	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	aie::OBJMesh        m_spearMesh;
	glm::mat4           m_spearTransform;

	// Cameras
	SimpleCamera        m_camera;
	bool                m_simpleCameraOn = false;

	BaseCamera*         m_baseCamera;

	StationaryCamera    m_stationaryCamera1;

	StationaryCamera    m_stationaryCamera2;

	StationaryCamera    m_stationaryCamera3;

	FlyCamera           m_flyCamera;

	bool m_isCameraStatic = false;

	float m_cameraX;
	float m_cameraY;
	float m_cameraZ;

	struct Light {
		glm::vec3 direction;
		glm::vec3 color;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

};