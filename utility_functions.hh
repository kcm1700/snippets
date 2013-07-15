#pragma once
#ifndef KCM_UTILITY_FUNCTIONS_H__
#define KCM_UTILITY_FUNCTIONS_H__

template<typename T> void NullifyDeleter(T &obj) { delete obj; obj = nullptr; }
template<typename T> void NullifyDeleterArray(T &obj) { delete[] obj; obj = nullptr; }
template<typename T, typename F> void NullifyDeleter(T &obj, const F &freef) { if (obj != nullptr) {freef(obj); obj = nullptr;} }

/// returns if a starts with b
template<typename TyContainer, typename TyContainer2> inline 
bool starts_with(const TyContainer &a, const TyContainer2 &b)
{
	auto I = a.cbegin(), IEnd = a.cend();
	auto J = b.cbegin(), JEnd = b.cend();
	while(J != JEnd && I != IEnd && *I == *J)
		++I, ++J;
	return J == JEnd;
}

#endif // !KCM_UTILITY_FUNCTIONS_H__
