namespace phoenix {

struct Window;

struct Object {
    Object(void);
    Object& operator=(const Object&) = delete;
    Object(const Object&) = delete;
/* private: */
    struct Data;
    Data *object;
private:
    virtual void unused(void);
};

struct Geometry {
    unsigned x, y;
    unsigned width, height;
    inline Geometry() : x(0), y(0), width(0), height(0) {}
    inline Geometry(unsigned x, unsigned y, unsigned width, unsigned height)
        : x(x), y(y), width(width), height(height) {}
};

struct Font : Object {
    enum class Style : unsigned {
        None = 0,
        Bold = 1,
        Italic = 2,
    };

    bool create(const nall::string &name, unsigned size,
        Font::Style style = Style::None);
    Font(void);
    ~Font(void);
/* private: */
    struct Data;
    Data *font;
};

inline Font::Style operator|(Font::Style a, Font::Style b)
    { return (Font::Style)((unsigned)a | (unsigned)b); }
inline Font::Style operator&(Font::Style a, Font::Style b)
    { return (Font::Style)((unsigned)a & (unsigned)b); }

struct Action : Object {
    virtual bool enabled(void) = 0;
    virtual void setEnabled(bool enabled = true) = 0;
    Action(void);
/* private: */
    struct Data;
    Data *action;
};

struct Menu : Action {
    void create(Window &parent, const nall::string &text);
    void create(Menu &parent, const nall::string &text);
    bool enabled();
    void setEnabled(bool enabled = true);
};

struct MenuSeparator : Action {
    void create(Menu &parent);
    bool enabled(void);
    void setEnabled(bool enabled = true);
};

struct MenuItem : Action {
    nall::function<void ()> onTick;
    void create(Menu &parent, const nall::string &text);
    bool enabled();
    void setEnabled(bool enabled = true);
};

struct MenuCheckItem : Action {
    nall::function<void ()> onTick;
    void create(Menu &parent, const nall::string &text);
    bool enabled(void);
    void setEnabled(bool enabled = true);
    bool checked(void);
    void setChecked(bool checked = true);
};

struct MenuRadioItem : Action {
    nall::function<void ()> onTick;
    void create(Menu &parent, const nall::string &text);
    void create(MenuRadioItem &parent, const nall::string &text);
    bool enabled(void);
    void setEnabled(bool enabled = true);
    bool checked(void);
    void setChecked(void);
};

struct Widget : Object {
    virtual void setFont(Font &font);
    bool visible(void);
    void setVisible(bool visible = true);
    bool enabled(void);
    void setEnabled(bool enabled = true);
    bool focused(void);
    void setFocused(void);
    virtual void setGeometry(unsigned x, unsigned y, unsigned width,
        unsigned height);
    Widget(void);
/* private: */
    struct Data;
    Data *widget;
};

struct Window : Widget {
    nall::function<bool ()> onClose;
    void create(unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    void setDefaultFont(Font &font);
    void setFont(Font &font);
    Geometry geometry(void);
    void setGeometry(unsigned x, unsigned y, unsigned width, unsigned height);
    void setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue);
    void setTitle(const nall::string &text);
    void setStatusText(const nall::string &text);
    void setMenuVisible(bool visible = true);
    void setStatusVisible(bool visible = true);
    Window(void);
/* private: */
    struct Data;
    Data *window;
    static Window None;
    void resize(unsigned width, unsigned height);
};

struct Button : Widget {
    nall::function<void ()> onTick;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
};

struct Canvas : Widget {
    void create(Window &parent, unsigned x, unsigned y,
        unsigned width, unsigned height);
    uint32_t* buffer(void);
    void redraw(void);
    Canvas(void);
    ~Canvas(void);
/* private: */
    struct Data;
    Data *canvas;
};

struct CheckBox : Widget {
    nall::function<void ()> onTick;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    bool checked();
    void setChecked(bool checked = true);
};

struct ComboBox : Widget {
    nall::function<void ()> onChange;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    void reset(void);
    void addItem(const nall::string &text);
    unsigned selection(void);
    void setSelection(unsigned item);
    ComboBox(void);
/* private: */
    struct Data;
    Data *comboBox;
};

struct EditBox : Widget {
    nall::function<void ()> onChange;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    nall::string getText();
    void setText(const nall::string &text);
    void setEditable(bool editable = true);
    void setWordWrap(bool wordWrap = true);
    EditBox(void);
/* private: */
    struct Data;
    Data *editBox;
};

struct HorizontalSlider : Widget {
    nall::function<void ()> onChange;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, unsigned length);
    unsigned position(void);
    void setPosition(unsigned position);
    HorizontalSlider(void);
/* private: */
    struct Data;
    Data *horizontalSlider;
};

struct Label : Widget {
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    void setText(const nall::string &text);
};

struct ListBox : Widget {
    nall::function<void ()> onActivate;
    nall::function<void ()> onChange;
    nall::function<void (unsigned)> onTick;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    void setHeaderVisible(bool headerVisible = true);
    void setCheckable(bool checkable = true);
    void reset(void);
    void resizeColumnsToContent(void);
    void addItem(const nall::string &text);
    void setItem(unsigned row, const nall::string &text);
    bool checked(unsigned row);
    void setChecked(unsigned row, bool checked = true);
    nall::optional<unsigned> selection(void);
    void setSelection(unsigned row);
    ListBox(void);
//private:
    struct Data;
    Data *listBox;
};

struct ProgressBar : Widget {
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height);
    unsigned position();
    void setPosition(unsigned position);
};

struct RadioBox : Widget {
    nall::function<void ()> onTick;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    void create(RadioBox &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    bool checked(void);
    void setChecked(void);
    RadioBox(void);
//private:
    struct Data;
    Data *radioBox;
};

struct TextBox : Widget {
    nall::function<void ()> onActivate;
    nall::function<void ()> onChange;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, const nall::string &text = "");
    nall::string text(void);
    void setText(const nall::string &text);
    void setEditable(bool editable = true);
};

struct VerticalSlider : Widget {
    nall::function<void ()> onChange;
    void create(Window &parent, unsigned x, unsigned y, unsigned width,
        unsigned height, unsigned length);
    unsigned position(void);
    void setPosition(unsigned position);
    VerticalSlider(void);
//private:
    struct Data;
    Data *verticalSlider;
};

struct Viewport : Widget {
    void create(Window &parent, unsigned x, unsigned y,
        unsigned width, unsigned height);
    uintptr_t handle(void);
};

struct MessageWindow : Object {
    enum class Buttons : unsigned {
        Ok,
        OkCancel,
        YesNo,
    };

    enum class Response : unsigned {
        Ok,
        Cancel,
        Yes,
        No,
    };

    static Response information(Window &parent, const nall::string &text,
        Buttons = Buttons::Ok);
    static Response question(Window &parent, const nall::string &text,
        Buttons = Buttons::YesNo);
    static Response warning(Window &parent, const nall::string &text,
        Buttons = Buttons::Ok);
    static Response critical(Window &parent, const nall::string &text,
        Buttons = Buttons::Ok);
};

struct OS : Object {
    static bool pending(void);
    static void run(void);
    static void main(void);
    static void quit(void);
    static unsigned desktopWidth(void);
    static unsigned desktopHeight(void);
    static nall::string folderSelect(Window &parent,
        const nall::string &path = "");
    static nall::string fileOpen(Window &parent, const nall::string &filter,
        const nall::string &path = "");
    static nall::string fileSave(Window &parent, const nall::string &filter,
        const nall::string &path = "");
/* private: */
    static void initialize(void);
    struct Data;
    static Data *os;
    static Object* findObject(unsigned id);
    friend class Object;
};

};
