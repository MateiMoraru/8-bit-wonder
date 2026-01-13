#include "utils.h"
#include <cmath>
#include <random>
#include <windows.h>
#include <iostream>
#include <psapi.h>

float random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

float distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

double get_CPU()
{
    static FILETIME prevSysKernel, prevSysUser;
    static FILETIME prevProcKernel, prevProcUser;
    FILETIME sysIdle, sysKernel, sysUser;
    FILETIME procCreation, procExit, procKernel, procUser;

    // Get system times
    if (!GetSystemTimes(&sysIdle, &sysKernel, &sysUser))
        return -1.0;

    // Get process times
    if (!GetProcessTimes(GetCurrentProcess(), &procCreation, &procExit, &procKernel, &procUser))
        return -1.0;

    // Convert FILETIME to ULARGE_INTEGER
    ULARGE_INTEGER sysK, sysU, procK, procU;
    sysK.LowPart = sysKernel.dwLowDateTime;  sysK.HighPart = sysKernel.dwHighDateTime;
    sysU.LowPart = sysUser.dwLowDateTime;    sysU.HighPart = sysUser.dwHighDateTime;
    procK.LowPart = procKernel.dwLowDateTime; procK.HighPart = procKernel.dwHighDateTime;
    procU.LowPart = procUser.dwLowDateTime;   procU.HighPart = procUser.dwHighDateTime;

    static ULARGE_INTEGER prevSysK = sysK, prevSysU = sysU;
    static ULARGE_INTEGER prevProcK = procK, prevProcU = procU;

    ULONGLONG sysTotalDiff = (sysK.QuadPart - prevSysK.QuadPart) + (sysU.QuadPart - prevSysU.QuadPart);
    ULONGLONG procTotalDiff = (procK.QuadPart - prevProcK.QuadPart) + (procU.QuadPart - prevProcU.QuadPart);

    prevSysK = sysK; prevSysU = sysU;
    prevProcK = procK; prevProcU = procU;

    if (sysTotalDiff == 0)
        return 0.0;

    double cpuUsage = 100.0 * procTotalDiff / sysTotalDiff;
    return cpuUsage;
}

size_t get_RAM()
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / (1024 * 1024); // in MB
}