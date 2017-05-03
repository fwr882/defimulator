#ifndef DEFIMULATOR_UI_APPLICATION_H
#define DEFIMULATOR_UI_APPLICATION_H

#include "configuration.h"

class Application {
public:
    Application(void);
    virtual ~Application(void);
private:
    Configuration m_config;
};

#endif
