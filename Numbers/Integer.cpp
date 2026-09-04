#ifndef TEMPLATE_INTEGERNUMBERS_
#define TEMPLATE_INTEGERNUMBERS_
#include "../Logic.cpp" // Must be up here, otherwise Natural:: adopts it
namespace Natural{
	#define BOOLCASTEDNATALT
	#include "Natural.cpp"
}
// See Turing.cpp
#define Helpers_ IntegerArithmeticTNUDEFBGPATPQBUUYSLRREVZSFYCD5XI

template<class Sign, class Natural> struct Int; // Sign=True -> Negative, Sign=False -> Positive; Natural = Natural::Nat<...>

template<class Int> struct AddOne;
template<class Int> struct SubtractOne;
template<class Int> struct Negate;
template<class Int1, class Int2> struct Equal;
template<class Int1, class Int2> struct GreaterThan;
template<class Int1, class Int2> struct LessThan;
template<class Int> struct Canonizer;
template<class Nat> struct Integrator;
template<class Int> struct Naturalizer;
// Later idk
template<class Int1, class Int2> struct BitwiseAnd;
template<class Int1, class Int2> struct BitwiseOr;
template<class Int1> struct BitwiseNot;
template<class Int1, class Int2> struct BitwiseXor;
//template<class Int, class ToShift> struct LeftShift;
//template<class Int, class ToShift> struct RightShift;

template<class Int1, class Int2> struct Add;
template<class Int1, class Int2> struct Multiply;
template<class Minuend, class Subtrahend> struct Subtract;
template<class Numerator, class Denominator> struct Divide;

/* Basics */

template<class... Bits>
struct CastToBool<Natural::Nat<False,Bits...>>{
	typedef typename CastToBool<Natural::Nat<Bits...>>::value value;
};
template<>
struct CastToBool<Natural::Nat<>>{
	typedef False value;
};

template<class Sign, class Nat>
struct AddOne<Int<Sign,Nat>>{
	typedef typename Ternary<Sign,
		Ternary<typename Natural::Equal<Nat,Natural::Nat<>>::value, // Might be zero
			Int<False,Natural::Nat<True>>, // When zero, just make one
			Int<True,typename Natural::SubtractOne<Nat>::value> // else get closer to zero
		>,
		Identity<Int<False,typename Natural::AddOne<Nat>::value>>
	>::value::value value;
};
template<class Sign, class Nat>
struct SubtractOne<Int<Sign,Nat>>{
	typedef typename Ternary<Sign,
		Identity<Int<True,typename Natural::AddOne<Nat>::value>>,
		Ternary<typename Natural::Equal<Nat,Natural::Nat<>>::value, // Might be zero
			Int<True,Natural::Nat<True>>,
			Int<False,typename Natural::SubtractOne<Nat>::value>
		>
	>::value::value value;
};
template<class Sign, class Nat>
struct Negate<Int<Sign,Nat>>{
	typedef Int<typename Not<Sign>::value,Nat> value;
};
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct Equal<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef typename Ternary<typename Xor<Sign1,Sign2>::value, // Are signs different?
		Ternary<typename Natural::Equal<Nat1,Natural::Nat<>>::value, // Are they zero?
			Natural::Equal<Nat2,Natural::Nat<>>,
			Identity<False>
		>,
		Identity<Natural::Equal<Nat1,Nat2>>
		>::value::value::value value;
};
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct GreaterThan<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef typename Ternary<typename Xor<Sign1,Sign2>::value, // Are signs different?
		Ternary<typename Natural::Equal<Nat1,Natural::Nat<>>::value, // Is Int1 zero?
			Ternary<Sign2,
				Natural::GreaterThan<Nat2,Natural::Nat<>>, // Int1 is zero, Int2 > Int1 -> Nat2 > 0
				Identity<False> // No negative is greater than zero. Not even -0
			>,
			// Int1 is not zero, and signs are different.
			//Ternary<Sign1,
			//	/* Negative case. Since Int1 is not zero, and Int2 is positive, always*/ False,
			//	/* Positive case. Since Int1 is not zero, and Int2 is negative, always*/ True
			//>
			// Collapses to
			Identity<Identity<Sign2>> // because last was Not<Sign1> and Sign2==Not<Sign1>
		>,
		Identity<Ternary<Sign1, // Same as Sign2
			Natural::GreaterThan<Nat2,Nat1>, // (-x)>(-y) -> y>x
			Natural::GreaterThan<Nat1,Nat2> // x>y -> x>y
		>>
	>::value::value::value::value value; // That's a lot of value from one function!
};
template<class Int1, class Int2> struct LessThan{
	// I am not going through that again.
	typedef typename GreaterThan<Int2,Int1>::value value;
};
template<class Sign, class Nat>
struct Canonizer<Int<Sign,Nat>>{
	typedef typename Ternary<typename Natural::Equal<Nat,Natural::Nat<>>::value,
		Int<False,Natural::Nat<>>,
		Int<Sign,typename Natural::Canonizer<Nat>::value>
	>::value value;
};

/* Bitwise */
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct BitwiseAnd<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef Int<typename And<Sign1,Sign2>::value, typename Natural::BitwiseAnd<Nat1,Nat2>::value> value;
};
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct BitwiseOr<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef Int<typename Or<Sign1,Sign2>::value, typename Natural::BitwiseOr<Nat1,Nat2>::value> value;
};
template<class Sign, class Nat>
struct BitwiseNot<Int<Sign,Nat>>{
	typedef Int<typename Not<Sign>::value, typename Natural::BitwiseNot<Nat>::value> value;
};
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct BitwiseXor<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef Int<typename Xor<Sign1,Sign2>::value, typename Natural::BitwiseXor<Nat1,Nat2>::value> value;
};

/* Arithmetic */
// Trivial!
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct Multiply<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef Int<typename Xor<Sign1,Sign2>::value,typename Natural::Multiply<Nat1,Nat2>::value> value;
};
template<class Sign1, class Nat1, class Sign2, class Nat2>
struct Divide<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef Int<typename Xor<Sign1,Sign2>::value,typename Natural::Divide<Nat1,Nat2>::value> value;
};

template<class Sign1, class Nat1, class Sign2, class Nat2>
struct Add<Int<Sign1,Nat1>,Int<Sign2,Nat2>>{
	typedef typename Ternary<typename Xor<Sign1,Sign2>::value,
		Ternary<Sign1,
			// Int1 is negative, Int2 is positive
			Ternary<typename Natural::GreaterThan<Nat1,Nat2>::value,
				// Int1 is more negative than Int2 is positive
				Int<True,typename Natural::Subtract<Nat1,Nat2>::value>,
				// Int2 is more positive than Int1 is negative
				Int<False,typename Natural::Subtract<Nat2,Nat1>::value>
			>,
			// Int1 is positive, Int2 is negative
			Ternary<typename Natural::GreaterThan<Nat1,Nat2>::value,
				// Int1 is more positive than Int2 is negative
				Int<False,typename Natural::Subtract<Nat1,Nat2>::value>,
				// Int2 is more negative than Int1 is positive
				Int<True,typename Natural::Subtract<Nat2,Nat1>::value>
			>
		>,
		Identity<Identity<Int<Sign1,typename Natural::Add<Nat1,Nat2>::value>>>
	>::value::value::value value;
};
template<class Int1, class Int2> struct Subtract{
	typedef typename Add<Int1,typename Negate<Int2>::value>::value value;
};

#define SINGLE_ARGUMENT_NATURALIZER(Function) template<class... Bits>\
struct Function<Natural::Nat<Bits...>>{\
	/* See below for why Natural:: is fine */\
	typedef typename Natural::Function<Natural::Nat<Bits...>>::value value;\
};

#define DOUBLE_ARGUMENT_NATURALIZER(Function) template<class Sign1, class Nat1, class... Bits2>\
struct Function<Int<Sign1,Nat1>,Natural::Nat<Bits2...>>{\
	typedef typename Function<Int<Sign1,Nat1>,Int<False,Natural::Nat<Bits2...>>>::value value;\
};\
template<class... Bits1, class Sign2, class Nat2>\
struct Function<Natural::Nat<Bits1...>,Int<Sign2,Nat2>>{\
	typedef typename Function<Int<False,Natural::Nat<Bits1...>>,Int<Sign2,Nat2>>::value value;\
};\
template<class... Bits1, class... Bits2>\
struct Function<Natural::Nat<Bits1...>,Natural::Nat<Bits2...>>{\
	/* Sending to Natural:: is fine because that's probably what the user wanted
	And it still works by the previous two integrations. */\
	typedef typename Natural::Function<Int<False,Natural::Nat<Bits1...>>,Int<False,Natural::Nat<Bits2...>>>::value value;\
};

SINGLE_ARGUMENT_NATURALIZER(AddOne)
SINGLE_ARGUMENT_NATURALIZER(SubtractOne)
SINGLE_ARGUMENT_NATURALIZER(Canonizer)
SINGLE_ARGUMENT_NATURALIZER(BitwiseNot)

DOUBLE_ARGUMENT_NATURALIZER(Equal)
DOUBLE_ARGUMENT_NATURALIZER(GreaterThan)
DOUBLE_ARGUMENT_NATURALIZER(LessThan)
DOUBLE_ARGUMENT_NATURALIZER(Add)
DOUBLE_ARGUMENT_NATURALIZER(Multiply)
DOUBLE_ARGUMENT_NATURALIZER(Subtract)
DOUBLE_ARGUMENT_NATURALIZER(Divide)
DOUBLE_ARGUMENT_NATURALIZER(BitwiseAnd)
DOUBLE_ARGUMENT_NATURALIZER(BitwiseOr)
DOUBLE_ARGUMENT_NATURALIZER(BitwiseXor)

template<class Sign, class Nat>
struct Integrator<Int<Sign,Nat>>{
	typedef Int<Sign,Nat> value;
};
template<class... Bits>
struct Integrator<Natural::Nat<Bits...>>{
	typedef Int<False,Natural::Nat<Bits...>> value;
};
template<class Sign, class Nat>
struct Naturalizer<Int<Sign,Nat>>{
	//typedef Nat value;
	typedef Ternary<Sign,
		Natural::Nat<>,
		Nat
	>::value value;
};
template<class... Bits>
struct Naturalizer<Natural::Nat<Bits...>>{
	typedef Natural::Nat<Bits...> value;
};

#undef Helpers_
#endif