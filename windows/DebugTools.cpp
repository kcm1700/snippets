#include <windows.h>
#include <stdio.h>

namespace DebugTools
{
#pragma warning(push)
#pragma warning(disable:4996)
    void __cdecl DebugString(const char *pFormat, ...)
    {
        char msg[1024];
        va_list pArg;

        va_start(pArg, pFormat);
        vsprintf_s(msg, pFormat, pArg);

        char buf[1024];
        sprintf_s(buf, "[%04d] %s", (int)(GetCurrentThreadId()), msg);
        OutputDebugStringA(buf);
    }
#pragma warning(pop)


    //
    // Usage: SetThreadName (-1, "MainThread");
    //
    const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
    typedef struct tagTHREADNAME_INFO
    {
        DWORD dwType; // Must be 0x1000.
        LPCSTR szName; // Pointer to name (in user addr space).
        DWORD dwThreadID; // Thread ID (-1=caller thread).
        DWORD dwFlags; // Reserved for future use, must be zero.
    } THREADNAME_INFO;
#pragma pack(pop)

    void __stdcall SetThreadName( DWORD dwThreadID, char* threadName)
    {
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = threadName;
        info.dwThreadID = dwThreadID;
        info.dwFlags = 0;

        __try
        {
            RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }
}
