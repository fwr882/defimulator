void Button::create(Window &parent, unsigned x, unsigned y, unsigned width,
    unsigned height, const string &text)
{
    widget->window = CreateWindow(
        L"BUTTON", utf16_t(text),
        WS_CHILD | WS_TABSTOP | WS_VISIBLE,
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
}
