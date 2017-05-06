#include "settings.h"

VideoSettings::VideoSettings(void)
{
    m_coloradjustmentlabel.set_text("Color Adjustment");

    m_brightnesslabel.set_label("Brightness:");
    m_brightnessvalue.set_text("100%");
    m_brightnessslider.set_draw_value(false);
    m_brightnessslider.set_increments(1, 5);
    m_brightnessslider.set_range(0, 200);
    m_brightnessslider.set_value(100);
    m_brightnessslider.set_digits(0);

    m_contrastlabel.set_label("Contrast:");
    m_contrastvalue.set_text("100%");
    m_contrastslider.set_draw_value(false);
    m_contrastslider.set_increments(1, 5);
    m_contrastslider.set_range(0, 200);
    m_contrastslider.set_value(100);
    m_contrastslider.set_digits(0);

    m_gammalabel.set_label("Gamma:");
    m_gammavalue.set_text("100%");
    m_gammaslider.set_draw_value(false);
    m_gammaslider.set_increments(1, 5);
    m_gammaslider.set_range(0, 200);
    m_gammaslider.set_value(100);
    m_gammaslider.set_digits(0);

    m_enablegamma.set_label("NTSC Gamma Ramp Simulation");
    m_enablegamma.set_active(true);

    m_vfilterlabel.set_text("Video Filter");
    m_vfilterclear.set_label("Clear");

    m_pshaderlabel.set_text("Pixel Shader");
    m_pshaderclear.set_label("Clear");

    m_layoutgrid.set_row_homogeneous(true);
    m_layoutgrid.set_column_homogeneous(true);

    /*
    * Lots of widgets to pack.  In order to make labels align to the
    * left, you have to set the alignment of the widget itself, not the
    * grid that you're putting it in.
    */
    m_coloradjustmentlabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_coloradjustmentlabel, 1, 1, 5, 1);

    m_brightnesslabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_brightnesslabel, 1, 2, 1, 1);
    m_layoutgrid.attach(m_brightnessvalue, 2, 2, 1, 1);
    m_layoutgrid.attach(m_brightnessslider, 3, 2, 3, 1);

    m_contrastlabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_contrastlabel, 1, 3, 1, 1);
    m_layoutgrid.attach(m_contrastvalue, 2, 3, 1, 1);
    m_layoutgrid.attach(m_contrastslider, 3, 3, 3, 1);

    m_gammalabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_gammalabel, 1, 4, 1, 1);
    m_layoutgrid.attach(m_gammavalue, 2, 4, 1, 1);
    m_layoutgrid.attach(m_gammaslider, 3, 4, 3, 1);

    m_layoutgrid.attach(m_enablegamma, 1, 5, 5, 1);

    m_layoutgrid.attach(m_vfilterlabel, 1, 6, 1, 1);
    m_layoutgrid.attach(m_vfilterbrowser, 2, 6, 3, 1);
    m_layoutgrid.attach(m_vfilterclear, 5, 6, 1, 1);

    m_layoutgrid.attach(m_pshaderlabel, 1, 7, 1, 1);
    m_layoutgrid.attach(m_pshaderbrowser, 2, 7, 3, 1);
    m_layoutgrid.attach(m_pshaderclear, 5, 7, 1, 1);

    this->add(m_layoutgrid);
    this->set_title("Video Settings");
}

void VideoSettings::synchronize(void)
{

}
