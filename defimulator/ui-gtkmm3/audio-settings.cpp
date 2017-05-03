#include "settings.h"

AudioSettings::AudioSettings(void)
{
    m_volumelabel.set_text("Volume:");
    m_volumevalue.set_text("100%");
    m_volumeslider.set_draw_value(false);
    m_volumeslider.set_increments(1, 5);
    m_volumeslider.set_range(0, 200);
    m_volumeslider.set_value(100);
    m_volumeslider.set_digits(0);

    m_frequencylabel.set_text("Frequency:");
    m_frequencyvalue.set_text("32000 Hz");
    m_frequencyslider.set_draw_value(false);
    m_frequencyslider.set_increments(1, 100);
    m_frequencyslider.set_range(31000, 33000);
    m_frequencyslider.set_value(32000);
    m_frequencyslider.set_digits(0);

    m_grid.set_row_homogeneous(true);
    m_grid.set_column_homogeneous(true);
    m_grid.attach(m_volumelabel, 1, 1, 1, 1);
    m_grid.attach(m_volumevalue, 2, 1, 1, 1);
    m_grid.attach(m_volumeslider, 3, 1, 3, 1);
    m_grid.attach(m_frequencylabel, 1, 2, 1, 1);
    m_grid.attach(m_frequencyvalue, 2, 2, 1, 1);
    m_grid.attach(m_frequencyslider, 3, 2, 3, 1);

    m_frequencyslider.signal_value_changed().connect(
        sigc::mem_fun(*this, &AudioSettings::synchronize));
    m_volumeslider.signal_value_changed().connect(
        sigc::mem_fun(*this, &AudioSettings::synchronize));

    this->add(m_grid);
    this->set_title("Audio Settings");
}

AudioSettings::~AudioSettings(void)
{

}

void AudioSettings::synchronize(void)
{
    std::stringstream vstr, fstr;

    vstr << static_cast<unsigned int>(m_volumeslider.get_value());
    vstr << "%";

    fstr << static_cast<unsigned int>(m_frequencyslider.get_value());
    fstr << "Hz";

    m_volumevalue.set_text(vstr.str().c_str());
    m_frequencyvalue.set_text(fstr.str().c_str());
}
