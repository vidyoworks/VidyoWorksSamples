/** {file:
    {name: LmiMallocAllocator.h}
    {description: Simple LmiAllocator that uses {code: malloc} and
    {code: free}.}
    {copyright:
    	(c) 2005-2009 Vidyo, Inc.,
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

#ifndef LMI_MALLOC_ALLOCATOR_H_
#define LMI_MALLOC_ALLOCATOR_H_

#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

/**
   {type:
     {name: LmiMallocAllocator}
     {parent: Os}
     {include: Lmi/Os/LmiMallocAllocator.h}
     {description: An LmiAllocator object that allocates memory using the
                   standard C {code: malloc} and {code: free} functions.}
   }
*/
typedef LmiAllocator LmiMallocAllocator;

/**
   {function:
     {name: LmiMallocAllocatorConstruct}
     {parent: LmiMallocAllocator}
     {description: Construct a new LmiMallocAllocator.}
     {prototype: LmiAllocator* LmiMallocAllocatorConstruct(LmiAllocator* a)}
     {parameter: {name: a}
       {description: A pointer to an uninitialized LmiAllocator.}}
     {return: The initialized LmiMallocAllocator, or {code: NULL} on failure.}
   }
*/
LmiAllocator* LmiMallocAllocatorConstruct(LmiAllocator* a);

/**
   {function:
     {name: LmiMallocAllocatorDestruct}
     {parent: LmiMallocAllocator}
     {description: Destruct an LmiMallocAllocator.}
     {prototype: void LmiMallocAllocatorDestruct(LmiAllocator* a)}
     {parameter: {name: a}
        {description: A pointer to an LmiMallocAllocator to destruct.}}
}
*/
void LmiMallocAllocatorDestruct(LmiAllocator* a);


/**
   {function:
     {name: LmiMallocAllocatorInitialize}
     {parent: LmiMallocAllocator}
     {description: Initialize LmiMallocAllocator, so LmiMallocAllocatorGet
                   works.}
     {prototype: LmiBool LmiMallocAllocatorInitialize(void)}
     {return: LMI_TRUE on success, LMI_FALSE on failure.}
   }
*/
LmiBool LmiMallocAllocatorInitialize(void);

/**
   {function:
     {name: LmiMallocAllocatorUninitialize}
     {parent: LmiMallocAllocator}
     {description: Uninitialize LmiMallocAllocator.}
     {prototype: void LmiMallocAllocatorUninitialize(void)}
   }
*/
void LmiMallocAllocatorUninitialize(void);

/**
   {function replaced-by="LmiMallocAllocatorGetDefault":
     {name: LmiMallocAllocatorGet}
     {parent: LmiMallocAllocator}
     {description: Get the single, global LmiMallocAllocator.}
     {prototype: LmiAllocator* LmiMallocAllocatorGet(void)}
	 {return: The global LmiMallocAllocator created by
	   LmiMallocAllocatorInitialize().}
     {note: To avoid creating redundant instances of LmiMallocAllocator,
            thus function should generally be used in preference to
            LmiMallocAllocatorConstruct.}
   }
*/
LmiAllocator* LmiMallocAllocatorGet(void);

/**
   {function:
     {name: LmiMallocAllocatorGetDefault}
     {parent: LmiMallocAllocator}
     {description: Get the single, global LmiMallocAllocator.}
     {prototype: LmiAllocator* LmiMallocAllocatorGetDefault(void)}
	 {return: The global LmiMallocAllocator created by
	   LmiMallocAllocatorInitialize().}
     {note: To avoid creating redundant instances of LmiMallocAllocator,
            this function should generally be used in preference to
            LmiMallocAllocatorConstruct.}
   }
*/
LmiAllocator* LmiMallocAllocatorGetDefault(void);

LMI_END_EXTERN_C

#endif /* LMI_MALLOC_ALLOCATOR_H_ */
