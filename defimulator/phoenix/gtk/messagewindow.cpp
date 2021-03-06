static MessageWindow::Response MessageWindow_response(
    MessageWindow::Buttons buttons, gint response)
{
    switch (response) {
    case GTK_RESPONSE_OK:
        return MessageWindow::Response::Ok;
    case GTK_RESPONSE_CANCEL:
        return MessageWindow::Response::Cancel;
    case GTK_RESPONSE_YES:
        return MessageWindow::Response::Yes;
    case GTK_RESPONSE_NO:
        return MessageWindow::Response::No;
    }

    switch (buttons) {
    case MessageWindow::Buttons::OkCancel:
        return MessageWindow::Response::Cancel;
    case MessageWindow::Buttons::YesNo:
        return MessageWindow::Response::No;
    }

    return MessageWindow::Response::Ok;

    /* I feel like this block of code is better served by the above switch.
    *
    if (response == GTK_RESPONSE_OK) {
        return MessageWindow::Response::Ok;
    }

    if (response == GTK_RESPONSE_CANCEL) {
        return MessageWindow::Response::Cancel;
    }

    if (response == GTK_RESPONSE_YES) {
        return MessageWindow::Response::Yes;
    }

    if (response == GTK_RESPONSE_NO) {
        return MessageWindow::Response::No;
    }

    if (buttons == MessageWindow::Buttons::OkCancel) {
        return MessageWindow::Response::Cancel;
    }

    if (buttons == MessageWindow::Buttons::YesNo) {
        return MessageWindow::Response::No;
    }

    return MessageWindow::Response::Ok;
    */
}

MessageWindow::Response MessageWindow::information(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    GtkButtonsType buttonsType = GTK_BUTTONS_OK;

    if (buttons == Buttons::OkCancel) {
        buttonsType = GTK_BUTTONS_OK_CANCEL;
    }

    if (buttons == Buttons::YesNo) {
        buttonsType = GTK_BUTTONS_YES_NO;
    }

    GtkWidget *dialog = nullptr;
    if (&parent != &Window::None) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(parent.object->widget),
            GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, buttonsType, "%s",
            (const char*)text);
    } else {
        dialog = gtk_message_dialog_new((GtkWindow*)0, GTK_DIALOG_MODAL,
            GTK_MESSAGE_INFO, buttonsType, "%s", (const char*)text);
    }

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return MessageWindow_response(buttons, response);
}

MessageWindow::Response MessageWindow::question(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    GtkButtonsType buttonsType = GTK_BUTTONS_OK;

    if (buttons == Buttons::OkCancel) {
        buttonsType = GTK_BUTTONS_OK_CANCEL;
    }

    if (buttons == Buttons::YesNo) {
        buttonsType = GTK_BUTTONS_YES_NO;
    }

    GtkWidget *dialog = nullptr;
    if (&parent != &Window::None) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(parent.object->widget),
            GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, buttonsType, "%s",
            (const char*)text);
    } else {
        dialog = gtk_message_dialog_new((GtkWindow*)0, GTK_DIALOG_MODAL,
            GTK_MESSAGE_QUESTION, buttonsType, "%s", (const char*)text);
    }

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return MessageWindow_response(buttons, response);
}

MessageWindow::Response MessageWindow::warning(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    GtkButtonsType buttonsType = GTK_BUTTONS_OK;

    if (buttons == Buttons::OkCancel) {
        buttonsType = GTK_BUTTONS_OK_CANCEL;
    }

    if (buttons == Buttons::YesNo) {
        buttonsType = GTK_BUTTONS_YES_NO;
    }

    GtkWidget *dialog = nullptr;
    if (&parent != &Window::None) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(parent.object->widget),
            GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, buttonsType, "%s",
            (const char*)text);
    } else {
        dialog = gtk_message_dialog_new((GtkWindow*)0, GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING, buttonsType, "%s", (const char*)text);
    }

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return MessageWindow_response(buttons, response);
}

MessageWindow::Response MessageWindow::critical(Window &parent,
    const string &text, MessageWindow::Buttons buttons)
{
    GtkButtonsType buttonsType = GTK_BUTTONS_OK;
    if (buttons == Buttons::OkCancel) {
        buttonsType = GTK_BUTTONS_OK_CANCEL;
    }

    if (buttons == Buttons::YesNo) {
        buttonsType = GTK_BUTTONS_YES_NO;
    }

    GtkWidget *dialog = nullptr;
    if (&parent != &Window::None) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(parent.object->widget),
            GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, buttonsType, "%s",
            (const char*)text);
    } else {
        dialog = gtk_message_dialog_new((GtkWindow*)0, GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR, buttonsType, "%s", (const char*)text);
    }

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    return MessageWindow_response(buttons, response);
}
