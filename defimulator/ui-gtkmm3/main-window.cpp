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
    m_menubar.m_quitbutton.signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_quit));

    m_menubar.m_loadcart.signal_activate().connect(
        sigc::bind<Cartridge::Type>(
            sigc::mem_fun(m_filebrowser, &FileBrowser::open),
            Cartridge::Type::STANDARD));
    m_menubar.m_loadbsxslotted.signal_activate().connect(
        sigc::bind<Cartridge::Type>(
            sigc::mem_fun(m_filebrowser, &FileBrowser::open),
            Cartridge::Type::BSX_SLOTTED));
    m_menubar.m_loadbsx.signal_activate().connect(
        sigc::bind<Cartridge::Type>(
            sigc::mem_fun(m_filebrowser, &FileBrowser::open),
            Cartridge::Type::BSX));
    m_menubar.m_loadsufamiturbo.signal_activate().connect(
        sigc::bind<Cartridge::Type>(
            sigc::mem_fun(m_filebrowser, &FileBrowser::open),
            Cartridge::Type::SUFAMI_TURBO));
    m_menubar.m_loadsupergameboy.signal_activate().connect(
        sigc::bind<Cartridge::Type>(
            sigc::mem_fun(m_filebrowser, &FileBrowser::open),
            Cartridge::Type::SUPER_GAME_BOY));

    m_filebrowser.m_accept.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_cartridge_load));

    this->add(m_vbox);
    this->set_title("Defimulator");
}

void MainWindow::on_cartridge_load(void)
{
    m_filebrowser.hide();
    /* Load the cartridge based upon the strings in the file browser */
}

void MainWindow::on_quit(void)
{
    this->hide();
}
