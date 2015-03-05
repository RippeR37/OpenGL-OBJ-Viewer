#ifndef CONTROLLER_STATE_INITIALIZATION_H_INCLUDED
#define CONTROLLER_STATE_INITIALIZATION_H_INCLUDED

#include <Utils/Interfaces/State.h>

namespace Controller {

    namespace State {

        class Initialization : public Util::Interface::State {
            public:
                Initialization(FW::Application& application);
                ~Initialization();

                void update(const double frameTime);
                void render();

                void onLoad();
                void onUnload();
                void signalExit();

            private:
                void setRandomSeed();
                void openWindow();
                void initializeWork();

            private:
                FW::Application& _Application;
        };

    }

}

#endif