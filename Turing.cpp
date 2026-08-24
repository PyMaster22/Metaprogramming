#ifndef TEMPLATE_TURINGMACHINE_
#define TEMPLATE_TURINGMACHINE_

template<class... Symbols> struct Tape;
struct HaltState{}; // Definition required for specialization
struct Left{};
struct Right{};
struct Blank{}; // For when Tape is overrun in either direction

template<
    class TapeLeft, class TapeCurrent, class TapeRight, 
    class State, template<class QState, class QSymbol> class StateDeltas
> struct MachineConfiguration;
// MachineStepper should not be used elsewhere. Hence, you may not.
namespace{
	template<
	    class TapeLeft, class TapeRight,
	    class NewState, class NewSymbol, class Direction,
	    template<class QState, class QSymbol> class StateDeltas
	> struct MachineStepper;
}

template<
    class TapeLeft, class TapeCurrent, class TapeRight, 
    class State, template<class QState, class QSymbol> class StateDeltas
> struct MachineConfiguration{
    typedef StateDeltas<State,TapeCurrent> delta;
    typedef typename delta::NewState newState;
    typedef typename delta::NewSymbol newSymbol;
    typedef typename delta::Direction direction;
    typedef typename MachineStepper<
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
    typedef MachineConfiguration<
        TapeLeft,TapeCurrent,TapeRight,
        HaltState,StateDeltas
    > Next;
};

// ditto
namespace{
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

#endif
