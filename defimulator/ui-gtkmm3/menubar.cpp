#include "menubar.h"

MenuBar::MenuBar(void)
{
    m_sysmenubutton.set_label("System");
    m_settingsmenubutton.set_label("Settings");
    m_toolsmenubutton.set_label("Tools");
    m_helpmenubutton.set_label("Help");

    this->append(m_sysmenubutton);
    this->append(m_settingsmenubutton);
    this->append(m_toolsmenubutton);
    this->append(m_helpmenubutton);

    m_loadcart.set_label("Load Cartridge");
    m_loadcartspecial.set_label("Load Special");
    m_powerbutton.set_label("Power");
    m_resetbutton.set_label("Reset");
    m_portonebutton.set_label("Controller Port 1");
    m_porttwobutton.set_label("Controller Port 2");

    m_loadbsxslotted.set_label("BS-X Slotted Cartridge ...");
    m_loadbsx.set_label("BS-X Cartridge ...");
    m_loadsufamiturbo.set_label("Sufami Turbo Cartridge ...");
    m_loadsupergameboy.set_label("Super Game Boy Cartridge ...");

    m_loadcartspecialmenu.append(m_loadbsxslotted);
    m_loadcartspecialmenu.append(m_loadbsx);
    m_loadcartspecialmenu.append(m_loadsufamiturbo);
    m_loadcartspecialmenu.append(m_loadsupergameboy);
    m_loadcartspecial.set_submenu(m_loadcartspecialmenu);

    Gtk::RadioButtonGroup portonegroup;
    m_portonenone = std::unique_ptr<Gtk::RadioMenuItem>(
        new Gtk::RadioMenuItem(portonegroup));
    m_portonegamepad = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(portonegroup));
    m_portonemultitap = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(portonegroup));
    m_portonemouse = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(portonegroup));

    m_portonenone->set_label("None");
    m_portonegamepad->set_label("Gamepad");
    m_portonemultitap->set_label("Multitap");
    m_portonemouse->set_label("Mouse");

    m_portonemenu.append(*m_portonenone.get());
    m_portonemenu.append(*m_portonegamepad.get());
    m_portonemenu.append(*m_portonemultitap.get());
    m_portonemenu.append(*m_portonemouse.get());
    m_portonebutton.set_submenu(m_portonemenu);

    /*
    * In order for the radio buttons to work (as in, only pick one instead
    * of operating like check boxes), they must be put in a button group,
    * Gtk::RadioButtonGroup in this case, and then the radio buttons must
    * be constructed with the group as the constructor argument.  For this
    * reason, all RadioMenuItem objects must be re-constructed.
    */
    Gtk::RadioButtonGroup porttwogroup;
    m_porttwonone = std::unique_ptr<Gtk::RadioMenuItem>(
        new Gtk::RadioMenuItem(porttwogroup));
    m_porttwogamepad = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));
    m_porttwomultitap = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));
    m_porttwomouse = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));
    m_porttwosuperscope = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));
    m_porttwojustifier = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));
    m_porttwojustifiers = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(porttwogroup));

    m_porttwonone->set_label("None");
    m_porttwogamepad->set_label("Gamepad");
    m_porttwomultitap->set_label("Multitap");
    m_porttwomouse->set_label("Mouse");
    m_porttwosuperscope->set_label("Super Scope");
    m_porttwojustifier->set_label("Justifier");
    m_porttwojustifiers->set_label("Justifiers");

    m_porttwomenu.append(*m_porttwonone.get());
    m_porttwomenu.append(*m_porttwogamepad.get());
    m_porttwomenu.append(*m_porttwomultitap.get());
    m_porttwomenu.append(*m_porttwomouse.get());
    m_porttwomenu.append(*m_porttwosuperscope.get());
    m_porttwomenu.append(*m_porttwojustifier.get());
    m_porttwomenu.append(*m_porttwojustifiers.get());
    m_porttwobutton.set_submenu(m_porttwomenu);

    m_sysmenu.append(m_loadcart);
    m_sysmenu.append(m_loadcartspecial);
    m_sysmenu.append(m_sep1);
    m_sysmenu.append(m_powerbutton);
    m_sysmenu.append(m_resetbutton);
    m_sysmenu.append(m_sep2);
    m_sysmenu.append(m_portonebutton);
    m_sysmenu.append(m_porttwobutton);
    m_sysmenubutton.set_submenu(m_sysmenu);

    m_videomode.set_label("Video Mode");
    m_smoothvideo.set_label("Smooth Video");
    m_synchronizevideo.set_label("Synchronize Video");
    m_synchronizeaudio.set_label("Synchronize Audio");
    m_muteaudio.set_label("Mute Audio");
    m_videosettings.set_label("Video Settings ...");
    m_audiosettings.set_label("Audio Settings ...");
    m_inputsettings.set_label("Input Settings ...");
    m_hotkeysettings.set_label("Hotkey Settings ...");
    m_advancedsettings.set_label("Advanced Settings ...");

    Gtk::RadioButtonGroup vidscalegroup;
    m_scaleone = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(vidscalegroup));
    m_scaletwo = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(vidscalegroup));
    m_scalethree = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(vidscalegroup));
    m_scalefour = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(vidscalegroup));
    m_scalefive = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(vidscalegroup));

    Gtk::RadioButtonGroup videoregiongroup;
    m_videontsc = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(videoregiongroup));
    m_videopal = std::unique_ptr<Gtk::RadioMenuItem>(
		new Gtk::RadioMenuItem(videoregiongroup));

    m_scaleone->set_label("Scale 1x");
    m_scaletwo->set_label("Scale 2x");
    m_scalethree->set_label("Scale 3x");
    m_scalefour->set_label("Scale 4x");
    m_scalefive->set_label("Scale 5x");
    m_correctaspectratio.set_label("Correct Aspect Ratio");
    m_videontsc->set_label("NTSC");
    m_videopal->set_label("PAL");

    m_videomodemenu.append(*m_scaleone.get());
    m_videomodemenu.append(*m_scaletwo.get());
    m_videomodemenu.append(*m_scalethree.get());
    m_videomodemenu.append(*m_scalefour.get());
    m_videomodemenu.append(*m_scalefive.get());
    m_videomodemenu.append(m_sep5);
    m_videomodemenu.append(m_correctaspectratio);
    m_videomodemenu.append(m_sep6);
    m_videomodemenu.append(*m_videontsc.get());
    m_videomodemenu.append(*m_videopal.get());
    m_videomode.set_submenu(m_videomodemenu);

    m_settingsmenu.append(m_videomode);
    m_settingsmenu.append(m_smoothvideo);
    m_settingsmenu.append(m_sep3);
    m_settingsmenu.append(m_synchronizevideo);
    m_settingsmenu.append(m_synchronizeaudio);
    m_settingsmenu.append(m_muteaudio);
    m_settingsmenu.append(m_sep4);
    m_settingsmenu.append(m_videosettings);
    m_settingsmenu.append(m_audiosettings);
    m_settingsmenu.append(m_inputsettings);
    m_settingsmenu.append(m_hotkeysettings);
    m_settingsmenu.append(m_advancedsettings);
    m_settingsmenubutton.set_submenu(m_settingsmenu);

    m_savestate.set_label("Save State");
    m_loadstate.set_label("Load State");
    m_capturemouse.set_label("Capture Mouse");
    m_cheateditor.set_label("Cheat Editor ...");
    m_statemanager.set_label("State Manager ...");
    #if defined(DEBUGGER)
    m_debuggerbutton.set_label("Debugger");
    #endif

    m_saveone.set_label("Slot 1");
    m_savetwo.set_label("Slot 2");
    m_savethree.set_label("Slot 3");
    m_savefour.set_label("Slot 4");
    m_savefive.set_label("Slot 5");
    m_savemenu.append(m_saveone);
    m_savemenu.append(m_savetwo);
    m_savemenu.append(m_savethree);
    m_savemenu.append(m_savefour);
    m_savemenu.append(m_savefive);
    m_savestate.set_submenu(m_savemenu);

    m_loadone.set_label("Slot 1");
    m_loadtwo.set_label("Slot 2");
    m_loadthree.set_label("Slot 3");
    m_loadfour.set_label("Slot 4");
    m_loadfive.set_label("Slot 5");
    m_loadmenu.append(m_loadone);
    m_loadmenu.append(m_loadtwo);
    m_loadmenu.append(m_loadthree);
    m_loadmenu.append(m_loadfour);
    m_loadmenu.append(m_loadfive);
    m_loadstate.set_submenu(m_loadmenu);

    m_toolsmenu.append(m_savestate);
    m_toolsmenu.append(m_loadstate);
    m_toolsmenu.append(m_sep7);
    m_toolsmenu.append(m_capturemouse);
    m_toolsmenu.append(m_sep8);
    m_toolsmenu.append(m_cheateditor);
    m_toolsmenu.append(m_statemanager);
    #if defined(DEBUGGER)
    m_toolsmenu.append(m_sepdebug);
    m_toolsmenu.append(m_debuggerbutton);
    #endif
    m_toolsmenubutton.set_submenu(m_toolsmenu);

    m_aboutbutton.set_label("About");
    m_helpmenu.append(m_aboutbutton);
    m_helpmenubutton.set_submenu(m_helpmenu);

    /*
    * Emulator is off when it's started, so a lot of controls don't
    * make sense (contextually) be be available for clicking.
    */
    m_powerbutton.set_sensitive(false);
    m_resetbutton.set_sensitive(false);

    /*
    * TODO:
    * Ensure we have sane defaults when the user starts the program.
    * But this will be changed, depending on what sort of settings the
    * user has saved.  So this is being set in the ctor now, but there
    * will be a mechanism built in to parse settings and configure the
    * GUI appropriately.
    */
    m_portonegamepad->set_active(true);
    m_porttwonone->set_active(true);
    m_scaletwo->set_active(true);
    m_correctaspectratio.set_active(true);
    m_synchronizeaudio.set_active(true);
}

MenuBar::~MenuBar(void) { }
