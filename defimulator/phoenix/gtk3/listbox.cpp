static void ListBox_activate(ListBox *self)
{

}

static void ListBox_change(ListBox *self)
{

}

static void ListBox_tick(GtkCellRendererToggle *cell, gchar *path_string,
    ListBox *self)
{

}

void ListBox::create(Window &parent, unsigned x, unsigned y, unsigned width,
    unsigned height, const string &text)
{

}

void ListBox::setFocused(void)
{

}

void ListBox::setHeaderVisible(bool visible)
{

}

void ListBox::setCheckable(bool checkable)
{

}

void ListBox::setFont(Font &font)
{

}

void ListBox::reset(void)
{

}

void ListBox::resizeColumnsToContent(void)
{

}

void ListBox::addItem(const string &text)
{

}

void ListBox::setItem(unsigned row, const string &text)
{

}

bool ListBox::checked(unsigned row)
{
    return false;
}

void ListBox::setChecked(unsigned row, bool checked)
{

}

/* XXX: Not sure what sort of container 'optional' is.. */
optional<unsigned> ListBox::selection(void)
{
    return { false, 0 };
}

void ListBox::setSelection(unsigned row)
{

}

ListBox::ListBox(void)
{

}
