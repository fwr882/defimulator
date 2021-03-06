#ifndef DEFIMULATOR_SNES_INTERFACE_H
#define DEFIMULATOR_SNES_INTERFACE_H

class Interface {
public:
    virtual void video_refresh(const uint16_t *data, unsigned width,
        unsigned height) { }
    virtual void audio_sample(uint16_t l_sample, uint16_t r_sample) { }
    virtual void input_poll(void) { }
    virtual int16_t input_poll(bool port, Input::Device device,
        unsigned index, unsigned id) { return 0; }
    virtual void message(const string &text) { print(text, "\n"); }
};

#endif
