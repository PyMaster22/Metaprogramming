#ifndef TEMPLATE_POSTTAGSYSTEM_
#define TEMPLATE_POSTTAGSYSTEM_
// See Turing.cpp
#define Helpers_ SW85BXKORF88XRV4M7J7BTR6Q22WKUJ7

// String of symbols. Basically list of anything, but named for human's sake
template<class... Symbols> struct String;

namespace Helpers_{
	template<class String1, class String2> struct MergeStrings;
	template<class... Symbols1, class... Symbols2>
	struct MergeStrings<String<Symbols1...>,String<Symbols2...>>{
		typedef String<Symbols1...,Symbols2...> value;
	};
}


template<class String, template<class Symbol> class Productions, class HaltSymbol> struct TwoTag;
// Default; 2+ symbols and not halted by first symbol
template<class Symbol1, class Symbol2, class... Symbols, template<class> class Productions, class HaltSymbol>
struct TwoTag<String<Symbol1,Symbol2,Symbols...>,Productions,HaltSymbol>{
	typedef String<Symbol1,Symbol2,Symbols...> Out;
	typedef TwoTag<
		typename Helpers_::MergeStrings<String<Symbols...>,typename Productions<Symbol1>::Produces>,
		Productions,HaltSymbol
	> Next;
};
// Halted by first symbol AND still has 2+ symbols
template<class Symbol2, class... Symbols, template<class> class Productions, class HaltSymbol>
struct TwoTag<String<HaltSymbol,Symbol2,Symbols...>,Productions,HaltSymbol>{
	typedef String<HaltSymbol,Symbol2,Symbols...> Out;
	// Next is same because halted
	typedef TwoTag<
		Out,Productions,HaltSymbol
	> Next;
};
// Halt by only having 1 symbol
template<class Symbol1, template<class> class Productions, class HaltSymbol>
struct TwoTag<String<Symbol1>,Productions,HaltSymbol>{
	typedef String<Symbol1> Out;
	// Next is same because halted
	typedef TwoTag<
		Out,Productions,HaltSymbol
	> Next;
};
// Halt by no symbols
template<template<class> class Productions, class HaltSymbol>
struct TwoTag<String<>,Productions,HaltSymbol>{
	typedef String<> Out;
	// Next is same because halted
	typedef TwoTag<
		Out,Productions,HaltSymbol
	> Next;
};


// Technically identical to String, but named for human's sake
template<class... ProductionStrings> struct CyclicProductions;

template<class String, class Productions, class ZeroSymbol, class OneSymbol> struct CyclicTag;
template<class... Symbols, class TopProduction, class... OtherProductions, class Zero, class One>
struct CyclicTag<String<Zero,Symbols...>,CyclicProductions<TopProduction,OtherProductions...>,Zero,One>{
	typedef String<Zero,Symbols...> Out;
	typedef CyclicTag<
		String<Symbols...>,
		CyclicProductions<OtherProductions,TopProduction>,
		Zero,One
	> Next;
};
template<class... Symbols, class TopProduction, class... OtherProductions, class Zero, class One>
struct CyclicTag<String<One,Symbols...>,CyclicProductions<TopProduction,OtherProductions...>,Zero,One>{
	typedef String<One,Symbols...> Out;
	typedef CyclicTag<
		typename Helpers_::MergeStrings<String<Symbols...>,TopProduction>::value,
		CyclicProductions<OtherProductions,TopProduction>,
		Zero,One
	> Next;
};

#endif