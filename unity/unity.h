

#include <r_exec/mem.h>             // for _Mem, Mem, MemStatic, etc
#include <r_comp/segments.h>        // for Image, ObjectNames, Metadata
#include <r_code/image.h>           // for Image
#include <r_comp/decompiler.h>      // for Decompiler
#include <stdint.h>


/////////////////////////////////////////////////////////////
// compiler fuckery
#ifndef __has_declspec_attribute         // Optional of course.
#define __has_declspec_attribute(x) 0  // Compatibility with non-clang compilers.
#endif

#if __has_declspec_attribute(dllexport)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

//#define DllExport   __declspec( dllexport )


/////////////////////////////////////////////////////////////
//

extern "C" int DLLEXPORT inline foo() { return 27; }

typedef void(/*__stdcall*/ * LogCallback) (const char * str);
//LogCallback gDebugCallback, gDebugErrorCallback;

extern "C" void DLLEXPORT RegisterCoutCallback(LogCallback callback);

extern "C" void DLLEXPORT RegisterCerrCallback(LogCallback callback);


/////////////////////////////////////////////////////////////
// slight future proofing for vis stuff

//namespace jerk {
//    class Atom {
//        // wtf is your problem ??
//        typedef enum { YOU_MOMMA=0x50FA7 };
//
//    };
//}

class VisContext
{


public:
    VisContext() : m_mem(NULL), m_seed_image(NULL), m_metadata(NULL)
    {
        current = this;
    }

    ~VisContext()
    {
        current = NULL;
    }

    r_exec::_Mem *m_mem;
    r_comp::Image *m_seed_image;
    r_comp::Metadata *m_metadata;

    static VisContext *current;

};


typedef uint64_t (/*__stdcall*/ *time_base_callback_t)();

#include "settings.h"
class ExecutionContext
{
protected:
    Settings settings;
    r_comp::Image seed;
    r_comp::Metadata metadata;
    r_exec::_Mem *mem;
    r_code::vector<r_code::Code *> ram_objects; // since mem appears to keep references to these...

    time_base_callback_t time_base_callback;
    r_comp::Decompiler decompiler;

    uint64_t last_starting_time;
public:
    ExecutionContext() : mem(NULL), time_base_callback(NULL), last_starting_time(0)
    {


    }

    int init(std::string settings_path);

    int init(std::string settings_path, time_base_callback_t tcb);


    ~ExecutionContext()
    {
        if (mem != NULL) {
            delete mem;
            mem = NULL;
        }
    }

    uint64_t start()
    {
        debug("EC::start") << "this=" <<(std::hex,(void*)this) << "mem=" << (void*)mem << (std::dec,"") << "\n";
        uint64_t starting_time = mem->start();
        last_starting_time = starting_time;
        return starting_time;
    }

    void stop()
    {
        debug("EC::stop") << "shutting rMem down...";
        mem->stop();
    }

    void dump_memory(std::string decompiled_output_path = "");


    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    // injection helpers

    void inject_vec3()


};
