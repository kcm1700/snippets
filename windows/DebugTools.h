#pragma once

namespace DebugTools
{
    void __stdcall DebugString(const char *pFormat, ...);
    void __stdcall SetThreadName( DWORD dwThreadID, char* threadName);
}

#define PRINT_CODE(_code) (DebugTools::DebugString(__FILE__"(%d) ["__FUNCTION__"]"#_code, __LINE__),_code,(void)0)
