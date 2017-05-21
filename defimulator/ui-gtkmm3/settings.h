#ifndef DEFIMULATOR_UI_SETTINGS_H
#define DEFIMULATOR_UI_SETTINGS_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/hvscale.h>
#include <gtkmm/label.h>
#include <gtkmm/listbox.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/window.h>

class AdvancedSettings : public Gtk::Window {
public:
    Gtk::Label m_driverselectionlabel;
    Gtk::Label m_videodriverlabel;
    Gtk::ComboBoxText m_videodriverbox;
    Gtk::Label m_audiodriverlabel;
    Gtk::ComboBoxText m_audiodriverbox;
    Gtk::Label m_inputdriverlabel;
    Gtk::ComboBoxText m_inputdriverbox;
    Gtk::Label m_focuspolicylabel;
    Gtk::RadioButton m_focuspolicypause;
    Gtk::RadioButton m_focuspolicyignore;
    Gtk::RadioButton m_focuspolicyallow;

    Gtk::Grid m_gridlayout;

    AdvancedSettings(void);
    virtual ~AdvancedSettings(void);
    void create(void);
};

class AudioSettings : public Gtk::Window {
public:
    Gtk::Label m_volumelabel;
    Gtk::Label m_volumevalue;
    Gtk::HScale m_volumeslider;
    Gtk::Box m_volbox;

    Gtk::Label m_frequencylabel;
    Gtk::Label m_frequencyvalue;
    Gtk::HScale m_frequencyslider;
    Gtk::Box m_freqbox;

    Gtk::Grid m_grid;
    Gtk::Box m_vbox;

    AudioSettings(void);
    virtual ~AudioSettings(void);
    void synchronize(void);
};

class InputSettings : public Gtk::Window {
public:
    Gtk::Label m_portlabel;
    Gtk::ComboBox m_portbox;
    Gtk::Label m_devicelabel;
    Gtk::ComboBox m_devicebox;
    Gtk::ListBox m_mappinglist;
    Gtk::Button m_mousexaxis;
    Gtk::Button m_mouseyaxis;
    Gtk::Button m_mouseleft;
    Gtk::Button m_mousemiddle;
    Gtk::Button m_mouseright;
    Gtk::Button m_clearbutton;
};

class VideoSettings : public Gtk::Window {
public:
    Gtk::Label m_coloradjustmentlabel;

    Gtk::Label m_brightnesslabel;
    Gtk::Label m_brightnessvalue;
    Gtk::HScale m_brightnessslider;

    Gtk::Label m_contrastlabel;
    Gtk::Label m_contrastvalue;
    Gtk::HScale m_contrastslider;

    Gtk::Label m_gammalabel;
    Gtk::Label m_gammavalue;
    Gtk::HScale m_gammaslider;

    Gtk::CheckButton m_enablegamma;

    Gtk::Label m_vfilterlabel;
    Gtk::FileChooserButton m_vfilterbrowser;
    Gtk::Button m_vfilterclear;

    Gtk::Label m_pshaderlabel;
    Gtk::FileChooserButton m_pshaderbrowser;
    Gtk::Button m_pshaderclear;

    Gtk::Grid m_layoutgrid;

    VideoSettings(void);
    virtual ~VideoSettings(void) { };
    void synchronize(void);
    void pshader_clear_clicked(void);
    void vfilter_clear_clicked(void);
};

#endif
