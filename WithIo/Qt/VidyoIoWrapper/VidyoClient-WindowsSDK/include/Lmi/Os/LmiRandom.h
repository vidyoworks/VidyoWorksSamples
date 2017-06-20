/** {file:
      {name: LmiRandom.h}
      {description: Random number handling.}
      {copyright:
      	(c) 2006-2016 Vidyo, Inc.,
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

#ifndef LMI_RANDOM_H_
#define LMI_RANDOM_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiRandomVars.h>

LMI_BEGIN_EXTERN_C

/**
   {package visibility="public":
     {name: Random}
	 {parent: Os}
	 {include: Lmi/Os/LmiRandom.h}
	 {description: A source of high-quality random numbers.}
   }
*/

/**
   {function visibility="private":
     {name: LmiRandomInitialize}
	 {parent: Random}
	 {description: Initialize the LmiRandom random number generator package.}
	 {prototype: LmiBool LmiRandomInitialize(void)}
	 {return: LMI_TRUE on success, LMI_FALSE on failure.}
   }
*/
LmiBool LmiRandomInitialize(void);

/**
   {function visibility="private":
     {name: LmiRandomUninitialize}
	 {parent: Random}
	 {description: Uninitialize the LmiRandom random number generator package.}
	 {prototype: void LmiRandomUninitialize(void)}
   }
*/
void LmiRandomUninitialize(void);


/**
   {function visibility="private":
     {name: LmiRandomGetBytes}
	 {parent: Random}
	 {description: Get N bytes of high-quality random numbers.}
	 {prototype: LmiBool LmiRandomGetBytes(char* buf, LmiSizeT buflen)}
	 {parameter:
	   {name: buf}
	   {description: A buffer to fill with random bytes.}}
	 {parameter:
	   {name: buflen}
	   {description: The size of the buffer to fill with random bytes.}}
	 {return: LMI_TRUE on success, LMI_FALSE on failure.}
   }
*/
LmiBool LmiRandomGetBytes(char* buf, LmiSizeT buflen);


typedef struct
{
	LmiVariableSimulator base;
} LmiRandomSimulator;

LmiRandomSimulator *LmiRandomSimulatorConstruct(LmiRandomSimulator *sim);
void LmiRandomSimulatorDestruct(LmiRandomSimulator *sim);
LmiVariableSimulator *LmiRandomSimulatorGetBase(LmiRandomSimulator *sim);

/**
{function visibility="public":
	{name: LmiPseudoRandomSimulatorGetDefault}
	{parent: Random}
	{include: Lmi/Os/LmiRandom.h}
	{description: Returns an LmiVariableSimulator object that uses a pseudorandom source
		of random numbers. If higher-quality random numbers are required, use
		LmiRandomSimulatorGetDefault instead.}
	{prototype: LmiVariableSimulator *LmiPseudoRandomSimulatorGetDefault(void)}
	{return: The simulator object.}
	{note: The object returned does its own locking; it is safe to use it from
		multiple threads at once.}
}
*/
LmiVariableSimulator *LmiPseudoRandomSimulatorGetDefault(void);

/**
{function visibility="public":
	{name: LmiRandomSimulatorGetDefault}
	{parent: Random}
	{include: Lmi/Os/LmiRandom.h}
	{description: Returns an LmiVariableSimulator object that uses a cryptographically secure
		source of random numbers. This source may be slower than a pseudorandom source; if
		high-quality random numbers are not necessary, use LmiPseudoRandomSimulatorGetDefault instead.}
	{prototype: LmiVariableSimulator *LmiRandomSimulatorGetDefault(void)}
	{return: The simulator object.}
	{note: The object returned does its own locking; it is safe to use it from
		multiple threads at once.}
}
*/
LmiVariableSimulator *LmiRandomSimulatorGetDefault(void);

LMI_END_EXTERN_C

#endif /* LMI_RANDOM_H_ */
