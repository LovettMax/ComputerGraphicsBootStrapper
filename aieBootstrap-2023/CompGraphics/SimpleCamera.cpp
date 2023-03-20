#include "SimpleCamera.h"
#include <glm/ext.hpp>
#include "Input.h"

SimpleCamera::SimpleCamera()
{
    m_position = glm::vec3(-10, 2, 0);
    m_phi = 0;
    m_theta = 0;
}

SimpleCamera::~SimpleCamera()
{
}

void SimpleCamera::Update(float deltaTime)
{
    aie::Input* input = aie::Input::getInstance();
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);

    glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
        glm::cos(phiR) * glm::sin(thetaR));
    glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
    glm::vec3 up(0, 1, 0);

    // We will use WASD to move and the Q & E to go up and down 
    if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
    {
        if (input->isKeyDown(aie::INPUT_KEY_W))
            m_position += forward * deltaTime * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_S))
            m_position -= forward * deltaTime * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_A))
            m_position -= right * deltaTime * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_D))
            m_position += right * deltaTime * m_camSprintSpeed;

        if (input->isKeyDown(aie::INPUT_KEY_Q))
            m_position -= up * deltaTime * m_camSprintSpeed;
        if (input->isKeyDown(aie::INPUT_KEY_E))
            m_position += up * deltaTime * m_camSprintSpeed;
    }
    else
    {
        if (input->isKeyDown(aie::INPUT_KEY_W))
            m_position += forward * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_S))
            m_position -= forward * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_A))
            m_position -= right * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_D))
            m_position += right * deltaTime;

        if (input->isKeyDown(aie::INPUT_KEY_Q))
            m_position -= up * deltaTime;
        if (input->isKeyDown(aie::INPUT_KEY_E))
            m_position += up * deltaTime;
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

glm::mat4 SimpleCamera::GetViewMatrix()
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    glm::vec3 forwad(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR),
        glm::cos(phiR) * glm::sin(thetaR));

    return glm::lookAt(m_position, m_position + forwad, 
        glm::vec3(0, 1, 0));
}

glm::mat4 SimpleCamera::GetProjectionMatrix(float width, float height)
{
    return glm::perspective(glm::pi<float>() * .25f, width / height, 
        .1f, 1000.f);
}

glm::mat4 SimpleCamera::GetTransform(glm::vec3 position, glm::vec3 eularAngles, glm::vec3 scale)
{
    return glm::mat4();
}
