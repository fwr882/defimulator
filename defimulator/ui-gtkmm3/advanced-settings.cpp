#include "settings.h"

AdvancedSettings::AdvancedSettings(void)
{
    m_driverselectionlabel.set_label("Driver Selection:.");

    /* XXX:
    * So this is obviously dummy code.  The video subsystem (ruby, I think)
    * needs to be queried for what sort of drivers that the system will
    * support.  So OpenGL, DirectDraw, SDL, etc..
    */
    m_videodriverlabel.set_label("Video:");
    m_videodriverbox.append("Some");
    m_videodriverbox.append("Video");
    m_videodriverbox.append("Drivers");

    m_audiodriverlabel.set_label("Audio:");
    m_audiodriverbox.append("Some");
    m_audiodriverbox.append("Audio");
    m_audiodriverbox.append("Drivers");

    m_inputdriverlabel.set_label("Input:");
    m_inputdriverbox.append("Some");
    m_inputdriverbox.append("Input");
    m_inputdriverbox.append("Drivers");

    m_driverbox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    m_driverbox.pack_start(m_videodriverlabel);
    m_driverbox.pack_start(m_videodriverbox);
    m_driverbox.pack_start(m_audiodriverlabel);
    m_driverbox.pack_start(m_audiodriverbox);
    m_driverbox.pack_start(m_inputdriverlabel);
    m_driverbox.pack_start(m_inputdriverbox);

    m_focuspolicylabel.set_text("Focus Policy:.");

    /* Must re-create buttons here to be able to group them together */
    Gtk::RadioButtonGroup group;
    m_focuspolicypause = Gtk::RadioButton(group);
    m_focuspolicyignore = Gtk::RadioButton(group);
    m_focuspolicyallow = Gtk::RadioButton(group);

    m_focuspolicypause.set_label("Pause Emulator When Inactive");
    m_focuspolicyignore.set_label("Ignore Input When Inactive");
    m_focuspolicyallow.set_label("Always Allow Input");

    m_vbox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    m_vbox.pack_start(m_driverselectionlabel);
    m_vbox.pack_start(m_videodriverlabel);
    m_vbox.pack_start(m_audiodriverlabel);
    m_vbox.pack_start(m_inputdriverlabel);

    m_policybox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    m_policybox.pack_start(m_focuspolicypause);
    m_policybox.pack_start(m_focuspolicyignore);
    m_policybox.pack_start(m_focuspolicyallow);

    m_vbox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    m_vbox.pack_start(m_driverselectionlabel);
    m_vbox.pack_start(m_driverbox);
    m_vbox.pack_start(m_focuspolicylabel);
    m_vbox.pack_start(m_policybox);

    this->add(m_vbox);
    this->set_title("Advanced Settings");
}

AdvancedSettings::~AdvancedSettings(void) { }
