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
#define IdentityParens(...) (__VA_ARGS__)

#endif