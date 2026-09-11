#ifndef MACROMAGIC_BASEFUNCTIONSTUFF_
#define MACROMAGIC_BASEFUNCTIONSTUFF_

#define EMPTY()
#define DEFER(Macro) Macro EMPTY()

#define EVAL1(...) Identity(Identity(Identity(Identity(Identity(Identity(Identity(Identity(Identity(Identity(__VA_ARGS__))))))))))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(EVAL1(__VA_ARGS__))))))))))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(EVAL2(__VA_ARGS__))))))))))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(EVAL3(__VA_ARGS__))))))))))
#define EVAL5(...) EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(EVAL4(__VA_ARGS__))))))))))
#define EVAL6(...) EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(EVAL5(__VA_ARGS__))))))))))
#define EVAL7(...) EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(EVAL6(__VA_ARGS__))))))))))
#define EVAL8(...) EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(EVAL7(__VA_ARGS__))))))))))
#define EVAL9(...) EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(EVAL8(__VA_ARGS__))))))))))
// If you need more than 10,000,000,000 expansions, you're probably doing something wrong...
// or not idk

#define EVAL(...) EVAL2(__VA_ARGS__)

#define DropFirstArgument(x,...) (__VA_ARGS__)
#define SecondArgument(x,...) FirstArgument(__VA_ARGS__,NULL)
// Generalized K Combinator
#define FirstArgument(x,...) x
#define Identity(...) __VA_ARGS__
// Technically (Identity(...)) but not because macro metaprogramming is weird
#define IdentityParens(...) (__VA_ARGS__)
// Same as Identity, but more obvious in purpose.
#define DeParen(...) __VA_ARGS__

#define GlueHelpers_ActualGlue(x,y) x ## y
#define Glue(x,y) GlueHelpers_ActualGlue(x,y)

#define IffHelpers_0(IfTrue,IfFalse) IfFalse
#define IffHelpers_1(IfTrue,IfFalse) IfTrue
#define IffHelpers_Iff2(Condition,IfTrue,IfFalse) Glue(IffHelpers_,Condition)(IfTrue, IfFalse)
#define IffHelpers_Iff(Condition,IfTrue,IfFalse) IffHelpers_Iff2(Condition,IfTrue,IfFalse)
#define Iff(Condition,IfTrue,IfFalse) EVAL(IffHelpers_Iff(Bool(EVAL(Condition)),EVAL(IfTrue),EVAL(IfFalse)))

#define IS_PROBE(...) SecondArgument(__VA_ARGS__,0)
#define PROBE() idk, 1

#define NotHelpers_0 PROBE()
#define Not(Bool) IS_PROBE(Glue(NotHelpers_,Bool))

#define Bool(Anything) Not(Not(Anything))

#define HasArgsHelpers_NoArgs() 0
#define HasArgs(...) Bool(FirstArgument(HasArgsHelpers_NoArgs __VA_ARGS__)())

#endif