/**
{file:
	{name: LmiAssociativeContainers.h }
	{description: Associative Containers concepts. }
	{copyright:
		(c) 2006-2012 Vidyo, Inc.,
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

#ifndef LMI_ASSOCIATIVE_CONTAINERS_H_
#define LMI_ASSOCIATIVE_CONTAINERS_H_

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUtility.h>
#include <Lmi/Utils/LmiContainers.h>

LMI_BEGIN_EXTERN_C


/**
{package visibility="private":
	{name: AssociativeContainers}
	{parent: Containers}
	{description: A package of associative parameterized container classes. }
}
*/

/* Associative Container concept */  
#define Declare_LmiAssociativeContainerTypesPart(X_, K_) \
	typedef K_ LmiKeyType(X_); \
	Declare_LmiPairTypes(LmiIterator(X_), LmiIterator(X_)) \
	Declare_LmiPairTypes(LmiConstIterator(X_), LmiConstIterator(X_))

#define Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiAssociativeContainerTypesPart(X_, K_)

#define Declare_LmiAssociativeContainerFuncsPart(X_) \
	LmiIterator(X_) LmiErase(X_)(X_* x, LmiIterator(X_) pos); \
	LmiIterator(X_) LmiEraseRange(X_)(X_* x, LmiIterator(X_) f, LmiIterator(X_) l); \
	LmiSizeType(X_) LmiEraseKey(X_)(X_* x, const LmiKeyType(X_)* k); \
	void LmiClear(X_)(X_* x); \
	LmiSizeType(X_) LmiCount(X_)(const X_* x, const LmiKeyType(X_)* k); \
	LmiPair(LmiIterator(X_), LmiIterator(X_)) LmiEqualRange(X_)(X_* x, const LmiKeyType(X_)* k); \
	LmiPair(LmiConstIterator(X_), LmiConstIterator(X_)) LmiEqualRangeConst(X_)(const X_* x, const LmiKeyType(X_)* k);

#define Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiPairFuncs(LmiIterator(X_), LmiIterator(X_)) \
	Declare_LmiPairFuncs(LmiConstIterator(X_), LmiConstIterator(X_)) \
	Declare_LmiForwardContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncsPart(X_)

#define Declare_LmiAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiAssociativeContainerFuncs(X_)

/* Simple Associative Container concept */
#define Declare_LmiSimpleAssociativeContainerTypesPart(X_, T_, CI_, S_, D_)

#define Declare_LmiSimpleAssociativeContainerTypes(X_, T_, CI_, S_, D_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, CI_, CI_, S_, D_, T_) \
	Declare_LmiSimpleAssociativeContainerTypesPart(X_, T_, CI_, S_, D_)

#define Declare_LmiSimpleAssociativeContainerFuncsPart(X_)

#define Declare_LmiSimpleAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiSimpleAssociativeContainerFuncsPart(X_)

#define Declare_LmiSimpleAssociativeContainer(X_, T_, CI_, S_, D_) \
	Declare_LmiSimpleAssociativeContainerTypes(X_, T_, CI_, S_, D_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiSimpleAssociativeContainerFuncs(X_)

/* Pair Associative Container concept */
#define Declare_LmiPairAssociativeContainerTypesPart(X_, T_, K_) \
	Declare_LmiPair(K_, T_) \
	typedef T_ LmiDataType(X_);

#define Declare_LmiPairAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiPairAssociativeContainerTypesPart(X_, T_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, LmiPair(K_, T_), I_, CI_, S_, D_, K_)
	
#define Declare_LmiPairAssociativeContainerFuncsPart(X_)

#define Declare_LmiPairAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiPairAssociativeContainerFuncsPart(X_)

#define Declare_LmiPairAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiPairAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiPairAssociativeContainerFuncs(X_)

/* Sorted Associative Container concept */
#define Declare_LmiSortedAssociativeContainerTypesPart(X_)

#define Declare_LmiSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiReversibleContainerTypesPart(X_, I_, CI_) \
	Declare_LmiSortedAssociativeContainerTypesPart(X_)

#define Declare_LmiSortedAssociativeContainerFuncsPart(X_) \
	LmiIterator(X_) LmiLowerBound(X_)(X_* x, const LmiKeyType(X_)* k); \
	LmiConstIterator(X_) LmiLowerBoundConst(X_)(const X_* x, const LmiKeyType(X_)* k); \
	LmiIterator(X_) LmiUpperBound(X_)(X_* x, const LmiKeyType(X_)* k); \
	LmiConstIterator(X_) LmiUpperBoundConst(X_)(const X_* x, const LmiKeyType(X_)* k); \
	LmiIterator(X_) LmiFind(X_)(X_* x, const LmiKeyType(X_)* k); \
	LmiConstIterator(X_) LmiFindConst(X_)(const X_* x, const LmiKeyType(X_)* k); \

#define Declare_LmiSortedAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	DeclareInline_LmiReversibleContainerFuncsPart(X_, LMI_NO_INLINE) \
	Declare_LmiSortedAssociativeContainerFuncsPart(X_) \

#define Declare_LmiSortedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K) \
	Declare_LmiSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiBidirectionalIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiReverseIterator(X_), T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiConstReverseIterator(X_), const T_, const T_, D_) \
	Declare_LmiSortedAssociativeContainerFuncs(X_)

/* Unordered Associative Container concept */
#define Declare_LmiUnorderedAssociativeContainerTypesPart(X_) \
	typedef LmiSizeT (*LmiHashFunctionType(X_))(const LmiKeyType(X_)* k);

#define Declare_LmiUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUnorderedAssociativeContainerTypesPart(X_)

#define Declare_LmiUnorderedAssociativeContainerFuncsPart(X_) \
	X_* LmiConstruct(X_)(X_* x, LmiHashFunctionType(X_) hash, LmiSizeType(X_) numBuckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator); \
	LmiIterator(X_) LmiFind(X_)(X_* x, const LmiKeyType(X_)* k); \
	LmiConstIterator(X_) LmiFindConst(X_)(const X_* x, const LmiKeyType(X_)* k); \
	LMI_INLINE_DECLARATION LmiHashFunctionType(X_) LmiHashFunction(X_)(const X_* x); \
	LMI_INLINE_DECLARATION LmiSizeType(X_) LmiBucketCount(X_)(const X_* x); \
	LmiBool LmiResize(X_)(X_* x, LmiSizeType(X_) n);

#define Declare_LmiUnorderedAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiUnorderedAssociativeContainerFuncsPart(X_)

#define Declare_LmiUnorderedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiUnorderedAssociativeContainerFuncs(X_)

/* Unique Associative Container concept */
#define Declare_LmiUniqueAssociativeContainerTypesPart(X_) \
	Declare_LmiPairTypes(LmiIterator(X_), LmiBool)

#define Declare_LmiUniqueAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueAssociativeContainerTypesPart(X_) 

#define Declare_LmiUniqueAssociativeContainerFuncsPart(X_) \
	Declare_LmiPairFuncs(LmiIterator(X_), LmiBool) \
	X_* LmiConstructRange(X_)(X_* x, LmiIterator(X_) first, LmiIterator(X_) last, LmiAllocator* a); \
	LmiPair(LmiIterator(X_), LmiBool) LmiInsert(X_)(X_* x, const LmiValueType(X_)* t); \
	LmiBool LmiInsertRange(X_)(X_* x, LmiIterator(X_) first, LmiIterator(X_) last);

#define Declare_LmiUniqueAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiUniqueAssociativeContainerFuncsPart(X_)

#define Declare_LmiUniqueAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiUniqueAssociativeContainerFuncs(X_)

/* Multiple Associative Container concept */
#define Declare_LmiMultipleAssociativeContainerTypesPart(X_)

#define Declare_LmiMultipleAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleAssociativeContainerTypesPart(X_)

#define Declare_LmiMultipleAssociativeContainerFuncsPart(X_) \
	X_* LmiConstructRange(X_)(X_* x, LmiIterator(X_) first, LmiIterator(X_) last, LmiAllocator* a); \
	LmiIterator(X_) LmiInsert(X_)(X_* x, const LmiValueType(X_)* t); \
	LmiBool LmiInsertRange(X_)(X_* x, LmiIterator(X_) first, LmiIterator(X_) last);

#define Declare_LmiMultipleAssociativeContainerFuncs(X_) \
	Declare_LmiAssociativeContainerFuncs(X_) \
	Declare_LmiMultipleAssociativeContainerFuncsPart(X_)

#define Declare_LmiMultipleAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiMultipleAssociativeContainerFuncs(X_)

/* Unique Sorted Associative Container concept */
#define Declare_LmiUniqueSortedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_)

#define Declare_LmiUniqueSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiReversibleContainerTypesPart(X_, I_, CI_) \
	Declare_LmiSortedAssociativeContainerTypesPart(X_) \
	Declare_LmiUniqueSortedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \

#define Declare_LmiUniqueSortedAssociativeContainerFuncsPart(X_)

#define Declare_LmiUniqueSortedAssociativeContainerFuncs(X_) \
	Declare_LmiUniqueAssociativeContainerFuncs(X_) \
	DeclareInline_LmiReversibleContainerFuncsPart(X_, LMI_NO_INLINE) \
	Declare_LmiSortedAssociativeContainerFuncsPart(X_) \
	Declare_LmiUniqueSortedAssociativeContainerFuncsPart(X_)

#define Declare_LmiUniqueSortedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	DeclareInline_LmiBidirectionalIterator(LmiIterator(X_), T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiConstIterator(X_), const T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiReverseIterator(X_), T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiConstReverseIterator(X_), const T_, const T_, D_, LMI_INLINE) \
	Declare_LmiUniqueSortedAssociativeContainerFuncs(X_)

/* Multiple Sorted Associative Container concept */
#define Declare_LmiMultipleSortedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_)

#define Declare_LmiMultipleSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiReversibleContainerTypesPart(X_, I_, CI_) \
	Declare_LmiSortedAssociativeContainerTypesPart(X_) \
	Declare_LmiMultipleSortedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \

#define Declare_LmiMultipleSortedAssociativeContainerFuncsPart(X_)

#define Declare_LmiMultipleSortedAssociativeContainerFuncs(X_) \
	Declare_LmiMultipleAssociativeContainerFuncs(X_) \
	Declare_LmiSortedAssociativeContainerFuncsPart(X_) \
	Declare_LmiMultipleSortedAssociativeContainerFuncsPart(X_)

#define Declare_LmiMultipleSortedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleSortedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	DeclareInline_LmiBidirectionalIterator(LmiIterator(X_), T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiConstIterator(X_), const T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiReverseIterator(X_), T_, const T_, D_, LMI_INLINE) \
	DeclareInline_LmiBidirectionalIterator(LmiConstReverseIterator(X_), const T_, const T_, D_, LMI_INLINE) \
	Declare_LmiMultipleSortedAssociativeContainerFuncs(X_)

/* Unique Unordered Associative Container concept */
#define Declare_LmiUniqueUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_)

#define Declare_LmiUniqueUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \

#define Declare_LmiUniqueUnorderedAssociativeContainerFuncsPart(X_)

#define Declare_LmiUniqueUnorderedAssociativeContainerFuncs(X_) \
	Declare_LmiUniqueAssociativeContainerFuncs(X_) \
	Declare_LmiUnorderedAssociativeContainerFuncsPart(X_) \
	Declare_LmiUniqueUnorderedAssociativeContainerFuncsPart(X_)

#define Declare_LmiUniqueUnorderedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUniqueUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiUniqueUnorderedAssociativeContainerFuncs(X_)

/* Multiple Unordered Associative Container concept */
#define Declare_LmiMultipleUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_)

#define Declare_LmiMultipleUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleUnorderedAssociativeContainerTypesPart(X_, T_, I_, CI_, S_, D_, K_) \

#define Declare_LmiMultipleUnorderedAssociativeContainerFuncsPart(X_)

#define Declare_LmiMultipleUnorderedAssociativeContainerFuncs(X_) \
	Declare_LmiMultipleAssociativeContainerFuncs(X_) \
	Declare_LmiUnorderedAssociativeContainerFuncsPart(X_) \
	Declare_LmiMultipleUnorderedAssociativeContainerFuncsPart(X_)

#define Declare_LmiMultipleUnorderedAssociativeContainer(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiMultipleUnorderedAssociativeContainerTypes(X_, T_, I_, CI_, S_, D_, K_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiMultipleUnorderedAssociativeContainerFuncs(X_)

LMI_END_EXTERN_C

#endif /* LMI_ASSOCIATIVE_CONTAINERS_H_ */
