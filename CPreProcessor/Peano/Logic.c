#ifndef MACROMAGIC_PEANOLOGIC_
#define MACROMAGIC_PEANOLOGIC_
#include "../Base.c"

#define IffHelpers_Succ(x) FirstArgument DropFirstArgument(x
#define IffHelpers_Zero SecondArgument DropFirstArgument(NULL
#define IffHelper_Iff2(x,t,f) IffHelpers_ ## x, t, f)
#define IffHelper_Iff(x,t,f) IffHelper_Iff2(x,t,f)

#define Iff(x,t,f) EVAL(IffHelper_Iff(EVAL(x),EVAL(t),EVAL(f)))


#endif