#include "file-browser.h"

FileBrowser::FileBrowser(void)
{
    m_slotonelabel.set_text("Base Cartridge:");
    m_slottwolabel.set_text("Slot A:");
    m_slotthreelabel.set_text("Slot B:");

    m_accept.set_label("Okay");
    m_cancel.set_label("Cancel");

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

    this->add(m_layoutgrid);
    this->set_title("Load Cartridge");
}

void FileBrowser::show(Mode m)
{
    /* Let's get everything in the 'on' state first. */
    this->m_slotonebrowser.set_sensitive(true);
    this->m_slottwobrowser.set_sensitive(true);
    this->m_slotthreebrowser.set_sensitive(true);

    /* Then selectively turn them off based upon how we open the dialog */
    switch (m) {
    case FileBrowser::SingleSlot:
        this->m_slottwobrowser.set_sensitive(false);
        this->m_slotthreebrowser.set_sensitive(false);
        this->m_slottwo = "";
        this->m_slotthree = "";
        break;
    case FileBrowser::DoubleSlot:
        this->m_slotthreebrowser.set_sensitive(false);
        this->m_slotthree = "";
        break;
    default:
        /* TripleSlot already has everything enabled by default */
        break;
    }

    this->show_all();
}

nall::string FileBrowser::get(int index)
{
    switch (index) {
    case 0:
        return m_slotone;
    case 1:
        return m_slottwo;
    case 2:
        return m_slotthree;
    default:
        return "";
    }
}
