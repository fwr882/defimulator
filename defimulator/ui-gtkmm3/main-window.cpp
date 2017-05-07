#include "main-window.h"

MainWindow::MainWindow(void)
{
    /* Just put something there!! */
    m_statusbar.push("No cartridge loaded.");

    m_vbox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    m_vbox.pack_start(m_menubar);
    m_vbox.pack_start(m_viewport);
    m_vbox.pack_start(m_statusbar);

    m_menubar.m_advancedsettings.signal_activate().connect(
        sigc::mem_fun(m_advancedsettings, &AdvancedSettings::show_all));
    m_menubar.m_audiosettings.signal_activate().connect(
        sigc::mem_fun(m_audiosettings, &AudioSettings::show_all));
    m_menubar.m_videosettings.signal_activate().connect(
        sigc::mem_fun(m_videosettings, &VideoSettings::show_all));
    m_menubar.m_loadcart.signal_activate().connect(
        sigc::mem_fun(m_filebrowser, &FileBrowser::show_one));
    m_menubar.m_loadbsxslotted.signal_activate().connect(
        sigc::mem_fun(m_filebrowser, &FileBrowser::show_two));
    m_menubar.m_loadbsx.signal_activate().connect(
        sigc::mem_fun(m_filebrowser, &FileBrowser::show_two));
    m_menubar.m_loadsufamiturbo.signal_activate().connect(
        sigc::mem_fun(m_filebrowser, &FileBrowser::show_three));
    m_menubar.m_loadsupergameboy.signal_activate().connect(
        sigc::mem_fun(m_filebrowser, &FileBrowser::show_two));

    this->add(m_vbox);
    this->set_title("Defimulator");
}

MainWindow::~MainWindow(void) { }
