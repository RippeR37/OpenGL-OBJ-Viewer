#include "Initialization.h"
#include "Manager.h"

#include <Utils/Frameworks/Application.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ctime>
#include <cstdlib>

namespace Controller {
    
    namespace State {

        Initialization::Initialization(FW::Application& application) : _Application(application) {
            
        }

        Initialization::~Initialization() {

        }

        void Initialization::update(double frameTime) {
            // do nothing
        }

        void Initialization::render() {
            // do nothing
        }

        void Initialization::onLoad() {
            setRandomSeed();
            openWindow();
            initializeWork();

            changeTo(&Manager::getWork());
        }

        void Initialization::onUnload() {

        }

        void Initialization::signalExit() {
            changeTo(&Manager::getShutdown());
        }

        void Initialization::setRandomSeed() {
            srand(static_cast<unsigned int>(time(nullptr)));
        }

        void Initialization::openWindow() {
            _Application.Window.setSize(800u, 600u);
            _Application.Window.setTitle("OBJ Model Viewer");
            _Application.Window.setDestroyCallback([&]() {
                _Application.signalExit();
            });

            if(_Application.Window.create() == false)
                throw Util::Exception::FatalError("Failed to create window");

            GL::Context::Current = _Application.Window.getContext();
            GL::Context::Current.setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        }

        void Initialization::initializeWork() {
            Manager::initializeWork(_Application);
        }
    
    }

}
