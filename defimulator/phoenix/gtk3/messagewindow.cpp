static MessageWindow::Response MessageWindow_response(
    MessageWindow::Buttons buttons, gint response)
{
    return MessageWindow::Response::Cancel;
}

MessageWindow::Response MessageWindow::information(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    return MessageWindow::Response::Cancel;
}

MessageWindow::Response MessageWindow::question(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    return MessageWindow::Response::Cancel;
}

MessageWindow::Response MessageWindow::warning(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    return MessageWindow::Response::Cancel;
}

MessageWindow::Response MessageWindow::critical(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    return MessageWindow::Response::Cancel;
}
