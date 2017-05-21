#ifndef DEFIMULATOR_UI_MAINWINDOW_H
#define DEFIMULATOR_UI_MAINWINDOW_H

#include <memory>

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>

#include <nall/config.hpp>

#include <ui-gtkmm3/base.h>
#include <ui-gtkmm3/file-browser.h>
#include <ui-gtkmm3/menubar.h>
#include <ui-gtkmm3/settings.h>
#include <ui-gtkmm3/viewport.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(std::shared_ptr<state_t> state);
    virtual ~MainWindow(void) { };
protected:
    MenuBar m_menubar;
    Viewport m_viewport;
    Gtk::Statusbar m_statusbar;
    Gtk::Box m_vbox;
private:
    AdvancedSettings m_advancedsettings;
    AudioSettings m_audiosettings;
    FileBrowser m_filebrowser;
    VideoSettings m_videosettings;

    std::shared_ptr<state_t> m_state;

    void on_cartridge_load(void);
    void on_quit(void);

    /* Overridden slots */
    bool on_delete_event(GdkEventAny *any_event) { on_quit(); };
};

#endif
