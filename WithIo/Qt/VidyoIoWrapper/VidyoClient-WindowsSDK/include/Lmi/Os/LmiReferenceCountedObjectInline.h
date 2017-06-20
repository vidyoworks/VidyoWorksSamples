/**
{file:
	{name: LmiReferenceCountedObjectInline.h}
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
LMI_INLINE void LmiReferenceCountedObjectDestruct(LmiReferenceCountedObject *obj)
{
	LmiAtomicIntegerDestruct(&obj->refs);
}

LMI_INLINE void LmiReferenceCountedObjectAddReference(LmiReferenceCountedObject *obj)
{
	LmiAtomicIntegerIncrement(&obj->refs);
}

LMI_INLINE void LmiReferenceCountedObjectRemoveReference(LmiReferenceCountedObject *obj)
{
	if(LmiAtomicIntegerDecrement(&obj->refs) == 0)
		obj->deleteCallback(obj);
}

LMI_INLINE LmiBool LmiReferenceCountedObjectUnique(const LmiReferenceCountedObject *obj)
{
	return LmiAtomicIntegerGetValue(&obj->refs) == 1;
}
