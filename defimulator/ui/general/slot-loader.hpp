struct SingleSlotLoader : TopLevelWindow {
    Label baseLabel;
    TextBox basePath;
    Button baseBrowse;
    Label slotLabel;
    TextBox slotPath;
    Button slotBrowse;
    Button okButton;

    void create(void);
    void loadCartridgeBsxSlotted(void);
    void loadCartridgeBsx(void);
    void loadCartridgeSuperGameBoy(void);

    enum class Mode : unsigned {
        BsxSlotted,
        Bsx,
        SuperGameBoy
    } mode;

    void load(void);
};

struct DoubleSlotLoader : TopLevelWindow {
    Label baseLabel;
    TextBox basePath;
    Button baseBrowse;
    Label slotALabel;
    TextBox slotAPath;
    Button slotABrowse;
    Label slotBLabel;
    TextBox slotBPath;
    Button slotBBrowse;
    Button okButton;

    void create(void);
    void loadCartridgeSufamiTurbo(void);

    void load(void);
};

extern SingleSlotLoader singleSlotLoader;
extern DoubleSlotLoader doubleSlotLoader;
