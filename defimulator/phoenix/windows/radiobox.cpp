void RadioBox::create(Window &parent, unsigned x, unsigned y, unsigned width,
    unsigned height, const string &text)
{
    radioBox->parentWindow = &parent;
    radioBox->parent = this;
    radioBox->parent->radioBox->items.append(this);

    widget->window = CreateWindow(
        L"BUTTON", utf16_t(text),
        WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_RADIOBUTTON,
        x, y, width, height,
        parent.widget->window, (HMENU)object->id, GetModuleHandle(0), 0
    );

    SetWindowLongPtr(widget->window, GWLP_USERDATA, (LONG_PTR)this);
    if (parent.window->defaultFont) {
        SendMessage(widget->window, WM_SETFONT,
            (WPARAM)(parent.window->defaultFont), 0);
    } else {
        SendMessage(widget->window, WM_SETFONT,
            (WPARAM)(OS::os->proportionalFont), 0);
    }

    setChecked();
}

void RadioBox::create(RadioBox &parent, unsigned x, unsigned y, unsigned width,
    unsigned height, const string &text)
{
    radioBox->parentWindow = parent.radioBox->parentWindow;
    radioBox->parent = parent.radioBox->parent;
    radioBox->parent->radioBox->items.append(this);

    widget->window = CreateWindow(
        L"BUTTON", utf16_t(text),
        WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_RADIOBUTTON,
        x, y, width, height,
        GetParent(radioBox->parent->widget->window),
        (HMENU)object->id, GetModuleHandle(0), 0
    );

    SetWindowLongPtr(widget->window, GWLP_USERDATA, (LONG_PTR)this);

    if(radioBox->parentWindow->window->defaultFont) {
        SendMessage(widget->window, WM_SETFONT,
            (WPARAM)(radioBox->parentWindow->window->defaultFont), 0);
    } else {
        SendMessage(widget->window, WM_SETFONT,
            (WPARAM)(OS::os->proportionalFont), 0);
    }
}

bool RadioBox::checked(void)
{
    return SendMessage(widget->window, BM_GETCHECK, 0, 0);
}

void RadioBox::setChecked(void)
{
    nall_foreach (item, radioBox->parent->radioBox->items) {
        SendMessage(item->widget->window, BM_SETCHECK,
            (WPARAM)(item == this), 0);
    }
}

RadioBox::RadioBox(void)
{
    radioBox = new RadioBox::Data;
}
