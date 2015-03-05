#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "FlyCamera.h"
#include "../Controllers/States/Manager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace Controller {

    FlyCamera::FlyCamera() : Camera() {
        _position = glm::vec3(0.0f, 70.0f, 0.0f);

        _mouseSpeed = 0.003f;
        _angleX = glm::radians(180.0f);
    }

    FlyCamera::~FlyCamera() {

    }

    void FlyCamera::update(double deltaTime) {
        GLFWwindow* window = nullptr;

        if(GL::Context::Current.getWindow() != nullptr)
            window = GL::Context::Current.getWindow()->getHandle();

        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            _speed = 15.0f;
        else
            _speed = 1.0f;

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            _position += _direction * static_cast<float>(deltaTime * _speed);
        
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            _position -= _direction * static_cast<float>(deltaTime * _speed);
        
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            _position += _right * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            _position -= _right * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            _position += _up * static_cast<float>(deltaTime * _speed);

        if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            _position -= _up * static_cast<float>(deltaTime * _speed);



        _direction = glm::vec3(std::cos(_angleY) * std::sin(_angleX), std::sin(_angleY), std::cos(_angleY) * cos(_angleX));
        _right     = glm::vec3(std::sin(_angleX - 3.14f/2.0f), 0, std::cos(_angleX - 3.14f/2.0f));
        _up        = glm::cross(_right, _direction);


        _matrix = glm::lookAt(_position, _position + _direction, _up);
    }

    void FlyCamera::updateMouse(double x, double y) {
        _angleX -= static_cast<float>(x) * _mouseSpeed;
        _angleY -= static_cast<float>(y) * _mouseSpeed;
    }

    void FlyCamera::updateMouseButton(int button, int action, int mods) {
        return;
    }
    
    void FlyCamera::updateKeyboard(int key, int scancode, int action, int mods) {
        return;
    }

    void FlyCamera::updateMouseWheel(double x, double y) {
        return;
    }
    
    void FlyCamera::resetAngles() {
        _angleX = 0;
        _angleY = 0;
    }

    void FlyCamera::setPos3D(const glm::vec3& position) {
        _position = position;
    }

    float FlyCamera::getAngleX() const {
        return _angleX;
    }

    float FlyCamera::getAngleY() const {
        return _angleY;
    }

    const glm::vec2 FlyCamera::getPos2D() const {
        return glm::vec2(_position[0], _position[2]);
    }

    const glm::vec3& FlyCamera::getPos3D() const {
        return _position;
    }

    const glm::mat4& FlyCamera::getMatrix() const {
        return _matrix;
    }

}