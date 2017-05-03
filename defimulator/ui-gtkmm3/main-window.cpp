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

    this->add(m_vbox);
    this->set_title("Defimulator");
    this->show_all();
}

MainWindow::~MainWindow(void) { }
