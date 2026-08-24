#ifndef TEMPLATE_MINSKYMACHINE_
#define TEMPLATE_MINSKYMACHINE_
#include "Peano.cpp"
// See Turing.cpp
#define Helpers_ MinskyMachineW2RNUWRV0ENZ6429JA3YC3YINUPEDLEX

// Instruction actions
struct Increment{};
struct DecrementJump{};
struct ZeroOut{}; // Canonical, but rarely used.
struct UnconditionalJump{};
struct Halt{};
// Register "symbols"
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

/* ZeroOut RRegister */
/* ZeroOut SRegister */
/* Increment RRegister */
/* Increment SRegister */
/* Decrement RRegister */
/* Decrement SRegister */
/* Unconditional Jump */
/* Halt */

#undef Helpers_
#endif