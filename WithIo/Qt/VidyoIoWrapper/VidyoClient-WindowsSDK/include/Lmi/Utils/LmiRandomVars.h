/**
{file:
	{name: LmiRandomVars.h}
	{description: }
	{copyright:
		(c) 2010-2014 Vidyo, Inc.,
		433 Hackensack Avenue,
		Hackensack, NJ  07601.

		All rights reserved.

		The information contained herein is proprietary to Vidyo, Inc.
		and shall not be reproduced, copied (in whole or in part), adapted,
		modified, disseminated, transmitted, transcribed, stored in a retrieval
		system, or translated into any language in any form by any means
		without the express written consent of Vidyo, Inc.
		                  ***** CONFIDENTIAL *****
	}
}
*/
#ifndef LMI_RANDOMVARS_H
#define LMI_RANDOMVARS_H

#include <Lmi/Utils/LmiTypes.h>

LMI_BEGIN_EXTERN_C

struct LmiVariableSimulator_;
typedef void (*LmiVariableSimulatorPlugInGenerateBytesCallback)(struct LmiVariableSimulator_ *sim, void *buf, LmiSizeT length);

typedef struct
{
	LmiVariableSimulatorPlugInGenerateBytesCallback generateBytes;
} LmiVariableSimulatorPlugIn;

/**
{type visibility="public":
	{name: LmiVariableSimulator}
	{parent: Utils}
	{include: Lmi/Utils/LmiRandomVars.h}
	{description: An object that simulates random variables with various distributions. Separate instances of this class
		may each have their own source of random bits. These sources may differ in the quality of the random numbers
		and the time required to generate them.}
}
*/
typedef struct LmiVariableSimulator_
{
	LmiVariableSimulatorPlugIn *plugIn;
} LmiVariableSimulator;

/* protected: */
LMI_INLINE_DECLARATION LmiVariableSimulator *LmiVariableSimulatorConstructBase_(LmiVariableSimulator *sim, LmiVariableSimulatorPlugIn *plugIn);
LMI_INLINE_DECLARATION void LmiVariableSimulatorDestruct_(LmiVariableSimulator *sim);
LMI_INLINE_DECLARATION void LmiVariableSimulatorGenerateBytes_(LmiVariableSimulator *sim, void *buf, LmiSizeT length);

/**
{function visibility="public":
	{name: LmiVariableSimulatorGetDiscreteUniform}
	{parent: LmiVariableSimulator}
	{description: Simulate a discrete uniform variable. Each of the values between 0 and (n-1) inclusive
		are equally likely to be selected.}
	{prototype: LmiUint LmiVariableSimulatorGetDiscreteUniform(LmiVariableSimulator *sim, LmiUint n)}
	{parameter: {name: sim} {description: The simulator object.}}
	{parameter: {name: n} {description: The number of values to choose from.}}
	{return: The value selected.}
	{note: Returns 0 if there are no values to choose from because n is 0.}
}
*/
LmiUint LmiVariableSimulatorGetDiscreteUniform(LmiVariableSimulator *sim, LmiUint n);

/**
{function visibility="public":
	{name: LmiVariableSimulatorGetDiscreteUniformInRange}
	{parent: LmiVariableSimulator}
	{description: Simulate a discrete uniform variable. Each of the values between min_ and max_ inclusive
		are equally likely to be selected.}
	{prototype: LmiInt LmiVariableSimulatorGetDiscreteUniformInRange(LmiVariableSimulator *sim, LmiInt min_, LmiInt max_)}
	{parameter: {name: sim} {description: The simulator object.}}
	{parameter: {name: min_} {description: The minimum value in the range.}}
	{parameter: {name: max_} {description: The maximum value in the range.}}
	{return: The value selected.}
	{note: The behavior is undefined if min_ > max_.}
}
*/
LMI_INLINE_DECLARATION LmiInt LmiVariableSimulatorGetDiscreteUniformInRange(LmiVariableSimulator *sim, LmiInt min_, LmiInt max_);

/**
{function visibility="public":
	{name: LmiVariableSimulatorGetStandardUniform}
	{parent: LmiVariableSimulator}
	{description: Simulate a standard uniform variable. This is a continuous uniform variable over the range 0 to 1.}
	{prototype: LmiFloat64 LmiVariableSimulatorGetStandardUniform(LmiVariableSimulator *sim)}
	{parameter: {name: sim} {description: The simulator object.}}
	{return: The value selected.}
}
*/
LmiFloat64 LmiVariableSimulatorGetStandardUniform(LmiVariableSimulator *sim);

/**
{function visibility="public":
	{name: LmiVariableSimulatorGetUniform}
	{parent: LmiVariableSimulator}
	{description: Simulate a continuous uniform variable over a specified range.}
	{prototype: LmiFloat64 LmiVariableSimulatorGetUniform(LmiVariableSimulator *sim, LmiFloat64 min_, LmiFloat64 max_)}
	{parameter: {name: sim} {description: The simulator object.}}
	{parameter: {name: min_} {description: The minimum value in the range.}}
	{parameter: {name: max_} {description: The maximum value in the range.}}
	{return: The value selected.}
	{note: The behavior is undefined if min_ > max_.}
}
*/
LMI_INLINE_DECLARATION LmiFloat64 LmiVariableSimulatorGetUniform(LmiVariableSimulator *sim, LmiFloat64 min_, LmiFloat64 max_);

/**
{function visibility="public":
	{name: LmiVariableSimulatorGetExponential}
	{parent: LmiVariableSimulator}
	{description: Simulate a random variable with an exponential distribution. This distribution may be useful to model
		events that happen independently and with a constant average rate.}
	{prototype: LmiFloat64 LmiVariableSimulatorGetExponential(LmiVariableSimulator *sim, LmiFloat64 mean)}
	{parameter: {name: sim} {description: The simulator object.}}
	{parameter: {name: mean} {description: The mean of the distribution.}}
	{return: The value selected.}
	{note: The behavior is undefined if mean <= 0.}
}
*/
LmiFloat64 LmiVariableSimulatorGetExponential(LmiVariableSimulator *sim, LmiFloat64 mean);

#define LmiShuffle(Ran_, T_) LmiTemplate2(LmiShuffle, Ran_, T_)
#define Declare_LmiShuffle(Ran_, T_) \
	void LmiShuffle(Ran_, T_)(Ran_ b, Ran_ e, LmiVariableSimulator *sim);
#define Define_LmiShuffle(Ran_, T_) \
	void LmiShuffle(Ran_, T_)(Ran_ b, Ran_ e, LmiVariableSimulator *sim) \
	{ \
		LmiUint n = (LmiUint)LmiSubtract(Ran_)(&e, &b); \
		while(n > 1) \
		{ \
			LmiUint r = LmiVariableSimulatorGetDiscreteUniform(sim, n); \
			Ran_ p = LmiAdd(Ran_)(&b, r); \
			LmiDecrement(Ran_)(&e); \
			LmiSwap(T_)(LmiContentOf(Ran_)(&p), LmiContentOf(Ran_)(&e)); \
			--n; \
		} \
	}

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiRandomVarsInline.h>
#endif

#endif
