#ifndef DEFIMULATOR_UI_MAINWINDOW_H
#define DEFIMULATOR_UI_MAINWINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>

#include <nall/config.hpp>

#include "menubar.h"
#include "settings.h"
#include "viewport.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow(void);
    virtual ~MainWindow(void);
protected:

    MenuBar m_menubar;
    Viewport m_viewport;
    Gtk::Statusbar m_statusbar;

    Gtk::Box m_vbox;
private:
    AdvancedSettings m_advancedsettings;
    AudioSettings m_audiosettings;
    VideoSettings m_videosettings;
};

#endif
