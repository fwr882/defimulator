#ifndef DEFIMULATOR_UI_VIEWPORT_H
#define DEFIMULATOR_UI_VIEWPORT_H

#include <gtkmm/drawingarea.h>

class Viewport : public Gtk::DrawingArea {
public:
    Viewport(void);
    virtual ~Viewport(void);
private:
};

#endif
