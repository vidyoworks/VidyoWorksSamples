/**
{file:
	{name: LmiStringVector.h}
	{description: Contains definitions for a vector of strings.}
	{copyright:
		(c) 2007-2015 Vidyo, Inc.,
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

#ifndef LMI_STRINGVECTOR_H
#define LMI_STRINGVECTOR_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiString.h>

LMI_BEGIN_EXTERN_C

#define LmiStringVector				    LmiVector(LmiString)
#define LmiStringVectorSizeType		    LmiVectorSizeType(LmiString)
#define LmiStringVectorDifferenceType	LmiVectorDifferenceType(LmiString)
#define LmiStringVectorDestruct		    LmiVectorDestruct(LmiString)
#define LmiStringVectorConstructDefault	LmiVectorConstructDefault(LmiString)
#define LmiStringVectorConstructN		LmiVectorConstructN(LmiString)
#define LmiStringVectorConstructRange	LmiVectorConstructRange(LmiString)
#define LmiStringVectorConstructCopy	LmiVectorConstructCopy(LmiString)
#define LmiStringVectorAssign			LmiVectorAssign(LmiString)
#define LmiStringVectorSwap			    LmiVectorSwap(LmiString)
#define LmiStringVectorGetAllocator	    LmiVectorGetAllocator(LmiString)
#define LmiStringVectorBegin			LmiVectorBegin(LmiString)
#define LmiStringVectorBeginConst		LmiVectorBeginConst(LmiString)
#define LmiStringVectorEnd				LmiVectorEnd(LmiString)
#define LmiStringVectorEndConst		    LmiVectorEndConst(LmiString)
#define LmiStringVectorRBegin			LmiVectorRBegin(LmiString)
#define LmiStringVectorRBeginConst		LmiVectorRBeginConst(LmiString)
#define LmiStringVectorREnd			    LmiVectorREnd(LmiString)
#define LmiStringVectorREndConst		LmiVectorREndConst(LmiString)
#define LmiStringVectorSize			    LmiVectorSize(LmiString)
#define LmiStringVectorMaxSize			LmiVectorMaxSize(LmiString)
#define LmiStringVectorEmpty			LmiVectorEmpty(LmiString)
#define LmiStringVectorEqual			LmiVectorEqual(LmiString)
#define LmiStringVectorLess			    LmiVectorLess(LmiString)
#define LmiStringVectorAt				LmiVectorAt(LmiString)
#define LmiStringVectorAtConst			LmiVectorAtConst(LmiString)
#define LmiStringVectorFront			LmiVectorFront(LmiString)
#define LmiStringVectorFrontConst		LmiVectorFrontConst(LmiString)
#define LmiStringVectorBack			    LmiVectorBack(LmiString)
#define LmiStringVectorBackConst		LmiVectorBackConst(LmiString)
#define LmiStringVectorInsert			LmiVectorInsert(LmiString)
#define LmiStringVectorInsertN			LmiVectorInsertN(LmiString)
#define LmiStringVectorInsertRange		LmiVectorInsertRange(LmiString)
#define LmiStringVectorErase			LmiVectorErase(LmiString)
#define LmiStringVectorEraseRange		LmiVectorEraseRange(LmiString)
#define LmiStringVectorClear			LmiVectorClear(LmiString)
#define LmiStringVectorResize			LmiVectorResize(LmiString)
#define LmiStringVectorPushBack		    LmiVectorPushBack(LmiString)
#define LmiStringVectorPopBack			LmiVectorPopBack(LmiString)
#define LmiStringVectorCapacity		    LmiVectorCapacity(LmiString)
#define LmiStringVectorReserve			LmiVectorReserve(LmiString)
#define LmiStringVectorDump			    LmiVectorDump(LmiString)

#define LmiStringVectorIterator					LmiVectorIterator(LmiString)
#define LmiStringVectorIteratorValueType		LmiVectorIteratorValueType(LmiString)
#define LmiStringVectorIteratorPointer			LmiVectorIteratorPointer(LmiString)
#define LmiStringVectorIteratorDifferenceType	LmiVectorIteratorDifferenceType(LmiString)
#define LmiStringVectorIteratorConstructCopy	LmiVectorIteratorConstructCopy(LmiString)
#define LmiStringVectorIteratorConstructExceptional	LmiVectorIteratorConstructExceptional(LmiString)
#define LmiStringVectorIteratorDestruct			LmiVectorIteratorDestruct(LmiString)
#define LmiStringVectorIteratorAssign			LmiVectorIteratorAssign(LmiString)
#define LmiStringVectorIteratorSwap				LmiVectorIteratorSwap(LmiString)
#define LmiStringVectorIteratorEqual			LmiVectorIteratorEqual(LmiString)
#define LmiStringVectorIteratorLess				LmiVectorIteratorLess(LmiString)
#define LmiStringVectorIteratorContentOf		LmiVectorIteratorContentOf(LmiString)
#define LmiStringVectorIteratorContentOfConst	LmiVectorIteratorContentOfConst(LmiString)
#define LmiStringVectorIteratorIncrement		LmiVectorIteratorIncrement(LmiString)
#define LmiStringVectorIteratorDecrement		LmiVectorIteratorDecrement(LmiString)
#define LmiStringVectorIteratorIncrementN		LmiVectorIteratorIncrementN(LmiString)
#define LmiStringVectorIteratorDecrementN		LmiVectorIteratorDecrementN(LmiString)
#define LmiStringVectorIteratorAt				LmiVectorIteratorAt(LmiString)
#define LmiStringVectorIteratorAdd				LmiVectorIteratorAdd(LmiString)
#define LmiStringVectorIteratorSubtract			LmiVectorIteratorSubtract(LmiString)
#define LmiStringVectorIteratorIsExceptional	LmiVectorIteratorIsExceptional(LmiString)

#define LmiStringVectorConstIterator				LmiVectorConstIterator(LmiString)
#define LmiStringVectorConstIteratorValueType		LmiVectorConstIteratorValueType(LmiString)
#define LmiStringVectorConstIteratorPointer			LmiVectorConstIteratorPointer(LmiString)
#define LmiStringVectorConstIteratorDifferenceType	LmiVectorConstIteratorDifferenceType(LmiString)
#define LmiStringVectorConstIteratorConstructCopy	LmiVectorConstIteratorConstructCopy(LmiString)
#define LmiStringVectorConstIteratorConstructExceptional	LmiVectorConstIteratorConstructExceptional(LmiString)
#define LmiStringVectorConstIteratorDestruct		LmiVectorConstIteratorDestruct(LmiString)
#define LmiStringVectorConstIteratorAssign			LmiVectorConstIteratorAssign(LmiString)
#define LmiStringVectorConstIteratorSwap			LmiVectorConstIteratorSwap(LmiString)
#define LmiStringVectorConstIteratorEqual			LmiVectorConstIteratorEqual(LmiString)
#define LmiStringVectorConstIteratorLess			LmiVectorConstIteratorLess(LmiString)
#define LmiStringVectorConstIteratorContentOf		LmiVectorConstIteratorContentOf(LmiString)
#define LmiStringVectorConstIteratorContentOfConst	LmiVectorConstIteratorContentOfConst(LmiString)
#define LmiStringVectorConstIteratorIncrement		LmiVectorConstIteratorIncrement(LmiString)
#define LmiStringVectorConstIteratorDecrement		LmiVectorConstIteratorDecrement(LmiString)
#define LmiStringVectorConstIteratorIncrementN		LmiVectorConstIteratorIncrementN(LmiString)
#define LmiStringVectorConstIteratorDecrementN		LmiVectorConstIteratorDecrementN(LmiString)
#define LmiStringVectorConstIteratorAt				LmiVectorConstIteratorAt(LmiString)
#define LmiStringVectorConstIteratorAdd				LmiVectorConstIteratorAdd(LmiString)
#define LmiStringVectorConstIteratorSubtract		LmiVectorConstIteratorSubtract(LmiString)
#define LmiStringVectorConstIteratorIsExceptional	LmiVectorConstIteratorIsExceptional(LmiString)

#define LmiStringVectorReverseIterator					LmiVectorReverseIterator(LmiString)
#define LmiStringVectorReverseIteratorValueType			LmiVectorReverseIteratorValueType(LmiString)
#define LmiStringVectorReverseIteratorPointer			LmiVectorReverseIteratorPointer(LmiString)
#define LmiStringVectorReverseIteratorDifferenceType	LmiVectorReverseIteratorDifferenceType(LmiString)
#define LmiStringVectorReverseIteratorConstructCopy		LmiVectorReverseIteratorConstructCopy(LmiString)
#define LmiStringVectorReverseIteratorConstructExceptional	LmiVectorReverseIteratorConstructExceptional(LmiString)
#define LmiStringVectorReverseIteratorDestruct			LmiVectorReverseIteratorDestruct(LmiString)
#define LmiStringVectorReverseIteratorAssign			LmiVectorReverseIteratorAssign(LmiString)
#define LmiStringVectorReverseIteratorSwap				LmiVectorReverseIteratorSwap(LmiString)
#define LmiStringVectorReverseIteratorEqual				LmiVectorReverseIteratorEqual(LmiString)
#define LmiStringVectorReverseIteratorLess				LmiVectorReverseIteratorLess(LmiString)
#define LmiStringVectorReverseIteratorContentOf			LmiVectorReverseIteratorContentOf(LmiString)
#define LmiStringVectorReverseIteratorContentOfConst	LmiVectorReverseIteratorContentOfConst(LmiString)
#define LmiStringVectorReverseIteratorIncrement		    LmiVectorReverseIteratorIncrement(LmiString)
#define LmiStringVectorReverseIteratorDecrement		    LmiVectorReverseIteratorDecrement(LmiString)
#define LmiStringVectorReverseIteratorIncrementN		LmiVectorReverseIteratorIncrementN(LmiString)
#define LmiStringVectorReverseIteratorDecrementN		LmiVectorReverseIteratorDecrementN(LmiString)
#define LmiStringVectorReverseIteratorAt				LmiVectorReverseIteratorAt(LmiString)
#define LmiStringVectorReverseIteratorAdd				LmiVectorReverseIteratorAdd(LmiString)
#define LmiStringVectorReverseIteratorSubtract			LmiVectorReverseIteratorSubtract(LmiString)
#define LmiStringVectorReverseIteratorIsExceptional	    LmiVectorReverseIteratorIsExceptional(LmiString)

#define LmiStringVectorConstReverseIterator				    LmiVectorConstReverseIterator(LmiString)
#define LmiStringVectorConstReverseIteratorValueType		LmiVectorConstReverseIteratorValueType(LmiString)
#define LmiStringVectorConstReverseIteratorPointer			LmiVectorConstReverseIteratorPointer(LmiString)
#define LmiStringVectorConstReverseIteratorDifferenceType	LmiVectorConstReverseIteratorDifferenceType(LmiString)
#define LmiStringVectorConstReverseIteratorConstructCopy	LmiVectorConstReverseIteratorConstructCopy(LmiString)
#define LmiStringVectorConstReverseIteratorConstructExceptional	LmiVectorConstReverseIteratorConstructExceptional(LmiString)
#define LmiStringVectorConstReverseIteratorDestruct		    LmiVectorConstReverseIteratorDestruct(LmiString)
#define LmiStringVectorConstReverseIteratorAssign			LmiVectorConstReverseIteratorAssign(LmiString)
#define LmiStringVectorConstReverseIteratorSwap			    LmiVectorConstReverseIteratorSwap(LmiString)
#define LmiStringVectorConstReverseIteratorEqual			LmiVectorConstReverseIteratorEqual(LmiString)
#define LmiStringVectorConstReverseIteratorLess			    LmiVectorConstReverseIteratorLess(LmiString)
#define LmiStringVectorConstReverseIteratorContentOf		LmiVectorConstReverseIteratorContentOf(LmiString)
#define LmiStringVectorConstReverseIteratorContentOfConst	LmiVectorConstReverseIteratorContentOfConst(LmiString)
#define LmiStringVectorConstReverseIteratorIncrement		LmiVectorConstReverseIteratorIncrement(LmiString)
#define LmiStringVectorConstReverseIteratorDecrement		LmiVectorConstReverseIteratorDecrement(LmiString)
#define LmiStringVectorConstReverseIteratorIncrementN		LmiVectorConstReverseIteratorIncrementN(LmiString)
#define LmiStringVectorConstReverseIteratorDecrementN		LmiVectorConstReverseIteratorDecrementN(LmiString)
#define LmiStringVectorConstReverseIteratorAt				LmiVectorConstReverseIteratorAt(LmiString)
#define LmiStringVectorConstReverseIteratorAdd				LmiVectorConstReverseIteratorAdd(LmiString)
#define LmiStringVectorConstReverseIteratorSubtract		    LmiVectorConstReverseIteratorSubtract(LmiString)
#define LmiStringVectorConstReverseIteratorIsExceptional	LmiVectorConstReverseIteratorIsExceptional(LmiString)


/**
   {type visibility="public":
     {name: LmiStringVector}
     {parent: Containers}
     {include: Lmi/Utils/LmiStringVector.h}
     {description: LmiStringVector is an instantiation of LmiVector over
       LmiString.}
     {note: See LmiVector, and the STL std::vector template, for descriptions
       of LmiStringVector\'s member functions.}
   }
*/

Declare_LmiVector(LmiString)
Declare_LmiVectorEqual(LmiString)
Declare_LmiVectorLess(LmiString)

/**
{function visibility="public":
	{name: LmiStringVectorAdd}
	{parent: LmiStringVector}
	{description: To add an element to an LmiStringVector object. Optionally, check for uniqueness while adding.}
	{prototype: LmiBool LmiStringVectorAdd(LmiStringVector* v, const LmiString* s, LmiBool checkForDuplicates)}
	{parameter: 
		{name: v}
		{description: The LmiStringVector object.}
	}
	{parameter: 
		{name: s}
		{description: The LmiString object that is to be added to the vector.}
	}
	{parameter: 
		{name: checkForDuplicates}
		{description: If set to LMI_TRUE, s is not added if it is already present in the vector.}
	}
	{return: LMI_TRUE if the operation was successful; LMI_FALSE, otherwise.}
}
*/
LmiBool LmiStringVectorAdd(LmiStringVector* v, const LmiString* s, LmiBool checkForDuplicates);

/**
{function visibility="public":
	{name: LmiStringVectorAddCStr}
	{parent: LmiStringVector}
	{description: To add an element in C-string format to an LmiStringVector object. Optionally, check for uniqueness while adding.}
	{prototype: LmiBool LmiStringVectorAddCStr(LmiStringVector* v, const char* s, LmiBool checkForDuplicates)}
	{parameter: 
		{name: v}
		{description: The LmiStringVector object.}
	}
	{parameter: 
		{name: s}
		{description: The C-string object that is to be added to the vector.}
	}
	{parameter: 
		{name: checkForDuplicates}
		{description: If set to LMI_TRUE, s is not added if it is already present in the vector.}
	}
	{return: LMI_TRUE if the operation was successful; LMI_FALSE, otherwise.}
}
*/
LmiBool LmiStringVectorAddCStr(LmiStringVector* v, const char* s, LmiBool checkForDuplicates);

/**
{function visibility="public":
	{name: LmiStringVectorRemove}
	{parent: LmiStringVector}
	{description: To remove an element from an LmiStringVector object.}
	{prototype: LmiBool LmiStringVectorRemove(LmiStringVector* v, const LmiString* s)}
	{parameter: 
		{name: v}
		{description: The LmiStringVector object.}
	}
	{parameter: 
		{name: s}
		{description: The element to be removed.}
	}
	{return: LMI_TRUE if the operation was successful; LMI_FALSE, otherwise.}
}
*/
LmiBool LmiStringVectorRemove(LmiStringVector* v, const LmiString* s);

/**
{function visibility="public":
	{name: LmiStringVectorRemoveCStr}
	{parent: LmiStringVector}
	{description: To remove an element (specified as a C-string) from an LmiStringVector object.}
	{prototype: LmiBool LmiStringVectorRemoveCStr(LmiStringVector* v, const char* s)}
	{parameter: 
		{name: v}
		{description: The LmiStringVector object.}
	}
	{parameter: 
		{name: s}
		{description: The element to be removed.}
	}
	{return: LMI_TRUE if the operation was successful; LMI_FALSE, otherwise.}
}
*/
LmiBool LmiStringVectorRemoveCStr(LmiStringVector* v, const char* s);

/**
{function visibility="public":
	{name: LmiStringVectorIsAMember}
	{parent: LmiStringVector}
	{description: To test the membership in an LmiStringVector.}
	{prototype: LmiBool LmiStringVectorIsAMember(const LmiStringVector* v, const LmiString* val)}
	{parameter: 
		{name: v}
		{description: The vector.}
	}
	{parameter: 
		{name: val}
		{description: The string whose membership needs to be tested.}
	}
	{return: LMI_TRUE if member; LMI_FALSE otherwise.}
}
*/
LmiBool LmiStringVectorIsAMember(const LmiStringVector* v, const LmiString* val);

/**
{function visibility="public":
	{name: LmiStringVectorIsAMemberCStr}
	{parent: LmiStringVector}
	{description: To test the membership (of a C-style string) in an LmiStringVector.}
	{prototype: LmiBool LmiStringVectorIsAMemberCStr(const LmiStringVector* v, const char* val)}
	{parameter: 
		{name: v}
		{description: The vector.}
	}
	{parameter: 
		{name: val}
		{description: The string whose membership needs to be tested.}
	}
	{return: LMI_TRUE if member; LMI_FALSE otherwise.}
}
*/
LmiBool LmiStringVectorIsAMemberCStr(const LmiStringVector* v, const char* val);

LMI_END_EXTERN_C

#endif /* LMI_STRINGVECTOR_H */
