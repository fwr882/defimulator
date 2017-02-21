class Input {
public:
    static const char *Handle;
    static const char *KeyboardSupport;
    static const char *MouseSupport;
    static const char *JoypadSupport;

    virtual bool cap(const nall::string& name) { return false; }
    virtual nall::any get(const nall::string& name) { return false; }
    virtual bool set(const nall::string& name, const nall::any& value)
        { return false; }

    virtual bool acquire(void) { return false; }
    virtual bool unacquire(void) { return false; }
    virtual bool acquired(void) { return false; }

    virtual bool poll(int16_t *table) { return false; }
    virtual bool init(void) { return true; }
    virtual void term(void) {}

    Input(void) {}
    virtual ~Input(void) {}
};
