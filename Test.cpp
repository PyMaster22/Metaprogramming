#include "Numbers/NaturalIntegration.cpp"
#include <iostream>

typedef IntToNat<3>::value Three;
typedef IntToNat<26>::value TwoSix;
typedef IntToNat<27>::value TwoSeven;
typedef IntToNat<28>::value TwoEight;


int main(){
	
	std::cout << NatToInt<Divide<TwoSix,Three>::value>::value << std::endl // 8
	<< NatToInt<Divide<TwoSeven,Three>::value>::value << std::endl        // 9
	<< NatToInt<Divide<TwoEight,Three>::value>::value << std::endl;      // 9

	return(0);
}