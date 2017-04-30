static gint Window_close(Window *window)
{
    return true;
}

void Window::create(unsigned x, unsigned y, unsigned width, unsigned height,
    const string &text)
{

}

bool Window::focused(void)
{
    return false;
}

void Window::setFocused(void)
{

}

Geometry Window::geometry(void)
{
    return Geometry(0, 0, 0, 0);
}

void Window::setGeometry(unsigned x, unsigned y, unsigned width,
    unsigned height)
{

}

void Window::setDefaultFont(Font &font)
{

}

void Window::setFont(Font &font)
{

}

void Window::setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue)
{

}

void Window::setTitle(const string &text)
{

}

void Window::setStatusText(const string &text)
{

}

void Window::setMenuVisible(bool visible)
{

}

void Window::setStatusVisible(bool visible)
{

}

Window::Window()
{

}
