#ifndef DEFIMULATOR_UI_SETTINGS_H
#define DEFIMULATOR_UI_SETTINGS_H

#include <ui/base.hpp>

struct AdvancedSettings : TopLevelWindow {
    Label driverSelectionLabel;
    Label videoDriverLabel;
    ComboBox videoDriverBox;
    Label audioDriverLabel;
    ComboBox audioDriverBox;
    Label inputDriverLabel;
    ComboBox inputDriverBox;
    Label focusPolicyLabel;
    RadioBox focusPolicyPause;
    RadioBox focusPolicyIgnore;
    RadioBox focusPolicyAllow;

    void create(void);
};

struct AudioSettings : TopLevelWindow {
    Label volumeLabel;
    Label volumeValue;
    HorizontalSlider volumeSlider;
    Label frequencyLabel;
    Label frequencyValue;
    HorizontalSlider frequencySlider;

    void create(void);
};

struct InputSettings : TopLevelWindow {
    Label portLabel;
    ComboBox portBox;
    Label deviceLabel;
    ComboBox deviceBox;
    ListBox mappingList;
    Button mouseXaxis;
    Button mouseYaxis;
    Button mouseLeft;
    Button mouseMiddle;
    Button mouseRight;
    Button clearButton;

    void inputEvent(uint16_t scancode, int16_t value);
    void calibrateJoypads(void);
    void create(void);
    void setVisible(void);
    void setVisible(bool hotkeys);
    InputSettings(void);

private:
    bool joypadsCalibrated;
    bool joypadsCalibrating;
    int16_t joypadCalibration[Joypad::Count][Joypad::Axes];
    unsigned activeMouse;

    void portChanged(void);
    void deviceChanged(void);
    void mappingChanged(void);
    void setMapping(const string &mapping);
    void assignInput(void);
    void clearInput(void);
    void endAssignment(void);
};

struct VideoSettings : TopLevelWindow {
    Label colorAdjustmentLabel;
    Label brightnessLabel;
    Label brightnessValue;
    HorizontalSlider brightnessSlider;
    Label contrastLabel;
    Label contrastValue;
    HorizontalSlider contrastSlider;
    Label gammaLabel;
    Label gammaValue;
    HorizontalSlider gammaSlider;
    CheckBox gammaRampCheck;

    Label filterLabel;
    TextBox filterPath;
    Button filterClear;
    Button filterSelect;

    Label shaderLabel;
    TextBox shaderPath;
    Button shaderClear;
    Button shaderSelect;

    void create(void);
    void adjust(void);
};

extern AdvancedSettings advancedSettings;
extern AudioSettings audioSettings;
extern InputSettings inputSettings;
extern VideoSettings videoSettings;

#endif
