#if defined(DEBUGGER)

#include <ui/base.hpp>

Debugger debugger;

void Debugger::create()
{
    console.create();
    cpuDebugger.create();
    smpDebugger.create();
    breakpointEditor.create();
    memoryEditor.create();

    Window::create(0, 0, 256, 256, "Debugger");
    application.addWindow(this, "Debugger", "160,160");

    unsigned x = 5;
    unsigned y = 5;

    enableDebugger.create(*this, x, y, 240, Style::CheckBoxHeight,
        "Enable debugger");
    y += Style::CheckBoxHeight;

    showConsole.create(*this, x, y, 240, Style::CheckBoxHeight, "Console");
    y += Style::CheckBoxHeight;

    showCPUDebugger.create(*this, x, y, 240, Style::CheckBoxHeight,
        "CPU debugger");
    y += Style::CheckBoxHeight;

    showSMPDebugger.create(*this, x, y, 240, Style::CheckBoxHeight,
        "SMP debugger");
    y += Style::CheckBoxHeight;

    showBreakpointEditor.create(*this, x, y, 240, Style::CheckBoxHeight,
        "Breakpoint editor");
    y += Style::CheckBoxHeight;

    showMemoryEditor.create(*this, x, y, 240, Style::CheckBoxHeight,
        "Memory editor");
    y += Style::CheckBoxHeight;

    /* windows shown by default */
    showConsole.setChecked();
    showCPUDebugger.setChecked();
    showSMPDebugger.setChecked();
    showBreakpointEditor.setChecked();

    setGeometry(0, 0, 250, y);

    enableDebugger.onTick = []() {
        debugger.enable(debugger.enableDebugger.checked());
    };

    showConsole.onTick = []() {
        console.setVisible(debugger.showConsole.checked());
    };

    showCPUDebugger.onTick = []() {
        cpuDebugger.setVisible(debugger.showCPUDebugger.checked());
    };

    showSMPDebugger.onTick = []() {
        smpDebugger.setVisible(debugger.showSMPDebugger.checked());
    };

    showBreakpointEditor.onTick = []() {
        breakpointEditor.setVisible(debugger.showBreakpointEditor.checked());
    };

    showMemoryEditor.onTick = []() {
        memoryEditor.setVisible(debugger.showMemoryEditor.checked());
    };

    onClose = []() {
        debugger.enable(false);
        return true;
    };

    synchronize();
}

void Debugger::synchronize(void)
{
    cpuDebugger.synchronize();
    smpDebugger.synchronize();
}

void Debugger::setVisible(bool visible)
{
    Window::setVisible(visible);
    console.setVisible(showConsole.checked() & visible);
    cpuDebugger.setVisible(showCPUDebugger.checked() & visible);
    smpDebugger.setVisible(showSMPDebugger.checked() & visible);
    breakpointEditor.setVisible(showBreakpointEditor.checked() & visible);
    memoryEditor.setVisible(showMemoryEditor.checked() & visible);
}

void Debugger::enable(bool state)
{
    enableDebugger.setChecked(state);
    synchronize();
}

void Debugger::run(void)
{
    if (enableDebugger.checked() == false) {
        SNES::system.run();
        return;
    }

    if (debugMode == DebugMode::None) {
        usleep(20 * 1000);
        return;
    }

    SNES::system.run();

    if (debugMode == DebugMode::WaitForBreakpoint) {
        if (SNES::debugger.break_event ==
            SNES::Debugger::BreakEvent::BreakpointHit) {
            debugMode = DebugMode::None;
            console.eventBreakpoint();
            breakpointEditor.eventBreakpoint();
            synchronize();
        }
    }

    SNES::debugger.break_event = SNES::Debugger::BreakEvent::None;
}

bool Debugger::step_cpu(void)
{
    if (enableDebugger.checked() == false) {
        return false;
    }

    console.eventTraceCPU();
    if (debugMode == DebugMode::StepIntoCPU) {
        debugMode = DebugMode::None;
        cpuDebugger.eventStepInto();
        synchronize();
        return true;
    }

    return false;
}

bool Debugger::step_smp(void)
{
    if (enableDebugger.checked() == false) {
        return false;
    }

    console.eventTraceSMP();
    if (debugMode == DebugMode::StepIntoSMP) {
        debugMode = DebugMode::None;
        smpDebugger.eventStepInto();
        synchronize();
        return true;
    }

    return false;
}

Debugger::Debugger()
{
    debugMode = DebugMode::None;
    SNES::cpu.step_event = { &Debugger::step_cpu, this };
    SNES::smp.step_event = { &Debugger::step_smp, this };
}

#endif
