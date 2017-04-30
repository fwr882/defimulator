static bool HexEditor_keyPress(GtkWidget *widget, GdkEventKey *event,
    HexEditor *self)
{
    return false;
}

static bool HexEditor_scroll(GtkRange *range, GtkScrollType scroll,
    gdouble value, HexEditor *self)
{
    return false;
}

void HexEditor::create(Window &parent, unsigned x, unsigned y,
    unsigned width, unsigned height)
{

}

void HexEditor::setSize(unsigned size)
{

}

void HexEditor::setOffset(unsigned offset)
{

}

void HexEditor::setColumns(unsigned columns)
{

}

void HexEditor::setRows(unsigned rows)
{

}

void HexEditor::update(void)
{

}

HexEditor::HexEditor(void)
{

}

//internal

bool HexEditor::keyPress(unsigned scancode)
{
    return false;
}

void HexEditor::scroll(unsigned position)
{

}

void HexEditor::setScroll(void)
{

}

void HexEditor::updateScroll(void)
{

}

unsigned HexEditor::cursorPosition(void)
{
    return 0;
}

void HexEditor::setCursorPosition(unsigned position)
{

}
