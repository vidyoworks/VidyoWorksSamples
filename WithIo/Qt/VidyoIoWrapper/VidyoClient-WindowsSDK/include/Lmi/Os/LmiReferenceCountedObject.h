/**
{file:
	{name: LmiReferenceCountedObject.h}
	{description: }
	{copyright:
		(c) 2009 Vidyo, Inc.,
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
#ifndef LMI_REFERENCECOUNTEDOBJECT_H
#define LMI_REFERENCECOUNTEDOBJECT_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Os/LmiAtomicInteger.h>

LMI_BEGIN_EXTERN_C

struct LmiReferenceCountedObject;

/**
{callback:
	{name: LmiReferenceCountedObjectDeleteCallback}
	{parent: LmiReferenceCountedObject}
	{description: A callback invoked when all references to the object have been removed.}
	{prototype: void (*LmiReferenceCountedObjectDeleteCallback)(LmiReferenceCountedObject *obj)}
	{parameter: {name: obj} {description: The object being deleted.}}
}
*/
typedef void (*LmiReferenceCountedObjectDeleteCallback)(struct LmiReferenceCountedObject *obj);

/**
{type visibility="public":
	{name: LmiReferenceCountedObject}
	{parent: Os}
	{include: Lmi/Os/LmiReferenceCountedObject.h}
	{description: Simple class for managing reference counts for another object. The object is
		constructed with a reference count of 1. LmiReferenceCountedObjectAddReference increments
		the reference count by 1 and LmiReferenceCountedObjectRemoveReference decrements it by 1.
		When the count becomes 0, the LmiReferenceCountedObjectDeleteCallback is invoked.}
}
*/
typedef struct LmiReferenceCountedObject
{
	LmiAtomicInteger refs;
	LmiReferenceCountedObjectDeleteCallback deleteCallback;
} LmiReferenceCountedObject;

/**
{function:
	{name: LmiReferenceCountedObjectConstruct}
	{parent: LmiReferenceCountedObject}
	{description: Constructs an LmiReferenceCountedObject.}
	{prototype: LmiReferenceCountedObject *LmiReferenceCountedObjectConstruct(LmiReferenceCountedObject *obj, 
		LmiReferenceCountedObjectDeleteCallback deleteCallback)}
	{parameter: {name: obj} {description: The LmiReferenceCountedObject to construct.}}
	{parameter: {name: deleteCallback} {description: A callback to be invoked when all references to the object
		have been removed.}}
	{return: A pointer to a constructed object on success, or NULL on failure.}
}
*/
LmiReferenceCountedObject *LmiReferenceCountedObjectConstruct(LmiReferenceCountedObject *obj, 
	LmiReferenceCountedObjectDeleteCallback deleteCallback);

/**
{function:
	{name: LmiReferenceCountedObjectDestruct}
	{parent: LmiReferenceCountedObject}
	{description: Destructs an LmiReferenceCountedObject.}
	{prototype: void LmiReferenceCountedObjectDestruct(LmiReferenceCountedObject *obj)}
	{parameter: {name: obj} {description: The LmiReferenceCountedObject to destruct.}}
}
*/
LMI_INLINE_DECLARATION void LmiReferenceCountedObjectDestruct(LmiReferenceCountedObject *obj);

/**
{function:
	{name: LmiReferenceCountedObjectAddReference}
	{parent: LmiReferenceCountedObject}
	{description: Increments an object's reference count.}
	{prototype: void LmiReferenceCountedObjectAddReference(LmiReferenceCountedObject *obj)}
	{parameter: {name: obj} {description: The LmiReferenceCountedObject.}}
}
*/
LMI_INLINE_DECLARATION void LmiReferenceCountedObjectAddReference(LmiReferenceCountedObject *obj);

/**
{function:
	{name: LmiReferenceCountedObjectRemoveReference}
	{parent: LmiReferenceCountedObject}
	{description: Decrements an object's reference count. When the count becomes 0,
		the LmiReferenceCountedObjectDeleteCallback is invoked.}
	{prototype: void LmiReferenceCountedObjectRemoveReference(LmiReferenceCountedObject *obj)}
	{parameter: {name: obj} {description: The LmiReferenceCountedObject.}}
}
*/
LMI_INLINE_DECLARATION void LmiReferenceCountedObjectRemoveReference(LmiReferenceCountedObject *obj);

/**
 {function:
	{name: LmiReferenceCountedObjectUnique}
	{parent: LmiReferenceCountedObject}
	{description: Get the whether a reference counted object is unique, i.e. its reference count is 1.}
	{prototype: LmiBool LmiReferenceCountedObjectUnique(const LmiReferenceCountedObject *obj)}
	{parameter: {name: obj} {description: The LmiReferenceCountedObject.}}
	{return: Whether the reference counted object's reference count is 1.}
 }
 */
LMI_INLINE_DECLARATION LmiBool LmiReferenceCountedObjectUnique(const LmiReferenceCountedObject *obj);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiReferenceCountedObjectInline.h>
#endif

#endif
