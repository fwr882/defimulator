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

extern InputSettings inputSettings;
