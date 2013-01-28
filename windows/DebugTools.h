#pragma once

#if _MSC_VER >= 1500
#include <stdio.h>
#define DebugStringConstraint _In_z_ _Printf_format_string_
#else
#define DebugStringConstraint
#endif

namespace DebugTools
{
    void __stdcall DebugString(DebugStringConstraint const char *pFormat, ...);
    void __stdcall SetThreadName( DWORD dwThreadID, char* threadName);
}

#define PRINT_CODE(_code) (DebugTools::DebugString(__FILE__"(%d) ["__FUNCTION__"]"#_code, __LINE__),_code,(void)0)
