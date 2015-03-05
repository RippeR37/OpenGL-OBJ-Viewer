#ifndef CONTROLLER_STATE_SHUTDOWN_H_INCLUDED
#define CONTROLLER_STATE_SHUTDOWN_H_INCLUDED

#include <Utils/Interfaces/State.h>
#include <Utils/Frameworks/Application.h>

namespace Controller {

    namespace State {

        class Shutdown : public Util::Interface::State {
            public:
                Shutdown(FW::Application& application);
                ~Shutdown();

                void update(const double frameTime);
                void render();

                void onLoad();
                void onUnload();
                void signalExit();

            private:
                void closeWindow();
                void terminateLibraries();

            private:
                FW::Application _Application;
        };

    }

}

#endif