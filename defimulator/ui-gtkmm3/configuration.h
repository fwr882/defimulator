#ifndef DEFIMULATOR_UI_CONFIGURATION_H
#define DEFIMULATOR_UI_CONFIGURATION_H

#include <nall/config.hpp>
#include <nall/platform.hpp>
#include <nall/string.hpp>

class Configuration : public nall::configuration {
public:
    struct Path {
        nall::string base;
        nall::string user;
        nall::string current;
        nall::string satellaviewBios;
        nall::string sufamiTurboBios;
        nall::string superGameBoyBios;
    } path;

    struct Video {
        nall::string driver;
        bool synchronize;
        bool smooth;
        nall::string filter;
        nall::string shader;
        bool region;
        unsigned scale;
        bool aspectRatioCorrection;
        unsigned brightness;
        unsigned contrast;
        unsigned gamma;
        bool useGammaRamp;
    } video;

    struct Audio {
        nall::string driver;
        bool synchronize;
        bool mute;
        unsigned volume;
        unsigned latency;
        unsigned inputFrequency;
        unsigned outputFrequency;
    } audio;

    struct Input {
        nall::string driver;
    } input;

    struct Settings {
        unsigned focusPolicy;
    } settings;

    struct Controller {
        unsigned port1;
        unsigned port2;
    } controller;

    /*
    * Diverging from the configuration structure from the original
    * UI. I'm trying to prevent global objects from happening again.
    */
    void load(void);
    void save(void);
    void create(void);
private:
    nall::string m_path;
};

#endif
