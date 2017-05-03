#include "application.h"

Application::Application(void)
{

}

Application::~Application(void) { }

void Application::main(int argc, char** argv)
{
    /* XXX: Where is 'PLATFORM_WIN' defined? */
    #if defined(PLATFORM_WIN)
    nall::utf8_args(argc, argv)
    #endif

    m_config.create();
}
