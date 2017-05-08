Action::Action(void)
{
    OS::os->objects.append(this);
    action = new Action::Data;
}

void Menu::create(Window &parent, const string &text)
{
    action->parentMenu = parent.window->menu;
    action->menu = CreatePopupMenu();
    AppendMenu(parent.window->menu, MF_STRING | MF_POPUP,
        (UINT_PTR)action->menu, utf16_t(text));
}

void Menu::create(Menu &parent, const string &text)
{
    action->parentMenu = parent.action->menu;
    action->menu = CreatePopupMenu();
    AppendMenu(parent.action->menu, MF_STRING | MF_POPUP,
        (UINT_PTR)action->menu, utf16_t(text));
}

bool Menu::enabled(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));
    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parentMenu, (UINT_PTR)action->menu, false, &info);
    return (info.fState & MFS_GRAYED) == 0;
}

void Menu::setEnabled(bool enabled)
{
    if (enabled) {
        EnableMenuItem(action->parentMenu, (UINT_PTR)action->menu,
            MF_BYCOMMAND | MF_ENABLED);
    } else {
        EnableMenuItem(action->parentMenu, (UINT_PTR)action->menu,
            MF_BYCOMMAND | MF_GRAYED);
    }
}

void MenuSeparator::create(Menu &parent)
{
    action->parent = &parent;
    AppendMenu(parent.action->menu, MF_SEPARATOR, object->id, L"");
}

bool MenuSeparator::enabled(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return (info.fState & MFS_GRAYED) == 0;
}

void MenuSeparator::setEnabled(bool enabled)
{
    if (enabled) {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_ENABLED);
    } else {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_GRAYED);
    }
}

void MenuItem::create(Menu &parent, const string &text)
{
    action->parent = &parent;
    AppendMenu(parent.action->menu, MF_STRING, object->id, utf16_t(text));
}

bool MenuItem::enabled(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return (info.fState & MFS_GRAYED) == 0;
}

void MenuItem::setEnabled(bool enabled)
{
    if (enabled) {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_ENABLED);
    } else {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_GRAYED);
    }
}

void MenuCheckItem::create(Menu &parent, const string &text)
{
    action->parent = &parent;
    AppendMenu(parent.action->menu, MF_STRING, object->id, utf16_t(text));
}

bool MenuCheckItem::enabled(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return (info.fState & MFS_GRAYED) == 0;
}

void MenuCheckItem::setEnabled(bool enabled)
{
    if (enabled) {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_ENABLED);
    } else {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_GRAYED);
    }
}

bool MenuCheckItem::checked(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return info.fState & MFS_CHECKED;
}

void MenuCheckItem::setChecked(bool checked)
{
    if (checked) {
        CheckMenuItem(action->parent->action->menu, object->id, MF_CHECKED);
    } else {
        CheckMenuItem(action->parent->action->menu, object->id, MF_UNCHECKED);

    }
}

void MenuRadioItem::create(Menu &parent, const string &text)
{
    action->parent = &parent;
    action->radioParent = this;
    action->items.append(this);
    AppendMenu(parent.action->menu, MF_STRING, object->id, utf16_t(text));
    setChecked();
}

void MenuRadioItem::create(MenuRadioItem &parent, const string &text)
{
    action->parent = parent.action->parent;
    action->radioParent = parent.action->radioParent;
    action->radioParent->action->items.append(this);
    AppendMenu(action->parent->action->menu, MF_STRING,
        object->id, utf16_t(text));
}

bool MenuRadioItem::enabled(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return (info.fState & MFS_GRAYED) == 0;
}

void MenuRadioItem::setEnabled(bool enabled)
{
    if (enabled) {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_ENABLED);
    } else {
        EnableMenuItem(action->parent->action->menu, object->id,
            MF_BYCOMMAND | MF_GRAYED);
    }
}

bool MenuRadioItem::checked(void)
{
    MENUITEMINFO info;
    memset(&info, 0, sizeof(MENUITEMINFO));

    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STATE;
    GetMenuItemInfo(action->parent->action->menu, object->id, false, &info);
    return info.fState & MFS_CHECKED;
}

void MenuRadioItem::setChecked(void)
{
    MenuRadioItem *parent = action->radioParent;
    nall_foreach (item, parent->action->items) {
        CheckMenuRadioItem(
            action->parent->action->menu,
            item->object->id, item->object->id,
            item->object->id + (item != this), MF_BYCOMMAND
        );
    }
}
