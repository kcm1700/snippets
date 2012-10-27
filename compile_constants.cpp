#include <stddef.h>
#include <stdint.h>

template<bool condition, typename A, typename B> struct tif{typedef A t;};
template<typename A, typename B> struct tif<false, A, B>{typedef B t;};

template<int a> struct tneg{enum{v = -a};};
template<int a, int b> struct tadd{enum{v = a+b};};
template<int a, int b> struct tsub{enum{v = a-b};};
template<int a, int b> struct tmul{enum{v = a*b};};
template<int a, int b> struct tquot{enum{v = a/b};};
template<int a, int b> struct tmod{enum{v = a%b};};

template<template<int> class F, int value> struct tbind{struct t{enum{v = F<value>::v};};};
template<template<int, int> class F, int value> struct tbind1st{template<int other> struct t{enum{v = F<value, other>::v};};};
template<template<int, int> class F, int value> struct tbind2nd{template<int other> struct t{enum{v = F<other, value>::v};};};
template<template<int, int> class F> struct tbindcombine{template<int other> struct t{enum{v = F<other, other>::v};};};

template<template<int, int> class Op, int n, template<int> class F> struct taccumulate{enum{v = Op<F<n>::v, taccumulate<Op, n-1, F>::v>::v};};
template<template<int, int> class Op, template<int> class F> struct taccumulate<Op, 0, F>{enum{v = F<0>::v};};

template<int a, int b> struct tmin{enum{v = a<b?a:b};};
template<int a, int b> struct tmax{enum{v = a>b?a:b};};

template<int a> struct tfactorial{enum{v = a * tfactorial<a-1>::v};};
template<> struct tfactorial<0>{enum{v = 1};};
template<uint32_t a, uint32_t mod> struct tfactorialmod{enum{v = (uint32_t)((uint64_t)a * (uint64_t)tfactorial<a-1>::v % mod)};};
template<uint32_t mod> struct tfactorialmod<0,mod>{enum{v = 1u};};

template<int a, int b> struct tpow{enum{v = tpow<a,b/2>::v * tpow<a,b-b/2>::v};};
template<int a> struct tpow<a, 1>{enum{v = a};};
template<int a> struct tpow<a, 0>{enum{v = 1};};

template<uint32_t a, uint32_t b, uint32_t mod> struct tpowmod{enum{v = (uint32_t)((uint64_t)tpowmod<a,b/2,mod>::v * (uint64_t)tpowmod<a,b-b/2,mod>::v % mod)};};
template<uint32_t a, uint32_t mod> struct tpowmod<a, 1, mod>{enum{v = a%mod};};
template<uint32_t a, uint32_t mod> struct tpowmod<a, 0, mod>{enum{v = 1u};};


/* countof
 * Usage: countof(some_array) */
#ifndef countof
template<typename T, size_t n> char (&countof_helper(T(&)[n]))[n];
#define countof(array) sizeof(countof_helper(array))
#endif

/* Endianness
 * TReverseByteOrder: reverse the byte representation of integer
 * TReverseBitOrder: reverse the bit representation of integer
 * usage:
 * to get reverse byte order of 12345678u, TReverseByteOrder<uint32_t, 12345678u{{, 4}}>::v
 * to get reverse bit order of 12345678u, TReverseBitOrder<uint32_t, 12345678u{{, 32}}>::v
 * */
template<typename T, T n, size_t bytes = sizeof(T)> class TReverseByteOrder {
	template<size_t size, T m> struct reverser {
		enum {
			lowBytes = size/2,
			highBytes = size-lowBytes,
			v = (reverser<lowBytes, m&(((T)1<<lowBytes*8)-(T)1)>::v << 8*highBytes)
			| reverser<highBytes, m>>8*lowBytes>::v
		};
	};
	template<T m> struct reverser<1,m>{enum{v = m };};
public:
	enum{v = reverser<bytes, n>::v};
};

template<typename T, T n, size_t bits = 8*sizeof(T)> class TReverseBitOrder {
	template<size_t size, T m> struct reverser {
		enum {
			lowBits = size/2,
			highBits = size-lowBits,
			v = (reverser<lowBits, m&(((T)1<<lowBits)-(T)1)>::v << highBits)
			| reverser<highBits, m>>lowBits>::v
		};
	};
	template<T m> struct reverser<1,m>{enum{v = m };};
public:
	enum{v = reverser<bits, n>::v};
};

// test code
#include <stdio.h>

template<int line> void my_assert_inner(bool result)
{
	if (result) return;
	printf("test failed at line %d!\n", line);
}

#define my_assert my_assert_inner<__LINE__>

int main()
{
	my_assert(tmin<1700,1500>::v == 1500);
	my_assert(countof("asdf") == 5);
	my_assert(TReverseByteOrder<uint32_t,15838294u>::v == 1454174464u);
	my_assert((int)taccumulate<tmul,5,tbind1st<tmax,1>::t>::v == (int)tfactorial<5>::v);
	return 0;
}
