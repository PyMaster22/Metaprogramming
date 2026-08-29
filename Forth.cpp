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

template<class Program, class InstructionPointer, class Stack, class LoopStack> struct ForthMachineConfiguration;
namespace Helpers_{
	template<class Program, class Pointer, class Word, class Stack, class LoopStack> struct ForthMachineStepper;
}
template<class Program, class Pointer, class Stack, class LoopStack> struct ForthMachineConfiguration{
	typedef typename InstructionLookup<Pointer,Program>::value Word;
	typedef typename Helpers_::ForthMachineStepper<
		Program,Pointer,
		Word,
		Stack,LoopStack
	>::Next Next;
};

namespace Helpers_{
	/* Stack manipulation */
	template<class Program, class Pointer, class StackItem1, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,DUP,Stack<StackItem1,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItem1,StackItem1,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,SWAP,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItem2,StackItem1,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,DROP,Stack<StackItem1,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,OVER,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItem1,StackItem2,StackItem1,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class StackItem3, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,ROT,Stack<StackItem1,StackItem2,StackItem3,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<StackItem3,StackItem1,StackItem2,StackItems...>,
			LoopStack
		> Next;
	};

	/* Arithmetic */
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,ADD,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<typename Add<StackItem1,StackItem2>::value,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,SUB,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<typename Subtract<StackItem1,StackItem2>::value,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,MUL,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<typename Multiply<StackItem1,StackItem2>::value,StackItems...>,
			LoopStack
		> Next;
	};
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,DIV,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<typename Divide<StackItem1,StackItem2>::value,StackItems...>,
			LoopStack
		> Next;
	};
	
	/* Comparison */
	template<class Program, class Pointer, class StackItem1, class StackItem2, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,ADD,Stack<StackItem1,StackItem2,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			Program,Pointer,
			Stack<typename ForthCast<typename Equal<StackItem1,StackItem2>::value>::value,StackItems...>,
			LoopStack
		> Next;
	};

	/* Conditional */ // Need to add IF/ELSE/Neither flag
	template<class Program, class Pointer, class StackItem1, class... StackItems, class LoopStack>
	struct ForthMachineStepper<Program,Pointer,IF,Stack<StackItem1,StackItems...>,LoopStack>{
		typedef ForthMachineConfiguration<
			
		> Next;
	};
}


#undef Helpers_
#endif