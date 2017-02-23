#ifndef RUBY_VIDEO_H
#define RUBY_VIDEO_H

class Video {
public:
    static const char *Handle;
    static const char *Synchronize;
    static const char *Filter;
    static const char *Shader;
    static const char *FragmentShader;
    static const char *VertexShader;

    enum Filter {
        FilterPoint,
        FilterLinear,
    };

    virtual bool cap(const nall::string& name) { return false; }
    virtual nall::any get(const nall::string& name) { return false; }
    virtual bool set(const nall::string& name, const nall::any& value)
        { return false; }

    virtual bool lock(uint32_t *&data, unsigned &pitch,
        unsigned width, unsigned height) { return false; }
    virtual void unlock(void)  {}

    virtual void clear(void) { }
    virtual void refresh(void) { }
    virtual bool init(void) { return true; }
    virtual void term(void) { }

    Video(void) { }
    virtual ~Video(void) { }
};

#endif
