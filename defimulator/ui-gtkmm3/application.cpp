#include "application.h"

Application::Application(void) { }

Application::~Application(void)
{
    delete(m_mainwindow);
}

void Application::main(int argc, char** argv)
{
    /* XXX: Where is 'PLATFORM_WIN' defined? */
    #if defined(PLATFORM_WIN)
    nall::utf8_args(argc, argv);
    #endif

    m_app = Gtk::Application::create(argc, argv, "org.grim210.defimulator")
        .release();
    m_mainwindow = new MainWindow();

    /* Initialize all the subsystems before we open the window. */
    m_config.create();

    /* show the window and run it! */
    m_mainwindow->show_all();
    m_app->run(*m_mainwindow);
}
