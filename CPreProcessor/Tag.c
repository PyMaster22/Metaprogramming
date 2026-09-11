#ifndef MACROMAGIC_POSTCYCLICTAGSYSTEM_
#define MACROMAGIC_POSTCYCLICTAGSYSTEM_
#include "Base.c"

#define JoinLists(x,y) Iff(HasArgs x,Iff(HasArgs y,(DeParen x,DeParen y),x),Iff(HasArgs y,y,()))
//#define RotateList(x) (DeParen DropFirstArgument x,FirstArgument x)
// Requires EVAL; Or
#define RotateList(x,...) (__VA_ARGS__,x)

#define CyclicTag(StringList,Productions) CyclicTag(\
	Iff(HasArgs FirstArgument Production,\
		Iff(HasArgs DropFirstArgument StringList,\
			JoinLists(DropFirstArgument StringList, Iff(FirstArgument StringList,FirstArgument Productions,())),\
			Iff(FirstArgument StringList,FirstArgument Productions,())\
		),\
		DropFirstArgument StringList\
	),\
	RotateList Productions\
)

// Example (line becomes next line):
//CyclicTag( (1),((1,1),(1,0),(0,0),(0,0)))
//CyclicTag( (1,1),((1,0),(0,0),(0,0),(1,1)))
//CyclicTag( (1,1,0),((0,0),(0,0),(1,1),(1,0)))
//CyclicTag( (1,0,0,0),((0,0),(1,1),(1,0),(0,0)))
//CyclicTag( (0,0,0,0,0),((1,1),(1,0),(0,0),(0,0)))
//CyclicTag( (0,0,0,0),((1,0),(0,0),(0,0),(1,1)))
//CyclicTag( (0,0,0),((0,0),(0,0),(1,1),(1,0)))
//CyclicTag( (0,0),((0,0),(1,1),(1,0),(0,0)))
//CyclicTag( (0),((1,1),(1,0),(0,0),(0,0)))
//CyclicTag( (),((1,0),(0,0),(0,0),(1,1))
// Error!
#endif