/** {file:
	  {name: LmiSharedPtr.h}
	  {description: Wrapper class for shared (reference-counted) pointers.}
	  {copyright:
	  	(c) 2009-2016 Vidyo, Inc.,
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
#ifndef LMI_SHARED_PTR_H_
#define LMI_SHARED_PTR_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiAssert.h>

#include <Lmi/Os/LmiAtomicInteger.h>

/* Set this to set DummyAlloc mode for every shared pointer in the system. */
/* #define LMI_SHAREDPTR_MEMDEBUG 1 */

LMI_BEGIN_EXTERN_C

/**
	{type:
    	{name: LmiSharedPtr}
		{parent: Os}
		{include: Lmi/Os/LmiSharedPtr.h}
		{description: Shared (reference-counted) pointer class.}
		{template-prototype: LmiSharedPtr(T)}
		{template-parameter:
			{name: T}
			{description: The type pointed-to by the shared pointer.}}
		{note: This object is modeled on the C++ TR1 std::tr1::shared_ptr<T>
			template class.}
		{note: An expansion of the macro Declare_LmiSharedPtr(T) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiSharedPtr(T) must be present in exactly
			one object file at link time.}
	}
*/

/**
	{callback:
    	{name: LmiSharedPtrDeleterCallback}
		{parent: LmiSharedPtr}
		{description: Callback invoked to perform custom deletion of a shared pointer.}
		{prototype: void (*LmiSharedPtrDeleterCallback)(LmiVoidPtr obj, LmiAllocator* a)}
		{parameter:
			{name: obj}
			{description: A pointer to the object to be deleted.}}
		{parameter:
			{name: a}
			{description: The allocator associated with the shared pointer.}}
	}
*/

/**
	{type:
    	{name: LmiWeakPtr}
		{parent: Os}
		{include: Lmi/Os/LmiSharedPtr.h}
		{description: Weak reference to shared (reference-counted) pointer class.}
		{template-prototype: LmiWeakPtr(T)}
		{template-parameter:
			{name: T}
			{description: The type pointed-to by the shared pointer.}}
		{note: This object is modeled on the C++ TR1 std::tr1::weak_ptr<T>
			template class.}
		{note: An expansion of the macro Declare_LmiSharedPtr(T) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiSharedPtr(T) must be present in exactly
			one object file at link time.}
	}
*/


#define LmiSharedPtr(T_) LmiTemplate1(LmiSharedPtr,T_)
#define LmiSharedPtrFunc_(T_,Func_) LmiClassFunc(LmiSharedPtr(T_),Func_)

#define LmiSharedPtrDefaultDeleter_(T_) LmiSharedPtrFunc_(T_, DefaultDeleter_)

#define LmiSharedPtrIncUseCount_(T_) LmiSharedPtrFunc_(T_, IncUseCount_)
#define LmiSharedPtrIncUseCountConditional_(T_) LmiSharedPtrFunc_(T_, IncUseCountConditional_)
#define LmiSharedPtrDecUseCount_(T_) LmiSharedPtrFunc_(T_, DecUseCount_)

#define LmiSharedPtrConstructDefault(T_) LmiConstructDefault(LmiSharedPtr(T_))
#define LmiSharedPtrConstruct(T_)        LmiConstruct(LmiSharedPtr(T_))
#define LmiSharedPtrConstructWithDeleter(T_) LmiSharedPtrFunc_(T_, ConstructWithDeleter)
#define LmiSharedPtrConstructFromWeakPtr(T_) LmiSharedPtrFunc_(T_, ConstructFromWeakPtr)
#define LmiSharedPtrDestruct(T_)         LmiDestruct(LmiSharedPtr(T_))
#define LmiSharedPtrConstructCopy(T_)    LmiConstructCopy(LmiSharedPtr(T_))
#define LmiSharedPtrGetAllocator(T_)	 LmiGetAllocator(LmiSharedPtr(T_))

#define LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiSharedPtr, T_, U_), ConstructFromOtherSharedPtr)
#define LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiSharedPtr, T_, U_), ConstructFromOtherWeakPtr)

#define LmiSharedPtrConstructFromSharedVoidPtr(T_) LmiSharedPtrConstructFromOtherSharedPtr(T_, void)
#define LmiSharedVoidPtrConstructFromSharedPtr(T_) LmiSharedPtrConstructFromOtherSharedPtr(void, T_)
#define LmiSharedPtrConstructFromWeakVoidPtr(T_) LmiSharedPtrConstructFromOtherWeakPtr(T_, void)
#define LmiSharedVoidPtrConstructFromWeakPtr(T_) LmiSharedPtrConstructFromOtherWeakPtr(void, T_)

#define LmiSharedPtrAssign(T_)	LmiAssign(LmiSharedPtr(T_))
#define LmiSharedPtrSwap(T_)	LmiSwap(LmiSharedPtr(T_))
#define LmiSharedPtrEqual(T_)	LmiEqual(LmiSharedPtr(T_))
#define LmiSharedPtrLess(T_)	LmiLess(LmiSharedPtr(T_))

#define LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiSharedPtr, T_, U_), AssignFromOtherSharedPtr)

#define LmiSharedPtrAssignFromSharedVoidPtr(T_) LmiSharedPtrAssignFromOtherSharedPtr(T_, void)
#define LmiSharedVoidPtrAssignFromSharedPtr(T_) LmiSharedPtrAssignFromOtherSharedPtr(void, T_)

#define LmiSharedPtrGet(T_)			LmiSharedPtrFunc_(T_, Get)
#define LmiSharedPtrUseCount(T_)	LmiSharedPtrFunc_(T_, UseCount)
#define LmiSharedPtrUnique(T_)		LmiSharedPtrFunc_(T_, Unique)
#define LmiSharedPtrGetDeleter(T_)	LmiSharedPtrFunc_(T_, GetDeleter)
#define LmiSharedPtrReset(T_)		LmiSharedPtrFunc_(T_, Reset)

#define LmiSharedPtrMakeUnique(T_)	LmiSharedPtrFunc_(T_, MakeUnique)


#define LmiWeakPtr(T_) LmiTemplate1(LmiWeakPtr,T_)
#define LmiWeakPtrFunc_(T_,Func_) LmiClassFunc(LmiWeakPtr(T_),Func_)

#define LmiWeakPtrIncWeakCount_(T_) LmiWeakPtrFunc_(T_, IncWeakCount_)
#define LmiWeakPtrDecWeakCount_(T_) LmiWeakPtrFunc_(T_, DecWeakCount_)

#define LmiWeakPtrConstructDefault(T_) LmiConstructDefault(LmiWeakPtr(T_))
#define LmiWeakPtrConstructFromSharedPtr(T_)  LmiWeakPtrFunc_(T_, ConstructFromSharedPtr)
#define LmiWeakPtrDestruct(T_)         LmiDestruct(LmiWeakPtr(T_))
#define LmiWeakPtrConstructCopy(T_)    LmiConstructCopy(LmiWeakPtr(T_))
#define LmiWeakPtrGetAllocator(T_)	 LmiGetAllocator(LmiWeakPtr(T_))

#define LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiWeakPtr, T_, U_), ConstructFromOtherWeakPtr)
#define LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiWeakPtr, T_, U_), ConstructFromOtherSharedPtr)

#define LmiWeakPtrConstructFromWeakVoidPtr(T_) LmiWeakPtrConstructFromOtherWeakPtr(T_, void)
#define LmiWeakVoidPtrConstructFromWeakPtr(T_) LmiWeakPtrConstructFromOtherWeakPtr(void, T_)
#define LmiWeakPtrConstructFromSharedVoidPtr(T_) LmiWeakPtrConstructFromOtherSharedPtr(T_, void)
#define LmiWeakVoidPtrConstructFromSharedPtr(T_) LmiWeakPtrConstructFromOtherSharedPtr(void, T_)

#define LmiWeakPtrAssign(T_)	LmiAssign(LmiWeakPtr(T_))
#define LmiWeakPtrAssignFromSharedPtr(T_)	LmiWeakPtrFunc_(T_, AssignFromSharedPtr)
#define LmiWeakPtrSwap(T_)	LmiSwap(LmiWeakPtr(T_))
#define LmiWeakPtrEqual(T_)	LmiEqual(LmiWeakPtr(T_))
#define LmiWeakPtrLess(T_)	LmiLess(LmiWeakPtr(T_))

#define LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiWeakPtr, T_, U_), AssignFromOtherWeakPtr)
#define LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) LmiClassFunc(LmiTemplate2(LmiWeakPtr, T_, U_), AssignFromOtherSharedPtr)

#define LmiWeakPtrAssignFromWeakVoidPtr(T_) LmiWeakPtrAssignFromOtherWeakPtr(T_, void)
#define LmiWeakVoidPtrAssignFromWeakPtr(T_) LmiWeakPtrAssignFromOtherWeakPtr(void, T_)
#define LmiWeakPtrAssignFromSharedVoidPtr(T_) LmiWeakPtrAssignFromOtherSharedPtr(T_, void)
#define LmiWeakVoidPtrAssignFromSharedPtr(T_) LmiWeakPtrAssignFromOtherSharedPtr(void, T_)

#define LmiWeakPtrUseCount(T_)	LmiWeakPtrFunc_(T_, UseCount)
#define LmiWeakPtrExpired(T_)		LmiWeakPtrFunc_(T_, Expired)
#define LmiWeakPtrReset(T_)		LmiWeakPtrFunc_(T_, Reset)


/**
	{type:
    	{name: LmiSharedVoidPtr}
		{parent: Os}
		{include: Lmi/Os/LmiSharedPtr.h}
		{description: Shared (reference-counted) pointer class to void.}
		{note: This object is modeled on the C++ TR1 std::tr1::shared_ptr<void>
			template class.}
	}
*/

/**
	{type:
    	{name: LmiWeakVoidPtr}
		{parent: Os}
		{include: Lmi/Os/LmiSharedPtr.h}
		{description: Weak reference to shared (reference-counted) pointer class to void.}
		{note: This object is modeled on the C++ TR1 std::tr1::weak_ptr<void>
			template class.}
	}
*/

#define LmiSharedVoidPtr	LmiSharedPtr(void)

#define LmiSharedVoidPtrConstructDefault LmiSharedPtrConstructDefault(void)

#define LmiSharedVoidPtrConstructWithDeleter	LmiSharedPtrConstructWithDeleter(void)
#define LmiSharedVoidPtrConstructFromWeakVoidPtr	LmiSharedPtrConstructFromWeakPtr(void)
#define LmiSharedVoidPtrDestruct	LmiSharedPtrDestruct(void)
#define LmiSharedVoidPtrConstructCopy	LmiSharedPtrConstructCopy(void)
#define LmiSharedVoidPtrGetAllocator	LmiSharedPtrGetAllocator(void)

#define LmiSharedVoidPtrAssign	LmiSharedPtrAssign(void)
#define LmiSharedVoidPtrSwap	LmiSharedPtrSwap(void)
#define LmiSharedVoidPtrEqual	LmiSharedPtrEqual(void)
#define LmiSharedVoidPtrLess	LmiSharedPtrLess(void)

#define LmiSharedVoidPtrGet	LmiSharedPtrGet(void)
#define LmiSharedVoidPtrUseCount	LmiSharedPtrUseCount(void)
#define LmiSharedVoidPtrUnique	LmiSharedPtrUnique(void)
#define LmiSharedVoidPtrGetDeleter	LmiSharedPtrGetDeleter(void)
#define LmiSharedVoidPtrReset	LmiSharedPtrReset(void)


#define LmiWeakVoidPtr	LmiWeakPtr(void)

#define LmiWeakVoidPtrConstructDefault	LmiWeakPtrConstructDefault(void)
#define LmiWeakVoidPtrConstructFromSharedVoidPtr	LmiWeakPtrConstructFromSharedPtr(void)
#define LmiWeakVoidPtrDestruct	LmiWeakPtrDestruct(void)
#define LmiWeakVoidPtrConstructCopy	LmiWeakPtrConstructCopy(void)
#define LmiWeakVoidPtrGetAllocator	LmiWeakPtrGetAllocator(void)

#define LmiWeakVoidPtrAssign	LmiWeakPtrAssign(void)
#define LmiWeakVoidPtrAssignFromSharedVoidPtr	LmiWeakPtrAssignFromSharedPtr(void)
#define LmiWeakVoidPtrSwap	LmiWeakPtrSwap(void)
#define LmiWeakVoidPtrEqual	LmiWeakPtrEqual(void)
#define LmiWeakVoidPtrLess	LmiWeakPtrLess(void)

#define LmiWeakVoidPtrUseCount	LmiWeakPtrUseCount(void)
#define LmiWeakVoidPtrExpired	LmiWeakPtrExpired(void)
#define LmiWeakVoidPtrReset	LmiWeakPtrReset(void)


typedef struct {
	LmiAtomicInteger useCount;
	LmiAtomicInteger weakCount;
} LmiSharedPtrRefCount;

LMI_INLINE_DECLARATION LmiSharedPtrRefCount* LmiSharedPtrRefCountConstruct(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION void LmiSharedPtrRefCountDestruct(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION void LmiSharedPtrRefCountIncUseCount(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrRefCountDecUseCount(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION LmiInt LmiSharedPtrRefCountGetUseCount(const LmiSharedPtrRefCount* r);

LMI_INLINE_DECLARATION LmiBool LmiSharedPtrRefCountIncUseCountConditional(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION void LmiSharedPtrRefCountIncWeakCount(LmiSharedPtrRefCount* r);
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrRefCountDecWeakCount(LmiSharedPtrRefCount* r);


typedef void (*LmiSharedPtrDeleterCallback)(LmiVoidPtr obj, LmiAllocator* a);

#define Declare_LmiSharedPtrClass(T_)		\
typedef struct {							\
	LmiSharedPtrRefCount* ref;				\
	T_* ptr;								\
	LmiAllocator* a;						\
	LmiSharedPtrDeleterCallback d;			\
} LmiSharedPtr(T_);


/* Identical structurally to shared ptr, but declared separately so they're
 * not compatible types. */
#define Declare_LmiWeakPtrClass(T_)			\
typedef struct {							\
	LmiSharedPtrRefCount* ref;				\
	T_* ptr;								\
	LmiAllocator* a;						\
	LmiSharedPtrDeleterCallback d;			\
} LmiWeakPtr(T_);



#define Declare_LmiSharedPtrIncUseCount_(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrIncUseCount_(T_)(LmiSharedPtr(T_) * s_);

#define DefineInline_LmiSharedPtrIncUseCount_(T_, INLINE_)		\
INLINE_															\
LmiBool LmiSharedPtrIncUseCount_(T_)(LmiSharedPtr(T_)* s_)			\
{																\
	if (s_->ref == NULL) return LMI_TRUE;						\
	LmiSharedPtrRefCountIncUseCount(s_->ref);					\
	return LMI_TRUE;											\
}

#define Declare_LmiSharedPtrIncUseCountConditional_(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrIncUseCountConditional_(T_)(LmiSharedPtr(T_) * s_);

#define DefineInline_LmiSharedPtrIncUseCountConditional_(T_, INLINE_)		\
INLINE_															\
LmiBool LmiSharedPtrIncUseCountConditional_(T_)(LmiSharedPtr(T_)* s_)	\
{																\
	if (s_->ref == NULL) return LMI_FALSE;						\
	return LmiSharedPtrRefCountIncUseCountConditional(s_->ref);	\
}


#define Declare_LmiSharedPtrDecUseCount_(T_) \
LMI_INLINE_DECLARATION void LmiSharedPtrDecUseCount_(T_)(LmiSharedPtr(T_) * s_);


#define DefineInline_LmiSharedPtrDecUseCount_(T_, INLINE_)		\
INLINE_															\
void LmiSharedPtrDecUseCount_(T_)(LmiSharedPtr(T_) * s_)		\
{																\
	/* s_->ref, s_->a may be freed by deleter, save locally */	\
	LmiSharedPtrRefCount* ref = s_->ref;						\
	LmiAllocator* a;											\
	if (ref == NULL) return;									\
																\
	if (!LmiSharedPtrRefCountDecUseCount(ref))					\
		return;													\
																\
	a = s_->a;													\
	s_->d((LmiVoidPtr)s_->ptr, a);								\
																\
	if (!LmiSharedPtrRefCountDecWeakCount(ref))					\
		return;													\
	LmiSharedPtrRefCountDestruct(ref);							\
	LmiAllocatorDeallocate(a, ref, sizeof(LmiSharedPtrRefCount)); \
}



#define Declare_LmiWeakPtrIncWeakCount_(T_) \
LMI_INLINE_DECLARATION LmiBool LmiWeakPtrIncWeakCount_(T_)(LmiWeakPtr(T_) * w_);

#define DefineInline_LmiWeakPtrIncWeakCount_(T_, INLINE_)		\
INLINE_															\
LmiBool LmiWeakPtrIncWeakCount_(T_)(LmiWeakPtr(T_)* w_)			\
{																\
	if (w_->ref == NULL) return LMI_TRUE;								\
	LmiSharedPtrRefCountIncWeakCount(w_->ref);					\
	return LMI_TRUE;											\
}


#define Declare_LmiWeakPtrDecWeakCount_(T_) \
LMI_INLINE_DECLARATION void LmiWeakPtrDecWeakCount_(T_)(LmiWeakPtr(T_) * w_);


#define DefineInline_LmiWeakPtrDecWeakCount_(T_, INLINE_)		\
INLINE_															\
void LmiWeakPtrDecWeakCount_(T_)(LmiWeakPtr(T_) * w_)			\
{																\
	if (w_->ref == NULL) return;								\
																\
	if (!LmiSharedPtrRefCountDecWeakCount(w_->ref))				\
		return;													\
	LmiAssert(LmiSharedPtrRefCountGetUseCount(w_->ref) == 0);	\
	LmiSharedPtrRefCountDestruct(w_->ref);						\
	LmiAllocatorDeallocate(w_->a, w_->ref, sizeof(LmiSharedPtrRefCount)); \
}


#define Declare_LmiSharedPtrDefaultDeleter_(T_) \
void LmiSharedPtrDefaultDeleter_(T_)(LmiVoidPtr objv, LmiAllocator* a);

#define Define_LmiSharedPtrDefaultDeleter_(T_) \
void LmiSharedPtrDefaultDeleter_(T_)(LmiVoidPtr objv, LmiAllocator* a)	\
{																		\
	T_* obj = (T_*)objv;												\
	LmiDestruct(T_)(obj);												\
	LmiAllocatorDeallocate(a, objv, sizeof(T_));						\
}
		 

/**
	{function:
    	{name: LmiSharedPtrConstructDefault}
		{parent: LmiSharedPtr}
		{description: Construct an empty shared pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructDefault(T_)(LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The empty shared pointer to construct.}}
		{return: The constructed shared pointer.  Does not fail.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr()}.}
	}
*/
#define Declare_LmiSharedPtrConstructDefault(T_) \
LMI_INLINE_DECLARATION													\
LmiSharedPtr(T_)* LmiSharedPtrConstructDefault(T_)(LmiSharedPtr(T_) * s_);


#define DefineInline_LmiSharedPtrConstructDefault(T_, INLINE_)			\
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrConstructDefault(T_)(LmiSharedPtr(T_) * s_) \
{																		\
	s_->ref = NULL;														\
	s_->ptr = NULL;														\
	s_->a = NULL;														\
	s_->d = NULL;														\
	return s_;															\
}
	
/**
	{function:
    	{name: LmiSharedPtrConstruct}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer corresponding to a specified pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstruct(T_)(LmiSharedPtr(T_)* s, T_* p, LmiAllocator* a)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: p} {description: The pointer to share.  This memory for the pointed-to object pointer must have been allocated using the LmiAllocator a.}}
		{parameter: {name: a} {description: An allocator.  This will be used both to allocate internal data structures for the shared pointer and to deallocate memory for the pointed-to object when its use count becomes 0.}}
		{return: The constructed shared pointer on success, or NULL on failure.}
		{note: LmiDestruct(T_)(p) will be called when the object's use count becomes 0.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(T_* p)}, but taking an allocator.}
	}
*/
#define Declare_LmiSharedPtrConstruct(T_) \
LmiSharedPtr(T_)* LmiSharedPtrConstruct(T_)(LmiSharedPtr(T_) * s_, T_* p, LmiAllocator* a);


#define Define_LmiSharedPtrConstruct(T_) \
LmiSharedPtr(T_)* LmiSharedPtrConstruct(T_)(LmiSharedPtr(T_) * s_, T_* p, LmiAllocator* a) \
{																		\
	s_->ref = (LmiSharedPtrRefCount*)LmiAllocatorAllocate(a, sizeof(LmiSharedPtrRefCount));	\
	if (s_->ref == NULL) {												\
		return NULL;													\
	}																	\
	if (LmiSharedPtrRefCountConstruct(s_->ref) == NULL) {				\
		LmiAllocatorDeallocate(a, s_->ref, sizeof(LmiSharedPtrRefCount)); \
		return NULL;													\
	}																	\
	s_->ptr = p;														\
	s_->a = a;															\
	s_->d = LmiSharedPtrDefaultDeleter_(T_);							\
	if (!LmiSharedPtrIncUseCount_(T_)(s_)) {							\
		LmiSharedPtrRefCountDestruct(s_->ref);							\
		LmiAllocatorDeallocate(a, s_->ref, sizeof(LmiSharedPtrRefCount)); \
		s_->ref = NULL;													\
		return NULL;													\
	} 																	\
	LmiSharedPtrRefCountIncWeakCount(s_->ref);							\
	return s_;															\
}


/**
	{function:
    	{name: LmiSharedPtrConstructWithDeleter}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer corresponding to a specified pointer with a custom deleter.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructWithDeleter(T_)(LmiSharedPtr(T_)* s, T_* p, LmiSharedPtrDeleterCallback d, LmiAllocator* a)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: p} {description: The pointer to share.}}
		{parameter: {name: d} {description: A deleter to be called when the shared pointer's reference count becomes 0.}}
		{parameter: {name: a} {description: An allocator.  This will only be used to allocate internal data structures, and will be passed to the deleter when the shared pointer's reference count becomes 0.}}
		{return: The constructed shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(T_* p, D d, A a)}.}
	}
*/

#define Declare_LmiSharedPtrConstructWithDeleter(T_) \
LmiSharedPtr(T_)* LmiSharedPtrConstructWithDeleter(T_)(LmiSharedPtr(T_) * s_, T_* p, LmiSharedPtrDeleterCallback d, LmiAllocator* a);
	
#define Define_LmiSharedPtrConstructWithDeleter(T_) \
LmiSharedPtr(T_)* LmiSharedPtrConstructWithDeleter(T_)(LmiSharedPtr(T_) * s_, T_* p, LmiSharedPtrDeleterCallback d, LmiAllocator* a) \
{																		\
	s_->ref = (LmiSharedPtrRefCount*)LmiAllocatorAllocate(a, sizeof(LmiSharedPtrRefCount));	\
	if (s_->ref == NULL) {												\
		return NULL;													\
	}																	\
	if (LmiSharedPtrRefCountConstruct(s_->ref) == NULL) {				\
		LmiAllocatorDeallocate(a, s_->ref, sizeof(LmiSharedPtrRefCount)); \
		return NULL;													\
	}																	\
	s_->ptr = p;														\
	s_->a = a;															\
	s_->d = d;															\
	if (!LmiSharedPtrIncUseCount_(T_)(s_)) {							\
		LmiSharedPtrRefCountDestruct(s_->ref);							\
		LmiAllocatorDeallocate(a, s_->ref, sizeof(LmiSharedPtrRefCount)); \
		s_->ref = NULL;													\
		return NULL;													\
	} 																	\
	LmiSharedPtrRefCountIncWeakCount(s_->ref);							\
	return s_;															\
}

/**
	{function:
    	{name: LmiSharedPtrDestruct}
		{parent: LmiSharedPtr}
		{description: Destruct a shared pointer.  If this brings the shared pointer's use count to 0, delete the underlying pointer.}
		{prototype: void LmiSharedPtrDestruct(T_)(LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to destruct.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::~shared_ptr()}.}
	}
*/

#define Declare_LmiSharedPtrDestruct(T_) \
LMI_INLINE_DECLARATION void LmiSharedPtrDestruct(T_)(LmiSharedPtr(T_) * s_);


#define DefineInline_LmiSharedPtrDestruct(T_, INLINE_)			\
INLINE_															\
void LmiSharedPtrDestruct(T_)(LmiSharedPtr(T_) * s_)			\
{																\
	LmiSharedPtrDecUseCount_(T_)(s_);							\
}

/**
	{function:
    	{name: LmiSharedPtrConstructCopy}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer as a copy of an existing one, sharing the same underlying pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructCopy(T_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer to copy.}}
		{return: The constructed shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(shared_ptr& const)}.}
	}
*/
#define Declare_LmiSharedPtrConstructCopy(T_) \
LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrConstructCopy(T_)(LmiSharedPtr(T_) * s_, const LmiSharedPtr(T_)* orig);
	
#define DefineInline_LmiSharedPtrConstructCopy(T_, INLINE_) \
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrConstructCopy(T_)(LmiSharedPtr(T_)* s_, const LmiSharedPtr(T_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = orig->ptr;												\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiSharedPtrIncUseCount_(T_)(s_)) {							\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}


/**
	{function:
    	{name: LmiSharedPtrConstructFromOtherSharedPtr}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer from a shared pointer of a different type, sharing the same underlying pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer to construct.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.  The type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The constructed shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(shared_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) must be in
			scope before calling this function, and an expansion
			of the macro Define_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_)			\
	LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_) * s_, const LmiSharedPtr(U_)* orig);
	
#define DefineInline_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_)* s_, const LmiSharedPtr(U_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = (T_*)orig->ptr;											\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiSharedPtrIncUseCount_(T_)(s_)) {							\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}


/**
	{function:
    	{name: LmiSharedPtrConstructFromSharedVoidPtr}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer from a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructFromSharedVoidPtr(T_)(LmiSharedPtr(T_)* s, const LmiSharedVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared void pointer.  The actual type of the object pointed to by the shared void pointer must be compatible with T_.}}
		{return: The constructed shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(shared_ptr<void>& const)}.}
	}
*/


/**
	{function:
    	{name: LmiSharedVoidPtrConstructFromSharedPtr}
		{parent: LmiSharedVoidPtr}
		{description: Construct a shared void pointer from a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructFromSharedPtr(T_)(LmiSharedVoidPtr* s, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the original shared pointer.}}
		{parameter: {name: s} {description: The shared void pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.}}
		{return: The constructed shared void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr(shared_ptr<T_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/


/**
	{function:
    	{name: LmiSharedPtrConstructFromWeakPtr}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer based on a weak pointer, sharing the same underlying pointer, if the weak pointer is not expired.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructFromWeakPtr(T_)(LmiSharedPtr(T_)* s, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer to copy.}}
		{return: The constructed shared pointer on success, or NULL on failure, including if the weak pointer is expired.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(weak_ptr& const)}, except returning NULL if the weak pointer is expired, rather than throwing std::bad_weak_ptr.}
	}
*/
#define Declare_LmiSharedPtrConstructFromWeakPtr(T_) \
LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrConstructFromWeakPtr(T_)(LmiSharedPtr(T_) * s_, const LmiWeakPtr(T_)* orig);
	
#define DefineInline_LmiSharedPtrConstructFromWeakPtr(T_, INLINE_) \
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrConstructFromWeakPtr(T_)(LmiSharedPtr(T_)* s_, const LmiWeakPtr(T_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = orig->ptr;												\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiSharedPtrIncUseCountConditional_(T_)(s_)) {					\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}


/**
	{function:
    	{name: LmiSharedPtrConstructFromOtherWeakPtr}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer based on a weak pointer of a different type, sharing the same underlying pointer, if the weak pointer is not expired.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherWeakPtr(T_, U_)(LmiSharedPtr(T_)* s, const LmiWeakPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer to construct.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing weak pointer.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer.  The type of the object pointed to by this weak pointer must be compatible with T_.}}
		{return: The constructed shared pointer on success, or NULL on failure, including if the weak pointer is expired.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(weak_ptr<U_>& const)}, except returning NULL if the weak pointer is expired, rather than throwing std::bad_weak_ptr.}
		{note: An expansion of the macro Declare_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) must be in
			scope before calling this function, and an expansion
			of the macro Define_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) \
	LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherWeakPtr(T_,U_)(LmiSharedPtr(T_) * s_, const LmiWeakPtr(U_)* orig);
	
#define DefineInline_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrConstructFromOtherWeakPtr(T_,U_)(LmiSharedPtr(T_)* s_, const LmiWeakPtr(U_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = (T_*)orig->ptr;											\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiSharedPtrIncUseCountConditional_(T_)(s_)) {					\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}


/**
	{function:
    	{name: LmiSharedPtrConstructFromWeakVoidPtr}
		{parent: LmiSharedPtr}
		{description: Construct a shared pointer based on a weak void pointer, sharing the same underlying pointer, if the weak pointer is not expired.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrConstructFromWeakVoidPtr(T_)(LmiSharedPtr(T_)* s, const LmiWeakVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer to construct.}}
		{parameter: {name: s} {description: The shared pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak void pointer.  The type of the object pointed to by this weak pointer must be compatible with T_.}}
		{return: The constructed shared pointer on success, or NULL on failure, including if the weak pointer is expired.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::shared_ptr(weak_ptr<void>& const)}, except returning NULL if the weak pointer is expired, rather than throwing std::bad_weak_ptr.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrConstructFromWeakPtr}
		{parent: LmiSharedVoidPtr}
		{description: Construct a shared void pointer based on a weak pointer, sharing the same underlying pointer, if the weak pointer is not expired.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructFromWeakPtr(T_)(LmiSharedVoidPtr* s, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the existing weak pointer.}}
		{parameter: {name: s} {description: The shared void pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer.}}
		{return: The constructed shared void pointer on success, or NULL on failure, including if the weak pointer is expired.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr(weak_ptr<T_>& const)}, except returning NULL if the weak pointer is expired, rather than throwing std::bad_weak_ptr.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/


/**
	{function:
    	{name: LmiSharedPtrGetAllocator}
		{parent: LmiSharedPtr}
		{description: Get the allocator used by a shared pointer.}
		{prototype: LmiAllocator* LmiSharedPtrGetAllocator(T_)(const LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer whose allocator to get.}}
		{return: The allocator used by the shared pointer, or NULL if the shared pointer is empty.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::get_allocator() const}.}
	}
*/
#define Declare_LmiSharedPtrGetAllocator(T_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiSharedPtrGetAllocator(T_)(const LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrGetAllocator(T_, INLINE_)				\
INLINE_																	\
LmiAllocator* LmiSharedPtrGetAllocator(T_)(const LmiSharedPtr(T_)* s) \
{																		\
	return s->a;														\
}


/**
	{function:
    	{name: LmiSharedPtrAssign}
		{parent: LmiSharedPtr}
		{description: Assign the value of one shared pointer to another existing one.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrAssign(T_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to assign.}}
		{parameter: {name: orig} {description: An existing shared pointer to copy.}}
		{return: The assigned-to shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::operator=(shared_ptr& const)}.}
		{note: If s and orig refer to different shared pointers, s\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/
#define Declare_LmiSharedPtrAssign(T_) \
LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrAssign(T_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(T_)* orig);

#define DefineInline_LmiSharedPtrAssign(T_, INLINE_)					\
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrAssign(T_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(T_)* orig) \
{																		\
	if (s->ref != orig->ref) {											\
		LmiSharedPtrDecUseCount_(T_)(s);								\
		s->ref = orig->ref;												\
		s->ptr = orig->ptr;												\
		s->d = orig->d;													\
		s->a = orig->a;													\
		if (!LmiSharedPtrIncUseCount_(T_)(s)) {							\
			s->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		s->ptr = orig->ptr;												\
		s->d = orig->d;													\
		s->a = orig->a;													\
	}																	\
	return s;															\
}


/**
	{function:
    	{name: LmiSharedPtrAssignFromOtherSharedPtr}
		{parent: LmiSharedPtr}
		{description: Assign the value of shared pointer to a shared pointer of a different type, sharing the same underlying pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrAssignFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer to be assigned to.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to assign.}}
		{parameter: {name: orig} {description: An existing shared pointer.  The type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The assigned-to shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::operator=(shared_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) must be in
			scope before calling this function, and an expansion
			of the macro Define_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_)			\
	LMI_INLINE_DECLARATION LmiSharedPtr(T_)* LmiSharedPtrAssignFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_) * s_, const LmiSharedPtr(U_)* orig);
	
#define DefineInline_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiSharedPtr(T_)* LmiSharedPtrAssignFromOtherSharedPtr(T_, U_)(LmiSharedPtr(T_)* s, const LmiSharedPtr(U_)* orig) \
{																		\
	if (s->ref != orig->ref) {											\
		LmiSharedPtrDecUseCount_(T_)(s);								\
		s->ref = orig->ref;												\
		s->ptr = (T_*)orig->ptr;											\
		s->d = orig->d;													\
		s->a = orig->a;													\
		if (!LmiSharedPtrIncUseCount_(T_)(s)) {							\
			s->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		s->ptr = (T_*)orig->ptr;										\
		s->d = orig->d;													\
		s->a = orig->a;													\
	}																	\
	return s;															\
}


/**
	{function:
    	{name: LmiSharedPtrAssignFromSharedVoidPtr}
		{parent: LmiSharedPtr}
		{description: Assign the value of shared void pointer to a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiSharedPtr(T_)* LmiSharedPtrAssignFromSharedVoidPtr(T_)(LmiSharedPtr(T_)* s, const LmiSharedVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer to be assigned to.}}
		{parameter: {name: s} {description: The shared pointer to assign.}}
		{parameter: {name: orig} {description: An existing shared void pointer.  The actual type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The assigned-to shared pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::operator=(shared_ptr<void>& const)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrAssignFromSharedPtr}
		{parent: LmiSharedVoidPtr}
		{description: Assign the value of shared pointer to a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrAssignFromSharedPtr(T_)(LmiSharedVoidPtr* s, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the existing shared pointer.}}
		{parameter: {name: s} {description: The shared void pointer to assign.}}
		{parameter: {name: orig} {description: An existing shared pointer.}}
		{return: The assigned-to shared void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::operator=(shared_ptr<T_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/

/**
	{function:
    	{name: LmiSharedPtrSwap}
		{parent: LmiSharedPtr}
		{description: Swap the values of two shared pointers.}
		{prototype: LmiBool LmiSharedPtrSwap(T_)(LmiSharedPtr(T_)* a, LmiSharedPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointers.}}
		{parameter: {name: a} {description: The first shared pointer to be swapped.}}
		{parameter: {name: b} {description: The second shared pointer to be swapped.}}
		{return: LMI_TRUE, always (cannot fail).}
		{note: Like ISO C++ TR1 function {code: template<T_> std::swap(std::tr1::shared_ptr<T_>&, std::tr1::shared_ptr<T_>&)}.}
	}
*/
#define Declare_LmiSharedPtrSwap(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrSwap(T_)(LmiSharedPtr(T_)* a, LmiSharedPtr(T_)* b);

#define DefineInline_LmiSharedPtrSwap(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiSharedPtrSwap(T_)(LmiSharedPtr(T_)* a, LmiSharedPtr(T_)* b)	\
{																		\
	LmiSharedPtr(T_) tmp;												\
																		\
	tmp = *a;															\
	*a = *b;															\
	*b = tmp;															\
																		\
	return LMI_TRUE;													\
}


/**
	{function:
    	{name: LmiSharedPtrReset}
		{parent: LmiSharedPtr}
		{description: Reset the value of a shared pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: void LmiSharedPtrReset(T_)(LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to be reset.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::reset()}.}
	}
*/
#define Declare_LmiSharedPtrReset(T_) \
LMI_INLINE_DECLARATION void LmiSharedPtrReset(T_)(LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrReset(T_, INLINE_)						\
INLINE_																	\
void LmiSharedPtrReset(T_)(LmiSharedPtr(T_)* s_)						\
{																		\
	LmiSharedPtrDecUseCount_(T_)(s_);									\
																		\
	s_->ref = NULL;														\
	s_->ptr = NULL;														\
	s_->a = NULL;														\
	s_->d = NULL;														\
}


/**
	{function:
    	{name: LmiSharedPtrEqual}
		{parent: LmiSharedPtr}
		{description: Compare the values of two shared pointers for equality.}
		{prototype: LmiBool LmiSharedPtrEqual(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointers.}}
		{parameter: {name: a} {description: The first shared pointer to compare.}}
		{parameter: {name: b} {description: The second shared pointer to compare.}}
		{return: Whether the pointers contained in the shared pointer objects are the same.}
		{note: Like ISO C++ TR1 function {code: template<T_> operator==(const std::tr1::shared_ptr<T_>&, const std::tr1::shared_ptr<T_>&)}.}
	}
*/
#define Declare_LmiSharedPtrEqual(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrEqual(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b);

#define DefineInline_LmiSharedPtrEqual(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiSharedPtrEqual(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b)	\
{																		\
	return a->ptr == b->ptr;											\
}


/**
	{function:
    	{name: LmiSharedPtrLess}
		{parent: LmiSharedPtr}
		{description: Compare the values of two shared pointers for ordering.}
		{prototype: LmiBool LmiSharedPtrLess(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointers.}}
		{parameter: {name: a} {description: The first shared pointer to compare.}}
		{parameter: {name: b} {description: The second shared pointer to compare.}}
		{return: Whether the pointer contained in the first shared pointer objects is less than the second one.}
		{note: Like ISO C++ TR1 function {code: template<T_> operator<(const std::tr1::shared_ptr<T_>&, const std::tr1::shared_ptr<T_>&)}.}
	}
*/
#define Declare_LmiSharedPtrLess(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrLess(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b);

#define DefineInline_LmiSharedPtrLess(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiSharedPtrLess(T_)(const LmiSharedPtr(T_)* a, const LmiSharedPtr(T_)* b)	\
{																		\
	return a->ptr < b->ptr;												\
}


/**
	{function:
    	{name: LmiSharedPtrGet}
		{parent: LmiSharedPtr}
		{description: Get the pointer pointed-to by a shared pointer.}
		{prototype: T_* LmiSharedPtrGet(T_)(const LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer whose pointer to get.}}
		{return: The pointer pointed-to by the shared pointer, or NULL.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::get() const}.}
	}
*/
#define Declare_LmiSharedPtrGet(T_) \
LMI_INLINE_DECLARATION T_* LmiSharedPtrGet(T_)(const LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrGet(T_, INLINE_)  \
INLINE_											   \
T_* LmiSharedPtrGet(T_)(const LmiSharedPtr(T_)* s) \
{												   \
	return s->ptr;								   \
}


/**
	{function:
    	{name: LmiSharedPtrUseCount}
		{parent: LmiSharedPtr}
		{description: Get the current use-count of a shared pointer.}
		{prototype: LmiInt LmiSharedPtrUseCount(T_)(const LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer whose use count to get.}}
		{return: The use count of the shared pointer.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::use_count()}.}
	}
*/
#define Declare_LmiSharedPtrUseCount(T_) \
LMI_INLINE_DECLARATION LmiInt LmiSharedPtrUseCount(T_)(const LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrUseCount(T_, INLINE_)					\
INLINE_																	\
LmiInt LmiSharedPtrUseCount(T_)(const LmiSharedPtr(T_)* s)				\
{																		\
	if (s->ref == NULL)													\
		return 0;														\
	return LmiSharedPtrRefCountGetUseCount(s->ref);						\
}


/**
	{function:
    	{name: LmiSharedPtrUnique}
		{parent: LmiSharedPtr}
		{description: Get the whether a shared pointer is unique, i.e. its use count is 1.}
		{prototype: LmiBool LmiSharedPtrUnique(T_)(const LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer whose uniqueness to get.}}
		{return: Whether the shared pointer's use-count is 1.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::unique()}.}
		{note: This function will return false for an empty shared pointer (one constructed with LmiSharedPtrConstructDefault(T_)).}
	}
*/
#define Declare_LmiSharedPtrUnique(T_) \
LMI_INLINE_DECLARATION LmiBool LmiSharedPtrUnique(T_)(const LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrUnique(T_, INLINE_)					\
INLINE_																	\
LmiBool LmiSharedPtrUnique(T_)(const LmiSharedPtr(T_)* s)				\
{																		\
	if (s->ref == NULL)													\
		return LMI_FALSE;												\
	return LmiSharedPtrRefCountGetUseCount(s->ref) == 1;				\
}

/**
	{function:
    	{name: LmiSharedPtrGetDeleter}
		{parent: LmiSharedPtr}
		{description: Get the deleter associated with a shared pointer.}
		{prototype: LmiSharedPtrDeleterCallback LmiSharedPtrGetDeleter(T_)(const LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer whose deleter to get.}}
		{return: The deleter associated with the shared pointer.  If the shared pointer was constructed without an explicit deleter, the default deleter function for the type is returned.  For a default-constructed shared pointer, this may be NULL.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<T_>::get_deleter() const}.}
	}
*/
#define Declare_LmiSharedPtrGetDeleter(T_) \
LMI_INLINE_DECLARATION LmiSharedPtrDeleterCallback LmiSharedPtrGetDeleter(T_)(const LmiSharedPtr(T_)* s);

#define DefineInline_LmiSharedPtrGetDeleter(T_, INLINE_)					\
INLINE_																	\
LmiSharedPtrDeleterCallback LmiSharedPtrGetDeleter(T_)(const LmiSharedPtr(T_)* s) \
{																		\
	return s->d;														\
}

/**
	{function:
		{name: LmiSharedPtrMakeUnique}
		{parent: LmiSharedPtr}
		{description: Cause a shared pointer to become unique, by duplicating the underlying
			object it points to.}
		{prototype: LmiBool LmiSharedPtrMakeUnique(T_)(LmiSharedPtr(T_)* s)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: s} {description: The shared pointer to make unique.}}
		{return: LMI_TRUE if the pointer was successfully made unique, LMI_FALSE otherwise.}
		{note: If the shared pointer was already unique prior to this function being called,
			the function will do nothing and return LMI_TRUE.  If the shared pointer was empty,
			the function will do nothing and return LMI_FALSE.}
		{note: An expansion of the macro Declare_LmiSharedPtrMakeUnique(T) must be in
			scope before invoking this function, and an expansion
			of the macro Define_LmiSharedPtrMakeUnique(T) must be present in exactly
			one object file at link time.  This function is not included in Declare_LmiSharedPtr.}
		{note: The type pointed to by this shared pointer must have a ConstructCopy method
			LmiConstructCopy(T_).}
		{note: The underlying object will be duplicated by calling LmiConstructCopy(T_), writing
			into memory of size sizeof(T_).  If the underlying object is not actually of type T_
			-- for instance, if it is actually a derivative class, or if the shared pointer
			was created by LmiSharedPtrConstructFromOtherSharedPtr -- this will probably do
			the wrong thing.}
		{note: This will invalidate any previous value returned by LmiSharedPtrGet on this shared
			pointer.}
		{note: This does not correspond to any ISO C++ TR1 function.}
	}
*/
#define Declare_LmiSharedPtrMakeUnique(T_) \
LmiBool LmiSharedPtrMakeUnique(T_)(LmiSharedPtr(T_)* s);

#define Define_LmiSharedPtrMakeUnique(T_)						\
LmiBool LmiSharedPtrMakeUnique(T_)(LmiSharedPtr(T_)* s)				\
{																	\
	T_ *p, *new_p;													\
	LmiSharedPtr(T_) new_s;											\
	LmiAllocator* a;												\
																	\
	p = LmiSharedPtrGet(T_)(s);										\
																	\
	if (p == NULL)													\
		return LMI_FALSE;											\
	if (LmiSharedPtrUnique(T_)(s))									\
		return LMI_TRUE;											\
																	\
	a = LmiSharedPtrGetAllocator(T_)(s);							\
																	\
	if ((new_p = (T_*)LmiAllocatorAllocate(a, sizeof(T_))) == NULL)	\
		goto FAIL_Allocate;											\
																	\
	if (LmiConstructCopy(T_)(new_p, p) == NULL)						\
		goto FAIL_ConstructCopy;									\
																	\
	if (LmiSharedPtrConstructWithDeleter(T_)(&new_s, new_p,			\
			LmiSharedPtrGetDeleter(T_)(s), a) == NULL)				\
		goto FAIL_ConstructSharedPtr;								\
																	\
	LmiSharedPtrSwap(T_)(&new_s, s);								\
	LmiSharedPtrDestruct(T_)(&new_s);								\
	return LMI_TRUE;												\
																	\
FAIL_ConstructSharedPtr:											\
																	\
	LmiDestruct(T_)(new_p);											\
FAIL_ConstructCopy:													\
																	\
	LmiAllocatorDeallocate(a, new_p, sizeof(T_));					\
FAIL_Allocate:														\
																	\
	return LMI_FALSE;												\
}

/**
	{function:
    	{name: LmiWeakPtrConstructDefault}
		{parent: LmiWeakPtr}
		{description: Construct an empty weak pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructDefault(T_)(LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The empty weak pointer to construct.}}
		{return: The constructed weak pointer.  Does not fail.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr()}.}
	}
*/
#define Declare_LmiWeakPtrConstructDefault(T_) \
LMI_INLINE_DECLARATION													\
LmiWeakPtr(T_)* LmiWeakPtrConstructDefault(T_)(LmiWeakPtr(T_) * w_);


#define DefineInline_LmiWeakPtrConstructDefault(T_, INLINE_)			\
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrConstructDefault(T_)(LmiWeakPtr(T_) * w_) \
{																		\
	w_->ref = NULL;														\
	w_->ptr = NULL;														\
	w_->a = NULL;														\
	w_->d = NULL;														\
	return w_;															\
}
	

/**
	{function:
    	{name: LmiWeakPtrDestruct}
		{parent: LmiWeakPtr}
		{description: Destruct a weak pointer.}
		{prototype: void LmiWeakPtrDestruct(T_)(LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to destruct.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::~weak_ptr()}.}
	}
*/

#define Declare_LmiWeakPtrDestruct(T_) \
LMI_INLINE_DECLARATION void LmiWeakPtrDestruct(T_)(LmiWeakPtr(T_) * w_);


#define DefineInline_LmiWeakPtrDestruct(T_, INLINE_)			\
INLINE_															\
void LmiWeakPtrDestruct(T_)(LmiWeakPtr(T_) * w_)				\
{																\
	LmiWeakPtrDecWeakCount_(T_)(w_);							\
}

/**
	{function:
    	{name: LmiWeakPtrConstructCopy}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer as a copy of an existing one, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructCopy(T_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer to copy.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(weak_ptr& const)}.}
	}
*/
#define Declare_LmiWeakPtrConstructCopy(T_) \
LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrConstructCopy(T_)(LmiWeakPtr(T_) * w_, const LmiWeakPtr(T_)* orig);
	
#define DefineInline_LmiWeakPtrConstructCopy(T_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrConstructCopy(T_)(LmiWeakPtr(T_)* w_, const LmiWeakPtr(T_)* orig) \
{																		\
	w_->ref = orig->ref;												\
	w_->ptr = orig->ptr;												\
	w_->a = orig->a;													\
	w_->d = orig->d;													\
	if (!LmiWeakPtrIncWeakCount_(T_)(w_)) {								\
		w_->ref = NULL;													\
		return NULL;													\
	}																	\
	return w_;															\
}

/**
	{function:
    	{name: LmiWeakPtrConstructFromOtherWeakPtr}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer from a weak pointer of a different type, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_)* s, const LmiWeakPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer to construct.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing weak pointer.}}
		{parameter: {name: s} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer.  The type of the object pointed to by this weak pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(weak_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_)			\
	LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_) * s_, const LmiWeakPtr(U_)* orig);
	
#define DefineInline_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_)* s_, const LmiWeakPtr(U_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = (T_*)orig->ptr;											\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiWeakPtrIncWeakCount_(T_)(s_)) {								\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}

/**
	{function:
    	{name: LmiWeakPtrConstructFromWeakVoidPtr}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer from a weak void pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructFromWeakVoidPtr(T_)(LmiWeakPtr(T_)* s, const LmiWeakVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: s} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak void pointer.  The actual type of the object pointed to by the weak void pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(weak_ptr<void>& const)}.}
	}
*/


/**
	{function:
    	{name: LmiWeakVoidPtrConstructFromWeakPtr}
		{parent: LmiWeakVoidPtr}
		{description: Construct a weak void pointer from a weak pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrConstructFromWeakPtr(T_)(LmiWeakVoidPtr* s, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the original weak pointer.}}
		{parameter: {name: s} {description: The weak void pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak pointer.}}
		{return: The constructed weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::weak_ptr(weak_ptr<T_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/


/**
	{function:
    	{name: LmiWeakPtrConstructFromSharedPtr}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer based on a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructFromSharedPtr(T_)(LmiWeakPtr(T_)* w, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer to copy.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(shared_ptr& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/
#define Declare_LmiWeakPtrConstructFromSharedPtr(T_) \
LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrConstructFromSharedPtr(T_)(LmiWeakPtr(T_) * w_, const LmiSharedPtr(T_)* orig);
	
#define DefineInline_LmiWeakPtrConstructFromSharedPtr(T_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrConstructFromSharedPtr(T_)(LmiWeakPtr(T_)* w_, const LmiSharedPtr(T_)* orig) \
{																		\
	w_->ref = orig->ref;												\
	w_->ptr = orig->ptr;												\
	w_->a = orig->a;													\
	w_->d = orig->d;													\
	if (!LmiWeakPtrIncWeakCount_(T_)(w_)) {								\
		w_->ref = NULL;													\
		return NULL;													\
	}																	\
	return w_;															\
}


/**
	{function:
    	{name: LmiWeakPtrConstructFromOtherSharedPtr}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer based on a shared pointer of a different type, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherSharedPtr(T_, U_)(LmiWeakPtr(T_)* s, const LmiSharedPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer to construct.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing shared pointer.}}
		{parameter: {name: s} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.  The type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(shared_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) \
	LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherSharedPtr(T_,U_)(LmiWeakPtr(T_) * s_, const LmiSharedPtr(U_)* orig);
	
#define DefineInline_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrConstructFromOtherSharedPtr(T_,U_)(LmiWeakPtr(T_)* s_, const LmiSharedPtr(U_)* orig) \
{																		\
	s_->ref = orig->ref;												\
	s_->ptr = (T_*)orig->ptr;											\
	s_->a = orig->a;													\
	s_->d = orig->d;													\
	if (!LmiWeakPtrIncWeakCount_(T_)(s_)) {								\
		s_->ref = NULL;													\
		return NULL;													\
	}																	\
	return s_;															\
}


/**
	{function:
    	{name: LmiWeakPtrConstructFromSharedVoidPtr}
		{parent: LmiWeakPtr}
		{description: Construct a weak pointer based on a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrConstructFromSharedVoidPtr(T_)(LmiWeakPtr(T_)* s, const LmiSharedVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer to construct.}}
		{parameter: {name: s} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared void pointer.  The type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::weak_ptr(shared_ptr<void>& const)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrConstructFromSharedPtr}
		{parent: LmiWeakVoidPtr}
		{description: Construct a weak void pointer based on a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrConstructFromSharedPtr(T_)(LmiWeakVoidPtr* s, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the existing shared pointer.}}
		{parameter: {name: s} {description: The weak void pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.}}
		{return: The constructed weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::weak_ptr(shared_ptr<T_>& const)}.}
	}
*/


/**
	{function:
    	{name: LmiWeakPtrGetAllocator}
		{parent: LmiWeakPtr}
		{description: Get the allocator used by a weak pointer.}
		{prototype: LmiAllocator* LmiWeakPtrGetAllocator(T_)(const LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer whose allocator to get.}}
		{return: The allocator used by the weak pointer, or NULL if the weak pointer is empty.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::get_allocator() const}.}
	}
*/
#define Declare_LmiWeakPtrGetAllocator(T_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiWeakPtrGetAllocator(T_)(const LmiWeakPtr(T_)* w);

#define DefineInline_LmiWeakPtrGetAllocator(T_, INLINE_)				\
INLINE_																	\
LmiAllocator* LmiWeakPtrGetAllocator(T_)(const LmiWeakPtr(T_)* w) \
{																		\
	return w->a;														\
}


/**
	{function:
    	{name: LmiWeakPtrAssign}
		{parent: LmiWeakPtr}
		{description: Assign the value of one weak pointer to another existing one.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssign(T_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to assign.}}
		{parameter: {name: orig} {description: An existing weak pointer to copy.}}
		{return: The assigned-to weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(weak_ptr& const)}.}
		{note: If s and orig refer to different weak pointers, s\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/
#define Declare_LmiWeakPtrAssign(T_) \
LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrAssign(T_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(T_)* orig);

#define DefineInline_LmiWeakPtrAssign(T_, INLINE_)						\
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrAssign(T_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(T_)* orig) \
{																		\
	if (w->ref != orig->ref) {											\
		LmiWeakPtrDecWeakCount_(T_)(w);									\
		w->ref = orig->ref;												\
		w->ptr = orig->ptr;												\
		w->d = orig->d;													\
		w->a = orig->a;													\
		if (!LmiWeakPtrIncWeakCount_(T_)(w)) {							\
			w->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		w->ptr = orig->ptr;												\
		w->d = orig->d;													\
		w->a = orig->a;													\
	}																	\
																		\
	return w;															\
}


/**
	{function:
    	{name: LmiWeakPtrAssignFromOtherWeakPtr}
		{parent: LmiWeakPtr}
		{description: Assign the value of a weak pointer to a weak pointer of a different type.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer to assign.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the existing weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to assign.}}
		{parameter: {name: orig} {description: An existing weak pointer.  The type of the object pointed to by this weak pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(weak_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) must be present in exactly
			one object file at link time.}
		{note: If w and orig refer to different weak pointers, w\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/
#define Declare_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_)			\
	LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_) * w, const LmiWeakPtr(U_)* orig);
	
#define DefineInline_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_, INLINE_) \
INLINE_																	\
 LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherWeakPtr(T_, U_)(LmiWeakPtr(T_)* w, const LmiWeakPtr(U_)* orig) \
{																		\
	if (w->ref != orig->ref) {											\
		LmiWeakPtrDecWeakCount_(T_)(w);									\
		w->ref = orig->ref;												\
		w->ptr = (T_*)orig->ptr;										\
		w->d = orig->d;													\
		w->a = orig->a;													\
		if (!LmiWeakPtrIncWeakCount_(T_)(w)) {							\
			w->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		w->ptr = (T_*)orig->ptr;										\
		w->d = orig->d;													\
		w->a = orig->a;													\
	}																	\
																		\
	return w;															\
}


/**
	{function:
    	{name: LmiWeakPtrAssignFromWeakVoidPtr}
		{parent: LmiWeakPtr}
		{description: Assign the value of a weak void pointer to a weak pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssignFromWeakVoidPtr(T_)(LmiWeakPtr(T_)* w, const LmiWeakVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to assign.}}
		{parameter: {name: orig} {description: An existing weak void pointer.  The underlying type of the object pointed to by this weak pointer must be compatible with T_.}}
		{return: The constructed weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(weak_ptr<void>& const)}.}
		{note: If w and orig refer to different weak pointers, w\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/


/**
	{function:
    	{name: LmiWeakVoidPtrAssignFromWeakPtr}
		{parent: LmiWeakPtr}
		{description: Assign the value of a weak pointer to a weak void pointer.}
		{prototype: LmiWeakVoidPtr LmiWeakVoidPtrAssignFromWeakPtr(T_)(LmiWeakVoidPtr* w, const LmiWeakPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the existing weak pointer.}}
		{parameter: {name: w} {description: The weak void pointer to assign.}}
		{parameter: {name: orig} {description: An existing weak pointer}}
		{return: The assigned-to weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::operator=(weak_ptr<T_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
		{note: If w and orig refer to different weak pointers, w\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/

/**
	{function:
		{name: LmiWeakPtrAssignFromSharedPtr}
		{parent: LmiWeakPtr}
		{description: Assign to a weak pointer from a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssignFromSharedPtr(T_)(LmiWeakPtr(T_)* w, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to assign to.}}
		{parameter: {name: orig} {description: An existing shared pointer to copy.}}
		{return: The assigned-to weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(shared_ptr<T_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/
#define Declare_LmiWeakPtrAssignFromSharedPtr(T_) \
LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrAssignFromSharedPtr(T_)(LmiWeakPtr(T_) * w, const LmiSharedPtr(T_)* orig);
	
#define DefineInline_LmiWeakPtrAssignFromSharedPtr(T_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrAssignFromSharedPtr(T_)(LmiWeakPtr(T_)* w, const LmiSharedPtr(T_)* orig) \
{																		\
	if (w->ref != orig->ref) {											\
		LmiWeakPtrDecWeakCount_(T_)(w);									\
		w->ref = orig->ref;												\
		w->ptr = orig->ptr;												\
		w->a = orig->a;													\
		w->d = orig->d;													\
		if (!LmiWeakPtrIncWeakCount_(T_)(w)) {							\
			w->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		w->ptr = orig->ptr;												\
		w->d = orig->d;													\
		w->a = orig->a;													\
	}																	\
	return w;															\
}

/**
	{function:
    	{name: LmiWeakPtrAssignFromOtherSharedPtr}
		{parent: LmiWeakPtr}
		{description: Assign to a weak pointer from a shared pointer of a different type, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherSharedPtr(T_, U_)(LmiWeakPtr(T_)* w, const LmiSharedPtr(U_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{template-parameter:
			{name: U_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: w} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.  The type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The assigned-to weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(shared_ptr<U_>& const)}.}
		{note: An expansion of the macro Declare_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) must be in
			scope before declaring an object of this type, and an expansion
			of the macro Define_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) must be present in exactly
			one object file at link time.}
	}
*/
#define Declare_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) \
	LMI_INLINE_DECLARATION LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherSharedPtr(T_,U_)(LmiWeakPtr(T_) * w, const LmiSharedPtr(U_)* orig);
	
#define DefineInline_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_, INLINE_) \
INLINE_																	\
LmiWeakPtr(T_)* LmiWeakPtrAssignFromOtherSharedPtr(T_,U_)(LmiWeakPtr(T_)* w, const LmiSharedPtr(U_)* orig) \
{																		\
	if (w->ref != orig->ref) {											\
		LmiWeakPtrDecWeakCount_(T_)(w);									\
		w->ref = orig->ref;												\
		w->ptr = (T_*)orig->ptr;										\
		w->a = orig->a;													\
		w->d = orig->d;													\
		if (!LmiWeakPtrIncWeakCount_(T_)(w)) {							\
			w->ref = NULL;												\
			return NULL;												\
		}																\
	}																	\
	else {																\
		w->ptr = (T_*)orig->ptr;										\
		w->d = orig->d;													\
		w->a = orig->a;													\
	}																	\
	return w;															\
}

/**
	{function:
    	{name: LmiWeakPtrAssignFromSharedVoidPtr}
		{parent: LmiWeakPtr}
		{description: Assign to a weak pointer from a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakPtr(T_)* LmiWeakPtrAssignFromSharedVoidPtr(T_)(LmiWeakPtr(T_)* w, const LmiSharedVoidPtr* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared void pointer.  The underlying type of the object pointed to by this shared pointer must be compatible with T_.}}
		{return: The assigned-to weak pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::operator=(shared_ptr<void>& const)}.}
	}
*/


/**
	{function:
    	{name: LmiWeakVoidPtrAssignFromSharedPtr}
		{parent: LmiWeakVoidPtr}
		{description: Assign to a weak void pointer from a shared pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr LmiWeakVoidPtrAssignFromSharedPtr(T_)(LmiWeakVoidPtr* w, const LmiSharedPtr(T_)* orig)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the shared pointer.}}
		{parameter: {name: w} {description: The weak void pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared pointer.}}
		{return: The assigned-to weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::operator=(shared_ptr<U_>& const)}.}
		{note: This function is declared and defined by Declare_LmiSharedPtr(T_) and Define_LmiSharedPtr(T_) respectively.}
	}
*/


/**
	{function:
    	{name: LmiWeakPtrSwap}
		{parent: LmiWeakPtr}
		{description: Swap the values of two weak pointers.}
		{prototype: LmiBool LmiWeakPtrSwap(T_)(LmiWeakPtr(T_)* a, LmiWeakPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointers.}}
		{parameter: {name: a} {description: The first weak pointer to be swapped.}}
		{parameter: {name: b} {description: The second weak pointer to be swapped.}}
		{return: LMI_TRUE, always (cannot fail).}
		{note: Like ISO C++ TR1 function {code: template<T_> std::swap(std::tr1::weak_ptr<T_>&, std::tr1::weak_ptr<T_>&)}.}
	}
*/
#define Declare_LmiWeakPtrSwap(T_) \
LMI_INLINE_DECLARATION LmiBool LmiWeakPtrSwap(T_)(LmiWeakPtr(T_)* a, LmiWeakPtr(T_)* b);

#define DefineInline_LmiWeakPtrSwap(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiWeakPtrSwap(T_)(LmiWeakPtr(T_)* a, LmiWeakPtr(T_)* b)		\
{																		\
	LmiWeakPtr(T_) tmp;													\
																		\
	tmp = *a;															\
	*a = *b;															\
	*b = tmp;															\
																		\
	return LMI_TRUE;													\
}


/**
	{function:
    	{name: LmiWeakPtrReset}
		{parent: LmiWeakPtr}
		{description: Reset the value of a weak pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: void LmiWeakPtrReset(T_)(LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer to be reset.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::reset()}.}
	}
*/
#define Declare_LmiWeakPtrReset(T_) \
LMI_INLINE_DECLARATION void LmiWeakPtrReset(T_)(LmiWeakPtr(T_)* w);

#define DefineInline_LmiWeakPtrReset(T_, INLINE_)						\
INLINE_																	\
void LmiWeakPtrReset(T_)(LmiWeakPtr(T_)* w_)							\
{																		\
	LmiWeakPtrDecWeakCount_(T_)(w_);									\
																		\
	w_->ref = NULL;														\
	w_->ptr = NULL;														\
	w_->a = NULL;														\
	w_->d = NULL;														\
}


/**
	{function:
    	{name: LmiWeakPtrEqual}
		{parent: LmiWeakPtr}
		{description: Compare the values of two weak pointers for equality.}
		{prototype: LmiBool LmiWeakPtrEqual(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointers.}}
		{parameter: {name: a} {description: The first weak pointer to compare.}}
		{parameter: {name: b} {description: The second weak pointer to compare.}}
		{return: Whether the pointers contained in the weak pointer objects are the same.}
		{note: Like ISO C++ TR1 function {code: template<T_> operator==(const std::tr1::weak_ptr<T_>&, const std::tr1::weak_ptr<T_>&)}.}
	}
*/
#define Declare_LmiWeakPtrEqual(T_) \
LMI_INLINE_DECLARATION LmiBool LmiWeakPtrEqual(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b);

#define DefineInline_LmiWeakPtrEqual(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiWeakPtrEqual(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b)	\
{																		\
	return a->ref == b->ref;											\
}


/**
	{function:
    	{name: LmiWeakPtrLess}
		{parent: LmiWeakPtr}
		{description: Compare the values of two weak pointers for ordering.}
		{prototype: LmiBool LmiWeakPtrLess(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointers.}}
		{parameter: {name: a} {description: The first weak pointer to compare.}}
		{parameter: {name: b} {description: The second weak pointer to compare.}}
		{return: Whether the pointer contained in the first weak pointer objects is less than the second one.}
		{note: Like ISO C++ TR1 function {code: template<T_> operator<(const std::tr1::weak_ptr<T_>&, const std::tr1::weak_ptr<T_>&)}.}
	}
*/
#define Declare_LmiWeakPtrLess(T_) \
LMI_INLINE_DECLARATION LmiBool LmiWeakPtrLess(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b);

#define DefineInline_LmiWeakPtrLess(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiWeakPtrLess(T_)(const LmiWeakPtr(T_)* a, const LmiWeakPtr(T_)* b)	\
{																		\
	return a->ref < b->ref;												\
}


/**
	{function:
    	{name: LmiWeakPtrUseCount}
		{parent: LmiWeakPtr}
		{description: Get the current use-count of a weak pointer.}
		{prototype: LmiInt LmiWeakPtrUseCount(T_)(const LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer whose use count to get.}}
		{return: The use count of the weak pointer.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::use_count()}.}
	}
*/
#define Declare_LmiWeakPtrUseCount(T_) \
LMI_INLINE_DECLARATION LmiInt LmiWeakPtrUseCount(T_)(const LmiWeakPtr(T_)* w);

#define DefineInline_LmiWeakPtrUseCount(T_, INLINE_)					\
INLINE_																	\
LmiInt LmiWeakPtrUseCount(T_)(const LmiWeakPtr(T_)* w)					\
{																		\
	if (w->ref == NULL)													\
		return 0;														\
	return LmiSharedPtrRefCountGetUseCount(w->ref);						\
}


/**
	{function:
    	{name: LmiWeakPtrExpired}
		{parent: LmiWeakPtr}
		{description: Get the whether a weak pointer is expired, i.e. its use count is 0.}
		{prototype: LmiBool LmiWeakPtrExpired(T_)(const LmiWeakPtr(T_)* w)}
		{template-parameter:
			{name: T_} {description: The type pointed to by the weak pointer.}}
		{parameter: {name: w} {description: The weak pointer whose expiredness to get.}}
		{return: Whether the weak pointer's use-count is 0.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<T_>::expired()}.}
		{note: This function will return true for an empty weak pointer (one constructed with LmiWeakPtrConstructDefault(T_)).}
	}
*/
#define Declare_LmiWeakPtrExpired(T_) \
LMI_INLINE_DECLARATION LmiBool LmiWeakPtrExpired(T_)(const LmiWeakPtr(T_)* w);

#define DefineInline_LmiWeakPtrExpired(T_, INLINE_)						\
INLINE_																	\
LmiBool LmiWeakPtrExpired(T_)(const LmiWeakPtr(T_)* w)					\
{																		\
	if (w->ref == NULL)													\
		return LMI_TRUE;												\
	return LmiSharedPtrRefCountGetUseCount(w->ref) == 0;				\
}

/* Declarations of LmiSharedPtr functions */
/* Functions that are also used for LmiSharedVoidPtr */
#define Declare_LmiSharedPtrBaseFuncs(T_)	\
  Declare_LmiSharedPtrIncUseCount_(T_)		   \
  Declare_LmiSharedPtrIncUseCountConditional_(T_)	\
  Declare_LmiSharedPtrDecUseCount_(T_)		   \
  Declare_LmiSharedPtrConstructDefault(T_)	   \
  Declare_LmiSharedPtrConstructWithDeleter(T_) \
  Declare_LmiSharedPtrConstructFromWeakPtr(T_) \
  Declare_LmiSharedPtrDestruct(T_)			   \
  Declare_LmiSharedPtrConstructCopy(T_)		   \
  Declare_LmiSharedPtrGetAllocator(T_)		   \
  Declare_LmiSharedPtrAssign(T_)			   \
  Declare_LmiSharedPtrSwap(T_)				   \
  Declare_LmiSharedPtrReset(T_)				   \
  Declare_LmiSharedPtrEqual(T_)				   \
  Declare_LmiSharedPtrLess(T_)				   \
  Declare_LmiSharedPtrGet(T_)				   \
  Declare_LmiSharedPtrUseCount(T_)			   \
  Declare_LmiSharedPtrUnique(T_)			   \
  Declare_LmiSharedPtrGetDeleter(T_)

#define Declare_LmiSharedPtrFuncs(T_)		   \
  Declare_LmiSharedPtrBaseFuncs(T_)		       \
  Declare_LmiSharedPtrDefaultDeleter_(T_)	   \
  Declare_LmiSharedPtrConstruct(T_)			   \
  Declare_LmiSharedPtrConstructFromOtherSharedPtr(T_, void)	\
  Declare_LmiSharedPtrConstructFromOtherSharedPtr(void, T_)	\
  Declare_LmiSharedPtrConstructFromOtherWeakPtr(T_, void)	\
  Declare_LmiSharedPtrConstructFromOtherWeakPtr(void, T_) \
  Declare_LmiSharedPtrAssignFromOtherSharedPtr(T_, void)	\
  Declare_LmiSharedPtrAssignFromOtherSharedPtr(void, T_)


#define Declare_LmiWeakPtrBaseFuncs(T_)		   \
  Declare_LmiWeakPtrIncWeakCount_(T_)		   \
  Declare_LmiWeakPtrDecWeakCount_(T_)		   \
  Declare_LmiWeakPtrConstructDefault(T_)	   \
  Declare_LmiWeakPtrConstructFromSharedPtr(T_) \
  Declare_LmiWeakPtrDestruct(T_)			   \
  Declare_LmiWeakPtrConstructCopy(T_)		   \
  Declare_LmiWeakPtrGetAllocator(T_)		   \
  Declare_LmiWeakPtrAssign(T_)				   \
  Declare_LmiWeakPtrAssignFromSharedPtr(T_)	   \
  Declare_LmiWeakPtrSwap(T_)				   \
  Declare_LmiWeakPtrReset(T_)				   \
  Declare_LmiWeakPtrEqual(T_)				   \
  Declare_LmiWeakPtrLess(T_)				   \
  Declare_LmiWeakPtrUseCount(T_)			   \
  Declare_LmiWeakPtrExpired(T_)

#define Declare_LmiWeakPtrFuncs(T_)		   \
  Declare_LmiWeakPtrBaseFuncs(T_)		       \
  Declare_LmiWeakPtrConstructFromOtherWeakPtr(T_, void)	\
  Declare_LmiWeakPtrConstructFromOtherWeakPtr(void, T_)	\
  Declare_LmiWeakPtrConstructFromOtherSharedPtr(T_, void)	\
  Declare_LmiWeakPtrConstructFromOtherSharedPtr(void, T_) \
  Declare_LmiWeakPtrAssignFromOtherWeakPtr(T_, void)	\
  Declare_LmiWeakPtrAssignFromOtherWeakPtr(void, T_)	\
  Declare_LmiWeakPtrAssignFromOtherSharedPtr(T_, void)	\
  Declare_LmiWeakPtrAssignFromOtherSharedPtr(void, T_)


/* Inlined LmiSharedPtr functions */
#define DefineInline_LmiSharedPtrFuncs_Internal(T_, INLINE_)            \
	DefineInline_LmiSharedPtrIncUseCount_(T_, INLINE_)					\
	DefineInline_LmiSharedPtrIncUseCountConditional_(T_, INLINE_)		\
	DefineInline_LmiSharedPtrDecUseCount_(T_, INLINE_)


#define DefineInline_LmiSharedPtrFuncs_PublicBase(T_, INLINE_)	   \
	DefineInline_LmiSharedPtrConstructDefault(T_, INLINE_)	   \
	DefineInline_LmiSharedPtrConstructFromWeakPtr(T_, INLINE_) \
	DefineInline_LmiSharedPtrDestruct(T_, INLINE_)			   \
	DefineInline_LmiSharedPtrConstructCopy(T_, INLINE_)		   \
	DefineInline_LmiSharedPtrGetAllocator(T_, INLINE_)		   \
	DefineInline_LmiSharedPtrAssign(T_, INLINE_)			   \
	DefineInline_LmiSharedPtrSwap(T_, INLINE_)				   \
	DefineInline_LmiSharedPtrReset(T_, INLINE_)				   \
	DefineInline_LmiSharedPtrEqual(T_, INLINE_)				   \
	DefineInline_LmiSharedPtrLess(T_, INLINE_)				   \
	DefineInline_LmiSharedPtrGet(T_, INLINE_)				   \
	DefineInline_LmiSharedPtrUseCount(T_, INLINE_)			   \
	DefineInline_LmiSharedPtrUnique(T_, INLINE_)			   \
	DefineInline_LmiSharedPtrGetDeleter(T_, INLINE_)

#define DefineInline_LmiSharedPtrFuncs_PublicExtra(T_, INLINE_)			\
	DefineInline_LmiSharedPtrConstructFromOtherSharedPtr(T_, void, INLINE_)	\
	DefineInline_LmiSharedPtrConstructFromOtherSharedPtr(void, T_, INLINE_)	\
	DefineInline_LmiSharedPtrConstructFromOtherWeakPtr(T_, void, INLINE_) \
	DefineInline_LmiSharedPtrConstructFromOtherWeakPtr(void, T_, INLINE_) \
	DefineInline_LmiSharedPtrAssignFromOtherSharedPtr(T_, void, INLINE_)	\
	DefineInline_LmiSharedPtrAssignFromOtherSharedPtr(void, T_, INLINE_)

/* Inlined LmiWeakPtr functions */
#define DefineInline_LmiWeakPtrFuncs_Internal(T_, INLINE_)	   \
	DefineInline_LmiWeakPtrIncWeakCount_(T_, INLINE_)		   \
	DefineInline_LmiWeakPtrDecWeakCount_(T_, INLINE_)		   \

#define DefineInline_LmiWeakPtrFuncs_PublicBase(T_, INLINE_)   \
	DefineInline_LmiWeakPtrConstructDefault(T_, INLINE_)	   \
	DefineInline_LmiWeakPtrConstructFromSharedPtr(T_, INLINE_) \
	DefineInline_LmiWeakPtrDestruct(T_, INLINE_)			   \
	DefineInline_LmiWeakPtrConstructCopy(T_, INLINE_)		   \
	DefineInline_LmiWeakPtrGetAllocator(T_, INLINE_)		   \
	DefineInline_LmiWeakPtrAssign(T_, INLINE_)				   \
	DefineInline_LmiWeakPtrAssignFromSharedPtr(T_, INLINE_)	   \
	DefineInline_LmiWeakPtrSwap(T_, INLINE_)				   \
	DefineInline_LmiWeakPtrReset(T_, INLINE_)				   \
	DefineInline_LmiWeakPtrEqual(T_, INLINE_)				   \
	DefineInline_LmiWeakPtrLess(T_, INLINE_)				   \
	DefineInline_LmiWeakPtrUseCount(T_, INLINE_)			   \
	DefineInline_LmiWeakPtrExpired(T_, INLINE_)

#define DefineInline_LmiWeakPtrFuncs_PublicExtra(T_, INLINE_)	   \
	DefineInline_LmiWeakPtrConstructFromOtherWeakPtr(T_, void, INLINE_) \
	DefineInline_LmiWeakPtrConstructFromOtherWeakPtr(void, T_, INLINE_) \
	DefineInline_LmiWeakPtrConstructFromOtherSharedPtr(T_, void, INLINE_)	\
	DefineInline_LmiWeakPtrConstructFromOtherSharedPtr(void, T_, INLINE_) \
	DefineInline_LmiWeakPtrAssignFromOtherWeakPtr(T_, void, INLINE_) \
	DefineInline_LmiWeakPtrAssignFromOtherWeakPtr(void, T_, INLINE_) \
	DefineInline_LmiWeakPtrAssignFromOtherSharedPtr(T_, void, INLINE_)	\
	DefineInline_LmiWeakPtrAssignFromOtherSharedPtr(void, T_, INLINE_)
	

/* Non-inlined LmiSharedPtr functions */
#define Define_LmiSharedPtrFuncs(T_) \
  Define_LmiSharedPtrConstruct(T_) \
  Define_LmiSharedPtrConstructWithDeleter(T_) \
  Define_LmiSharedPtrDefaultDeleter_(T_)

/* No non-inlined LmiWeakPtr functions */


#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS

#define DefineInlineHeader_LmiSharedPtrFuncs(T_) \
  DefineInline_LmiSharedPtrFuncs_Internal(T_, LMI_INLINE) \
  DefineInline_LmiSharedPtrFuncs_PublicBase(T_, LMI_INLINE)	  \
  DefineInline_LmiSharedPtrFuncs_PublicExtra(T_, LMI_INLINE)	  \
  DefineInline_LmiWeakPtrFuncs_Internal(T_, LMI_INLINE)	  \
  DefineInline_LmiWeakPtrFuncs_PublicBase(T_, LMI_INLINE) \
  DefineInline_LmiWeakPtrFuncs_PublicExtra(T_, LMI_INLINE)

#define DefineInlineHeader_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_, LMI_INLINE)
#define DefineInlineHeader_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_, LMI_INLINE)

#define DefineInlineHeader_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_, LMI_INLINE)

#define DefineInlineHeader_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_, LMI_INLINE)
#define DefineInlineHeader_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_, LMI_INLINE)

#define DefineInlineHeader_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_, LMI_INLINE)
#define DefineInlineHeader_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_, LMI_INLINE)



#else

#define DefineInlineHeader_LmiSharedPtrFuncs(T_) /* (defined as empty) */

#define DefineInlineHeader_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineHeader_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineHeader_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineHeader_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineHeader_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineHeader_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineHeader_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */

#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS

#define DefineInlineSource_LmiSharedPtrFuncs(T_) \
  DefineInline_LmiSharedPtrFuncs_Internal(T_, LMI_INLINE_SOURCE_FILE) \
  DefineInline_LmiSharedPtrFuncs_PublicBase(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiSharedPtrFuncs_PublicExtra(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiWeakPtrFuncs_Internal(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiWeakPtrFuncs_PublicBase(T_, LMI_INLINE_SOURCE_FILE) \
  DefineInline_LmiWeakPtrFuncs_PublicExtra(T_, LMI_INLINE_SOURCE_FILE)

#define DefineInlineSource_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_, LMI_INLINE_SOURCE_FILE)
#define DefineInlineSource_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_, LMI_INLINE_SOURCE_FILE)

#define DefineInlineSource_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_, LMI_INLINE_SOURCE_FILE)

#define DefineInlineSource_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_, LMI_INLINE_SOURCE_FILE)
#define DefineInlineSource_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_, LMI_INLINE_SOURCE_FILE)

#define DefineInlineSource_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) \
	DefineInline_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_, LMI_INLINE_SOURCE_FILE)
#define DefineInlineSource_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) \
	DefineInline_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_, LMI_INLINE_SOURCE_FILE)

#else

#define DefineInlineSource_LmiSharedPtrFuncs(T_) /* (defined as empty) */

#define DefineInlineSource_LmiSharedPtrConstructFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineSource_LmiSharedPtrConstructFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineSource_LmiSharedPtrAssignFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineSource_LmiWeakPtrConstructFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineSource_LmiWeakPtrConstructFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */

#define DefineInlineSource_LmiWeakPtrAssignFromOtherWeakPtr(T_, U_) \
	/* (defined as empty) */
#define DefineInlineSource_LmiWeakPtrAssignFromOtherSharedPtr(T_, U_) \
	/* (defined as empty) */


#endif

#define Declare_LmiSharedPtr(T_)										\
	Declare_LmiSharedPtrClass(T_)										\
	Declare_LmiWeakPtrClass(T_)											\
    Declare_LmiSharedPtrFuncs(T_)										\
    Declare_LmiWeakPtrFuncs(T_)											\
    DefineInlineHeader_LmiSharedPtrFuncs(T_)							\

#define Define_LmiSharedPtr(T_)					\
	DefineInlineSource_LmiSharedPtrFuncs(T_)	\
	Define_LmiSharedPtrFuncs(T_)

/* For the sake of validation, make Declare_LmiWeakPtr a synonym for
   Declare_LmiSharedPtr (and similarly for Define.).  Actual code should only use
   the SharedPtr version.  Declaring both in the same translation unit is an
   error. */
#define Declare_LmiWeakPtr(T_) Declare_LmiSharedPtr(T_)
#define Define_LmiWeakPtr(T_) Define_LmiSharedPtr(T_)

/* Alternate implementation, for tracking down reference count leaks:
 * allocate memory every time a ref count is incremented, and free it every
 * time it's decremented.  This lets ordinary memory leak checkers detect
 * reference count leaks. */
/* Note that the declaration and definition must match! */


/* A value that is unlikely to show up frequently in normal malloc allocations. */
#define LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE 17

/* Alternate class definitions.  These are deliberately structured to be
 * incompatible with the regular definitions. */
#define Declare_LmiSharedPtrClass_DummyAlloc(T_)		\
typedef struct {							\
	T_* ptr;								\
	LmiSharedPtrRefCount* ref;				\
	void* dummy;							\
	LmiAllocator* a;						\
	LmiSharedPtrDeleterCallback d;			\
} LmiSharedPtr(T_);


#define Declare_LmiWeakPtrClass_DummyAlloc(T_)			\
typedef struct {							\
	T_* ptr;								\
	LmiSharedPtrRefCount* ref;				\
	void* dummy;							\
	LmiAllocator* a;						\
	LmiSharedPtrDeleterCallback d;			\
} LmiWeakPtr(T_);


#define DefineInline_LmiSharedPtrIncUseCount_DummyAlloc_(T_, INLINE_)	\
INLINE_															\
LmiBool LmiSharedPtrIncUseCount_(T_)(LmiSharedPtr(T_)* s_)			\
{																\
	if (s_->ref == NULL) {										\
		s_->dummy = NULL;										\
		return LMI_TRUE;										\
	}															\
	if ((s_->dummy = LmiAllocatorAllocate(s_->a,				\
				LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE)) == NULL)	\
		return LMI_FALSE;										\
	LmiSharedPtrRefCountIncUseCount(s_->ref);					\
	return LMI_TRUE;											\
}


#define DefineInline_LmiSharedPtrIncUseCountConditional_DummyAlloc_(T_, INLINE_)		\
INLINE_															\
LmiBool LmiSharedPtrIncUseCountConditional_(T_)(LmiSharedPtr(T_)* s_)	\
{																\
	LmiBool ret;												\
	if (s_->ref == NULL) return LMI_FALSE;						\
	if ((s_->dummy = LmiAllocatorAllocate(s_->a,				\
				LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE)) == NULL)	\
		return LMI_FALSE;										\
	ret = LmiSharedPtrRefCountIncUseCountConditional(s_->ref);	\
	if (!ret)													\
		LmiAllocatorDeallocate(s_->a, s_->dummy,				\
			LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE);				\
	return ret;													\
}


#define DefineInline_LmiSharedPtrDecUseCount_DummyAlloc_(T_, INLINE_)		\
INLINE_															\
void LmiSharedPtrDecUseCount_(T_)(LmiSharedPtr(T_) * s_)		\
{																\
	/* s_->ref, s_->a may be freed by deleter, save locally */	\
	LmiSharedPtrRefCount* ref = s_->ref;						\
	LmiAllocator* a;											\
	if (ref == NULL) return;				    				\
																\
	a = s_->a;													\
	LmiAllocatorDeallocate(a, s_->dummy,						\
		LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE);					\
																\
	if (!LmiSharedPtrRefCountDecUseCount(ref))					\
		return;													\
																\
	s_->d((LmiVoidPtr)s_->ptr, a);								\
																\
	if (!LmiSharedPtrRefCountDecWeakCount(ref))					\
		return;													\
	LmiSharedPtrRefCountDestruct(ref);							\
	LmiAllocatorDeallocate(a, ref, sizeof(LmiSharedPtrRefCount)); \
}


#define DefineInline_LmiWeakPtrIncWeakCount_DummyAlloc_(T_, INLINE_)	\
INLINE_															\
LmiBool LmiWeakPtrIncWeakCount_(T_)(LmiWeakPtr(T_)* w_)			\
{																\
	if (w_->ref == NULL) return LMI_TRUE;						\
	if ((w_->dummy = LmiAllocatorAllocate(w_->a,				\
				LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE)) == NULL)	\
		return LMI_FALSE;										\
	LmiSharedPtrRefCountIncWeakCount(w_->ref);					\
	return LMI_TRUE;											\
}


#define DefineInline_LmiWeakPtrDecWeakCount_DummyAlloc_(T_, INLINE_)		\
INLINE_															\
void LmiWeakPtrDecWeakCount_(T_)(LmiWeakPtr(T_) * w_)			\
{																\
	if (w_->ref == NULL) return;								\
																\
	LmiAllocatorDeallocate(w_->a, w_->dummy,					\
		LMI_SHAREDPTR_DUMMYALLOC_ALLOCSIZE);					\
																\
	if (!LmiSharedPtrRefCountDecWeakCount(w_->ref))				\
		return;													\
	LmiAssert(LmiSharedPtrRefCountGetUseCount(w_->ref) == 0);	\
	LmiSharedPtrRefCountDestruct(w_->ref);						\
	LmiAllocatorDeallocate(w_->a, w_->ref, sizeof(LmiSharedPtrRefCount)); \
}

#define DefineInline_LmiSharedPtrFuncs_Internal_DummyAlloc(T_, INLINE_)	\
	DefineInline_LmiSharedPtrIncUseCount_DummyAlloc_(T_, INLINE_)		\
	DefineInline_LmiSharedPtrIncUseCountConditional_DummyAlloc_(T_, INLINE_) \
	DefineInline_LmiSharedPtrDecUseCount_DummyAlloc_(T_, INLINE_)

#define DefineInline_LmiWeakPtrFuncs_Internal_DummyAlloc(T_, INLINE_)	   \
	DefineInline_LmiWeakPtrIncWeakCount_DummyAlloc_(T_, INLINE_)		\
	DefineInline_LmiWeakPtrDecWeakCount_DummyAlloc_(T_, INLINE_)		\


#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS

#define DefineInlineHeader_LmiSharedPtrFuncs_DummyAlloc(T_) \
  DefineInline_LmiSharedPtrFuncs_Internal_DummyAlloc(T_, LMI_INLINE)  \
  DefineInline_LmiSharedPtrFuncs_PublicBase(T_, LMI_INLINE)				  \
  DefineInline_LmiSharedPtrFuncs_PublicExtra(T_, LMI_INLINE)				  \
  DefineInline_LmiWeakPtrFuncs_Internal_DummyAlloc(T_, LMI_INLINE)	  \
  DefineInline_LmiWeakPtrFuncs_PublicBase(T_, LMI_INLINE)			  \
  DefineInline_LmiWeakPtrFuncs_PublicExtra(T_, LMI_INLINE)

#else

#define DefineInlineHeader_LmiSharedPtrFuncs_DummyAlloc(T_) /* (defined as empty) */

#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS

#define DefineInlineSource_LmiSharedPtrFuncs_DummyAlloc(T_) \
  DefineInline_LmiSharedPtrFuncs_Internal_DummyAlloc(T_, LMI_INLINE_SOURCE_FILE) \
  DefineInline_LmiSharedPtrFuncs_PublicBase(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiSharedPtrFuncs_PublicExtra(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiWeakPtrFuncs_Internal_DummyAlloc(T_, LMI_INLINE_SOURCE_FILE)	  \
  DefineInline_LmiWeakPtrFuncs_PublicBase(T_, LMI_INLINE_SOURCE_FILE)	\
  DefineInline_LmiWeakPtrFuncs_PublicExtra(T_, LMI_INLINE_SOURCE_FILE)

#else

#define DefineInlineSource_LmiSharedPtrFuncs_DummyAlloc(T_) /* (defined as empty) */

#endif

#define Declare_LmiSharedPtr_DummyAlloc(T_)								\
	Declare_LmiSharedPtrClass_DummyAlloc(T_)							\
	Declare_LmiWeakPtrClass_DummyAlloc(T_)								\
    Declare_LmiSharedPtrFuncs(T_)										\
    Declare_LmiWeakPtrFuncs(T_)											\
    DefineInlineHeader_LmiSharedPtrFuncs_DummyAlloc(T_)					\

#define Define_LmiSharedPtr_DummyAlloc(T_)				\
	DefineInlineSource_LmiSharedPtrFuncs_DummyAlloc(T_)	\
	Define_LmiSharedPtrFuncs(T_)


#if LMI_SHAREDPTR_MEMDEBUG
#undef Declare_LmiSharedPtr
#undef Define_LmiSharedPtr
#define Declare_LmiSharedPtr(T_) Declare_LmiSharedPtr_DummyAlloc(T_) 
#define Define_LmiSharedPtr(T_)  Define_LmiSharedPtr_DummyAlloc(T_) 
#endif


/* LmiSharedVoidPtr */

/**
	{function:
    	{name: LmiSharedVoidPtrConstructDefault}
		{parent: LmiSharedVoidPtr}
		{description: Construct an empty shared void pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructDefault(LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The empty shared void pointer to construct.}}
		{return: The constructed shared void pointer.  Does not fail.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr()}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrConstructWithDeleter}
		{parent: LmiSharedVoidPtr}
		{description: Construct a shared void pointer corresponding to a specified pointer with a custom deleter.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructWithDeleter(LmiSharedVoidPtr* s, LmiVoidPtr p, LmiSharedPtrDeleterCallback d, LmiAllocator* a)}
		{parameter: {name: s} {description: The shared void pointer to construct.}}
		{parameter: {name: p} {description: The pointer to share.}}
		{parameter: {name: d} {description: A deleter to be called when the shared void pointer's reference count becomes 0.}}
		{parameter: {name: a} {description: An allocator.  This will only be used to allocate internal data structures, and will be passed to the deleter when the shared void pointer's reference count becomes 0.}}
		{return: The constructed shared void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr(void* p, D d, A a)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrDestruct}
		{parent: LmiSharedVoidPtr}
		{description: Destruct a shared void pointer.  If this brings the shared void pointer's use count to 0, delete the underlying pointer.}
		{prototype: void LmiSharedVoidPtrDestruct(LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer to destruct.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::~shared_ptr()}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrConstructCopy}
		{parent: LmiSharedVoidPtr}
		{description: Construct a shared void pointer as a copy of an existing one, sharing the same underlying pointer.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructCopy(LmiSharedVoidPtr* s, const LmiSharedVoidPtr* orig)}
		{parameter: {name: s} {description: The shared void pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared void pointer to copy.}}
		{return: The constructed shared void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr(shared_ptr& const)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrConstructFromWeakVoidPtr}
		{parent: LmiSharedVoidPtr}
		{description: Construct a shared void pointer based on a weak void pointer, sharing the same underlying pointer, if the weak void pointer is not expired.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrConstructFromWeakVoidPtr(LmiSharedVoidPtr* s, const LmiWeakVoidPtr* orig)}
		{parameter: {name: s} {description: The shared void pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak void pointer to copy.}}
		{return: The constructed shared void pointer on success, or NULL on failure, including if the weak void pointer is expired.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::shared_ptr(weak_ptr& const)}, except returning NULL if the weak void pointer is expired, rather than throwing std::bad_weak_ptr.}
	}
*/


/**
	{function:
    	{name: LmiSharedVoidPtrGetAllocator}
		{parent: LmiSharedVoidPtr}
		{description: Get the allocator used by a shared void pointer.}
		{prototype: LmiAllocator* LmiSharedVoidPtrGetAllocator(const LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer whose allocator to get.}}
		{return: The allocator used by the shared void pointer, or NULL if the shared void pointer is empty.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::get_allocator() const}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrAssign}
		{parent: LmiSharedVoidPtr}
		{description: Assign the value of one shared void pointer to another existing one.}
		{prototype: LmiSharedVoidPtr* LmiSharedVoidPtrAssign(LmiSharedVoidPtr* s, const LmiSharedVoidPtr* orig)}
		{parameter: {name: s} {description: The shared void pointer to assign.}}
		{parameter: {name: orig} {description: An existing shared void pointer to copy.}}
		{return: The assigned-to shared void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::operator=(shared_ptr& const)}.}
		{note: If s and orig refer to different shared void pointers, s\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrSwap}
		{parent: LmiSharedVoidPtr}
		{description: Swap the values of two shared void pointers.}
		{prototype: LmiBool LmiSharedVoidPtrSwap(LmiSharedVoidPtr* a, LmiSharedVoidPtr* b)}
		{parameter: {name: a} {description: The first shared void pointer to be swapped.}}
		{parameter: {name: b} {description: The second shared void pointer to be swapped.}}
		{return: LMI_TRUE, always (cannot fail).}
		{note: Like ISO C++ TR1 function {code: std::swap(std::tr1::shared_ptr<void>&, std::tr1::shared_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrReset}
		{parent: LmiSharedVoidPtr}
		{description: Reset the value of a shared void pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: void LmiSharedVoidPtrReset(LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer to be reset.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::reset()}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrEqual}
		{parent: LmiSharedVoidPtr}
		{description: Compare the values of two shared void pointers for equality.}
		{prototype: LmiBool LmiSharedVoidPtrEqual(const LmiSharedVoidPtr* a, const LmiSharedVoidPtr* b)}
		{parameter: {name: a} {description: The first shared void pointer to compare.}}
		{parameter: {name: b} {description: The second shared void pointer to compare.}}
		{return: Whether the pointers contained in the shared void pointer objects are the same.}
		{note: Like ISO C++ TR1 function {code: operator==(const std::tr1::shared_ptr<void>&, const std::tr1::shared_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrLess}
		{parent: LmiSharedVoidPtr}
		{description: Compare the values of two shared void pointers for ordering.}
		{prototype: LmiBool LmiSharedVoidPtrLess(const LmiSharedVoidPtr* a, const LmiSharedVoidPtr* b)}
		{parameter: {name: a} {description: The first shared void pointer to compare.}}
		{parameter: {name: b} {description: The second shared void pointer to compare.}}
		{return: Whether the pointer contained in the first shared void pointer objects is less than the second one.}
		{note: Like ISO C++ TR1 function {code: operator<(const std::tr1::shared_ptr<void>&, const std::tr1::shared_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrGet}
		{parent: LmiSharedVoidPtr}
		{description: Get the pointer pointed-to by a shared void pointer.}
		{prototype: LmiVoidPtr LmiSharedVoidPtrGet(const LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer whose pointer to get.}}
		{return: The pointer pointed-to by the shared void pointer, or NULL.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::get() const}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrUseCount}
		{parent: LmiSharedVoidPtr}
		{description: Get the current use-count of a shared void pointer.}
		{prototype: LmiInt LmiSharedVoidPtrUseCount(LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer whose use count to get.}}
		{return: The use count of the shared void pointer.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::use_count()}.}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrUnique}
		{parent: LmiSharedVoidPtr}
		{description: Get the whether a shared void pointer is unique, i.e. its use count is 1.}
		{prototype: LmiBool LmiSharedVoidPtrUnique(LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer whose uniqueness to get.}}
		{return: Whether the shared void pointer's use-count is 1.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::unique()}.}
		{note: This function will return false for an empty shared void pointer (one constructed with LmiSharedVoidPtrConstructDefault).}
	}
*/

/**
	{function:
    	{name: LmiSharedVoidPtrGetDeleter}
		{parent: LmiSharedVoidPtr}
		{description: Get the deleter associated with a shared void pointer.}
		{prototype: LmiSharedPtrDeleterCallback LmiSharedVoidPtrGetDeleter(const LmiSharedVoidPtr* s)}
		{parameter: {name: s} {description: The shared void pointer whose deleter to get.}}
		{return: The deleter associated with the shared void pointer.  For a default-constructed shared void pointer, this may be NULL.}
		{note: Like ISO C++ TR1 function {code: std::tr1::shared_ptr<void>::get_deleter() const}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrConstructDefault}
		{parent: LmiWeakVoidPtr}
		{description: Construct an empty weak void pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrConstructDefault(LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The empty weak void pointer to construct.}}
		{return: The constructed weak void pointer.  Does not fail.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::weak_ptr()}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrDestruct}
		{parent: LmiWeakVoidPtr}
		{description: Destruct a weak void pointer.}
		{prototype: void LmiWeakVoidPtrDestruct(LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The weak void pointer to destruct.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::~weak_ptr()}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrConstructCopy}
		{parent: LmiWeakVoidPtr}
		{description: Construct a weak void pointer as a copy of an existing one, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrConstructCopy(LmiWeakVoidPtr* w, const LmiWeakVoidPtr* orig)}
		{parameter: {name: w} {description: The weak void pointer to construct.}}
		{parameter: {name: orig} {description: An existing weak void pointer to copy.}}
		{return: The constructed weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::weak_ptr(weak_ptr& const)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrConstructFromSharedVoidPtr}
		{parent: LmiWeakVoidPtr}
		{description: Construct a weak void pointer based on a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrConstructFromSharedVoidPtr(LmiWeakVoidPtr* w, const LmiSharedVoidPtr* orig)}
		{parameter: {name: w} {description: The weak void pointer to construct.}}
		{parameter: {name: orig} {description: An existing shared void pointer to copy.}}
		{return: The constructed weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::weak_ptr(shared_ptr& const)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrGetAllocator}
		{parent: LmiWeakVoidPtr}
		{description: Get the allocator used by a weak void pointer.}
		{prototype: LmiAllocator* LmiWeakVoidPtrGetAllocator(const LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The weak void pointer whose allocator to get.}}
		{return: The allocator used by the weak void pointer, or NULL if the weak void pointer is empty.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::get_allocator() const}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrAssign}
		{parent: LmiWeakVoidPtr}
		{description: Assign the value of one weak void pointer to another existing one.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrAssign(LmiWeakVoidPtr* w, const LmiWeakVoidPtr* orig)}
		{parameter: {name: w} {description: The weak void pointer to assign.}}
		{parameter: {name: orig} {description: An existing weak void pointer to copy.}}
		{return: The assigned-to weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::operator=(weak_ptr& const)}.}
		{note: If s and orig refer to different weak void pointers, s\'s use
			count is decremented, and orig\'s use count is incremented.}
	}
*/

/**
	{function:
		{name: LmiWeakVoidPtrAssignFromSharedVoidPtr}
		{parent: LmiWeakVoidPtr}
		{description: Construct a weak void pointer based on a shared void pointer, sharing the same underlying pointer.}
		{prototype: LmiWeakVoidPtr* LmiWeakVoidPtrAssignFromSharedVoidPtr(LmiWeakVoidPtr* w, const LmiSharedVoidPtr* orig)}
		{parameter: {name: w} {description: The weak void pointer to assign to.}}
		{parameter: {name: orig} {description: An existing shared void pointer to copy.}}
		{return: The assigned-to weak void pointer on success, or NULL on failure.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::operator=(shared_ptr<void>& const)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrSwap}
		{parent: LmiWeakVoidPtr}
		{description: Swap the values of two weak void pointers.}
		{prototype: LmiBool LmiWeakVoidPtrSwap(LmiWeakVoidPtr* a, LmiWeakVoidPtr* b)}
		{parameter: {name: a} {description: The first weak void pointer to be swapped.}}
		{parameter: {name: b} {description: The second weak void pointer to be swapped.}}
		{return: LMI_TRUE, always (cannot fail).}
		{note: Like ISO C++ TR1 function {code: std::swap(std::tr1::weak_ptr<void>&, std::tr1::weak_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrReset}
		{parent: LmiWeakVoidPtr}
		{description: Reset the value of a weak void pointer, pointing to NULL
			and with a use-count of 0.}
		{prototype: void LmiWeakVoidPtrReset(LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The weak void pointer to be reset.}}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::reset()}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrEqual}
		{parent: LmiWeakVoidPtr}
		{description: Compare the values of two weak void pointers for equality.}
		{prototype: LmiBool LmiWeakVoidPtrEqual(const LmiWeakVoidPtr* a, const LmiWeakVoidPtr* b)}
		{parameter: {name: a} {description: The first weak void pointer to compare.}}
		{parameter: {name: b} {description: The second weak void pointer to compare.}}
		{return: Whether the pointers contained in the weak void pointer objects are the same.}
		{note: Like ISO C++ TR1 function {code: operator==(const std::tr1::weak_ptr<void>&, const std::tr1::weak_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrLess}
		{parent: LmiWeakVoidPtr}
		{description: Compare the values of two weak void pointers for ordering.}
		{prototype: LmiBool LmiWeakVoidPtrLess(const LmiWeakVoidPtr* a, const LmiWeakVoidPtr* b)}
		{parameter: {name: a} {description: The first weak void pointer to compare.}}
		{parameter: {name: b} {description: The second weak void pointer to compare.}}
		{return: Whether the pointer contained in the first weak void pointer objects is less than the second one.}
		{note: Like ISO C++ TR1 function {code: operator<(const std::tr1::weak_ptr<void>&, const std::tr1::weak_ptr<void>&)}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrUseCount}
		{parent: LmiWeakVoidPtr}
		{description: Get the current use-count of a weak void pointer.}
		{prototype: LmiInt LmiWeakVoidPtrUseCount(const LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The weak void pointer whose use count to get.}}
		{return: The use count of the weak void pointer.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::use_count()}.}
	}
*/

/**
	{function:
    	{name: LmiWeakVoidPtrExpired}
		{parent: LmiWeakVoidPtr}
		{description: Get the whether a weak void pointer is expired, i.e. its use count is 0.}
		{prototype: LmiBool LmiWeakVoidPtrExpired(const LmiWeakVoidPtr* w)}
		{parameter: {name: w} {description: The weak void pointer whose expiredness to get.}}
		{return: Whether the weak void pointer's use-count is 0.}
		{note: Like ISO C++ TR1 function {code: std::tr1::weak_ptr<void>::expired()}.}
		{note: This function will return true for an empty weak void pointer (one constructed with LmiWeakVoidPtrConstructDefault).}
	}
*/

Declare_LmiSharedPtrClass(void)
Declare_LmiWeakPtrClass(void)
Declare_LmiSharedPtrBaseFuncs(void)
Declare_LmiWeakPtrBaseFuncs(void)


/* Macros for wrapping a shared pointer object into a new type.
Use (Declare_LmiSharedPtrWrapper in X.h and Define_LmiSharedPtrWrapper in XInline.h)
or Define_LmiSharedPtrWrapper_Static in X.c. */

#define Declare_LmiSharedPtrWrapper_Struct_(H, B) \
	typedef struct \
	{ \
		LmiSharedPtr(B) sp; \
	} H;

#define Define_LmiSharedPtrWrapper_Bodies_(I, H, B, BEq, BLess) \
	I H *LmiConstructCopy(H)(H *h, const H *other) \
	{ \
		if(LmiSharedPtrConstructCopy(B)(&h->sp, &other->sp) == NULL) \
			return NULL; \
		return h; \
	} \
	\
	I void LmiDestruct(H)(H *h) \
	{ \
		LmiSharedPtrDestruct(B)(&h->sp); \
	} \
	\
	I H *LmiAssign(H)(H *h, const H *other) \
	{ \
		if(LmiSharedPtrAssign(B)(&h->sp, &other->sp) == NULL) \
			return NULL; \
		return h; \
	} \
	\
	I LmiBool LmiSwap(H)(H *a, H *b) \
	{ \
		return LmiSharedPtrSwap(B)(&a->sp, &b->sp); \
	} \
	\
	I LmiBool LmiEqual(H)(const H *a, const H *b) \
	{ \
		return LmiSharedPtrEqual(B)(&a->sp, &b->sp) || BEq(LmiSharedPtrGet(B)(&a->sp), LmiSharedPtrGet(B)(&b->sp)); \
	} \
	\
	I LmiBool LmiLess(H)(const H *a, const H *b) \
	{ \
		return !LmiSharedPtrEqual(B)(&a->sp, &b->sp) && BLess(LmiSharedPtrGet(B)(&a->sp), LmiSharedPtrGet(B)(&b->sp)); \
	} \
	\
	I H *LmiClassFunc(H, ConstructFromSharedVoidPtr)(H *h, const LmiSharedVoidPtr *other) \
	{ \
		if(LmiSharedPtrConstructFromSharedVoidPtr(B)(&h->sp, other) == NULL) \
			return NULL; \
		return h; \
	} \
	I LmiSharedVoidPtr *LmiClassFunc(H, GetSharedVoidPtr)(H *h, LmiSharedVoidPtr *b) \
	{ \
		return LmiSharedVoidPtrAssignFromSharedPtr(B)(b, &h->sp); \
	} \
	\
	I B *LmiClassFunc(H, GetImpl)(H *h) \
	{ \
		return LmiSharedPtrGet(B)(&h->sp); \
	} \
	\
	I const B *LmiClassFunc(H, GetImplConst)(const H *h) \
	{ \
		return LmiSharedPtrGet(B)(&h->sp); \
	}

#define Declare_LmiSharedPtrWrapper(H, B) \
	Declare_LmiSharedPtrWrapper_Struct_(H, B) \
	LMI_INLINE_DECLARATION H *LmiConstructCopy(H)(H *h, const H *other); \
	LMI_INLINE_DECLARATION void LmiDestruct(H)(H *h); \
	LMI_INLINE_DECLARATION H *LmiAssign(H)(H *h, const H *other); \
	LMI_INLINE_DECLARATION LmiBool LmiSwap(H)(H *a, H *b); \
	LMI_INLINE_DECLARATION LmiBool LmiEqual(H)(const H *a, const H *b); \
	LMI_INLINE_DECLARATION LmiBool LmiLess(H)(const H *a, const H *b); \
	LMI_INLINE_DECLARATION H *LmiClassFunc(H, ConstructFromSharedVoidPtr)(H *h, const LmiSharedVoidPtr *other); \
	LMI_INLINE_DECLARATION LmiSharedVoidPtr *LmiClassFunc(H, GetSharedVoidPtr)(H *h, LmiSharedVoidPtr *b); \
	LMI_INLINE_DECLARATION B *LmiClassFunc(H, GetImpl)(H *h); \
	LMI_INLINE_DECLARATION const B *LmiClassFunc(H, GetImplConst)(const H *h);
#define LmiSharedPtrWrapperShallowEqual(a, b) LMI_FALSE
#define LmiSharedPtrWrapperShallowLess(a, b) ((a) < (b))
#define Define_LmiSharedPtrWrapper(H, B) \
	Define_LmiSharedPtrWrapper_Bodies_(LMI_INLINE, H, B, LmiEqual(B), LmiLess(B))
#define Define_LmiSharedPtrWrapper_NoCompare(H, B) \
	Define_LmiSharedPtrWrapper_Bodies_(LMI_INLINE, H, B, LmiSharedPtrWrapperShallowEqual, LmiSharedPtrWrapperShallowLess)
#define Define_LmiSharedPtrWrapper_Static(H, B) \
	Declare_LmiSharedPtrWrapper_Struct_(H, B) \
	Define_LmiSharedPtrWrapper_Bodies_(LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE, H, B, LmiEqual(B), LmiLess(B))
#define Define_LmiSharedPtrWrapper_Static_NoCompare(H, B) \
	Declare_LmiSharedPtrWrapper_Struct_(H, B) \
	Define_LmiSharedPtrWrapper_Bodies_(LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE, H, B, LmiSharedPtrWrapperShallowEqual, LmiSharedPtrWrapperShallowLess)


/* Macros for wrapping a weak pointer object into a new type.
Requires shared pointer wrapper.
Use (Declare_LmiWeakPtrWrapper in X.h and Define_LmiWeakPtrWrapper in XInline.h)
or Define_LmiWeakPtrWrapper_Static in X.c. */

#define Declare_LmiWeakPtrWrapper_Struct_(W, B) \
	typedef struct \
	{ \
		LmiWeakPtr(B) wp; \
	} W;

#define Define_LmiWeakPtrWrapper_Bodies_(I, W, H, B) \
	I W *LmiConstructDefault(W)(W *w) \
	{ \
		if(LmiWeakPtrConstructDefault(B)(&w->wp) == NULL) \
			return NULL; \
		return w; \
	} \
	\
	I W *LmiConstruct(W)(W *w, const H *h) \
	{ \
		if(LmiWeakPtrConstructFromSharedPtr(B)(&w->wp, &h->sp) == NULL) \
			return NULL; \
		return w; \
	} \
	\
	I W *LmiConstructCopy(W)(W *w, const W *other) \
	{ \
		if(LmiWeakPtrConstructCopy(B)(&w->wp, &other->wp) == NULL) \
			return NULL; \
		return w; \
	} \
	\
	I void LmiDestruct(W)(W *w) \
	{ \
		LmiWeakPtrDestruct(B)(&w->wp); \
	} \
	\
	I W *LmiAssign(W)(W *w, const W *other) \
	{ \
		if(LmiWeakPtrAssign(B)(&w->wp, &other->wp) == NULL) \
			return NULL; \
		return w; \
	} \
	I W *LmiClassFunc(W, AssignFromObj)(W *w, const H *h) \
	{ \
		if(LmiWeakPtrAssignFromSharedPtr(B)(&w->wp, &h->sp) == NULL) \
			return NULL; \
		return w; \
	} \
	\
	I LmiBool LmiSwap(W)(W *a, W *b) \
	{ \
		return LmiWeakPtrSwap(B)(&a->wp, &b->wp); \
	} \
	\
	I LmiBool LmiEqual(W)(const W *a, const W *b) \
	{ \
		return LmiWeakPtrEqual(B)(&a->wp, &b->wp); \
	} \
	\
	I LmiBool LmiLess(W)(const W *a, const W *b) \
	{ \
		return LmiWeakPtrLess(B)(&a->wp, &b->wp); \
	} \
	\
	I void LmiClassFunc(W, Set)(W *w, const H *h) \
	{ \
		LmiWeakPtrAssignFromSharedPtr(B)(&w->wp, &h->sp); \
	} \
	\
	I void LmiClassFunc(W, Reset)(W *w) \
	{ \
		LmiWeakPtrReset(B)(&w->wp); \
	} \
	\
	I LmiBool LmiClassFunc(W, Expired)(const W *w) \
	{ \
		return LmiWeakPtrExpired(B)(&w->wp); \
	} \
	\
	I W *LmiClassFunc(W, ConstructFromWeakVoidPtr)(W *w, const LmiWeakVoidPtr *other) \
	{ \
		if(LmiWeakPtrConstructFromWeakVoidPtr(B)(&w->wp, other) == NULL) \
			return NULL; \
		return w; \
	} \
	\
	I LmiWeakVoidPtr *LmiClassFunc(H, GetWeakVoidPtr)(W *w, LmiWeakVoidPtr *b) \
	{ \
		return LmiWeakVoidPtrAssignFromWeakPtr(B)(b, &w->wp); \
	} \
	\
	I H *LmiClassFunc(H, ConstructFromHandle)(H *h, const W *w) \
	{ \
		if(LmiSharedPtrConstructFromWeakPtr(B)(&h->sp, &w->wp) == NULL) \
			return NULL; \
		return h; \
	}

#define Declare_LmiWeakPtrWrapper(W, H, B) \
	Declare_LmiWeakPtrWrapper_Struct_(W, B) \
	LMI_INLINE_DECLARATION W *LmiConstructDefault(W)(W *w); \
	LMI_INLINE_DECLARATION W *LmiConstruct(W)(W *w, const H *h); \
	LMI_INLINE_DECLARATION W *LmiConstructCopy(W)(W *w, const W *other); \
	LMI_INLINE_DECLARATION void LmiDestruct(W)(W *w); \
	LMI_INLINE_DECLARATION W *LmiAssign(W)(W *w, const W *other); \
	LMI_INLINE_DECLARATION W *LmiClassFunc(W, AssignFromObj)(W *w, const H *h); \
	LMI_INLINE_DECLARATION LmiBool LmiSwap(W)(W *a, W *b); \
	LMI_INLINE_DECLARATION LmiBool LmiEqual(W)(const W *a, const W *b); \
	LMI_INLINE_DECLARATION LmiBool LmiLess(W)(const W *a, const W *b); \
	LMI_INLINE_DECLARATION void LmiClassFunc(W, Set)(W *w, const H *h); \
	LMI_INLINE_DECLARATION void LmiClassFunc(W, Reset)(W *w); \
	LMI_INLINE_DECLARATION LmiBool LmiClassFunc(W, Expired)(const W *w); \
	LMI_INLINE_DECLARATION W *LmiClassFunc(W, ConstructFromWeakVoidPtr)(W *w, const LmiWeakVoidPtr *other); \
	LMI_INLINE_DECLARATION LmiWeakVoidPtr *LmiClassFunc(H, GetWeakVoidPtr)(W *w, LmiWeakVoidPtr *b); \
	LMI_INLINE_DECLARATION H *LmiClassFunc(H, ConstructFromHandle)(H *h, const W *w);
#define Define_LmiWeakPtrWrapper(W, H, B) Define_LmiWeakPtrWrapper_Bodies_(LMI_INLINE, W, H, B)
#define Define_LmiWeakPtrWrapper_Static(W, H, B) \
	Declare_LmiWeakPtrWrapper_Struct_(W, B) \
	Define_LmiWeakPtrWrapper_Bodies_(LMI_POSSIBLY_UNUSED LMI_STATIC_INLINE, W, H, B)

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Os/LmiSharedPtrInline.h>
#endif

#endif /* LMI_SHARED_PTR_H_ */
