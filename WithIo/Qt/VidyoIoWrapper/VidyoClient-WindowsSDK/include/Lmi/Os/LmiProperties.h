/**
{file:
	{name: LmiProperties.h}
	{description: Interface definition for a properties class.}
	{copyright:
		(c) 2014-2016 Vidyo, Inc.,
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

#if !defined(LMI_PROPERTIES_H_)
#define LMI_PROPERTIES_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiString.h>
#include <Lmi/Utils/LmiMap.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiStack.h>
#include <Lmi/Utils/LmiStringVector.h>

#include <Lmi/Os/LmiTime.h>
#include <Lmi/Os/LmiSharedPtr.h>
#include <Lmi/Os/LmiMutex.h>

LMI_BEGIN_EXTERN_C

struct LmiProperties_;

/**
{type:
	{name: LmiPropertyValueType}
	{parent: LmiPropertyValue}
	{include: Lmi/Os/LmiProperties.h}
	{description: Describes the type of value stored in an LmiPropertyValue.}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Bool}
		{description: An LmiBool.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Int}
		{description: An LmiInt.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Int16}
		{description: An LmiInt16.}
	}
  	{value:
 		{name: LMI_PROPERTYVALUE_TYPE_Int64}
 		{description: An LmiInt64.}
 	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Uint}
		{description: An LmiUint.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Uint16}
		{description: An LmiUint16.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_SizeT}
		{description: An LmiSizeT.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Float32}
		{description: An LmiFloat32.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Float64}
		{description: An LmiFloat64.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Time}
		{description: An LmiTime.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_VoidPtr}
		{description: An LmiVoidPtr.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_String}
		{description: An LmiString.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Properties}
		{description: An LmiProperty.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_Vector}
		{description: An LmiVector(LmiPropertyValue).}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_WeakVoidPtr}
		{description: An LmiWeakVoidPtr.}
	}
	{value:
		{name: LMI_PROPERTYVALUE_TYPE_SharedVoidPtr}
		{description: An LmiSharedVoidPtr.}
	}
}
*/
typedef enum {
	LMI_PROPERTYVALUE_TYPE_Bool,
	LMI_PROPERTYVALUE_TYPE_Int,
	LMI_PROPERTYVALUE_TYPE_Int16,
	LMI_PROPERTYVALUE_TYPE_Int64,
	LMI_PROPERTYVALUE_TYPE_Uint,
	LMI_PROPERTYVALUE_TYPE_Uint16,
	LMI_PROPERTYVALUE_TYPE_SizeT,
	LMI_PROPERTYVALUE_TYPE_Float32,
	LMI_PROPERTYVALUE_TYPE_Float64,
	LMI_PROPERTYVALUE_TYPE_Time,
	LMI_PROPERTYVALUE_TYPE_VoidPtr,
	LMI_PROPERTYVALUE_TYPE_String,
	LMI_PROPERTYVALUE_TYPE_Properties,
	LMI_PROPERTYVALUE_TYPE_Vector,
	LMI_PROPERTYVALUE_TYPE_WeakVoidPtr,
	LMI_PROPERTYVALUE_TYPE_SharedVoidPtr
} LmiPropertyValueType;

/* Forward declare LmiPropertyValue, so that LmiVector(LmiPropertyValue) can be declared before LmiPropertyValue (which contains
 an LmiVector(LmiPropertyValue))is defined. */
typedef struct LmiPropertyValue_ LmiPropertyValue;

/* Declare the LmiVector without its header inlines since they require LmiPropertyValue to be fully defined. The header inlines
 are defined later, after LmiPropertyValue and its methods are declared. See Declare_LmiVectorInlines(LmiPropertyValue) later in the file. */
Declare_LmiVector_NoInlines(LmiPropertyValue)

/**
{type:
	{name: LmiPropertyValue}
	{parent: LmiProperties}
	{include: Lmi/Os/LmiProperties.h}
	{description: Describes a property value. A property value can be any of the various types described by LmiPropertyValueType.}
}
*/
struct LmiPropertyValue_ {
	LmiBool settable;
	LmiPropertyValueType type;
	union {
		LmiBool b;
		LmiInt i;
		LmiInt16 i16;
		LmiInt64 i64;
		LmiUint ui;
		LmiUint16 ui16;
		LmiSizeT sz;
		LmiFloat32 f32;
		LmiFloat64 f64;
		LmiTime t;
		LmiVoidPtr vp;
		LmiString s;
		struct LmiProperties_* p;
		LmiVector(LmiPropertyValue) vec;
		LmiSharedVoidPtr sp;
		LmiWeakVoidPtr wp;
	} u;
};

/**
{function:
	{name: LmiPropertyValueConstructBool}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiBool property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructBool(LmiPropertyValue* x, LmiBool b, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: b}
		{description: The LmiBool to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructBool(LmiPropertyValue* x, LmiBool b, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructInt}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiInt property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructInt(LmiPropertyValue* x, LmiInt i, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i}
		{description: The LmiInt to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructInt(LmiPropertyValue* x, LmiInt i, LmiBool settable);
/**
{function:
	{name: LmiPropertyValueConstructInt16}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiInt16 property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructInt16(LmiPropertyValue* x, LmiInt16 i16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i16}
		{description: The LmiInt16 to assign to the property value.}
	}
  	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructInt16(LmiPropertyValue* x, LmiInt16 i16, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructInt64}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiInt64 property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructInt64(LmiPropertyValue* x, LmiInt64 i64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i64}
		{description: The LmiInt64 to assign to the property value.}
	}
  	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructInt64(LmiPropertyValue* x, LmiInt64 i64, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructUint}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiUint property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructUint(LmiPropertyValue* x, LmiUint ui, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: ui}
		{description: The LmiUint to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructUint(LmiPropertyValue* x, LmiUint ui, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructUint16}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiUint16 property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructUint16(LmiPropertyValue* x, LmiUint16 ui16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: ui16}
		{description: The LmiUint16 to assign to the property value.}
	}
  	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructUint16(LmiPropertyValue* x, LmiUint16 ui16, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructSizeT}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiSizeT property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructSizeT(LmiPropertyValue* x, LmiSizeT sz, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: sz}
		{description: The LmiSizeT to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructSizeT(LmiPropertyValue* x, LmiSizeT sz, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructFloat32}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiFloat32 property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructFloat32(LmiPropertyValue* x, LmiFloat32 f32, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: f32}
		{description: The LmiFloat32 to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructFloat32(LmiPropertyValue* x, LmiFloat32 f32, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructFloat64}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiFloat64 property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructFloat64(LmiPropertyValue* x, LmiFloat64 f64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: f64}
		{description: The LmiFloat64 to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructFloat64(LmiPropertyValue* x, LmiFloat64 f64, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructTime}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiTime property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructTime(LmiPropertyValue* x, LmiTime  t, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: t}
		{description: The LmiTime to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructTime(LmiPropertyValue* x, LmiTime  t, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructVoidPtr}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiVoidPtr property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructVoidPtr(LmiPropertyValue* x, LmiVoidPtr vp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: vp}
		{description: The LmiVoidPtr to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructVoidPtr(LmiPropertyValue* x, LmiVoidPtr vp, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructString}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiString property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructString(LmiPropertyValue* x, const LmiString* s, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: s}
		{description: The LmiString to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructString(LmiPropertyValue* x, const LmiString* s, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructStringCStr}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiString property value from a C string.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructStringCStr(LmiPropertyValue* x, const char* s, LmiBool settable, LmiAllocator* a)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: s}
		{description: The C string to assign to the LmiString property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{parameter:
		{name: a}
		{description: An allocator.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructStringCStr(LmiPropertyValue* x, const char* str, LmiBool settable, LmiAllocator* a);

/**
{function:
	{name: LmiPropertyValueConstructProperties}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiProperties property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructProperties(LmiPropertyValue* x, const LmiProperties* p, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: p}
		{description: The LmiProperties to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructProperties(LmiPropertyValue* x, const struct LmiProperties_* p, LmiBool settable);


/**
{function:
	{name: LmiPropertyValueConstructVector}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiVector(LmiPropertyValue) property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructVector(LmiPropertyValue* x, const LmiVector(LmiPropertyValue)* v, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: v}
		{description: The LmiVector(LmiPropertyValue) to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiPropertyValueAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructVector(LmiPropertyValue* x, const LmiVector(LmiPropertyValue)* p, LmiBool settable);



/**
{function:
	{name: LmiPropertyValueConstructSharedVoidPtr}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiSharedVoidPtr property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructSharedVoidPtr(LmiPropertyValue* x, const LmiSharedVoidPtr* sp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: sp}
		{description: The LmiSharedVoidPtr to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiSharedVoidPtrAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructSharedVoidPtr(LmiPropertyValue* x, const LmiSharedVoidPtr* sp, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructWeakVoidPtr}
	{parent: LmiPropertyValue}
	{description: Constructs an LmiSharedVoidPtr property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructWeakVoidPtr(LmiPropertyValue* x, const LmiWeakVoidPtr* wp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: wp}
		{description: The LmiWeakVoidPtr to assign to the property value.}
	}
	{parameter:
		{name: settable}
		{description: Defines whether or not LmiWeakVoidPtrAssign will succeed on the property value.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructWeakVoidPtr(LmiPropertyValue* x, const LmiWeakVoidPtr* wp, LmiBool settable);

/**
{function:
	{name: LmiPropertyValueConstructCopy}
	{parent: LmiPropertyValue}
	{description: Constructs a property value from another property value.}
	{prototype: LmiPropertyValue* LmiPropertyValueConstructCopy(LmiPropertyValue* x, const LmiPropertyValue* y)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: y}
		{description: A property value whose value to assign to {code:x}.}
	}
	{return: Returns a pointer to the constructed property value or NULL on error.}
}
*/
LmiPropertyValue* LmiPropertyValueConstructCopy(LmiPropertyValue* x, const LmiPropertyValue* y);

/**
{function:
	{name: LmiPropertyValueDestruct}
	{parent: LmiPropertyValue}
	{description: Destructs a property value.}
	{prototype: void LmiPropertyValueDestruct(LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
}
*/
void LmiPropertyValueDestruct(LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueAssign}
	{parent: LmiPropertyValue}
	{description: Assigns one property value to another.}
	{prototype: LmiPropertyValue* LmiPropertyValueAssign(LmiPropertyValue* x, const LmiPropertyValue* y)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: y}
		{description: A property value whose value to assign to {code:x}.}
	}
	{return: Returns a pointer to the assigned-to property value or NULL if {code:x} is not settable or some other error occurred.}
}
*/
LmiPropertyValue* LmiPropertyValueAssign(LmiPropertyValue* x, const LmiPropertyValue* y);

/**
{function:
	{name: LmiPropertyValueEqual}
	{parent: LmiPropertyValue}
	{description: Determines whether two property values are equal.}
	{prototype: LmiBool LmiPropertyValueEqual(const LmiPropertyValue* x, const LmiPropertyValue* y)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: y}
		{description: A property value.}
	}
	{return: Return LMI_TRUE if the properties are of the same type and value, or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertyValueEqual(const LmiPropertyValue* x, const LmiPropertyValue* y);

/**
{function:
	{name: LmiPropertyValueIsSettable}
	{parent: LmiPropertyValue}
	{description: Determines whether or not a property value is settable.}
	{prototype: LmiBool LmiPropertyValueIsSettable(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns LMI_TRUE if the property value is settable or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertyValueIsSettable(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetType}
	{parent: LmiPropertyValue}
	{description: Gets the property value type of a property value.}
	{prototype: LmiPropertyValueType LmiPropertyValueGetType(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns the type of the property value.}
}
*/
LmiPropertyValueType LmiPropertyValueGetType(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetBool}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiBool of a property value.}
	{prototype: const LmiBool* LmiPropertyValueGetBool(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiBool of the property value on success, or NULL if the type of the property value is not an LmiBool.}
}
*/
const LmiBool* LmiPropertyValueGetBool(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetInt}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiInt of a property value.}
	{prototype: const LmiInt* LmiPropertyValueGetInt(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiInt of the property value on success, or NULL if the type of the property value is not an LmiInt.}
}
*/
const LmiInt* LmiPropertyValueGetInt(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetInt16}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiInt16 of a property value.}
	{prototype: const LmiInt16* LmiPropertyValueGetInt16(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiInt16 of the property value on success, or NULL if the type of the property value is not an LmiInt16.}
}
*/
const LmiInt16* LmiPropertyValueGetInt16(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetInt64}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiInt64 of a property value.}
	{prototype: const LmiInt64* LmiPropertyValueGetInt64(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiInt64 of the property value on success, or NULL if the type of the property value is not an LmiInt64.}
}
*/
const LmiInt64* LmiPropertyValueGetInt64(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetUint}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiUint of a property value.}
	{prototype: const LmiUint* LmiPropertyValueGetUint(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiUint of the property value on success, or NULL if the type of the property value is not an LmiUint.}
}
*/
const LmiUint* LmiPropertyValueGetUint(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetUint16}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiUint16 of a property value.}
	{prototype: const LmiUint16* LmiPropertyValueGetUint16(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiUint16 of the property value on success, or NULL if the type of the property value is not an LmiUint16.}
}
*/
const LmiUint16* LmiPropertyValueGetUint16(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetSizeT}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiSizeT of a property value.}
	{prototype: const LmiSizeT* LmiPropertyValueGetSizeT(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiSizeT of the property value on success, or NULL if the type of the property value is not an LmiSizeT.}
}
*/
const LmiSizeT* LmiPropertyValueGetSizeT(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetFloat32}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiFloat32 of a property value.}
	{prototype: const LmiFloat32* LmiPropertyValueGetFloat32(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiFloat32 of the property value on success, or NULL if the type of the property value is not an LmiFloat32.}
}
*/
const LmiFloat32* LmiPropertyValueGetFloat32(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetFloat64}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiFloat64 of a property value.}
	{prototype: const LmiFloat64* LmiPropertyValueGetFloat64(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiFloat64 of the property value on success, or NULL if the type of the property value is not an LmiFloat64.}
}
*/
const LmiFloat64* LmiPropertyValueGetFloat64(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetTime}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiTime of a property value.}
	{prototype: const LmiTime* LmiPropertyValueGetTime(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiTime of the property value on success, or NULL if the type of the property value is not an LmiTime.}
}
*/
const LmiTime* LmiPropertyValueGetTime(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetVoidPtr}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiVoidPtr of a property value.}
	{prototype: const LmiVoidPtr* LmiPropertyValueGetVoidPtr(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiVoidPtr.}
}
*/
const LmiVoidPtr* LmiPropertyValueGetVoidPtr(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetString}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiString of a property value.}
	{prototype: const LmiString* LmiPropertyValueGetString(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiString of the property value on success, or NULL if the type of the property value is not an LmiString.}
}
*/
const LmiString* LmiPropertyValueGetString(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetProperties}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiProperties of a property value.}
	{prototype: const LmiProperties* LmiPropertyValueGetProperties(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiProperties of the property value on success, or NULL if the type of the property value is not an LmiProperties.}
}
*/
const struct LmiProperties_* LmiPropertyValueGetProperties(const LmiPropertyValue* x);


/**
{function:
	{name: LmiPropertyValueGetVector}
	{parent: LmiPropertyValue}
	{description: Gets a LmiVector(LmiPropertyValue) pointer to an LmiVector(LmiPropertyValue) of a property value.}
	{prototype: const LmiVector(LmiPropertyValue)* LmiPropertyValueGetVector(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiVector(LmiPropertyValue) of the property value on success, or NULL if the type of the property value is not an LmiVector(LmiPropertyValue).}
}
*/
const LmiVector(LmiPropertyValue)* LmiPropertyValueGetVector(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueToBool}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiBool.}
	{prototype: LmiBool* LmiPropertyValueToBool(const LmiPropertyValue* x, LmiBool* b)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: b}
		{description: An LmiBool to hold a copy of the property's value.}
	}
	{return: Returns {code:b} on success, or NULL if the type of the property value is not an LmiBool or any other error occurs.}
}
*/

/**
{function:
	{name: LmiPropertyValueGetSharedVoidPtr}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiSharedVoidPtr of a property value.}
	{prototype: const LmiSharedVoidPtr* LmiPropertyValueGetSharedVoidPtr(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiSharedVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiSharedVoidPtr.}
}
*/
const LmiSharedVoidPtr* LmiPropertyValueGetSharedVoidPtr(const LmiPropertyValue* x);

/**
{function:
	{name: LmiPropertyValueGetWeakVoidPtr}
	{parent: LmiPropertyValue}
	{description: Gets a const pointer to an LmiWeakVoidPtr of a property value.}
	{prototype: const LmiWeakVoidPtr* LmiPropertyValueGetWeakVoidPtr(const LmiPropertyValue* x)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{return: Returns a pointer to an LmiWeakVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiWeakVoidPtr.}
}
*/
const LmiWeakVoidPtr* LmiPropertyValueGetWeakVoidPtr(const LmiPropertyValue* x);

LmiBool* LmiPropertyValueToBool(const LmiPropertyValue* x, LmiBool* b);

/**
{function:
	{name: LmiPropertyValueToInt}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiInt.}
	{prototype: LmiInt* LmiPropertyValueToInt(const LmiPropertyValue* x, LmiInt* i)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i}
		{description: An LmiInt to hold a copy of the property's value.}
	}
	{return: Returns {code:i} on success, or NULL if the type of the property value is not an LmiInt or any other error occurs.}
}
*/
LmiInt* LmiPropertyValueToInt(const LmiPropertyValue* x, LmiInt* i);

/**
{function:
	{name: LmiPropertyValueToInt16}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiInt16.}
	{prototype: LmiInt16* LmiPropertyValueToInt16(const LmiPropertyValue* x, LmiInt16* i16)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i16}
		{description: An LmiInt16 to hold a copy of the property's value.}
	}
	{return: Returns {code:i16} on success, or NULL if the type of the property value is not an LmiInt16 or any other error occurs.}
}
*/
LmiInt16* LmiPropertyValueToInt16(const LmiPropertyValue* x, LmiInt16* i16);

/**
{function:
	{name: LmiPropertyValueToInt64}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiInt64.}
	{prototype: LmiInt64* LmiPropertyValueToInt64(const LmiPropertyValue* x, LmiInt64* i64)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: i64}
		{description: An LmiInt64 to hold a copy of the property's value.}
	}
	{return: Returns {code:i64} on success, or NULL if the type of the property value is not an LmiInt64 or any other error occurs.}
}
*/
LmiInt64* LmiPropertyValueToInt64(const LmiPropertyValue* x, LmiInt64* i64);

/**
{function:
	{name: LmiPropertyValueToUint}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiUint.}
	{prototype: LmiUint* LmiPropertyValueToUint(const LmiPropertyValue* x, LmiUint* ui)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: ui}
		{description: An LmiUint to hold a copy of the property's value.}
	}
	{return: Returns {code:ui} on success, or NULL if the type of the property value is not an LmiUint or any other error occurs.}
}
*/
LmiUint* LmiPropertyValueToUint(const LmiPropertyValue* x, LmiUint* ui);

/**
{function:
	{name: LmiPropertyValueToUint16}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiUint16.}
	{prototype: LmiUint16* LmiPropertyValueToUint16(const LmiPropertyValue* x, LmiUint16* ui16)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: ui16}
		{description: An LmiUint16 to hold a copy of the property's value.}
	}
	{return: Returns {code:ui16} on success, or NULL if the type of the property value is not an LmiUint16 or any other error occurs.}
}
*/
LmiUint16* LmiPropertyValueToUint16(const LmiPropertyValue* x, LmiUint16* ui16);

/**
{function:
	{name: LmiPropertyValueToSizeT}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiSizeT.}
	{prototype: LmiSizeT* LmiPropertyValueToSizeT(const LmiPropertyValue* x, LmiSizeT* sz)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: sz}
		{description: An LmiSizeT to hold a copy of the property's value.}
	}
	{return: Returns {code:sz} on success, or NULL if the type of the property value is not an LmiSizeT or any other error occurs.}
}
*/
LmiSizeT* LmiPropertyValueToSizeT(const LmiPropertyValue* x, LmiSizeT* sz);

/**
{function:
	{name: LmiPropertyValueToFloat32}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiFloat32.}
	{prototype: LmiFloat32* LmiPropertyValueToFloat32(const LmiPropertyValue* x, LmiFloat32* f32)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: f32}
		{description: An LmiFloat32 to hold a copy of the property's value.}
	}
	{return: Returns {code:f32} on success, or NULL if the type of the property value is not an LmiFloat32 or any other error occurs.}
}
*/
LmiFloat32* LmiPropertyValueToFloat32(const LmiPropertyValue* x, LmiFloat32* f32);

/**
{function:
	{name: LmiPropertyValueToFloat64}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiFloat64.}
	{prototype: LmiFloat64* LmiPropertyValueToFloat64(const LmiPropertyValue* x, LmiFloat64* f64)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: f64}
		{description: An LmiFloat64 to hold a copy of the property's value.}
	}
	{return: Returns {code:f64} on success, or NULL if the type of the property value is not an LmiFloat64 or any other error occurs.}
}
*/
LmiFloat64* LmiPropertyValueToFloat64(const LmiPropertyValue* x, LmiFloat64* f64);

/**
{function:
	{name: LmiPropertyValueToTime}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiTime.}
	{prototype: LmiTime* LmiPropertyValueToTime(const LmiPropertyValue* x, LmiTime* t)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: t}
		{description: An LmiTime to hold a copy of the property's value.}
	}
	{return: Returns {code:t} on success, or NULL if the type of the property value is not an LmiTime or any other error occurs.}
}
*/
LmiTime* LmiPropertyValueToTime(const LmiPropertyValue* x, LmiTime* t);

/**
{function:
	{name: LmiPropertyValueToVoidPtr}
	{parent: LmiPropertyValue}
	{description: Converts a property value to a void pointer.}
	{prototype: LmiVoidPtr* LmiPropertyValueToVoidPtr(const LmiPropertyValue* x, LmiVoidPtr* vp)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: vp}
		{description: An LmiVoidPtr to hold a copy of the property's value. }
	}
	{return: Returns {code:vp} on success, or NULL if the type of the property value is not an LmiVoidPtr or any other error occurs.}
}
*/
LmiVoidPtr* LmiPropertyValueToVoidPtr(const LmiPropertyValue* x, LmiVoidPtr* vp);

/**
{function:
	{name: LmiPropertyValueToString}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiString.}
	{prototype: LmiString* LmiPropertyValueToString(const LmiPropertyValue* x, LmiString* s)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: s}
		{description: An LmiString to hold a copy of the property's value.}
	}
	{return: Returns {code:s} on success, or NULL if the type of the property value is not an LmiString or any other error occurs.}
}
*/
LmiString* LmiPropertyValueToString(const LmiPropertyValue* x, LmiString* s);

/**
{function:
	{name: LmiPropertyValueToProperties}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiProperties.}
	{prototype: LmiProperties* LmiPropertyValueToProperties(const LmiPropertyValue* x, LmiProperties* p)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: p}
		{description: An LmiProperties to hold a copy of the property's value.}
	}
	{return: Returns {code:s} on success, or NULL if the type of the property value is not an LmiProperties or any other error occurs.}
}
*/
struct LmiProperties_* LmiPropertyValueToProperties(const LmiPropertyValue* x, struct LmiProperties_* p);

/**
{function:
	{name: LmiPropertyValueToVector}
	{parent: LmiPropertyValue}
	{description: Converts a property value to an LmiVector(LmiPropertyValue).}
	{prototype: LmiVector(LmiPropertyValue)* LmiPropertyValueToVector(const LmiPropertyValue* x, LmiVector(LmiPropertyValue)* v)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: v}
		{description: An LmiVector(LmiPropertyValue) to hold a copy of the property's value.}
	}
	{return: Returns {code:v} on success, or NULL if the type of the property value is not an LmiVector(LmiPropertyValue) or any other error occurs.}
}
*/
LmiVector(LmiPropertyValue)* LmiPropertyValueToVector(const LmiPropertyValue* x, LmiVector(LmiPropertyValue)* p);

/**
{function:
	{name: LmiPropertyValueToSharedVoidPtr}
	{parent: LmiPropertyValue}
	{description: Converts a property value to a void pointer.}
	{prototype: LmiSharedVoidPtr* LmiPropertyValueToSharedVoidPtr(const LmiPropertyValue* x, LmiSharedVoidPtr* sp)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: sp}
		{description: An LmiSharedVoidPtr to hold a copy of the property's value. }
	}
	{return: Returns {code:sp} on success, or NULL if the type of the property value is not an LmiSharedVoidPtr or any other error occurs.}
}
*/
LmiSharedVoidPtr* LmiPropertyValueToSharedVoidPtr(const LmiPropertyValue* x, LmiSharedVoidPtr* sp);

/**
{function:
	{name: LmiPropertyValueToWeakVoidPtr}
	{parent: LmiPropertyValue}
	{description: Converts a property value to a void pointer.}
	{prototype: LmiWeakVoidPtr* LmiPropertyValueToWeakVoidPtr(const LmiPropertyValue* x, LmiWeakVoidPtr* wp)}
	{parameter:
		{name: x}
		{description: A property value.}
	}
	{parameter:
		{name: wp}
		{description: An LmiWeakVoidPtr to hold a copy of the property's value. }
	}
	{return: Returns {code:wp} on success, or NULL if the type of the property value is not an LmiWeakVoidPtr or any other error occurs.}
}
*/
LmiWeakVoidPtr* LmiPropertyValueToWeakVoidPtr(const LmiPropertyValue* x, LmiWeakVoidPtr* wp);

/* Generate the header inlines for the LmiVector(LmiPropertyValue) after LmiPropertyValue and its methods are declared */
Declare_LmiVector_Inlines(LmiPropertyValue)

Declare_LmiVectorEqual(LmiPropertyValue)

struct LmiPropertyListener_;

/**
{callback:
	{name: LmiPropertyListenerCallback}
	{parent: LmiPropertyListener}
	{description: Describes a callback called by LmiPropertyListener to notify an application of a property change. }
	{prototype: void (*LmiPropertyListenerCallback)(const LmiPropertyListener* x, LmiProperties* properties, const LmiString* name, const LmiPropertyValue* oldValue, const LmiPropertyValue* newValue)}
	{parameter:
		{name: x}
		{description: The property listener. }
	}
	{parameter:
		{name: properties}
		{description: The property set containing the property that triggered the listener. }
	}
	{parameter:
		{name: name}
		{description: The name of the property that triggered the listener. }
	}
	{parameter:
		{name: oldValue}
		{description: The old property value. On LMI_PROPERTYLISTENER_TRIGGER_Before calls, this is the current value of the property, unless the property was added, in which case this parameter is NULL. On LMI_PROPERTYLISTENER_TRIGGER_After calls, this is the current value of the property, or NULL if the property was added or removed.}
	}
	{parameter:
		{name: newValue}
		{description: The new property value. On LMI_PROPERTYLISTENER_TRIGGER_Before calls, this is the value the property will have subsequently, or NULL, if the property is being removed. On LMI_PROPERTYLISTENER_TRIGGER_After calls, this is the current value of the property, or NULL if the property was removed.}
	}
}
*/
typedef void (*LmiPropertyListenerCallback)(const struct LmiPropertyListener_ * x, struct LmiProperties_* properties, const LmiString* name, const LmiPropertyValue* oldValue, const LmiPropertyValue* newValue);

/**
{type:
	{name: LmiPropertyListenerTrigger}
	{parent: LmiPropertyListener}
	{include: Lmi/Os/LmiProperties.h}
	{description: Describes the trigger for a property listener to fire.}
	{value:
		{name: LMI_PROPERTYLISTENER_TRIGGER_Before}
		{description: Specifies that the listener should be called prior to the property value changing.}
	}
	{value:
		{name: LMI_PROPERTYLISTENER_TRIGGER_After}
		{description: Specifies that the listener should be called after the property value is changed.}
	}
}
*/
typedef enum {
	LMI_PROPERTYLISTENER_TRIGGER_Before,
	LMI_PROPERTYLISTENER_TRIGGER_After
} LmiPropertyListenerTrigger;

/**
{type:
	{name: LmiPropertyListener}
	{parent: LmiProperties}
	{include: Lmi/Os/LmiProperties.h}
	{description: Describes a property listener.  A property listener allows and application to be notified whenever a property is added, removed, or its value is changed.  A listener can be configured to trigger before the add, remove, or value change takes place or after (see LmiPropertyListenerTrigger for details).  A listener can be scoped to trigger on an individual property of the property set by specifying the property's name or on all properties of the property set by setting the name parameter to NULL.}
}
*/
typedef struct LmiPropertyListener_ {
	LmiBool all;
	LmiString name;
	LmiPropertyListenerTrigger trigger;
	LmiPropertyListenerCallback cb;
	LmiVoidPtr data;
} LmiPropertyListener;

/**
{function:
	{name: LmiPropertyListenerConstruct}
	{parent: LmiPropertyListener}
	{description: Constructs a property listener.}
	{prototype: LmiPropertyListener* LmiPropertyListenerConstruct(LmiPropertyListener* x, LmiPropertyListenerTrigger trigger, const LmiString* name, LmiPropertyListenerCallback cb, LmiVoidPtr data)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{parameter:
		{name: trigger}
		{description: The trigger to listen for.}
	}
	{parameter:
		{name: name}
		{description: The name of the property to listen to or NULL to listener to all properties.}
	}
	{parameter:
		{name: cb}
		{description: The callback to call when the property is changed.}
	}
	{parameter:
		{name: data}
		{description: A user data pointer.}
	}
	{return: Returns a pointer to the constructed object or NULL on error.}
}
*/
LmiPropertyListener* LmiPropertyListenerConstruct(LmiPropertyListener* x, LmiPropertyListenerTrigger trigger, const LmiString* name, LmiPropertyListenerCallback cb, LmiVoidPtr data);

/**
{function:
	{name: LmiPropertyListenerConstructCStr}
	{parent: LmiPropertyListener}
	{description: Constructs a property listener.}
	{prototype: LmiPropertyListener* LmiPropertyListenerConstructCStr(LmiPropertyListener* x, LmiPropertyListenerTrigger trigger, const char* name, LmiPropertyListenerCallback cb, LmiVoidPtr data, LmiAllocator* a)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{parameter:
		{name: trigger}
		{description: The trigger to listen for.}
	}
	{parameter:
		{name: name}
		{description: The name of the property to listen to or NULL to listen to all properties.}
	}
	{parameter:
		{name: cb}
		{description: The callback to call when the property is changed.}
	}
	{parameter:
		{name: data}
		{description: A user data pointer.}
	}
	{parameter:
		{name: a}
		{description: An allocator.}
	}
	{return: Returns a pointer to the constructed object or NULL on error.}
	{note: Path notation cannot be used in the property listeners.}
}
*/
LmiPropertyListener* LmiPropertyListenerConstructCStr(LmiPropertyListener* x, LmiPropertyListenerTrigger trigger, const char* name,
  LmiPropertyListenerCallback cb, LmiVoidPtr data, LmiAllocator* a);

/**
{function:
	{name: LmiPropertyListenerConstructCopy}
	{parent: LmiPropertyListener}
	{description: Constructs a property listener from another property listener.}
	{prototype: LmiPropertyListener* LmiPropertyListenerConstructCopy(LmiPropertyListener* x, const LmiPropertyListener* y)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{parameter:
		{name: y}
		{description: A property listener.}
	}
	{return: Returns a pointer to the constructed object or NULL on error.}
	{note: Path notation cannot be used in the property listeners.}
}
*/
LmiPropertyListener* LmiPropertyListenerConstructCopy(LmiPropertyListener* x, const LmiPropertyListener* y);

/**
{function:
	{name: LmiPropertyListenerDestruct}
	{parent: LmiPropertyListener}
	{description: Destructs a property listener.}
	{prototype: void LmiPropertyListenerDestruct(LmiPropertyListener* x)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
}
*/
void LmiPropertyListenerDestruct(LmiPropertyListener* x);

/**
{function:
	{name: LmiPropertyListenerAssign}
	{parent: LmiPropertyListener}
	{description: Assigns a property listener from another property listener.}
	{prototype: LmiPropertyListener* LmiPropertyListenerAssign(LmiPropertyListener* x, const LmiPropertyListener* y)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{parameter:
		{name: y}
		{description: A property listener.}
	}
	{return: Returns a pointer to the assigned-to object or NULL on error.}
}
*/
LmiPropertyListener* LmiPropertyListenerAssign(LmiPropertyListener* x, const LmiPropertyListener* y);

/**
{function:
	{name: LmiPropertyListenerEqual}
	{parent: LmiPropertyListener}
	{description: Determines whether two property listeners are equal.}
	{prototype: LmiBool LmiPropertyListenerEqual(const LmiPropertyListener* x, const LmiPropertyListener* y)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{parameter:
		{name: y}
		{description: A property listener.}
	}
	{return: Returns LMI_TRUE if the listeners are equal or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertyListenerEqual(const LmiPropertyListener* x, const LmiPropertyListener* y);

/**
{function:
	{name: LmiPropertyListenerGetTrigger}
	{parent: LmiPropertyListener}
	{description: Gets the trigger of a property listener.}
	{prototype: LmiPropertyListenerTrigger LmiPropertyListenerGetTrigger(const LmiPropertyListener* x)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{return: Returns the trigger for the listener.}
}
*/
LmiPropertyListenerTrigger LmiPropertyListenerGetTrigger(const LmiPropertyListener* x);

/**
{function:
	{name: LmiPropertyListenerGetName}
	{parent: LmiPropertyListener}
	{description: Gets the property name the listener is set on.}
	{prototype: const LmiString* LmiPropertyListenerGetName(const LmiPropertyListener* x)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{return: Returns a pointer to the name or NULL if the listener is listening to all properties.}
}
*/
const LmiString* LmiPropertyListenerGetName(const LmiPropertyListener* x);

/**
{function:
	{name: LmiPropertyListenerGetData}
	{parent: LmiPropertyListener}
	{description: Gets the user data pointer of the property listener.}
	{prototype: LmiVoidPtr LmiPropertyListenerGetData(const LmiPropertyListener* x)}
	{parameter:
		{name: x}
		{description: A property listener.}
	}
	{return: Returns the user data pointer passed to {code:LmiPropertyListenerConstruct} or {code:LmiPropertyListenerConstructCStr}.}
}
*/
LmiVoidPtr LmiPropertyListenerGetData(const LmiPropertyListener* x);

Declare_LmiMap(LmiString, LmiPropertyValue)
Declare_LmiVector(LmiPropertyListener)

/**
{type:
	{name: LmiProperties}
	{parent: Os}
	{include: Lmi/Os/LmiProperties.h}
	{description: Describes a set of properties and listeners for observing changes to those properties.}
}
*/
typedef struct LmiProperties_ {
	LmiMutex mutex;
	LmiMap(LmiString, LmiPropertyValue) map;
	LmiVector(LmiPropertyListener) listeners;
	LmiBool visited; /* Loop detection */
} LmiProperties;


/**
{function:
	{name: LmiPropertiesConstructDefault}
	{parent: LmiProperties}
	{description: Constructs an empty property set.}
	{prototype: LmiProperties* LmiPropertiesConstructDefault(LmiProperties* x, LmiAllocator* a)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: a}
		{description: An allocator. }
	}
	{return: Returns a pointer to the constructed object or NULL on error.}
}
*/
LmiProperties* LmiPropertiesConstructDefault(LmiProperties* x, LmiAllocator* a);
/**
{function:
	{name: LmiPropertiesConstructCopy}
	{parent: LmiProperties}
	{description: Constructs a property set from another property set.}
	{prototype: LmiProperties* LmiPropertiesConstructCopy(LmiProperties* x, const LmiProperties* y)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: y}
		{description: A property set.}
	}
	{return: Returns a pointer to the constructed object or NULL on error.}
}
*/
LmiProperties* LmiPropertiesConstructCopy(LmiProperties* x, const LmiProperties* y);
/**
{function:
	{name: LmiPropertiesDestruct}
	{parent: LmiProperties}
	{description: Destructs a property set.}
	{prototype: void LmiPropertiesDestruct(LmiProperties* x)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
}
*/
void LmiPropertiesDestruct(LmiProperties* x);

/**
{function:
	{name: LmiPropertiesAssign}
	{parent: LmiProperties}
	{description: Assigns one property set to another property set.}
	{prototype: LmiProperties* LmiPropertiesAssign(LmiProperties* x, const LmiProperties* y)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: y}
		{description: A property set.}
	}
	{return: Returns a pointer to the assigned-to object or NULL on error.}
}
*/
LmiProperties* LmiPropertiesAssign(LmiProperties* x, const LmiProperties* y);


/**
{function:
	{name: LmiPropertiesEqual}
	{parent: LmiProperties}
	{description: Compares one property set to another property set for equality.}
	{prototype: LmiBool LmiPropertiesEqual(const LmiProperties* x, const LmiProperties* y)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: y}
		{description: A property set.}
	}
	{return: Returns LMI_TRUE if the property sets are equal or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesEqual(const LmiProperties* x, const LmiProperties* y);


/**
{function:
	{name: LmiPropertiesLess}
	{parent: LmiProperties}
	{description: Compares one property set to another property set for less-than equality.}
	{prototype: LmiBool LmiPropertiesLess(const LmiProperties* x, const LmiProperties* y)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: y}
		{description: A property set.}
	}
	{return: Returns LMI_TRUE if the {code:x} is less than {code:y} or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesLess(const LmiProperties* x, const LmiProperties* y);

/**
{function:
	{name: LmiPropertiesGetAllocator}
	{parent: LmiProperties}
	{description: Gets the allocator of the property set.}
	{prototype: LmiAllocator* LmiPropertiesGetAllocator(const LmiProperties* x)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{return: Returns a pointer to the property set's allocator.}
}
*/
LmiAllocator* LmiPropertiesGetAllocator(const LmiProperties* x);

/**
{function:
	{name: LmiPropertiesAddListener}
	{parent: LmiProperties}
	{description: Adds a listener to the property set. Note: it's possible to register a property listener for a specific property even before before the property has been added.}
	{prototype: LmiBool LmiPropertiesAddListener(LmiProperties* x, LmiPropertyListener* listener)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: listener}
		{description: The listener to add.}
	}
	{return: Returns LMI_TRUE if the listener was added successfully, or LMI_FALSE if an error occurred.}

	{example:
		#include <stdio.h>
		#include <Lmi/Os/LmiMallocAllocator.h>
		#include <Lmi/Os/LmiProperties.h>
		void PrintPropertyValue(FILE* fp, const LmiPropertyValue* v) \{
			LmiPropertyValueType type = LmiPropertyValueGetType(v);
			if (type == LMI_PROPERTYVALUE_TYPE_Bool) \{
				fprintf(fp, "%s", (*LmiPropertyValueGetBool(v)) ? "true" : "false");
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Int) \{
				fprintf(fp, "%d", *LmiPropertyValueGetInt(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Int16) \{
				fprintf(fp, "%d", *LmiPropertyValueGetInt16(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Int64) \{
				fprintf(fp, "%lld", *LmiPropertyValueGetInt64(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Uint) \{
				fprintf(fp, "%u", *LmiPropertyValueGetUint(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Uint16) \{
				fprintf(fp, "%u", *LmiPropertyValueGetUint16(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_SizeT) \{
				fprintf(fp, "%zu", *LmiPropertyValueGetSizeT(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Float32) \{
				fprintf(fp, "%.2f", *LmiPropertyValueGetFloat32(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Float64) \{
				fprintf(fp, "%.5f", *LmiPropertyValueGetFloat64(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_Time) \{
				fprintf(fp, "%lld", (long long)*LmiPropertyValueGetTime(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_VoidPtr) \{
				fprintf(fp, "%p", *LmiPropertyValueGetVoidPtr(v));
			\} else if (type == LMI_PROPERTYVALUE_TYPE_String) \{
				fprintf(fp, "\\"%s\\"", LmiStringCStr(LmiPropertyValueGetString(v)));
			\}
		\}

		void BeforeCb(const LmiPropertyListener* x, LmiProperties* properties, const LmiString* name, const LmiPropertyValue* oldValue, const LmiPropertyValue* newValue) \{
			FILE* fp = (FILE*)LmiPropertyListenerGetData(x);

			fprintf(fp, "Before Event: ");

			\/\* Value Changed \*\/
			if ((oldValue != NULL) && (newValue != NULL)) \{
				fprintf(fp, "Property %s will change value from ", LmiStringCStr(name));
				PrintPropertyValue(fp, oldValue);
				fprintf(fp, " to ");
				PrintPropertyValue(fp, newValue);
				fprintf(fp, ".\n");

			\/\* Property Removed \*\/
			\} else if (oldValue != NULL) \{
				fprintf(fp, "Property %s will be removed (value currently is ", LmiStringCStr(name));
				PrintPropertyValue(fp, oldValue);
				fprintf(fp, ").\n");
			\/\* Property Added \*\/
			\} else if (newValue != NULL) \{
				fprintf(fp, "Property %s will be added (value will be ", LmiStringCStr(name));
				PrintPropertyValue(fp, newValue);
				fprintf(fp, ").\n");
			\}
		\}

		void AfterCb(const LmiPropertyListener* x, LmiProperties* properties, const LmiString* name, const LmiPropertyValue* oldValue, const LmiPropertyValue* newValue) \{
			FILE* fp = (FILE*)LmiPropertyListenerGetData(x);

			fprintf(fp, "After Event: ");

			\/\* Value changed \*\/
			if ((oldValue != NULL) && (newValue != NULL)) \{
				fprintf(fp, "Property %s has value changed to ", LmiStringCStr(name));
				PrintPropertyValue(fp, newValue);
				fprintf(fp, ".\n");
			\/\* Property Removed \*\/
			\} else if ((oldValue == NULL) && (newValue == NULL)) \{
				fprintf(fp, "Property %s was removed.\n", LmiStringCStr(name));
			\/\* Property Added \*\/
			\} else if (newValue != NULL) \{
				fprintf(fp, "Property %s was added (value is ", LmiStringCStr(name));
				PrintPropertyValue(fp, newValue);
				fprintf(fp, ").\n");
			\}
		\}

		int main() \{
			LmiAllocator* alloc;
			LmiProperties properties;
			LmiString name;
			LmiPropertyValue value, value2;
			LmiPropertyListener before, after;
			char nameCStr[] = "path1.path2.path3";

			LmiMallocAllocatorInitialize();
			alloc = LmiMallocAllocatorGetDefault();
			LmiStringConstructCStr(&name, "prop1.prop2", alloc);

			\/\* Construct a property set \*\/
			LmiPropertiesConstructDefault(&properties, alloc);

			\/\* Register a "before" listener property \*\/
			LmiPropertyListenerConstruct(&before, LMI_PROPERTYLISTENER_TRIGGER_Before, &name, BeforeCb, stdout);
			LmiPropertiesAddListener(&properties, &before);

			\/\* Register a "after" listener property \*\/
			LmiPropertyListenerConstruct(&after, LMI_PROPERTYLISTENER_TRIGGER_After, &name, AfterCb, stdout);
			LmiPropertiesAddListener(&properties, &after);

			\/\* Add a property \*\/
			LmiPropertyValueConstructInt(&value, 123, LMI_TRUE);
			LmiPropertiesAddProperty(&properties, &name, &value);

			\/\* Set a property \*\/
			LmiPropertyValueConstructInt(&value2, 456, LMI_TRUE);
			LmiPropertiesSetProperty(&properties, &name, &value2);

			\/\* Another way to set property \*\/
			LmiPropertiesSetIntValueCStr(&properties, nameCStr, 42, LMI_TRUE, alloc);

			\/\* Remove a property \*\/
			LmiPropertiesRemoveProperty(&properties, &name);

			\/\* Clean-up \*\/
			LmiPropertyValueDestruct(&value2);
			LmiPropertyValueDestruct(&value);
			LmiStringDestruct(&name);
			LmiPropertyListenerDestruct(&before);
			LmiPropertyListenerDestruct(&after);
			LmiPropertiesDestruct(&properties);

			return 0;
		\}
	}
}
*/
LmiBool LmiPropertiesAddListener(LmiProperties* x, LmiPropertyListener* listener);

/**
{function:
	{name: LmiPropertiesRemoveListener}
	{parent: LmiProperties}
	{description: Removes a listener from the property set. }
	{prototype: LmiBool LmiPropertiesRemoveListener(LmiProperties* x, LmiPropertyListener* listener)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: listener}
		{description: The listener to remove.}
	}
	{return: Returns LMI_TRUE if the listener was successfully removed or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesRemoveListener(LmiProperties* x, LmiPropertyListener* listener);

/**
{function:
	{name: LmiPropertiesAddProperty}
	{parent: LmiProperties}
	{description: Adds a property to the property set.  Adding a property triggers matching property listeners.}
	{prototype: LmiBool LmiPropertiesAddProperty(LmiProperties* x, const LmiString* name, const LmiPropertyValue* v)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{parameter:
		{name: v}
		{description: The property value to set the property to.}
	}
	{return: Returns LMI_TRUE if the property does not yet exist and the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesAddProperty(LmiProperties* x, const LmiString* name, const LmiPropertyValue* v);

/**
{function:
	{name: LmiPropertiesAddPropertyCStr}
	{parent: LmiProperties}
	{description: Adds a property to the property set.  Adding a property triggers matching property listeners.}
	{prototype: LmiBool LmiPropertiesAddPropertyCStr(LmiProperties* x, const char* name, const LmiPropertyValue* v)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{parameter:
		{name: v}
		{description: The property value to set the property to.}
	}
	{return: Returns LMI_TRUE if the property does not yet exist and the property value was successful set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesAddPropertyCStr(LmiProperties* x, const char* name, const LmiPropertyValue* v);

/**
{function:
	{name: LmiPropertiesRemoveProperty}
	{parent: LmiProperties}
	{description: Removes a property from the property set. Removing a property triggers matching property listeners registered for the property. }
	{prototype: LmiBool LmiPropertiesRemoveProperty(LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns LMI_TRUE if the property exists and the property was removed successful or LMI_FALSE otherwise.}
	{note: if path has multiple components, levels below last will not be removed. For example removing of "path1.path2" path will only
	cause "path2" to be removed; "path1" will stay even when empty.}
}
*/
LmiBool LmiPropertiesRemoveProperty(LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesRemovePropertyCStr}
	{parent: LmiProperties}
	{description: Removes a property to the property set. Removing a property triggers matching property listeners.}
	{prototype: LmiBool LmiPropertiesRemovePropertyCStr(LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns LMI_TRUE if the property exists and the property was removed successful or LMI_FALSE otherwise.}
	{note: if path has multiple components, levels below last will not be removed. For example removing of "path1.path2" path will only
	cause "path2" to be removed; "path1" will stay even when empty.}
}
*/
LmiBool LmiPropertiesRemovePropertyCStr(LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetPropertyConst}
	{parent: LmiProperties}
	{description: Gets the property value of a property in the property set.}
	{prototype: const LmiPropertyValue* LmiPropertiesGetPropertyConst(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'), and vector elements are indicated by brackets ('['). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns a pointer to the property's value or NULL if the property was not found.}
}
*/
const LmiPropertyValue* LmiPropertiesGetPropertyConst(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetPropertyCStrConst}
	{parent: LmiProperties}
	{description: Gets the property value of a property in the property set.}
	{prototype: const LmiPropertyValue* LmiPropertiesGetPropertyCStrConst(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'), and vector elements are indicated by brackets ('['). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns a pointer to the property's value or NULL if the property was not found.}
}
*/
const LmiPropertyValue* LmiPropertiesGetPropertyCStrConst(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetProperty}
	{parent: LmiProperties}
	{description: Gets the property value of a property in the property set.}
	{prototype: LmiPropertyValue* LmiPropertiesGetProperty(LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'), and vector elements are indicated by brackets ('['). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns a pointer to the property's value or NULL if the property was not found.}
}
*/
LmiPropertyValue* LmiPropertiesGetProperty(LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetPropertyCStr}
	{parent: LmiProperties}
	{description: Gets the property value of a property in the property set.}
	{prototype: LmiPropertyValue* LmiPropertiesGetPropertyCStr(LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'), and vector elements are indicated by brackets ('['). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{return: Returns a pointer to the property's value or NULL if the property was not found.}
}
*/
LmiPropertyValue* LmiPropertiesGetPropertyCStr(LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesSetProperty}
	{parent: LmiProperties}
	{description: Sets the value of a property in the property set.  If the property doesn't already exist, the property is added.
	  Setting a property triggers matching top level property listeners.}
	{prototype: LmiBool LmiPropertiesSetProperty(LmiProperties* x, const LmiString* name, const LmiPropertyValue* v)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{parameter:
		{name: v}
		{description: The property value to set the property to.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
	{note: Path will be created if does not exist.
	If one of the path's components already exists and is not a type of LmiProperties, it will be replaced with LmiProperties.}
}
*/
LmiBool LmiPropertiesSetProperty(LmiProperties* x, const LmiString* name, const LmiPropertyValue* v);

/**
{function:
	{name: LmiPropertiesSetPropertyCStr}
	{parent: LmiProperties}
	{description: Sets the value of a property in the property set. If the property doesn't already exist, the property is added.
	  Setting a property triggers top level property listeners registered for the property.}
	{prototype: LmiBool LmiPropertiesSetPropertyCStr(LmiProperties* x, const char* name, const LmiPropertyValue* v)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: name}
		{description: The name or path to the property (i.e. "valueName", "valueParent.valueName", etc).
		  Paths are specified using dotted notation (element1.element2) where elements of the path are
		  delimited by dots ('.'). Path delimiters can be escaped with a backslash ('\\').  For example,
		  "path\\.continues" specifies a simple name rather than a path.}
	}
	{parameter:
		{name: v}
		{description: The property value to set the property to.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetPropertyCStr(LmiProperties* x, const char* name, const LmiPropertyValue* v);

/**
{function:
	{name: LmiPropertiesMerge}
	{parent: LmiProperties}
	{description: Merges two properties. Read only properties are not updated.}
	{prototype: LmiProperties* LmiPropertiesMerge(LmiProperties* x, const LmiProperties* y)}
	{parameter:
		{name: x}
		{description: A property set that will contain a merged value.}
	}
	{parameter:
		{name: y}
		{description: A property set.}
	}
	{return: Returns a pointer to the merged object or NULL on error.}
}
*/
LmiProperties* LmiPropertiesMerge(LmiProperties* x, const LmiProperties* y);

/* Properties helpers */
/* Setting */

/**
{function:
	{name: LmiPropertiesSetBoolValue}
	{parent: LmiProperties}
	{description: Sets LmiBool property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetBoolValue(LmiProperties* x, const LmiString* name, LmiBool b, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: b}
		{description: Value of the property of LmiBool type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetBoolValue(LmiProperties* x, const LmiString* name, LmiBool b, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetIntValue}
	{parent: LmiProperties}
	{description: Sets LmiInt property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetIntValue(LmiProperties* x, const LmiString* name, LmiInt i, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i}
		{description: Value of the property of LmiInt type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetIntValue(LmiProperties* x, const LmiString* name, LmiInt i, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetInt16Value}
	{parent: LmiProperties}
	{description: Sets LmiInt16 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetInt16Value(LmiProperties* x, const LmiString* name, LmiInt16 i16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i16}
		{description: Value of the property of LmiInt16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetInt16Value(LmiProperties* x, const LmiString* name, LmiInt16 i16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetInt64Value}
	{parent: LmiProperties}
	{description: Sets LmiInt64 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetInt64Value(LmiProperties* x, const LmiString* name, LmiInt64 i64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i64}
		{description: Value of the property of LmiInt64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetInt64Value(LmiProperties* x, const LmiString* name, LmiInt64 i64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetUintValue}
	{parent: LmiProperties}
	{description: Sets LmiUint property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetUintValue(LmiProperties* x, const LmiString* name, LmiUint ui, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui}
		{description: Value of the property of LmiUint type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetUintValue(LmiProperties* x, const LmiString* name, LmiUint ui, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetUint16Value}
	{parent: LmiProperties}
	{description: Sets LmiUint16 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetUint16Value(LmiProperties* x, const LmiString* name, LmiUint16 ui16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui16}
		{description: Value of the property of LmiUint16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetUint16Value(LmiProperties* x, const LmiString* name, LmiUint16 ui16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetSizeTValue}
	{parent: LmiProperties}
	{description: Sets LmiSizeT property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetSizeTValue(LmiProperties* x, const LmiString* name, LmiSizeT sz, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sz}
		{description: Value of the property of LmiSizeT type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetSizeTValue(LmiProperties* x, const LmiString* name, LmiSizeT sz, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetFloat32Value}
	{parent: LmiProperties}
	{description: Sets LmiFloat32 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetFloat32Value(LmiProperties* x, const LmiString* name, LmiFloat32 f32, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f32}
		{description: Value of the property of LmiFloat32 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetFloat32Value(LmiProperties* x, const LmiString* name, LmiFloat32 f32, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetFloat64Value}
	{parent: LmiProperties}
	{description: Sets LmiFloat64 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetFloat64Value(LmiProperties* x, const LmiString* name, LmiFloat64 f64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f64}
		{description: Value of the property of LmiFloat64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetFloat64Value(LmiProperties* x, const LmiString* name, LmiFloat64 f64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetTimeValue}
	{parent: LmiProperties}
	{description: Sets LmiTime property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetTimeValue(LmiProperties* x, const LmiString* name, LmiTime t, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: t}
		{description: Value of the property of LmiTime type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetTimeValue(LmiProperties* x, const LmiString* name, LmiTime t, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetVoidPtrValue}
	{parent: LmiProperties}
	{description: Sets LmiVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetVoidPtrValue(LmiProperties* x, const LmiString* name, LmiVoidPtr vp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: vp}
		{description: Value of the property of LmiVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetVoidPtrValue(LmiProperties* x, const LmiString* name, LmiVoidPtr vp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetStringValue}
	{parent: LmiProperties}
	{description: Sets LmiString property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetStringValue(LmiProperties* x, const LmiString* name, const LmiString* s, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: s}
		{description: Value of the property of LmiString pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetStringValue(LmiProperties* x, const LmiString* name, const LmiString* s, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetStringCStrValue}
	{parent: LmiProperties}
	{description: Sets C string property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetStringCStrValue(LmiProperties* x, const LmiString* name, const char* str, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: str}
		{description: Value of the property of C string type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetStringCStrValue(LmiProperties* x, const LmiString* name, const char* str, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetPropertiesValue}
	{parent: LmiProperties}
	{description: Sets LmiProperties property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetPropertiesValue(LmiProperties* x, const LmiString* name, const LmiProperties* pr, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: pr}
		{description: Value of the property of LmiProperties pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetPropertiesValue(LmiProperties* x, const LmiString* name, const struct LmiProperties_* pr, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetVectorValue}
	{parent: LmiProperties}
	{description: Sets LmiVector(LmiPropertyValue) property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetVectorValue(LmiProperties* x, const LmiString* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: v}
		{description: Value of the property of LmiVector(LmiPropertyValue) type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetVectorValue(LmiProperties* x, const LmiString* name, const LmiVector(LmiPropertyValue)* pr, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetSharedVoidPtrValue}
	{parent: LmiProperties}
	{description: Sets LmiSharedVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetSharedVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiSharedVoidPtr* sp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sp}
		{description: Value of the property of LmiSharedVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetSharedVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiSharedVoidPtr* sp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetWeakVoidPtrValue}
	{parent: LmiProperties}
	{description: Sets LmiWeakVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetWeakVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiWeakVoidPtr* wp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: wp}
		{description: Value of the property of LmiWeakVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetWeakVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiWeakVoidPtr* wp, LmiBool settable);

/* Setting CSTR */
/**
{function:
	{name: LmiPropertiesSetBoolValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiBool property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetBoolValueCStr(LmiProperties* x, const char* name, LmiBool b, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: b}
		{description: Value of the property of LmiBool type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetBoolValueCStr(LmiProperties* x, const char* name, LmiBool b, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetIntValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiInt property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetIntValueCStr(LmiProperties* x, const char* name, LmiInt i, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i}
		{description: Value of the property of LmiInt type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetIntValueCStr(LmiProperties* x, const char* name, LmiInt i, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetInt16ValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiInt16 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetInt16ValueCStr(LmiProperties* x, const char* name, LmiInt16 i16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i16}
		{description: Value of the property of LmiInt16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetInt16ValueCStr(LmiProperties* x, const char* name, LmiInt16 i16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetInt64ValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiInt64 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetInt64ValueCStr(LmiProperties* x, const char* name, LmiInt64 i64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i64}
		{description: Value of the property of LmiInt64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetInt64ValueCStr(LmiProperties* x, const char* name, LmiInt64 i64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetUintValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiUint property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetUintValueCStr(LmiProperties* x, const char* name, LmiUint ui, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui}
		{description: Value of the property of LmiUint type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetUintValueCStr(LmiProperties* x, const char* name, LmiUint ui, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetUint16ValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiUint16 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetUint16ValueCStr(LmiProperties* x, const char* name, LmiUint16 ui16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui16}
		{description: Value of the property of LmiUint16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetUint16ValueCStr(LmiProperties* x, const char* name, LmiUint16 ui16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetSizeTValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiSizeT property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetSizeTValueCStr(LmiProperties* x, const char* name, LmiSizeT sz, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sz}
		{description: Value of the property of LmiSizeT type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetSizeTValueCStr(LmiProperties* x, const char* name, LmiSizeT sz, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetFloat32ValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiFloat32 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetFloat32ValueCStr(LmiProperties* x, const char* name, LmiFloat32 f32, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f32}
		{description: Value of the property of LmiFloat32 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetFloat32ValueCStr(LmiProperties* x, const char* name, LmiFloat32 f32, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetFloat64ValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiFloat64 property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetFloat64ValueCStr(LmiProperties* x, const char* name, LmiFloat64 f64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f64}
		{description: Value of the property of LmiFloat64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetFloat64ValueCStr(LmiProperties* x, const char* name, LmiFloat64 f64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetTimeValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiTime property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetTimeValueCStr(LmiProperties* x, const char* name, LmiTime t, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: t}
		{description: Value of the property of LmiTime type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetTimeValueCStr(LmiProperties* x, const char* name, LmiTime t, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetVoidPtrValueCStr(LmiProperties* x, const char* name, LmiVoidPtr vp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: vp}
		{description: Value of the property of LmiVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetVoidPtrValueCStr(LmiProperties* x, const char* name, LmiVoidPtr vp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetStringValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiString property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetStringValueCStr(LmiProperties* x, const char* name, const LmiString* s, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: s}
		{description: Value of the property of LmiString pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetStringValueCStr(LmiProperties* x, const char* name, const LmiString* s, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetStringCStrValueCStr}
	{parent: LmiProperties}
	{description: Sets C string property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetStringCStrValueCStr(LmiProperties* x, const char* name, const char* str, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: str}
		{description: Value of the property of C string type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetStringCStrValueCStr(LmiProperties* x, const char* name, const char* str, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetPropertiesValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiProperties property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetPropertiesValueCStr(LmiProperties* x, const char* name, const LmiProperties* pr, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: pr}
		{description: Value of the property of LmiProperties pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetPropertiesValueCStr(LmiProperties* x, const char* name, const struct LmiProperties_* pr, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetVectorValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiVector(LmiPropertyValue) property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetVectorValueCStr(LmiProperties* x, const char* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: v}
		{description: Value of the property of LmiProperties pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetVectorValueCStr(LmiProperties* x, const char* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetSharedVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiSharedVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetSharedVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiSharedVoidPtr* sp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sp}
		{description: Value of the property of LmiSharedVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetSharedVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiSharedVoidPtr* sp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesSetWeakVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Sets LmiWeakVoidPtr property value to the specified path.}
	{prototype: LmiBool LmiPropertiesSetWeakVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiWeakVoidPtr* wp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: wp}
		{description: Value of the property of LmiWeakVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully set or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesSetWeakVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiWeakVoidPtr* wp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddBoolValue}
	{parent: LmiProperties}
	{description: Adds LmiBool property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddBoolValue(LmiProperties* x, const LmiString* name, LmiBool b, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: b}
		{description: Value of the property of LmiBool type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/


LmiBool LmiPropertiesAddBoolValue(LmiProperties* x, const LmiString* name, LmiBool b, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddIntValue}
	{parent: LmiProperties}
	{description: Adds LmiInt property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddIntValue(LmiProperties* x, const LmiString* name, LmiInt i, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i}
		{description: Value of the property of LmiInt type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddIntValue(LmiProperties* x, const LmiString* name, LmiInt i, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddInt16Value}
	{parent: LmiProperties}
	{description: Adds LmiInt16 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddInt16Value(LmiProperties* x, const LmiString* name, LmiInt16 i16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i16}
		{description: Value of the property of LmiInt16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddInt16Value(LmiProperties* x, const LmiString* name, LmiInt16 i16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddInt64Value}
	{parent: LmiProperties}
	{description: Adds LmiInt64 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddInt64Value(LmiProperties* x, const LmiString* name, LmiInt64 i64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i64}
		{description: Value of the property of LmiInt64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddInt64Value(LmiProperties* x, const LmiString* name, LmiInt64 i64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddUintValue}
	{parent: LmiProperties}
	{description: Adds LmiUint property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddUintValue(LmiProperties* x, const LmiString* name, LmiUint ui, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui}
		{description: Value of the property of LmiUint type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddUintValue(LmiProperties* x, const LmiString* name, LmiUint ui, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddUint16Value}
	{parent: LmiProperties}
	{description: Adds LmiUint16 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddUint16Value(LmiProperties* x, const LmiString* name, LmiUint16 ui16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui16}
		{description: Value of the property of LmiUint16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddUint16Value(LmiProperties* x, const LmiString* name, LmiUint16 ui16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddSizeTValue}
	{parent: LmiProperties}
	{description: Adds LmiSizeT property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddSizeTValue(LmiProperties* x, const LmiString* name, LmiSizeT sz, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sz}
		{description: Value of the property of LmiSizeT type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddSizeTValue(LmiProperties* x, const LmiString* name, LmiSizeT sz, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddFloat32Value}
	{parent: LmiProperties}
	{description: Adds LmiFloat32 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddFloat32Value(LmiProperties* x, const LmiString* name, LmiFloat32 f32, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f32}
		{description: Value of the property of LmiFloat32 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddFloat32Value(LmiProperties* x, const LmiString* name, LmiFloat32 f32, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddFloat64Value}
	{parent: LmiProperties}
	{description: Adds LmiFloat64 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddFloat64Value(LmiProperties* x, const LmiString* name, LmiFloat64 f64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f64}
		{description: Value of the property of LmiFloat64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddFloat64Value(LmiProperties* x, const LmiString* name, LmiFloat64 f64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddTimeValue}
	{parent: LmiProperties}
	{description: Adds LmiTime property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddTimeValue(LmiProperties* x, const LmiString* name, LmiTime t, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: t}
		{description: Value of the property of LmiTime type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddTimeValue(LmiProperties* x, const LmiString* name, LmiTime t, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddVoidPtrValue}
	{parent: LmiProperties}
	{description: Adds LmiVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddVoidPtrValue(LmiProperties* x, const LmiString* name, LmiVoidPtr vp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: vp}
		{description: Value of the property of LmiVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddVoidPtrValue(LmiProperties* x, const LmiString* name, LmiVoidPtr vp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddStringValue}
	{parent: LmiProperties}
	{description: Adds LmiString property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddStringValue(LmiProperties* x, const LmiString* name, const LmiString* s, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: s}
		{description: Value of the property of LmiString pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddStringValue(LmiProperties* x, const LmiString* name, const LmiString* s, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddStringCStrValue}
	{parent: LmiProperties}
	{description: Adds C string property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddStringCStrValue(LmiProperties* x, const LmiString* name, const char* str, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: str}
		{description: Value of the property of C string type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddStringCStrValue(LmiProperties* x, const LmiString* name, const char* str, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddPropertiesValue}
	{parent: LmiProperties}
	{description: Adds LmiProperties property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddPropertiesValue(LmiProperties* x, const LmiString* name, const LmiProperties* pr, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: pr}
		{description: Value of the property of LmiProperties pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddPropertiesValue(LmiProperties* x, const LmiString* name, const struct LmiProperties_* pr, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddVectorValue}
	{parent: LmiProperties}
	{description: Adds LmiVector(LmiPropertyValue) property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddVectorValue(LmiProperties* x, const LmiString* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: v}
		{description: Value of the property of LmiVector(LmiPropertyValue) type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddVectorValue(LmiProperties* x, const LmiString* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddSharedVoidPtrValue}
	{parent: LmiProperties}
	{description: Adds LmiSharedVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddSharedVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiSharedVoidPtr* sp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sp}
		{description: Value of the property of LmiSharedVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddSharedVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiSharedVoidPtr* sp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddWeakVoidPtrValue}
	{parent: LmiProperties}
	{description: Adds LmiWeakVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddWeakVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiWeakVoidPtr* wp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: wp}
		{description: Value of the property of LmiWeakVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddWeakVoidPtrValue(LmiProperties* x, const LmiString* name, const LmiWeakVoidPtr* wp, LmiBool settable);

/* Setting CSTR */
/**
{function:
	{name: LmiPropertiesAddBoolValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiBool property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddBoolValueCStr(LmiProperties* x, const char* name, LmiBool b, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: b}
		{description: Value of the property of LmiBool type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddBoolValueCStr(LmiProperties* x, const char* name, LmiBool b, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddIntValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiInt property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddIntValueCStr(LmiProperties* x, const char* name, LmiInt i, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i}
		{description: Value of the property of LmiInt type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddIntValueCStr(LmiProperties* x, const char* name, LmiInt i, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddInt16ValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiInt16 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddInt16ValueCStr(LmiProperties* x, const char* name, LmiInt16 i16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i16}
		{description: Value of the property of LmiInt16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddInt16ValueCStr(LmiProperties* x, const char* name, LmiInt16 i16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddInt64ValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiInt64 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddInt64ValueCStr(LmiProperties* x, const char* name, LmiInt64 i64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: i64}
		{description: Value of the property of LmiInt64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddInt64ValueCStr(LmiProperties* x, const char* name, LmiInt64 i64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddUintValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiUint property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddUintValueCStr(LmiProperties* x, const char* name, LmiUint ui, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui}
		{description: Value of the property of LmiUint type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddUintValueCStr(LmiProperties* x, const char* name, LmiUint ui, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddUint16ValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiUint16 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddUint16ValueCStr(LmiProperties* x, const char* name, LmiUint16 ui16, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: ui16}
		{description: Value of the property of LmiUint16 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddUint16ValueCStr(LmiProperties* x, const char* name, LmiUint16 ui16, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddSizeTValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiSizeT property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddSizeTValueCStr(LmiProperties* x, const char* name, LmiSizeT sz, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sz}
		{description: Value of the property of LmiSizeT type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddSizeTValueCStr(LmiProperties* x, const char* name, LmiSizeT sz, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddFloat32ValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiFloat32 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddFloat32ValueCStr(LmiProperties* x, const char* name, LmiFloat32 f32, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f32}
		{description: Value of the property of LmiFloat32 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddFloat32ValueCStr(LmiProperties* x, const char* name, LmiFloat32 f32, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddFloat64ValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiFloat64 property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddFloat64ValueCStr(LmiProperties* x, const char* name, LmiFloat64 f64, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: f64}
		{description: Value of the property of LmiFloat64 type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddFloat64ValueCStr(LmiProperties* x, const char* name, LmiFloat64 f64, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddTimeValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiTime property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddTimeValueCStr(LmiProperties* x, const char* name, LmiTime t, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: t}
		{description: Value of the property of LmiTime type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddTimeValueCStr(LmiProperties* x, const char* name, LmiTime t, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddVoidPtrValueCStr(LmiProperties* x, const char* name, LmiVoidPtr vp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: vp}
		{description: Value of the property of LmiVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddVoidPtrValueCStr(LmiProperties* x, const char* name, LmiVoidPtr vp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddStringValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiString property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddStringValueCStr(LmiProperties* x, const char* name, const LmiString* s, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: s}
		{description: Value of the property of LmiString pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddStringValueCStr(LmiProperties* x, const char* name, const LmiString* s, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddStringCStrValueCStr}
	{parent: LmiProperties}
	{description: Adds C string property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddStringCStrValueCStr(LmiProperties* x, const char* name, const char* str, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: str}
		{description: Value of the property of C string type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddStringCStrValueCStr(LmiProperties* x, const char* name, const char* str, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddPropertiesValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiProperties property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddPropertiesValueCStr(LmiProperties* x, const char* name, const LmiProperties* pr, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: pr}
		{description: Value of the property of LmiProperties pointer type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddPropertiesValueCStr(LmiProperties* x, const char* name, const struct LmiProperties_* pr, LmiBool settable);
/**
{function:
	{name: LmiPropertiesAddVectorValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiVector(LmiPropertyValue) property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddVectorValueCStr(LmiProperties* x, const char* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: v}
		{description: Value of the property of LmiVector(LmiPropertyValue) type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddVectorValueCStr(LmiProperties* x, const char* name, const LmiVector(LmiPropertyValue)* v, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddSharedVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiSharedVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddSharedVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiSharedVoidPtr* sp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: sp}
		{description: Value of the property of LmiSharedVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddSharedVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiSharedVoidPtr* sp, LmiBool settable);

/**
{function:
	{name: LmiPropertiesAddWeakVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Adds LmiWeakVoidPtr property value to the specified path. See LmiPropertiesAddProperty for details on behavior.}
	{prototype: LmiBool LmiPropertiesAddWeakVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiWeakVoidPtr* wp, LmiBool settable)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{parameter:
		{name: wp}
		{description: Value of the property of LmiWeakVoidPtr type.}
	}
	{parameter:
		{name: settable}
		{description: Defines if property can be overwritten.}
	}
	{return: Returns LMI_TRUE if the property value was successfully added or LMI_FALSE on failure or if property exists.}
}
*/
LmiBool LmiPropertiesAddWeakVoidPtrValueCStr(LmiProperties* x, const char* name, const LmiWeakVoidPtr* wp, LmiBool settable);

/* Getting */
/**
{function:
	{name: LmiPropertiesIsSettableValue}
	{parent: LmiProperties}
	{description: Determines whether or not a property value in a path is settable.}
	{prototype: const LmiBool* LmiPropertiesIsSettableValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns pointer to the boolean, which is LMI_TRUE if the property value is settable or LMI_FALSE otherwise. NULL on failure.}
}
*/
const LmiBool* LmiPropertiesIsSettableValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetTypeValue}
	{parent: LmiProperties}
	{description: Gets the property value type of a property value.}
	{prototype: const LmiPropertyValueType* LmiPropertiesGetTypeValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to the type of the property value or NULL on failure.}
}
*/
const LmiPropertyValueType* LmiPropertiesGetTypeValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetBoolValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiBool of a property value.}
	{prototype: const LmiBool* LmiPropertiesGetBoolValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiBool of the property value on success, or NULL if the type of the property value is not an LmiBool or property is not set.}
}
*/
const LmiBool* LmiPropertiesGetBoolValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetIntValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt of a property value.}
	{prototype: const LmiInt* LmiPropertiesGetIntValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt of the property value on success, or NULL if the type of the property value is not an LmiInt or property is not set.}
}
*/
const LmiInt* LmiPropertiesGetIntValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetInt16Value}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt16 of a property value.}
	{prototype: const LmiInt16* LmiPropertiesGetInt16Value(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt16 of the property value on success, or NULL if the type of the property value is not an LmiInt16 or property is not set.}
}
*/
const LmiInt16* LmiPropertiesGetInt16Value(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetInt64Value}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt64 of a property value.}
	{prototype: const LmiInt64* LmiPropertiesGetInt64Value(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt64 of the property value on success, or NULL if the type of the property value is not an LmiInt64 or property is not set.}
}
*/
const LmiInt64* LmiPropertiesGetInt64Value(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetUintValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiUint of a property value.}
	{prototype: const LmiUint* LmiPropertiesGetUintValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiUint of the property value on success, or NULL if the type of the property value is not an LmiUint or property is not set.}
}
*/
const LmiUint* LmiPropertiesGetUintValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetUint16Value}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiUint16 of a property value.}
	{prototype: const LmiUint16* LmiPropertiesGetUint16Value(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiUint16 of the property value on success, or NULL if the type of the property value is not an LmiUint16 or property is not set.}
}
*/
const LmiUint16* LmiPropertiesGetUint16Value(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetSizeTValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiSizeT of a property value.}
	{prototype: const LmiSizeT* LmiPropertiesGetSizeTValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiSizeT of the property value on success, or NULL if the type of the property value is not an LmiSizeT or property is not set.}
}
*/
const LmiSizeT* LmiPropertiesGetSizeTValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetFloat32Value}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiFloat32 of a property value.}
	{prototype: const LmiFloat32* LmiPropertiesGetFloat32Value(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiFloat32 of the property value on success, or NULL if the type of the property value is not an LmiFloat32 or property is not set.}
}
*/
const LmiFloat32* LmiPropertiesGetFloat32Value(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetFloat64Value}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiFloat64 of a property value.}
	{prototype: const LmiFloat64* LmiPropertiesGetFloat64Value(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiFloat64 of the property value on success, or NULL if the type of the property value is not an LmiFloat64 or property is not set.}
}
*/
const LmiFloat64* LmiPropertiesGetFloat64Value(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetTimeValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiTime of a property value.}
	{prototype: const LmiTime* LmiPropertiesGetTimeValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiTime of the property value on success, or NULL if the type of the property value is not an LmiTime or property is not set.}
}
*/
const LmiTime* LmiPropertiesGetTimeValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetVoidPtrValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiVoidPtr of a property value.}
	{prototype: const LmiVoidPtr* LmiPropertiesGetVoidPtrValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiVoidPtr or property is not set.}
}
*/
const LmiVoidPtr* LmiPropertiesGetVoidPtrValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetStringValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiString of a property value.}
	{prototype: const LmiString* LmiPropertiesGetStringValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiString of the property value on success, or NULL if the type of the property value is not an LmiString or property is not set.}
}
*/
const LmiString* LmiPropertiesGetStringValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetPropertiesValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiProperties of a property value.}
	{prototype: const LmiProperties* LmiPropertiesGetPropertiesValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiProperties of the property value on success, or NULL if the type of the property value is not an LmiProperties or property is not set.}
}
*/
const LmiProperties* LmiPropertiesGetPropertiesValue(const LmiProperties* x, const LmiString* name);


/**
{function:
	{name: LmiPropertiesGetVectorValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiVector(LmiPropertyValue) of a property value.}
	{prototype: const LmiVector(LmiPropertyValue)* LmiPropertiesGetVectorValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiVector(LmiPropertyValue) of the property value on success, or NULL if the type of the property value is not an LmiVector(LmiPropertyValue) or property is not set.}
}
*/
const LmiVector(LmiPropertyValue)* LmiPropertiesGetVectorValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetSharedVoidPtrValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiSharedVoidPtr of a property value.}
	{prototype: const LmiSharedVoidPtr* LmiPropertiesGetSharedVoidPtrValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiSharedVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiSharedVoidPtr or property is not set.}
}
*/
const LmiSharedVoidPtr* LmiPropertiesGetSharedVoidPtrValue(const LmiProperties* x, const LmiString* name);

/**
{function:
	{name: LmiPropertiesGetWeakVoidPtrValue}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiWeakVoidPtr of a property value.}
	{prototype: const LmiWeakVoidPtr* LmiPropertiesGetWeakVoidPtrValue(const LmiProperties* x, const LmiString* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiWeakVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiWeakVoidPtr or property is not set.}
}
*/
const LmiWeakVoidPtr* LmiPropertiesGetWeakVoidPtrValue(const LmiProperties* x, const LmiString* name);

/* Getting CStr */
/**
{function:
	{name: LmiPropertiesIsSettableValueCStr}
	{parent: LmiProperties}
	{description: Determines whether or not a property value in a path is settable.}
	{prototype: const LmiBool* LmiPropertiesIsSettableValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns pointer to the boolean, which is LMI_TRUE if the property value is settable or LMI_FALSE otherwise. NULL on failure.}
}
*/
const LmiBool* LmiPropertiesIsSettableValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetTypeValueCStr}
	{parent: LmiProperties}
	{description: Gets the property value type of a property value.}
	{prototype: const LmiPropertyValueType* LmiPropertiesGetTypeValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to the type of the property value or NULL on failure.}
}
*/
const LmiPropertyValueType* LmiPropertiesGetTypeValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetBoolValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiBool of a property value.}
	{prototype: const LmiBool* LmiPropertiesGetBoolValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiBool of the property value on success, or NULL if the type of the property value is not an LmiBool or property is not set.}
}
*/
const LmiBool* LmiPropertiesGetBoolValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetIntValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt of a property value.}
	{prototype: const LmiInt* LmiPropertiesGetIntValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt of the property value on success, or NULL if the type of the property value is not an LmiInt or property is not set.}
}
*/
const LmiInt* LmiPropertiesGetIntValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetInt16ValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt16 of a property value.}
	{prototype: const LmiInt16* LmiPropertiesGetInt16ValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt16 of the property value on success, or NULL if the type of the property value is not an LmiInt16 or property is not set.}
}
*/
const LmiInt16* LmiPropertiesGetInt16ValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetInt64ValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiInt64 of a property value.}
	{prototype: const LmiInt64* LmiPropertiesGetInt64ValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiInt64 of the property value on success, or NULL if the type of the property value is not an LmiInt64 or property is not set.}
}
*/
const LmiInt64* LmiPropertiesGetInt64ValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetUintValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiUint of a property value.}
	{prototype: const LmiUint* LmiPropertiesGetUintValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiUint of the property value on success, or NULL if the type of the property value is not an LmiUint or property is not set.}
}
*/
const LmiUint* LmiPropertiesGetUintValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetUint16ValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiUint16 of a property value.}
	{prototype: const LmiUint16* LmiPropertiesGetUint16ValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiUint16 of the property value on success, or NULL if the type of the property value is not an LmiUint16 or property is not set.}
}
*/
const LmiUint16* LmiPropertiesGetUint16ValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetSizeTValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiSizeT of a property value.}
	{prototype: const LmiSizeT* LmiPropertiesGetSizeTValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiSizeT of the property value on success, or NULL if the type of the property value is not an LmiSizeT or property is not set.}
}
*/
const LmiSizeT* LmiPropertiesGetSizeTValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetFloat32ValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiFloat32 of a property value.}
	{prototype: const LmiFloat32* LmiPropertiesGetFloat32ValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiFloat32 of the property value on success, or NULL if the type of the property value is not an LmiFloat32 or property is not set.}
}
*/
const LmiFloat32* LmiPropertiesGetFloat32ValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetFloat64ValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiFloat64 of a property value.}
	{prototype: const LmiFloat64* LmiPropertiesGetFloat64ValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiFloat64 of the property value on success, or NULL if the type of the property value is not an LmiFloat64 or property is not set.}
}
*/
const LmiFloat64* LmiPropertiesGetFloat64ValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetTimeValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiTime of a property value.}
	{prototype: const LmiTime* LmiPropertiesGetTimeValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiTime of the property value on success, or NULL if the type of the property value is not an LmiTime or property is not set.}
}
*/
const LmiTime* LmiPropertiesGetTimeValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiVoidPtr of a property value.}
	{prototype: const LmiVoidPtr* LmiPropertiesGetVoidPtrValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiVoidPtr or property is not set.}
}
*/
const LmiVoidPtr* LmiPropertiesGetVoidPtrValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetStringValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiString of a property value.}
	{prototype: const LmiString* LmiPropertiesGetStringValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiString of the property value on success, or NULL if the type of the property value is not an LmiString or property is not set.}
}
*/
const LmiString* LmiPropertiesGetStringValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetPropertiesValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiProperties of a property value.}
	{prototype: const LmiProperties* LmiPropertiesGetPropertiesValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiProperties of the property value on success, or NULL if the type of the property value is not an LmiProperties or property is not set.}
}
*/
const LmiProperties* LmiPropertiesGetPropertiesValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetVectorValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiVector(LmiPropertyValue) of a property value.}
	{prototype: const LmiVector(LmiPropertyValue)* LmiPropertiesGetVectorValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiVector(LmiPropertyValue) of the property value on success, or NULL if the type of the property value is not an LmiVector(LmiPropertyValue) or property is not set.}
}
*/
const LmiVector(LmiPropertyValue)* LmiPropertiesGetVectorValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetSharedVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiSharedVoidPtr of a property value.}
	{prototype: const LmiSharedVoidPtr* LmiPropertiesGetSharedVoidPtrValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiSharedVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiSharedVoidPtr or property is not set.}
}
*/
const LmiSharedVoidPtr* LmiPropertiesGetSharedVoidPtrValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetWeakVoidPtrValueCStr}
	{parent: LmiProperties}
	{description: Gets a const pointer to an LmiWeakVoidPtr of a property value.}
	{prototype: const LmiWeakVoidPtr* LmiPropertiesGetWeakVoidPtrValueCStr(const LmiProperties* x, const char* name)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: name}
		{description: The path to the property, i.e. "valueName", "valueParent.valueName", etc.}
	}
	{return: Returns a pointer to an LmiWeakVoidPtr of the property value on success, or NULL if the type of the property value is not an LmiWeakVoidPtr or property is not set.}
}
*/
const LmiWeakVoidPtr* LmiPropertiesGetWeakVoidPtrValueCStr(const LmiProperties* x, const char* name);

/**
{function:
	{name: LmiPropertiesGetAllNames}
	{parent: LmiProperties}
	{description: Gets all the names of the property values in the property set.}
	{prototype: LmiBool LmiPropertiesGetAllNames(const LmiProperties* x, LmiVector(LmiString) *names)}
	{parameter:
		{name: x}
		{description: A property set.}
	}
	{parameter:
		{name: names}
		{description: The names.}
	}
	{return: Returns LMI_TRUE if successful or LMI_FALSE otherwise.}
}
*/
LmiBool LmiPropertiesGetAllNames(const LmiProperties* x, LmiVector(LmiString) *names);
/**
{function:
	{name: LmiPropertiesDumpToJSON}
	{parent: LmiProperties}
	{description: Gets all names for the values in properties.}
	{prototype: const LmiString* LmiPropertiesDumpToJSON(const LmiProperties* x, LmiString *json)}
	{parameter:
		{name: x}
		{description: A properties object.}
	}
	{parameter:
		{name: json}
		{description: Empty initialized string, JSON string representing content of the x. }
	}
	{return: Pointer to a string representing x, or NULL on failure.}
	{note: This function is expensive, please be thoughtful of that. }
}
*/
const LmiString* LmiPropertiesDumpToJSON(const LmiProperties* x, LmiString *json);

LMI_END_EXTERN_C

#endif

