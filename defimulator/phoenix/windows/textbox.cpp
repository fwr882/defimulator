void TextBox::create(Window &parent, unsigned x, unsigned y, unsigned width,
    unsigned height, const string &text)
{
    widget->window = CreateWindowEx(
        WS_EX_CLIENTEDGE, L"EDIT", utf16_t(text),
        WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
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

string TextBox::text(void)
{
    unsigned length = GetWindowTextLength(widget->window);
    wchar_t text[length + 1];

    GetWindowText(widget->window, text, length + 1);
    text[length] = 0;

    return utf8_t(text);
}

void TextBox::setText(const string &text)
{
    object->locked = true;
    SetWindowText(widget->window, utf16_t(text));
    object->locked = false;
}

void TextBox::setEditable(bool editable)
{
    SendMessage(widget->window, EM_SETREADONLY, editable == false, 0);
}
