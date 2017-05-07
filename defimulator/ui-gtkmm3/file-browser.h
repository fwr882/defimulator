#ifndef DEFIMULATOR_UI_FILEBROWSER_H
#define DEFIMULATOR_UI_FILEBROWSER_H

#include <gtkmm/button.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include <nall/string.hpp>

#include "cartridge.h"

class FileBrowser : public Gtk::Window {
public:
    Gtk::Label m_slotonelabel;
    Gtk::FileChooserButton m_slotonebrowser;

    Gtk::Label m_slottwolabel;
    Gtk::FileChooserButton m_slottwobrowser;

    Gtk::Label m_slotthreelabel;
    Gtk::FileChooserButton m_slotthreebrowser;

    Gtk::Grid m_layoutgrid;
    Gtk::Button m_accept;
    Gtk::Button m_cancel;

    FileBrowser(void);
    virtual ~FileBrowser(void) { };

    void open(Cartridge::Type ctype);
    nall::string get(int index);
    Cartridge::Type type(void);
private:
    Cartridge::Type m_type;
    nall::string m_slotone, m_slottwo, m_slotthree;
    void cancel_pressed(void);
    void okay_pressed(void);
    void window_closed(void);
};

#endif
