static MessageWindow::Response MessageWindow_response(
    MessageWindow::Buttons buttons, UINT response)
{
    switch (response) {
    case IDOK:
        return MessageWindow::Response::Ok;
    case IDCANCEL:
        return MessageWindow::Response::Cancel;
    case IDYES:
        return MessageWindow::Response::Yes;
    case IDNO:
        return MessageWindow::Response::No;
    }

    switch (buttons) {
    case MessageWindow::Buttons::OkCancel:
        return MessageWindow::Response::Cancel;
    case MessageWindow::Buttons::YesNo:
        return MessageWindow::Response::No;
    }

    return MessageWindow::Response::Ok;
}

MessageWindow::Response MessageWindow::information(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    UINT flags = MB_ICONINFORMATION;

    if (buttons == Buttons::Ok) {
        flags |= MB_OK;
    }

    if (buttons == Buttons::OkCancel) {
        flags |= MB_OKCANCEL;
    }

    if (buttons == Buttons::YesNo) {
        flags |= MB_YESNO;
    }

    if (&parent != &Window::None) {
        return MessageWindow_response(buttons,
            MessageBox(parent.widget->window, utf16_t(text), L"", flags));
    }

    return MessageWindow_response(buttons,
        MessageBox(0, utf16_t(text), L"", flags));
}

MessageWindow::Response MessageWindow::question(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    UINT flags = MB_ICONQUESTION;

    if (buttons == Buttons::Ok) {
        flags |= MB_OK;
    }

    if (buttons == Buttons::OkCancel) {
        flags |= MB_OKCANCEL;
    }

    if (buttons == Buttons::YesNo) {
        flags |= MB_YESNO;
    }

    if (&parent != &Window::None) {
        return MessageWindow_response(buttons,
            MessageBox(parent.widget->window, utf16_t(text), L"", flags));
    }

    return MessageWindow_response(buttons,
        MessageBox(0, utf16_t(text), L"", flags));
}

MessageWindow::Response MessageWindow::warning(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    UINT flags = MB_ICONWARNING;

    if (buttons == Buttons::Ok) {
        flags |= MB_OK;
    }

    if (buttons == Buttons::OkCancel) {
        flags |= MB_OKCANCEL;
    }

    if (buttons == Buttons::YesNo) {
        flags |= MB_YESNO;
    }

    if (&parent != &Window::None) {
        MessageWindow_response(buttons,
            MessageBox(parent.widget->window, utf16_t(text), L"", flags));
    }

    return MessageWindow_response(buttons,
        MessageBox(0, utf16_t(text), L"", flags));
}

MessageWindow::Response MessageWindow::critical(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    UINT flags = MB_ICONERROR;

    if (buttons == Buttons::Ok) {
        flags |= MB_OK;
    }

    if (buttons == Buttons::OkCancel) {
        flags |= MB_OKCANCEL;
    }

    if (buttons == Buttons::YesNo) {
        flags |= MB_YESNO;
    }

    if (&parent != &Window::None) {
        return MessageWindow_response(buttons,
            MessageBox(parent.widget->window, utf16_t(text), L"", flags));
    }

    return MessageWindow_response(buttons,
        MessageBox(0, utf16_t(text), L"", flags));
}
