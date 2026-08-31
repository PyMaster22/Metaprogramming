#ifndef TEMPLATE_REGISTERMACHINE_
#define TEMPLATE_REGISTERMACHINE_
#include "../Numbers/Natural.cpp"
// See Turing.cpp
#define Helpers_ RegisterMachinePQRSE99TE1RI7WT23AFHBQWWQOKUBFKH

// Instructions
struct INC; // Increment
template<class JumpPointer> struct JZD; // Jump if zero; otherwise, decrement.
struct ZER; // Zero out
struct H; // Halt
//struct JMP;
template<class Identifier> struct Register;

// Arbitrary Registers
template<class Identifier, class Value> struct MemoryCell;
template<class... MemoryCells> struct Registers;
namespace Helpers_{
	template<class Memory1, class Memory2> struct JoinMemory;

	//template<class Identifier, class Memory> struct CreateRegister;
	template<class Identifier, class Memory> struct Increment;
	template<class Identifier, class Memory> struct TestIfZero;
	template<class Identifier, class Memory> struct Decrement;
	template<class Identifier, class Memory> struct ZeroOut;
}

template<class InstructionPointer, class Register_, class Instruction_> struct Instruction;
template<class... Instructions> struct Program;
namespace Helpers_{template<class InstructionPointer, class Program_> struct InstructionLookup;}

template<class ProgramCounter, class Program_, class Memory> struct MachineConfiguration;
namespace Helpers_{
	template<class InstructionPointer, class Register_, class Instruction_, class Program_, class Memory> struct MachineStepper;
}


template<class ProgramCounter, class Program_, class Memory> struct MachineConfiguration{
	typedef Memory Out;
	typedef typename Helpers_::MachineStepper<
		ProgramCounter,
		typename Helpers_::InstructionLookup<ProgramCounter,Program_>::Register,
		typename Helpers_::InstructionLookup<ProgramCounter,Program_>::Instruction,
		Program_,Memory
	>::Next Next;
};

namespace Helpers_{
	template<class... MemoryCells1, class... MemoryCells2>
	struct JoinMemory<Registers<MemoryCells1...>,Registers<MemoryCells2...>>{
		typedef Registers<MemoryCells1...,MemoryCells2...> value;
	};

	template<class Identifier>
	struct Increment<Identifier,Registers<>>{
		typedef Registers<MemoryCell<Identifier,Nat<True>>> value;
	};
	template<class Identifier, class Value, class... Rest>
	struct Increment<Identifier,Registers<MemoryCell<Identifier,Value>,Rest...>>{
		typedef Registers<MemoryCell<Identifier,typename AddOne<Value>::value>,Rest...> value;
	};
	template<class Identifier, class TopRegister, class... Rest>
	struct Increment<Identifier,Registers<TopRegister,Rest...>>{
		typedef typename JoinMemory<
			Registers<TopRegister>,
			typename Increment<Identifier,Registers<Rest...>>::value
		>::value value;
	};

	template<class Identifier>
	struct TestIfZero<Identifier,Registers<>>{
		typedef True value;
	};
	template<class Identifier, class Value, class... Rest>
	struct TestIfZero<Identifier,Registers<MemoryCell<Identifier,Value>,Rest...>>{
		typedef typename Equal<Value,Nat<>>::value value;
	};
	template<class Identifier, class TopRegister, class... Rest>
	struct TestIfZero<Identifier,Registers<TopRegister,Rest...>>{
		typedef typename TestIfZero<Identifier,Registers<Rest...>>::value value;
	};
	
	template<class Identifier>
	struct Decrement<Identifier,Registers<>>{
		typedef Registers<MemoryCell<Identifier,Nat<>>> value;
	};
	template<class Identifier, class Value, class... Rest>
	struct Decrement<Identifier,Registers<MemoryCell<Identifier,Value>,Rest...>>{
		typedef Registers<MemoryCell<Identifier,typename SubtractOne<Value>::value>,Rest...> value;
	};
	template<class Identifier, class TopRegister, class... Rest>
	struct Decrement<Identifier,Registers<TopRegister,Rest...>>{
		typedef typename JoinMemory<
			Registers<TopRegister>,
			typename Decrement<Identifier,Registers<Rest...>>::value
		>::value value;
	};

	template<class Identifier>
	struct ZeroOut<Identifier,Registers<>>{
		typedef Registers<MemoryCell<Identifier,Nat<>>> value;
	};
	template<class Identifier, class Value, class... Rest>
	struct ZeroOut<Identifier,Registers<MemoryCell<Identifier,Value>,Rest...>>{
		typedef Registers<MemoryCell<Identifier,Nat<>>,Rest...> value;
	};
	template<class Identifier, class TopRegister, class... Rest>
	struct ZeroOut<Identifier,Registers<TopRegister,Rest...>>{
		typedef typename JoinMemory<
			Registers<TopRegister>,
			typename ZeroOut<Identifier,Registers<Rest...>>::value
		>::value value;
	};

	template<class InstructionPointer>
	struct InstructionLookup<InstructionPointer,Program<>>{
		// Crash into the end of the program
	};
	template<class InstructionPointer, class Register_, class Instruction_, class... Rest>
	struct InstructionLookup<InstructionPointer,Program<Instruction<InstructionPointer,Register<Register_>,Instruction_>,Rest...>>{
		typedef Register_ Register;
		typedef Instruction_ Instruction;
	};
	template<class InstructionPointer, class TopInstruction, class... Rest>
	struct InstructionLookup<InstructionPointer,Program<TopInstruction,Rest...>>{
		typedef typename InstructionLookup<InstructionPointer,Program<Rest...>>::Register Register;
		typedef typename InstructionLookup<InstructionPointer,Program<Rest...>>::Instruction Instruction;
	};


	template<class InstructionPointer, class Register_, class Program_, class Memory>
	struct MachineStepper<InstructionPointer,Register_,INC,Program_,Memory>{
		typedef MachineConfiguration<
			typename AddOne<InstructionPointer>::value,
			Program_,
			typename Increment<Register_,Memory>::value
		> Next;
	};
	template<class InstructionPointer, class Register_, class JumpPointer, class Program_, class Memory>
	struct MachineStepper<InstructionPointer,Register_,JZD<JumpPointer>,Program_,Memory>{
		typedef MachineConfiguration<
			typename Ternary<typename TestIfZero<Register_,Memory>::value,
				Identity<JumpPointer>,
				AddOne<InstructionPointer>
			>::value::value,
			Program_,
			typename Decrement<Register_,Memory>::value
		> Next;
	};
	template<class InstructionPointer, class Register_, class Program_, class Memory>
	struct MachineStepper<InstructionPointer,Register_,ZER,Program_,Memory>{
		typedef MachineConfiguration<
			typename AddOne<InstructionPointer>::value,
			Program_,
			typename ZeroOut<Register_,Memory>::value
		> Next;
	};
	template<class InstructionPointer, class Register_, class Program_, class Memory>
	struct MachineStepper<InstructionPointer,Register_,H,Program_,Memory>{
		typedef MachineConfiguration<
			InstructionPointer,
			Program_,
			Memory
		> Next;
	};
}


/* Example
typedef Program<
	Instruction<Nat<>,Register<Nat<>>,INC>,
	Instruction<Nat<True>,Register<Nat<True>>,INC>,
	Instruction<Nat<False,True>,Register<Nat<False>>,JZD<Nat<False,False,True>>>, // technically diff register
	Instruction<Nat<True,True>,Register<Nat<>>,INC>,
	Instruction<Nat<False,False,True>,Register<Nat<>>,H>
> Prog;
MachineConfiguration<Nat<>,Prog,Regiters<>>::Next...::Out
-->
Registers<MemoryCell<Nat<>, Nat<True>>, MemoryCell<Nat<True>, Nat<True>>, MemoryCell<Nat<False>, Nat<>>>
*/

#undef Helpers_
#endif
