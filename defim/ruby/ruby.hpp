/*
  ruby
  version: 0.06 (2009-05-22)
  license: public domain
*/

#ifndef RUBY_H
#define RUBY_H

#include <nall/algorithm.hpp>
#include <nall/any.hpp>
#include <nall/array.hpp>
#include <nall/bit.hpp>
#include <nall/detect.hpp>
#include <nall/input.hpp>
#include <nall/sort.hpp>
#include <nall/stdint.hpp>
#include <nall/string.hpp>
#include <nall/vector.hpp>

namespace ruby {

#include <ruby/video.hpp>
#include <ruby/audio.hpp>
#include <ruby/input.hpp>

class VideoInterface {
public:
    void driver(const char *driver = "");
    const char* default_driver(void);
    const char* driver_list(void);
    bool init(void);
    void term(void);

    bool cap(const nall::string& name);
    nall::any get(const nall::string& name);
    bool set(const nall::string& name, const nall::any& value);

    bool lock(uint32_t *&data, unsigned &pitch,
        unsigned width, unsigned height);
    void unlock(void);
    void clear(void);
    void refresh(void);
    VideoInterface(void);
    ~VideoInterface(void);

private:
    Video *p;
};

class AudioInterface {
public:
    void driver(const char *driver = "");
    const char* default_driver(void);
    const char* driver_list(void);
    bool init(void);
    void term(void);

    bool cap(const nall::string& name);
    nall::any get(const nall::string& name);
    bool set(const nall::string& name, const nall::any& value);

    void sample(uint16_t left, uint16_t right);
    void clear(void);
    AudioInterface(void);
    ~AudioInterface(void);

private:
    Audio *p;

    unsigned volume;

    /* resample unit */
    double hermite(double mu, double a, double b, double c, double d);
    bool resample_enabled;
    double r_step, r_frac;
    int r_left[4], r_right[4];
};

class InputInterface {
public:
    void driver(const char *driver = "");
    const char* default_driver(void);
    const char* driver_list(void);
    bool init(void);
    void term(void);

    bool cap(const nall::string& name);
    nall::any get(const nall::string& name);
    bool set(const nall::string& name, const nall::any& value);

    bool acquire(void);
    bool unacquire(void);
    bool acquired(void);

    bool poll(int16_t *table);
    InputInterface(void);
    ~InputInterface(void);

private:
    Input *p;
};

extern VideoInterface video;
extern AudioInterface audio;
extern InputInterface input;

};

#endif
