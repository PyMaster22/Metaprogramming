#ifndef TEMPLATE_TURINGMACHINE_
#define TEMPLATE_TURINGMACHINE_
// Anon namespacing helpers doesn't actually work.
// This is required to prevent collisions.
// I.e. use random characters to create a unique-ish namespace.
#define Helpers_ S4YM0SUJ4VJQ5BWRD6CT1JCH0XPS2AGM

template<class... Symbols> struct Tape;
struct HaltState{}; // Definition required for specialization
struct Left{};
struct Right{};
struct Blank{}; // For when Tape is overrun in either direction

namespace Helpers_{
	template<class Tape1, class Tape2> struct MergeTapes;
	template<class Tape> struct ReverseTape;
	template<class TapeLeft, class Current, class TapeRight> struct ReadOut;

	template<class Symbol1, class... Symbols>
	struct ReverseTape<Tape<Symbol1,Symbols...>>{
		typedef typename MergeTapes<
			typename ReverseTape<Tape<Symbols...>>::value,
			Tape<Symbol1>
		>::value value;
	};
	template<> struct ReverseTape<Tape<>>{
		typedef Tape<> value;
	};

	template<class... Symbols1, class... Symbols2>
	struct MergeTapes<Tape<Symbols1...>,Tape<Symbols2...>>{
		typedef Tape<Symbols1...,Symbols2...> value;
	};

	template<class Left, class CurSymbol, class Right>
	struct ReadOut{
		typedef typename MergeTapes<
			typename MergeTapes<
				typename ReverseTape<Left>::value,
				Tape<CurSymbol>
			>::value,
			Right
		>::value value;
	};

	
	template<
	    class TapeLeft, class TapeRight,
	    class NewState, class NewSymbol, class Direction,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper;
}

template<
    class TapeLeft, class TapeCurrent, class TapeRight, 
    class State, template<class QState, class QSymbol> class StateDeltas
> struct MachineConfiguration;

template<
    class TapeLeft, class TapeCurrent, class TapeRight, 
    class State, template<class QState, class QSymbol> class StateDeltas
> struct MachineConfiguration{
	typedef typename Helpers_::ReadOut<TapeLeft,TapeCurrent,TapeRight>::value Out;
    typedef StateDeltas<State,TapeCurrent> delta;
    typedef typename delta::NewState newState;
    typedef typename delta::NewSymbol newSymbol;
    typedef typename delta::Direction direction;
    typedef typename Helpers_::MachineStepper<
        TapeLeft,TapeRight,
        newState,newSymbol,direction,
        StateDeltas
    >::Next Next;
};
/* If machine Halts */
template<
    class TapeLeft, class TapeCurrent, class TapeRight, 
    template<class QState, class QSymbol> class StateDeltas
> struct MachineConfiguration<TapeLeft,TapeCurrent,TapeRight,HaltState,StateDeltas>{
	typedef typename Helpers_::ReadOut<TapeLeft,TapeCurrent,TapeRight>::value Out;
    typedef MachineConfiguration<
        TapeLeft,TapeCurrent,TapeRight,
        HaltState,StateDeltas
    > Next;
};


namespace Helpers_{
	/* Write + move Left */
	template<
	    class LeftSymbol1, class... LeftSymbols, class... RightSymbols,
	    class NewState, class NewSymbol,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper<Tape<LeftSymbol1,LeftSymbols...>,Tape<RightSymbols...>,NewState,NewSymbol,Left,StateDeltas>{
	    typedef MachineConfiguration<
	        Tape<LeftSymbols...>,
	        LeftSymbol1,
	        Tape<NewSymbol,RightSymbols...>,
	        NewState,StateDeltas
	    > Next;
	};
	/* Write + move Right */
	template<
	    class... LeftSymbols, class RightSymbol1, class... RightSymbols,
	    class NewState, class NewSymbol,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper<Tape<LeftSymbols...>,Tape<RightSymbol1,RightSymbols...>,NewState,NewSymbol,Right,StateDeltas>{
	    typedef MachineConfiguration<
	        Tape<NewSymbol,LeftSymbols...>,
	        RightSymbol1,
	        Tape<RightSymbols...>,
	        NewState,StateDeltas
	    > Next;
	};
	/* Write + move Left; Left empty */
	template<
	    class... RightSymbols,
	    class NewState, class NewSymbol,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper<Tape<>,Tape<RightSymbols...>,NewState,NewSymbol,Left,StateDeltas>{
	    typedef MachineConfiguration<
	        Tape<>,
	        Blank,
	        Tape<NewSymbol,RightSymbols...>,
	        NewState,StateDeltas
	    > Next;
	};
	/* Write + move Right; Right empty */
	template<
	    class... LeftSymbols,
	    class NewState, class NewSymbol,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper<Tape<LeftSymbols...>,Tape<>,NewState,NewSymbol,Right,StateDeltas>{
	    typedef MachineConfiguration<
	        Tape<NewSymbol,LeftSymbols...>,
	        Blank,
	        Tape<>,
	        NewState,StateDeltas
	    > Next;
	};
}

#undef Helpers_
#endif
