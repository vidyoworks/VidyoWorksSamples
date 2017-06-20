/**
{file: 
	{name: LmiDeque.h}
	{description: Double-ended queue. Supports efficient inserts and
		removes at beginning and end of sequence.}
	{copyright:
		(c) 2007-2013 Vidyo, Inc.,
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
#ifndef LMI_DEQUE_H
#define LMI_DEQUE_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

/* Name mangling */
#define LmiDeque(T_)              LmiTemplate1(LmiDeque, T_)
#define LmiDequeConstruct(T_)     LmiClassFunc(LmiDeque(T_), Construct)
#define LmiDequeConstructCopy(T_) LmiClassFunc(LmiDeque(T_), ConstructCopy)
#define LmiDequeDestruct(T_)      LmiClassFunc(LmiDeque(T_), Destruct)
#define LmiDequeFront(T_)         LmiClassFunc(LmiDeque(T_), Front)
#define LmiDequeFrontConst(T_)    LmiClassFunc(LmiDeque(T_), FrontConst)
#define LmiDequeBack(T_)          LmiClassFunc(LmiDeque(T_), Back)
#define LmiDequeBackConst(T_)     LmiClassFunc(LmiDeque(T_), BackConst)
#define LmiDequeAt(T_)            LmiClassFunc(LmiDeque(T_), At)
#define LmiDequeAtConst(T_)       LmiClassFunc(LmiDeque(T_), AtConst)
#define LmiDequeRealloc_(T_)      LmiClassFunc(LmiDeque(T_), Realloc_)
#define LmiDequeGrowIfFull_(T_)   LmiClassFunc(LmiDeque(T_), GrowIfFull_)
#define LmiDequePushFront(T_)     LmiClassFunc(LmiDeque(T_), PushFront)
#define LmiDequePushBack(T_)      LmiClassFunc(LmiDeque(T_), PushBack)
#define LmiDequePopFront(T_)      LmiClassFunc(LmiDeque(T_), PopFront)
#define LmiDequePopBack(T_)       LmiClassFunc(LmiDeque(T_), PopBack)
#define LmiDequeSize(T_)          LmiClassFunc(LmiDeque(T_), Size)
#define LmiDequeCapacity(T_)      LmiClassFunc(LmiDeque(T_), Capacity)
#define LmiDequeReserve(T_)       LmiClassFunc(LmiDeque(T_), Reserve)
#define LmiDequeEmpty(T_)         LmiClassFunc(LmiDeque(T_), Empty)
#define LmiDequeClear(T_)         LmiClassFunc(LmiDeque(T_), Clear)

#define Define_LmiDequeConstruct(T_, INLINE_) \
	INLINE_ LmiDeque(T_) *LmiDequeConstruct(T_)(LmiDeque(T_) *q, LmiAllocator *alloc) \
	{ \
		q->data = q->dataEnd = q->begin = q->end = NULL; \
		q->alloc = alloc; \
		return q; \
	}

#define Define_LmiDequeConstructCopy(T_) \
	LmiDeque(T_) *LmiDequeConstructCopy(T_)(LmiDeque(T_) *d, const LmiDeque(T_) *s) \
	{ \
		LmiSizeT i, n = LmiDequeSize(T_)(s); \
		d->alloc = s->alloc; \
		if(n == 0) \
		{ \
			d->data = d->dataEnd = d->begin = d->end = NULL; \
			return d; \
		} \
		d->begin = d->data = (T_ *)LmiAllocatorAllocate(d->alloc, (n + 1) * sizeof(T_)); \
		d->end = d->begin + n; \
		d->dataEnd = d->end + 1; \
		for(i=0; i<n; ++i) \
		{ \
			if(LmiConstructCopy(T_)(d->data + i, LmiDequeAtConst(T_)(s, i)) == NULL) \
			{ \
				while(i > 0) \
				{ \
					--i; \
					LmiDestruct(T_)(d->data + i); \
				} \
				return NULL; \
			} \
		} \
		return d; \
	}

#define Define_LmiDequeDestruct(T_, INLINE_) \
	INLINE_ void LmiDequeDestruct(T_)(LmiDeque(T_) *q) \
	{ \
		if(q->data != NULL) \
		{ \
			while(!LmiDequeEmpty(T_)(q)) \
				LmiDequePopFront(T_)(q); \
			\
			LmiAllocatorDeallocate(q->alloc, q->data, (q->dataEnd - q->data) * sizeof(T_)); \
		} \
	}

#define Define_LmiDequeFront(T_, INLINE_) \
	INLINE_ T_ *LmiDequeFront(T_)(LmiDeque(T_) *q) \
	{ \
		return q->begin; \
	}

#define Define_LmiDequeFrontConst(T_, INLINE_) \
	INLINE_ const T_ *LmiDequeFrontConst(T_)(const LmiDeque(T_) *q) \
	{ \
		return q->begin; \
	}

#define Define_LmiDequeBack(T_, INLINE_) \
	INLINE_ T_ *LmiDequeBack(T_)(LmiDeque(T_) *q) \
	{ \
		return (q->end == q->data) ? (q->dataEnd - 1) : (q->end - 1); \
	}

#define Define_LmiDequeBackConst(T_, INLINE_) \
	INLINE_ const T_ *LmiDequeBackConst(T_)(const LmiDeque(T_) *q) \
	{ \
		return (q->end == q->data) ? (q->dataEnd - 1) : (q->end - 1); \
	}

#define Define_LmiDequeAt(T_, INLINE_) \
	INLINE_ T_ *LmiDequeAt(T_)(LmiDeque(T_) *q, LmiSizeT i) \
	{ \
		LmiSizeT r = q->dataEnd - q->begin; \
		return (i < r) ? &q->begin[i] : &q->data[i - r]; \
	}

#define Define_LmiDequeAtConst(T_, INLINE_) \
	INLINE_ const T_ *LmiDequeAtConst(T_)(const LmiDeque(T_) *q, LmiSizeT i) \
	{ \
		LmiSizeT r = q->dataEnd - q->begin; \
		return (i < r) ? &q->begin[i] : &q->data[i - r]; \
	}

#define Define_LmiDequeRealloc_(T_) \
	LmiBool LmiDequeRealloc_(T_)(LmiDeque(T_) *q, LmiSizeT newCapacity) \
	{ \
		if(q->data == NULL) \
		{ \
			q->begin = q->end = q->data = \
				(T_ *)LmiAllocatorAllocate(q->alloc, newCapacity * sizeof(T_)); \
			if (q->data == NULL) \
				return LMI_FALSE; \
			q->dataEnd = q->data + newCapacity; \
		} \
		else \
		{ \
			T_ *newData = (T_ *)LmiAllocatorAllocate(q->alloc, newCapacity * sizeof(T_)); \
			T_ *wp = newData, *rp = q->begin; \
			if (newData == NULL) \
				return LMI_FALSE; \
			\
			while(rp != q->end) \
			{ \
				if (LmiConstructCopy(T_)(wp, rp) == NULL) { \
					T_* dp = newData; \
					while (dp != wp) { \
						LmiDestruct(T_)(dp); \
					} \
					return LMI_FALSE; \
				} \
				wp++; \
			\
				if(++rp == q->dataEnd) \
					rp = q->data; \
			} \
			rp = q->begin; \
			while(rp != q->end) \
			{ \
				LmiDestruct(T_)(rp); \
				\
				if(++rp == q->dataEnd) \
					rp = q->data; \
			} \
			\
			LmiAllocatorDeallocate(q->alloc, q->data, \
				(q->dataEnd - q->data) * sizeof(T_)); \
			\
			q->data = q->begin = newData; \
			q->end = wp; \
			q->dataEnd = newData + newCapacity; \
		} \
		return LMI_TRUE; \
	}


#define Define_LmiDequeGrowIfFull_(T_, INLINE_) \
	INLINE_ LmiBool LmiDequeGrowIfFull_(T_)(LmiDeque(T_) *q) \
	{ \
		LmiSizeT newCapacity; \
		if(q->data == NULL) \
		{ \
			newCapacity = 32; \
		} \
		else { \
			T_ *next = q->end + 1; \
			if(!(next == q->begin || (next == q->dataEnd && q->begin == q->data))) \
				return LMI_TRUE; \
			newCapacity = (q->dataEnd - q->data) * 2; \
		} \
		return LmiDequeRealloc_(T_)(q, newCapacity); \
	}

#define Define_LmiDequePushFront(T_, INLINE_) \
	INLINE_ LmiBool LmiDequePushFront(T_)(LmiDeque(T_) *q, const T_ *val) \
	{ \
		if (!LmiDequeGrowIfFull_(T_)(q)) \
			return LMI_FALSE; \
		if(q->begin == q->data) \
			q->begin = q->dataEnd; \
		--q->begin; \
		if (LmiConstructCopy(T_)(q->begin, val) == NULL) { \
			++q->begin; \
			if(q->begin == q->dataEnd) \
				q->begin = q->data; \
			return LMI_FALSE; \
		} \
		return LMI_TRUE; \
	}

#define Define_LmiDequePushBack(T_, INLINE_) \
	INLINE_ LmiBool LmiDequePushBack(T_)(LmiDeque(T_) *q, const T_ *val) \
	{ \
		if (!LmiDequeGrowIfFull_(T_)(q)) \
			return LMI_FALSE; \
		if (LmiConstructCopy(T_)(q->end, val) == NULL) \
			return LMI_FALSE; \
		if(++q->end == q->dataEnd) \
			q->end = q->data; \
		return LMI_TRUE; \
	}

#define Define_LmiDequePopFront(T_, INLINE_) \
	INLINE_ void LmiDequePopFront(T_)(LmiDeque(T_) *q) \
	{ \
		LmiDestruct(T_)(q->begin); \
		\
		if(++q->begin == q->dataEnd) \
			q->begin = q->data; \
	}

#define Define_LmiDequePopBack(T_, INLINE_) \
	INLINE_ void LmiDequePopBack(T_)(LmiDeque(T_) *q) \
	{ \
		if(q->end == q->data) \
			q->end = q->dataEnd; \
		--q->end; \
		\
		LmiDestruct(T_)(q->end); \
	}

#define Define_LmiDequeSize(T_, INLINE_) \
	INLINE_ LmiSizeT LmiDequeSize(T_)(const LmiDeque(T_) *q) \
	{ \
		LmiInt s = (LmiInt)(q->end - q->begin); \
		return (s >= 0) ? s : (q->dataEnd - q->data + s); \
	}

#define Define_LmiDequeCapacity(T_, INLINE_) \
	INLINE_ LmiSizeT LmiDequeCapacity(T_)(const LmiDeque(T_) *q) \
	{ \
		return (q->dataEnd - q->data); \
	}

#define Define_LmiDequeReserve(T_, INLINE_) \
	INLINE_ LmiBool LmiDequeReserve(T_)(LmiDeque(T_) *q, LmiSizeT newCapacity) \
	{ \
		if (newCapacity <= LmiDequeCapacity(T_)(q)) \
			return LMI_TRUE; \
		return LmiDequeRealloc_(T_)(q, newCapacity); \
	}

#define Define_LmiDequeEmpty(T_, INLINE_) \
	INLINE_ LmiBool LmiDequeEmpty(T_)(const LmiDeque(T_) *q) \
	{ \
		return q->begin == q->end; \
	}

#define Define_LmiDequeClear(T_, INLINE_) \
	INLINE_ void LmiDequeClear(T_)(LmiDeque(T_) *q) \
	{ \
		if(q->data != NULL) \
		{ \
			while(!LmiDequeEmpty(T_)(q)) \
				LmiDequePopFront(T_)(q); \
		} \
	}

#define DefineInline_LmiDeque(T_, INLINE_) \
	Define_LmiDequeFront(T_, INLINE_) \
	Define_LmiDequeFrontConst(T_, INLINE_) \
	Define_LmiDequeBack(T_, INLINE_) \
	Define_LmiDequeBackConst(T_, INLINE_) \
	Define_LmiDequeAt(T_, INLINE_) \
	Define_LmiDequeAtConst(T_, INLINE_) \
	Define_LmiDequeGrowIfFull_(T_, INLINE_) \
	Define_LmiDequePushFront(T_, INLINE_) \
	Define_LmiDequePushBack(T_, INLINE_) \
	Define_LmiDequePopFront(T_, INLINE_) \
	Define_LmiDequePopBack(T_, INLINE_) \
	Define_LmiDequeSize(T_, INLINE_) \
	Define_LmiDequeCapacity(T_, INLINE_) \
	Define_LmiDequeReserve(T_, INLINE_) \
	Define_LmiDequeEmpty(T_, INLINE_) \
	Define_LmiDequeClear(T_, INLINE_) \
	Define_LmiDequeConstruct(T_, INLINE_) \
	Define_LmiDequeDestruct(T_, INLINE_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#define DefineInlineHeader_LmiDeque(T_) DefineInline_LmiDeque(T_, LMI_INLINE)
#else
#define DefineInlineHeader_LmiDeque(T_)
#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS
#define DefineInlineSource_LmiDeque(T_) DefineInline_LmiDeque(T_, LMI_INLINE_SOURCE_FILE)
#else
#define DefineInlineSource_LmiDeque(T_)
#endif

#define Declare_LmiDeque(T_) \
	typedef struct \
	{ \
		T_ *data; \
		T_ *dataEnd; \
		T_ *begin; \
		T_ *end; \
		LmiAllocator *alloc; \
	} LmiDeque(T_); \
	LMI_INLINE_DECLARATION LmiDeque(T_) *LmiDequeConstruct(T_)(LmiDeque(T_) *q, LmiAllocator *alloc); \
	LmiDeque(T_) *LmiDequeConstructCopy(T_)(LmiDeque(T_) *d, const LmiDeque(T_) *s); \
	LMI_INLINE_DECLARATION void LmiDequeDestruct(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION T_ *LmiDequeFront(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION const T_ *LmiDequeFrontConst(T_)(const LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION T_ *LmiDequeBack(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION const T_ *LmiDequeBackConst(T_)(const LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION T_ *LmiDequeAt(T_)(LmiDeque(T_) *q, LmiSizeT i); \
	LMI_INLINE_DECLARATION const T_ *LmiDequeAtConst(T_)(const LmiDeque(T_) *q, LmiSizeT i); \
	LmiBool LmiDequeRealloc_(T_)(LmiDeque(T_) *q, LmiSizeT newCapacity); \
	LMI_INLINE_DECLARATION LmiBool LmiDequeGrowIfFull_(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION LmiBool LmiDequePushFront(T_)(LmiDeque(T_) *q, const T_ *val); \
	LMI_INLINE_DECLARATION LmiBool LmiDequePushBack(T_)(LmiDeque(T_) *q, const T_ *val); \
	LMI_INLINE_DECLARATION void LmiDequePopFront(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION void LmiDequePopBack(T_)(LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION LmiSizeT LmiDequeSize(T_)(const LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION LmiSizeT LmiDequeCapacity(T_)(const LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION LmiBool LmiDequeReserve(T_)(LmiDeque(T_) *q, LmiSizeT newCapacity); \
	LMI_INLINE_DECLARATION LmiBool LmiDequeEmpty(T_)(const LmiDeque(T_) *q); \
	LMI_INLINE_DECLARATION void LmiDequeClear(T_)(LmiDeque(T_) *q); \
	DefineInlineHeader_LmiDeque(T_)

#define Define_LmiDeque(T_) \
	DefineInlineSource_LmiDeque(T_) \
	Define_LmiDequeConstructCopy(T_) \
	Define_LmiDequeRealloc_(T_)

LMI_END_EXTERN_C

#endif
