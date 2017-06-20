/** {file:
      {name: LmiHeap.h}
      {description: Functionality to support Heap.}
      {copyright:
      	(c) 2005-2015 Vidyo, Inc.,
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
#if !defined(LMI_HEAP_H_)
#define LMI_HEAP_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiContainers.h>
#include <Lmi/Utils/LmiIterators.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>

#include <Lmi/Utils/LmiVector.h>

LMI_BEGIN_EXTERN_C

/* Name mangling */
#define LmiHeap(T_)									LmiTemplate1(LmiHeap, T_)
#define LmiHeapConstructDefault(T_)					LmiClassFunc(LmiHeap(T_), ConstructDefault)
#define LmiHeapConstructN(T_)						LmiClassFunc(LmiHeap(T_), ConstructN)
#define LmiHeapDestruct(T_)							LmiClassFunc(LmiHeap(T_), Destruct)
#define LmiHeapSize(T_)								LmiClassFunc(LmiHeap(T_), Size)
#define LmiHeapEmpty(T_)							LmiClassFunc(LmiHeap(T_), Empty)
#define LmiHeapRemoveAt(T_)							LmiClassFunc(LmiHeap(T_), RemoveAt)
#define LmiHeapAt(T_)								LmiClassFunc(LmiHeap(T_), At)
#define LmiHeapPush(T_)								LmiClassFunc(LmiHeap(T_), Push)
#define LmiHeapPop(T_)								LmiClassFunc(LmiHeap(T_), Pop)
#define LmiHeapValidate(T_)							LmiClassFunc(LmiHeap(T_), Validate)

#define LmiHeapDump(T_)								LmiClassFunc(LmiHeap(T_), Dump)


/***** Declarations *****/

#define Declare_LmiHeapPop(T_) \
	void LmiHeapPop(T_)(LmiHeap(T_)* x);

#define Declare_LmiHeapPush(T_) \
	void LmiHeapPush(T_)(LmiHeap(T_)* x, T_ * t);

#define Declare_LmiHeapRemoveAt(T_) \
	void LmiHeapRemoveAt(T_)(LmiHeap(T_)* x, LmiSizeT pos);

#define Declare_LmiHeapAt(T_) \
	T_* LmiHeapAt(T_)(LmiHeap(T_)* x, LmiSizeT pos);

#define Declare_LmiHeapConstructDefault(T_) \
	LmiHeap(T_)* LmiHeapConstructDefault(T_)(LmiHeap(T_)* x, LmiAllocator* a);

#define Declare_LmiHeapConstructN(T_) \
	LmiHeap(T_)* LmiHeapConstructN(T_)(LmiHeap(T_)* x, LmiSizeT n, LmiAllocator* a);

#define Declare_LmiHeapDestruct(T_) \
	void LmiHeapDestruct(T_)(LmiHeap(T_)* x);

#define Declare_LmiHeapSize(T_) \
	LmiSizeT LmiHeapSize(T_)(const LmiHeap(T_)* x);

#define Declare_LmiHeapEmpty(T_) \
	LmiBool LmiHeapEmpty(T_)(const LmiHeap(T_)* x);

#define Declare_LmiHeapValidate(T_) \
		LmiBool LmiHeapValidate(T_)(const LmiHeap(T_) *x, LmiSizeT start_index);

#define Declare_LmiHeapDump(T_) \
	void LmiHeapDump(T_)(LmiHeap(T_) *x);


/* Heap Template */
#define Declare_LmiHeap(T_) \
	Declare_LmiVector(T_) \
	typedef struct { \
		LmiVector(T_) v; \
	} LmiHeap(T_); \
	Declare_LmiHeapPop(T_) \
	Declare_LmiHeapPush(T_) \
	Declare_LmiHeapConstructDefault(T_) \
	Declare_LmiHeapConstructN(T_) \
	Declare_LmiHeapDestruct(T_) \
	Declare_LmiHeapSize(T_) \
	Declare_LmiHeapEmpty(T_) \
	Declare_LmiHeapValidate(T_) \
	Declare_LmiHeapDump(T_) \
	Declare_LmiHeapRemoveAt(T_) \
	Declare_LmiHeapAt(T_)


/****** Definitions ******/
#define Define_LmiHeapDump(T_) \
	void LmiHeapDump(T_)(LmiHeap(T_) *x) { \
	LmiSizeT i; \
	for (i = 0; i < LmiVectorSize(T_)(&x->v); i++) \
		LmiDump(T_)(LmiVectorAt(T_)(&x->v, i)); \
	return; \
	}

#define Define_LmiHeapDestruct(T_) \
	void LmiHeapDestruct(T_)(LmiHeap(T_)* x) { \
		LmiVectorDestruct(T_)(&x->v); \
		return; \
	}

#define Define_LmiHeapConstructDefault(T_) \
	LmiHeap(T_)* LmiHeapConstructDefault(T_)(LmiHeap(T_)* x, LmiAllocator* a) { \
		LmiVectorConstructDefault(T_)(&x->v, a); \
		return x; \
	}

#define Define_LmiHeapConstructN(T_) \
	LmiHeap(T_)* LmiHeapConstructN(T_)(LmiHeap(T_)* x, LmiSizeT n, LmiAllocator* a) { \
		LmiVectorConstructDefault(T_)(&x->v, a); \
		LmiVectorReserve(T_)(&x->v, n); \
		return x; \
	}
#define Define_LmiHeapSize(T_) \
	LmiSizeT LmiSize(LmiHeap(T_))(const LmiHeap(T_)* x) { return LmiVectorSize(T_)(&x->v); }

#define Define_LmiHeapEmpty(T_) \
	LmiBool LmiEmpty(LmiHeap(T_))(const LmiHeap(T_)* x) { return LmiVectorEmpty(T_)(&x->v); }

#define Define_LmiHeapAt(T_) \
	T_* LmiHeapAt(T_)(LmiHeap(T_)* x, LmiSizeT pos) { \
		if (pos < LmiVectorSize(T_)(&x->v)) return LmiVectorAt(T_)(&x->v, pos); \
		else return NULL; \
	}

#define Define_LmiHeapPop(T_) \
	void LmiHeapPop(T_)(LmiHeap(T_)* x) { LmiHeapRemoveAt(T_)(x, 0); }

#define Define_LmiHeapPush(T_) \
	void LmiHeapPush(T_)(LmiHeap(T_) *x, T_* t) { \
		LmiSizeT child, parent; \
		LmiVectorPushBack(T_)(&x->v, t); \
		child = LmiVectorSize(T_)(&x->v); \
		parent = child / 2; \
		while (parent >= 1) \
		{ \
			if (LmiLess(T_)(LmiVectorAt(T_)(&x->v, child-1), LmiVectorAt(T_)(&x->v, parent-1))) \
			{ \
				LmiSwap(T_)(LmiVectorAt(T_)(&x->v, child-1), LmiVectorAt(T_)(&x->v, parent-1)); \
				child = parent; \
				parent = parent / 2; \
			} \
			else \
				parent = 0; \
		} \
		return; \
	}

#define Define_LmiHeapRemoveAt(T_) \
	void LmiHeapRemoveAt(T_)(LmiHeap(T_) *x, LmiSizeT pos) { \
		LmiSizeT child, parent; \
		/* Range check... */ \
		if(pos >= LmiVectorSize(T_)(&x->v)) \
			return; \
		/* Retrieve the item to be removed */ \
		/* If the item to be removed is the last item in the heap */ \
		if ((pos + 1) == LmiVectorSize(T_)(&x->v)) \
		{ \
			LmiVectorPopBack(T_)(&x->v); \
		} else { \
			LmiSwap(T_)(LmiVectorAt(T_)(&x->v, pos), LmiVectorAt(T_)(&x->v, LmiVectorSize(T_)(&x->v) - 1)); \
			LmiVectorPopBack(T_)(&x->v); \
			/* Rebalance the tree */ \
			while ((pos+1) > 1) \
			{ \
				LmiSizeT parentEntryIndex = (pos - 1) / 2;\
				LmiSwap(T_)(LmiVectorAt(T_)(&x->v, pos), LmiVectorAt(T_)(&x->v, parentEntryIndex)); \
				pos = parentEntryIndex; \
			} \
			parent = 1; \
			child = 2; \
			while (child <= LmiVectorSize(T_)(&x->v)) \
			{ \
				if ((child+1) <= LmiVectorSize(T_)(&x->v)) \
				{ \
					if (LmiLess(T_)(LmiVectorAt(T_)(&x->v, child), LmiVectorAt(T_)(&x->v, child - 1))) \
						child++; \
				} \
				if (!LmiLess(T_)(LmiVectorAt(T_)(&x->v, parent - 1), LmiVectorAt(T_)(&x->v, child - 1))) \
				{ \
					LmiSwap(T_)(LmiVectorAt(T_)(&x->v, child - 1), LmiVectorAt(T_)(&x->v, parent - 1)); \
					parent = child; \
				} \
				child = 2 * child; \
			} \
		} \
		return; \
	}

#define Define_LmiHeapValidate(T_) \
	LmiBool LmiHeapValidate(T_)(const LmiHeap(T_) *x, LmiSizeT startIndex) { \
	LmiBool leftSubtree; \
	LmiBool rightSubtree; \
	leftSubtree = rightSubtree = LMI_TRUE; \
	if ((2 * startIndex) <= LmiVectorSize(T_)(&x->v)) \
	{ \
		if (!LmiLess(T_)(LmiVectorAtConst(T_)(&x->v, (2 * startIndex)-1), LmiVectorAtConst(T_)(&x->v, (startIndex-1)))) \
			leftSubtree = LmiHeapValidate(T_)(x, (2 * startIndex)); \
		else \
			leftSubtree = LMI_FALSE; \
	} \
	if (((2 * startIndex) + 1) <= LmiVectorSize(T_)(&x->v)) \
	{ \
		if (!LmiLess(T_)(LmiVectorAtConst(T_)(&x->v, (2 * startIndex)), LmiVectorAtConst(T_)(&x->v, (startIndex - 1)))) \
			rightSubtree = LmiHeapValidate(T_)(x, (2 * startIndex)); \
		else \
			rightSubtree = LMI_FALSE; \
	} \
	return leftSubtree && rightSubtree; \
}

#define Define_LmiHeap(T_) \
	Define_LmiVector(T_) \
	Define_LmiHeapPop(T_) \
	Define_LmiHeapPush(T_) \
	Define_LmiHeapConstructDefault(T_) \
	Define_LmiHeapConstructN(T_) \
	Define_LmiHeapDestruct(T_) \
	Define_LmiHeapSize(T_) \
	Define_LmiHeapEmpty(T_) \
	Define_LmiHeapValidate(T_) \
	Define_LmiHeapDump(T_) \
	Define_LmiHeapRemoveAt(T_) \
	Define_LmiHeapAt(T_)

LMI_END_EXTERN_C

#endif
