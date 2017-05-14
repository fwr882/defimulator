/*
* This class encapsulates the MenuBar at the top of the defimulator
* window.  The definitions are organized in a 'bread-first' manner with
* all the main menu buttons being declared first, with the rest of the
* menus being declared left-to-right.
*
* This class inherits from "MenuBar" of the gtkmm library so that it can
* be planted directly in the application window with little else to be
* concerned with from the window's perspective.
*
*/

#ifndef DEFIMULATOR_UI_MENUBAR_H
#define DEFIMULATOR_UI_MENUBAR_H

/* For std::unique_ptr<> */
#include <memory>

#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/window.h>

class MenuBar : public Gtk::MenuBar {
/*
* XXX:
* Since we started this journey with everything being a struct instead
* of a class, I'm making everything public to start with.  Once I get it
* working, I'll start moving things into the private portion of the class.
*/
public:
    /* All the main options in the menu bar */
    Gtk::MenuItem m_sysmenubutton;
    Gtk::MenuItem m_settingsmenubutton;
    Gtk::MenuItem m_toolsmenubutton;
    Gtk::MenuItem m_helpmenubutton;

    /*
    * The "System" menu
    */
    Gtk::Menu m_sysmenu;
    Gtk::MenuItem m_loadcart;
    Gtk::MenuItem m_loadcartspecial;
    Gtk::SeparatorMenuItem m_sep1;
    Gtk::MenuItem m_powerbutton;
    Gtk::MenuItem m_resetbutton;
    Gtk::SeparatorMenuItem m_sep2;
    Gtk::MenuItem m_portonebutton;
    Gtk::MenuItem m_porttwobutton;
    Gtk::SeparatorMenuItem m_sep3;
    Gtk::MenuItem m_quitbutton;

    /* System->Load Special Cartridge menu */
    Gtk::Menu m_loadcartspecialmenu;
    Gtk::MenuItem m_loadbsxslotted;
    Gtk::MenuItem m_loadbsx;
    Gtk::MenuItem m_loadsufamiturbo;
    Gtk::MenuItem m_loadsupergameboy;

    /* System->Port One menu */
    Gtk::Menu m_portonemenu;
    std::unique_ptr<Gtk::RadioMenuItem> m_portonenone;
    std::unique_ptr<Gtk::RadioMenuItem> m_portonegamepad;
    std::unique_ptr<Gtk::RadioMenuItem> m_portonemultitap;
    std::unique_ptr<Gtk::RadioMenuItem> m_portonemouse;

    /* System->Port Two menu */
    Gtk::Menu m_porttwomenu;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwonone;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwogamepad;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwomultitap;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwomouse;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwosuperscope;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwojustifier;
    std::unique_ptr<Gtk::RadioMenuItem> m_porttwojustifiers;

    /*
    * The "Settings" Menu
    */
    Gtk::Menu m_settingsmenu;
    Gtk::MenuItem m_videomode;
    Gtk::CheckMenuItem m_smoothvideo;
    Gtk::SeparatorMenuItem m_sep4;
    Gtk::CheckMenuItem m_synchronizevideo;
    Gtk::CheckMenuItem m_synchronizeaudio;
    Gtk::CheckMenuItem m_muteaudio;
    Gtk::SeparatorMenuItem m_sep5;
    Gtk::MenuItem m_videosettings;
    Gtk::MenuItem m_audiosettings;
    Gtk::MenuItem m_inputsettings;
    Gtk::MenuItem m_hotkeysettings;
    Gtk::MenuItem m_advancedsettings;

    /* Settings->Video Mode menu */
    Gtk::Menu m_videomodemenu;
    std::unique_ptr<Gtk::RadioMenuItem> m_scaleone;
    std::unique_ptr<Gtk::RadioMenuItem> m_scaletwo;
    std::unique_ptr<Gtk::RadioMenuItem> m_scalethree;
    std::unique_ptr<Gtk::RadioMenuItem> m_scalefour;
    std::unique_ptr<Gtk::RadioMenuItem> m_scalefive;
    Gtk::SeparatorMenuItem m_sep6;
    Gtk::CheckMenuItem m_correctaspectratio;
    Gtk::SeparatorMenuItem m_sep7;
    std::unique_ptr<Gtk::RadioMenuItem> m_videontsc;
    std::unique_ptr<Gtk::RadioMenuItem> m_videopal;

    /*
    * The "Tools" Menu
    */
    Gtk::Menu m_toolsmenu;
    Gtk::MenuItem m_savestate;
    Gtk::MenuItem m_loadstate;
    Gtk::SeparatorMenuItem m_sep8;
    Gtk::MenuItem m_capturemouse;
    Gtk::SeparatorMenuItem m_sep9;
    Gtk::MenuItem m_cheateditor;
    Gtk::MenuItem m_statemanager;
    #if defined(DEBUGGER)
    Gtk::SeparatorMenuItem m_sepdebug;
    Gtk::MenuItem m_debuggerbutton;
    #endif

    /* "Tools->Save State" Menu */
    Gtk::Menu m_savemenu;
    Gtk::MenuItem m_saveone;
    Gtk::MenuItem m_savetwo;
    Gtk::MenuItem m_savethree;
    Gtk::MenuItem m_savefour;
    Gtk::MenuItem m_savefive;

    /* "Tools->Load State" Menu */
    Gtk::Menu m_loadmenu;
    Gtk::MenuItem m_loadone;
    Gtk::MenuItem m_loadtwo;
    Gtk::MenuItem m_loadthree;
    Gtk::MenuItem m_loadfour;
    Gtk::MenuItem m_loadfive;

    /*
    * The "Help" Menu
    */
    Gtk::Menu m_helpmenu;
    Gtk::MenuItem m_aboutbutton;

    MenuBar(void);
    virtual ~MenuBar(void);
};

#endif
