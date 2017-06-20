/**
{file:
	{name: LmiTypes.h}
	{description: basic type declarations for LMI software.}
	{copyright:
		(c) 2005-2014 Vidyo, Inc.,
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
#ifndef LMI_TYPES_H_
#define LMI_TYPES_H_

#include <stdlib.h> /* NULL, size_t */
#include <stddef.h> /* ptrdiff_t */
#include <limits.h> /* CHAR_BIT */

#include <Lmi/Utils/SysDep/LmiBaseTypes.h>
#include <Lmi/Utils/LmiObjects.h>

LMI_BEGIN_EXTERN_C

/**
   {package:
     {name: BasicTypes}
	 {parent: Utils}
	 {include: Lmi/Utils/LmiTypes.h}
	 {description: Common base integer types.}
   }
*/

/**
	{type: 
		{name: LmiBool}
		{parent: BasicTypes}
		{description: Boolean type.}
		{value: {name: LMI_FALSE} {description: A false value of LmiBool.}}
		{value: {name: LMI_TRUE} {description: A true value of LmiBool.}}
	}
*/


/**
	{function:
		{name: LmiBoolConstruct}
		{parent: LmiBool}
		{description: Construct a default instance of an LmiBool object.}
		{prototype: LmiBool* LmiBoolConstruct(LmiBool* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiBool object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiBool object is initialized with the value 0.
			LmiBool construction will not fail.}
	}

	{function:
		{name: LmiBoolConstructCopy}
		{parent: LmiBool}
		{description: Construct a new LmiBool object as a copy of an
			existing one.}
		{prototype: LmiBool* LmiBoolConstructCopy(LmiBool* dst, const LmiBool* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiBool object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiBool object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiBool construction will not fail.}
	}

	{function:
		{name: LmiBoolDestruct}
		{parent: LmiBool}
		{description: Destruct an LmiBool object.}
		{prototype: void LmiBoolDestruct(LmiBool* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiBool object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiBoolAssign}
		{parent: LmiBool}
		{description: Assign the value of one LmiBool object to another one.}
		{prototype: LmiBool* LmiBoolAssign(LmiBool* dst, const LmiBool* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiBool object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiBool object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiBool assignment will not fail.}
	}
   
	{function:
		{name: LmiBoolEqual}
		{parent: LmiBool}
		{description: Compare the values of two LmiBool objects for
			equality.}
		{prototype: LmiBool LmiBoolEqual(const LmiBool* a, const LmiBool* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiBool object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiBool object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiBoolLess}
		{parent: LmiBool}
		{description: Compare the values of two LmiBool objects for
			ordering.}
		{prototype: LmiBool LmiBoolLess(const LmiBool* a, const LmiBool* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiBool object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiBool object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiBoolSwap}
		{parent: LmiBool}
		{description: Swap the contents of two LmiBool objects.}
		{prototype: LmiBool LmiBoolSwap(LmiBool* a, LmiBool* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiBool object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiBool object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiBool swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiBool)

/**
   {type:
     {name: LmiInt}
     {parent: BasicTypes}
     {description: Basic integer type.}
   }
*/

/**
	{function:
		{name: LmiIntConstruct}
		{parent: LmiInt}
		{description: Construct a default instance of an LmiInt object.}
		{prototype: LmiInt* LmiIntConstruct(LmiInt* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiInt object is initialized with the value 0.
			LmiInt construction will not fail.}
	}

	{function:
		{name: LmiIntConstructCopy}
		{parent: LmiInt}
		{description: Construct a new LmiInt object as a copy of an
			existing one.}
		{prototype: LmiInt* LmiIntConstructCopy(LmiInt* dst, const LmiInt* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiInt object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiInt construction will not fail.}
	}

	{function:
		{name: LmiIntDestruct}
		{parent: LmiInt}
		{description: Destruct an LmiInt object.}
		{prototype: void LmiIntDestruct(LmiInt* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiIntAssign}
		{parent: LmiInt}
		{description: Assign the value of one LmiInt object to another one.}
		{prototype: LmiInt* LmiIntAssign(LmiInt* dst, const LmiInt* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiInt object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiInt assignment will not fail.}
	}
   
	{function:
		{name: LmiIntEqual}
		{parent: LmiInt}
		{description: Compare the values of two LmiInt objects for
			equality.}
		{prototype: LmiBool LmiIntEqual(const LmiInt* a, const LmiInt* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiIntLess}
		{parent: LmiInt}
		{description: Compare the values of two LmiInt objects for
			ordering.}
		{prototype: LmiBool LmiIntLess(const LmiInt* a, const LmiInt* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiIntSwap}
		{parent: LmiInt}
		{description: Swap the contents of two LmiInt objects.}
		{prototype: LmiBool LmiIntSwap(LmiInt* a, LmiInt* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiInt swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiInt)

/**
	{function:
		{name: LmiIntAbsoluteValue}
		{parent: LmiInt}
		{description: Get the absolute value of an integer.}
		{prototype: LmiInt LmiIntAbsoluteValue(const LmiInt* x)}
		{parameter:
			{name: x}
			{description: A pointer to an LmiInt object.}}
		{return: An LmiInt containing the absolute value of the LmiInt pointed to by x.}
	}
*/
LmiInt LmiIntAbsoluteValue(const LmiInt* x);

#if CHAR_BIT != 8
/* Ensure that the LMI_SIZEOF measurements computed by autoconf
   correspond to the values we think they do. */
#error "The LMI SDK does not currently support platforms non-8-bit bytes"
#endif


/**
   {type:
     {name: LmiInt8}
     {parent: BasicTypes}
     {description: Basic 8-bit integer type.}
   }
*/

/**
	{function:
		{name: LmiInt8Construct}
		{parent: LmiInt8}
		{description: Construct a default instance of an LmiInt8 object.}
		{prototype: LmiInt8* LmiInt8Construct(LmiInt8* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt8 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiInt8 object is initialized with the value 0.
			LmiInt8 construction will not fail.}
	}

	{function:
		{name: LmiInt8ConstructCopy}
		{parent: LmiInt8}
		{description: Construct a new LmiInt8 object as a copy of an
			existing one.}
		{prototype: LmiInt8* LmiInt8ConstructCopy(LmiInt8* dst, const LmiInt8* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt8 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiInt8 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiInt8 construction will not fail.}
	}

	{function:
		{name: LmiInt8Destruct}
		{parent: LmiInt8}
		{description: Destruct an LmiInt8 object.}
		{prototype: void LmiInt8Destruct(LmiInt8* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt8 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiInt8Assign}
		{parent: LmiInt8}
		{description: Assign the value of one LmiInt8 object to another one.}
		{prototype: LmiInt8* LmiInt8Assign(LmiInt8* dst, const LmiInt8* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt8 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiInt8 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiInt8 assignment will not fail.}
	}
   
	{function:
		{name: LmiInt8Equal}
		{parent: LmiInt8}
		{description: Compare the values of two LmiInt8 objects for
			equality.}
		{prototype: LmiBool LmiInt8Equal(const LmiInt8* a, const LmiInt8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt8 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt8 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiInt8Less}
		{parent: LmiInt8}
		{description: Compare the values of two LmiInt8 objects for
			ordering.}
		{prototype: LmiBool LmiInt8Less(const LmiInt8* a, const LmiInt8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt8 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt8 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiInt8Swap}
		{parent: LmiInt8}
		{description: Swap the contents of two LmiInt8 objects.}
		{prototype: LmiBool LmiInt8Swap(LmiInt8* a, LmiInt8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt8 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt8 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiInt8 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiInt8)

/**
   {type:
     {name: LmiInt16}
     {parent: BasicTypes}
     {description: Basic 16-bit integer type.}
   }
*/

/**
	{function:
		{name: LmiInt16Construct}
		{parent: LmiInt16}
		{description: Construct a default instance of an LmiInt16 object.}
		{prototype: LmiInt16* LmiInt16Construct(LmiInt16* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt16 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiInt16 object is initialized with the value 0.
			LmiInt16 construction will not fail.}
	}

	{function:
		{name: LmiInt16ConstructCopy}
		{parent: LmiInt16}
		{description: Construct a new LmiInt16 object as a copy of an
			existing one.}
		{prototype: LmiInt16* LmiInt16ConstructCopy(LmiInt16* dst, const LmiInt16* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt16 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiInt16 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiInt16 construction will not fail.}
	}

	{function:
		{name: LmiInt16Destruct}
		{parent: LmiInt16}
		{description: Destruct an LmiInt16 object.}
		{prototype: void LmiInt16Destruct(LmiInt16* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt16 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiInt16Assign}
		{parent: LmiInt16}
		{description: Assign the value of one LmiInt16 object to another one.}
		{prototype: LmiInt16* LmiInt16Assign(LmiInt16* dst, const LmiInt16* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt16 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiInt16 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiInt16 assignment will not fail.}
	}
   
	{function:
		{name: LmiInt16Equal}
		{parent: LmiInt16}
		{description: Compare the values of two LmiInt16 objects for
			equality.}
		{prototype: LmiBool LmiInt16Equal(const LmiInt16* a, const LmiInt16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt16 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt16 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiInt16Less}
		{parent: LmiInt16}
		{description: Compare the values of two LmiInt16 objects for
			ordering.}
		{prototype: LmiBool LmiInt16Less(const LmiInt16* a, const LmiInt16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt16 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt16 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiInt16Swap}
		{parent: LmiInt16}
		{description: Swap the contents of two LmiInt16 objects.}
		{prototype: LmiBool LmiInt16Swap(LmiInt16* a, LmiInt16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt16 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt16 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiInt16 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiInt16)

/**
   {type:
     {name: LmiInt32}
     {parent: BasicTypes}
     {description: Basic 32-bit integer type.}
   }
*/

/**
	{function:
		{name: LmiInt32Construct}
		{parent: LmiInt32}
		{description: Construct a default instance of an LmiInt32 object.}
		{prototype: LmiInt32* LmiInt32Construct(LmiInt32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt32 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiInt32 object is initialized with the value 0.
			LmiInt32 construction will not fail.}
	}

	{function:
		{name: LmiInt32ConstructCopy}
		{parent: LmiInt32}
		{description: Construct a new LmiInt32 object as a copy of an
			existing one.}
		{prototype: LmiInt32* LmiInt32ConstructCopy(LmiInt32* dst, const LmiInt32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt32 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiInt32 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiInt32 construction will not fail.}
	}

	{function:
		{name: LmiInt32Destruct}
		{parent: LmiInt32}
		{description: Destruct an LmiInt32 object.}
		{prototype: void LmiInt32Destruct(LmiInt32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt32 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiInt32Assign}
		{parent: LmiInt32}
		{description: Assign the value of one LmiInt32 object to another one.}
		{prototype: LmiInt32* LmiInt32Assign(LmiInt32* dst, const LmiInt32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt32 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiInt32 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiInt32 assignment will not fail.}
	}
   
	{function:
		{name: LmiInt32Equal}
		{parent: LmiInt32}
		{description: Compare the values of two LmiInt32 objects for
			equality.}
		{prototype: LmiBool LmiInt32Equal(const LmiInt32* a, const LmiInt32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt32 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiInt32Less}
		{parent: LmiInt32}
		{description: Compare the values of two LmiInt32 objects for
			ordering.}
		{prototype: LmiBool LmiInt32Less(const LmiInt32* a, const LmiInt32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt32 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiInt32Swap}
		{parent: LmiInt32}
		{description: Swap the contents of two LmiInt32 objects.}
		{prototype: LmiBool LmiInt32Swap(LmiInt32* a, LmiInt32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt32 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt32 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiInt32 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiInt32)

/**
   {type:
     {name: LmiInt64}
     {parent: BasicTypes}
     {description: Basic 64-bit integer type.}
   }
*/

/**
	{function:
		{name: LmiInt64Construct}
		{parent: LmiInt64}
		{description: Construct a default instance of an LmiInt64 object.}
		{prototype: LmiInt64* LmiInt64Construct(LmiInt64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt64 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiInt64 object is initialized with the value 0.
			LmiInt64 construction will not fail.}
	}

	{function:
		{name: LmiInt64ConstructCopy}
		{parent: LmiInt64}
		{description: Construct a new LmiInt64 object as a copy of an
			existing one.}
		{prototype: LmiInt64* LmiInt64ConstructCopy(LmiInt64* dst, const LmiInt64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt64 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiInt64 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiInt64 construction will not fail.}
	}

	{function:
		{name: LmiInt64Destruct}
		{parent: LmiInt64}
		{description: Destruct an LmiInt64 object.}
		{prototype: void LmiInt64Destruct(LmiInt64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiInt64 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiInt64Assign}
		{parent: LmiInt64}
		{description: Assign the value of one LmiInt64 object to another one.}
		{prototype: LmiInt64* LmiInt64Assign(LmiInt64* dst, const LmiInt64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiInt64 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiInt64 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiInt64 assignment will not fail.}
	}
   
	{function:
		{name: LmiInt64Equal}
		{parent: LmiInt64}
		{description: Compare the values of two LmiInt64 objects for
			equality.}
		{prototype: LmiBool LmiInt64Equal(const LmiInt64* a, const LmiInt64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt64 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiInt64Less}
		{parent: LmiInt64}
		{description: Compare the values of two LmiInt64 objects for
			ordering.}
		{prototype: LmiBool LmiInt64Less(const LmiInt64* a, const LmiInt64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt64 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiInt64Swap}
		{parent: LmiInt64}
		{description: Swap the contents of two LmiInt64 objects.}
		{prototype: LmiBool LmiInt64Swap(LmiInt64* a, LmiInt64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiInt64 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiInt64 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiInt64 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiInt64)

/**
   {function validate="no":
     {name: LMI_INT64_C}
	 {parent: LmiUint64}
	 {description: A macro that expands to a signed 64-bit integer
	   constant.}
	 {prototype: LmiInt64 LMI_INT64_C(LmiInt64 val)}
	 {parameter: 
	   {name: val}
	   {description: A signed decimal, octal, or hexadecimal constant,
	     with a value no greater than 2^63 - 1 and no less than -(2^63).}}
	 {return: Expands to a signed integer constant with the value val
	   and the type LmiInt64.  For example, if LmiInt64 is a name for the
	   C type long long int, then LMI_INT64_C(0x123) might expand
	   to the integer constant 0x123LL.}
	}
*/


/**
   {type:
     {name: LmiIntPtrT}
     {parent: BasicTypes}
     {description: A signed integer type as big as an object pointer.}
   }
*/

/**
	{function:
		{name: LmiIntPtrTConstruct}
		{parent: LmiIntPtrT}
		{description: Construct a default instance of an LmiIntPtrT object.}
		{prototype: LmiIntPtrT* LmiIntPtrTConstruct(LmiIntPtrT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiIntPtrT object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiIntPtrT object is initialized with the value 0.
			LmiIntPtrT construction will not fail.}
	}

	{function:
		{name: LmiIntPtrTConstructCopy}
		{parent: LmiIntPtrT}
		{description: Construct a new LmiIntPtrT object as a copy of an
			existing one.}
		{prototype: LmiIntPtrT* LmiIntPtrTConstructCopy(LmiIntPtrT* dst, const LmiIntPtrT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiIntPtrT object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiIntPtrT object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiIntPtrT construction will not fail.}
	}

	{function:
		{name: LmiIntPtrTDestruct}
		{parent: LmiIntPtrT}
		{description: Destruct an LmiIntPtrT object.}
		{prototype: void LmiIntPtrTDestruct(LmiIntPtrT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiIntPtrT object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiIntPtrTAssign}
		{parent: LmiIntPtrT}
		{description: Assign the value of one LmiIntPtrT object to another one.}
		{prototype: LmiIntPtrT* LmiIntPtrTAssign(LmiIntPtrT* dst, const LmiIntPtrT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiIntPtrT object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiIntPtrT object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiIntPtrT assignment will not fail.}
	}
   
	{function:
		{name: LmiIntPtrTEqual}
		{parent: LmiIntPtrT}
		{description: Compare the values of two LmiIntPtrT objects for
			equality.}
		{prototype: LmiBool LmiIntPtrTEqual(const LmiIntPtrT* a, const LmiIntPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiIntPtrT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiIntPtrT object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiIntPtrTLess}
		{parent: LmiIntPtrT}
		{description: Compare the values of two LmiIntPtrT objects for
			ordering.}
		{prototype: LmiBool LmiIntPtrTLess(const LmiIntPtrT* a, const LmiIntPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiIntPtrT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiIntPtrT object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiIntPtrTSwap}
		{parent: LmiIntPtrT}
		{description: Swap the contents of two LmiIntPtrT objects.}
		{prototype: LmiBool LmiIntPtrTSwap(LmiIntPtrT* a, LmiIntPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiIntPtrT object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiIntPtrT object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiIntPtrT swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiIntPtrT)

/**
   {type:
     {name: LmiUint}
     {parent: BasicTypes}
     {description: Basic unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiUintConstruct}
		{parent: LmiUint}
		{description: Construct a default instance of an LmiUint object.}
		{prototype: LmiUint* LmiUintConstruct(LmiUint* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUint object is initialized with the value 0.
			LmiUint construction will not fail.}
	}

	{function:
		{name: LmiUintConstructCopy}
		{parent: LmiUint}
		{description: Construct a new LmiUint object as a copy of an
			existing one.}
		{prototype: LmiUint* LmiUintConstructCopy(LmiUint* dst, const LmiUint* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUint object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUint construction will not fail.}
	}

	{function:
		{name: LmiUintDestruct}
		{parent: LmiUint}
		{description: Destruct an LmiUint object.}
		{prototype: void LmiUintDestruct(LmiUint* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUintAssign}
		{parent: LmiUint}
		{description: Assign the value of one LmiUint object to another one.}
		{prototype: LmiUint* LmiUintAssign(LmiUint* dst, const LmiUint* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUint object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUint assignment will not fail.}
	}
   
	{function:
		{name: LmiUintEqual}
		{parent: LmiUint}
		{description: Compare the values of two LmiUint objects for
			equality.}
		{prototype: LmiBool LmiUintEqual(const LmiUint* a, const LmiUint* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUintLess}
		{parent: LmiUint}
		{description: Compare the values of two LmiUint objects for
			ordering.}
		{prototype: LmiBool LmiUintLess(const LmiUint* a, const LmiUint* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUintSwap}
		{parent: LmiUint}
		{description: Swap the contents of two LmiUint objects.}
		{prototype: LmiBool LmiUintSwap(LmiUint* a, LmiUint* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUint swapping will not fail.}
	}
*/

Declare_LmiBasicType(LmiUint)

/**
   {type:
     {name: LmiUint8}
     {parent: BasicTypes}
     {description: Basic 8-bit unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiUint8Construct}
		{parent: LmiUint8}
		{description: Construct a default instance of an LmiUint8 object.}
		{prototype: LmiUint8* LmiUint8Construct(LmiUint8* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint8 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUint8 object is initialized with the value 0.
			LmiUint8 construction will not fail.}
	}

	{function:
		{name: LmiUint8ConstructCopy}
		{parent: LmiUint8}
		{description: Construct a new LmiUint8 object as a copy of an
			existing one.}
		{prototype: LmiUint8* LmiUint8ConstructCopy(LmiUint8* dst, const LmiUint8* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint8 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUint8 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUint8 construction will not fail.}
	}

	{function:
		{name: LmiUint8Destruct}
		{parent: LmiUint8}
		{description: Destruct an LmiUint8 object.}
		{prototype: void LmiUint8Destruct(LmiUint8* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint8 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUint8Assign}
		{parent: LmiUint8}
		{description: Assign the value of one LmiUint8 object to another one.}
		{prototype: LmiUint8* LmiUint8Assign(LmiUint8* dst, const LmiUint8* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint8 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUint8 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUint8 assignment will not fail.}
	}
   
	{function:
		{name: LmiUint8Equal}
		{parent: LmiUint8}
		{description: Compare the values of two LmiUint8 objects for
			equality.}
		{prototype: LmiBool LmiUint8Equal(const LmiUint8* a, const LmiUint8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint8 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint8 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUint8Less}
		{parent: LmiUint8}
		{description: Compare the values of two LmiUint8 objects for
			ordering.}
		{prototype: LmiBool LmiUint8Less(const LmiUint8* a, const LmiUint8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint8 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint8 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUint8Swap}
		{parent: LmiUint8}
		{description: Swap the contents of two LmiUint8 objects.}
		{prototype: LmiBool LmiUint8Swap(LmiUint8* a, LmiUint8* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint8 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint8 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUint8 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiUint8)

/**
   {type:
     {name: LmiUint16}
     {parent: BasicTypes}
     {description: Basic 16-bit unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiUint16Construct}
		{parent: LmiUint16}
		{description: Construct a default instance of an LmiUint16 object.}
		{prototype: LmiUint16* LmiUint16Construct(LmiUint16* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint16 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUint16 object is initialized with the value 0.
			LmiUint16 construction will not fail.}
	}

	{function:
		{name: LmiUint16ConstructCopy}
		{parent: LmiUint16}
		{description: Construct a new LmiUint16 object as a copy of an
			existing one.}
		{prototype: LmiUint16* LmiUint16ConstructCopy(LmiUint16* dst, const LmiUint16* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint16 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUint16 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUint16 construction will not fail.}
	}

	{function:
		{name: LmiUint16Destruct}
		{parent: LmiUint16}
		{description: Destruct an LmiUint16 object.}
		{prototype: void LmiUint16Destruct(LmiUint16* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint16 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUint16Assign}
		{parent: LmiUint16}
		{description: Assign the value of one LmiUint16 object to another one.}
		{prototype: LmiUint16* LmiUint16Assign(LmiUint16* dst, const LmiUint16* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint16 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUint16 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUint16 assignment will not fail.}
	}
   
	{function:
		{name: LmiUint16Equal}
		{parent: LmiUint16}
		{description: Compare the values of two LmiUint16 objects for
			equality.}
		{prototype: LmiBool LmiUint16Equal(const LmiUint16* a, const LmiUint16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint16 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint16 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUint16Less}
		{parent: LmiUint16}
		{description: Compare the values of two LmiUint16 objects for
			ordering.}
		{prototype: LmiBool LmiUint16Less(const LmiUint16* a, const LmiUint16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint16 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint16 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUint16Swap}
		{parent: LmiUint16}
		{description: Swap the contents of two LmiUint16 objects.}
		{prototype: LmiBool LmiUint16Swap(LmiUint16* a, LmiUint16* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint16 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint16 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUint16 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiUint16)

/**
   {type:
     {name: LmiUint32}
     {parent: BasicTypes}
     {description: Basic 32-bit unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiUint32Construct}
		{parent: LmiUint32}
		{description: Construct a default instance of an LmiUint32 object.}
		{prototype: LmiUint32* LmiUint32Construct(LmiUint32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint32 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUint32 object is initialized with the value 0.
			LmiUint32 construction will not fail.}
	}

	{function:
		{name: LmiUint32ConstructCopy}
		{parent: LmiUint32}
		{description: Construct a new LmiUint32 object as a copy of an
			existing one.}
		{prototype: LmiUint32* LmiUint32ConstructCopy(LmiUint32* dst, const LmiUint32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint32 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUint32 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUint32 construction will not fail.}
	}

	{function:
		{name: LmiUint32Destruct}
		{parent: LmiUint32}
		{description: Destruct an LmiUint32 object.}
		{prototype: void LmiUint32Destruct(LmiUint32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint32 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUint32Assign}
		{parent: LmiUint32}
		{description: Assign the value of one LmiUint32 object to another one.}
		{prototype: LmiUint32* LmiUint32Assign(LmiUint32* dst, const LmiUint32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint32 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUint32 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUint32 assignment will not fail.}
	}
   
	{function:
		{name: LmiUint32Equal}
		{parent: LmiUint32}
		{description: Compare the values of two LmiUint32 objects for
			equality.}
		{prototype: LmiBool LmiUint32Equal(const LmiUint32* a, const LmiUint32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint32 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUint32Less}
		{parent: LmiUint32}
		{description: Compare the values of two LmiUint32 objects for
			ordering.}
		{prototype: LmiBool LmiUint32Less(const LmiUint32* a, const LmiUint32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint32 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUint32Swap}
		{parent: LmiUint32}
		{description: Swap the contents of two LmiUint32 objects.}
		{prototype: LmiBool LmiUint32Swap(LmiUint32* a, LmiUint32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint32 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint32 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUint32 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiUint32)

/**
   {type:
     {name: LmiUint64}
     {parent: BasicTypes}
     {description: Basic 64-bit unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiUint64Construct}
		{parent: LmiUint64}
		{description: Construct a default instance of an LmiUint64 object.}
		{prototype: LmiUint64* LmiUint64Construct(LmiUint64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint64 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUint64 object is initialized with the value 0.
			LmiUint64 construction will not fail.}
	}

	{function:
		{name: LmiUint64ConstructCopy}
		{parent: LmiUint64}
		{description: Construct a new LmiUint64 object as a copy of an
			existing one.}
		{prototype: LmiUint64* LmiUint64ConstructCopy(LmiUint64* dst, const LmiUint64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint64 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUint64 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUint64 construction will not fail.}
	}

	{function:
		{name: LmiUint64Destruct}
		{parent: LmiUint64}
		{description: Destruct an LmiUint64 object.}
		{prototype: void LmiUint64Destruct(LmiUint64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUint64 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUint64Assign}
		{parent: LmiUint64}
		{description: Assign the value of one LmiUint64 object to another one.}
		{prototype: LmiUint64* LmiUint64Assign(LmiUint64* dst, const LmiUint64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUint64 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUint64 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUint64 assignment will not fail.}
	}
   
	{function:
		{name: LmiUint64Equal}
		{parent: LmiUint64}
		{description: Compare the values of two LmiUint64 objects for
			equality.}
		{prototype: LmiBool LmiUint64Equal(const LmiUint64* a, const LmiUint64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint64 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUint64Less}
		{parent: LmiUint64}
		{description: Compare the values of two LmiUint64 objects for
			ordering.}
		{prototype: LmiBool LmiUint64Less(const LmiUint64* a, const LmiUint64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint64 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUint64Swap}
		{parent: LmiUint64}
		{description: Swap the contents of two LmiUint64 objects.}
		{prototype: LmiBool LmiUint64Swap(LmiUint64* a, LmiUint64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUint64 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUint64 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUint64 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiUint64)

/**
   {function validate="no":
     {name: LMI_UINT64_C}
	 {parent: LmiUint64}
	 {description: A macro that expands to an unsigned 64-bit integer
	   constant.}
	 {prototype: LmiUint64 LMI_UINT64_C(LmiUint64 val)}
	 {parameter: 
	   {name: val}
	   {description: An unsigned decimal, octal, or hexadecimal constant,
	     with a value no greater than 2^64 - 1.}}
	 {return: Expands to an unsigned integer constant with the value val
	   and the type LmiUint64.  For example, if LmiUint64 is a name for the
	   C type unsigned long long int, then LMI_UINT64_C(0x123) might expand
	   to the integer constant 0x123ULL.}
	}
*/


/**
   {type:
     {name: LmiUintPtrT}
     {parent: BasicTypes}
     {description: An unsigned integer type as big as an object pointer.}
   }
*/

/**
	{function:
		{name: LmiUintPtrTConstruct}
		{parent: LmiUintPtrT}
		{description: Construct a default instance of an LmiUintPtrT object.}
		{prototype: LmiUintPtrT* LmiUintPtrTConstruct(LmiUintPtrT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUintPtrT object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiUintPtrT object is initialized with the value 0.
			LmiUintPtrT construction will not fail.}
	}

	{function:
		{name: LmiUintPtrTConstructCopy}
		{parent: LmiUintPtrT}
		{description: Construct a new LmiUintPtrT object as a copy of an
			existing one.}
		{prototype: LmiUintPtrT* LmiUintPtrTConstructCopy(LmiUintPtrT* dst, const LmiUintPtrT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUintPtrT object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiUintPtrT object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiUintPtrT construction will not fail.}
	}

	{function:
		{name: LmiUintPtrTDestruct}
		{parent: LmiUintPtrT}
		{description: Destruct an LmiUintPtrT object.}
		{prototype: void LmiUintPtrTDestruct(LmiUintPtrT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiUintPtrT object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiUintPtrTAssign}
		{parent: LmiUintPtrT}
		{description: Assign the value of one LmiUintPtrT object to another one.}
		{prototype: LmiUintPtrT* LmiUintPtrTAssign(LmiUintPtrT* dst, const LmiUintPtrT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiUintPtrT object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiUintPtrT object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiUintPtrT assignment will not fail.}
	}
   
	{function:
		{name: LmiUintPtrTEqual}
		{parent: LmiUintPtrT}
		{description: Compare the values of two LmiUintPtrT objects for
			equality.}
		{prototype: LmiBool LmiUintPtrTEqual(const LmiUintPtrT* a, const LmiUintPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUintPtrT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUintPtrT object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiUintPtrTLess}
		{parent: LmiUintPtrT}
		{description: Compare the values of two LmiUintPtrT objects for
			ordering.}
		{prototype: LmiBool LmiUintPtrTLess(const LmiUintPtrT* a, const LmiUintPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUintPtrT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUintPtrT object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiUintPtrTSwap}
		{parent: LmiUintPtrT}
		{description: Swap the contents of two LmiUintPtrT objects.}
		{prototype: LmiBool LmiUintPtrTSwap(LmiUintPtrT* a, LmiUintPtrT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiUintPtrT object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiUintPtrT object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiUintPtrT swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiUintPtrT)


/**
   {type:
     {name: LmiSizeT}
     {parent: BasicTypes}
     {description: The size of an object in memory.}
     {constant: {name: LMI_SIZET_MAX}
             {type: LmiSizeT}
             {description: The maximum value of an LmiSizeT.}}
     {constant replaced-by="LMI_SIZET_MAX": {name: LMI_SIZE_T_MAX}
             {type: LmiSizeT}
             {description: The maximum value of an LmiSizeT (deprecated).}}
     {note: This is an unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiSizeTConstruct}
		{parent: LmiSizeT}
		{description: Construct a default instance of an LmiSizeT object.}
		{prototype: LmiSizeT* LmiSizeTConstruct(LmiSizeT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiSizeT object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiSizeT object is initialized with the value 0.
			LmiSizeT construction will not fail.}
	}

	{function:
		{name: LmiSizeTConstructCopy}
		{parent: LmiSizeT}
		{description: Construct a new LmiSizeT object as a copy of an
			existing one.}
		{prototype: LmiSizeT* LmiSizeTConstructCopy(LmiSizeT* dst, const LmiSizeT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiSizeT object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiSizeT object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiSizeT construction will not fail.}
	}

	{function:
		{name: LmiSizeTDestruct}
		{parent: LmiSizeT}
		{description: Destruct an LmiSizeT object.}
		{prototype: void LmiSizeTDestruct(LmiSizeT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiSizeT object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiSizeTAssign}
		{parent: LmiSizeT}
		{description: Assign the value of one LmiSizeT object to another one.}
		{prototype: LmiSizeT* LmiSizeTAssign(LmiSizeT* dst, const LmiSizeT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiSizeT object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiSizeT object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiSizeT assignment will not fail.}
	}
   
	{function:
		{name: LmiSizeTEqual}
		{parent: LmiSizeT}
		{description: Compare the values of two LmiSizeT objects for
			equality.}
		{prototype: LmiBool LmiSizeTEqual(const LmiSizeT* a, const LmiSizeT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiSizeT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiSizeT object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiSizeTLess}
		{parent: LmiSizeT}
		{description: Compare the values of two LmiSizeT objects for
			ordering.}
		{prototype: LmiBool LmiSizeTLess(const LmiSizeT* a, const LmiSizeT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiSizeT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiSizeT object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiSizeTSwap}
		{parent: LmiSizeT}
		{description: Swap the contents of two LmiSizeT objects.}
		{prototype: LmiBool LmiSizeTSwap(LmiSizeT* a, LmiSizeT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiSizeT object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiSizeT object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiSizeT swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiSizeT)

/**
   {type:
     {name: LmiDistanceT}
     {parent: BasicTypes}
     {description: The distance between two pointer values.}
     {note: This is an unsigned integer type.}
   }
*/

/**
	{function:
		{name: LmiDistanceTConstruct}
		{parent: LmiDistanceT}
		{description: Construct a default instance of an LmiDistanceT object.}
		{prototype: LmiDistanceT* LmiDistanceTConstruct(LmiDistanceT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiDistanceT object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiDistanceT object is initialized with the value 0.
			LmiDistanceT construction will not fail.}
	}

	{function:
		{name: LmiDistanceTConstructCopy}
		{parent: LmiDistanceT}
		{description: Construct a new LmiDistanceT object as a copy of an
			existing one.}
		{prototype: LmiDistanceT* LmiDistanceTConstructCopy(LmiDistanceT* dst, const LmiDistanceT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiDistanceT object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiDistanceT object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiDistanceT construction will not fail.}
	}

	{function:
		{name: LmiDistanceTDestruct}
		{parent: LmiDistanceT}
		{description: Destruct an LmiDistanceT object.}
		{prototype: void LmiDistanceTDestruct(LmiDistanceT* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiDistanceT object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiDistanceTAssign}
		{parent: LmiDistanceT}
		{description: Assign the value of one LmiDistanceT object to another one.}
		{prototype: LmiDistanceT* LmiDistanceTAssign(LmiDistanceT* dst, const LmiDistanceT* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiDistanceT object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiDistanceT object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiDistanceT assignment will not fail.}
	}
   
	{function:
		{name: LmiDistanceTEqual}
		{parent: LmiDistanceT}
		{description: Compare the values of two LmiDistanceT objects for
			equality.}
		{prototype: LmiBool LmiDistanceTEqual(const LmiDistanceT* a, const LmiDistanceT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiDistanceT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiDistanceT object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiDistanceTLess}
		{parent: LmiDistanceT}
		{description: Compare the values of two LmiDistanceT objects for
			ordering.}
		{prototype: LmiBool LmiDistanceTLess(const LmiDistanceT* a, const LmiDistanceT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiDistanceT object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiDistanceT object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiDistanceTSwap}
		{parent: LmiDistanceT}
		{description: Swap the contents of two LmiDistanceT objects.}
		{prototype: LmiBool LmiDistanceTSwap(LmiDistanceT* a, LmiDistanceT* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiDistanceT object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiDistanceT object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiDistanceT swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiDistanceT)


/**
   {type: 
   {name: LmiVoidPtr}
   {parent: BasicTypes}
   {description: A generic object pointer.}}
*/

/**
	{function:
		{name: LmiVoidPtrConstruct}
		{parent: LmiVoidPtr}
		{description: Construct a default instance of an LmiVoidPtr object.}
		{prototype: LmiVoidPtr* LmiVoidPtrConstruct(LmiVoidPtr* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiVoidPtr object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiVoidPtr object is initialized with the value {code:((void*)0)} ({code:NULL}).
			LmiVoidPtr construction will not fail.}
	}

	{function:
		{name: LmiVoidPtrConstructCopy}
		{parent: LmiVoidPtr}
		{description: Construct a new LmiVoidPtr object as a copy of an
			existing one.}
		{prototype: LmiVoidPtr* LmiVoidPtrConstructCopy(LmiVoidPtr* dst, const LmiVoidPtr* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiVoidPtr object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiVoidPtr object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiVoidPtr construction will not fail.}
	}

	{function:
		{name: LmiVoidPtrDestruct}
		{parent: LmiVoidPtr}
		{description: Destruct an LmiVoidPtr object.}
		{prototype: void LmiVoidPtrDestruct(LmiVoidPtr* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiVoidPtr object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiVoidPtrAssign}
		{parent: LmiVoidPtr}
		{description: Assign the value of one LmiVoidPtr object to another one.}
		{prototype: LmiVoidPtr* LmiVoidPtrAssign(LmiVoidPtr* dst, const LmiVoidPtr* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiVoidPtr object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiVoidPtr object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiVoidPtr assignment will not fail.}
	}
   
	{function:
		{name: LmiVoidPtrEqual}
		{parent: LmiVoidPtr}
		{description: Compare the values of two LmiVoidPtr objects for
			equality.}
		{prototype: LmiBool LmiVoidPtrEqual(const LmiVoidPtr* a, const LmiVoidPtr* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiVoidPtr object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiVoidPtr object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiVoidPtrLess}
		{parent: LmiVoidPtr}
		{description: Compare the values of two LmiVoidPtr objects for
			ordering.}
		{prototype: LmiBool LmiVoidPtrLess(const LmiVoidPtr* a, const LmiVoidPtr* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiVoidPtr object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiVoidPtr object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiVoidPtrSwap}
		{parent: LmiVoidPtr}
		{description: Swap the contents of two LmiVoidPtr objects.}
		{prototype: LmiBool LmiVoidPtrSwap(LmiVoidPtr* a, LmiVoidPtr* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiVoidPtr object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiVoidPtr object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiVoidPtr swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiVoidPtr)

/**
   {type:
     {name: LmiWideChar}
     {parent: BasicTypes}
     {description: Wide character type, holding UCS4 (32-bit) Unicode characters.}
   }
*/

Declare_LmiBasicType(LmiWideChar)


/**
   {type:
     {name: LmiFloat32}
     {parent: BasicTypes}
     {description: Basic 32-bit single precision floating point type.}
   }
*/

/**
	{function:
		{name: LmiFloat32Construct}
		{parent: LmiFloat32}
		{description: Construct a default instance of an LmiFloat32 object.}
		{prototype: LmiFloat32* LmiFloat32Construct(LmiFloat32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiFloat32 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiFloat32 object is initialized with the value 0.
			LmiFloat32 construction will not fail.}
	}

	{function:
		{name: LmiFloat32ConstructCopy}
		{parent: LmiFloat32}
		{description: Construct a new LmiFloat32 object as a copy of an
			existing one.}
		{prototype: LmiFloat32* LmiFloat32ConstructCopy(LmiFloat32* dst, const LmiFloat32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiFloat32 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiFloat32 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiFloat32 construction will not fail.}
	}

	{function:
		{name: LmiFloat32Destruct}
		{parent: LmiFloat32}
		{description: Destruct an LmiFloat32 object.}
		{prototype: void LmiFloat32Destruct(LmiFloat32* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiFloat32 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiFloat32Assign}
		{parent: LmiFloat32}
		{description: Assign the value of one LmiFloat32 object to another one.}
		{prototype: LmiFloat32* LmiFloat32Assign(LmiFloat32* dst, const LmiFloat32* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiFloat32 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiFloat32 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiFloat32 assignment will not fail.}
	}
   
	{function:
		{name: LmiFloat32Equal}
		{parent: LmiFloat32}
		{description: Compare the values of two LmiFloat32 objects for
			equality.}
		{prototype: LmiBool LmiFloat32Equal(const LmiFloat32* a, const LmiFloat32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat32 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiFloat32Less}
		{parent: LmiFloat32}
		{description: Compare the values of two LmiFloat32 objects for
			ordering.}
		{prototype: LmiBool LmiFloat32Less(const LmiFloat32* a, const LmiFloat32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat32 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat32 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiFloat32Swap}
		{parent: LmiFloat32}
		{description: Swap the contents of two LmiFloat32 objects.}
		{prototype: LmiBool LmiFloat32Swap(LmiFloat32* a, LmiFloat32* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat32 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat32 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiFloat32 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiFloat32)


/**
   {type:
     {name: LmiFloat64}
     {parent: BasicTypes}
     {description: Basic 64-bit double precision floating point type.}
   }
*/

/**
	{function:
		{name: LmiFloat64Construct}
		{parent: LmiFloat64}
		{description: Construct a default instance of an LmiFloat64 object.}
		{prototype: LmiFloat64* LmiFloat64Construct(LmiFloat64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiFloat64 object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The LmiFloat64 object is initialized with the value 0.
			LmiFloat64 construction will not fail.}
	}

	{function:
		{name: LmiFloat64ConstructCopy}
		{parent: LmiFloat64}
		{description: Construct a new LmiFloat64 object as a copy of an
			existing one.}
		{prototype: LmiFloat64* LmiFloat64ConstructCopy(LmiFloat64* dst, const LmiFloat64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiFloat64 object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing LmiFloat64 object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: LmiFloat64 construction will not fail.}
	}

	{function:
		{name: LmiFloat64Destruct}
		{parent: LmiFloat64}
		{description: Destruct an LmiFloat64 object.}
		{prototype: void LmiFloat64Destruct(LmiFloat64* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the LmiFloat64 object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: LmiFloat64Assign}
		{parent: LmiFloat64}
		{description: Assign the value of one LmiFloat64 object to another one.}
		{prototype: LmiFloat64* LmiFloat64Assign(LmiFloat64* dst, const LmiFloat64* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the LmiFloat64 object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing LmiFloat64 object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: LmiFloat64 assignment will not fail.}
	}
   
	{function:
		{name: LmiFloat64Equal}
		{parent: LmiFloat64}
		{description: Compare the values of two LmiFloat64 objects for
			equality.}
		{prototype: LmiBool LmiFloat64Equal(const LmiFloat64* a, const LmiFloat64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat64 object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: LmiFloat64Less}
		{parent: LmiFloat64}
		{description: Compare the values of two LmiFloat64 objects for
			ordering.}
		{prototype: LmiBool LmiFloat64Less(const LmiFloat64* a, const LmiFloat64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat64 object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat64 object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: LmiFloat64Swap}
		{parent: LmiFloat64}
		{description: Swap the contents of two LmiFloat64 objects.}
		{prototype: LmiBool LmiFloat64Swap(LmiFloat64* a, LmiFloat64* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first LmiFloat64 object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second LmiFloat64 object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: LmiFloat64 swapping will not fail.}
	}
*/
Declare_LmiBasicType(LmiFloat64)

LMI_END_EXTERN_C

#endif /* LMI_TYPES_H_ */
