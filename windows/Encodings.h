#pragma once
#ifndef NativeUtils_Encodings_h__
#define NativeUtils_Encodings_h__

#include <string>
#include <Stringapiset.h>

namespace Encodings
{
    inline std::wstring MultiToUTF16(const std::string &source, UINT codepage, DWORD flags)
    {
        std::wstring ret(::MultiByteToWideChar(codepage, flags, source.data(), source.length(), nullptr, 0), wchar_t());
        ::MultiByteToWideChar(codepage, flags, source.data(), source.length(), &ret[0], ret.length());
        return ret;
    }
    inline std::string UTF16ToMulti(const std::wstring &source, UINT codepage, DWORD flags)
    {
        std::string ret(::WideCharToMultiByte(codepage, flags, source.data(), source.length(), nullptr, 0, nullptr, nullptr), char());
        ::WideCharToMultiByte(codepage, flags, source.data(), source.length(), &ret[0], ret.length(), nullptr, nullptr);
        return ret;
    }
    inline std::string UTF16ToAnsi(const std::wstring &source) { return UTF16ToMulti(source, CP_ACP, 0); }
    inline std::string UTF16ToUTF8(const std::wstring &source) { return UTF16ToMulti(source, CP_UTF8, 0); }
    inline std::string UTF16ToUTF7(const std::wstring &source) { return UTF16ToMulti(source, CP_UTF7, 0); }
    inline std::wstring AnsiToUTF16(const std::string &source) { return MultiToUTF16(source, CP_ACP, 0); }
    inline std::wstring UTF8ToUTF16(const std::string &source) { return MultiToUTF16(source, CP_UTF8, 0); }
    inline std::wstring UTF7ToUTF16(const std::string &source) { return MultiToUTF16(source, CP_UTF7, 0); }
}

#endif//NativeUtils_Encodings_h__
