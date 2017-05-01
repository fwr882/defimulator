#ifndef DEFIMULATOR_UI_TOOLS_STATEMANAGER_H
#define DEFIMULATOR_UI_TOOLS_STATEMANAGER_H

#include <ui/base.hpp>

struct StateManager : TopLevelWindow {
    ListBox stateList;
    Label descLabel;
    TextBox descEdit;
    Button loadButton;
    Button saveButton;
    Button eraseButton;

    void create(void);
    void synchronize(void);
    void refresh(void);
    void load(void);
    void save(void);
    void slotLoad(void);
    void slotSave(void);
    void slotErase(void);
    string slotLoadDescription(unsigned slot);
    void slotSaveDescription(void);

private:
    enum : unsigned {
        HeaderLength = 28,
        DescriptionLength = 512,
    };

    serializer slot[32];
};

extern StateManager stateManager;

#endif
