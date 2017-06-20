/**
   {file:
     {name: LmiRegex.h}
     {description: Functions to evaluate and parse regular expressions.}
     {copyright:
     	(c) 2011 Vidyo, Inc.,
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

#ifndef LMI_REGEX_H_
#define LMI_REGEX_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

typedef struct {
	LmiBool negate;
	LmiWideChar start;
	LmiWideChar end;
} LmiRegexRange;

typedef enum {
	LMI_REGEXATOMTYPE_Epsilon,
	LMI_REGEXATOMTYPE_CharVal,
	LMI_REGEXATOMTYPE_Any,
	LMI_REGEXATOMTYPE_Ranges
} LmiRegexAtomType;

typedef struct {
	LmiRegexAtomType type;
	/* Could use union here, but it's nice to be able to statically
	   initialize without needing designated initializers. */
	LmiWideChar charValue;
	LmiRegexRange* ranges;
	LmiSizeT numRanges;
} LmiRegexAtom;

typedef enum {
	LMI_REGEXTRANSITIONTYPE_Normal,
	LMI_REGEXTRANSITIONTYPE_BackCount,
	LMI_REGEXTRANSITIONTYPE_ForwardCount,
} LmiRegexTransitionType;

typedef struct {
	LmiRegexTransitionType type;
	LmiRegexAtom atom;
	LmiSizeT stateFrom;
	LmiSizeT stateTo;
	LmiInt countMin;
	LmiInt countMax; /* -1 == unbounded */
	LmiSizeT counterNum;
} LmiRegexTransition;

typedef enum {
	LMI_REGEXSTATETYPE_Start,
	LMI_REGEXSTATETYPE_Transition,
	LMI_REGEXSTATETYPE_Final
} LmiRegexStateType;

typedef struct {
	LmiSizeT stateNum;
	LmiRegexStateType type;
	LmiRegexTransition* transitions;
	LmiSizeT numTransitions;
} LmiRegexState;

/**
	{type visibility="private":
    	{name: LmiRegex}
		{parent: Utils}
		{include: Lmi/Utils/LmiRegex.h}
		{description: A compiled regular expression.}
	}
*/
typedef struct {
	LmiRegexState* states;
	LmiSizeT numStates;
	LmiSizeT numCounters;
	LmiAllocator* a;
} LmiRegex;

/**
	{function visibility="private":
		{name: LmiRegexConstruct}
		{parent: LmiRegex}
		{description: Compile a regular expression into an LmiRegex object.}
		{prototype: LmiRegex* LmiRegexConstruct(LmiRegex* r, const char* expression, LmiAllocator* a)}
		{parameter:
			{name: r}
			{description: The regular expression object into which to place the compiled expression.}}
		{parameter:
			{name: expression}
			{description: The expression to compile.}}
		{parameter:
			{name: a}
			{description: An allocator to use for dynamically-allocated parts of the regular expression.}}
		{return: The object on success, NULL on failure.}
	}
*/
LmiRegex* LmiRegexConstruct(LmiRegex* r, const char* expression, LmiAllocator* a);


/**
	{function visibility="private":
		{name: LmiRegexDestruct}
		{parent: LmiRegex}
		{description: Destruct a regular expression object.}
		{prototype: void LmiRegexDestruct(LmiRegex* r)}
		{parameter:
			{name: r}
			{description: The object to destruct.}}
	}
*/
void LmiRegexDestruct(LmiRegex* r);


/**
	{function visibility="private":
		{name: LmiRegexMatchExact}
		{parent: LmiRegex}
		{description: Test whether a given string is completely matched by a given regular expression object.}
		{prototype: LmiBool LmiRegexMatchExact(const LmiRegex* r, const char* string, LmiAllocator* a)}
		{parameter:
			{name: r}
			{description: The regular expression object to use to do the match.}}
		{parameter:
			{name: string}
			{description: The string against which to match the regular expression.}}
		{parameter:
			{name: a}
			{description: An allocator to use for dynamically-allocated memory needed during regular expression matching.}}
		{return: LMI_TRUE if the regular expression completely matches the string; LMI_FALSE otherwise, or on failure.}
	}
*/
LmiBool LmiRegexMatchExact(const LmiRegex* r, const char* string, LmiAllocator *a);

LMI_END_EXTERN_C

#endif /* LMI_REGEX_H_ */
