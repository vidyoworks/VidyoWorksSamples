/**
{file: 
	{name: LmiUnordered.h }
	{description: LMI unordered (hashed) container.}
	{copyright:
		(c) 2006-2015 Vidyo, Inc.,
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

#ifndef LMI_UNORDERED_H_
#define LMI_UNORDERED_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiAssociativeContainers.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUtility.h>
#include <Lmi/Utils/LmiList.h>
#include <Lmi/Utils/LmiVector.h>
#include <Lmi/Utils/LmiAssert.h>

LMI_BEGIN_EXTERN_C


/**************************************************** Set & Multiset *******************************************************/

/* Unordered Map & Multimap Bucket */
#define LmiUnorderedBucket(K_, T_)										LmiTemplate2(LmiUnorderedBucket, K_, T_)
#define LmiUnorderedBucketConstructCopy(K_, T_)							LmiConstructCopy(LmiUnorderedBucket(K_, T_))
#define LmiUnorderedBucketDestruct(K_, T_)								LmiDestruct(LmiUnorderedBucket(K_, T_))
#define LmiUnorderedBucketAssign(K_, T_)								LmiAssign(LmiUnorderedBucket(K_, T_))
#define LmiUnorderedBucketEqual(K_, T_)									LmiEqual(LmiUnorderedBucket(K_, T_))
#define LmiUnorderedBucketLess(K_, T_)									LmiLess(LmiUnorderedBucket(K_, T_))

/* Unordered Map & Multimap Statistics */
#define LmiUnorderedStatistics(K_, T_)									LmiTemplate2(LmiUnorderedStatistics, K_, T_)

/* Unordered Map & Multimap Internal Representation */
#define LmiUnordered(K_, T_)											LmiTemplate2(LmiUnordered, K_, T_)
#define LmiUnorderedHashFunctionType(K_, T_)							LmiHashFunctionType(LmiUnordered(K_, T_))
#define LmiUnorderedSizeType(K_, T_)									LmiSizeType(LmiUnordered(K_, T_))
#define LmiUnorderedValueType(K_, T_)									LmiValueType(LmiUnordered(K_, T_))
#define LmiUnorderedConstruct(K_, T_)									LmiConstruct(LmiUnordered(K_, T_))
#define LmiUnorderedConstructRange(K_, T_)								LmiConstructRange(LmiUnordered(K_, T_))
#define LmiUnorderedConstructCopy(K_, T_)								LmiConstructCopy(LmiUnordered(K_, T_))
#define LmiUnorderedDestruct(K_, T_)									LmiDestruct(LmiUnordered(K_, T_))
#define LmiUnorderedAssign(K_, T_)										LmiAssign(LmiUnordered(K_, T_))
#define LmiUnorderedSwap(K_, T_)										LmiSwap(LmiUnordered(K_, T_))
#define LmiUnorderedBegin(K_, T_)										LmiBegin(LmiUnordered(K_, T_))
#define LmiUnorderedBeginConst(K_, T_)									LmiBeginConst(LmiUnordered(K_, T_))
#define LmiUnorderedEnd(K_, T_)											LmiEnd(LmiUnordered(K_, T_))
#define LmiUnorderedEndConst(K_, T_)									LmiEndConst(LmiUnordered(K_, T_))
#define LmiUnorderedEmpty(K_, T_)										LmiEmpty(LmiUnordered(K_, T_))
#define LmiUnorderedSize(K_, T_)										LmiSize(LmiUnordered(K_, T_))
#define LmiUnorderedMaxSize(K_, T_)										LmiMaxSize(LmiUnordered(K_, T_))
#define LmiUnorderedCount(K_, T_)										LmiCount(LmiUnordered(K_, T_))
#define LmiUnorderedEqual(K_, T_)										LmiEqual(LmiUnordered(K_, T_))
#define LmiUnorderedLess(K_, T_)										LmiLess(LmiUnordered(K_, T_))
#define LmiUnorderedClear(K_, T_)										LmiClear(LmiUnordered(K_, T_))
#define LmiUnorderedErase(K_, T_)										LmiErase(LmiUnordered(K_, T_))
#define LmiUnorderedEraseRange(K_, T_)									LmiEraseRange(LmiUnordered(K_, T_))
#define LmiUnorderedEraseKey(K_, T_)									LmiEraseKey(LmiUnordered(K_, T_))
#define LmiUnorderedEqualRange(K_, T_)									LmiEqualRange(LmiUnordered(K_, T_))
#define LmiUnorderedEqualRangeConst(K_, T_)								LmiEqualRangeConst(LmiUnordered(K_, T_))
#define LmiUnorderedFind(K_, T_)										LmiFind(LmiUnordered(K_, T_))
#define LmiUnorderedFindConst(K_, T_)									LmiFindConst(LmiUnordered(K_, T_))
#define LmiUnorderedInsert_(K_, T_)										LmiUnorderedInsert_##_##K_##__##T_
#define LmiUnorderedBucketCount(K_, T_)									LmiBucketCount(LmiUnordered(K_, T_))
#define LmiUnorderedHashFunction(K_, T_)								LmiHashFunction(LmiUnordered(K_, T_))
#define LmiUnorderedResize(K_, T_)										LmiResize(LmiUnordered(K_, T_))
#define LmiUnorderedGetNodeSize(K_, T_)									LmiClassFunc(LmiUnordered(K_, T_), GetNodeSize)
#define LmiUnorderedGetStatistics(K_, T_)								LmiClassFunc(LmiUnordered(K_, T_), GetStatistics)
#define LmiUnorderedGetBucketAllocator(K_, T_)							LmiClassFunc(LmiUnordered(K_, T_), GetBucketAllocator)
#define LmiUnorderedGetNodeAllocator(K_, T_)							LmiClassFunc(LmiUnordered(K_, T_), GetNodeAllocator)


/* Unordered Map & Multimap Iterator Internal Representation */
#define LmiUnorderedIterator(K_, T_)									LmiIterator(LmiUnordered(K_, T_))
#define LmiUnorderedIteratorConstruct(K_, T_)							LmiConstruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorDestruct(K_, T_)							LmiDestruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorConstructCopy(K_, T_)						LmiConstructCopy(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorAssign(K_, T_)								LmiAssign(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorSwap(K_, T_)								LmiSwap(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorEqual(K_, T_)								LmiEqual(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorContentOf(K_, T_)							LmiContentOf(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorIncrement(K_, T_)							LmiIncrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorDecrement(K_, T_)							LmiDecrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorConstructExceptional(K_, T_)				LmiConstructExceptional(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedIteratorIsExceptional(K_, T_)						LmiIsExceptional(LmiListIterator(LmiPair(K_, T_)))

/* Unordered Map & Multimap Iterator Internal Representation */
#define LmiUnorderedConstIterator(K_, T_)								LmiConstIterator(LmiUnordered(K_, T_))
#define LmiUnorderedConstIteratorConstruct(K_, T_)						LmiConstruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorDestruct(K_, T_)						LmiDestruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorConstructCopy(K_, T_)					LmiConstructCopy(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorAssign(K_, T_)							LmiAssign(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorSwap(K_, T_)							LmiSwap(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorEqual(K_, T_)							LmiEqual(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorContentOf(K_, T_)						LmiContentOf(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorIncrement(K_, T_)						LmiIncrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorDecrement(K_, T_)						LmiDecrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorConstructExceptional(K_, T_)			LmiConstructExceptional(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedConstIteratorIsExceptional(K_, T_)					LmiIsExceptional(LmiListConstIterator(LmiPair(K_, T_)))

#define Declare_LmiUnorderedInsert_(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedInsert_(K_, T_)(LmiUnordered(K_, T_)* x, const LmiUnorderedValueType(K_, T_)* value);

#define Declare_LmiUnorderedGetNodeSize(K_, T_) \
LMI_INLINE_DECLARATION LmiUnorderedSizeType(K_, T_) LmiUnorderedGetNodeSize(K_, T_)(const LmiUnordered(K_, T_)* x);

#define Declare_LmiUnorderedGetStatistics(K_, T_) \
void LmiUnorderedGetStatistics(K_, T_)(const LmiUnordered(K_, T_)* x, LmiUnorderedStatistics(K_, T_)* stats);

#define Declare_LmiUnorderedGetBucketAllocator(K_, T_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiUnorderedGetBucketAllocator(K_, T_)(LmiUnordered(K_, T_)* x);

#define Declare_LmiUnorderedGetNodeAllocator(K_, T_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiUnorderedGetNodeAllocator(K_, T_)(LmiUnordered(K_, T_)* x);

#define Declare_LmiUnordered(K_, T_) \
	Declare_LmiPair(K_, T_) \
	Declare_LmiList(LmiPair(K_, T_)) \
	typedef struct { \
		LmiListIterator(LmiPair(K_, T_)) first; \
		LmiSizeT count; \
	} LmiUnorderedBucket(K_, T_); \
	LMI_INLINE_DECLARATION LmiUnorderedBucket(K_, T_)* LmiUnorderedBucketConstructCopy(K_, T_)(LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y); \
	LMI_INLINE_DECLARATION void LmiUnorderedBucketDestruct(K_, T_)(LmiUnorderedBucket(K_, T_)* x); \
	LMI_INLINE_DECLARATION LmiUnorderedBucket(K_, T_)* LmiUnorderedBucketAssign(K_, T_)(LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y); \
	LMI_INLINE_DECLARATION LmiBool LmiUnorderedBucketEqual(K_, T_)(const LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y); \
	LMI_INLINE_DECLARATION LmiBool LmiUnorderedBucketLess(K_, T_)(const LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y); \
	Declare_LmiVector(LmiUnorderedBucket(K_, T_)) \
	typedef struct { \
		LmiSizeT size; \
		LmiSizeT (*hash)(const K_*); \
		LmiList(LmiPair(K_, T_)) l; \
		LmiVector(LmiUnorderedBucket(K_, T_)) v; \
	} LmiUnordered(K_, T_); \
	typedef struct { \
		LmiSizeT loadingMin; \
		LmiSizeT loadingMax; \
	} LmiUnorderedStatistics(K_, T_); \
	Declare_LmiUnorderedAssociativeContainer(LmiUnordered(K_, T_), LmiPair(K_, T_), LmiListIterator(LmiPair(K_, T_)), LmiListConstIterator(LmiPair(K_, T_)), LmiSizeT, LmiDistanceT, K_) \
	Declare_LmiUnorderedInsert_(K_, T_) \
	Declare_LmiUnorderedGetNodeSize(K_, T_) \
	Declare_LmiUnorderedGetStatistics(K_, T_) \
	Declare_LmiUnorderedGetBucketAllocator(K_, T_) \
	Declare_LmiUnorderedGetNodeAllocator(K_, T_) \
	DefineInlineHeader_LmiUnorderedFuncs(K_, T_)

#define DefineInline_LmiUnorderedBucketConstructCopy(K_, T_, INLINE_) \
INLINE_ LmiUnorderedBucket(K_, T_)* LmiUnorderedBucketConstructCopy(K_, T_)(LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y) { \
	LmiListIteratorConstructCopy(LmiPair(K_, T_))(&x->first, &y->first); \
	x->count = y->count; \
	return x; \
}

#define DefineInline_LmiUnorderedBucketDestruct(K_, T_, INLINE_) \
INLINE_ void LmiUnorderedBucketDestruct(K_, T_)(LmiUnorderedBucket(K_, T_)* x) {}

#define DefineInline_LmiUnorderedBucketAssign(K_, T_, INLINE_) \
INLINE_ LmiUnorderedBucket(K_, T_)* LmiUnorderedBucketAssign(K_, T_)(LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y) { \
	LmiListIteratorAssign(LmiPair(K_, T_))(&x->first, &y->first); \
	x->count = y->count; \
	return x; \
}
#define DefineInline_LmiUnorderedBucketEqual(K_, T_, INLINE_) \
INLINE_ LmiBool LmiUnorderedBucketEqual(K_, T_)(const LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y) { \
	return LmiListIteratorEqual(LmiPair(K_, T_))(&x->first, &y->first) && (x->count == y->count); \
}

#define DefineInline_LmiUnorderedBucketLess(K_, T_, INLINE_) \
INLINE_ LmiBool LmiUnorderedBucketLess(K_, T_)(const LmiUnorderedBucket(K_, T_)* x, const LmiUnorderedBucket(K_, T_)* y) { \
	return (x->count < y->count); \
}

#define DefineInline_LmiUnorderedBucket(K_, T_, INLINE_)   \
	DefineInline_LmiUnorderedBucketConstructCopy(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucketDestruct(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucketAssign(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucketEqual(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucketLess(K_, T_, INLINE_)

#define Define_LmiUnorderedConstruct(K_, T_) \
LmiUnordered(K_, T_)* LmiUnorderedConstruct(K_, T_)(LmiUnordered(K_, T_)* x, LmiUnorderedHashFunctionType(K_, T_) hash, LmiUnorderedSizeType(K_, T_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator) { \
	static const LmiUnorderedSizeType(K_, T_) sizes[] = { \
			   2U,        3U,         7U,        17U,        31U,         61U,        127U,        257U, \
			 509U,     1021U,      2053U,      4093U,      8191U,      16381U,      32771U,      65537U, \
		  131071U,   262147U,    524287U,   1048573U,   2097143U,    4194301U,    8388617U,   16777213U, \
		33554467U, 67108859U, 134217757U, 268435459U, 536870909U, 1073741827U, 2147483647U, 4294967291U \
	}; \
	LmiUnorderedBucket(K_, T_) b; \
	LmiUnorderedSizeType(K_, T_) i; \
	x->size = 0; \
	if (LmiListConstructDefault(LmiPair(K_, T_))(&x->l, nodeAllocator) == NULL) \
		return NULL; \
	b.first = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	b.count = 0; \
	/* Find new vector size */ \
	for (i = 0; sizes[i] < buckets; ++i) \
		; \
	if (LmiVectorConstructN(LmiUnorderedBucket(K_, T_))(&x->v, sizes[i], &b, bucketAllocator) == NULL) { \
		LmiListDestruct(LmiPair(K_, T_))(&x->l); \
		return NULL; \
	} \
	x->hash = hash; \
	return x; \
}

#define Define_LmiUnorderedConstructCopy(K_, T_) \
LmiUnordered(K_, T_)* LmiUnorderedConstructCopy(K_, T_)(LmiUnordered(K_, T_)* x, const LmiUnordered(K_, T_)* y) { \
	LmiPair(K_, T_)* p; \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	LmiListIterator(LmiPair(K_, T_)) end; \
	LmiSizeT i; \
	if (LmiListConstructCopy(LmiPair(K_, T_))(&x->l, &y->l) == NULL) \
		return NULL; \
	if (LmiVectorConstructCopy(LmiUnorderedBucket(K_, T_))(&x->v, &y->v) == NULL) \
		return NULL; \
	x->size = y->size; \
	x->hash = y->hash; \
	/* Loop over x's list and reset the iterators in x's buckets */ \
	end = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	for (pos = LmiListBegin(LmiPair(K_, T_))(&x->l); \
	  !LmiListIteratorEqual(LmiPair(K_, T_))(&pos, &end); \
	  LmiListIteratorIncrement(LmiPair(K_, T_))(&pos)) { \
		p = LmiListIteratorContentOf(LmiPair(K_, T_))(&pos); \
		b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(&p->first) % LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)); \
		LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &pos); \
		for (i = 1; i < b->count; ++i) \
			LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	/* Set all buckets with a count of zero to point at list end */ \
	for (i = 0; i < LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); ++i) { \
		b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, i); \
		if (b->count == 0) \
			LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &end); \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&end); \
	return x; \
}

#define Define_LmiUnorderedDestruct(K_, T_) \
void LmiUnorderedDestruct(K_, T_)(LmiUnordered(K_, T_)* x) { \
	LmiListDestruct(LmiPair(K_, T_))(&x->l); \
	LmiVectorDestruct(LmiUnorderedBucket(K_, T_))(&x->v); \
}

#define Define_LmiUnorderedAssign(K_, T_) \
LmiUnordered(K_, T_)* LmiUnorderedAssign(K_, T_)(LmiUnordered(K_, T_)* x, const LmiUnordered(K_, T_)* y) { \
	LmiPair(K_, T_)* p; \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	LmiListIterator(LmiPair(K_, T_)) end; \
	LmiSizeT i; \
	if (LmiListAssign(LmiPair(K_, T_))(&x->l, &y->l) == NULL) \
		return NULL; \
	if (LmiVectorAssign(LmiUnorderedBucket(K_, T_))(&x->v, &y->v) == NULL) \
		return NULL; \
	x->size = y->size; \
	x->hash = y->hash; \
	/* Loop over x's list and reset the iterators in x's buckets */ \
	end = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	for (pos = LmiListBegin(LmiPair(K_, T_))(&x->l); \
	  !LmiListIteratorEqual(LmiPair(K_, T_))(&pos, &end); \
	  LmiListIteratorIncrement(LmiPair(K_, T_))(&pos)) { \
		p = LmiListIteratorContentOf(LmiPair(K_, T_))(&pos); \
		b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(&p->first) % LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)); \
		LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &pos); \
		for (i = 1; i < b->count; ++i) \
			LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	/* Set all buckets with a count of zero to point at list end */ \
	for (i = 0; i < LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); ++i) { \
		b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, i); \
		if (b->count == 0) \
			LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &end); \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&end); \
	return x; \
}

#define Define_LmiUnorderedSwap(K_, T_) \
LmiBool LmiUnorderedSwap(K_, T_)(LmiUnordered(K_, T_)* x, LmiUnordered(K_, T_)* y) { \
	LmiSizeT tempSize = x->size; \
	LmiSizeT i; \
	LmiSizeT (*tempHash)(const K_*) = x->hash; \
	LmiListIterator(LmiPair(K_, T_)) xEnd, yEnd; \
	if ((LmiUnorderedGetBucketAllocator(K_, T_)(x) !=	\
			LmiUnorderedGetBucketAllocator(K_, T_)(y)) || \
		(LmiUnorderedGetNodeAllocator(K_, T_)(x) !=	  \
			LmiUnorderedGetNodeAllocator(K_, T_)(y))) { \
		/* TODO */ \
		return LMI_FALSE; \
	} \
	if (!LmiVectorSwap(LmiUnorderedBucket(K_, T_))(&x->v, &y->v)) { \
		return LMI_FALSE; \
	} \
	if (!LmiListSwap(LmiPair(K_, T_))(&x->l, &y->l)) { \
		return LMI_FALSE; \
	} \
	x->size = y->size; \
	y->size = tempSize; \
	x->hash = y->hash; \
	y->hash = tempHash; \
	/* Fix up empty buckets */ \
	xEnd = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	yEnd = LmiListEnd(LmiPair(K_, T_))(&y->l); \
	for (i = 0; i < LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); i++) { \
		LmiUnorderedBucket(K_, T_)* b = \
			LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, i); \
		if (LmiListIteratorEqual(LmiPair(K_, T_))(&b->first, &yEnd)) {	\
			LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &xEnd);\
		} \
	} \
	for (i = 0; i < LmiVectorSize(LmiUnorderedBucket(K_, T_))(&y->v); i++) { \
		LmiUnorderedBucket(K_, T_)* b = \
			LmiVectorAt(LmiUnorderedBucket(K_, T_))(&y->v, i); \
		if (LmiListIteratorEqual(LmiPair(K_, T_))(&b->first, &xEnd)) {	\
			LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &yEnd); \
		} \
	}				 \
	return LMI_TRUE; \
}

#define Define_LmiUnorderedBegin(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedBegin(K_, T_)(LmiUnordered(K_, T_)* x) { \
	return LmiListBegin(LmiPair(K_, T_))(&x->l); \
}

#define Define_LmiUnorderedBeginConst(K_, T_) \
LmiUnorderedConstIterator(K_, T_) LmiUnorderedBeginConst(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return LmiListBeginConst(LmiPair(K_, T_))(&x->l); \
}

#define Define_LmiUnorderedEnd(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedEnd(K_, T_)(LmiUnordered(K_, T_)* x) { \
	return LmiListEnd(LmiPair(K_, T_))(&x->l); \
}

#define Define_LmiUnorderedEndConst(K_, T_) \
LmiUnorderedConstIterator(K_, T_) LmiUnorderedEndConst(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return LmiListEndConst(LmiPair(K_, T_))(&x->l); \
}

#define Define_LmiUnorderedEmpty(K_, T_) \
LmiBool LmiUnorderedEmpty(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return (x->size == 0); \
}

#define Define_LmiUnorderedSize(K_, T_) \
LmiUnorderedSizeType(K_, T_) LmiUnorderedSize(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return x->size; \
}

#define Define_LmiUnorderedMaxSize(K_, T_) \
LmiUnorderedSizeType(K_, T_) LmiUnorderedMaxSize(K_, T_)(const	LmiUnordered(K_, T_)* x) { \
	return LmiVectorMaxSize(LmiUnorderedBucket(K_, T_))(&x->v); \
}

#define Define_LmiUnorderedCount(K_, T_) \
LmiUnorderedSizeType(K_, T_) LmiUnorderedCount(K_, T_)(const LmiUnordered(K_, T_) * x, const K_* key) { \
	LmiUnorderedSizeType(K_, T_) c = 0; \
	LmiUnorderedConstIterator(K_, T_) pos = LmiUnorderedFindConst(K_, T_)(x, key); \
	LmiUnorderedConstIterator(K_, T_) end = LmiUnorderedEndConst(K_, T_)(x); \
	while ((!LmiUnorderedConstIteratorEqual(K_, T_)(&pos, &end)) && \
	  (LmiEqual(K_)(&LmiUnorderedConstIteratorContentOf(K_, T_)(&pos)->first, key))) { \
		++c; \
		LmiUnorderedConstIteratorIncrement(K_, T_)(&pos); \
	} \
	LmiUnorderedConstIteratorDestruct(K_, T_)(&pos); \
	LmiUnorderedConstIteratorDestruct(K_, T_)(&end); \
	return c; \
}

#define Define_LmiUnorderedClear(K_, T_) \
void LmiUnorderedClear(K_, T_)(LmiUnordered(K_, T_)* x) { \
	LmiUnorderedSizeType(K_, T_) i, buckets = LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
	LmiUnorderedBucket(K_, T_) b; \
	LmiListClear(LmiPair(K_, T_))(&x->l); \
	b.first = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	b.count = 0; \
	x->size = 0; \
	LmiVectorClear(LmiUnorderedBucket(K_, T_))(&x->v); \
	for (i = 0; i < buckets; ++i) \
		LmiVectorPushBack(LmiUnorderedBucket(K_, T_))(&x->v, &b); \
}

#define Define_LmiUnorderedErase(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedErase(K_, T_)(LmiUnordered(K_, T_)* x, LmiUnorderedIterator(K_, T_) pos) { \
	LmiUnorderedSizeType(K_, T_) size = LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
	K_* k = &LmiUnorderedIteratorContentOf(K_, T_)(&pos)->first; \
	LmiUnorderedBucket(K_, T_)* b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(k) % size); \
	LmiUnorderedIterator(K_, T_) r = LmiListErase(LmiPair(K_, T_))(&x->l, pos); \
	LmiAssert(x->size != 0); \
	LmiAssert(b->count != 0); \
	--(x->size); \
	--(b->count); \
	/* If their are no more values in the bucket reset the bucket */ \
	if (b->count == 0) \
		b->first = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	/* If the value at pos is the first item in its bucket update the bucket iterator */ \
	else if (LmiUnorderedIteratorEqual(K_, T_)(&pos, &b->first)) \
		LmiUnorderedIteratorAssign(K_, T_)(&b->first, &r); \
	return r; \
}

#define Define_LmiUnorderedEraseRange(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedEraseRange(K_, T_)(LmiUnordered(K_, T_)* x, LmiUnorderedIterator(K_, T_) f, LmiUnorderedIterator(K_, T_) l) { \
	while (!LmiUnorderedIteratorEqual(K_, T_)(&f, &l)) \
		f = LmiUnorderedErase(K_, T_)(x, f); \
	return l; \
}

#define Define_LmiUnorderedEraseKey(K_, T_) \
LmiUnorderedSizeType(K_, T_) LmiUnorderedEraseKey(K_, T_)(LmiUnordered(K_, T_)* x, const K_* key) { \
	LmiUnorderedSizeType(K_, T_) size = LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
	LmiUnorderedSizeType(K_, T_) i, c = 0; \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	K_* k; \
	b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(key) % size); \
	LmiListIteratorConstructCopy(LmiPair(K_, T_))(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = &LmiListIteratorContentOf(LmiPair(K_, T_))(&pos)->first; \
		if (LmiEqual(K_)(k, key)) { \
			LmiBool first = LmiListIteratorEqual(LmiPair(K_, T_))(&pos, &b->first); \
			pos = LmiListErase(LmiPair(K_, T_))(&x->l, pos); \
			if (first) \
				LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &pos); \
			++c; \
		} else \
			LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	x->size -= c; \
	b->count -= c; \
	if (b->count == 0) b->first = LmiListEnd(LmiPair(K_, T_))(&x->l); \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	return c; \
}

#define Define_LmiUnorderedEqualRange(K_, T_) \
LmiPair(LmiUnorderedIterator(K_, T_), LmiUnorderedIterator(K_, T_)) LmiUnorderedEqualRange(K_, T_)(LmiUnordered(K_, T_)* x, const K_* key) { \
	LmiPair(LmiUnorderedIterator(K_, T_), LmiUnorderedIterator(K_, T_)) r; \
	LmiUnorderedIterator(K_, T_) end = LmiUnorderedEnd(K_, T_)(x); \
	r.first = LmiUnorderedFind(K_, T_)(x, key); \
	for (LmiUnorderedIteratorConstructCopy(K_, T_)(&r.second, &r.first); \
	  !LmiUnorderedIteratorEqual(K_, T_)(&r.second, &end); \
	  LmiUnorderedIteratorIncrement(K_, T_)(&r.second)) { \
		if (!LmiEqual(K_)(&LmiUnorderedIteratorContentOf(K_, T_)(&r.second)->first, key)) break; \
	} \
	LmiUnorderedIteratorDestruct(K_, T_)(&end); \
	return r; \
}

#define Define_LmiUnorderedEqualRangeConst(K_, T_) \
LmiPair(LmiUnorderedConstIterator(K_, T_), LmiUnorderedConstIterator(K_, T_)) LmiUnorderedEqualRangeConst(K_, T_)(const LmiUnordered(K_, T_)* x, const K_* key) { \
	LmiPair(LmiUnorderedConstIterator(K_, T_), LmiUnorderedConstIterator(K_, T_)) r; \
	LmiUnorderedConstIterator(K_, T_) end = LmiUnorderedEndConst(K_, T_)(x); \
	r.first = LmiUnorderedFindConst(K_, T_)(x, key); \
	for (LmiUnorderedConstIteratorConstructCopy(K_, T_)(&r.second, &r.first); \
	  !LmiUnorderedConstIteratorEqual(K_, T_)(&r.second, &end); \
	  LmiUnorderedConstIteratorIncrement(K_, T_)(&r.second)) { \
		if (!LmiEqual(K_)(&LmiUnorderedConstIteratorContentOf(K_, T_)(&r.second)->first, key)) break; \
	} \
	LmiUnorderedConstIteratorDestruct(K_, T_)(&end); \
	return r; \
}

#define Define_LmiUnorderedFind(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedFind(K_, T_)(LmiUnordered(K_, T_)* x, const K_* key) { \
	LmiUnorderedSizeType(K_, T_) i, size = LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	K_* k; \
	b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(key) % size); \
	LmiListIteratorConstructCopy(LmiPair(K_, T_))(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = &LmiListIteratorContentOf(LmiPair(K_, T_))(&pos)->first; \
		if (LmiEqual(K_)(k, key)) \
			break; \
		LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	return (i == b->count) ? LmiListEnd(LmiPair(K_, T_))(&x->l) : pos; \
}

#define Define_LmiUnorderedFindConst(K_, T_) \
LmiUnorderedConstIterator(K_, T_) LmiUnorderedFindConst(K_, T_)(const LmiUnordered(K_, T_)* x, const K_* key) { \
	LmiUnorderedSizeType(K_, T_) i, size = LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
	const LmiUnorderedBucket(K_, T_)* b; \
	LmiListConstIterator(LmiPair(K_, T_)) pos; \
	const K_* k; \
	b = LmiVectorAtConst(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(key) % size); \
	LmiListConstIteratorConstructCopy(LmiPair(K_, T_))(&pos, (LmiListConstIterator(LmiPair(K_, T_))*)&b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = &LmiListConstIteratorContentOf(LmiPair(K_, T_))(&pos)->first; \
		if (LmiEqual(K_)(k, key)) \
			break; \
		LmiListConstIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	LmiListConstIteratorDestruct(LmiPair(K_, T_))(&pos); \
	return (i == b->count) ? LmiListEndConst(LmiPair(K_, T_))(&x->l) : pos; \
}

#define Define_LmiUnorderedInsert_(K_, T_) \
LmiUnorderedIterator(K_, T_) LmiUnorderedInsert_(K_, T_)(LmiUnordered(K_, T_)* x, const LmiUnorderedValueType(K_, T_)* value) { \
	LmiUnorderedIterator(K_, T_) r; \
	LmiUnorderedSizeType(K_, T_) i; \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	K_* k; \
	LmiUnorderedResize(K_, T_)(x, x->size + 1); \
	b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(&value->first) % LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)); \
	LmiListIteratorConstructCopy(LmiPair(K_, T_))(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = &LmiListIteratorContentOf(LmiPair(K_, T_))(&pos)->first; \
		if (LmiEqual(K_)(k, &value->first)) break; \
		LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	r = LmiListInsert(LmiPair(K_, T_))(&x->l, pos, value); \
	/* If the insert failed ... */ \
	if (LmiListIteratorIsExceptional(LmiPair(K_, T_))(r)) return r; \
	/* If the value was added to the front of the list update the bucket iterator */ \
	if (LmiListIteratorEqual(LmiPair(K_, T_))(&pos, &b->first)) \
       LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &r); \
	++(x->size); \
	++(b->count); \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	return r; \
}

#define DefineInline_LmiUnorderedHashFunction(K_, T_, INLINE_)				\
INLINE_ LmiUnorderedHashFunctionType(K_, T_) LmiUnorderedHashFunction(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return x->hash; \
}

#define DefineInline_LmiUnorderedBucketCount(K_, T_, INLINE_)				\
INLINE_ LmiUnorderedSizeType(K_, T_) LmiUnorderedBucketCount(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v); \
}

#define Define_LmiUnorderedResize(K_, T_) \
LmiBool LmiUnorderedResize(K_, T_)(LmiUnordered(K_, T_)* x, LmiUnorderedSizeType(K_, T_) n) { \
	static const LmiUnorderedSizeType(K_, T_) sizes[] = { \
		2U,        3U,         7U,        17U,        31U,         61U,        127U,        257U, \
		509U,     1021U,      2053U,      4093U,      8191U,      16381U,      32771U,      65537U, \
		131071U,   262147U,    524287U,   1048573U,   2097143U,    4194301U,    8388617U,   16777213U, \
		33554467U, 67108859U, 134217757U, 268435459U, 536870909U, 1073741827U, 2147483647U, 4294967291U \
	}; \
	LmiBool r = LMI_TRUE; \
	if (n > LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)) { \
		LmiUnorderedSizeType(K_, T_) size = 0; \
		LmiList(LmiPair(K_, T_)) l; \
		/* Create new list */ \
		if (LmiListConstructDefault(LmiPair(K_, T_))(&l, LmiListGetAllocator(LmiPair(K_, T_))(&x->l)) == 0) { \
			r = LMI_FALSE; \
		} else { \
			LmiVector(LmiUnorderedBucket(K_, T_)) v; \
			LmiUnorderedBucket(K_, T_) b; \
			LmiUnorderedSizeType(K_, T_) i; \
			/* Create empty bucket */ \
			b.first = LmiListEnd(LmiPair(K_, T_))(&x->l); \
			b.count = 0; \
			/* Find new vector size */ \
			for (i = 0; sizes[i] < n; ++i) \
				; \
			/* Create new vector */ \
			if (LmiVectorConstructN(LmiUnorderedBucket(K_, T_))(&v, sizes[i], &b, LmiVectorGetAllocator(LmiUnorderedBucket(K_, T_))(&x->v)) == 0) { \
				r = LMI_FALSE; \
			} else { \
				LmiListIterator(LmiPair(K_, T_)) first, last, end; \
				/* Swap the original size, list & vector with the temporary ones */ \
				LmiSizeTSwap(&x->size, &size); \
				LmiListSwap(LmiPair(K_, T_))(&x->l, &l); \
				LmiVectorSwap(LmiUnorderedBucket(K_, T_))(&x->v, &v); \
				/* Construct the various iterators */ \
				first = LmiListBegin(LmiPair(K_, T_))(&l); \
				LmiListIteratorConstruct(LmiPair(K_, T_))(&last); \
				end = LmiListEnd(LmiPair(K_, T_))(&l); \
				/* Walk the original list inserting each list node range with the same key into the new list/vector */ \
				while (!LmiListIteratorEqual(LmiPair(K_, T_))(&first, &end)) { \
					K_* key = &LmiListIteratorContentOf(LmiPair(K_, T_))(&first)->first; \
					/* The search starts with last == incr(first), so count from 1. */ \
					LmiUnorderedSizeType(K_, T_) n = 1; \
					LmiUnorderedBucket(K_, T_)* bp; \
					/* Find the last list node with the same key as the current list node, and count the number of such nodes. */ \
					LmiListIteratorAssign(LmiPair(K_, T_))(&last, &first); \
					for (LmiListIteratorIncrement(LmiPair(K_, T_))(&last); \
					  !LmiListIteratorEqual(LmiPair(K_, T_))(&last, &end) && \
					  LmiEqual(K_)(&LmiListIteratorContentOf(LmiPair(K_, T_))(&last)->first, key); \
					  LmiListIteratorIncrement(LmiPair(K_, T_))(&last)) \
						++n; \
					/* Find the new bucket */ \
					bp = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(key) % LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)); \
					/* Splice the range into the new list */ \
					LmiListSplice(LmiPair(K_, T_))(&x->l, bp->first, &l, first, last); \
					LmiListIteratorAssign(LmiPair(K_, T_))(&bp->first, &first); \
					bp->count += n; \
					x->size += n; \
					LmiListIteratorAssign(LmiPair(K_, T_))(&first, &last); \
				} \
				/* Destruct various iterators */ \
				LmiListIteratorDestruct(LmiPair(K_, T_))(&first); \
				LmiListIteratorDestruct(LmiPair(K_, T_))(&last); \
				LmiListIteratorDestruct(LmiPair(K_, T_))(&end); \
				/* Destroy the temporary vector */ \
				LmiVectorDestruct(LmiUnorderedBucket(K_, T_))(&v); \
			} \
			/* Destroy the temporary list */ \
			LmiListDestruct(LmiPair(K_, T_))(&l); \
		} \
	} \
	return r; \
}

#define DefineInline_LmiUnorderedGetNodeSize(K_, T_, INLINE_)				\
INLINE_ LmiUnorderedSizeType(K_, T_) LmiUnorderedGetNodeSize(K_, T_)(const LmiUnordered(K_, T_)* x) { \
	return LmiListGetNodeSize(LmiPair(K_, T_))(&x->l); \
}

#define Define_LmiUnorderedGetStatistics(K_, T_) \
void LmiUnorderedGetStatistics(K_, T_)(const LmiUnordered(K_, T_)* x, LmiUnorderedStatistics(K_, T_)* stats) { \
	LmiVectorConstIterator(LmiUnorderedBucket(K_, T_)) pos, end; \
	stats->loadingMin = ~0; \
	stats->loadingMax = 0; \
	for (pos = LmiVectorBeginConst(LmiUnorderedBucket(K_, T_))(&x->v), \
	  end = LmiVectorEndConst(LmiUnorderedBucket(K_, T_))(&x->v); \
	  !LmiVectorConstIteratorEqual(LmiUnorderedBucket(K_, T_))(&pos, &end); \
	  LmiVectorConstIteratorIncrement(LmiUnorderedBucket(K_, T_))(&pos)) { \
		const LmiUnorderedBucket(K_, T_)* bucket; \
		bucket = LmiVectorConstIteratorContentOf(LmiUnorderedBucket(K_, T_))(&pos); \
		if (bucket->count < stats->loadingMin) \
			stats->loadingMin = bucket->count; \
		if (bucket->count > stats->loadingMax) \
			stats->loadingMax = bucket->count; \
	} \
	LmiVectorConstIteratorDestruct(LmiUnorderedBucket(K_, T_))(&pos); \
	LmiVectorConstIteratorDestruct(LmiUnorderedBucket(K_, T_))(&end); \
}

#define DefineInline_LmiUnorderedGetBucketAllocator(K_, T_, INLINE_)		\
INLINE_ LmiAllocator* LmiUnorderedGetBucketAllocator(K_, T_)(LmiUnordered(K_, T_)* x) { \
	return LmiVectorGetAllocator(LmiUnorderedBucket(K_, T_))(&x->v); \
}

#define DefineInline_LmiUnorderedGetNodeAllocator(K_, T_, INLINE_)				\
INLINE_ LmiAllocator* LmiUnorderedGetNodeAllocator(K_, T_)(LmiUnordered(K_, T_)* x) { \
	return LmiListGetAllocator(LmiPair(K_, T_))(&x->l); \
}

#define DefineInline_LmiUnorderedFuncs(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucket(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedGetNodeSize(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedGetBucketAllocator(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedGetNodeAllocator(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedHashFunction(K_, T_, INLINE_) \
	DefineInline_LmiUnorderedBucketCount(K_, T_, INLINE_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiUnorderedFuncs(K_, T_) \
	DefineInline_LmiUnorderedFuncs(K_, T_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiUnorderedFuncs(K_, T_)  /* defined as empty */
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define DefineInlineSource_LmiUnorderedFuncs(K_, T_) \
	DefineInline_LmiUnorderedFuncs(K_, T_, LMI_INLINE_SOURCE_FILE)
#else
#define DefineInlineSource_LmiUnorderedFuncs(K_, T_)  /* defined as empty */
#endif


#define Define_LmiUnordered(K_, T_) \
	Define_LmiPair(K_, T_) \
	Define_LmiList(LmiPair(K_, T_)) \
	DefineInlineSource_LmiUnorderedFuncs(K_, T_) \
	Define_LmiVector(LmiUnorderedBucket(K_, T_)) \
	Define_LmiUnorderedConstruct(K_, T_) \
	Define_LmiUnorderedConstructCopy(K_, T_) \
	Define_LmiUnorderedDestruct(K_, T_) \
	Define_LmiUnorderedAssign(K_, T_) \
	Define_LmiUnorderedSwap(K_, T_) \
	Define_LmiUnorderedBegin(K_, T_) \
	Define_LmiUnorderedBeginConst(K_, T_) \
	Define_LmiUnorderedEnd(K_, T_) \
	Define_LmiUnorderedEndConst(K_, T_) \
	Define_LmiUnorderedEmpty(K_, T_) \
	Define_LmiUnorderedSize(K_, T_) \
	Define_LmiUnorderedMaxSize(K_, T_) \
	Define_LmiUnorderedCount(K_, T_) \
	Define_LmiUnorderedClear(K_, T_) \
	Define_LmiUnorderedErase(K_, T_) \
	Define_LmiUnorderedEraseRange(K_, T_) \
	Define_LmiUnorderedEraseKey(K_, T_) \
	Define_LmiUnorderedEqualRange(K_, T_) \
	Define_LmiUnorderedEqualRangeConst(K_, T_) \
	Define_LmiUnorderedFind(K_, T_) \
	Define_LmiUnorderedFindConst(K_, T_) \
	Define_LmiUnorderedInsert_(K_, T_) \
	Define_LmiUnorderedResize(K_, T_) \
	Define_LmiUnorderedGetStatistics(K_, T_)

/* Unordered Map */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiUnorderedMap}
	{parent: LmiUnorderedMap}
	{description: Declare a parameterized unordered map container and its subtypes.}
	{prototype: void Declare_LmiUnorderedMap(Type K, Type T)}
	{parameter: 
		{name: K}
		{description: The unordered map's element key type.}
	}
	{parameter: 
		{name: T}
		{description: The unordered map's element value type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate an unordered map of integers keyed by LmiString *\/
		Declare_LmiUnorderedMap(LmiString, LmiInt)
		void func() \{
			LmiUnorderedMap(LmiString, LmiInt) numbers;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMap}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiUnordered.h}
	{description: 
		An unordered map (a.k.a hash table) is a container that contains a 
		set of elements that can be retrieved in O(Log N) time (on average). 
		No notion of ordering is maintained in.  Each element's key must be 
		unique in the unordered map.
	}
	{template-prototype: LmiUnorderedMap(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMapHashFunctionType}
	{parent: LmiUnorderedMap}
	{description: The hash function type for unordered map.}
	{template-prototype: LmiUnorderedMapHashFunctionType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type visibility="private":
	{name: LmiUnorderedMapSizeType}
	{parent: LmiUnorderedMap}
	{description: The size type for unordered map.}
	{template-prototype: LmiUnorderedMapSizeType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMapValueType}
	{parent: LmiUnorderedMap}
	{description: The value type for unordered map.  This is equivalent
	to LmiPair(K_, T_).}
	{template-prototype: LmiUnorderedMapValueType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMapStatistics}
	{parent: LmiUnorderedMap}
	{description: Describes the statistics of an unordered map.}
	{template-prototype: LmiUnorderedMapStatistics(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiUnorderedMap}
	{parent: LmiUnorderedMap}
	{description: Define a parameterized unordered map container and its subtypes.}
	{prototype: void Define_LmiUnorderedMap(Type K, Type T)}
	{parameter: 
		{name: K}
		{description: The unordered map's element key type.}
	}
	{parameter: 
		{name: T}
		{description: The unordered map's element value type.}
	}
	{example:
		/\* Instantiate a unordered map of integers container class *\/
		Define_LmiUnorderedMap(LmiString, LmiInt)
		LmiSizeT hf(const LmiString* key) \{
			return (LmiSizeT)LmiStrToInt32(LmiStringCStr(key), NULL, 10);
		\}
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiUnorderedMap(LmiString, LmiInt) numbers;
			LmiInt i;
			LmiUnorderedMapConstruct(LmiString, LmiInt)(&numbers, hf, 10,
			  LmiMallocAllocatorGetDefault(), LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiPair(LmiString, LmiInt) p;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGetDefault());
				LmiPairConstruct(LmiString, LmiInt)(&p, &name, &i);
				LmiUnorderedMapInsert(LmiString, LmiInt)(&numbers, &p);
			\}
			LmiUnorderedMapDestruct(LmiString, LmiInt)(&numbers);
		\}
	}
}
*/	

/**
{function visibility="private":
	{name: LmiUnorderedMapConstruct}
	{parent: LmiUnorderedMap}
	{description: 
		Construct an unordered map.  
	}
	{prototype: LmiUnorderedMap(K_, T_)* LmiUnorderedMapConstruct(K_, T_)(LmiUnorderedMap(K_, T_)* x, LmiUnorderedMapHashFunctionType(K_, T_) hash, LmiUnorderedMapSizeType(K_, T_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: hash}
		{description: The hash function to use.}
	}
	{parameter: 
		{name: buckets}
		{description: A hint to the initial number of buckets that the unordered map should contain.}
	}
	{parameter: 
		{name: bucketAllocator}
		{description: The allocator to use to allocate buckets. }
	}
	{parameter: 
		{name: nodeAllocator}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiUnorderedMapGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed unordered map or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapConstructCopy}
	{parent: LmiUnorderedMap}
	{description: Construct an unordered map from another unordered map.}
	{prototype: LmiUnorderedMap(K_, T_)* LmiUnorderedMapConstructCopy(K_, T_)(LmiUnorderedMap(K_, T_)* x, const LmiUnorderedMap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: y}
		{description: The unordered map to use to initialize the unordered map being constructed. }
	}
	{return: A pointer to the constructed unordered map or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapDestruct}
	{parent: LmiUnorderedMap}
	{description: Destruct an unordered map.}
	{prototype: void LmiUnorderedMapDestruct(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapAssign}
	{parent: LmiUnorderedMap}
	{description: Copy one unordered map to another unordered map.}
	{prototype: LmiUnorderedMap(K_, T_)* LmiUnorderedMapAssign(K_, T_)(LmiUnorderedMap(K_, T_)* x, const LmiUnorderedMap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: y}
		{description: The unordered map to assign from.}
	}
	{return: A pointer to the constructed unordered map or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapSwap}
	{parent: LmiUnorderedMap}
	{description: Swap two unordered maps.}
	{prototype: LmiBool LmiUnorderedMapSwap(K_, T_)(LmiUnorderedMap(K_, T_)* x, LmiUnorderedMap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: y}
		{description: The other unordered map.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapBegin}
	{parent: LmiUnorderedMap}
	{description: Gets an iterator to the first element in the unordered map.}
	{prototype: LmiUnorderedMapIterator(K_, T_) LmiUnorderedMapBegin(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: An iterator to the first element in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapBeginConst}
	{parent: LmiUnorderedMap}
	{description: Gets a read-only iterator to the first element in the unordered map.}
	{prototype: LmiUnorderedMapConstIterator(K_, T_) LmiUnorderedMapBeginConst(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: A read-only iterator to the first element in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEnd}
	{parent: LmiUnorderedMap}
	{description: Gets an iterator to the element one past the last element in the unordered map.}
	{prototype: LmiUnorderedMapIterator(K_, T_) LmiUnorderedMapEnd(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: An iterator to the element one past the last element in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEndConst}
	{parent: LmiUnorderedMap}
	{description: Gets a read-only iterator to the element one past the last element in the unordered map.}
	{prototype: LmiUnorderedMapConstIterator(K_, T_) LmiUnorderedMapEndConst(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: A read-only iterator to the element one past the last element in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEmpty}
	{parent: LmiUnorderedMap}
	{description: Determines whether the unordered map contains any elements.}
	{prototype: LmiBool LmiUnorderedMapEmpty(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: LMI_TRUE if the unordered map is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapSize}
	{parent: LmiUnorderedMap}
	{description: Gets the number of elements in the unordered map.}
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapSize(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The number of elements in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapMaxSize}
	{parent: LmiUnorderedMap}
	{description: Gets the maximum size that the unordered map can be.}
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapMaxSize(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The maximum number of elements that the unordered map can hold.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapCount}
	{parent: LmiUnorderedMap}
	{description: Gets the number of elements in the unordered map with a given key. }
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapCount(K_, T_)(const LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the unordered map with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapClear}
	{parent: LmiUnorderedMap}
	{description: Removes all elements from the unordered map.}
	{prototype: void LmiUnorderedMapClear(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapErase}
	{parent: LmiUnorderedMap}
	{description: Removes the specified element from the unordered map.}
	{prototype: LmiUnorderedMapIterator(K_, T_) LmiUnorderedMapErase(K_, T_)(LmiUnorderedMap(K_, T_)* x, LmiUnorderedMapIterator(K_, T_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEraseRange}
	{parent: LmiUnorderedMap}
	{description: Removes all elements in the specified range from the unordered map.}
	{prototype: LmiUnorderedMapIterator(K_, T_) LmiUnorderedMapEraseRange(K_, T_)(LmiUnorderedMap(K_, T_)* x, LmiUnorderedMapIterator(K_, T_) f, LmiUnorderedMapIterator(K_, T_) l)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEraseKey}
	{parent: LmiUnorderedMap}
	{description: Remove all elements in the unordered map with a specified key.}
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapEraseKey(K_, T_)(LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEqualRange}
	{parent: LmiUnorderedMap}
	{description: Gets a pair of iterators pointing to all elements in the unordered map with the specified key.}
	{prototype: LmiPair(LmiUnorderedMapIterator(K_, T_), LmiUnorderedMapIterator(K_, T_)) LmiUnorderedMapEqualRange(K_, T_)(LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapEqualRangeConst}
	{parent: LmiUnorderedMap}
	{description: Gets a pair of read-only iterators pointing to all elements in the unordered map with the specified key.}
	{prototype: LmiPair(LmiUnorderedMapConstIterator(K_, T_), LmiUnorderedMapConstIterator(K_, T_)) LmiUnorderedMapEqualRangeConst(K_, T_)(const LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapFind}
	{parent: LmiUnorderedMap}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMapIterator(K_, T_) LmiUnorderedMapFind(K_, T_)(LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the unordered map whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapFindConst}
	{parent: LmiUnorderedMap}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMapConstIterator(K_, T_) LmiUnorderedMapFindConst(K_, T_)(const LmiUnorderedMap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the unordered map whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapInsert}
	{parent: LmiUnorderedMap}
	{description: Inserts an element into the unordered map.}
	{prototype: LmiPair(LmiUnorderedMapIterator(K_, T_), LmiBool) LmiUnorderedMapInsert(K_, T_)(LmiUnorderedMap(K_, T_)* x, const LmiUnorderedMapValueType(K_, T_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: value}
		{description: A pair whose first member is the element's key and the whose second member is the element's value.}
	}
	{return: 
		Returns a pair containing an iterator and a boolean.  Upon successful 
		insertion the pair's iterator points to the newly inserted element and 
		the pair's boolean value is set to LMI_TRUE.  If the element is already 
		present in the unordered map, then the pair's iterator points to that 
		element and the pair's boolean value is set to LMI_FALSE.  If any other 
		error (such as memory exhaustion) occurs, the pair's iterator is set to 
		NULL and the pair's boolean value is set to LMI_FALSE.
	}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapHashFunction}
	{parent: LmiUnorderedMap}
	{description: Gets a pointer to the hash function of the unordered map.}
	{prototype: LmiUnorderedMapHashFunctionType(K_, T_) LmiUnorderedMapHashFunction(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The hash function of the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapBucketCount}
	{parent: LmiUnorderedMap}
	{description: Gets the number of buckets in the unordered map.  A bucket
	contains all elements whose keys hash to the same index.}
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapBucketCount(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The number of buckets in the unordered map.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapResize}
	{parent: LmiUnorderedMap}
	{description: Resizes an unordered map.  Resizing changes the number of
	buckets used to store the elements, not the number of elements. Also, the
	number of buckets specified, may not be the actual number of buckets the 
	unordered map resizes uses. The specified size is only a hint to the object.}
	{prototype: LmiBool LmiUnorderedMapResize(K_, T_)(LmiUnorderedMap(K_, T_)* x, LmiUnorderedMapSizeType(K_, T_) n)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: n}
		{description: A hint to the number of buckets to size the unordered map to. }
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapGetNodeSize}
	{parent: LmiUnorderedMap}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiUnorderedMapSizeType(K_, T_) LmiUnorderedMapGetNodeSize(K_, T_)(const LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapGetStatistics}
	{parent: LmiUnorderedMap}
	{description: Gets performance statistics.}
	{prototype: void LmiUnorderedMapGetStatistics(K_, T_)(const LmiUnorderedMap(K_, T_)* x, LmiUnorderedMapStatistics(K_, T_)* stats)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{parameter: 
		{name: stats}
		{description: A point to a statistics object to be filled in. }
	}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapGetBucketAllocator}
	{parent: LmiUnorderedMap}
	{description: Gets a map\'s bucket allocator.}
	{prototype: LmiAllocator* LmiUnorderedMapGetBucketAllocator(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The allocator passed to the map\'s constructor as its bucket allocator.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMapGetNodeAllocator}
	{parent: LmiUnorderedMap}
	{description: Gets a map\'s node allocator.}
	{prototype: LmiAllocator* LmiUnorderedMapGetNodeAllocator(K_, T_)(LmiUnorderedMap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered map.}
	}
	{return: The allocator passed to the map\'s constructor as its node allocator.}
	{note: 
		The macro Define_LmiUnorderedMap must be called at global scope before calling 
		any LmiUnorderedMap member functions. 
	}
}
*/
#define LmiUnorderedMap(K_, T_)											LmiTemplate2(LmiUnordered, K_, T_)
#define LmiUnorderedMapHashFunctionType(K_, T_)							LmiHashFunctionType(LmiUnordered(K_, T_))
#define LmiUnorderedMapSizeType(K_, T_)									LmiSizeType(LmiUnordered(K_, T_))
#define LmiUnorderedMapValueType(K_, T_)								LmiValueType(LmiUnordered(K_, T_))
#define LmiUnorderedMapConstruct(K_, T_)								LmiConstruct(LmiUnordered(K_, T_))
#define LmiUnorderedMapConstructRange(K_, T_)							LmiConstructRange(LmiUnordered(K_, T_))
#define LmiUnorderedMapConstructCopy(K_, T_)							LmiConstructCopy(LmiUnordered(K_, T_))
#define LmiUnorderedMapDestruct(K_, T_)									LmiDestruct(LmiUnordered(K_, T_))
#define LmiUnorderedMapAssign(K_, T_)									LmiAssign(LmiUnordered(K_, T_))
#define LmiUnorderedMapSwap(K_, T_)										LmiSwap(LmiUnordered(K_, T_))
#define LmiUnorderedMapBegin(K_, T_)									LmiBegin(LmiUnordered(K_, T_))
#define LmiUnorderedMapBeginConst(K_, T_)								LmiBeginConst(LmiUnordered(K_, T_))
#define LmiUnorderedMapEnd(K_, T_)										LmiEnd(LmiUnordered(K_, T_))
#define LmiUnorderedMapEndConst(K_, T_)									LmiEndConst(LmiUnordered(K_, T_))
#define LmiUnorderedMapEmpty(K_, T_)									LmiEmpty(LmiUnordered(K_, T_))
#define LmiUnorderedMapSize(K_, T_)										LmiSize(LmiUnordered(K_, T_))
#define LmiUnorderedMapMaxSize(K_, T_)									LmiMaxSize(LmiUnordered(K_, T_))
#define LmiUnorderedMapCount(K_, T_)									LmiCount(LmiUnordered(K_, T_))
#define LmiUnorderedMapEqual(K_, T_)									LmiEqual(LmiUnordered(K_, T_))
#define LmiUnorderedMapLess(K_, T_)										LmiLess(LmiUnordered(K_, T_))
#define LmiUnorderedMapInsert(K_, T_)									LmiInsert(LmiUnorderedMap(K_, T_))
#define LmiUnorderedMapInsertRange(K_, T_)								LmiInsertRange(LmiUnordered(K_, T_))
#define LmiUnorderedMapAt(K_, T_)										LmiAt(LmiUnordered(K_, T_))
#define LmiUnorderedMapClear(K_, T_)									LmiClear(LmiUnordered(K_, T_))
#define LmiUnorderedMapErase(K_, T_)									LmiErase(LmiUnordered(K_, T_))
#define LmiUnorderedMapEraseRange(K_, T_)								LmiEraseRange(LmiUnordered(K_, T_))
#define LmiUnorderedMapEraseKey(K_, T_)									LmiEraseKey(LmiUnordered(K_, T_))
#define LmiUnorderedMapEqualRange(K_, T_)								LmiEqualRange(LmiUnordered(K_, T_))
#define LmiUnorderedMapEqualRangeConst(K_, T_)							LmiEqualRangeConst(LmiUnordered(K_, T_))
#define LmiUnorderedMapFind(K_, T_)										LmiFind(LmiUnordered(K_, T_))
#define LmiUnorderedMapFindConst(K_, T_)								LmiFindConst(LmiUnordered(K_, T_))
#define LmiUnorderedMapBucketCount(K_, T_)								LmiBucketCount(LmiUnordered(K_, T_))
#define LmiUnorderedMapHashFunction(K_, T_)								LmiHashFunction(LmiUnordered(K_, T_))
#define LmiUnorderedMapResize(K_, T_)									LmiResize(LmiUnordered(K_, T_))
#define LmiUnorderedMapGetStatistics(K_, T_)							LmiUnorderedGetStatistics(K_, T_)
#define LmiUnorderedMapGetBucketAllocator(K_, T_)						LmiUnorderedGetBucketAllocator(K_, T_)
#define LmiUnorderedMapGetNodeAllocator(K_, T_)							LmiUnorderedGetNodeAllocator(K_, T_)

/* Unordered Map Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedMapIterator}
	{parent: LmiUnorderedMap}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for unordered map.}
	{template-prototype: LmiUnorderedMapIterator(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
#define LmiUnorderedMapIterator(K_, T_)									LmiIterator(LmiUnordered(K_, T_))
#define LmiUnorderedMapIteratorConstruct(K_, T_)						LmiConstruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorDestruct(K_, T_)							LmiDestruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorConstructCopy(K_, T_)					LmiConstructCopy(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorAssign(K_, T_)							LmiAssign(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorSwap(K_, T_)								LmiSwap(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorEqual(K_, T_)							LmiEqual(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorContentOf(K_, T_)						LmiContentOf(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorIncrement(K_, T_)						LmiIncrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorDecrement(K_, T_)						LmiDecrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorConstructExceptional(K_, T_)				LmiConstructExceptional(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapIteratorIsExceptional(K_, T_)					LmiIsExceptional(LmiListIterator(LmiPair(K_, T_)))
																		
/* Unordered Map Const Iterator */										
/**
{type visibility="private":
	{name: LmiUnorderedMapConstIterator}
	{parent: LmiUnorderedMap}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for unordered map.}
	{template-prototype: LmiUnorderedMapConstIterator(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered map's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered map's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMap must be called before declaring an 
		object of this type.  
	}
}
*/
#define LmiUnorderedMapConstIterator(K_, T_)							LmiConstIterator(LmiUnordered(K_, T_))
#define LmiUnorderedMapConstIteratorConstruct(K_, T_)					LmiConstruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorDestruct(K_, T_)					LmiDestruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorConstructCopy(K_, T_)				LmiConstructCopy(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorAssign(K_, T_)						LmiAssign(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorSwap(K_, T_)						LmiSwap(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorEqual(K_, T_)						LmiEqual(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorContentOf(K_, T_)					LmiContentOf(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorIncrement(K_, T_)					LmiIncrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorDecrement(K_, T_)					LmiDecrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorConstructExceptional(K_, T_)		LmiConstructExceptional(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMapConstIteratorIsExceptional(K_, T_)				LmiIsExceptional(LmiListConstIterator(LmiPair(K_, T_)))

#define Define_LmiUnorderedMapInsert(K_, T_) \
LmiPair(LmiUnorderedMapIterator(K_, T_), LmiBool) LmiUnorderedMapInsert(K_, T_)(LmiUnorderedMap(K_, T_)* x, const LmiUnorderedMapValueType(K_, T_)* value) { \
	LmiPair(LmiUnorderedMapIterator(K_, T_), LmiBool) r; \
	LmiUnorderedSizeType(K_, T_) i; \
	LmiUnorderedBucket(K_, T_)* b; \
	LmiListIterator(LmiPair(K_, T_)) pos; \
	LmiUnorderedResize(K_, T_)(x, x->size + 1); \
	b = LmiVectorAt(LmiUnorderedBucket(K_, T_))(&x->v, x->hash(&value->first) % LmiVectorSize(LmiUnorderedBucket(K_, T_))(&x->v)); \
	LmiListIteratorConstructCopy(LmiPair(K_, T_))(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		K_* k; \
		k = &LmiListIteratorContentOf(LmiPair(K_, T_))(&pos)->first; \
		if (LmiEqual(K_)(k, &value->first)) { \
			LmiListIteratorAssign(LmiPair(K_, T_))(&r.first, &pos); \
			LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
			r.second = LMI_FALSE; \
			return r; \
		} \
		LmiListIteratorIncrement(LmiPair(K_, T_))(&pos); \
	} \
	r.first = LmiListInsert(LmiPair(K_, T_))(&x->l, pos, value); \
	/* If the insert did not fail ... */ \
	if (!LmiListIteratorIsExceptional(LmiPair(K_, T_))(r.first)) { \
		/* If the value was added to the front of the list update the bucket iterator */ \
		if (LmiListIteratorEqual(LmiPair(K_, T_))(&pos, &b->first)) \
			LmiListIteratorAssign(LmiPair(K_, T_))(&b->first, &r.first); \
		++(x->size); \
		++(b->count); \
		r.second = LMI_TRUE; \
	} else { \
		r.second = LMI_FALSE; \
	} \
	LmiListIteratorDestruct(LmiPair(K_, T_))(&pos); \
	return r; \
}

#define Declare_LmiUnorderedMapAt(K_, T_) \
	T_ *LmiUnorderedMapAt(K_, T_)(LmiUnorderedMap(K_, T_) *map, const K_ *key);

#define Define_LmiUnorderedMapAt(K_, T_) \
T_ *LmiUnorderedMapAt(K_, T_)(LmiUnorderedMap(K_, T_) *map, const K_ *key) { \
	LmiUnorderedMapValueType(K_, T_) value; \
	LmiPair(LmiUnorderedMapIterator(K_, T_), LmiBool) insertResult; \
	LmiConstructCopy(K_)(&value.first, key); \
	LmiConstruct(T_)(&value.second); \
	insertResult = LmiUnorderedMapInsert(K_, T_)(map, &value); \
	LmiDestruct(T_)(&value.second); \
	LmiDestruct(K_)(&value.first); \
	return &LmiUnorderedMapIteratorContentOf(K_, T_)(&insertResult.first)->second; \
}

#define Declare_LmiUnorderedMap(K_, T_) \
	Declare_LmiUnordered(K_, T_) \
	Declare_LmiUniqueAssociativeContainerTypesPart(LmiUnorderedMap(K_, T_)) \
	Declare_LmiUniqueAssociativeContainerFuncsPart(LmiUnorderedMap(K_, T_))

#define Define_LmiUnorderedMap(K_, T_) \
	Define_LmiUnordered(K_, T_) \
	Define_LmiUnorderedMapInsert(K_, T_)

/* Unordered Multimap */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiUnorderedMultimap}
	{parent: LmiUnorderedMultimap}
	{description: Declare a parameterized unordered multimap container and its subtypes.}
	{prototype: void Declare_LmiUnorderedMultimap(Type K, Type T)}
	{parameter: 
		{name: K}
		{description: The unordered multimap's element key type.}
	}
	{parameter: 
		{name: T}
		{description: The unordered multimap's element value type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate an unordered multimap of integers keyed by LmiString *\/
		Declare_LmiUnorderedMultimap(LmiString, LmiInt)
		void func() \{
			LmiUnorderedMultimap(LmiString, LmiInt) numbers;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultimap}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiUnordered.h}
	{description: 
		An unordered multimap (a.k.a hash table) is a container that contains a 
		set of elements that can be retrieved in O(Log N) time (on average). 
		No notion of ordering is maintained in.  Multiple elements with the same 
		key may be stored in the unordered multimap.
	}
	{template-prototype: LmiUnorderedMultimap(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultimap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultimapHashFunctionType}
	{parent: LmiUnorderedMultimap}
	{description: The hash function type for unordered multimap.}
	{template-prototype: LmiUnorderedMultimapHashFunctionType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultimap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultimapSizeType}
	{parent: LmiUnorderedMultimap}
	{description: The size type for unordered multimap.}
	{template-prototype: LmiUnorderedMultimapSizeType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultimap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultimapValueType}
	{parent: LmiUnorderedMultimap}
	{description: The value type for unordered multimap.  This is equivalent
	to LmiPair(K_, T_).}
	{template-prototype: LmiUnorderedMultimapValueType(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultimap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultimapStatistics}
	{parent: LmiUnorderedMultimap}
	{description: Describes the statistics of an unordered multimap.}
	{template-prototype: LmiUnorderedMultimapStatistics(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultimap must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiUnorderedMultimap}
	{parent: LmiUnorderedMultimap}
	{description: Define a parameterized unordered multimap container and its subtypes.}
	{prototype: void Define_LmiUnorderedMultimap(Type K, Type T)}
	{parameter: 
		{name: K}
		{description: The unordered multimap's element key type.}
	}
	{parameter: 
		{name: T}
		{description: The unordered multimap's element value type.}
	}
	{example:
		/\* Instantiate a unordered multimap of integers container class *\/
		Define_LmiUnorderedMultimap(LmiString, LmiInt)
		LmiSizeT hf(const LmiString* key) \{
			return (LmiSizeT)LmiStrToInt32(LmiStringCStr(key), NULL, 10);
		\}
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiUnorderedMultimap(LmiString, LmiInt) numbers;
			LmiInt i;
			LmiUnorderedMultimapConstruct(LmiString, LmiInt)(&numbers, hf, 10,
			  LmiMallocAllocatorGetDefault(), LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiPair(LmiString, LmiInt) p;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGetDefault());
				LmiPairConstruct(LmiString, LmiInt)(&p, &name, &i);
				LmiUnorderedMultimapInsert(LmiString, LmiInt)(&numbers, &p);
			\}
			LmiUnorderedMultimapDestruct(LmiString, LmiInt)(&numbers);
		\}
	}
}
*/	
/**
{function visibility="private":
	{name: LmiUnorderedMultimapConstruct}
	{parent: LmiUnorderedMultimap}
	{description: 
		Construct an unordered multimap.}
	{prototype: LmiUnorderedMultimap(K_, T_)* LmiUnorderedMultimapConstruct(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimapHashFunctionType(K_, T_) hash, LmiUnorderedMultimapSizeType(K_, T_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: hash}
		{description: The hash function to use.}
	}
	{parameter: 
		{name: buckets}
		{description: A hint to the initial number of buckets that the unordered multimap should contain.}
	}
	{parameter: 
		{name: bucketAllocator}
		{description: The allocator to use to allocate buckets. }
	}
	{parameter: 
		{name: nodeAllocator}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiUnorderedMultimapGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed unordered multimap or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapConstructCopy}
	{parent: LmiUnorderedMultimap}
	{description: Construct an unordered multimap from another unordered multimap.}
	{prototype: LmiUnorderedMultimap(K_, T_)* LmiUnorderedMultimapConstructCopy(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const LmiUnorderedMultimap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: y}
		{description: The unordered multimap to use to initialize the unordered multimap being constructed. }
	}
	{return: A pointer to the constructed unordered multimap or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapDestruct}
	{parent: LmiUnorderedMultimap}
	{description: Destruct an unordered multimap.}
	{prototype: void LmiUnorderedMultimapDestruct(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapAssign}
	{parent: LmiUnorderedMultimap}
	{description: Copy one unordered multimap to another unordered multimap.}
	{prototype: LmiUnorderedMultimap(K_, T_)* LmiUnorderedMultimapAssign(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const LmiUnorderedMultimap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: y}
		{description: The unordered multimap to assign from.}
	}
	{return: A pointer to the constructed unordered multimap or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapSwap}
	{parent: LmiUnorderedMultimap}
	{description: Swap two unordered multimaps.}
	{prototype: LmiBool LmiUnorderedMultimapSwap(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimap(K_, T_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: y}
		{description: The other unordered multimap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapBegin}
	{parent: LmiUnorderedMultimap}
	{description: Gets an iterator to the first element in the unordered multimap.}
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapBegin(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: An iterator to the first element in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapBeginConst}
	{parent: LmiUnorderedMultimap}
	{description: Gets a read-only iterator to the first element in the unordered multimap.}
	{prototype: LmiUnorderedMultimapConstIterator(K_, T_) LmiUnorderedMultimapBeginConst(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: A read-only iterator to the first element in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEnd}
	{parent: LmiUnorderedMultimap}
	{description: Gets an iterator to the element one past the last element in the unordered multimap.}
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapEnd(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: An iterator to the element one past the last element in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEndConst}
	{parent: LmiUnorderedMultimap}
	{description: Gets a read-only iterator to the element one past the last element in the unordered multimap.}
	{prototype: LmiUnorderedMultimapConstIterator(K_, T_) LmiUnorderedMultimapEndConst(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: A read-only iterator to the element one past the last element in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEmpty}
	{parent: LmiUnorderedMultimap}
	{description: Determines whether the unordered multimap contains any elements.}
	{prototype: LmiBool LmiUnorderedMultimapEmpty(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: LMI_TRUE if the unordered multimap is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapSize}
	{parent: LmiUnorderedMultimap}
	{description: Gets the number of elements in the unordered multimap.}
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapSize(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The number of elements in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapMaxSize}
	{parent: LmiUnorderedMultimap}
	{description: Gets the maximum size that the unordered multimap can be.}
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapMaxSize(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The maximum number of elements that the unordered multimap can hold.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapCount}
	{parent: LmiUnorderedMultimap}
	{description: Gets the number of elements in the unordered multimap with a given key. }
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapCount(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the unordered multimap with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapClear}
	{parent: LmiUnorderedMultimap}
	{description: Removes all elements from the unordered multimap.}
	{prototype: void LmiUnorderedMultimapClear(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapErase}
	{parent: LmiUnorderedMultimap}
	{description: Removes the specified element from the unordered multimap.}
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapErase(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimapIterator(K_, T_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEraseRange}
	{parent: LmiUnorderedMultimap}
	{description: Removes all elements in the specified range from the unordered multimap.}
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapEraseRange(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimapIterator(K_, T_) f, LmiUnorderedMultimapIterator(K_, T_) l)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEraseKey}
	{parent: LmiUnorderedMultimap}
	{description: Remove all elements in the unordered multimap with a specified key.}
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapEraseKey(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEqualRange}
	{parent: LmiUnorderedMultimap}
	{description: Gets a pair of iterators pointing to all elements in the unordered multimap with the specified key.}
	{prototype: LmiPair(LmiUnorderedMultimapIterator(K_, T_), LmiUnorderedMultimapIterator(K_, T_)) LmiUnorderedMultimapEqualRange(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapEqualRangeConst}
	{parent: LmiUnorderedMultimap}
	{description: Gets a pair of read-only iterators pointing to all elements in the unordered multimap with the specified key.}
	{prototype: LmiPair(LmiUnorderedMultimapConstIterator(K_, T_), LmiUnorderedMultimapConstIterator(K_, T_)) LmiUnorderedMultimapEqualRangeConst(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapFind}
	{parent: LmiUnorderedMultimap}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapFind(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the unordered multimap whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapFindConst}
	{parent: LmiUnorderedMultimap}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMultimapConstIterator(K_, T_) LmiUnorderedMultimapFindConst(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the unordered multimap whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapInsert}
	{parent: LmiUnorderedMultimap}
	{description: Inserts an element into the unordered multimap.}
	{prototype: LmiUnorderedMultimapIterator(K_, T_) LmiUnorderedMultimapInsert(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, const LmiUnorderedMultimapValueType(K_, T_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: value}
		{description: A pair whose first member is the element's key and the whose second member is the element's value.}
	}
	{return: An iterator to the newly inserted element or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapHashFunction}
	{parent: LmiUnorderedMultimap}
	{description: Gets a pointer to the hash function of the unordered multimap.}
	{prototype: LmiUnorderedMultimapHashFunctionType(K_, T_) LmiUnorderedMultimapHashFunction(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The hash function of the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapBucketCount}
	{parent: LmiUnorderedMultimap}
	{description: Gets the number of buckets in the unordered multimap.  A bucket
	contains all elements whose keys hash to the same index.}
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapBucketCount(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The number of buckets in the unordered multimap.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapResize}
	{parent: LmiUnorderedMultimap}
	{description: Resizes an unordered multimap.  Resizing changes the number of
	buckets used to store the elements, not the number of elements. Also, the
	number of buckets specified, may not be the actual number of buckets the 
	unordered multimap resizes uses. The specified size is only a hint to the object.}
	{prototype: LmiBool LmiUnorderedMultimapResize(K_, T_)(LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimapSizeType(K_, T_) n)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: n}
		{description: A hint to the number of buckets to size the unordered multimap to. }
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapGetNodeSize}
	{parent: LmiUnorderedMultimap}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiUnorderedMultimapSizeType(K_, T_) LmiUnorderedMultimapGetNodeSize(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapGetStatistics}
	{parent: LmiUnorderedMultimap}
	{description: Gets performance statistics.}
	{prototype: void LmiUnorderedMultimapGetStatistics(K_, T_)(const LmiUnorderedMultimap(K_, T_)* x, LmiUnorderedMultimapStatistics(K_, T_)* stats)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{parameter: 
		{name: stats}
		{description: A point to a statistics object to be filled in. }
	}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapGetBucketAllocator}
	{parent: LmiUnorderedMultimap}
	{description: Gets a multimap\'s bucket allocator.}
	{prototype: LmiAllocator* LmiUnorderedMultimapGetBucketAllocator(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The allocator passed to the multimap\'s constructor as its bucket allocator.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultimapGetNodeAllocator}
	{parent: LmiUnorderedMultimap}
	{description: Gets a multimap\'s node allocator.}
	{prototype: LmiAllocator* LmiUnorderedMultimapGetNodeAllocator(K_, T_)(LmiUnorderedMultimap(K_, T_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multimap.}
	}
	{return: The allocator passed to the multimap\'s constructor as its node allocator.}
	{note: 
		The macro Define_LmiUnorderedMultimap must be called at global scope before calling 
		any LmiUnorderedMultimap member functions. 
	}
}
*/
#define LmiUnorderedMultimap(K_, T_)									LmiTemplate2(LmiUnordered, K_, T_)
#define LmiUnorderedMultimapHashFunctionType(K_, T_)					LmiHashFunctionType(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapSizeType(K_, T_)							LmiSizeType(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapValueType(K_, T_)							LmiValueType(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapConstruct(K_, T_)							LmiConstruct(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapConstructRange(K_, T_)						LmiConstructRange(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapConstructCopy(K_, T_)						LmiConstructCopy(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapDestruct(K_, T_)							LmiDestruct(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapAssign(K_, T_)								LmiAssign(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapSwap(K_, T_)								LmiSwap(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapBegin(K_, T_)								LmiBegin(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapBeginConst(K_, T_)							LmiBeginConst(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEnd(K_, T_)									LmiEnd(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEndConst(K_, T_)							LmiEndConst(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEmpty(K_, T_)								LmiEmpty(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapSize(K_, T_)								LmiSize(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapMaxSize(K_, T_)								LmiMaxSize(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapCount(K_, T_)								LmiCount(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEqual(K_, T_)								LmiEqual(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapLess(K_, T_)								LmiLess(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapInsert(K_, T_)								LmiUnorderedInsert_(K_, T_)
#define LmiUnorderedMultimapInsertRange(K_, T_)							LmiInsertRange(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapClear(K_, T_)								LmiClear(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapErase(K_, T_)								LmiErase(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEraseRange(K_, T_)							LmiEraseRange(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEraseKey(K_, T_)							LmiEraseKey(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEqualRange(K_, T_)							LmiEqualRange(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapEqualRangeConst(K_, T_)						LmiEqualRangeConst(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapFind(K_, T_)								LmiFind(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapFindConst(K_, T_)							LmiFindConst(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapBucketCount(K_, T_)							LmiBucketCount(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapHashFunction(K_, T_)						LmiHashFunction(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapResize(K_, T_)								LmiResize(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapGetStatistics(K_, T_)						LmiUnorderedGetStatistics(K_, T_)
#define LmiUnorderedMultimapGetBucketAllocator(K_, T_)					LmiUnorderedGetBucketAllocator(K_, T_)
#define LmiUnorderedMultimapGetNodeAllocator(K_, T_)					LmiUnorderedGetNodeAllocator(K_, T_)

/* Unordered Multimap Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedMultimapIterator}
	{parent: LmiUnorderedMultimap}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for unordered multimap.}
	{template-prototype: LmiUnorderedMultimapIterator(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
}
*/
#define LmiUnorderedMultimapIterator(K_, T_)							LmiIterator(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapIteratorConstruct(K_, T_)					LmiConstruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorDestruct(K_, T_)					LmiDestruct(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorConstructCopy(K_, T_)				LmiConstructCopy(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorAssign(K_, T_)						LmiAssign(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorSwap(K_, T_)						LmiSwap(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorEqual(K_, T_)						LmiEqual(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorContentOf(K_, T_)					LmiContentOf(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorIncrement(K_, T_)					LmiIncrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorDecrement(K_, T_)					LmiDecrement(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorConstructExceptional(K_, T_)		LmiConstructExceptional(LmiListIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapIteratorIsExceptional(K_, T_)				LmiIsExceptional(LmiListIterator(LmiPair(K_, T_)))

/* Unordered Map Const Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedMultimapConstIterator}
	{parent: LmiUnorderedMultimap}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for unordered multimap.}
	{template-prototype: LmiUnorderedMultimapConstIterator(K_, T_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multimap's element key type.}
	}
	{template-parameter: 
		{name: T_}
		{description: The unordered multimap's element value type.}
	}
}
*/
#define LmiUnorderedMultimapConstIterator(K_, T_)						LmiConstIterator(LmiUnordered(K_, T_))
#define LmiUnorderedMultimapConstIteratorConstruct(K_, T_)				LmiConstruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorDestruct(K_, T_)				LmiDestruct(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorConstructCopy(K_, T_)			LmiConstructCopy(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorAssign(K_, T_)					LmiAssign(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorSwap(K_, T_)					LmiSwap(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorEqual(K_, T_)					LmiEqual(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorContentOf(K_, T_)				LmiContentOf(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorIncrement(K_, T_)				LmiIncrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorDecrement(K_, T_)				LmiDecrement(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorConstructExceptional(K_, T_)	LmiConstructExceptional(LmiListConstIterator(LmiPair(K_, T_)))
#define LmiUnorderedMultimapConstIteratorIsExceptional(K_, T_)			LmiIsExceptional(LmiListConstIterator(LmiPair(K_, T_)))

#define Declare_LmiUnorderedMultimap(K_, T_) \
	Declare_LmiUnordered(K_, T_) \
	Declare_LmiMultipleAssociativeContainerTypesPart(LmiUnordered(K_, T_)) \
	Declare_LmiMultipleAssociativeContainerFuncsPart(LmiUnordered(K_, T_))

#define Define_LmiUnorderedMultimap(K_, T_) \
	Define_LmiUnordered(K_, T_)

/**************************************************** Set & Multiset *******************************************************/
/* Unordered Set & Multiset Bucket */
#define LmiUSetBucket(K_)										LmiTemplate1(LmiUSetBucket, K_)
#define LmiUSetBucketConstructCopy(K_)							LmiConstructCopy(LmiUSetBucket(K_))
#define LmiUSetBucketDestruct(K_)								LmiDestruct(LmiUSetBucket(K_))
#define LmiUSetBucketAssign(K_)									LmiAssign(LmiUSetBucket(K_))
#define LmiUSetBucketEqual(K_)									LmiEqual(LmiUSetBucket(K_))
#define LmiUSetBucketLess(K_)									LmiLess(LmiUSetBucket(K_))

/* Unordered Set & Multiset Statistics */
#define LmiUSetStatistics(K_)									LmiTemplate1(LmiUSetStatistics, K_)

/* Unordered Set Internal Representation */
#define LmiUSet(K_)												LmiTemplate1(LmiUSet, K_)
#define LmiUSetHashFunctionType(K_)								LmiHashFunctionType(LmiUSet(K_))
#define LmiUSetSizeType(K_)										LmiSizeType(LmiUSet(K_))
#define LmiUSetValueType(K_)									LmiValueType(LmiUSet(K_))
#define LmiUSetConstruct(K_)									LmiConstruct(LmiUSet(K_))
#define LmiUSetConstructRange(K_)								LmiConstructRange(LmiUSet(K_))
#define LmiUSetConstructCopy(K_)								LmiConstructCopy(LmiUSet(K_))
#define LmiUSetDestruct(K_)										LmiDestruct(LmiUSet(K_))
#define LmiUSetAssign(K_)										LmiAssign(LmiUSet(K_))
#define LmiUSetSwap(K_)											LmiSwap(LmiUSet(K_))
#define LmiUSetBegin(K_)										LmiBegin(LmiUSet(K_))
#define LmiUSetBeginConst(K_)									LmiBeginConst(LmiUSet(K_))
#define LmiUSetEnd(K_)											LmiEnd(LmiUSet(K_))
#define LmiUSetEndConst(K_)										LmiEndConst(LmiUSet(K_))
#define LmiUSetEmpty(K_)										LmiEmpty(LmiUSet(K_))
#define LmiUSetSize(K_)											LmiSize(LmiUSet(K_))
#define LmiUSetMaxSize(K_)										LmiMaxSize(LmiUSet(K_))
#define LmiUSetCount(K_)										LmiCount(LmiUSet(K_))
#define LmiUSetEqual(K_)										LmiEqual(LmiUSet(K_))
#define LmiUSetLess(K_)											LmiLess(LmiUSet(K_))
#define LmiUSetClear(K_)										LmiClear(LmiUSet(K_))
#define LmiUSetErase(K_)										LmiErase(LmiUSet(K_))
#define LmiUSetEraseRange(K_)									LmiEraseRange(LmiUSet(K_))
#define LmiUSetEraseKey(K_)										LmiEraseKey(LmiUSet(K_))
#define LmiUSetEqualRange(K_)									LmiEqualRange(LmiUSet(K_))
#define LmiUSetEqualRangeConst(K_)								LmiEqualRangeConst(LmiUSet(K_))
#define LmiUSetFind(K_)											LmiFind(LmiUSet(K_))
#define LmiUSetFindConst(K_)									LmiFindConst(LmiUSet(K_))
#define LmiUSetInsert_(K_)										LmiUSetInsert_##_##K_##__##T_
#define LmiUSetBucketCount(K_)									LmiBucketCount(LmiUSet(K_))
#define LmiUSetHashFunction(K_)									LmiHashFunction(LmiUSet(K_))
#define LmiUSetResize(K_)										LmiResize(LmiUSet(K_))
#define LmiUSetGetNodeSize(K_)									LmiClassFunc(LmiUSet(K_), GetNodeSize)
#define LmiUSetGetStatistics(K_)								LmiClassFunc(LmiUSet(K_), GetStatistics)
#define LmiUSetGetBucketAllocator(K_)							LmiClassFunc(LmiUSet(K_), GetBucketAllocator)
#define LmiUSetGetNodeAllocator(K_)								LmiClassFunc(LmiUSet(K_), GetNodeAllocator)


/* Unordered Set Iterator Internal Representation */
#define LmiUSetIterator(K_)										LmiIterator(LmiUSet(K_))
#define LmiUSetIteratorConstruct(K_)							LmiConstruct(LmiListIterator(K_))
#define LmiUSetIteratorDestruct(K_)								LmiDestruct(LmiListIterator(K_))
#define LmiUSetIteratorConstructCopy(K_)						LmiConstructCopy(LmiListIterator(K_))
#define LmiUSetIteratorAssign(K_)								LmiAssign(LmiListIterator(K_))
#define LmiUSetIteratorSwap(K_)									LmiSwap(LmiListIterator(K_))
#define LmiUSetIteratorEqual(K_)								LmiEqual(LmiListIterator(K_))
#define LmiUSetIteratorContentOf(K_)							LmiContentOf(LmiListIterator(K_))
#define LmiUSetIteratorIncrement(K_)							LmiIncrement(LmiListIterator(K_))
#define LmiUSetIteratorDecrement(K_)							LmiDecrement(LmiListIterator(K_))
#define LmiUSetIteratorConstructExceptional(K_)					LmiConstructExceptional(LmiListIterator(K_))
#define LmiUSetIteratorIsExceptional(K_)						LmiIsExceptional(LmiListIterator(K_))

/* Unordered Set Const Iterator Internal Representation */
#define LmiUSetConstIterator(K_)								LmiConstIterator(LmiUSet(K_))
#define LmiUSetConstIteratorConstruct(K_)						LmiConstruct(LmiListConstIterator(K_))
#define LmiUSetConstIteratorDestruct(K_)						LmiDestruct(LmiListConstIterator(K_))
#define LmiUSetConstIteratorConstructCopy(K_)					LmiConstructCopy(LmiListConstIterator(K_))
#define LmiUSetConstIteratorAssign(K_)							LmiAssign(LmiListConstIterator(K_))
#define LmiUSetConstIteratorSwap(K_)							LmiSwap(LmiListConstIterator(K_))
#define LmiUSetConstIteratorEqual(K_)							LmiEqual(LmiListConstIterator(K_))
#define LmiUSetConstIteratorContentOf(K_)						LmiContentOf(LmiListConstIterator(K_))
#define LmiUSetConstIteratorIncrement(K_)						LmiIncrement(LmiListConstIterator(K_))
#define LmiUSetConstIteratorDecrement(K_)						LmiDecrement(LmiListConstIterator(K_))
#define LmiUSetConstIteratorConstructExceptional(K_)			LmiConstructExceptional(LmiListConstIterator(K_))
#define LmiUSetConstIteratorIsExceptional(K_)					LmiIsExceptional(LmiListConstIterator(K_))

#define Declare_LmiUSetInsert_(K_) \
LmiUSetIterator(K_) LmiUSetInsert_(K_)(LmiUSet(K_)* x, const LmiUSetValueType(K_)* value);

#define Declare_LmiUSetGetNodeSize(K_) \
LMI_INLINE_DECLARATION LmiUSetSizeType(K_) LmiUSetGetNodeSize(K_)(const LmiUSet(K_)* x);

#define Declare_LmiUSetGetStatistics(K_) \
void LmiUSetGetStatistics(K_)(const LmiUSet(K_)* x, LmiUSetStatistics(K_)* stats);

#define Declare_LmiUSetGetBucketAllocator(K_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiUSetGetBucketAllocator(K_)(LmiUSet(K_)* x);

#define Declare_LmiUSetGetNodeAllocator(K_) \
LMI_INLINE_DECLARATION LmiAllocator* LmiUSetGetNodeAllocator(K_)(LmiUSet(K_)* x);

#define Declare_LmiUSet(K_) \
	Declare_LmiList(K_) \
	typedef struct { \
		LmiListIterator(K_) first; \
		LmiSizeT count; \
	} LmiUSetBucket(K_); \
	LMI_INLINE_DECLARATION LmiUSetBucket(K_)* LmiUSetBucketConstructCopy(K_)(LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y); \
	LMI_INLINE_DECLARATION void LmiUSetBucketDestruct(K_)(LmiUSetBucket(K_)* x); \
	LMI_INLINE_DECLARATION LmiUSetBucket(K_)* LmiUSetBucketAssign(K_)(LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y); \
	LMI_INLINE_DECLARATION LmiBool LmiUSetBucketEqual(K_)(const LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y); \
	LMI_INLINE_DECLARATION LmiBool LmiUSetBucketLess(K_)(const LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y); \
	Declare_LmiVector(LmiUSetBucket(K_)) \
	typedef struct { \
		LmiSizeT size; \
		LmiSizeT (*hash)(const K_*); \
		LmiList(K_) l; \
		LmiVector(LmiUSetBucket(K_)) v; \
	} LmiUSet(K_); \
	typedef struct { \
		LmiSizeT loadingMin; \
		LmiSizeT loadingMax; \
	} LmiUSetStatistics(K_); \
	Declare_LmiUnorderedAssociativeContainer(LmiUSet(K_), K_, LmiListIterator(K_), LmiListConstIterator(K_), LmiSizeT, LmiDistanceT, K_) \
	Declare_LmiUSetInsert_(K_) \
	Declare_LmiUSetGetNodeSize(K_) \
	Declare_LmiUSetGetStatistics(K_) \
	Declare_LmiUSetGetBucketAllocator(K_) \
	Declare_LmiUSetGetNodeAllocator(K_) \
	DefineInlineHeader_LmiUSetFuncs(K_)

#define DefineInline_LmiUSetBucketConstructCopy(K_, INLINE_) \
INLINE_ LmiUSetBucket(K_)* LmiUSetBucketConstructCopy(K_)(LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y) { \
	LmiListIteratorConstructCopy(K_)(&x->first, &y->first); \
	x->count = y->count; \
	return x; \
}

#define DefineInline_LmiUSetBucketDestruct(K_, INLINE_) \
INLINE_ void LmiUSetBucketDestruct(K_)(LmiUSetBucket(K_)* x) {}

#define DefineInline_LmiUSetBucketAssign(K_, INLINE_) \
INLINE_ LmiUSetBucket(K_)* LmiUSetBucketAssign(K_)(LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y) { \
	LmiListIteratorAssign(K_)(&x->first, &y->first); \
	x->count = y->count; \
	return x; \
}
#define DefineInline_LmiUSetBucketEqual(K_, INLINE_) \
INLINE_ LmiBool LmiUSetBucketEqual(K_)(const LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y) { \
	return LmiListIteratorEqual(K_)(&x->first, &y->first) && (x->count == y->count); \
}

#define DefineInline_LmiUSetBucketLess(K_, INLINE_) \
INLINE_ LmiBool LmiUSetBucketLess(K_)(const LmiUSetBucket(K_)* x, const LmiUSetBucket(K_)* y) { \
	return (x->count < y->count); \
}

#define DefineInline_LmiUSetBucket(K_, INLINE_)   \
	DefineInline_LmiUSetBucketConstructCopy(K_, INLINE_) \
	DefineInline_LmiUSetBucketDestruct(K_, INLINE_) \
	DefineInline_LmiUSetBucketAssign(K_, INLINE_) \
	DefineInline_LmiUSetBucketEqual(K_, INLINE_) \
	DefineInline_LmiUSetBucketLess(K_, INLINE_)

#define Define_LmiUSetConstruct(K_) \
LmiUSet(K_)* LmiUSetConstruct(K_)(LmiUSet(K_)* x, LmiUSetHashFunctionType(K_) hash, LmiUSetSizeType(K_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator) { \
	static const LmiUSetSizeType(K_) sizes[] = { \
			   2U,        3U,         7U,        17U,        31U,         61U,        127U,        257U, \
			 509U,     1021U,      2053U,      4093U,      8191U,      16381U,      32771U,      65537U, \
		  131071U,   262147U,    524287U,   1048573U,   2097143U,    4194301U,    8388617U,   16777213U, \
		33554467U, 67108859U, 134217757U, 268435459U, 536870909U, 1073741827U, 2147483647U, 4294967291U \
	}; \
	LmiUSetBucket(K_) b; \
	LmiUSetSizeType(K_) i; \
	x->size = 0; \
	if (LmiListConstructDefault(K_)(&x->l, nodeAllocator) == NULL) \
		return NULL; \
	b.first = LmiListEnd(K_)(&x->l); \
	b.count = 0; \
	/* Find new vector size */ \
	for (i = 0; sizes[i] < buckets; ++i) \
		; \
	if (LmiVectorConstructN(LmiUSetBucket(K_))(&x->v, sizes[i], &b, bucketAllocator) == NULL) { \
		LmiListDestruct(K_)(&x->l); \
		return NULL; \
	} \
	x->hash = hash; \
	return x; \
}

#define Define_LmiUSetConstructCopy(K_) \
LmiUSet(K_)* LmiUSetConstructCopy(K_)(LmiUSet(K_)* x, const LmiUSet(K_)* y) { \
	K_* p; \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	LmiListIterator(K_) end; \
	LmiSizeT i; \
	if (LmiListConstructCopy(K_)(&x->l, &y->l) == NULL) \
		return NULL; \
	if (LmiVectorConstructCopy(LmiUSetBucket(K_))(&x->v, &y->v) == NULL) \
		return NULL; \
	x->size = y->size; \
	x->hash = y->hash; \
	/* Loop over x's list and reset the iterators in x's buckets */ \
	end = LmiListEnd(K_)(&x->l); \
	for (pos = LmiListBegin(K_)(&x->l); \
	  !LmiListIteratorEqual(K_)(&pos, &end); \
	  LmiListIteratorIncrement(K_)(&pos)) { \
		p = LmiListIteratorContentOf(K_)(&pos); \
		b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(p) % LmiVectorSize(LmiUSetBucket(K_))(&x->v)); \
		LmiListIteratorAssign(K_)(&b->first, &pos); \
		for (i = 1; i < b->count; ++i) \
			LmiListIteratorIncrement(K_)(&pos); \
	} \
	LmiListIteratorDestruct(K_)(&pos); \
	/* Set all buckets with a count of zero to point at list end */ \
	for (i = 0; i < LmiVectorSize(LmiUSetBucket(K_))(&x->v); ++i) { \
		b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, i); \
		if (b->count == 0) \
			LmiListIteratorAssign(K_)(&b->first, &end); \
	} \
	LmiListIteratorDestruct(K_)(&end); \
	return x; \
}

#define Define_LmiUSetDestruct(K_) \
void LmiUSetDestruct(K_)(LmiUSet(K_)* x) { \
	LmiListDestruct(K_)(&x->l); \
	LmiVectorDestruct(LmiUSetBucket(K_))(&x->v); \
}

#define Define_LmiUSetAssign(K_) \
LmiUSet(K_)* LmiUSetAssign(K_)(LmiUSet(K_)* x, const LmiUSet(K_)* y) { \
	K_* p; \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	LmiListIterator(K_) end; \
	LmiSizeT i; \
	if (LmiListAssign(K_)(&x->l, &y->l) == NULL) \
		return NULL; \
	if (LmiVectorAssign(LmiUSetBucket(K_))(&x->v, &y->v) == NULL) \
		return NULL; \
	x->size = y->size; \
	x->hash = y->hash; \
	/* Loop over x's list and reset the iterators in x's buckets */ \
	end = LmiListEnd(K_)(&x->l); \
	for (pos = LmiListBegin(K_)(&x->l); \
	  !LmiListIteratorEqual(K_)(&pos, &end); \
	  LmiListIteratorIncrement(K_)(&pos)) { \
		p = LmiListIteratorContentOf(K_)(&pos); \
		b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(p) % LmiVectorSize(LmiUSetBucket(K_))(&x->v)); \
		LmiListIteratorAssign(K_)(&b->first, &pos); \
		for (i = 1; i < b->count; ++i) \
			LmiListIteratorIncrement(K_)(&pos); \
	} \
	LmiListIteratorDestruct(K_)(&pos); \
	/* Set all buckets with a count of zero to point at list end */ \
	for (i = 0; i < LmiVectorSize(LmiUSetBucket(K_))(&x->v); ++i) { \
		b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, i); \
		if (b->count == 0) \
			LmiListIteratorAssign(K_)(&b->first, &end); \
	} \
	LmiListIteratorDestruct(K_)(&end); \
	return x; \
}

#define Define_LmiUSetSwap(K_) \
LmiBool LmiUSetSwap(K_)(LmiUSet(K_)* x, LmiUSet(K_)* y) { \
	LmiSizeT tempSize = x->size; \
	LmiSizeT i; \
	LmiSizeT (*tempHash)(const K_*) = x->hash; \
	LmiListIterator(K_) xEnd, yEnd; \
	if ((LmiUSetGetBucketAllocator(K_)(x) !=	\
			LmiUSetGetBucketAllocator(K_)(y)) || \
		(LmiUSetGetNodeAllocator(K_)(x) !=	  \
			LmiUSetGetNodeAllocator(K_)(y))) { \
		/* TODO */ \
		return LMI_FALSE; \
	} \
	if (!LmiVectorSwap(LmiUSetBucket(K_))(&x->v, &y->v)) { \
		return LMI_FALSE; \
	} \
	if (!LmiListSwap(K_)(&x->l, &y->l)) { \
		return LMI_FALSE; \
	} \
	x->size = y->size; \
	y->size = tempSize; \
	x->hash = y->hash; \
	y->hash = tempHash; \
	/* Fix up empty buckets */ \
	xEnd = LmiListEnd(K_)(&x->l); \
	yEnd = LmiListEnd(K_)(&y->l); \
	for (i = 0; i < LmiVectorSize(LmiUSetBucket(K_))(&x->v); i++) { \
		LmiUSetBucket(K_)* b = \
			LmiVectorAt(LmiUSetBucket(K_))(&x->v, i); \
		if (LmiListIteratorEqual(K_)(&b->first, &yEnd)) {	\
			LmiListIteratorAssign(K_)(&b->first, &xEnd);\
		} \
	} \
	for (i = 0; i < LmiVectorSize(LmiUSetBucket(K_))(&y->v); i++) { \
		LmiUSetBucket(K_)* b = \
			LmiVectorAt(LmiUSetBucket(K_))(&y->v, i); \
		if (LmiListIteratorEqual(K_)(&b->first, &xEnd)) {	\
			LmiListIteratorAssign(K_)(&b->first, &yEnd); \
		} \
	}				 \
	return LMI_TRUE; \
}

#define Define_LmiUSetBegin(K_) \
LmiUSetIterator(K_) LmiUSetBegin(K_)(LmiUSet(K_)* x) { \
	return LmiListBegin(K_)(&x->l); \
}

#define Define_LmiUSetBeginConst(K_) \
LmiUSetConstIterator(K_) LmiUSetBeginConst(K_)(const LmiUSet(K_)* x) { \
	return LmiListBeginConst(K_)(&x->l); \
}

#define Define_LmiUSetEnd(K_) \
LmiUSetIterator(K_) LmiUSetEnd(K_)(LmiUSet(K_)* x) { \
	return LmiListEnd(K_)(&x->l); \
}

#define Define_LmiUSetEndConst(K_) \
LmiUSetConstIterator(K_) LmiUSetEndConst(K_)(const LmiUSet(K_)* x) { \
	return LmiListEndConst(K_)(&x->l); \
}

#define Define_LmiUSetEmpty(K_) \
LmiBool LmiUSetEmpty(K_)(const LmiUSet(K_)* x) { \
	return (x->size == 0); \
}

#define Define_LmiUSetSize(K_) \
LmiUSetSizeType(K_) LmiUSetSize(K_)(const LmiUSet(K_)* x) { \
	return x->size; \
}

#define Define_LmiUSetMaxSize(K_) \
LmiUSetSizeType(K_) LmiUSetMaxSize(K_)(const	LmiUSet(K_)* x) { \
	return LmiVectorMaxSize(LmiUSetBucket(K_))(&x->v); \
}

#define Define_LmiUSetCount(K_) \
LmiUSetSizeType(K_) LmiUSetCount(K_)(const LmiUSet(K_) * x, const K_* key) { \
	LmiUSetSizeType(K_) c = 0; \
	LmiUSetConstIterator(K_) pos = LmiUSetFindConst(K_)(x, key); \
	LmiUSetConstIterator(K_) end = LmiUSetEndConst(K_)(x); \
	while ((!LmiUSetConstIteratorEqual(K_)(&pos, &end)) && \
	  (LmiEqual(K_)(LmiUSetConstIteratorContentOf(K_)(&pos), key))) { \
		++c; \
		LmiUSetConstIteratorIncrement(K_)(&pos); \
	} \
	LmiUSetConstIteratorDestruct(K_)(&pos); \
	LmiUSetConstIteratorDestruct(K_)(&end); \
	return c; \
}

#define Define_LmiUSetClear(K_) \
void LmiUSetClear(K_)(LmiUSet(K_)* x) { \
	LmiUSetSizeType(K_) i, buckets = LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
	LmiUSetBucket(K_) b; \
	LmiListClear(K_)(&x->l); \
	b.first = LmiListEnd(K_)(&x->l); \
	b.count = 0; \
	x->size = 0; \
	LmiVectorClear(LmiUSetBucket(K_))(&x->v); \
	for (i = 0; i < buckets; ++i) \
		LmiVectorPushBack(LmiUSetBucket(K_))(&x->v, &b); \
}

#define Define_LmiUSetErase(K_) \
LmiUSetIterator(K_) LmiUSetErase(K_)(LmiUSet(K_)* x, LmiUSetIterator(K_) pos) { \
	LmiUSetSizeType(K_) size = LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
	K_* k = LmiUSetIteratorContentOf(K_)(&pos); \
	LmiUSetBucket(K_)* b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(k) % size); \
	LmiUSetIterator(K_) r = LmiListErase(K_)(&x->l, pos); \
	LmiAssert(x->size != 0); \
	LmiAssert(b->count != 0); \
	--(x->size); \
	--(b->count); \
	/* If their are no more values in the bucket reset the bucket */ \
	if (b->count == 0) \
		b->first = LmiListEnd(K_)(&x->l); \
	/* If the value at pos is the first item in its bucket update the bucket iterator */ \
	else if (LmiUSetIteratorEqual(K_)(&pos, &b->first)) \
		LmiUSetIteratorAssign(K_)(&b->first, &r); \
	return r; \
}

#define Define_LmiUSetEraseRange(K_) \
LmiUSetIterator(K_) LmiUSetEraseRange(K_)(LmiUSet(K_)* x, LmiUSetIterator(K_) f, LmiUSetIterator(K_) l) { \
	while (!LmiUSetIteratorEqual(K_)(&f, &l)) \
		f = LmiUSetErase(K_)(x, f); \
	return l; \
}

#define Define_LmiUSetEraseKey(K_) \
LmiUSetSizeType(K_) LmiUSetEraseKey(K_)(LmiUSet(K_)* x, const K_* key) { \
	LmiUSetSizeType(K_) size = LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
	LmiUSetSizeType(K_) i, c = 0; \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	K_* k; \
	b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(key) % size); \
	LmiListIteratorConstructCopy(K_)(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = LmiListIteratorContentOf(K_)(&pos); \
		if (LmiEqual(K_)(k, key)) { \
			LmiBool first = LmiListIteratorEqual(K_)(&pos, &b->first); \
			pos = LmiListErase(K_)(&x->l, pos); \
			if (first) \
				LmiListIteratorAssign(K_)(&b->first, &pos); \
			++c; \
		} else \
			LmiListIteratorIncrement(K_)(&pos); \
	} \
	x->size -= c; \
	b->count -= c; \
	if (b->count == 0) b->first = LmiListEnd(K_)(&x->l); \
	LmiListIteratorDestruct(K_)(&pos); \
	return c; \
}

#define Define_LmiUSetEqualRange(K_) \
LmiPair(LmiUSetIterator(K_), LmiUSetIterator(K_)) LmiUSetEqualRange(K_)(LmiUSet(K_)* x, const K_* key) { \
	LmiPair(LmiUSetIterator(K_), LmiUSetIterator(K_)) r; \
	LmiUSetIterator(K_) end = LmiUSetEnd(K_)(x); \
	r.first = LmiUSetFind(K_)(x, key); \
	for (LmiUSetIteratorConstructCopy(K_)(&r.second, &r.first); \
	  !LmiUSetIteratorEqual(K_)(&r.second, &end); \
	  LmiUSetIteratorIncrement(K_)(&r.second)) { \
		if (!LmiEqual(K_)(LmiUSetIteratorContentOf(K_)(&r.second), key)) break; \
	} \
	LmiUSetIteratorDestruct(K_)(&end); \
	return r; \
}

#define Define_LmiUSetEqualRangeConst(K_) \
LmiPair(LmiUSetConstIterator(K_), LmiUSetConstIterator(K_)) LmiUSetEqualRangeConst(K_)(const LmiUSet(K_)* x, const K_* key) { \
	LmiPair(LmiUSetConstIterator(K_), LmiUSetConstIterator(K_)) r; \
	LmiUSetConstIterator(K_) end = LmiUSetEndConst(K_)(x); \
	r.first = LmiUSetFindConst(K_)(x, key); \
	for (LmiUSetConstIteratorConstructCopy(K_)(&r.second, &r.first); \
	  !LmiUSetConstIteratorEqual(K_)(&r.second, &end); \
	  LmiUSetConstIteratorIncrement(K_)(&r.second)) { \
		if (!LmiEqual(K_)(LmiUSetConstIteratorContentOf(K_)(&r.second), key)) break; \
	} \
	LmiUSetConstIteratorDestruct(K_)(&end); \
	return r; \
}

#define Define_LmiUSetFind(K_) \
LmiUSetIterator(K_) LmiUSetFind(K_)(LmiUSet(K_)* x, const K_* key) { \
	LmiUSetSizeType(K_) i, size = LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	K_* k; \
	b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(key) % size); \
	LmiListIteratorConstructCopy(K_)(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = LmiListIteratorContentOf(K_)(&pos); \
		if (LmiEqual(K_)(k, key)) \
			break; \
		LmiListIteratorIncrement(K_)(&pos); \
	} \
	LmiListIteratorDestruct(K_)(&pos); \
	return (i == b->count) ? LmiListEnd(K_)(&x->l) : pos; \
}

#define Define_LmiUSetFindConst(K_) \
LmiUSetConstIterator(K_) LmiUSetFindConst(K_)(const LmiUSet(K_)* x, const K_* key) { \
	LmiUSetSizeType(K_) i, size = LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
	const LmiUSetBucket(K_)* b; \
	LmiListConstIterator(K_) pos; \
	const K_* k; \
	b = LmiVectorAtConst(LmiUSetBucket(K_))(&x->v, x->hash(key) % size); \
	LmiListConstIteratorConstructCopy(K_)(&pos, (LmiListConstIterator(K_)*)&b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = LmiListConstIteratorContentOf(K_)(&pos); \
		if (LmiEqual(K_)(k, key)) \
			break; \
		LmiListConstIteratorIncrement(K_)(&pos); \
	} \
	LmiListConstIteratorDestruct(K_)(&pos); \
	return (i == b->count) ? LmiListEndConst(K_)(&x->l) : pos; \
}

#define Define_LmiUSetInsert_(K_) \
LmiUSetIterator(K_) LmiUSetInsert_(K_)(LmiUSet(K_)* x, const LmiUSetValueType(K_)* value) { \
	LmiUSetIterator(K_) r; \
	LmiUSetSizeType(K_) i; \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	K_* k; \
	LmiUSetResize(K_)(x, x->size + 1); \
	b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(value) % LmiVectorSize(LmiUSetBucket(K_))(&x->v)); \
	LmiListIteratorConstructCopy(K_)(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		k = LmiListIteratorContentOf(K_)(&pos); \
		if (LmiEqual(K_)(k, value)) break; \
		LmiListIteratorIncrement(K_)(&pos); \
	} \
	r = LmiListInsert(K_)(&x->l, pos, value); \
	/* If the insert failed ... */ \
	if (LmiListIteratorIsExceptional(K_)(r)) return r; \
	/* If the value was added to the front of the list update the bucket iterator */ \
	if (LmiListIteratorEqual(K_)(&pos, &b->first)) \
		LmiListIteratorAssign(K_)(&b->first, &r); \
	++(x->size); \
	++(b->count); \
	LmiListIteratorDestruct(K_)(&pos); \
	return r; \
}

#define DefineInline_LmiUSetHashFunction(K_, INLINE_)				\
INLINE_ LmiUSetHashFunctionType(K_) LmiUSetHashFunction(K_)(const LmiUSet(K_)* x) { \
	return x->hash; \
}

#define DefineInline_LmiUSetBucketCount(K_, INLINE_)				\
INLINE_ LmiUSetSizeType(K_) LmiUSetBucketCount(K_)(const LmiUSet(K_)* x) { \
	return LmiVectorSize(LmiUSetBucket(K_))(&x->v); \
}

#define Define_LmiUSetResize(K_) \
LmiBool LmiUSetResize(K_)(LmiUSet(K_)* x, LmiUSetSizeType(K_) n) { \
	static const LmiUSetSizeType(K_) sizes[] = { \
		2U,        3U,         7U,        17U,        31U,         61U,        127U,        257U, \
		509U,     1021U,      2053U,      4093U,      8191U,      16381U,      32771U,      65537U, \
		131071U,   262147U,    524287U,   1048573U,   2097143U,    4194301U,    8388617U,   16777213U, \
		33554467U, 67108859U, 134217757U, 268435459U, 536870909U, 1073741827U, 2147483647U, 4294967291U \
	}; \
	LmiBool r = LMI_TRUE; \
	if (n > LmiVectorSize(LmiUSetBucket(K_))(&x->v)) { \
		LmiUSetSizeType(K_) size = 0; \
		LmiList(K_) l; \
		/* Create new list */ \
		if (LmiListConstructDefault(K_)(&l, LmiListGetAllocator(K_)(&x->l)) == 0) { \
			r = LMI_FALSE; \
		} else { \
			LmiVector(LmiUSetBucket(K_)) v; \
			LmiUSetBucket(K_) b; \
			LmiUSetSizeType(K_) i; \
			/* Create empty bucket */ \
			b.first = LmiListEnd(K_)(&x->l); \
			b.count = 0; \
			/* Find new vector size */ \
			for (i = 0; sizes[i] < n; ++i) \
				; \
			/* Create new vector */ \
			if (LmiVectorConstructN(LmiUSetBucket(K_))(&v, sizes[i], &b, LmiVectorGetAllocator(LmiUSetBucket(K_))(&x->v)) == 0) { \
				r = LMI_FALSE; \
			} else { \
				LmiListIterator(K_) first, last, end; \
				/* Swap the original size, list & vector with the temporary ones */ \
				LmiSizeTSwap(&x->size, &size); \
				LmiListSwap(K_)(&x->l, &l); \
				LmiVectorSwap(LmiUSetBucket(K_))(&x->v, &v); \
				/* Construct the various iterators */ \
				first = LmiListBegin(K_)(&l); \
				LmiListIteratorConstruct(K_)(&last); \
				end = LmiListEnd(K_)(&l); \
				/* Walk the original list inserting each list node range with the same key into the new list/vector */ \
				while (!LmiListIteratorEqual(K_)(&first, &end)) { \
					K_* key = LmiListIteratorContentOf(K_)(&first); \
					/* The search starts with last == incr(first), so count from 1. */ \
					LmiUSetSizeType(K_) n = 1; \
					LmiUSetBucket(K_)* bp; \
					/* Find the last list node with the same key as the current list node, and count the number of such nodes. */ \
					LmiListIteratorAssign(K_)(&last, &first); \
					for (LmiListIteratorIncrement(K_)(&last); \
					  !LmiListIteratorEqual(K_)(&last, &end) && \
					  LmiEqual(K_)(LmiListIteratorContentOf(K_)(&last), key); \
					  LmiListIteratorIncrement(K_)(&last)) \
						++n; \
					/* Find the new bucket */ \
					bp = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(key) % LmiVectorSize(LmiUSetBucket(K_))(&x->v)); \
					/* Splice the range into the new list */ \
					LmiListSplice(K_)(&x->l, bp->first, &l, first, last); \
					LmiListIteratorAssign(K_)(&bp->first, &first); \
					bp->count += n; \
					x->size += n; \
					LmiListIteratorAssign(K_)(&first, &last); \
				} \
				/* Destruct various iterators */ \
				LmiListIteratorDestruct(K_)(&first); \
				LmiListIteratorDestruct(K_)(&last); \
				LmiListIteratorDestruct(K_)(&end); \
				/* Destroy the temporary vector */ \
				LmiVectorDestruct(LmiUSetBucket(K_))(&v); \
			} \
			/* Destroy the temporary list */ \
			LmiListDestruct(K_)(&l); \
		} \
	} \
	return r; \
}

#define DefineInline_LmiUSetGetNodeSize(K_, INLINE_)				\
INLINE_ LmiUSetSizeType(K_) LmiUSetGetNodeSize(K_)(const LmiUSet(K_)* x) { \
	return LmiListGetNodeSize(K_)(&x->l); \
}

#define Define_LmiUSetGetStatistics(K_) \
void LmiUSetGetStatistics(K_)(const LmiUSet(K_)* x, LmiUSetStatistics(K_)* stats) { \
	LmiVectorConstIterator(LmiUSetBucket(K_)) pos, end; \
	stats->loadingMin = ~0; \
	stats->loadingMax = 0; \
	for (pos = LmiVectorBeginConst(LmiUSetBucket(K_))(&x->v), \
	  end = LmiVectorEndConst(LmiUSetBucket(K_))(&x->v); \
	  !LmiVectorConstIteratorEqual(LmiUSetBucket(K_))(&pos, &end); \
	  LmiVectorConstIteratorIncrement(LmiUSetBucket(K_))(&pos)) { \
		const LmiUSetBucket(K_)* bucket; \
		bucket = LmiVectorConstIteratorContentOf(LmiUSetBucket(K_))(&pos); \
		if (bucket->count < stats->loadingMin) \
			stats->loadingMin = bucket->count; \
		if (bucket->count > stats->loadingMax) \
			stats->loadingMax = bucket->count; \
	} \
	LmiVectorConstIteratorDestruct(LmiUSetBucket(K_))(&pos); \
	LmiVectorConstIteratorDestruct(LmiUSetBucket(K_))(&end); \
}

#define DefineInline_LmiUSetGetBucketAllocator(K_, INLINE_)		\
INLINE_ LmiAllocator* LmiUSetGetBucketAllocator(K_)(LmiUSet(K_)* x) { \
	return LmiVectorGetAllocator(LmiUSetBucket(K_))(&x->v); \
}

#define DefineInline_LmiUSetGetNodeAllocator(K_, INLINE_)				\
INLINE_ LmiAllocator* LmiUSetGetNodeAllocator(K_)(LmiUSet(K_)* x) { \
	return LmiListGetAllocator(K_)(&x->l); \
}

#define DefineInline_LmiUSetFuncs(K_, INLINE_) \
	DefineInline_LmiUSetBucket(K_, INLINE_) \
	DefineInline_LmiUSetGetNodeSize(K_, INLINE_) \
	DefineInline_LmiUSetGetBucketAllocator(K_, INLINE_) \
	DefineInline_LmiUSetGetNodeAllocator(K_, INLINE_) \
	DefineInline_LmiUSetHashFunction(K_, INLINE_) \
	DefineInline_LmiUSetBucketCount(K_, INLINE_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiUSetFuncs(K_) \
	DefineInline_LmiUSetFuncs(K_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiUSetFuncs(K_)  /* defined as empty */
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define DefineInlineSource_LmiUSetFuncs(K_) \
	DefineInline_LmiUSetFuncs(K_, LMI_INLINE_SOURCE_FILE)
#else
#define DefineInlineSource_LmiUSetFuncs(K_)  /* defined as empty */
#endif


#define Define_LmiUSet(K_) \
	Define_LmiList(K_) \
	DefineInlineSource_LmiUSetFuncs(K_) \
	Define_LmiVector(LmiUSetBucket(K_)) \
	Define_LmiUSetConstruct(K_) \
	Define_LmiUSetConstructCopy(K_) \
	Define_LmiUSetDestruct(K_) \
	Define_LmiUSetAssign(K_) \
	Define_LmiUSetSwap(K_) \
	Define_LmiUSetBegin(K_) \
	Define_LmiUSetBeginConst(K_) \
	Define_LmiUSetEnd(K_) \
	Define_LmiUSetEndConst(K_) \
	Define_LmiUSetEmpty(K_) \
	Define_LmiUSetSize(K_) \
	Define_LmiUSetMaxSize(K_) \
	Define_LmiUSetCount(K_) \
	Define_LmiUSetClear(K_) \
	Define_LmiUSetErase(K_) \
	Define_LmiUSetEraseRange(K_) \
	Define_LmiUSetEraseKey(K_) \
	Define_LmiUSetEqualRange(K_) \
	Define_LmiUSetEqualRangeConst(K_) \
	Define_LmiUSetFind(K_) \
	Define_LmiUSetFindConst(K_) \
	Define_LmiUSetInsert_(K_) \
	Define_LmiUSetResize(K_) \
	Define_LmiUSetGetStatistics(K_)

/* Unordered Set */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiUnorderedSet}
	{parent: LmiUnorderedSet}
	{description: Declare a parameterized unordered set container and its subtypes.}
	{prototype: void Declare_LmiUnorderedSet(Type K)}
	{parameter: 
		{name: K}
		{description: The unordered set's element key type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate an unordered set of strings *\/
		Declare_LmiUnorderedSet(LmiString)
		void func() \{
			LmiUnorderedSet(LmiString) strings;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedSet}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiUSet.h}
	{description: 
		An unordered set (a.k.a hash table) is a container that contains a 
		set of elements that can be retrieved in O(Log N) time (on average). 
		No notion of ordering is maintained in.  Each element's key must be 
		unique in the unordered set.
	}
	{template-prototype: LmiUnorderedSet(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedSetHashFunctionType}
	{parent: LmiUnorderedSet}
	{description: The hash function type for unordered set.}
	{template-prototype: LmiUnorderedSetHashFunctionType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type visibility="private":
	{name: LmiUnorderedSetSizeType}
	{parent: LmiUnorderedSet}
	{description: The size type for unordered set.}
	{template-prototype: LmiUnorderedSetSizeType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedSetValueType}
	{parent: LmiUnorderedSet}
	{description: The value type for unordered set.  This is equivalent
	to K_.}
	{template-prototype: LmiUnorderedSetValueType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedSetStatistics}
	{parent: LmiUnorderedSet}
	{description: Describes the statistics of an unordered set.}
	{template-prototype: LmiUnorderedSetStatistics(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiUnorderedSet}
	{parent: LmiUnorderedSet}
	{description: Define a parameterized unordered set container and its subtypes.}
	{prototype: void Define_LmiUnorderedSet(Type K)}
	{parameter: 
		{name: K}
		{description: The unordered set's element key type.}
	}
	{example:
		/\* Instantiate a unordered set of strings container class *\/
		Define_LmiUnorderedSet(LmiString)
		LmiSizeT hf(const LmiString* key) \{
			return (LmiSizeT)LmiStrToInt32(LmiStringCStr(key), NULL, 10);
		\}
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiUnorderedSet(LmiString) numbers;
			LmiInt i;
			LmiUnorderedSetConstruct(LmiString)(&numbers, hf, 10,
			  LmiMallocAllocatorGetDefault(), LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGetDefault());
				LmiUnorderedSetInsert(LmiString)(&numbers, &name);
			\}
			LmiUnorderedSetDestruct(LmiString)(&numbers);
		\}
	}
}
*/	

/**
{function visibility="private":
	{name: LmiUnorderedSetConstruct}
	{parent: LmiUnorderedSet}
	{description: 
		Construct an unordered set.  
	}
	{prototype: LmiUnorderedSet(K_)* LmiUnorderedSetConstruct(K_)(LmiUnorderedSet(K_)* x, LmiUnorderedSetHashFunctionType(K_) hash, LmiUnorderedSetSizeType(K_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: hash}
		{description: The hash function to use.}
	}
	{parameter: 
		{name: buckets}
		{description: A hint to the initial number of buckets that the unordered set should contain.}
	}
	{parameter: 
		{name: bucketAllocator}
		{description: The allocator to use to allocate buckets. }
	}
	{parameter: 
		{name: nodeAllocator}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiUnorderedSetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed unordered set or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetConstructCopy}
	{parent: LmiUnorderedSet}
	{description: Construct an unordered set from another unordered set.}
	{prototype: LmiUnorderedSet(K_)* LmiUnorderedSetConstructCopy(K_)(LmiUnorderedSet(K_)* x, const LmiUnorderedSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: y}
		{description: The unordered set to use to initialize the unordered set being constructed. }
	}
	{return: A pointer to the constructed unordered set or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetDestruct}
	{parent: LmiUnorderedSet}
	{description: Destruct an unordered set.}
	{prototype: void LmiUnorderedSetDestruct(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetAssign}
	{parent: LmiUnorderedSet}
	{description: Copy one unordered set to another unordered set.}
	{prototype: LmiUnorderedSet(K_)* LmiUnorderedSetAssign(K_)(LmiUnorderedSet(K_)* x, const LmiUnorderedSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: y}
		{description: The unordered set to assign from.}
	}
	{return: A pointer to the constructed unordered set or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetSwap}
	{parent: LmiUnorderedSet}
	{description: Swap two unordered sets.}
	{prototype: LmiBool LmiUnorderedSetSwap(K_)(LmiUnorderedSet(K_)* x, LmiUnorderedSet(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: y}
		{description: The other unordered set.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetBegin}
	{parent: LmiUnorderedSet}
	{description: Gets an iterator to the first element in the unordered set.}
	{prototype: LmiUnorderedSetIterator(K_) LmiUnorderedSetBegin(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: An iterator to the first element in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetBeginConst}
	{parent: LmiUnorderedSet}
	{description: Gets a read-only iterator to the first element in the unordered set.}
	{prototype: LmiUnorderedSetConstIterator(K_) LmiUnorderedSetBeginConst(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: A read-only iterator to the first element in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEnd}
	{parent: LmiUnorderedSet}
	{description: Gets an iterator to the element one past the last element in the unordered set.}
	{prototype: LmiUnorderedSetIterator(K_) LmiUnorderedSetEnd(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: An iterator to the element one past the last element in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEndConst}
	{parent: LmiUnorderedSet}
	{description: Gets a read-only iterator to the element one past the last element in the unordered set.}
	{prototype: LmiUnorderedSetConstIterator(K_) LmiUnorderedSetEndConst(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: A read-only iterator to the element one past the last element in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEmpty}
	{parent: LmiUnorderedSet}
	{description: Determines whether the unordered set contains any elements.}
	{prototype: LmiBool LmiUnorderedSetEmpty(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: LMI_TRUE if the unordered set is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetSize}
	{parent: LmiUnorderedSet}
	{description: Gets the number of elements in the unordered set.}
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetSize(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The number of elements in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetMaxSize}
	{parent: LmiUnorderedSet}
	{description: Gets the maximum size that the unordered set can be.}
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetMaxSize(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The maximum number of elements that the unordered set can hold.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetCount}
	{parent: LmiUnorderedSet}
	{description: Gets the number of elements in the unordered set with a given key. }
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetCount(K_)(const LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the unordered set with the specified key.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetClear}
	{parent: LmiUnorderedSet}
	{description: Removes all elements from the unordered set.}
	{prototype: void LmiUnorderedSetClear(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetErase}
	{parent: LmiUnorderedSet}
	{description: Removes the specified element from the unordered set.}
	{prototype: LmiUnorderedSetIterator(K_) LmiUnorderedSetErase(K_)(LmiUnorderedSet(K_)* x, LmiUnorderedSetIterator(K_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEraseRange}
	{parent: LmiUnorderedSet}
	{description: Removes all elements in the specified range from the unordered set.}
	{prototype: LmiUnorderedSetIterator(K_) LmiUnorderedSetEraseRange(K_)(LmiUnorderedSet(K_)* x, LmiUnorderedSetIterator(K_) f, LmiUnorderedSetIterator(K_) l)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEraseKey}
	{parent: LmiUnorderedSet}
	{description: Remove all elements in the unordered set with a specified key.}
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetEraseKey(K_)(LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEqualRange}
	{parent: LmiUnorderedSet}
	{description: Gets a pair of iterators pointing to all elements in the unordered set with the specified key.}
	{prototype: LmiPair(LmiUnorderedSetIterator(K_), LmiUnorderedSetIterator(K_)) LmiUnorderedSetEqualRange(K_)(LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetEqualRangeConst}
	{parent: LmiUnorderedSet}
	{description: Gets a pair of read-only iterators pointing to all elements in the unordered set with the specified key.}
	{prototype: LmiPair(LmiUnorderedSetConstIterator(K_), LmiUnorderedSetConstIterator(K_)) LmiUnorderedSetEqualRangeConst(K_)(const LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetFind}
	{parent: LmiUnorderedSet}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiUnorderedSetIterator(K_) LmiUnorderedSetFind(K_)(LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the unordered set whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetFindConst}
	{parent: LmiUnorderedSet}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiUnorderedSetConstIterator(K_) LmiUnorderedSetFindConst(K_)(const LmiUnorderedSet(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the unordered set whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetInsert}
	{parent: LmiUnorderedSet}
	{description: Inserts an element into the unordered set.}
	{prototype: LmiPair(LmiUnorderedSetIterator(K_), LmiBool) LmiUnorderedSetInsert(K_)(LmiUnorderedSet(K_)* x, const LmiUnorderedSetValueType(K_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: value}
		{description: A element's key.}
	}
	{return: 
		Returns a pair containing an iterator and a boolean.  Upon successful 
		insertion the pair's iterator points to the newly inserted element and 
		the pair's boolean value is set to LMI_TRUE.  If the element is already 
		present in the unordered set, then the pair's iterator points to that 
		element and the pair's boolean value is set to LMI_FALSE.  If any other 
		error (such as memory exhaustion) occurs, the pair's iterator is set to 
		NULL and the pair's boolean value is set to LMI_FALSE.
	}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetHashFunction}
	{parent: LmiUnorderedSet}
	{description: Gets a pointer to the hash function of the unordered set.}
	{prototype: LmiUnorderedSetHashFunctionType(K_) LmiUnorderedSetHashFunction(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The hash function of the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetBucketCount}
	{parent: LmiUnorderedSet}
	{description: Gets the number of buckets in the unordered set.  A bucket
	contains all elements whose keys hash to the same index.}
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetBucketCount(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The number of buckets in the unordered set.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetResize}
	{parent: LmiUnorderedSet}
	{description: Resizes an unordered set.  Resizing changes the number of
	buckets used to store the elements, not the number of elements. Also, the
	number of buckets specified, may not be the actual number of buckets the 
	unordered set resizes uses. The specified size is only a hint to the object.}
	{prototype: LmiBool LmiUnorderedSetResize(K_)(LmiUnorderedSet(K_)* x, LmiUnorderedSetSizeType(K_) n)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: n}
		{description: A hint to the number of buckets to size the unordered set to. }
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetGetNodeSize}
	{parent: LmiUnorderedSet}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiUnorderedSetSizeType(K_) LmiUnorderedSetGetNodeSize(K_)(const LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetGetStatistics}
	{parent: LmiUnorderedSet}
	{description: Gets performance statistics.}
	{prototype: void LmiUnorderedSetGetStatistics(K_)(const LmiUnorderedSet(K_)* x, LmiUnorderedSetStatistics(K_)* stats)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{parameter: 
		{name: stats}
		{description: A point to a statistics object to be filled in. }
	}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetGetBucketAllocator}
	{parent: LmiUnorderedSet}
	{description: Gets a set\'s bucket allocator.}
	{prototype: LmiAllocator* LmiUnorderedSetGetBucketAllocator(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The allocator passed to the set\'s constructor as its bucket allocator.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedSetGetNodeAllocator}
	{parent: LmiUnorderedSet}
	{description: Gets a set\'s node allocator.}
	{prototype: LmiAllocator* LmiUnorderedSetGetNodeAllocator(K_)(LmiUnorderedSet(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered set.}
	}
	{return: The allocator passed to the set\'s constructor as its node allocator.}
	{note: 
		The macro Define_LmiUnorderedSet must be called at global scope before calling 
		any LmiUnorderedSet member functions. 
	}
}
*/
#define LmiUnorderedSet(K_)											LmiTemplate1(LmiUSet, K_)
#define LmiUnorderedSetHashFunctionType(K_)							LmiHashFunctionType(LmiUSet(K_))
#define LmiUnorderedSetSizeType(K_)									LmiSizeType(LmiUSet(K_))
#define LmiUnorderedSetValueType(K_)								LmiValueType(LmiUSet(K_))
#define LmiUnorderedSetConstruct(K_)								LmiConstruct(LmiUSet(K_))
#define LmiUnorderedSetConstructRange(K_)							LmiConstructRange(LmiUSet(K_))
#define LmiUnorderedSetConstructCopy(K_)							LmiConstructCopy(LmiUSet(K_))
#define LmiUnorderedSetDestruct(K_)									LmiDestruct(LmiUSet(K_))
#define LmiUnorderedSetAssign(K_)									LmiAssign(LmiUSet(K_))
#define LmiUnorderedSetSwap(K_)										LmiSwap(LmiUSet(K_))
#define LmiUnorderedSetBegin(K_)									LmiBegin(LmiUSet(K_))
#define LmiUnorderedSetBeginConst(K_)								LmiBeginConst(LmiUSet(K_))
#define LmiUnorderedSetEnd(K_)										LmiEnd(LmiUSet(K_))
#define LmiUnorderedSetEndConst(K_)									LmiEndConst(LmiUSet(K_))
#define LmiUnorderedSetEmpty(K_)									LmiEmpty(LmiUSet(K_))
#define LmiUnorderedSetSize(K_)										LmiSize(LmiUSet(K_))
#define LmiUnorderedSetMaxSize(K_)									LmiMaxSize(LmiUSet(K_))
#define LmiUnorderedSetCount(K_)									LmiCount(LmiUSet(K_))
#define LmiUnorderedSetEqual(K_)									LmiEqual(LmiUSet(K_))
#define LmiUnorderedSetLess(K_)										LmiLess(LmiUSet(K_))
#define LmiUnorderedSetInsert(K_)									LmiInsert(LmiUnorderedSet(K_))
#define LmiUnorderedSetInsertRange(K_)								LmiInsertRange(LmiUSet(K_))
#define LmiUnorderedSetAt(K_)										LmiAt(LmiUSet(K_))
#define LmiUnorderedSetClear(K_)									LmiClear(LmiUSet(K_))
#define LmiUnorderedSetErase(K_)									LmiErase(LmiUSet(K_))
#define LmiUnorderedSetEraseRange(K_)								LmiEraseRange(LmiUSet(K_))
#define LmiUnorderedSetEraseKey(K_)									LmiEraseKey(LmiUSet(K_))
#define LmiUnorderedSetEqualRange(K_)								LmiEqualRange(LmiUSet(K_))
#define LmiUnorderedSetEqualRangeConst(K_)							LmiEqualRangeConst(LmiUSet(K_))
#define LmiUnorderedSetFind(K_)										LmiFind(LmiUSet(K_))
#define LmiUnorderedSetFindConst(K_)								LmiFindConst(LmiUSet(K_))
#define LmiUnorderedSetBucketCount(K_)								LmiBucketCount(LmiUSet(K_))
#define LmiUnorderedSetHashFunction(K_)								LmiHashFunction(LmiUSet(K_))
#define LmiUnorderedSetResize(K_)									LmiResize(LmiUSet(K_))
#define LmiUnorderedSetGetStatistics(K_)							LmiUSetGetStatistics(K_)
#define LmiUnorderedSetGetBucketAllocator(K_)						LmiUSetGetBucketAllocator(K_)
#define LmiUnorderedSetGetNodeAllocator(K_)							LmiUSetGetNodeAllocator(K_)

/* Unordered Set Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedSetIterator}
	{parent: LmiUnorderedSet}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for unordered set.}
	{template-prototype: LmiUnorderedSetIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
#define LmiUnorderedSetIterator(K_)									LmiIterator(LmiUSet(K_))
#define LmiUnorderedSetIteratorConstruct(K_)						LmiConstruct(LmiListIterator(K_))
#define LmiUnorderedSetIteratorDestruct(K_)							LmiDestruct(LmiListIterator(K_))
#define LmiUnorderedSetIteratorConstructCopy(K_)					LmiConstructCopy(LmiListIterator(K_))
#define LmiUnorderedSetIteratorAssign(K_)							LmiAssign(LmiListIterator(K_))
#define LmiUnorderedSetIteratorSwap(K_)								LmiSwap(LmiListIterator(K_))
#define LmiUnorderedSetIteratorEqual(K_)							LmiEqual(LmiListIterator(K_))
#define LmiUnorderedSetIteratorContentOf(K_)						LmiContentOf(LmiListIterator(K_))
#define LmiUnorderedSetIteratorIncrement(K_)						LmiIncrement(LmiListIterator(K_))
#define LmiUnorderedSetIteratorDecrement(K_)						LmiDecrement(LmiListIterator(K_))
#define LmiUnorderedSetIteratorConstructExceptional(K_)				LmiConstructExceptional(LmiListIterator(K_))
#define LmiUnorderedSetIteratorIsExceptional(K_)					LmiIsExceptional(LmiListIterator(K_))
																		
/* Unordered Set Const Iterator */										
/**
{type visibility="private":
	{name: LmiUnorderedSetConstIterator}
	{parent: LmiUnorderedSet}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for unordered set.}
	{template-prototype: LmiUnorderedSetConstIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered set's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedSet must be called before declaring an 
		object of this type.  
	}
}
*/
#define LmiUnorderedSetConstIterator(K_)							LmiConstIterator(LmiUSet(K_))
#define LmiUnorderedSetConstIteratorConstruct(K_)					LmiConstruct(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorDestruct(K_)					LmiDestruct(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorConstructCopy(K_)				LmiConstructCopy(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorAssign(K_)						LmiAssign(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorSwap(K_)						LmiSwap(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorEqual(K_)						LmiEqual(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorContentOf(K_)					LmiContentOf(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorIncrement(K_)					LmiIncrement(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorDecrement(K_)					LmiDecrement(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorConstructExceptional(K_)		LmiConstructExceptional(LmiListConstIterator(K_))
#define LmiUnorderedSetConstIteratorIsExceptional(K_)				LmiIsExceptional(LmiListConstIterator(K_))

#define Declare_LmiUnorderedSet(K_) \
	Declare_LmiUSet(K_) \
	Declare_LmiUniqueAssociativeContainerTypesPart(LmiUnorderedSet(K_)) \
	Declare_LmiUniqueAssociativeContainerFuncsPart(LmiUnorderedSet(K_))

#define Define_LmiUnorderedSetInsert(K_) \
LmiPair(LmiUnorderedSetIterator(K_), LmiBool) LmiUnorderedSetInsert(K_)(LmiUnorderedSet(K_)* x, const LmiUnorderedSetValueType(K_)* value) { \
	LmiPair(LmiUnorderedSetIterator(K_), LmiBool) r; \
	LmiUSetSizeType(K_) i; \
	LmiUSetBucket(K_)* b; \
	LmiListIterator(K_) pos; \
	LmiUSetResize(K_)(x, x->size + 1); \
	b = LmiVectorAt(LmiUSetBucket(K_))(&x->v, x->hash(value) % LmiVectorSize(LmiUSetBucket(K_))(&x->v)); \
	LmiListIteratorConstructCopy(K_)(&pos, &b->first); \
	for (i = 0; i < b->count; ++i) { \
		K_* k; \
		k = LmiListIteratorContentOf(K_)(&pos); \
		if (LmiEqual(K_)(k, value)) { \
			LmiListIteratorAssign(K_)(&r.first, &pos); \
			LmiListIteratorDestruct(K_)(&pos); \
			r.second = LMI_FALSE; \
			return r; \
		} \
		LmiListIteratorIncrement(K_)(&pos); \
	} \
	r.first = LmiListInsert(K_)(&x->l, pos, value); \
	/* If the insert did not fail ... */ \
	if (!LmiListIteratorIsExceptional(K_)(r.first)) { \
		/* If the value was added to the front of the list update the bucket iterator */ \
		if (LmiListIteratorEqual(K_)(&pos, &b->first)) \
			LmiListIteratorAssign(K_)(&b->first, &r.first); \
		++(x->size); \
		++(b->count); \
		r.second = LMI_TRUE; \
	} else { \
		r.second = LMI_FALSE; \
	} \
	LmiListIteratorDestruct(K_)(&pos); \
	return r; \
}

#define Define_LmiUnorderedSet(K_) \
	Define_LmiUSet(K_) \
	Define_LmiUnorderedSetInsert(K_)

/* Unordered Multiset */
/**
{function visibility="private" validate="no":
	{name: Declare_LmiUnorderedMultiset}
	{parent: LmiUnorderedMultiset}
	{description: Declare a parameterized unordered multiset container and its subtypes.}
	{prototype: void Declare_LmiUnorderedMultiset(Type K)}
	{parameter: 
		{name: K}
		{description: The unordered multiset's element key type.}
	}
	{note: Must be called at global scope.}
	{example:
		/\* Instantiate an unordered multiset of strings *\/
		Declare_LmiUnorderedMultiset(LmiString)
		void func() \{
			LmiUnorderedMultiset(LmiString) strings;
		\}
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultiset}
	{parent: AssociativeContainers}
	{include: Lmi/Utils/LmiUSet.h}
	{description: 
		An unordered multiset (a.k.a hash table) is a container that contains a 
		set of elements that can be retrieved in O(Log N) time (on average). 
		No notion of ordering is maintained in.  Multiple elements with the same 
		key may be stored in the unordered multiset.
	}
	{template-prototype: LmiUnorderedMultiset(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultisetHashFunctionType}
	{parent: LmiUnorderedMultiset}
	{description: The hash function type for unordered multiset.}
	{template-prototype: LmiUnorderedMultisetHashFunctionType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultisetSizeType}
	{parent: LmiUnorderedMultiset}
	{description: The size type for unordered multiset.}
	{template-prototype: LmiUnorderedMultisetSizeType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultisetValueType}
	{parent: LmiUnorderedMultiset}
	{description: The value type for unordered multiset.  This is equivalent
	to K_.}
	{template-prototype: LmiUnorderedMultisetValueType(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiUnorderedMultisetStatistics}
	{parent: LmiUnorderedMultiset}
	{description: Describes the statistics of an unordered multiset.}
	{template-prototype: LmiUnorderedMultisetStatistics(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{note: 
		The macro Declare_LmiUnorderedMultiset must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{function visibility="private" validate="no":
	{name: Define_LmiUnorderedMultiset}
	{parent: LmiUnorderedMultiset}
	{description: Define a parameterized unordered multiset container and its subtypes.}
	{prototype: void Define_LmiUnorderedMultiset(Type K)}
	{parameter: 
		{name: K}
		{description: The unordered multiset's element key type.}
	}
	{example:
		/\* Instantiate a unordered multiset of strings container class *\/
		Define_LmiUnorderedMultiset(LmiString)
		LmiSizeT hf(const LmiString* key) \{
			return (LmiSizeT)LmiStrToInt32(LmiStringCStr(key), NULL, 10);
		\}
		void func() \{
			static const char* names[] = \{
			  "zero","one", "two", "three", "four", 
			  "five", "six", "seven", "eight", "nine" 
			\};
			LmiUnorderedMultiset(LmiString) numbers;
			LmiInt i;
			LmiUnorderedMultisetConstruct(LmiString)(&numbers, hf, 10,
			  LmiMallocAllocatorGetDefault(), LmiMallocAllocatorGetDefault());
			for (i = 0; i < 10; ++i) \{
				LmiString name;
				LmiStringConstructCStr(&name, names[i], LmiMallocAllocatorGetDefault());
				LmiUnorderedMultisetInsert(LmiString)(&numbers, &name);
			\}
			LmiUnorderedMultisetDestruct(LmiString)(&numbers);
		\}
	}
}
*/	
/**
{function visibility="private":
	{name: LmiUnorderedMultisetConstruct}
	{parent: LmiUnorderedMultiset}
	{description: 
		Construct an unordered multiset.}
	{prototype: LmiUnorderedMultiset(K_)* LmiUnorderedMultisetConstruct(K_)(LmiUnorderedMultiset(K_)* x, LmiUnorderedMultisetHashFunctionType(K_) hash, LmiUnorderedMultisetSizeType(K_) buckets, LmiAllocator* bucketAllocator, LmiAllocator* nodeAllocator)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: hash}
		{description: The hash function to use.}
	}
	{parameter: 
		{name: buckets}
		{description: A hint to the initial number of buckets that the unordered multiset should contain.}
	}
	{parameter: 
		{name: bucketAllocator}
		{description: The allocator to use to allocate buckets. }
	}
	{parameter: 
		{name: nodeAllocator}
		{description: The allocator to use to allocate elements. The allocator must support allocation of at least LmiUnorderedMultisetGetNodeSize() bytes.}
	}
	{return: A pointer to the constructed unordered multiset or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetConstructCopy}
	{parent: LmiUnorderedMultiset}
	{description: Construct an unordered multiset from another unordered multiset.}
	{prototype: LmiUnorderedMultiset(K_)* LmiUnorderedMultisetConstructCopy(K_)(LmiUnorderedMultiset(K_)* x, const LmiUnorderedMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: y}
		{description: The unordered multiset to use to initialize the unordered multiset being constructed. }
	}
	{return: A pointer to the constructed unordered multiset or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetDestruct}
	{parent: LmiUnorderedMultiset}
	{description: Destruct an unordered multiset.}
	{prototype: void LmiUnorderedMultisetDestruct(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetAssign}
	{parent: LmiUnorderedMultiset}
	{description: Copy one unordered multiset to another unordered multiset.}
	{prototype: LmiUnorderedMultiset(K_)* LmiUnorderedMultisetAssign(K_)(LmiUnorderedMultiset(K_)* x, const LmiUnorderedMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: y}
		{description: The unordered multiset to assign from.}
	}
	{return: A pointer to the constructed unordered multiset or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetSwap}
	{parent: LmiUnorderedMultiset}
	{description: Swap two unordered multisets.}
	{prototype: LmiBool LmiUnorderedMultisetSwap(K_)(LmiUnorderedMultiset(K_)* x, LmiUnorderedMultiset(K_)* y)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: y}
		{description: The other unordered multiset.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetBegin}
	{parent: LmiUnorderedMultiset}
	{description: Gets an iterator to the first element in the unordered multiset.}
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetBegin(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: An iterator to the first element in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetBeginConst}
	{parent: LmiUnorderedMultiset}
	{description: Gets a read-only iterator to the first element in the unordered multiset.}
	{prototype: LmiUnorderedMultisetConstIterator(K_) LmiUnorderedMultisetBeginConst(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: A read-only iterator to the first element in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEnd}
	{parent: LmiUnorderedMultiset}
	{description: Gets an iterator to the element one past the last element in the unordered multiset.}
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetEnd(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: An iterator to the element one past the last element in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEndConst}
	{parent: LmiUnorderedMultiset}
	{description: Gets a read-only iterator to the element one past the last element in the unordered multiset.}
	{prototype: LmiUnorderedMultisetConstIterator(K_) LmiUnorderedMultisetEndConst(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: A read-only iterator to the element one past the last element in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEmpty}
	{parent: LmiUnorderedMultiset}
	{description: Determines whether the unordered multiset contains any elements.}
	{prototype: LmiBool LmiUnorderedMultisetEmpty(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: LMI_TRUE if the unordered multiset is empty or LMI_FALSE if it is not.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetSize}
	{parent: LmiUnorderedMultiset}
	{description: Gets the number of elements in the unordered multiset.}
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetSize(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The number of elements in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetMaxSize}
	{parent: LmiUnorderedMultiset}
	{description: Gets the maximum size that the unordered multiset can be.}
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetMaxSize(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The maximum number of elements that the unordered multiset can hold.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetCount}
	{parent: LmiUnorderedMultiset}
	{description: Gets the number of elements in the unordered multiset with a given key. }
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetCount(K_)(const LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose elements are to be counted.}
	}
	{return: The number of elements in the unordered multiset with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetClear}
	{parent: LmiUnorderedMultiset}
	{description: Removes all elements from the unordered multiset.}
	{prototype: void LmiUnorderedMultisetClear(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetErase}
	{parent: LmiUnorderedMultiset}
	{description: Removes the specified element from the unordered multiset.}
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetErase(K_)(LmiUnorderedMultiset(K_)* x, LmiUnorderedMultisetIterator(K_) pos)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: pos}
		{description: An iterator to the element to erase.}
	}
	{return: An iterator to the element after the erased element.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEraseRange}
	{parent: LmiUnorderedMultiset}
	{description: Removes all elements in the specified range from the unordered multiset.}
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetEraseRange(K_)(LmiUnorderedMultiset(K_)* x, LmiUnorderedMultisetIterator(K_) f, LmiUnorderedMultisetIterator(K_) l)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: f}
		{description: An iterator to the first element to erase.}
	}
	{parameter: 
		{name: l}
		{description: An iterator to one past the last element to erase.}
	}
	{return: An iterator to the element after the erased elements.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEraseKey}
	{parent: LmiUnorderedMultiset}
	{description: Remove all elements in the unordered multiset with a specified key.}
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetEraseKey(K_)(LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key of the elements to erase.}
	}
	{return: The number of elements erased.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEqualRange}
	{parent: LmiUnorderedMultiset}
	{description: Gets a pair of iterators pointing to all elements in the unordered multiset with the specified key.}
	{prototype: LmiPair(LmiUnorderedMultisetIterator(K_), LmiUnorderedMultisetIterator(K_)) LmiUnorderedMultisetEqualRange(K_)(LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetEqualRangeConst}
	{parent: LmiUnorderedMultiset}
	{description: Gets a pair of read-only iterators pointing to all elements in the unordered multiset with the specified key.}
	{prototype: LmiPair(LmiUnorderedMultisetConstIterator(K_), LmiUnorderedMultisetConstIterator(K_)) LmiUnorderedMultisetEqualRangeConst(K_)(const LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key whose range is to be found.}
	}
	{return: A pair of read-only iterators specifying the range of elements with the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetFind}
	{parent: LmiUnorderedMultiset}
	{description: Gets an iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetFind(K_)(LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found. }
	}
	{return: An iterator to the first element in the unordered multiset whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetFindConst}
	{parent: LmiUnorderedMultiset}
	{description: Gets a read-only iterator to the first element with the specified key. }
	{prototype: LmiUnorderedMultisetConstIterator(K_) LmiUnorderedMultisetFindConst(K_)(const LmiUnorderedMultiset(K_)* x, const K_* key)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: key}
		{description: The key to the element to be found.}
	}
	{return: A read-only iterator to the first element in the unordered multiset whose key matches the specified key.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetInsert}
	{parent: LmiUnorderedMultiset}
	{description: Inserts an element into the unordered multiset.}
	{prototype: LmiUnorderedMultisetIterator(K_) LmiUnorderedMultisetInsert(K_)(LmiUnorderedMultiset(K_)* x, const LmiUnorderedMultisetValueType(K_)* value)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: value}
		{description: A pair whose first member is the element's key and the whose second member is the element's value.}
	}
	{return: An iterator to the newly inserted element or NULL on error.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetHashFunction}
	{parent: LmiUnorderedMultiset}
	{description: Gets a pointer to the hash function of the unordered multiset.}
	{prototype: LmiUnorderedMultisetHashFunctionType(K_) LmiUnorderedMultisetHashFunction(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The hash function of the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetBucketCount}
	{parent: LmiUnorderedMultiset}
	{description: Gets the number of buckets in the unordered multiset.  A bucket
	contains all elements whose keys hash to the same index.}
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetBucketCount(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The number of buckets in the unordered multiset.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetResize}
	{parent: LmiUnorderedMultiset}
	{description: Resizes an unordered multiset.  Resizing changes the number of
	buckets used to store the elements, not the number of elements. Also, the
	number of buckets specified, may not be the actual number of buckets the 
	unordered multiset resizes uses. The specified size is only a hint to the object.}
	{prototype: LmiBool LmiUnorderedMultisetResize(K_)(LmiUnorderedMultiset(K_)* x, LmiUnorderedMultisetSizeType(K_) n)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: n}
		{description: A hint to the number of buckets to size the unordered multiset to. }
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetGetNodeSize}
	{parent: LmiUnorderedMultiset}
	{description: Gets the size of the internal node object that contains each stored element in the container.  This
	function is useful for determining the proper block size for block allocators that might be used with this container.}
	{prototype: LmiUnorderedMultisetSizeType(K_) LmiUnorderedMultisetGetNodeSize(K_)(const LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset or NULL.}
	}
	{return: The number of bytes needed to store a node.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetGetStatistics}
	{parent: LmiUnorderedMultiset}
	{description: Gets performance statistics.}
	{prototype: void LmiUnorderedMultisetGetStatistics(K_)(const LmiUnorderedMultiset(K_)* x, LmiUnorderedMultisetStatistics(K_)* stats)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{parameter: 
		{name: stats}
		{description: A point to a statistics object to be filled in. }
	}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetGetBucketAllocator}
	{parent: LmiUnorderedMultiset}
	{description: Gets a multiset\'s bucket allocator.}
	{prototype: LmiAllocator* LmiUnorderedMultisetGetBucketAllocator(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The allocator passed to the multiset\'s constructor as its bucket allocator.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/

/**
{function visibility="private":
	{name: LmiUnorderedMultisetGetNodeAllocator}
	{parent: LmiUnorderedMultiset}
	{description: Gets a multiset\'s node allocator.}
	{prototype: LmiAllocator* LmiUnorderedMultisetGetNodeAllocator(K_)(LmiUnorderedMultiset(K_)* x)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
	{parameter: 
		{name: x}
		{description: The unordered multiset.}
	}
	{return: The allocator passed to the multiset\'s constructor as its node allocator.}
	{note: 
		The macro Define_LmiUnorderedMultiset must be called at global scope before calling 
		any LmiUnorderedMultiset member functions. 
	}
}
*/
#define LmiUnorderedMultiset(K_)									LmiTemplate1(LmiUSet, K_)
#define LmiUnorderedMultisetHashFunctionType(K_)					LmiHashFunctionType(LmiUSet(K_))
#define LmiUnorderedMultisetSizeType(K_)							LmiSizeType(LmiUSet(K_))
#define LmiUnorderedMultisetValueType(K_)							LmiValueType(LmiUSet(K_))
#define LmiUnorderedMultisetConstruct(K_)							LmiConstruct(LmiUSet(K_))
#define LmiUnorderedMultisetConstructRange(K_)						LmiConstructRange(LmiUSet(K_))
#define LmiUnorderedMultisetConstructCopy(K_)						LmiConstructCopy(LmiUSet(K_))
#define LmiUnorderedMultisetDestruct(K_)							LmiDestruct(LmiUSet(K_))
#define LmiUnorderedMultisetAssign(K_)								LmiAssign(LmiUSet(K_))
#define LmiUnorderedMultisetSwap(K_)								LmiSwap(LmiUSet(K_))
#define LmiUnorderedMultisetBegin(K_)								LmiBegin(LmiUSet(K_))
#define LmiUnorderedMultisetBeginConst(K_)							LmiBeginConst(LmiUSet(K_))
#define LmiUnorderedMultisetEnd(K_)									LmiEnd(LmiUSet(K_))
#define LmiUnorderedMultisetEndConst(K_)							LmiEndConst(LmiUSet(K_))
#define LmiUnorderedMultisetEmpty(K_)								LmiEmpty(LmiUSet(K_))
#define LmiUnorderedMultisetSize(K_)								LmiSize(LmiUSet(K_))
#define LmiUnorderedMultisetMaxSize(K_)								LmiMaxSize(LmiUSet(K_))
#define LmiUnorderedMultisetCount(K_)								LmiCount(LmiUSet(K_))
#define LmiUnorderedMultisetEqual(K_)								LmiEqual(LmiUSet(K_))
#define LmiUnorderedMultisetLess(K_)								LmiLess(LmiUSet(K_))
#define LmiUnorderedMultisetInsert(K_)								LmiUSetInsert_(K_)
#define LmiUnorderedMultisetInsertRange(K_)							LmiInsertRange(LmiUSet(K_))
#define LmiUnorderedMultisetClear(K_)								LmiClear(LmiUSet(K_))
#define LmiUnorderedMultisetErase(K_)								LmiErase(LmiUSet(K_))
#define LmiUnorderedMultisetEraseRange(K_)							LmiEraseRange(LmiUSet(K_))
#define LmiUnorderedMultisetEraseKey(K_)							LmiEraseKey(LmiUSet(K_))
#define LmiUnorderedMultisetEqualRange(K_)							LmiEqualRange(LmiUSet(K_))
#define LmiUnorderedMultisetEqualRangeConst(K_)						LmiEqualRangeConst(LmiUSet(K_))
#define LmiUnorderedMultisetFind(K_)								LmiFind(LmiUSet(K_))
#define LmiUnorderedMultisetFindConst(K_)							LmiFindConst(LmiUSet(K_))
#define LmiUnorderedMultisetBucketCount(K_)							LmiBucketCount(LmiUSet(K_))
#define LmiUnorderedMultisetHashFunction(K_)						LmiHashFunction(LmiUSet(K_))
#define LmiUnorderedMultisetResize(K_)								LmiResize(LmiUSet(K_))
#define LmiUnorderedMultisetGetStatistics(K_)						LmiUSetGetStatistics(K_)
#define LmiUnorderedMultisetGetBucketAllocator(K_)					LmiUSetGetBucketAllocator(K_)
#define LmiUnorderedMultisetGetNodeAllocator(K_)					LmiUSetGetNodeAllocator(K_)

/* Unordered Multiset Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedMultisetIterator}
	{parent: LmiUnorderedMultiset}
	{model-of: LmiBidirectionalIterator}
	{description: The iterator type for unordered multiset.}
	{template-prototype: LmiUnorderedMultisetIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
}
*/
#define LmiUnorderedMultisetIterator(K_)							LmiIterator(LmiUSet(K_))
#define LmiUnorderedMultisetIteratorConstruct(K_)					LmiConstruct(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorDestruct(K_)					LmiDestruct(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorConstructCopy(K_)				LmiConstructCopy(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorAssign(K_)						LmiAssign(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorSwap(K_)						LmiSwap(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorEqual(K_)						LmiEqual(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorContentOf(K_)					LmiContentOf(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorIncrement(K_)					LmiIncrement(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorDecrement(K_)					LmiDecrement(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorConstructExceptional(K_)		LmiConstructExceptional(LmiListIterator(K_))
#define LmiUnorderedMultisetIteratorIsExceptional(K_)				LmiIsExceptional(LmiListIterator(K_))

/* Unordered Multiset Const Iterator */
/**
{type visibility="private":
	{name: LmiUnorderedMultisetConstIterator}
	{parent: LmiUnorderedMultiset}
	{model-of: LmiBidirectionalIterator}
	{description: The read-only iterator type for unordered multiset.}
	{template-prototype: LmiUnorderedMultisetConstIterator(K_)}
	{template-parameter: 
		{name: K_}
		{description: The unordered multiset's element key type.}
	}
}
*/
#define LmiUnorderedMultisetConstIterator(K_)						LmiConstIterator(LmiUSet(K_))
#define LmiUnorderedMultisetConstIteratorConstruct(K_)				LmiConstruct(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorDestruct(K_)				LmiDestruct(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorConstructCopy(K_)			LmiConstructCopy(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorAssign(K_)					LmiAssign(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorSwap(K_)					LmiSwap(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorEqual(K_)					LmiEqual(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorContentOf(K_)				LmiContentOf(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorIncrement(K_)				LmiIncrement(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorDecrement(K_)				LmiDecrement(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorConstructExceptional(K_)	LmiConstructExceptional(LmiListConstIterator(K_))
#define LmiUnorderedMultisetConstIteratorIsExceptional(K_)			LmiIsExceptional(LmiListConstIterator(K_))

#define Declare_LmiUnorderedMultiset(K_) \
	Declare_LmiUSet(K_) \
	Declare_LmiMultipleAssociativeContainerTypesPart(LmiUSet(K_)) \
	Declare_LmiMultipleAssociativeContainerFuncsPart(LmiUSet(K_))

#define Define_LmiUnorderedMultiset(K_) \
	Define_LmiUSet(K_)

LMI_END_EXTERN_C

#endif /* LMI_UNORDERED_H_ */

