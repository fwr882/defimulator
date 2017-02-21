#include <gameboy/gameboy.hpp>

#define SCHEDULER_CPP
namespace GameBoy {

Scheduler scheduler;

void Scheduler::enter(void)
{
    host_thread = co_active();
    co_switch(active_thread);
}

void Scheduler::exit(ExitReason reason)
{
    exit_reason = reason;
    active_thread = co_active();
    co_switch(host_thread);
}

void Scheduler::swapto(Processor &p)
{
    active_thread = p.thread;
    co_switch(active_thread);
}

void Scheduler::init(void)
{
    host_thread = co_active();
    active_thread = cpu.thread;
}

Scheduler::Scheduler(void)
{
    exit_reason = ExitReason::UnknownEvent;
    host_thread = 0;
    active_thread = 0;
}

}
