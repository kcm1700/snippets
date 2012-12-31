#pragma once
#ifndef KCM_UTILITY_FUNCTIONS_H__
#define KCM_UTILITY_FUNCTIONS_H__

template<typename T> void NullifyDeleter(T &obj) { delete obj; obj = nullptr; }
template<typename T> void NullifyDeleterArray(T &obj) { delete[] obj; obj = nullptr; }
template<typename T, typename F> void NullifyDeleter(T &obj, const F &freef) { if (obj != nullptr) {freef(obj); obj = nullptr;} }

#endif // !KCM_UTILITY_FUNCTIONS_H__
