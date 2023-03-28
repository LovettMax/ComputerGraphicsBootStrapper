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
#include "Scene.h"
#include "Instance.h"
#include "RenderTarget.h"
#include "String"
#include "ParticleEmitter.h"


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

	// Shape Checks
	bool gridChecked = true;
	bool textureChecked = false;
	bool cubeChecked = false;
	bool headChecked = false;

	void SetStationaryCameraMatrix(StationaryCamera* cam);

	bool QuadLoader();
	void QuadDraw(glm::mat4 pvm);

	bool CubeLoader();
	void CubeDraw(glm::mat4 pvm);
	
	void DrawGizmos(glm::mat4 projectionView, glm::mat4 transform,
		Mesh& gizmoMesh, glm::vec3 position);

	void SimpleDraw(glm::mat4 pvm, Mesh& mesh);
	
	bool Cylinder();
	void CylinderDraw(glm::mat4 pvm);

	bool BunnyLoader();
	void BunnyDraw(glm::mat4 pvm);

	bool SpearLoader();

	bool ToadLoader();

	bool HeadLoader();

	void ObjDraw(glm::mat4 pv, glm::mat4 transform, aie::OBJMesh* objMesh);
	bool ObjLoader(aie::OBJMesh& objMesh, glm::mat4& transform,
		float scale, const char* filepath, bool flipTexture);

	void QuadTextureDraw(glm::mat4 pvm);
	bool QuadTextureLoader();

	void PhongDraw(glm::mat4 pvm, glm::mat4 transform);

	int m_postProcessingEffect = 0;

	std::string defaultString = "blur";

	

	Scene* m_scene;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	aie::ShaderProgram  m_simpleShader;
	aie::ShaderProgram  m_colorShader;
	aie::ShaderProgram  m_phongShader;
	aie::ShaderProgram  m_texturedShader;
	aie::ShaderProgram  m_normalLitShader;
	aie::ShaderProgram  m_postProcessShader;
	aie::ShaderProgram  m_particleShader;

	aie::RenderTarget m_renderTarget;

	Mesh                m_fullScreenQuad;

	Mesh                m_quadMesh;
	glm::mat4           m_quadTransform;

	Mesh                m_cubeMesh;
	glm::mat4           m_cubeTransform;

	Mesh                m_gizmosMesh;
	glm::mat4           m_gizmosTransform;

	Mesh                m_cylinderMesh;
	glm::mat4           m_cylinderTransform;

	aie::OBJMesh        m_bunnyMesh;
	glm::mat4           m_bunnyTransform;

	aie::OBJMesh        m_spearMesh;
	glm::mat4           m_spearTransform;

	aie::OBJMesh        m_jadeToadMesh;
	glm::mat4           m_jadeToadTransform;

	aie::OBJMesh        m_headMesh;
	glm::mat4           m_headTransform;

	// Cameras
	SimpleCamera        m_camera;
	bool                m_simpleCameraOn = false;

	BaseCamera*         m_baseCamera;
	BaseCamera*         m_tempCamera;

	StationaryCamera    m_stationaryCamera1;

	StationaryCamera    m_stationaryCamera2;

	StationaryCamera    m_stationaryCamera3;

	FlyCamera           m_flyCamera;

	bool m_isCameraStatic = false;

	float m_cameraX;
	float m_cameraY;
	float m_cameraZ;

	Light m_light;

	Light* m_blueLight;
	Light* m_redLight;
	glm::vec3 m_ambientLight;

	ParticleEmitter*     m_emmiter;
	glm::mat4           m_particleEmitTransform;
};