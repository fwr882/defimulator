#ifndef DEFIMULATOR_UI_MAINWINDOW_H
#define DEFIMULATOR_UI_MAINWINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>

#include "menubar.h"
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

};

#endif
