#ifndef TEMPLATE_MEMORY_
#define TEMPLATE_MEMORY_
#include "Numbers/Natural.cpp"
// See Turing.cpp
#define Helpers_ MemoryArrayS14PAS40R9GQLQO4WR57F3OYJV3KL94F

// Nat<> -> Cell; Nat<False,...> -> FalseCells<Nat<...>>; Nat<True,...> -> TrueCells<Nat<...>> 
template<class Cell, class FalseCells, class TrueCells> struct Memory;
// should this be Helpers_::'d?
struct NULLMemory;

// OOP?!? In my functional language???
template<class Index, class MemoryObject> struct MemoryRead;
template<class Index, class Value, class MemoryObject> struct MemoryWrite;

namespace Helpers_{
	template<class CanonIndex, class MemoryObject> struct XMemoryLookup;
	template<class CanonIndex, class Value, class MemoryObject> struct XMemoryWriter;

	template<class Index>
	struct XMemoryLookup<Index,NULLMemory>{
		typedef NULLMemory value;
	};
	// Ternary search
	template<class Cell, class... Other>
	struct XMemoryLookup<Nat<>,Memory<Cell,Other...>>{
		typedef Cell value;
	};
	template<class... Bits, class Cell, class FalseCells, class TrueCells>
	struct XMemoryLookup<Nat<False,Bits...>,Memory<Cell,FalseCells,TrueCells>>{
		typedef typename XMemoryLookup<Nat<Bits...>,FalseCells>::value value;
	};
	template<class... Bits, class Cell, class FalseCells, class TrueCells>
	struct XMemoryLookup<Nat<True,Bits...>,Memory<Cell,FalseCells,TrueCells>>{
		typedef typename XMemoryLookup<Nat<Bits...>,TrueCells>::value value;
	};

	template<class Value>
	struct XMemoryWriter<Nat<>,Value,NULLMemory>{
		typedef Memory<Value,NULLMemory,NULLMemory> value;
	};
	template<class... Bits, class Value>
	struct XMemoryWriter<Nat<False,Bits...>,Value,NULLMemory>{
		typedef Memory<NULLMemory,typename XMemoryWriter<Nat<Bits...>,Value,NULLMemory>::value,NULLMemory> value;
	};
	template<class... Bits, class Value>
	struct XMemoryWriter<Nat<True,Bits...>,Value,NULLMemory>{
		typedef Memory<NULLMemory,NULLMemory,typename XMemoryWriter<Nat<Bits...>,Value,NULLMemory>::value> value;
	};
	template<class Value, class Cell, class FalseCells, class TrueCells>
	struct XMemoryWriter<Nat<>,Value,Memory<Cell,FalseCells,TrueCells>>{
		typedef Memory<Value,FalseCells,TrueCells> value;
	};
	template<class... Bits, class Value, class Cell, class FalseCells, class TrueCells>
	struct XMemoryWriter<Nat<False,Bits...>,Value,Memory<Cell,FalseCells,TrueCells>>{
		typedef Memory<Cell,typename XMemoryWriter<Nat<Bits...>,Value,FalseCells>::value,TrueCells> value;
	};
	template<class... Bits, class Value, class Cell, class FalseCells, class TrueCells>
	struct XMemoryWriter<Nat<True,Bits...>,Value,Memory<Cell,FalseCells,TrueCells>>{
		typedef Memory<Cell,FalseCells,typename XMemoryWriter<Nat<Bits...>,Value,TrueCells>::value> value;
	};
}

template<class Index, class MemoryObject>
struct MemoryRead{
	typedef typename Helpers_::XMemoryLookup<
		// I could be evil and not have the canonizer...
		typename Canonizer<Index>::value,
		MemoryObject
	>::value value;
};

template<class Index, class Value, class MemoryObject>
struct MemoryWrite{
	// functional programming be like:
	// You modified one value? Here's an entire copy of that
	// datastructure with that one modification!
	typedef typename Helpers_::XMemoryWriter<
		typename Canonizer<Index>::value,
		Value,
		MemoryObject
	>::value value;
	// I love it
};

#undef Helpers_
#endif