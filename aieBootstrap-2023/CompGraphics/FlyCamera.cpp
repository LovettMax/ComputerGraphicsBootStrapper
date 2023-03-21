#include "FlyCamera.h"
#include <glm/ext.hpp>
#include "Input.h"

FlyCamera::FlyCamera()
{
    m_speed = 1;
    up = glm::vec3(0, 1, 0);
}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float deltaTime)
{
    aie::Input* input = aie::Input::getInstance();
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);

    glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
        glm::cos(phiR) * glm::sin(thetaR));
    glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));

    // We will use WASD to move and the Q & E to go up and down 
    if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
    {
        if (input->isKeyDown(aie::INPUT_KEY_W))
            m_position += forward * deltaTime * m_speed * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_S))
            m_position -= forward * deltaTime * m_speed * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_A))
            m_position -= right * deltaTime * m_speed * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_D))
            m_position += right * deltaTime * m_speed * m_camSprintSpeed;

        if (input->isKeyDown(aie::INPUT_KEY_Q))
            m_position -= up * deltaTime * m_speed * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_E))
            m_position += up * deltaTime * m_speed * m_camSprintSpeed;
    }
    else
    {
        if (input->isKeyDown(aie::INPUT_KEY_W))
            m_position += forward * m_speed * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_S))
            m_position -= forward * m_speed * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_A))
            m_position -= right * m_speed * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_D))
            m_position += right * m_speed * deltaTime;

        if (input->isKeyDown(aie::INPUT_KEY_Q))
            m_position -= up * m_speed * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_E))
            m_position += up * m_speed * deltaTime;
    }


    // Get the mouse coordinates
    float mx = input->getMouseX();
    float my = input->getMouseY();

    // If the right button is held down, increment theta and phi (rotate)
    if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
    {
        m_theta += m_turnSpeed * (mx - m_lastMouse.x) * deltaTime;
        m_phi += m_turnSpeed * (my - m_lastMouse.y) * deltaTime;
    }

    m_lastMouse = glm::vec2(mx, my);

}

void FlyCamera::SetSpeed(float speed)
{
	m_speed = speed;
}
