#ifndef TEMPLATE_LAMBDACALCULUS_
#define TEMPLATE_LAMBDACALCULUS_
// See Turing.cpp
#define Helpers_ LambdaCalculusWVMC3IB7AX8HT514OTQY7XT7T7XX0ME2

template<class Name> struct Variable;
template<class Parameter, class Expression> struct Lambda;
template<class Lambda, class Argument> struct Application;

template<class Name, class Value> struct Association;
template<class... Associations> struct Environment;
template<class Parameter, class Lambda, class Environment> struct Closure;

template<class Lambda, class Environment> struct Evaluate;

namespace Helpers_{
	template<class Name, class Environment> struct Lookup;
	template<class Closure, class Parameter> struct Apply;

	template<class Environment1, class Environment2> struct JoinEnvironments;
	
	template<class... Associations1, class... Associations2>
	struct JoinEnvironments<Environment<Associations1...>,Environment<Associations2...>>{
		typedef Environment<Associations1...,Associations2...> value;
	};

	template<class Name, class Value, class... Rest>
	struct Lookup<Name,Environment<Association<Name,Value>,Rest...>>{
		typedef Value value;
	};
	template<class Name, class TopAssoc, class... Rest>
	struct Lookup<Name,Environment<TopAssoc,Rest...>>{
		typedef typename Lookup<Name,Environment<Rest...>>::value value;
	};

	template<class Parameter, class Value, class Expression, class Env>
	struct Apply<Closure<Parameter,Expression,Env>,Value>{
		typedef typename Evaluate<
			Expression,
			typename JoinEnvironments<
				Environment<Association<Parameter,Value>>,
				Env
			>::value
		>::value value;
	};
}

template<class VariableName, class Environment>
struct Evaluate<Variable<VariableName>,Environment>{
	typedef typename Helpers_::Lookup<VariableName,Environment>::value value;
};
template<class Parameter, class Expression, class Environment>
struct Evaluate<Lambda<Parameter,Expression>,Environment>{
	typedef Closure<Parameter,Expression,Environment> value;
};
template<class Function, class Argument, class Environment>
struct Evaluate<Application<Function,Argument>,Environment>{
	typedef typename Helpers_::Apply<
		typename Evaluate<Function,Environment>::value,
		typename Evaluate<Argument,Environment>::value
	>::value value;
};

#undef Helpers_
#endif