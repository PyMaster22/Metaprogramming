#ifndef TEMPLATE_PEANO_
#define TEMPLATE_PEANO_
// Called Peano because unary numbers
// See Turing.cpp
#define Helpers_ PeanoArithmeticYXJN05X2VQXI0U7Y5IVNKRFU0HBEP8BW

struct Zero{};
template<class Int> struct Succ;
template<class Int> struct Pred;

template<class Int> struct AddOne; // Nontrivial with Succ & Pred
template<> struct AddOne<Zero>{
	typedef Succ<Zero> value;
};
template<class Int> struct AddOne<Succ<Int>>{
	typedef Succ<Succ<Int>> value;
};
template<class Int> struct AddOne<Pred<Int>>{
	typedef Int value;
};
template<class Int> struct SubtractOne;
template<> struct SubtractOne<Zero>{
	typedef Pred<Zero> value;
};
template<class Int> struct SubtractOne<Succ<Int>>{
	typedef Int value;
};
template<class Int> struct SubtractOne<Pred<Int>>{
	typedef Pred<Pred<Int>> value;
};

template<class Int> struct Negate;
template<> struct Negate<Zero>{
	typedef Zero value;
};
template<class Int> struct Negate<Succ<Int>>{
	typedef Pred<typename Negate<Int>::value> value;
};
template<class Int> struct Negate<Pred<Int>>{
	typedef Succ<typename Negate<Int>::value> value;
};



// (Arithmetic: immediately implements booleans)
// Zero is false. All else is true. Succ<Zero> is canonical true.
/* Equality */
template<class Int1, class Int2> struct Equal;
template<class Int1, class Int2> struct Equal{
	typedef Zero value;
};
template<class Int1, class Int2 struct Equal<Succ<Int1>,Succ<Int2>>{
	typedef typename Equal<Int1,Int2>::value value;
};
template<class Int1, class Int2> struct Equal<Pred<Int1>,Pred<Int2>>{
	typedef typename Equal<Int1,Int2>::value value;
};
template<> struct Equal<Zero,Zero>{
	typedef Succ<Zero> value;
};

/* Greater than */
// Ordered; Int1>Int2
template<class Int1, class Int2> struct GreaterThan;
template<class Int1> struct GreaterThan<Succ<Int1>,Zero>{
	typedef Succ<Zero> value;
};
template<class Int1, class Int2> struct GreaterThan<Succ<Int1>,Pred<Int2>>{
	typedef Succ<Zero> value;
};
template<class Int1, class Int2> struct GreaterThan<Succ<Int1>,Succ<Int2>>{
	typedef typename GreaterThan<Int1,Int2>::value value;
};
template<class Int1, class Int2> struct GreaterThan<Pred<Int1>,Int2>{
	// (-x)>y -> (-y)>x
	typedef typename GreaterThan<
		typename Negate<Int2>::value,
		typename Negate<Pred<Int1>>::value
	>::value value;
};

/* Less than */
// x<y -> y>x
template<class Int1, class Int2> struct LessThan;
template<class Int1, class Int2> struct LessThan{
	typedef typename GreaterThan<Int2,Int1>::value value;
};

/* Addition */
template<class Int1, class Int2> struct Add;
template<class Int1>
struct Add<Int1,Zero>{
	typedef Int1 value;
};
template<class Int1, class Int2>
struct Add<Int1,Succ<Int2>>{
	typedef typename Add<typename AddOne<Int1>::value,Int2>::value value;
};
template<class Int1, class Int2>
struct Add<Int1,Pred<Int2>>{
	typedef typename Add<typename SubtractOne<Int1>::value,Int2>::value value;
};

/* Subtraction */
// Addition with extra step
// Not recommended due to being ordered.
template<class Int1, class Int2> struct Subtract;
template<class Int1, class Int2> struct Subtract{
	typedef typename Add<Int1,typename Negate<Int2>::value>::value value;
};


/* Multiplication */
// nontrivial
namespace Helpers_{
	template<class M, class N, class Accumulator> struct XMultiply;
	template<class M, class N, class A>
	struct XMultiply<M,Succ<N>,A>{
		typedef typename XMultiply<M,N,typename Add<M,A>::value>::value value;
	};
	struct XMultiply<M,Pred<N>,A>{
		typedef typename XMultiply<M,N,typename Add<M,A>::value>::value value;
	};
	template<class M, class A>
	struct XMultiply<M,Zero,A>{
		typedef A value;
	};
}
template<class M, class N> struct Multiply;
template<class M, class N> struct Multiply{
	typedef typename Helpers_::XMultiply<M,N,Zero>::value value;
};

/* Division */
// Far more difficult; procrastinating.

#undef Helpers_
#endif