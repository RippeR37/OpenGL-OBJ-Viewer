#ifndef CONTROLLER_STATE_MANAGER_H_INCLUDED
#define CONTROLLER_STATE_MANAGER_H_INCLUDED

#include "Initialization.h"
#include "Shutdown.h"
#include "Work.h"

#include <Utils/Frameworks/Application.h>

namespace Controller {

    namespace State {

        class Manager {
            public:
                static void initialize(FW::Application& application);
                static void initializeWork(FW::Application& application);

                static Initialization& getInitialization();
                static Shutdown& getShutdown();

                static Work& getWork();

            private:
                Manager();
                ~Manager();
                
                static Manager& get();

                Initialization* initialization;
                Shutdown* shutdown;
                Work* work;
        };
    }

}

#endif