#ifndef ConvertingFromIntegerTypeToPeanoNumberalCurrently
	#define ConvertingFromIntegerTypeToPeanoNumberalCurrently
	#undef __BASE_LEVEL
	#include "../GetBaseLevel.c"
#endif

#if defined(InputNumber) && ((InputNumber) - (__INCLUDE_LEVEL__ - __BASE_LEVEL) > 0)
	Succ(
	#include __FILE__
	)
#else
	Zero
#endif

#if __INCLUDE_LEVEL__ == __BASE_LEVEL
	#undef __BASE_LEVEL
	#undef ConvertingFromIntegerTypeToPeanoNumberalCurrently
#endif