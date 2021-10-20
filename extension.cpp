#include <extension.h>


GetMem g_GetMem;                /**< Global singleton for extension's main interface */
SMEXT_LINK(&g_GetMem);


#ifdef _WIN32

    #include <Windows.h>
    #include <Psapi.h>

#else

    #include <unistd.h>
    #include <ios>
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <unistd.h>

    using namespace std;

    int GetUsedMemorySizeInKB()
    {
        FILE* statm = fopen("/proc/self/statm", "r");
        if (!statm)
        {
            return -1;
        }

        long rss_in_pages;
        long virt_in_pages;
        fscanf(statm, "%li %li", &virt_in_pages, &rss_in_pages);
        fclose(statm);

        // sysconf(_SC_PAGESIZE) returns in bytes, we need KB
        double pagesize_in_kb    = sysconf(_SC_PAGESIZE) / 1024.0;

        long rss_in_kb = rss_in_pages * pagesize_in_kb;
        return rss_in_kb;
    }


#endif

static cell_t Native_GetMem(IPluginContext *pContext, const cell_t *params)
{
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        signed int  UsedMem = pmc.WorkingSetSize / 1024;
    #else
        long        UsedMem = GetUsedMemorySizeInKB();
    #endif

    return UsedMem;
}

const sp_nativeinfo_t GetMemNatives[] =
{
    {"GetMem", Native_GetMem},
    {nullptr, nullptr},
};

bool GetMem::SDK_OnLoad(char *error, size_t maxlen, bool late)
{
    sharesys->AddNatives(myself, GetMemNatives);
    sharesys->RegisterLibrary(myself, "GetMem");

    return true;
}
