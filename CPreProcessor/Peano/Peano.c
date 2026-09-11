#ifndef MACROMAGIC_PEANOARITHMETIC_
#define MACROMAGIC_PEANOARITHMETIC_
#include "../Base.c"
#include "Logic.c"

#define AddHelpers_Succ(x) AddHelpers_SuccMover(x
#define AddHelpers_Zero SecondArgument(NULL
#define AddHelpers_SuccMover(x,y) DEFER(AddHelpers_Indirection)()(x,Succ(y))
#define AddHelpers_Indirection() AddHelpers_Add2
#define AddHelpers_Add2(x,y) AddHelpers_ ## x, y)
#define AddHelpers_Add(x,y) AddHelpers_Add2(x,y)

#define Add(x,y) EVAL(AddHelpers_Add(EVAL(x),EVAL(y)))


#define MultiplyHelpers_Succ(x) MultiplyHelpers_Adder(x
#define MultiplyHelpers_Zero SecondArgument(NULL
#define MultiplyHelpers_Adder(x,y,z) DEFER(MultiplyHelpers_Indirection)()(x,Add(y,z),z)
#define MultiplyHelpers_Indirection() MultiplyHelpers_Mult2
#define MultiplyHelpers_Mult2(x,y,z) MultiplyHelpers_ ## x, y, z)
#define MultiplyHelpers_Mult(x,y) MultiplyHelpers_Mult2(x,Zero,y)

// Broken past 1*y for whatever reason
#define Multiply(x,y) EVAL(MultiplyHelpers_Mult(EVAL(x),EVAL(y)))

#endif