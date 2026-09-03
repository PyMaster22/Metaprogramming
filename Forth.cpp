#ifndef TEMPLATE_FORTHLANGUAGE_
#define TEMPLATE_FORTHLANGUAGE_
#include "Numbers/Integer.cpp" // Need negatives.
// Hacky afffff
#define Nat Natural::Nat
#include "Memory.cpp"
#undef Nat
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
/* Bitwise */
struct AND;
struct OR;
struct NOT;
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
/* Memory */
struct STORE;
struct FETCH;
// Use C macros? (i don't want more alists pleeeease)
//template<class Name> struct VARIABLE;
// Use C macros!
//template<class Name> struct CONSTANT;

template<class... Items> struct Stack;

template<class... IndexedWords> struct Program;

template<class Program, class Stack, class MachineMemory> struct ForthMachineConfiguration;


template<class Stack, class MachineMemory>
struct ForthMachineConfiguration<Program<>,Stack,MachineMemory>{
	typedef Stack Out;
	typedef MachineMemory MemoryDump; // idk where else this would belong
	typedef ForthMachineConfiguration<
		Program<>,
		Stack
	> Halted;
};
/* Stack manipulation */
// Literal
template<class IntSign, class IntMagnitude, class... Rest, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<Int<IntSign,IntMagnitude>,Rest...>,Stack<StackRest...>,MachineMemory>{
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Int<IntSign,IntMagnitude>,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<DUP,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack1,Stack1,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<SWAP,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack2,Stack1,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<DROP,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<OVER,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack1,Stack2,Stack1,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class Stack3, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<ROT,Rest...>,Stack<Stack1,Stack2,Stack3,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<Stack3,Stack1,Stack2,StackRest...>,
		MachineMemory
	>::Halted Halted;
};

/* Arithmetic */
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<ADD,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
			typename Add<Stack1,Stack2>::value
		,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<SUB,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
			typename Subtract<Stack1,Stack2>::value
		,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<MUL,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
			typename Multiply<Stack1,Stack2>::value
		,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<DIV,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
			typename Divide<Stack1,Stack2>::value
		,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
/* Bitwise */
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<AND,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<typename Helpers_::ForthCast<
			typename BitwiseAnd<Stack1,Stack2>::value
		>::value,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<OR,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<typename Helpers_::ForthCast<
			typename BitwiseOr<Stack1,Stack2>::value
		>::value,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<NOT,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<typename Helpers_::ForthCast<
			typename BitwiseNot<Stack1>::value
		>::value,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
/* Comparator */
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<EQ,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
		typename Helpers_::ForthCast<typename Equal<Stack1,Stack2>::value>::value
		,StackRest...>,
		MachineMemory
	>::Halted Halted;
};
/* Conditional */
template<class IfSoProgram, class IfFalseProgram, class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<IF<IfSoProgram,IfFalseProgram>,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		typename ForthMachineConfiguration<
			typename Ternary<typename Equal<Stack1,Int<False,Natural::Nat<>>>::value,
				IfFalseProgram,
				IfSoProgram
			>::value,
			Stack<StackRest...>
		>::Halted::Out,
		MachineMemory
	>::Halted Halted;
};
/* Loop */
template<class... LoopProgram, class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<LOOP<Program<LoopProgram...>>,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	// typedef Stack Out;
	typedef typename ForthMachineConfiguration<
		Program<Rest...>,
		typename ForthMachineConfiguration<
			typename Ternary<typename Equal<Stack1,Int<False,Natural::Nat<>>>::value,
				Program<>,
				Program<LoopProgram...,LOOP<Program<LoopProgram...>>>
			>::value,
			Stack<StackRest...>
		>::Halted::Out,
		MachineMemory
	>::Halted Halted;
};
/* Memory */
template<class... Rest, class Stack1, class Stack2, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<STORE,Rest...>,Stack<Stack1,Stack2,StackRest...>,MachineMemory>{
	typedef ForthMachineConfiguration<
		Program<Rest...>,
		Stack<StackRest...>,
		typename MemoryWrite<Naturalizer<Stack2>,Stack1,MachineMemory>::value
	>::Halted Halted;
};
template<class... Rest, class Stack1, class... StackRest, class MachineMemory>
struct ForthMachineConfiguration<Program<FETCH,Rest...>,Stack<Stack1,StackRest...>,MachineMemory>{
	typedef ForthMachineConfiguration<
		Program<Rest...>,
		Stack<
			typename MemoryRead<Stack1,MachineMemory>::value,
		StackRest...>,
		MachineMemory
	>::Halted Halted;
};


#undef Helpers_
#endif