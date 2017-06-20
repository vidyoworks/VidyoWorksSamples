/**
{file:
	{name: LmiPseudoRandom.h}
	{description: Object for Pseudo-Random Numbers.}
	{copyright:
		(c) 2008-2015 Vidyo, Inc.,
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
#ifndef LMI_PSEUDO_RANDOM_H_
#define LMI_PSEUDO_RANDOM_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiRandomVars.h>

LMI_BEGIN_EXTERN_C

/**
	{type visibility="private":
		{name: LmiPseudoRandomGenerator}
		{parent: Utils}
		{include: Lmi/Utils/LmiPseudoRandom.h}
		{description: A source of pseudo-random numbers.}
		{note: If cryptographically random numbers are needed, Random
			should be used instead.}
		{note: This is currently implemented as a linear congruential algorithm
			modeled after the POSIX function lrand48().}
	}
*/
typedef struct {
	LmiUint64 state;
} LmiPseudoRandomGenerator;

/**
	{function visibility="private":
		{name: LmiPseudoRandomGeneratorConstruct}
		{parent: LmiPseudoRandomGenerator}
		{description: Construct a new pseudo-random number generator.}
		{prototype: LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorConstruct(LmiPseudoRandomGenerator* r, LmiInt64 seed)}
		{parameter:
			{name: r}
			{description: The pseudo-random number generator to construct.}}
		{parameter:
			{name: seed}
			{description: The initial seed value to use for the generator.}}
		{return: r on success, NULL on failure.}
		{note: The type of the seed argument is chosen to be the same type as
			LmiTime, so pseudo-random number generators can conveniently be
			seeded with the current time.}
	}
*/
LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorConstruct(LmiPseudoRandomGenerator* r, LmiInt64 seed);

/**
	{function visibility="private":
		{name: LmiPseudoRandomGeneratorDestruct}
		{parent: LmiPseudoRandomGenerator}
		{description: Destruct a pseudo-random number generator.}
		{prototype: void LmiPseudoRandomGeneratorDestruct(LmiPseudoRandomGenerator* r)}
		{parameter:
			{name: r}
			{description: The pseudo-random generator to destruct.}}
	}
*/
void LmiPseudoRandomGeneratorDestruct(LmiPseudoRandomGenerator* r);


/**
	{function visibility="private":
		{name: LmiPseudoRandomGeneratorConstructCopy}
		{parent: LmiPseudoRandomGenerator}
		{description: Construct a pseudo-random number generator as a copy of an existing one.}
		{prototype: LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorConstructCopy(LmiPseudoRandomGenerator* r, const LmiPseudoRandomGenerator* orig)}
		{parameter:
			{name: r}
			{description: The pseudo-random number generator to construct.}}
		{parameter:
			{name: orig}
			{description: An existing pseudo-random generator to copy.}}
		{return: r on success, NULL on failure.}
		{note: The two pseudo-random number generators will generate the same sequence of numbers after the copy.}
	}
*/
LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorConstructCopy(LmiPseudoRandomGenerator* r, const LmiPseudoRandomGenerator* orig);

/**
	{function visibility="private":
		{name: LmiPseudoRandomGeneratorAssign}
		{parent: LmiPseudoRandomGenerator}
		{description: Assign a pseudo-random number generator as a copy of an existing one.}
		{prototype: LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorAssign(LmiPseudoRandomGenerator* r, const LmiPseudoRandomGenerator* orig)}
		{parameter:
			{name: r}
			{description: The pseudo-random number generator to assign.}}
		{parameter:
			{name: orig}
			{description: An existing pseudo-random generator to copy.}}
		{return: r on success, NULL on failure.}
		{note: The two pseudo-random number generators will generate the same sequence of numbers after the assignment.}
	}
*/
LmiPseudoRandomGenerator* LmiPseudoRandomGeneratorAssign(LmiPseudoRandomGenerator* r, const LmiPseudoRandomGenerator* orig);


/**
	{function visibility="private":
		{name: LmiPseudoRandomGeneratorGetUint32}
		{parent: LmiPseudoRandomGenerator}
		{description: Get a pseudo-random LmiUint32 from a pseudo-random number generator.}
		{prototype: LmiUint32 LmiPseudoRandomGeneratorGetUint32(LmiPseudoRandomGenerator* r)}
		{parameter:
			{name: r}
			{description: The pseudo-random number generator from which to get a random LmiUint32 value.}}
		{return: A pseudo-random integer in the range 0 - 2^32 - 1.}
	}
*/
LmiUint32 LmiPseudoRandomGeneratorGetUint32(LmiPseudoRandomGenerator* r);


typedef struct
{
	LmiVariableSimulator base;
	LmiPseudoRandomGenerator generator;
} LmiPseudoRandomSimulator;

LmiPseudoRandomSimulator *LmiPseudoRandomSimulatorConstruct(LmiPseudoRandomSimulator *sim, LmiInt64 seed);
void LmiPseudoRandomSimulatorDestruct(LmiPseudoRandomSimulator *sim);
LmiVariableSimulator *LmiPseudoRandomSimulatorGetBase(LmiPseudoRandomSimulator *sim);

LMI_END_EXTERN_C

#endif /* LMI_PSEUDO_RANDOM_H_ */
