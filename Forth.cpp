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
struct DUP{};
struct SWAP{};
struct DROP{};
struct OVER{};
struct ROT{};
/* Arithmetic */
struct ADD{};
struct SUB{};
struct MUL{};
struct DIV{};
/* Comparison */
struct EQ{};
/* New words */
//struct DEF{};
//struct ENDEF{};
/* Conditions */
struct IF{};
struct ELSE{};
struct THEN{};
/* Loops */
struct BEGIN{};
struct UNTIL{};

template<class... Items> struct Stack;
template<class... InstructionIndexes> struct LoopStack;
template<class Depth, class IFOrELSE> struct DepthIndexedIf; // needed cause nested loops
template<class... DepthIndexedIfsElses> struct IfStack;

namespace Helpers_{
	template<class IfStack, class IFOrELSE> struct AppendDeeperIf;

	template<class Depth, class IFOrELSE, class... Rest, class NewIFOrELSE>
	struct AppendDeeperIf<IfStack<DepthIndexedIf<Depth,IFOrELSE>,Rest...>,NewIFOrELSE>{
		typedef IfStack<DepthIndexedIf<typename AddOne<Depth>::value,NewIFOrELSE>,DepthIndexedIf<Depth,IFOrELSE>,Rest...> value;
	};
	template<class NewIFOrELSE>
	struct AppendDeeperIf<IfStack<>,NewIFOrELSE>{
		typedef IfStack<DepthIndexedIf<Int<False,Natural::Nat<>>,NewIFOrELSE>>
	};
}

template<class Index, class Word> struct IndexedWord; // needed cause loops
template<class... IndexedWords> struct Program;
template<class Index, class Program> struct InstructionLookup;

template<class Index, class Word, class... Rest>
struct InstructionLookup<Index,Program<IndexedWord<Index,Word>,Rest...>>{
	typedef Word value;
};
template<class Index, class TopIndexedWord, class... Rest>
struct InstructionLookup<Index,Program<TopIndexedWord,Rest...>>{
	typedef typename InstructionLookup<Index,Program<Rest...>>::value value;
};

template<class Program, class InstructionPointer, class Stack, class LoopStack, class IfStack> struct ForthMachineConfiguration;
namespace Helpers_{
	template<class Program, class Pointer, class Word, class Stack, class LoopStack, class IfStack> struct ForthMachineStepper;
}
template<class Program, class Pointer, class Stack, class LoopStack, class IfStack> struct ForthMachineConfiguration{
	typedef typename InstructionLookup<Pointer,Program>::value Word;
	typedef typename Helpers_::ForthMachineStepper<
		Program,Pointer,
		Word,
		Stack,LoopStack,IfStack
	>::Next Next;
};

namespace Helpers_{
	/* Stack manipulation */

	/* Arithmetic */
	
	/* Comparison */

	/* Conditional */
	template<class Program, class Pointer, class StackItem1, class... StackItems, class LoopStack, class... IfStackItems>
	struct ForthMachineStepper<Program,Pointer,IF,Stack<StackItem1,StackItems...>,LoopStack,IfStack<IfStackItems...>>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItems...>,
			LoopStack,
			IfStack<typename Ternary<typename Equal<StackItem1,Int<False,Natural::Nat<False>>>::value,
				ELSE, // Top of stack is zero, the only falsey value.
				IF
			>::value,IfStackItems...>
		> Next;
	};
}


#undef Helpers_
#endif