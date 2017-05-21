#include "settings.h"

AdvancedSettings::AdvancedSettings(void)
{
    m_driverselectionlabel.set_label("Driver Selection");

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

    m_focuspolicylabel.set_text("Focus Policy");

    /* Must re-create buttons here to be able to group them together */
    Gtk::RadioButtonGroup group;
    m_focuspolicypause = Gtk::RadioButton(group);
    m_focuspolicyignore = Gtk::RadioButton(group);
    m_focuspolicyallow = Gtk::RadioButton(group);

    m_focuspolicypause.set_label("Pause Emulator When Inactive");
    m_focuspolicyignore.set_label("Ignore Input When Inactive");
    m_focuspolicyallow.set_label("Always Allow Input");

    m_gridlayout.set_border_width(10);
    m_gridlayout.set_row_spacing(5);
    m_gridlayout.set_column_spacing(5);
    m_gridlayout.set_row_homogeneous(true);
    m_gridlayout.set_column_homogeneous(true);

    m_gridlayout.attach(m_driverselectionlabel, 1, 1, 6, 1);
    m_gridlayout.attach(m_videodriverlabel, 1, 2, 1, 1);
    m_gridlayout.attach(m_videodriverbox, 2, 2, 1, 1);
    m_gridlayout.attach(m_audiodriverlabel, 3, 2, 1, 1);
    m_gridlayout.attach(m_audiodriverbox, 4, 2, 1, 1);
    m_gridlayout.attach(m_inputdriverlabel, 5, 2, 1, 1);
    m_gridlayout.attach(m_inputdriverbox, 6, 2, 1, 1);
    m_gridlayout.attach(m_focuspolicylabel, 1, 3, 6, 1);
    m_gridlayout.attach(m_focuspolicypause, 1, 4, 2, 1);
    m_gridlayout.attach(m_focuspolicyignore, 3, 4, 2, 1);
    m_gridlayout.attach(m_focuspolicyallow, 5, 4, 2, 1);

    this->add(m_gridlayout);
    this->set_title("Advanced Settings");
}

AdvancedSettings::~AdvancedSettings(void) { }
