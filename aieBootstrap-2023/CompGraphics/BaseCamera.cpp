#include "BaseCamera.h"
#include <glm/ext.hpp>
#include "Input.h"

BaseCamera::BaseCamera()
{
    m_position = glm::vec3(0, 0, 0);
    m_phi = 0;
    m_theta = 0;
}

BaseCamera::~BaseCamera()
{
}

void BaseCamera::Update(float deltaTime)
{
}

glm::mat4 BaseCamera::GetWorldTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
	 
    return glm::translate(glm::mat4(1), position)
        * glm::rotate(glm::mat4(1),
            glm::radians(eularAngles.z), glm::vec3(0, 0, 1))
        * glm::rotate(glm::mat4(1),
            glm::radians(eularAngles.y), glm::vec3(0, 1, 0))
        * glm::rotate(glm::mat4(1),
            glm::radians(eularAngles.x), glm::vec3(1, 0, 0))
        * glm::scale(glm::mat4(1), scale);
}

glm::mat4 BaseCamera::GetProjectionMatrix(float width, float height)
{
    return glm::perspective(glm::pi<float>() * .25f, width / height,
        .1f, 1000.f);
}

glm::mat4 BaseCamera::GetViewMatrix()
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    glm::vec3 forwad(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
        glm::cos(phiR) * glm::sin(thetaR));

    return glm::lookAt(m_position, m_position + forwad,
        glm::vec3(0, 1, 0));
}


void BaseCamera::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}

void BaseCamera::SetAspectRatio(float width, float height)
{

}

void BaseCamera::SetViewMatrix(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
}

void BaseCamera::SetProjectionMatrix(float fieldOfView, float aspectRatio, float, float)
{
}

void BaseCamera::SetProjectionMatrix(float fieldOfView, float width, float height, float, float)
{
}
