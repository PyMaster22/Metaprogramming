#ifndef TEMPLATE_LISPLANGUAGE_
#define TEMPLATE_LISPLANGUAGE_
#include "Logic.cpp"
// See Turing.cpp
#define Helpers_ LISPLanguageO6NARP7XDV6MZSP1H7I2HZSWPOOA7Z3O

struct Nil;
template<class car, class cdr> struct cons;
template<class Name> struct Symbol;

struct If;
struct Quote;
struct Atom;
struct Car;
struct Cdr;

struct Lambda;
struct Application;

template<class Parameter, class LambdaBody, class Environment> struct Closure;

template<class Expression, class Environment> struct Evaluate;

namespace Helpers_{
	template<class SymbolName, class Environment> struct SymbolLookup;
	template<class Closure, class Parameter> struct Apply;
}


namespace Helpers_{
	template<class Rest>
	struct SymbolLookup<True,Rest>{
		typedef True value;
	};
	template<class Rest>
	struct SymbolLookup<False,Rest>{
		typedef False value;
	};
	template<class SymbolName, class Value, class Rest>
	struct SymbolLookup<SymbolName,cons<cons<SymbolName,Value>,Rest>>{
		typedef Value value;
	};
	template<class SymbolName, class TopSymbol, class Rest>
	struct SymbolLookup<SymbolName,cons<TopSymbol,Rest>>{
		typedef typename SymbolLookup<SymbolName,Rest>::value value;
	};

	template<class Parameter, class Value, class Expression, class Environment>
	struct Apply<Closure<Parameter,Expression,Environment>,Value>{
		typedef typename Evaluate<
			Expression,
			cons<
				cons<Parameter,Value>,
				Environment
			>
		>::value value;
	};
}

template<class SymbolName, class Environment>
struct Evaluate<Symbol<SymbolName>,Environment>{
	typedef typename Helpers_::SymbolLookup<SymbolName,Environment>::value value;
};
template<class Expression, class TrueCase, class FalseCase, class Environment>
struct Evaluate<cons<If,cons<Expression,cons<TrueCase,cons<FalseCase,Nil>>>>,Environment>{
	typedef typename Ternary<typename Evaluate<Expression,Environment>::value,
		Evaluate<TrueCase,Environment>,
		Evaluate<FalseCase,Environment>
	>::value::value value;
};
template<class Expression, class Environment>
struct Evaluate<cons<Quote,Expression>,Environment>{
	typedef Expression value;
};
template<class Expression, class Environment>
struct Evaluate<cons<Atom,cons<Expression,Nil>>,Environment>{
	typedef True value;
};
template<class ExpressionCAR, class ExpressionCDR, class Environment>
struct Evaluate<cons<Atom,cons<ExpressionCAR,ExpressionCDR>>,Environment>{
	typedef False value;
};
template<class ExpressionCAR, class ExpressionCDR, class Environment>
struct Evaluate<cons<Car,cons<ExpressionCAR,ExpressionCDR>>,Environment>{
	typedef typename Evaluate<ExpressionCAR,Environment>::value value;
};
template<class ExpressionCAR, class ExpressionCDR, class Environment>
struct Evaluate<cons<Cdr,cons<ExpressionCAR,ExpressionCDR>>,Environment>{
	typedef typename Evaluate<ExpressionCDR,Environment>::value value;
};

template<class Argument, class Expression, class Environment>
struct Evaluate<cons<Lambda,cons<Argument,cons<Expression,Nil>>>,Environment>{
	typedef Closure<Argument,Expression,Environment> value;
};
template<class Lambda, class Parameter, class Environment>
struct Evaluate<cons<Application,cons<Lambda,cons<Parameter,Nil>>>,Environment>{
	typedef typename Helpers_::Apply<
		typename Evaluate<Lambda,Environment>::value,
		typename Evaluate<Parameter,Environment>::value
	>::value value;
};

#undef Helpers_
#endif