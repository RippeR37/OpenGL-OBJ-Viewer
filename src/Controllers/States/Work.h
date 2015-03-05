#ifndef CONTROLLER_STATE_WORK_H_INCLUDED
#define CONTROLLER_STATE_WORK_H_INCLUDED

#include "../FlyCamera.h"
#include "../../Models/Grid.h"

#include <Utils/Interfaces/State.h>
#include <Utils/GL+/Pipeline.h>
#include <Utils/GL+/Models/OBJ.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Controller {

    namespace State {

        class Work : public Util::Interface::State {
            public:
                enum class Visibility {
                    Hidden,
                    Visible
                };

                enum class VisibilityDetailed {
                    Hidden,
                    Visible,
                    Detailed
                };

                enum class ShaderType {
                    Phong,
                    Toon,
                    Silhouette
                };

            public:
                Work(FW::Application& application);
                ~Work();
                
                void update(const double frameTime);
                void render();

                void onLoad();
                void onUnload();
                void signalExit();

                void setCallbacks(bool setFlag);
                void setContext();

                const FlyCamera& getCamera() const;

                static void handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
                static void handleMouseWheel(GLFWwindow* window, double x, double y);
                static void handleMouseMovement(GLFWwindow* window, double x, double y);
                
            public:
                Visibility stateGrid;
                VisibilityDetailed stateAABB;

                GL::Pipeline pipeline;

            private:
                void setModels();
                void chooseModel(int modelID = -1);
                void change(Visibility& visibility);
                void change(VisibilityDetailed& visibility);

            private:
                FlyCamera _camera;

            private:
                Model::Grid _grid;
                GL::Model::OBJ _modelOBJ;

            private:
                FW::Application& _Application;
        };

    }

}

#endif