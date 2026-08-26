#ifndef TEMPLATE_BOOLEANLOGIC_
#define TEMPLATE_BOOLEANLOGIC_
// See Turing.cpp
#define Helpers_ BooleanLogicSQDNE34BKQO46ER7X2SMP9JLPNI89JTI

struct True{};
struct False{};

// Defines truthy and falsey values. Truthy by default
template<class Anything> struct CastToBool;
template<class Anything> struct CastToBool{
	typedef True value;
};
template<> struct CastToBool<False>{
	typedef False value;
};

// AKA If
template<class Condition, class TrueCase, class FalseCase> struct Ternary;
template<class C, class T, class F> struct Ternary{
	typedef typename Ternary<typename CastToBool<C>::value,T,F>::value value;
};
template<class T, class F> struct Ternary<False,T,F>{ // tf
	typedef F value;
};
template<class T, class F> struct Ternary<True,T,F>{
	typedef T value;
};

template<class Bool1, class Bool2> struct And;
template<class Bool1, class Bool2> struct Or;
template<class Bool1> struct Not;

template<class Bool1, class Bool2> struct And{
	typedef typename CastToBool<typename Ternary<Bool1,Bool2,False>::value>::value value;
};
template<class Bool1, class Bool2> struct Or{
	typedef typename CastToBool<typename Ternary<Bool1,True,Bool2>::value>::value value;
};
template<class Bool1> struct Not{
	typedef typename Ternary<Bool1,False,True>::value value;
};

#undef Helpers_
#endif