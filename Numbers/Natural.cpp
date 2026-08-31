#ifndef TEMPLATE_NATURALNUMBERS_
#define TEMPLATE_NATURALNUMBERS_
#include "../Logic.cpp"
// See Turing.cpp
#define Helpers_ NaturalNumbersTYWPF96Z8TU35RIKKFFDNT87HTPU57QZ

// Little endian because arbitrary precision and limitations of specialization
template<class... Bits> struct Nat;

template<class Nat> struct AddOne;
template<class Nat> struct SubtractOne;
template<class Nat1, class Nat2> struct Equal;
template<class Nat1, class Nat2> struct GreaterThan;
template<class Nat1, class Nat2> struct LessThan;

template<class Nat1, class Nat2> struct BitwiseAnd;
template<class Nat1, class Nat2> struct BitwiseOr;
template<class Nat1> struct BitwiseNot;
template<class Nat1, class Nat2> struct BitwiseXor;
template<class Nat, class ToShift> struct LeftShift;
template<class Nat, class ToShift> struct RightShift;

template<class Nat1, class Nat2> struct Add;
template<class Nat1, class Nat2> struct Multiply;
template<class Minuend, class Subtrahend> struct Subtract;
template<class Numerator, class Denominator> struct Divide;

namespace Helpers_{
	template<class Nat> struct NatNatToNat;
	template<class Nat> struct StripTrailingFalses;
	template<class Nat1, class Nat2> struct CheckEqualLength;
	template<class Nat1, class Nat2> struct CheckLongerThan;
	template<class Nat1> struct ReverseBits;
	template<class Nat1> struct BitLength;

	template<class Bit, class... NatBits>
	struct NatNatToNat<Nat<Bit,Nat<NatBits...>>>{
		typedef Nat<Bit,NatBits...> value;
	};
	template<class... NatBits, class Bit>
	struct NatNatToNat<Nat<Nat<NatBits...>,Bit>>{
		typedef Nat<NatBits...,Bit> value;
	};
	template<class Bit>
	struct NatNatToNat<Nat<Bit,Nat<False>>>{
		typedef Nat<Bit> value;
	};

	template<class Nat> struct StripTrailingFalses{
		typedef Nat value;
	};
	template<class Bit1, class... Bits>
	struct StripTrailingFalses<Nat<Bit1,Bits...>>{
		typedef typename NatNatToNat<Nat<
			Bit1,
			typename StripTrailingFalses<Nat<Bits...>>::value
		>>::value value;
	};

	template<class Bit1, class... Bits1, class Bit2, class... Bits2>
	struct CheckEqualLength<Nat<Bit1,Bits1...>,Nat<Bit2,Bits2...>>{
		typedef typename CheckEqualLength<Nat<Bits1...>,Nat<Bits2...>>::value value;
	};
	template<class... Bits1>
	struct CheckEqualLength<Nat<Bits1...>,Nat<>>{
		typedef False value;
	};
	template<class... Bits2>
	struct CheckEqualLength<Nat<>,Nat<Bits2...>>{
		typedef False value;
	};
	template<>
	struct CheckEqualLength<Nat<>,Nat<>>{
		typedef True value;
	};
	
	template<class Bit1, class... Bits1, class Bit2, class... Bits2>
	struct CheckLongerThan<Nat<Bit1,Bits1...>,Nat<Bit2,Bits2...>>{
		typedef typename CheckLongerThan<Nat<Bits1...>,Nat<Bits2...>>::value value;
	};
	template<class... Bits1>
	struct CheckLongerThan<Nat<Bits1...>,Nat<>>{
		typedef True value;
	};
	template<class... Bits2>
	struct CheckLongerThan<Nat<>,Nat<Bits2...>>{
		typedef False value;
	};
	template<>
	struct CheckLongerThan<Nat<>,Nat<>>{
		typedef False value;
	};

	template<class Nat>
	struct ReverseBits{
		typedef Nat value;
	};
	template<class Bit1, class... Bits>
	struct ReverseBits<Nat<Bit1,Bits...>>{
		typedef typename NatNatToNat<Nat<
			typename ReverseBits<Nat<Bits...>>::value,
			Bit1
		>>::value value;
	};

	template<> struct BitLength<Nat<>>{
		typedef Nat<> value;
	};
	template<class Bit1, class... Bits>
	struct BitLength<Nat<Bit1,Bits...>>{
		typedef typename AddOne<typename BitLength<Nat<Bits...>>::value>::value value;
	};
}

/* Basics */

template<> struct CastToBool<Nat<>>{
	typedef False value;
};
template<class... Bits> struct CastToBool<Nat<False,Bits...>>{
	typedef typename CastToBool<Nat<Bits...>>::value value;
};

template<> struct AddOne<Nat<>>{
	typedef Nat<True> value;
};
template<class... Bits>
struct AddOne<Nat<False,Bits...>>{
	typedef Nat<True,Bits...> value;
};
template<class... Bits>
struct AddOne<Nat<True,Bits...>>{
	typedef typename Helpers_::NatNatToNat<
		Nat<False,typename AddOne<Nat<Bits...>>::value>
	>::value value;
};

// SubtractOne<0> -> 0
template<> struct SubtractOne<Nat<>>{
	typedef Nat<> value;
};
template<class... Bits>
struct SubtractOne<Nat<False,Bits...>>{
	typedef typename Helpers_::NatNatToNat<
		Nat<True,typename SubtractOne<Nat<Bits...>>::value>
	>::value value;
};
template<class... Bits>
struct SubtractOne<Nat<True,Bits...>>{
	typedef Nat<False,Bits...> value;
};

template<class Nat1, class Nat2> struct Equal{
	typedef False value;
};
template<> struct Equal<Nat<>,Nat<>>{
	typedef True value;
};
template<class Bit1, class... Bits1, class... Bits2>
struct Equal<Nat<Bit1,Bits1...>,Nat<Bit1,Bits2...>>{
	typedef typename Equal<Nat<Bits1...>,Nat<Bits2...>>::value value;
};
template<class... Bits1>
struct Equal<Nat<False,Bits1...>,Nat<>>{
	typedef typename Equal<Nat<Bits1...>,Nat<>>::value value;
};
template<class... Bits2>
struct Equal<Nat<>,Nat<False,Bits2...>>{
	typedef typename Equal<Nat<>,Nat<Bits2...>>::value value;
};

namespace Helpers_{
	template<class ReversedNat1, class ReversedNat2> struct XGreaterThan;
	template<>
	struct XGreaterThan<Nat<>,Nat<>>{
		typedef False value;
	};
	template<class Nat1>
	struct XGreaterThan<Nat1,Nat<>>{
		typedef typename Not<typename Equal<Nat1,Nat<>>::value>::value value;
	};
	template<class Nat2>
	struct XGreaterThan<Nat<>,Nat2>{
		typedef typename Not<typename Equal<Nat2,Nat<>>::value>::value value;
	};
	template<class... Bits1, class... Bits2>
	struct XGreaterThan<Nat<False,Bits1...>,Nat<False,Bits2...>>{
		typedef typename XGreaterThan<Nat<Bits1...>,Nat<Bits2...>>::value value;
	};
	template<class... Bits1, class... Bits2>
	struct XGreaterThan<Nat<True,Bits1...>,Nat<False,Bits2...>>{
		typedef True value;
	};
	template<class... Bits1, class... Bits2>
	struct XGreaterThan<Nat<False,Bits1...>,Nat<True,Bits2...>>{
		typedef False value;
	};
	template<class... Bits1, class... Bits2>
	struct XGreaterThan<Nat<True,Bits1...>,Nat<True,Bits2...>>{
		typedef typename XGreaterThan<Nat<Bits1...>,Nat<Bits2...>>::value value;
	};
	/* // Further Ternary optimizations?
	template<class Input1, class Input2> struct GreaterThan_V{
		typedef typename GreaterThan<typename Input1::value, typename Input2::value>::value value;
	};
	*/
}

// Nat1 > Nat2
template<class Nat1, class Nat2> struct GreaterThan{
	typedef typename Ternary<typename Helpers_::CheckEqualLength<Nat1,Nat2>::value,
		Helpers_::XGreaterThan<
			typename Helpers_::ReverseBits<Nat1>::value,
			typename Helpers_::ReverseBits<Nat2>::value
		>,
		Helpers_::CheckLongerThan<
			typename Helpers_::StripTrailingFalses<Nat1>::value,
			typename Helpers_::StripTrailingFalses<Nat2>::value
	>>::value::value value;
};
// Nat1 < Nat2
template<class Nat1, class Nat2> struct LessThan{
	typedef typename Not<typename Or<
		typename GreaterThan<Nat1,Nat2>::value,
		typename Equal<Nat1,Nat2>::value
	>::value>::value value;
};

/* Bitwise */

template<class Nat1>
struct BitwiseAnd<Nat1,Nat<>>{
	typedef Nat<> value;
};
template<class Nat2>
struct BitwiseAnd<Nat<>,Nat2>{
	typedef Nat<> value;
};
template<> struct BitwiseAnd<Nat<>,Nat<>>{
	typedef Nat<> value;
};
template<class Bit1, class Bit2, class... Bits1, class... Bits2>
struct BitwiseAnd<Nat<Bit1,Bits1...>,Nat<Bit2,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		typename And<Bit1,Bit2>::value,
		typename BitwiseAnd<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};

template<class Nat1>
struct BitwiseOr<Nat1,Nat<>>{
	typedef Nat1 value;
};
template<class Nat2>
struct BitwiseOr<Nat<>,Nat2>{
	typedef Nat2 value;
};
template<> struct BitwiseOr<Nat<>,Nat<>>{
	typedef Nat<> value;
};
template<class Bit1, class Bit2, class... Bits1, class... Bits2>
struct BitwiseOr<Nat<Bit1,Bits1...>,Nat<Bit2,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		typename Or<Bit1,Bit2>::value,
		typename BitwiseOr<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};

template<> struct BitwiseNot<Nat<>>{
	typedef Nat<> value;
};
template<class Bit1, class... Bits>
struct BitwiseNot<Nat<Bit1,Bits...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		Not<Bit1>,
		typename BitwiseNot<Nat<Bits...>>::value
	>>::value value;
};

template<class Nat1>
struct BitwiseXor<Nat1,Nat<>>{
	typedef Nat<> value;
};
template<class Nat2>
struct BitwiseXor<Nat<>,Nat2>{
	typedef Nat<> value;
};
template<> struct BitwiseXor<Nat<>,Nat<>>{
	typedef Nat<> value;
};
template<class Bit1, class Bit2, class... Bits1, class... Bits2>
struct BitwiseXor<Nat<Bit1,Bits1...>,Nat<Bit2,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		typename Xor<Bit1,Bit2>::value,
		typename BitwiseXor<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};

template<class ToShift>
struct LeftShift<Nat<>,ToShift>{
	typedef Nat<> value;
};
template<class... Bits, class ToShift>
struct LeftShift<Nat<Bits...>,ToShift>{
	typedef typename Ternary<typename Equal<ToShift,Nat<>>::value,
		Identity<Nat<Bits...>>,
		LeftShift<Nat<False,Bits...>,typename SubtractOne<ToShift>::value>
	>::value::value value;
};
template<class ToShift>
struct RightShift<Nat<>,ToShift>{
	typedef Nat<> value;
};
template<class Bit1, class... Bits, class ToShift>
struct RightShift<Nat<Bit1,Bits...>,ToShift>{
	typedef typename Ternary<typename Equal<ToShift,Nat<>>::value,
		Identity<Nat<Bit1,Bits...>>,
		RightShift<Nat<Bits...>,typename SubtractOne<ToShift>::value>
	>::value::value value;
};


/* Standard arithmetic */

template<> struct Add<Nat<>,Nat<>>{
	typedef Nat<> value;
};
template<class Nat1> struct Add<Nat1,Nat<>>{
	typedef Nat1 value;
};
template<class Nat2> struct Add<Nat<>,Nat2>{
	typedef Nat2 value;
};
template<class... Bits1, class... Bits2>
struct Add<Nat<False,Bits1...>,Nat<False,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		False,
		typename Add<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};
template<class... Bits1, class... Bits2>
struct Add<Nat<True,Bits1...>,Nat<False,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		True,
		typename Add<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};
template<class... Bits1, class... Bits2>
struct Add<Nat<False,Bits1...>,Nat<True,Bits2...>>{
	typedef typename Helpers_::NatNatToNat<Nat<
		True,
		typename Add<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value value;
};
template<class... Bits1, class... Bits2>
struct Add<Nat<True,Bits1...>,Nat<True,Bits2...>>{
	typedef typename AddOne<typename AddOne<typename Helpers_::NatNatToNat<Nat<
		False,
		typename Add<Nat<Bits1...>,Nat<Bits2...>>::value
	>>::value>::value>::value value;
};

namespace Helpers_{
	template<class Nat1, class Nat2, class Accumulator> struct XMultiply;
	template<class Nat2, class A>
	struct XMultiply<Nat<>,Nat2,A>{
		typedef A value;
	};
	template<class... Bits1, class Nat2, class... ABits>
	struct XMultiply<Nat<False,Bits1...>,Nat2,Nat<ABits...>>{
		typedef typename Ternary<typename Equal<Nat<Bits1...>,Nat<>>::value,
			Identity<Nat<ABits...>>,
			XMultiply<Nat<Bits1...>,Nat2,Nat<False,ABits...>>
		>::value::value value;
	};
	template<class... Bits1, class Nat2, class... ABits>
	struct XMultiply<Nat<True,Bits1...>,Nat2,Nat<ABits...>>{
		typedef typename XMultiply<
			Nat<False,Bits1...>,
			Nat2,
			typename Add<Nat2,Nat<ABits...>>::value
		>::value value;
	};
}
template<class Nat1, class Nat2> struct Multiply{
	//typedef typename Helpers_::XMultiply<Nat1,Nat2,Nat<>>::value value;
	typedef typename Add<
		typename Ternary<typename Equal<Nat1,Nat<>>::value,Nat<>,Nat2>::value,
		typename Ternary<typename Equal<Nat1,Nat<>>::value,
			Identity<Nat<>>,
			Multiply<typename SubtractOne<Nat1>::value,Nat2>
		>::value::value
	>::value value;
};

namespace Helpers_{
	template<class Nat1, class Nat2> struct XSubtract;
	template<> struct XSubtract<Nat<>,Nat<>>{
		typedef Nat<> value;
	};
	template<class Nat1>
	struct XSubtract<Nat1,Nat<>>{
		typedef Nat1 value;
	};
	template<class Nat2>
	struct XSubtract<Nat<>,Nat2>{
		typedef Nat<> value;
	};
	template<class... Bits1, class... Bits2>
	struct XSubtract<Nat<False,Bits1...>,Nat<False,Bits2...>>{
		typedef typename NatNatToNat<Nat<
			False,
			typename XSubtract<Nat<Bits1...>,Nat<Bits2...>>::value
		>>::value value;
	};
	template<class... Bits1, class... Bits2>
	struct XSubtract<Nat<True,Bits1...>,Nat<False,Bits2...>>{
		typedef typename NatNatToNat<Nat<
			True,
			typename XSubtract<Nat<Bits1...>,Nat<Bits2...>>::value
		>>::value value;
	};
	template<class... Bits1, class... Bits2>
	struct XSubtract<Nat<False,Bits1...>,Nat<True,Bits2...>>{
		typedef typename SubtractOne<typename NatNatToNat<Nat<
			False,
			typename XSubtract<Nat<Bits1...>,Nat<Bits2...>>::value
		>>::value>::value value;
	};
	template<class... Bits1, class... Bits2>
	struct XSubtract<Nat<True,Bits1...>,Nat<True,Bits2...>>{
		typedef typename NatNatToNat<Nat<
			False,
			typename XSubtract<Nat<Bits1...>,Nat<Bits2...>>::value
		>>::value value;
	};
}
template<class Nat1, class Nat2>
struct Subtract{
	typedef typename Ternary<typename GreaterThan<Nat1,Nat2>::value,
		Ternary<typename Equal<Nat2,Nat<>>::value,
			Identity<Nat1>,
			Helpers_::XSubtract<Nat1,Nat2>
		>,Identity<Identity<Nat<>>>
	>::value::value::value value;
};

namespace Helpers_{
	template<class Numerator, class Denominator, class Quotient, class Remainder, class i> struct XDivide;
	template<class N, class D, class Q, class R, class i>
	struct XDivide{
		typedef typename Add<
			typename LeftShift<R,Nat<True>>::value,
			typename BitwiseAnd<typename RightShift<N,i>::value,Nat<True>>::value
		>::value NewR;
		typedef typename Not<typename LessThan<NewR,D>::value>::value ToQuotient;
		typedef typename Subtract<NewR,
			typename Ternary<ToQuotient,D,Nat<>>::value
		>::value FinalR;
		typedef typename BitwiseOr<Q,typename LeftShift<Nat<ToQuotient>,i>::value>::value FinalQ;
		typedef typename Ternary<typename Equal<i,Nat<>>::value,
			Identity<FinalQ>,
			XDivide<N,D,FinalQ,FinalR,typename SubtractOne<i>::value>
		>::value::value value;
	}; 
}
template<class Nat1, class Nat2> struct Divide{
	typedef typename Helpers_::XDivide<Nat1,Nat2,Nat<>,Nat<>,typename Helpers_::BitLength<Nat1>::value>::value value;
};


#undef Helpers_
#endif