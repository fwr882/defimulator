#ifndef DEFIMULATOR_UI_GENERAL_FILEBROWSER_H
#define DEFIMULATOR_UI_GENERAL_FILEBROWSER_H

#include <ui/base.hpp>

struct FileBrowser : TopLevelWindow {
    TextBox pathBox;
    Button browseButton;
    Button upButton;
    ListBox contentsBox;

    enum class Mode : unsigned {
        Cartridge,
        Satellaview,
        SufamiTurbo,
        GameBoy,
        Filter,
        Shader
    } mode;

    void fileOpen(Mode mode, function<void (string)> callback);
    void create(void);

private:
    function<void (string)> callback;
    string folder;
    lstring filters;
    lstring contents;

    void folderBrowse(void);
    void folderUp(void);
    void fileActivate(void);
    void setFolder(const string &pathname);
    string cartridgeFolder(const string &pathname);
    void loadFile(const string &filename);
};

extern FileBrowser fileBrowser;

#endif
