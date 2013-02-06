#pragma once
#ifndef NativeUtils_Encodings_h__
#define NativeUtils_Encodings_h__

#include <string>
#if WINVER < 0x0602
#include <winnls.h>
#else
#include <Stringapiset.h>
#endif

namespace Encodings
{
    inline std::wstring MultiToUTF16(const std::string &source, UINT codepage, DWORD flags)
    {
        std::wstring ret(::MultiByteToWideChar(codepage, flags, source.data(), static_cast<int>(source.length()), nullptr, 0), wchar_t());
		if (ret.empty()) return ret;
        ::MultiByteToWideChar(codepage, flags, source.data(), static_cast<int>(source.length()), &ret[0], static_cast<int>(ret.length()));
        return ret;
    }
    inline std::string UTF16ToMulti(const std::wstring &source, UINT codepage, DWORD flags)
    {
        std::string ret(::WideCharToMultiByte(codepage, flags, source.data(), static_cast<int>(source.length()), nullptr, 0, nullptr, nullptr), char());
		if (ret.empty()) return ret;
        ::WideCharToMultiByte(codepage, flags, source.data(), static_cast<int>(source.length()), &ret[0], static_cast<int>(ret.length()), nullptr, nullptr);
        return ret;
    }
    inline std::string UTF16ToAnsi(const std::wstring &source) { return UTF16ToMulti(source, CP_ACP, 0); }
    inline std::string UTF16ToUTF8(const std::wstring &source) { return UTF16ToMulti(source, CP_UTF8, 0); }
    inline std::string UTF16ToUTF7(const std::wstring &source) { return UTF16ToMulti(source, CP_UTF7, 0); }
    inline std::wstring AnsiToUTF16(const std::string &source) { return MultiToUTF16(source, CP_ACP, 0); }
    inline std::wstring UTF8ToUTF16(const std::string &source) { return MultiToUTF16(source, CP_UTF8, 0); }
    inline std::wstring UTF7ToUTF16(const std::string &source) { return MultiToUTF16(source, CP_UTF7, 0); }
    inline std::string AnsiToUTF8(const std::string &source) { return UTF16ToUTF8(AnsiToUTF16(source)); }
    inline std::string UTF8ToAnsi(const std::string &source) { return UTF16ToAnsi(UTF8ToUTF16(source)); }
}

#endif//NativeUtils_Encodings_h__
