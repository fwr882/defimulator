#if defined(PROFILE_ACCURACY)
namespace Info {
    static const char Profile[] = "Accuracy";
}

#include <snes/cpu/cpu.hpp>
#include <snes/smp/smp.hpp>
#include <snes/dsp/dsp.hpp>
#include <snes/ppu/ppu.hpp>

#elif defined(PROFILE_COMPATIBILITY)
namespace Info {
    static const char Profile[] = "Compatibility";
}

#include <snes/cpu/cpu.hpp>
#include <snes/smp/smp.hpp>
#include <snes/alt/dsp/dsp.hpp>
#include <snes/alt/ppu-compatibility/ppu.hpp>

#elif(PROFILE_PERFORMANCE)
namespace Info {
    static const char Profile[] = "Performance";
}

#include <snes/alt/cpu/cpu.hpp>
#include <snes/smp/smp.hpp>
#include <snes/alt/dsp/dsp.hpp>
#include <snes/alt/ppu-performance/ppu.hpp>

#else
#error "ERROR: You must define a profile when compiling defimulator."
#endif /* profiles */
