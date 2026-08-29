#ifndef TEMPLATE_NATURALINTEGRATION_
#define TEMPLATE_NATURALINTEGRATION_
#include "Natural.cpp"
// See Turing.cpp
#define Helpers_ NaturalIntegrationZCZMD5IH2O86W1XFTVXU3MH7J3QMLZVG

template<unsigned int CPPValue> struct IntToNat;
template<class Nat> struct NatToInt;

template<> struct IntToNat<0>{
	typedef Nat<> value;
};
template<unsigned int CPPValue>
requires((CPPValue&1)==0)
struct IntToNat<CPPValue>{
	typedef typename NaturalNumbersTYWPF96Z8TU35RIKKFFDNT87HTPU57QZ::NatNatToNat<Nat<
		False,
		typename IntToNat<CPPValue/2>::value
	>>::value value;
};
template<unsigned int CPPValue>
requires((CPPValue&1)==1)
struct IntToNat<CPPValue>{
	typedef typename NaturalNumbersTYWPF96Z8TU35RIKKFFDNT87HTPU57QZ::NatNatToNat<Nat<
		True,
		typename IntToNat<CPPValue/2>::value
	>>::value value;
};

template<>
struct NatToInt<Nat<>>{
	static constexpr unsigned int value = 0;
};
template<class... Bits>
struct NatToInt<Nat<False,Bits...>>{
	static constexpr unsigned int value = 2 * NatToInt<Nat<Bits...>>::value;
};
template<class... Bits>
struct NatToInt<Nat<True,Bits...>>{
	static constexpr unsigned int value = 1 + 2 * NatToInt<Nat<Bits...>>::value;
};

#undef Helpers_
#endif