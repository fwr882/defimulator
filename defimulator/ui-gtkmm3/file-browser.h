#ifndef DEFIMULATOR_UI_FILEBROWSER_H
#define DEFIMULATOR_UI_FILEBROWSER_H

#include <gtkmm/button.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include <nall/string.hpp>

class FileBrowser : public Gtk::Window {
public:
    enum Mode {
        SingleSlot,
        DoubleSlot,
        TripleSlot
    };

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
    void show(Mode m);
    void show_one(void) { show(FileBrowser::SingleSlot); };
    void show_two(void) { show(FileBrowser::DoubleSlot); };
    void show_three(void) { show(FileBrowser::TripleSlot); };
    nall::string get(int index);
private:
    nall::string m_slotone, m_slottwo, m_slotthree;
};

#endif
