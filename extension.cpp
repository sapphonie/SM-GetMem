#include <extension.h>


GetMem g_GetMem;                /**< Global singleton for extension's main interface */
SMEXT_LINK(&g_GetMem);


#ifdef _WIN32

    #include <Windows.h>
    #include <Psapi.h>

#else

    //https://stackoverflow.com/a/64166/6638566
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>



    int parseLine(char* line)
    {
        // This assumes that a digit will be found and the line ends in " Kb".
        int i = strlen(line);
        const char* p = line;
        while (*p <'0' || *p > '9') p++;
        line[i-3] = '\0';
        i = atoi(p);
        return i;
    }

    // Note: this value is in KB!
    int getVmSizeInKB()
    {
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL)
        {
            if (strncmp(line, "VmSize:", 7) == 0)
            {
                result = parseLine(line);
                break;
            }
        }

        fclose(file);
        return result;
    }
#endif

static cell_t Native_GetMem(IPluginContext *pContext, const cell_t *params)
{
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage / 1024;
    #else
        size_t virtualMemUsedByMe = getVmSizeInKB();
    #endif

    return virtualMemUsedByMe;
}

const sp_nativeinfo_t GetMemNatives[] =
{
    {"GetMem", Native_GetMem},
    {nullptr, nullptr},
};

bool GetMem::SDK_OnLoad(char *error, size_t maxlen, bool late)
{
    sharesys->AddNatives(myself, GetMemNatives);
    return true;
}
