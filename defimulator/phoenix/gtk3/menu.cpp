static void Action_setFont(GtkWidget *widget, gpointer font)
{

}

bool Action::visible(void)
{
    return false;
}

void Action::setVisible(bool visible)
{

}

bool Action::enabled(void)
{
    return false;
}

void Action::setEnabled(bool enabled)
{

}

Action::Action(void)
{

}

void Menu::create(Window &parent, const string &text)
{

}

void Menu::create(Menu &parent, const string &text)
{

}

void MenuSeparator::create(Menu &parent)
{

}

static void MenuItem_tick(MenuItem *self)
{

}

void MenuItem::create(Menu &parent, const string &text)
{

}

static void MenuCheckItem_tick(MenuCheckItem *self)
{

}

void MenuCheckItem::create(Menu &parent, const string &text)
{

}

bool MenuCheckItem::checked(void)
{
    return false;
}

void MenuCheckItem::setChecked(bool state)
{

}

static void MenuRadioItem_tick(MenuRadioItem *self)
{

}

void MenuRadioItem::create(Menu &parent, const string &text)
{

}

void MenuRadioItem::create(MenuRadioItem &parent, const string &text)
{

}

bool MenuRadioItem::checked(void)
{
    return false;
}

void MenuRadioItem::setChecked(void)
{

}
