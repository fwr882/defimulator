struct AudioSettings : TopLevelWindow {
  Label volumeLabel;
  Label volumeValue;
  HorizontalSlider volumeSlider;
  Label frequencyLabel;
  Label frequencyValue;
  HorizontalSlider frequencySlider;

  void create();
};

extern AudioSettings audioSettings;
