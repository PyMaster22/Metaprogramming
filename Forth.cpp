#ifndef TEMPLATE_FORTHLANGUAGE_
#define TEMPLATE_FORTHLANGUAGE_
#include "Numbers/Integer.cpp" // Need negatives.
// See Turing.cpp
#define Helpers_ FORTHProgrammingFMF8CDPDXUZ1PVD3ZGZ08IA4773DDJHF

namespace Helpers_{
	template<class Bool> struct ForthCast;
	template<> struct ForthCast<False>{
		typedef Int<False,Natural::Nat<False>> value;
	};
	template<> struct ForthCast<True>{
		typedef Int<True,Natural::Nat<True>> value;
	};
}

/* Words */
/* Stack manipulation */
struct DUP;
struct SWAP;
struct DROP;
struct OVER;
struct ROT;
/* Arithmetic */
struct ADD;
struct SUB;
struct MUL;
struct DIV;
/* Comparison */
struct EQ;
/* New words */
// Use C macros!
//struct DEF;
//struct ENDEF;
/* Conditional */
// Equivalent to IF TrueProgram ELSE FalsePRogram THEN (next tokens)
template<class TrueProgram, class FalseProgram> struct IF;
/* Loops */
// Equivalent to DUP IF BEGIN LoopProgram UNTIL ELSE DROP THEN (next tokens)
// To get original behavior: LoopProgram,LOOP<LoopProgram>,...
template<class LoopProgram> struct LOOP;

template<class... Items> struct Stack;

template<class... IndexedWords> struct Program;

template<class Program, class Stack> struct ForthMachineConfiguration;


template<class Stack>
struct ForthMachineConfiguration<Program<>,Stack>{
	typedef Stack Out;
	typedef ForthMachineConfiguration<
		Program<>,
		Stack
	> Halted;
};
/* Stack manipulation */
// Literal
template<class IntSign, class IntMagnitude, class... Rest, class... StackRest>
struct ForthMachineConfiguration<Program<Int<IntSign,IntMagnitude>,Rest...>,Stack<StackRest...>>{
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Int<IntSign,IntMagnitude>,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest>
struct ForthMachineConfiguration<Program<DUP,Rest...>,Stack<Stack1,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack1,Stack1,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<SWAP,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack2,Stack1,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest>
struct ForthMachineConfiguration<Program<DROP,Rest...>,Stack<Stack1,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<OVER,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack1,Stack2,Stack1,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class Stack3, class... StackRest>
struct ForthMachineConfiguration<Program<ROT,Rest...>,Stack<Stack1,Stack2,Stack3,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack3,Stack1,Stack2,StackRest...>
	>::Halted Halted;
};

/* Arithmetic */
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<ADD,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Add<Stack1,Stack2>::value
		,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<SUB,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Subtract<Stack1,Stack2>::value
		,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<MUL,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Multiply<Stack1,Stack2>::value
		,StackRest...>
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<DIV,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Divide<Stack1,Stack2>::value
		,StackRest...>
	>::Halted Halted;
};
/* Comparator */
template<class... Rest, class Stack1, class Stack2, class... StackRest>
struct ForthMachineConfiguration<Program<EQ,Rest...>,Stack<Stack1,Stack2,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Helpers_::ForthCast<typename Equal<Stack1,Stack2>::value>::value
		,StackRest...>
	>::Halted Halted;
};
/* Conditional */
template<class IfSoProgram, class IfFalseProgram, class... Rest, class Stack1, class... StackRest>
struct ForthMachineConfiguration<Program<IF<IfSoProgram,IfFalseProgram>,Rest...>,Stack<Stack1,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		typename ForthMachineConfiguration<
			typename Ternary<typename Equal<Stack1,Int<False,Natural::Nat<>>>::value,
				IfFalseProgram,
				IfSoProgram
			>::value,
			Stack<StackRest...>
		>::Halted::Out
	>::Halted Halted;
};
/* Loop */
template<class... LoopProgram, class... Rest, class Stack1, class... StackRest>
struct ForthMachineConfiguration<Program<LOOP<Program<LoopProgram...>>,Rest...>,Stack<Stack1,StackRest...>>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		typename ForthMachineConfiguration<
			typename Ternary<typename Equal<Stack1,Int<False,Natural::Nat<>>>::value,
				Program<>,
				Program<LoopProgram...,LOOP<Program<LoopProgram...>>>
			>::value,
			Stack<StackRest...>
		>::Halted::Out
	>::Halted Halted;
};

#undef Helpers_
#endif