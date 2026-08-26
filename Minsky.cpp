#ifndef TEMPLATE_MINSKYMACHINE_
#define TEMPLATE_MINSKYMACHINE_
#include "Numbers/Peano.cpp"
// See Turing.cpp
#define Helpers_ MinskyMachineW2RNUWRV0ENZ6429JA3YC3YINUPEDLEX

// Instruction actions
struct Increment{};
struct DecrementJump{};
struct ZeroOut{}; // Canonical, but rarely used.
struct UnconditionalJump{};
struct Halt{};
// Register Instructions
struct RRegister{};
struct SRegister{};

template<class RRegister, class SRegsiter> struct RegisterPair; // For ::Out
template<class RRegister, class SRegister> struct RegisterPair{
	typedef RRegister RegisterR;
	typedef SRegister RegisterS;
};

// Specialization is faster, but this allows inline definitions.
template<class Pointer, class Register, class Action, class JumpPointer> struct Instruction;
template<class... Instruction> struct Instructions;
template<class Pointer, class Instructions> struct Lookup;
template<class Pointer, class Register, class Action, class JumpPointer, class... OtherInstructions>
struct Lookup<Pointer,Instructions<Instruction<Instruction<Pointer,Register,Action,JumpPointer>,OtherInstructions...>>>{
	typedef Register Register;
	typedef Action Action;
	typedef JumpPointer JumpPointer;
};
template<class Pointer, class Instruction, class... OtherInstructions>
struct Lookup<Pointer,Instructions<Instruction,OtherInstructions...>>{
	typedef typename Lookup<Pointer,Instructions<OtherInstructions...>>::Register Register;
	typedef typename Lookup<Pointer,Instructions<OtherInstructions...>>::Action Action;
	typedef typename Lookup<Pointer,Instructions<OtherInstructions...>>::JumpPointer JumpPointer;
};

namespace Helpers_{
	template<
		class RRegister, class SRegister,
		class Instructions, class InstructionPointer,
		class ActionRegister, class Action, class JumpPointer
	> struct MachineStepper;
}

template<class Instructions, class RRegister, class SRegister, class InstructionPointer> struct MinskyMachine;
template<class Instructions, class RRegister, class SRegister, class Pointer> struct MinskyMachine{
	typedef RegisterPair<RRegister,SRegister> Out;
	typedef Lookup<Instructions,Pointer> Instruction;
	typedef typename Helpers_::MachineStepper<
		RRegister,SRegister,Instructions,Pointer,
		typename Instruction::Register,
		typename Instruction::Action,
		typename Instruction::JumpPointer
	>::Next Next;
};

namespace Helpers_{
	/* ZeroOut RRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		RRegister,ZeroOut,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			Zero, RegisterS,
			typename AddOne<Pointer>::value
		> Next;
	};
	/* ZeroOut SRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		SRegister,ZeroOut,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			RegisterR, Zero,
			typename AddOne<Pointer>::value
		> Next;
	};
	/* Increment RRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		RRegister,Increment,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			typename AddOne<RegisterR>::value, RegisterS,
			typename AddOne<Pointer>::value
		> Next;
	};
	/* Increment SRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		SRegister,Increment,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			RegisterR, typename AddOne<RegisterS>::value,
			typename AddOne<Pointer>::value
		> Next;
	};
	/* Decrement RRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		RRegister,DecrementJump,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			typename SubtractOne<RegisterR>::value, RegisterS,
			typename AddOne<Pointer>::value
		> Next;
	};
	template<
		class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		Zero,RegisterS,Instructions,Pointer,
		RRegister,DecrementJump,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			Zero, RegisterS,
			JumpPointer
		> Next;
	};
	/* Decrement SRegister */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		SRegister,DecrementJump,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			RegisterR, typename SubtractOne<RegisterS>::value,
			typename AddOne<Pointer>::value
		> Next;
	};
	template<
		class RegisterR, class Instructions, class Pointer,
		class JumpPointer
	> struct MachineStepper<
		RegisterR,Zero,Instructions,Pointer,
		SRegister,DecrementJump,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,
			RegisterR, Zero,
			JumpPointer
		> Next;
	};
	/* Unconditional Jump */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class Register, class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		Register,UnconditionalJump,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions, RegisterR, RegisterS,
			JumpPointer
		> Next;
	};
	/* Halt */
	template<
		class RegisterR, class RegisterS, class Instructions, class Pointer,
		class Register, class JumpPointer
	> struct MachineStepper<
		RegisterR,RegisterS,Instructions,Pointer,
		Register,Halt,JumpPointer
	>{
		typedef MinskyMachine<
			Instructions,RegisterR,RegisterS,Pointer
		> Next;
	};
}

#undef Helpers_
#endif