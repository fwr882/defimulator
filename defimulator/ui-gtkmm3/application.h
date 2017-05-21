#ifndef DEFIMULATOR_UI_APPLICATION_H
#define DEFIMULATOR_UI_APPLICATION_H

#include <memory>

#include <gtkmm/application.h>

#include "base.h"
#include "cartridge.h"
#include "configuration.h"
#include "input.h"
#include "main-window.h"

class Application {
public:
    Application(void);
    virtual ~Application(void);
    void main(int argc, char** argv);
private:
    Gtk::Application* m_app;
    MainWindow* m_mainwindow;

    Cartridge m_cartridge;
    Configuration m_config;
    InputMapper m_inputmapper;

    std::shared_ptr<state_t> m_state;
};

#endif
