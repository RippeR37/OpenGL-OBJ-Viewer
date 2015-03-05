#include "Manager.h"

namespace Controller {

    namespace State {

        Manager::Manager() {
            initialization = nullptr;
            shutdown = nullptr;
            work = nullptr;
        }

        Manager::~Manager() {
            delete initialization;
            delete shutdown;
            delete work;
        }

        Manager& Manager::get() {
            static Manager instance;
            return instance;
        }

        void Manager::initialize(FW::Application& application) {
            if(Manager::get().initialization == nullptr)
                Manager::get().initialization = new Initialization(application);

            if(Manager::get().shutdown = nullptr)
                Manager::get().shutdown = new Shutdown(application);
        }

        void Manager::initializeWork(FW::Application& application) {
            if(Manager::get().work == nullptr)
                Manager::get().work = new Work(application);
        }

        Initialization& Manager::getInitialization() {
            return *Manager::get().initialization;
        }

        Shutdown& Manager::getShutdown() {
            return *Manager::get().shutdown;
        }

        Work& Manager::getWork() {
            return *Manager::get().work;
        }

    }

}