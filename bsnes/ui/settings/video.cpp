VideoSettings videoSettings;

void VideoSettings::create() {
  Window::create(0, 0, 256, 256, "Video Settings");
  application.addWindow(this, "VideoSettings", "160,160");

  unsigned x = 5, y = 5, height = Style::TextBoxHeight;

  colorAdjustmentLabel.create(*this, x, y, 430, Style::LabelHeight, "Color Adjustment :."); y += Style::LabelHeight + 5;
  colorAdjustmentLabel.setFont(application.proportionalFontBold);

  brightnessLabel.create (*this, x,       y,  80, Style::SliderHeight, "Brightness:");
  brightnessValue.create (*this, x +  80, y,  40, Style::SliderHeight, "100%");
  brightnessSlider.create(*this, x + 130, y, 300, Style::SliderHeight, 201); y += Style::SliderHeight;

  contrastLabel.create   (*this, x,       y,  80, Style::SliderHeight, "Contrast:");
  contrastValue.create   (*this, x + 80,  y,  50, Style::SliderHeight, "100%");
  contrastSlider.create  (*this, x + 130, y, 300, Style::SliderHeight, 201); y += Style::SliderHeight;

  gammaLabel.create      (*this, x,       y,  80, Style::SliderHeight, "Gamma:");
  gammaValue.create      (*this, x +  80, y,  50, Style::SliderHeight, "100%");
  gammaSlider.create     (*this, x + 130, y, 300, Style::SliderHeight, 201); y += Style::SliderHeight + 5;

  gammaRampCheck.create  (*this, x,       y, 430, Style::CheckBoxHeight, "Enable NTSC gamma ramp simulation"); y += Style::CheckBoxHeight + 5;

  filterLabel.create(*this, x, y, 340, Style::LabelHeight, "Video Filter :."); y += Style::LabelHeight + 5;
  filterLabel.setFont(application.proportionalFontBold);

  filterPath.create(*this, x, y, 430 - height - height - 10, height);
  filterPath.setEditable(false);
  filterPath.setText(config.video.filter);
  filterClear.create(*this, x + 430 - height - height - 5, y, height, height, "");
  filterSelect.create(*this, x + 430 - height, y, height, height, "..."); y += height + 5;

  shaderLabel.create(*this, x, y, 340, Style::LabelHeight, "Pixel Shader :."); y += Style::LabelHeight + 5;
  shaderLabel.setFont(application.proportionalFontBold);

  shaderPath.create(*this, x, y, 430 - height - height - 10, height);
  shaderPath.setEditable(false);
  shaderPath.setText(config.video.shader);
  shaderClear.create(*this, x + 430 - height - height - 5, y, height, height, "");
  shaderSelect.create(*this, x + 430 - height, y, height, height, "..."); y += height + 5;

  setGeometry(0, 0, 440, y);

  brightnessSlider.setPosition(config.video.brightness);
  contrastSlider.setPosition(config.video.contrast);
  gammaSlider.setPosition(config.video.gamma);
  gammaRampCheck.setChecked(config.video.useGammaRamp);

  contrastSlider.onChange = brightnessSlider.onChange = gammaSlider.onChange = gammaRampCheck.onTick =
  { &VideoSettings::adjust, this };

  filterClear.onTick = []() {
    config.video.filter = "";
    videoSettings.filterPath.setText(config.video.filter);
    utility.setFilter();
  };

  filterSelect.onTick = []() {
    fileBrowser.fileOpen(FileBrowser::Mode::Filter, [](string filename) {
      config.video.filter = filename;
      videoSettings.filterPath.setText(config.video.filter);
      utility.setFilter();
    });
  };

  shaderClear.onTick = []() {
    config.video.shader = "";
    videoSettings.shaderPath.setText(config.video.shader);
    utility.setShader();
  };

  shaderSelect.onTick = []() {
    fileBrowser.fileOpen(FileBrowser::Mode::Shader, [](string filename) {
      config.video.shader = filename;
      videoSettings.shaderPath.setText(config.video.shader);
      utility.setShader();
    });
  };
}

void VideoSettings::adjust() {
  brightnessValue.setText({ brightnessSlider.position(), "%" });
  contrastValue.setText({ contrastSlider.position(), "%" });
  gammaValue.setText({ gammaSlider.position(), "%" });

  config.video.brightness = brightnessSlider.position();
  config.video.contrast = contrastSlider.position();
  config.video.gamma = gammaSlider.position();
  config.video.useGammaRamp = gammaRampCheck.checked();
  palette.update();
}
