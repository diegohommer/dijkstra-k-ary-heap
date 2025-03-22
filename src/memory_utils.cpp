#include "memory_utils.h"

#ifdef __linux__
# include <sys/sysinfo.h>
#endif

#ifdef __APPLE__
# include <mach/task.h>
# include <mach/mach_init.h>
#endif

#ifdef _WINDOWS
# include <windows.h>
# include <psapi.h>
#else
# include <sys/resource.h>
#endif

// SOURCE: https://stackoverflow.com/questions/372484/how-do-i-programmatically-check-memory-use-in-a-fairly-portable-way-c-c%29
size_t memory_used(bool resident) {
#if defined(__linux__)
    size_t size = 0;
    FILE *file = fopen("/proc/self/statm", "r");
    if (file) {
        unsigned long vm = 0;
        if (fscanf(file, "%lu", &vm) != 1) {
            fclose(file);
            return 0; 
        }
        fclose(file);
        size = (size_t)vm * getpagesize();
    }
    return size;

#elif defined(__APPLE__)
    struct task_basic_info t_info;
    mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;
    task_info(current_task(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count);
    return (resident ? t_info.resident_size : t_info.virtual_size);

#elif defined(_WINDOWS)
    PROCESS_MEMORY_COUNTERS counters;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters)))
        return counters.PagefileUsage;
    else return 0;

#else
    return 0;   // Unsupported platform
#endif
}
