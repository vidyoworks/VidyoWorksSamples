/**
{file:
	{name: LmiBasicTypesContainer.h}
	{description: Contains definitions for basic type containers.}
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
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

#ifndef LMI_BASICTYPESCONTAINER_H
#define LMI_BASICTYPESCONTAINER_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUnordered.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiDeque.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiSet.h>

LMI_BEGIN_EXTERN_C

/* Vector declarations. */

Declare_LmiVector(LmiInt8)
Declare_LmiVectorLess(LmiInt8)

Declare_LmiVector(LmiUint8)
Declare_LmiVectorLess(LmiUint8)

Declare_LmiVector(LmiInt16)
Declare_LmiVectorLess(LmiInt16)

Declare_LmiVector(LmiUint16)
Declare_LmiVectorLess(LmiUint16)

Declare_LmiVector(LmiInt)
Declare_LmiVectorLess(LmiInt)

Declare_LmiVector(LmiUint)
Declare_LmiVectorEqual(LmiUint)
Declare_LmiVectorLess(LmiUint)

Declare_LmiVector(LmiInt64)
Declare_LmiVectorLess(LmiInt64)

Declare_LmiVector(LmiUint64)
Declare_LmiVectorLess(LmiUint64)

Declare_LmiVector(LmiFloat32)
Declare_LmiVectorLess(LmiFloat32)

Declare_LmiVector(LmiFloat64)
Declare_LmiVectorLess(LmiFloat64)

Declare_LmiVector(LmiBool)


/**
   {type visibility="private":
     {name: LmiPointerVector}
     {parent: Containers}
     {include: Lmi/Utils/LmiPointerVector.h}
     {description: LmiPointerVector is an instantiation of LmiVector over
       pointers-to-void.}
     {note: See LmiVector, and the STL std::vector template, for descriptions
       of LmiPointerVector\'s member functions.}
     {note visibility="private": In general, LmiPointerVector should be
       used in preference to vectors of pointers to specific types, to avoid
       unnecessary code duplication in the SDK\'s object files.}
   }
*/
Declare_LmiVector(LmiVoidPtr)
Declare_LmiVectorEqual(LmiVoidPtr)

/**
   {type visibility="private":
     {name: LmiPointerList}
     {parent: Containers}
     {include: Lmi/Utils/LmiPointerList.h}
     {description: LmiPointerList is an instantiation of LmiList over
       pointers-to-void.}
     {note: See LmiList, and the STL std::list template, for descriptions
       of LmiPointerList\'s member functions.}
     {note visibility="private": In general, LmiPointerList should be
       used in preference to lists of pointers to specific types, to avoid
       unnecessary code duplication in the SDK\'s object files.}
   }
*/
/**
{type visibility="private":
	{name: LmiPointerListIterator}
	{parent: LmiPointerList}
	{include: Lmi/Utils/LmiPointerList.h}
	{description: The iterator type for LmiPointerList.}
}
*/
/**
{type visibility="private":
	{name: LmiPointerListConstIterator}
	{parent: LmiPointerList}
	{include: Lmi/Utils/LmiPointerList.h}
	{description: The read-only iterator type for LmiPointerList.}
}
*/
/**
{type visibility="private":
	{name: LmiPointerListReverseIterator}
	{parent: LmiPointerList}
	{include: Lmi/Utils/LmiPointerList.h}
	{description: The reverse iterator type for LmiPointerList.}
}
*/
/**
{type visibility="private":
	{name: LmiPointerListConstReverseIterator}
	{parent: LmiPointerList}
	{include: Lmi/Utils/LmiPointerList.h}
	{description: The reverse read-only iterator type for LmiPointerList.}
}
*/

Declare_LmiList(LmiVoidPtr)

Declare_LmiDeque(LmiVoidPtr)

Declare_LmiPair(LmiInt64, LmiInt64)
Declare_LmiVector(LmiPair(LmiInt64, LmiInt64))

Declare_LmiUnorderedMap(LmiUint, LmiVoidPtr)

Declare_LmiSet(LmiUint)

LMI_END_EXTERN_C

#endif /* LMI_BASICTYPESCONTAINER_H */
