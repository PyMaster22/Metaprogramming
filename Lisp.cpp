#ifndef TEMPLATE_LISPLANGUAGE_
#define TEMPLATE_LISPLANGUAGE_
#include "Logic.cpp"
// See Turing.cpp
#define Helpers_ LISPLanguageO6NARP7XDV6MZSP1H7I2HZSWPOOA7Z3O

struct Nil;
template<class car, class cdr> struct cons{
	typedef car CAR;
	typedef cdr CDR;
};
template<class Name> struct Symbol;

template<class Expression, class TrueCase, class FalseCase> struct If;
template<class Expression> struct Quote;
template<class Expression> struct Atom;
template<class Expression> struct Car;
template<class Expression> struct Cdr;

template<class Argument, class Expression> struct Lambda;
template<class Lambda, class Parameter> struct Application;

// Environment is CONS!
//template<class Name, class Value> struct Association;
//template<class... Associations> struct Environment;
template<class Parameter, class LambdaBody, class Environment> struct Closure;

template<class Expression, class Environment> struct Evaluate;

namespace Helpers_{
	template<class SymbolName, class Environment> struct SymbolLookup;
	template<class Closure, class Parameter> struct Apply;
	
	template<class Expression> struct IsAtom;
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
	template<class SymbolName>
	struct SymbolLookup<SymbolName,Nil>{
		typedef SymbolName value;
	};
	template<class SymbolName, class Value, class Rest>
	struct SymbolLookup<SymbolName,cons<cons<Symbol<SymbolName>,Value>,Rest>>{
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

	template<class Expression> struct IsAtom{
		typedef True value;
	};
	template<class CAR, class CDR>
	struct IsAtom<cons<CAR,CDR>>{
		typedef False value;
	};
}

template<class SymbolName, class Environment>
struct Evaluate<Symbol<SymbolName>,Environment>{
	typedef typename Helpers_::SymbolLookup<SymbolName,Environment>::value value;
};
template<class Expression, class TrueCase, class FalseCase, class Environment>
struct Evaluate<If<Expression,TrueCase,FalseCase>,Environment>{
	typedef typename Ternary<typename Evaluate<Expression,Environment>::value,
		Evaluate<TrueCase,Environment>,
		Evaluate<FalseCase,Environment>
	>::value::value value;
};
template<class Expression, class Environment>
struct Evaluate<Quote<Expression>,Environment>{
	typedef Expression value;
};
template<class Expression, class Environment>
struct Evaluate<Atom<Expression>,Environment>{
	typedef typename Helpers_::IsAtom<
		typename Evaluate<Expression,Environment>::value
	>::value value;
};
template<class Expression, class Environment>
struct Evaluate<Car<Expression>,Environment>{
	typedef typename Evaluate<Expression,Environment>::value::CAR value;
};
template<class Expression, class Environment>
struct Evaluate<Cdr<Expression>,Environment>{
	typedef typename Evaluate<Expression,Environment>::value::CDR value;
};

template<class Argument, class Expression, class Environment>
struct Evaluate<Lambda<Argument,Expression>,Environment>{
	typedef Closure<Argument,Expression,Environment> value;
};
template<class Lambda, class Parameter, class Environment>
struct Evaluate<Application<Lambda,Parameter>,Environment>{
	typedef typename Helpers_::Apply<
		typename Evaluate<Lambda,Environment>::value,
		typename Evaluate<Parameter,Environment>::value
	>::value value;
};
template<class ExpressionCAR, class ExpressionCDR, class Environment>
struct Evaluate<cons<ExpressionCAR,ExpressionCDR>,Environment>{
	typedef cons<
		typename Evaluate<ExpressionCAR,Environment>::value,
		typename Evaluate<ExpressionCDR,Environment>::value
	> value;
};

#undef Helpers_
#endif