#include "CompGraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

CompGraphicsApp::CompGraphicsApp() {

}

CompGraphicsApp::~CompGraphicsApp() {

}

bool CompGraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);


	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	return LaunchShaders();
}

void CompGraphicsApp::shutdown() {

	Gizmos::destroy();
}

void CompGraphicsApp::update(float deltaTime) {


	// wipe the gizmos clean for this frame
	Gizmos::clear();



	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// PLANETARY EXERCISE ----
	//Planetary();
	// -----------------------


	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CompGraphicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 
		getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	// Draw the quad setup in QuadLoader()
	auto pv = m_projectionMatrix * m_viewMatrix;
	QuadDraw(pv * m_quadTransform);

	// Draw the bunny setup in BunnyLoader()
	BunnyDraw(pv * m_bunnyTransform);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

bool CompGraphicsApp::LaunchShaders()
{
	// used for loading in a simple quad
	if (!QuadLoader())
		return false;
	// used for loading bunny quad
	if (!BunnyLoader())
		return false;

#pragma region BunnyRegion
	

#pragma endregion

	return true;
}

bool CompGraphicsApp::QuadLoader()
{
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	if (m_simpleShader.link() == false)
	{
		printf("Simple Shader has an Error: %s\n",
			m_simpleShader.getLastError());
		return false;
	}

	// Defined as 4 vertices for the 2 triangles
	Mesh::Vertex vertices[4];
	vertices[0].position = { -.5f, 0,  .5f, 1 };
	vertices[1].position = { .5f, 0,  .5f, 1 };
	vertices[2].position = { -.5f, 0, -.5f, 1 };
	vertices[3].position = { .5f, 0, -.5f, 1 };

	unsigned int indices[6] = { 0 ,1 ,2 ,2 ,1 ,3 };



	m_quadMesh.Intialise(4, vertices, 6, indices);

	// This is a 10 'unit' wide quad
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, .5
	};
	return true;
}

void CompGraphicsApp::QuadDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_simpleShader.bind();

	// Bind the transform

	m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	// Draw the quad using Mesh's draw
	m_quadMesh.Draw();
}

bool CompGraphicsApp::BunnyLoader()
{
	m_colorShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/color.vert");
	m_colorShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/color.frag");
	if (m_colorShader.link() == false)
	{
		printf("Color shader Error: %s\n", m_colorShader.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("./stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}

	m_bunnyTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return true;
}

void CompGraphicsApp::BunnyDraw(glm::mat4 pvm)
{
	// Bind the shader
	m_colorShader.bind();

	// Bind the transform
	m_colorShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the color 
	m_colorShader.bindUniform("BaseColor", glm::vec4(1));

	m_bunnyMesh.draw();
}

void CompGraphicsApp::Planetary()
{
	float time = getTime();

	glm::mat4 t = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::normalize(glm::vec3(0, 1, 0)));
	t[3] = glm::vec4(0, 0, 0, 0);



	vec3 sunPos = vec3(3, 5, 5);

	mat4 mercury = mat4(1);
	mercury = glm::translate(mercury, vec3(glm::sin(time * .6f) * 1.2, 0, glm::cos(time * .6f) * 1.2));

	mat4 venus = mat4(1);
	venus = glm::translate(venus, vec3(glm::sin(time * .6f) * 1.8, 0, glm::cos(time * .6f) * 1.8));

	mat4 earth = mat4(1);
	earth = glm::translate(earth, vec3(glm::sin(time * .6f) * 2.5, 0, glm::cos(time * .6f) * 2.5));

	mat4 mars = mat4(1);
	mars = glm::translate(mars, vec3(glm::sin(time * .6f) * 3.2, 0, glm::cos(time * .6f) * 3.2));

	mat4 jupiter = mat4(1);
	jupiter = glm::translate(jupiter, vec3(glm::sin(time * .6f) * 4, 0, glm::cos(time * .6f) * 4));

	mat4 saturn = mat4(1);
	saturn = glm::translate(saturn, vec3(glm::sin(time * .6f) * 5.2, 0, glm::cos(time * .6f) * 5.2));

	mat4 neptune = mat4(1);
	neptune = glm::translate(neptune, vec3(glm::sin(time * .6f) * 6.1, 0, glm::cos(time * .6f) * 6.1));

	mat4 uranus = mat4(1);
	uranus = glm::translate(uranus, vec3(glm::sin(time * .6f) * 6.8, 0, glm::cos(time * .6f) * 6.8));

	vec3 saturnPos = saturn[3];

	Gizmos::addSphere(sunPos, .8, 20, 20, vec4(1.00, 0.38, 0.00, 1.0)); // Sun
	Gizmos::addSphere(sunPos, .09, 10, 10, vec4(1.00, 0.60, 0.25, 1.0), &mercury); // Mercury
	Gizmos::addSphere(sunPos, .17, 10, 10, vec4(0.97, 0.62, 0.33, 1.0), &venus); // Venus
	Gizmos::addSphere(sunPos, .2, 10, 10, vec4(0.25, 0.64, 0.99, 1.0), &earth); // Earth
	Gizmos::addSphere(sunPos, .15, 10, 10, vec4(0.99, 0.69, 0.42, 1.0), &mars); // Mars
	Gizmos::addSphere(sunPos, .4, 10, 10, vec4(0.99, 0.52, 0.35, 1.0), &jupiter); // Jupiter
	Gizmos::addSphere(sunPos, .35, 10, 10, vec4(0.97, 0.91, 0.55, 1.0), &saturn); // Saturn
	Gizmos::addRing(sunPos, .43f, .53f, 20, vec4(0.64, 0.56, 0.41, 1.0), &saturn); // Saturn Inner Ring
	Gizmos::addRing(sunPos, .55f, .6f, 20, vec4(0.64, 0.56, 0.41, 1.0), &saturn); // Saturn Outer Ring
	Gizmos::addSphere(sunPos, .2, 10, 10, vec4(0.39, 0.80, 1.00, 1.0), &neptune); // Neptune
	Gizmos::addRing(sunPos, .28f, .31f, 20, vec4(0.87, 0.96, 1.00, 1.0), &neptune); // Neptune Outer Ring
	Gizmos::addSphere(sunPos, .2, 10, 10, vec4(0.00, 0.51, 1.00, 1.0), &uranus); // Uranus
}
