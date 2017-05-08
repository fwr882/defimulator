#include "file-browser.h"

FileBrowser::FileBrowser(void)
{
    m_slotonelabel.set_text("Base Cartridge:");
    m_slottwolabel.set_text("Slot A:");
    m_slotthreelabel.set_text("Slot B:");

    m_accept.set_label("Okay");
    m_cancel.set_label("Cancel");

    m_layoutgrid.set_border_width(10);
    m_layoutgrid.set_column_spacing(5);
    m_layoutgrid.set_row_spacing(5);
    m_layoutgrid.set_row_homogeneous(true);
    m_layoutgrid.set_column_homogeneous(true);

    m_slotonelabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_slotonelabel, 1, 1, 1, 1);
    m_layoutgrid.attach(m_slotonebrowser, 2, 1, 2, 1);

    m_slottwolabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_slottwolabel, 1, 2, 1, 1);
    m_layoutgrid.attach(m_slottwobrowser, 2, 2, 2, 1);

    m_slotthreelabel.set_halign(Gtk::Align::ALIGN_START);
    m_layoutgrid.attach(m_slotthreelabel, 1, 3, 1, 1);
    m_layoutgrid.attach(m_slotthreebrowser, 2, 3, 2, 1);

    m_layoutgrid.attach(m_accept, 2, 4, 1, 1);
    m_layoutgrid.attach(m_cancel, 3, 4, 1, 1);

    m_cancel.signal_clicked().connect(sigc::mem_fun(*this,
        &FileBrowser::cancel_pressed));

    this->add(m_layoutgrid);
    this->set_title("Load Cartridge");
}

void FileBrowser::open(Cartridge::Type type)
{
    m_type = type;

    m_slotone = nall::string("");
    m_slottwo = nall::string("");
    m_slotthree = nall::string("");

    m_slotonebrowser.set_sensitive(false);
    m_slottwobrowser.set_sensitive(false);
    m_slotthreebrowser.set_sensitive(false);

    switch (m_type) {
    case Cartridge::SUFAMI_TURBO:
        this->m_slotthreebrowser.set_sensitive(true);
        /* fallthrough */
    case Cartridge::BSX:
    case Cartridge::BSX_SLOTTED:
    case Cartridge::SUPER_GAME_BOY:
        this->m_slottwobrowser.set_sensitive(true);
        /* fallthrough */
    case Cartridge::STANDARD:
        this->m_slotonebrowser.set_sensitive(true);
        break;
    default:
        g_print("FileBrowser::open: Something went horribly wrong.\n");
    }

    this->show_all();
}

nall::string FileBrowser::get(int index)
{
    switch (index) {
    case 1:
        return m_slotone;
    case 2:
        return m_slottwo;
    case 3:
        return m_slotthree;
    default:
        return nall::string("");
    }
}

Cartridge::Type FileBrowser::type(void)
{
    return m_type;
}

void FileBrowser::cancel_pressed(void)
{
    g_print("FileBrowser::cancel_pressed\n");

    m_slotone = "";
    m_slottwo = "";
    m_slotthree = "";

    this->hide();
}

