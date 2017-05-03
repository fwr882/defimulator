#ifndef DEFIMULATOR_UI_SETTINGS_H
#define DEFIMULATOR_UI_SETTINGS_H

#include <gtkmm/box.h>
//#include <gtkmm/comboboxtext.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/window.h>

class AdvancedSettings : public Gtk::Window {
public:
    Gtk::Label m_driverselectionlabel;
    Gtk::Label m_videodriverlabel;
    //Gtk::ComboBoxText m_videodriverbox;
    Gtk::Label m_audiodriverlabel;
    //Gtk::ComboBoxText m_audiodriverbox;
    Gtk::Label m_inputdriverlabel;
    //Gtk::ComboBoxText m_inputdriverbox;
    Gtk::Label m_focuspolicylabel;
    Gtk::RadioButton m_focuspolicypause;
    Gtk::RadioButton m_focuspolicyignore;
    Gtk::RadioButton m_focuspolicyallow;

    Gtk::Box m_vbox;
    Gtk::Box m_driverbox;
    Gtk::Box m_policybox;

    AdvancedSettings(void);
    virtual ~AdvancedSettings(void);
    void create(void);
};

#endif
