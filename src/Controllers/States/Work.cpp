#include "Manager.h"
#include "Work.h"

#include <Utils/TimeLoop.h>

#include <GLFW/glfw3.h>

#include <iostream>

namespace Controller {

    namespace State {

        Work::Work(FW::Application& application) : _Application(application) {
            stateGrid = Visibility::Visible;
            stateAABB = VisibilityDetailed::Hidden;
        }

        Work::~Work() {

        }

        void Work::update(double frameTime) {
            static const double timeStep = 1.0 / 120.0;

            if(shouldSkip())
                return;
        
            Util::TimeLoop::semiFixed(frameTime, timeStep, [&, this](double deltaTime) {
                _camera.update(deltaTime);
            });
        }

        void Work::render() {
            if(shouldSkip())
                return;

            GL::Context::Current.clearBuffers(GL::Context::BufferMask::Color_Depth);

            pipeline.setView(_camera.getMatrix());
                   
            if(stateGrid == Visibility::Visible)
                _grid.render(pipeline);

            _modelOBJ.render(pipeline);

            if(stateAABB != VisibilityDetailed::Hidden)
                _modelOBJ.renderAABB(pipeline, stateAABB == VisibilityDetailed::Detailed);
        }

        void Work::onLoad() {
            changeTo(this);
            setCallbacks(true);
            setContext();
            setModels();
        }

        void Work::onUnload() {
            setCallbacks(false);
        }

        void Work::signalExit() {
            changeTo(&Manager::getShutdown());
        }
        
        void Work::setCallbacks(bool setFlag) {
            if(setFlag) {
                glfwSetKeyCallback(_Application.Window.getHandle(), Work::handleKeyboard);
                glfwSetScrollCallback(_Application.Window.getHandle(), Work::handleMouseWheel);
                glfwSetCursorPosCallback(_Application.Window.getHandle(), Work::handleMouseMovement);
                glfwSetInputMode(_Application.Window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            } else {
                glfwSetKeyCallback(_Application.Window.getHandle(), nullptr);
                glfwSetScrollCallback(_Application.Window.getHandle(), nullptr);
                glfwSetCursorPosCallback(_Application.Window.getHandle(), nullptr);
                glfwSetInputMode(_Application.Window.getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            glfwSetCursorPos(_Application.Window.getHandle(), 400.0, 300.0);
        }

        void Work::setContext() {
            GL::Context::Current.setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
            pipeline.setProjection(60.0f, 4.0f/3.0f, 0.01f, 10000.0f);
            
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
        }

        void Work::setModels() {
            _grid.setMin(glm::ivec2(-100));
            _grid.setMax(glm::ivec2( 100));
            _grid.build();

            chooseModel(7);
        }

        const FlyCamera& Work::getCamera() const {
            return _camera;
        }

        void Work::chooseModel(int modelID) {
            _modelOBJ.clear();

            switch(modelID) {
                case 1: _modelOBJ.load("assets/models/clownfish/clownfish.obj"); break;
                case 2: _modelOBJ.load("assets/models/goldenfish/goldenfish.obj"); break;
                case 3: _modelOBJ.load("assets/models/park/park.obj"); break;
                case 4: _modelOBJ.load("assets/models/cow/cow.obj"); break;
                case 5: _modelOBJ.load("assets/models/bench/bench.obj"); break;
                case 6: _modelOBJ.load("assets/models/chair/chair.obj"); break;
                case 7: _modelOBJ.load("assets/models/teapot/teapot.obj"); break;

                default: _modelOBJ.load("assets/models/suzanne/suzanne.obj"); break;
            }

            // Setting up camera position
            _camera.setPos3D(
                glm::vec3(
                    (_modelOBJ.getAABB().getMin().x + _modelOBJ.getAABB().getMax().x) * 0.5f,
                    (_modelOBJ.getAABB().getMin().y + _modelOBJ.getAABB().getMax().y) * 0.75f,
                     _modelOBJ.getAABB().getMax().z * 3.5f
                )
            );
        }

        void Work::change(Visibility& visibility) {
            switch(visibility) {
                case Visibility::Hidden:
                    visibility = Visibility::Visible; break;

                default:
                    visibility = Visibility::Hidden; break;
            }
        }

        void Work::change(VisibilityDetailed& visibility) {
            switch(visibility) {
                case VisibilityDetailed::Hidden:
                    visibility = VisibilityDetailed::Visible; break;

                case VisibilityDetailed::Visible:
                    visibility = VisibilityDetailed::Detailed; break;

                default: 
                    visibility = VisibilityDetailed::Hidden; break;
            }
        }

        void Work::handleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
            static Work& thisState = Manager::getWork();

            if(action == GLFW_PRESS) {
                switch(key) {
                    case GLFW_KEY_ESCAPE:
                        thisState.changeTo(&Manager::getShutdown());
                        break;

                    case GLFW_KEY_0: thisState.chooseModel(0); break;
                    case GLFW_KEY_1: thisState.chooseModel(1); break;
                    case GLFW_KEY_2: thisState.chooseModel(2); break;
                    case GLFW_KEY_3: thisState.chooseModel(3); break;
                    case GLFW_KEY_4: thisState.chooseModel(4); break;
                    case GLFW_KEY_5: thisState.chooseModel(5); break;
                    case GLFW_KEY_6: thisState.chooseModel(6); break;
                    case GLFW_KEY_7: thisState.chooseModel(7); break;
                    case GLFW_KEY_8: thisState.chooseModel(8); break;
                    case GLFW_KEY_9: thisState.chooseModel(9); break;

                    case GLFW_KEY_G: thisState.change(thisState.stateGrid); break;
                    case GLFW_KEY_O: thisState.change(thisState.stateAABB); break;

                    default:
                        break;
                }
            }
        }
    
        void Work::handleMouseWheel(GLFWwindow* window, double x, double y) {
            static Work& thisState = Manager::getWork();
        }

        void Work::handleMouseMovement(GLFWwindow* window, double x, double y) {
            static Work& thisState = Manager::getWork();
            static double centerX = thisState._Application.Window.getWidth()  / 2.0;
            static double centerY = thisState._Application.Window.getHeight() / 2.0;
            static double dx;
            static double dy;

            dx = x - centerX;
            dy = y - centerY;

            thisState._camera.updateMouse(static_cast<int>(dx), static_cast<int>(dy));
            glfwSetCursorPos(window, centerX, centerY);
        }

    }

}