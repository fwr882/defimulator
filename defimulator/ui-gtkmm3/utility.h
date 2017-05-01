#ifndef DEFIMULATOR_UI_UTILITY_H
#define DEFIMULATOR_UI_UTILITY_H

#include <ui/base.hpp>

struct Utility : property<Utility> {
    void setTitle(const string &text);
    void updateStatus(void);
    void setStatus(const string &text);
    void showMessage(const string &text);

    void setControllers(void);
    void setScale(unsigned scale = 0);
    void setFilter(void);
    void setShader(void);

    void cartridgeLoaded(void);
    void cartridgeUnloaded(void);

    void saveState(unsigned slot);
    void loadState(unsigned slot);

    Utility(void);

private:
    string statusCurrentText;
    string statusText;
    string statusMessage;
    time_t statusTime;
};

extern Utility utility;

#endif
