#include "Shutdown.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Controller {

    namespace State {

        Shutdown::Shutdown(FW::Application& application) : _Application(application) {

        }

        Shutdown::~Shutdown() {

        }

        void Shutdown::update(double frameTime) {
            // do nothing
        }

        void Shutdown::render() {
            // do nothing
        }

        void Shutdown::onLoad() {
            changeTo(nullptr);
        }

        void Shutdown::onUnload() {
            closeWindow();
            terminateLibraries();
        }

        void Shutdown::signalExit() {
            changeTo(nullptr);
        }

        void Shutdown::closeWindow() {
            GL::Context::Current = GL::Context::DefaultContext;
            _Application.Window.destroy();
        }

        void Shutdown::terminateLibraries() {
            glfwTerminate();
        }

    }
}
