struct MainWindow : TopLevelWindow {
  Menu system;
  MenuItem systemLoadCartridge;
  Menu systemLoadCartridgeSpecial;
  MenuItem systemLoadCartridgeBsxSlotted;
  MenuItem systemLoadCartridgeBsx;
  MenuItem systemLoadCartridgeSufamiTurbo;
  MenuItem systemLoadCartridgeSuperGameBoy;
  MenuSeparator systemSeparator1;
  MenuItem systemPower;
  MenuItem systemReset;
  MenuSeparator systemSeparator2;
  Menu systemPort1;
  MenuRadioItem systemPort1None;
  MenuRadioItem systemPort1Gamepad;
  MenuRadioItem systemPort1Multitap;
  MenuRadioItem systemPort1Mouse;
  Menu systemPort2;
  MenuRadioItem systemPort2None;
  MenuRadioItem systemPort2Gamepad;
  MenuRadioItem systemPort2Multitap;
  MenuRadioItem systemPort2Mouse;
  MenuRadioItem systemPort2SuperScope;
  MenuRadioItem systemPort2Justifier;
  MenuRadioItem systemPort2Justifiers;

  Menu settings;
  Menu settingsVideoMode;
  MenuRadioItem settingsVideoMode1x;
  MenuRadioItem settingsVideoMode2x;
  MenuRadioItem settingsVideoMode3x;
  MenuRadioItem settingsVideoMode4x;
  MenuRadioItem settingsVideoMode5x;
  MenuSeparator settingsVideoModeSeparator1;
  MenuCheckItem settingsVideoModeAspectRatioCorrection;
  MenuSeparator settingsVideoModeSeparator2;
  MenuRadioItem settingsVideoModeNTSC;
  MenuRadioItem settingsVideoModePAL;
  MenuCheckItem settingsSmoothVideo;
  MenuSeparator settingsSeparator1;
  MenuCheckItem settingsSynchronizeVideo;
  MenuCheckItem settingsSynchronizeAudio;
  MenuCheckItem settingsMuteAudio;
  MenuSeparator settingsSeparator2;
  MenuItem settingsVideo;
  MenuItem settingsAudio;
  MenuItem settingsInput;
  MenuItem settingsAdvanced;

  Menu tools;
  Menu toolsStateSave;
  MenuItem toolsStateSave1;
  MenuItem toolsStateSave2;
  MenuItem toolsStateSave3;
  MenuItem toolsStateSave4;
  MenuItem toolsStateSave5;
  Menu toolsStateLoad;
  MenuItem toolsStateLoad1;
  MenuItem toolsStateLoad2;
  MenuItem toolsStateLoad3;
  MenuItem toolsStateLoad4;
  MenuItem toolsStateLoad5;
  MenuSeparator toolsSeparator1;
  MenuItem toolsCaptureMouse;
  MenuSeparator toolsSeparator2;
  MenuItem toolsCheatEditor;
  MenuItem toolsStateManager;
  #if defined(DEBUGGER)
  MenuSeparator toolsSeparator3;
  MenuItem toolsDebugger;
  #endif

  Menu help;
  MenuItem helpAbout;

  Viewport viewport;

  void create();
  void synchronize();
};

extern MainWindow mainWindow;
