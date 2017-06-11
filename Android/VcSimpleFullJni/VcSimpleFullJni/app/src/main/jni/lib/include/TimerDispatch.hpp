//
//  TimerDispatch.hpp
//  Vidyo Android Client 
//
//  Created by raz.galili 
//  Copyright 2010 Vidyo Inc. All rights reserved.
//
// Generalized timer interface
//
// Usage:
// for c: 
//		define function:
//		void myfunc() {/* your codee here */}
// 		 executeAfterDelay(myfunc, 0.05, "my func id"); //would execute your func in 0.05 seconds from time of call
// or create a func of type:
//		void myfuncWithParameter(void* param) {/* your codee here */}
// 		 executeAfterDelaywithData(myfuncWithParameter, &someDataStructure, 0.05, "my second func id"); //would execute your func in 0.05 seconds from time of call, passing address of data structure
//	for c++:
//	class yourClass{ 
//			anyType yourMemeberFunc(ParamType param) { //...
//				}
//	} instantiatedClass;
//	...
//	TD::executeAfterDelay(instantiatedClass, yourClass::yourMemeberFunc, 0.05, "different id"); ////would execute your member func in 0.05 seconds from time of call
//
// and if you want to cancel the timer call use:
//	cancelTimer("different id"); 
//


#ifndef __TimerDispatch_hpp__
#define __TimerDispatch_hpp__

#include "VidyoJniCommon.h"

#if defined(__cplusplus)
extern "C" {
#endif

//todo: add Construct
//todo: add Destruct

typedef void (*simpleVoidFunction)(void);
typedef void (*voidFunctionWithData)(void*);

//the foloowing are the C safe versions of the ap

//execute func() after delaySeconds of seconds
void executeAfterDelay(simpleVoidFunction func, double delaySeconds, const char *timerID);  

//execute func(data)) after delaySeconds of seconds 
void executeAfterDelaywithData(voidFunctionWithData func,void *data, double delaySeconds, const char *timerID); 

// cancel timer with timerID id. 
// if the timer function started executing, cancel would wait until it is done to come back
void cancelTimer(const char *timerID); 

#if defined(__cplusplus)
}
#endif

	
#if defined(__cplusplus)

// Helper functor class
// Let us hide the implementation of the call to the member function 
typedef struct _BaseFunctor
{
	virtual ~_BaseFunctor(){};
	virtual void operator()(){}
} BaseFunctor, *BaseFunctorPtr;

//generalized execution of pointers to functors
void executeAfterDelay(BaseFunctorPtr t, double delaySeconds, const char *timerID);


//the following are the C++  versions of the api
template<class T, typename TRetrun, typename TParam>
struct TD
{
	typedef TRetrun (T::*FuncType)() ;
	
	struct RealFunctor : public BaseFunctor
	{
		T &_t;
		FuncType _func;
		RealFunctor(T &t, FuncType func) :_t(t), _func(func){};
		virtual void operator()(){ ((_t).*(_func))(); }
	};

	static void executeAfterDelay(T &t, FuncType func, double delaySeconds, const char *timerID)
	{	
		::executeAfterDelay(static_cast<BaseFunctorPtr>( new TD<T,TRetrun,TParam>::RealFunctor(t,func) ), delaySeconds, timerID);
	}
};

#endif 



#endif //__TimerDispatch_hpp__


