#include <gtkmm/application.h>
#include "main-window.h"

int main(int argc, char* argv[])
{
    Gtk::Application* app = Gtk::Application::create(argc, argv,
        "org.grim210.defimulator").release();

    MainWindow win;
    app->run(win);

    return 0;
}
