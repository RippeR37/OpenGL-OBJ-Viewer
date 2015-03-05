#ifndef CONTROLLER_FLYCAMERA_H_INCLUDED
#define CONTROLLER_FLYCAMERA_H_INCLUDED

#include <Utils/Interfaces/Camera.h>

#include <glm/glm.hpp>

namespace Controller {

    class FlyCamera : public Util::Interface::Camera {
        public:
            FlyCamera();
            ~FlyCamera();

            void update(double deltaTime);
            void updateMouse(double x, double y);
            void updateMouseButton(int button, int action, int mods);
            void updateKeyboard(int key, int scancode, int action, int mods);
            void updateMouseWheel(double x, double y);

            void resetAngles();

            void setPos3D(const glm::vec3& position);

            float getAngleX() const;
            float getAngleY() const;
            const glm::vec2  getPos2D() const;
            const glm::vec3& getPos3D() const;
            const glm::mat4& getMatrix() const;

        private:
            float _speed;
            float _angleX;
            float _angleY;
            float _mouseSpeed;
    };

}

#endif