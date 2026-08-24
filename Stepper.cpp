#ifndef TEMPLATE_MACHINESTEPPER_
#define TEMPLATE_MACHINESTEPPER_

// Assumes ::Next and ::Out
template<class System, unsigned int Steps> struct MachineStepper;
template<class System, unsigned int Steps>
struct MachineStepper{
	typedef typename MachineStepper<
		typename System::Next,
		Steps-1
	>::value value;
};
template<class System>
struct MachineStepper<System,0>{
	typedef typename System::Out value;
};

#endif