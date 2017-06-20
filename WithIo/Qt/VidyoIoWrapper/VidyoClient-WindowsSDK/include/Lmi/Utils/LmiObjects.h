/** {file:
    {name: LmiObjects.h}
    {description: Definition of basic object properties.}
    {copyright:
    	(c) 2005-2012 Vidyo, Inc.,
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

#ifndef LMI_OBJECTS_H_
#define LMI_OBJECTS_H_

#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/SysDep/LmiBaseTypes.h>

/*
   {package visibility="private":
     {name: LmiObjectOverview}
     {parent: Utils}
	 {include: include N/A}
     {description: General LMI Object Definitions}
     {note: Vidyo\'s code is written entirely in C.  However, it
            makes use of many techniques of object-orientation and
            templatization, as is more commonly found in C++.  This section
            defines how an object and its associated functions should be
            named in order that it may be used by the LMI template
            classes.}}
   
   {type visibility="private":
     {name: LmiObject}
     {parent: LmiObjectOverview}
     {description: Lmi{italic:Object} represents any object in the LMI
                   object scheme.  It must have Construct (of some kind) and Destruct methods.
                   It may optionally have ConstructDefault, ConstructCopy, Assign, Equal, Less
                   and Swap methods defined for it as well.}
     {note: Lmi{italic:Object} is not an actual type; this name is used as 
            an example.}
   }

   {function visibility="private":
     {name: LmiObjectConstructDefault}
     {parent: LmiObject}
     {description: Construct a default instance of an Lmi{italic:Object}
                   object.}
     {prototype: LmiObject* LmiObjectConstructDefault(LmiObject* obj, LmiAllocator* a)}
     {parameter:
       {name: obj}
       {description: A pointer to the object to initialize.
       The object is assumed to be previously uninitialized.}}
     {parameter:
       {name: a}
       {description: A pointer to the object's allocator or NULL 
	   if the object has no need of an allocator.}}
     {return: A pointer to the constructed object on full successful
              completion, otherwise {code: NULL}.}
     {note: Where possible, a constructor should either complete entirely
     successfully or else have no effect (other than logging or the like).
     Objects should never be left in a half-constructed state.}
   }

   {function visibility="private":
     {name: LmiObjectConstructCopy}
     {parent: LmiObject}
     {description: Construct a new Lmi{italic:Object} object as a copy of an
                   existing one.}
     {prototype: LmiObject* LmiObjectConstructCopy(LmiObject* dst, const LmiObject* src)}
     {parameter:
       {name: dst}
       {description: A pointer to the object to initialize.
       The object is assumed to be previously uninitialized.}}
     {parameter:
       {name: src}
       {description: An existing Lmi{italic:Object} object.
        This object is semantically unmodified by this operation; however,
        it may have internal state changed (for example reference counts).}}
     {return: A pointer to the constructed object on full successful
              completion, otherwise {code: NULL}.}
     {note: Where possible, a constructor should either complete entirely
            successfully or else have no effect (other than logging or the
            like). Objects should never be left in a half-constructed state.}
     {note: The {code: src} parameter may optionally be defined without
            the {code: const} qualifier, if necessary.}
   }

   {function visibility="private":
     {name: LmiObjectDestruct}
     {parent: LmiObject}
     {description: Destruct an Lmi{italic:Object} object.}
     {prototype: void LmiObjectDestruct(LmiObject* obj)}
     {parameter:
       {name: obj}
       {description: A pointer to the object to deinitialize.  The object is
       assumed to be previously initialized.}}
     {note: This function returns no value.  On error, the failure should be
     recorded in some way, but often no other action can be taken.}
   }

   {function visibility="private":
     {name: LmiObjectAssign}
     {parent: LmiObject}
     {description: Assign the value of one Lmi{italic:Object} object to
     another one.}
     {prototype: LmiObject* LmiObjectAssign(LmiObject* dst, const LmiObject* src)}
     {parameter:
       {name: dst}
       {description: A pointer to the object to be assigned. The object is
       assumed to already be initialized; the function must free its
       existing state if necessary.}}
     {parameter:
       {name: src}
       {description: A pointer to an existing Lmi{italic:Object}
        object. This object is semantically unmodified by this operation;
        however, it may have internal state changed (for example reference
        counts).}}
     {return: A pointer to dst, or NULL on failure.  On failure, the
       destination object is left in a valid but unspecified state.}
     {note: Where possible, an assignment should either complete entirely
      successfully or else have no effect (other than logging or the like).
      Objects should never be left in a half-assigned state.}
     {note: The {code: src} parameter may optionally be defined without
      the {code: const} qualifier, if necessary.}
     {note: Self-assignment is valid.  Care may be needed to handle the case
      when {code: src} == {code: dst}.}
   }
   
   {function visibility="private":
     {name: LmiObjectEqual}
     {parent: LmiObject}
     {description: Compare the values of two Lmi{italic:Object} objects for
      equality.}
     {prototype: LmiBool LmiObjectEqual(const LmiObject* a,
      const LmiObject* b)}
     {parameter:
       {name: a}
       {description: A pointer to the first object to be compared.}}
     {parameter:
       {name: b}
       {description: A pointer to the second object to be compared.}}
     {return: LMI_TRUE if the objects pointed to are equal, otherwise
      LMI_FALSE.}
     {note: The parameters are semantically unmodified by this operation;
       however, they may have internal state changed.  In this case the
       parameters may optionally be defined without the {code: const}
       qualifier, if necessary.}
     {note: This must be an equivalence relation.  I.e., for all X, Y, Z:
      {code: X == X}; 
      {code: X == Y} iff {code: Y == X}; and
      {code: X == Y && Y == Z} implies {code: X == Z}.}
     {note: Self-comparison is valid.  Care may be needed to handle the case
      when {code: a} == {code: b}.}
   }
   
   {function visibility="private":
     {name: LmiObjectLess}
     {parent: LmiObject}
     {description: Compare the values of two Lmi{italic:Object} objects for
      ordering.}
     {prototype: LmiBool LmiObjectLess(const LmiObject* a,
      const LmiObject* b)}
     {parameter:
       {name: a}
       {description: A pointer to the first object to be compared.}}
     {parameter:
       {name: b}
       {description: A pointer to the second object to be compared.}}
     {return: LMI_TRUE if the parameter pointed to by {code: a} is less than
      the one pointed to by {code: b}, otherwise LMI_FALSE.}
     {note: The parameters are semantically unmodified by this operation;
      however, they may have internal state changed.  In this case the
      parameters may optionally be defined without the {code: const} qualifier,
      if necessary.}
     {note: This must be a strict ordering.  I.e., for all X, Y, Z, 
      {code: !(X < X)};
      {code: X < Y} implies {code: !(Y < X)}; and
      {code: X < Y && Y < Z} implies {code: X < Z}.
      It need not, however, be a total ordering; two objects may be
      incommensurate.  That is to say, it is valid to have
      {code: !(X < Y) && !(Y < X) && !(X == Y)}.}
     {note: Self-comparison is valid.  Care may be needed to handle the case
      when {code: a} == {code: b}.}
   }

   {function visibility="private":
     {name: LmiObjectSwap}
     {parent: LmiObject}
     {description: Swap the contents of two Lmi{italic:Object} objects.}
     {prototype: LmiBool LmiObjectSwap(LmiObject* a, LmiObject* b)}
     {parameter:
       {name: a}
       {description: A pointer to the first object to be swapped.}}
     {parameter:
       {name: b}
       {description: A pointer to the second object to be swapped.}}
     {return: LMI_TRUE on success, LMI_FALSE on allocator failure.}
     {note: Self-swapping is valid.  Care may be needed to handle the case
      when {code: a} == {code: b}.}
   }

*/

/**
   {function visibility="private" validate="no":
     {name: Declare_LmiBasicType}
     {parent: BasicTypes}
     {description:
       {p: Declare the standard set of LmiObject operators on a basic type:
       Construct, ConstructCopy, Destruct, Assign, Equal, Less, and Swap.
       If possible, also define these as inline functions.}
       {p: A basic type is one on which the
       C assignment and comparison operators are valid and satisfy the
       constraints of the Lmi object model, and which can have {code:
       0} assigned to it.  That is to say, this is valid for all C integer, 
       pointer, and enumerated types, and it is valid for floating-point types if {code:
       NaN} is disregarded.  (Because {code: NaN} != {code: NaN}, == is not an
       equivalence relation for C floating-point types.)}
     }
     {prototype: void Declare_LmiBasicType(Type T)}
     {parameter: {name: T}
       {description: Type for which to define object operators.}}
	 {note: This is a macro that must be called at global scope and expands to a declaration 
	   and (if possible) inline definition of LmiObject operator functions on the type T.}
     {note: See also Define_LmiBasicType.}
}
*/

#define DefineInline_LmiBasicType(T_, INLINE_)                  \
  INLINE_ T_* LmiConstruct(T_)(T_ * obj_)                       \
  {                                                             \
    *obj_ = (T_)0;                                              \
    return obj_;                                                \
  }                                                             \
                                                                \
  INLINE_ void LmiDestruct(T_)(T_ * obj_)                       \
  {                                                             \
  }                                                             \
                                                                \
  INLINE_ T_* LmiConstructCopy(T_)(T_ * dst_, const T_ * src_)  \
  {                                                             \
    *dst_ = *src_;                                              \
    return dst_;                                                \
  }                                                             \
                                                                \
  INLINE_ T_* LmiAssign(T_)(T_ * dst_, const T_ * src_)         \
  {                                                             \
    *dst_ = *src_;                                              \
    return dst_;                                                \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiSwap(T_)(T_ * a_, T_ * b_)                 \
  {                                                             \
    T_ temp = *b_;                                              \
    *b_ = *a_;                                                  \
    *a_ = temp;                                                 \
    return LMI_TRUE;                                            \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiEqual(T_)(const T_ * a_, const T_ * b_)    \
  {                                                             \
    return *a_ == *b_;                                          \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiLess(T_)(const T_ * a_, const T_ * b_)     \
  {                                                             \
    return *a_ < *b_;                                           \
  }

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiBasicType(T_) \
  DefineInline_LmiBasicType(T_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiBasicType(T_) /* (defined as empty) */
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define DefineInlineSource_LmiBasicType(T_) \
  DefineInline_LmiBasicType(T_, LMI_INLINE_SOURCE_FILE)
#else
#define DefineInlineSource_LmiBasicType(T_) /* (defined as empty) */
#endif

#define Declare_LmiBasicType(T_)              \
  LMI_INLINE_DECLARATION T_* LmiConstruct(T_)(T_*);                  \
	DeclareInline_LmiAssignable(T_, LMI_INLINE_DECLARATION) \
       DeclareInline_LmiEqualityComparable(T_, LMI_INLINE_DECLARATION)      \
       DeclareInline_LmiLessThanComparable(T_, LMI_INLINE_DECLARATION)      \
       DefineInlineHeader_LmiBasicType(T_)

#define Define_LmiBasicType(T_) \
  DefineInlineSource_LmiBasicType(T_)

/* * NOT A DOCBLOCK
	The docblocks below can be used for the functions declared and defined
	by Declare/Define_LmiBasicType.  Replace "-TYPE-" by the name of the type
	being declared.
   
   
	{function:
		{name: -TYPE-Construct}
		{parent: -TYPE-}
		{description: Construct a default instance of an -TYPE- object.}
		{prototype: -TYPE-* -TYPE-Construct(-TYPE-* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the -TYPE- object to initialize.}}
		{return: A pointer to the constructed object on full successful
        	completion, otherwise {code: NULL}.}
		{note: The -TYPE- object is initialized with the value 0.
			-TYPE- construction will not fail.}
	}

	{function:
		{name: -TYPE-ConstructCopy}
		{parent: -TYPE-}
		{description: Construct a new -TYPE- object as a copy of an
			existing one.}
		{prototype: -TYPE-* -TYPE-ConstructCopy(-TYPE-* dst, const -TYPE-* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the -TYPE- object to initialize as a
				copy.}}
		{parameter:
			{name: src}
			{description: An existing -TYPE- object.}}
		{return: A pointer to the constructed object on full successful
			completion, otherwise {code: NULL}.}
		{note: -TYPE- construction will not fail.}
	}

	{function:
		{name: -TYPE-Destruct}
		{parent: -TYPE-}
		{description: Destruct an -TYPE- object.}
		{prototype: void -TYPE-Destruct(-TYPE-* obj)}
		{parameter:
			{name: obj}
			{description: A pointer to the -TYPE- object to destruct.
				The object is assumed to be previously initialized.}}
		{note: This function does nothing; it is provided for completeness
			and to support the use of container classes.}
	}

	{function:
		{name: -TYPE-Assign}
		{parent: -TYPE-}
		{description: Assign the value of one -TYPE- object to another one.}
		{prototype: -TYPE-* -TYPE-Assign(-TYPE-* dst, const -TYPE-* src)}
		{parameter:
			{name: dst}
			{description: A pointer to the -TYPE- object to be assigned.
				The object is assumed to already be initialized.}}
		{parameter:
			{name: src}
			{description: A pointer to an existing -TYPE- object.}}
	   	{return: A pointer to dst, or {code: NULL} on failure.}
		{note: -TYPE- assignment will not fail.}
	}
   
	{function:
		{name: -TYPE-Equal}
		{parent: -TYPE-}
		{description: Compare the values of two -TYPE- objects for
			equality.}
		{prototype: LmiBool -TYPE-Equal(const -TYPE-* a, const -TYPE-* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first -TYPE- object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second -TYPE- object
				to be compared.}}
		{return: LMI_TRUE if the objects pointed to are equal, otherwise
			LMI_FALSE.}
	}
   
	{function:
		{name: -TYPE-Less}
		{parent: -TYPE-}
		{description: Compare the values of two -TYPE- objects for
			ordering.}
		{prototype: LmiBool -TYPE-Less(const -TYPE-* a, const -TYPE-* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first -TYPE- object
				to be compared.}}
		{parameter:
			{name: b}
			{description: A pointer to the second -TYPE- object
				to be compared.}}
		{return: LMI_TRUE if the parameter pointed to by {code: a} is less than
			the one pointed to by {code: b}, otherwise LMI_FALSE.}
	}

	{function:
		{name: -TYPE-Swap}
		{parent: -TYPE-}
		{description: Swap the contents of two -TYPE- objects.}
		{prototype: LmiBool -TYPE-Swap(-TYPE-* a, -TYPE-* b)}
		{parameter:
			{name: a}
			{description: A pointer to the first -TYPE- object
				to be swapped.}}
		{parameter:
			{name: b}
			{description: A pointer to the second -TYPE- object
				to be swapped.}}
		{return: LMI_TRUE on success, LMI_FALSE on failure.}
		{note: -TYPE- swapping will not fail.}
	}
*/

/**
   {function visibility="private" validate="no":
     {name: Declare_LmiFunctionPointerType}
     {parent: BasicTypes}
     {description:
       {p: Declare the standard set of LmiObject operators on a function pointer type:
       Construct, ConstructCopy, Destruct, Assign, Equal, and Swap.
	   Also declare Less as a stub (always-false) function for the sake of
	   container templates.
       If possible, also define these as inline functions.}
     }
     {prototype: void Declare_LmiFunctionPointerType(Type T)}
     {parameter: {name: T}
       {description: Type for which to define object operators.}}
	 {note: This is a macro that must be called at global scope and expands to a declaration 
	   and (if possible) inline definition of LmiObject operator functions on the type T.}
     {note: See also Define_LmiFunctionPointerType.}
}
*/

#define DefineInline_LmiFunctionPointerType(T_, INLINE_)                  \
  INLINE_ T_* LmiConstruct(T_)(T_ * obj_)                       \
  {                                                             \
    *obj_ = (T_)0;                                              \
    return obj_;                                                \
  }                                                             \
                                                                \
  INLINE_ void LmiDestruct(T_)(T_ * obj_)                       \
  {                                                             \
  }                                                             \
                                                                \
  INLINE_ T_* LmiConstructCopy(T_)(T_ * dst_, const T_ * src_)  \
  {                                                             \
    *dst_ = *src_;                                              \
    return dst_;                                                \
  }                                                             \
                                                                \
  INLINE_ T_* LmiAssign(T_)(T_ * dst_, const T_ * src_)         \
  {                                                             \
    *dst_ = *src_;                                              \
    return dst_;                                                \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiSwap(T_)(T_ * a_, T_ * b_)                 \
  {                                                             \
    T_ temp = *b_;                                              \
    *b_ = *a_;                                                  \
    *a_ = temp;                                                 \
    return LMI_TRUE;                                            \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiEqual(T_)(const T_ * a_, const T_ * b_)    \
  {                                                             \
    return *a_ == *b_;                                          \
  }                                                             \
                                                                \
  INLINE_ LmiBool LmiLess(T_)(const T_ * a_, const T_ * b_)     \
  {                                                             \
    return LMI_FALSE;                                           \
  }																\

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiFunctionPointerType(T_) \
  DefineInline_LmiFunctionPointerType(T_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiFunctionPointerType(T_) /* (defined as empty) */
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define DefineInlineSource_LmiFunctionPointerType(T_) \
  DefineInline_LmiFunctionPointerType(T_, LMI_INLINE_SOURCE_FILE)
#else
#define DefineInlineSource_LmiFunctionPointerType(T_) /* (defined as empty) */
#endif

#define Declare_LmiFunctionPointerType(T_)              \
  LMI_INLINE_DECLARATION T_* LmiConstruct(T_)(T_*);                  \
	DeclareInline_LmiAssignable(T_, LMI_INLINE_DECLARATION) \
       DeclareInline_LmiEqualityComparable(T_, LMI_INLINE_DECLARATION)      \
       DeclareInline_LmiLessThanComparable(T_, LMI_INLINE_DECLARATION)      \
       DefineInlineHeader_LmiFunctionPointerType(T_)

#define Define_LmiFunctionPointerType(T_) \
  DefineInlineSource_LmiFunctionPointerType(T_)


    
#endif /* LMI_OBJECTS_H_ */
