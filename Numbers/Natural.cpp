#ifndef TEMPLATE_NATURALNUMBERS_
#define TEMPLATE_NATURALNUMBERS_
#include "../Logic.cpp"
// See Turing.cpp
#define Helpers_ NaturalNumbersTYWPF96Z8TU35RIKKFFDNT87HTPU57QZ

// Little endian because arbitrary precision and limitations of specialization
template<class... Bits> struct Nat;

namespace Helpers_{
	template<class Nat> struct NatNatToNat;
	template<class Bit, class... NatBits>
	struct NatNatToNat<Nat<Bit,Nat<NatBits...>>>{
		typedef Nat<Bit,NatBits...> value;
	};
}

/* Basics */
template<class Nat> struct AddOne;
template<class Nat> struct SubtractOne;
template<class Nat1, class Nat2> struct Equal;

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

/* Bitwise */
template<class Nat1, class Nat2> struct BitwiseAnd;
template<class Nat1, class Nat2> struct BitwiseOr;
template<class Nat1> struct BitwiseNot;
template<class Nat1, class Nat2> struct BitwiseXor;

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
	typedef Nat<> value;
};
template<class Nat2>
struct BitwiseOr<Nat<>,Nat2>{
	typedef Nat<> value;
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

/* Standard arithmetic */
template<class Nat1, class Nat2> struct Add;
template<class Nat1, class Nat2> struct Subtract;


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


#undef Helpers_
#endif