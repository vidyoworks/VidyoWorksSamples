/** 
{file:
	{name: LmiContainers.h}
	{description: Container Concepts (in the STL sense) for classes.}
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

#ifndef LMI_CONTAINERS_H_
#define LMI_CONTAINERS_H_

#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiIterators.h>
#include <Lmi/Utils/LmiUtility.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiAllocator.h>

/**
{package:
	{name: Containers}
	{parent: Utils}
	{description: A package of basic parameterized container classes. }
}
*/

/* X_ = Model */
/* T_ Value Type */
/* I_ Iterator Type */
/* CI_ = ConstIterator Type */
/* S_ Size Type */
/* D_ Difference Type */

/* Container concept */
#define Declare_LmiContainerTypesPart(X_, T_, I_, CI_, S_, D_) \
	typedef T_ LmiValueType(X_); \
	typedef I_ LmiIterator(X_); \
	typedef CI_ LmiConstIterator(X_); \
	typedef S_ LmiSizeType(X_); \
	typedef D_ LmiDifferenceType(X_);
#define Declare_LmiContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiContainerTypesPart(X_, T_, I_, CI_, S_, D_)
#define DeclareInline_LmiContainerFuncsPart(X_, INLINE_) \
	INLINE_ LmiIterator(X_) LmiBegin(X_)(X_* x); \
	INLINE_ LmiConstIterator(X_) LmiBeginConst(X_)(const X_* x); \
	INLINE_ LmiIterator(X_) LmiEnd(X_)(X_* x); \
	INLINE_ LmiConstIterator(X_) LmiEndConst(X_)(const X_* x); \
	INLINE_ LmiSizeType(X_) LmiSize(X_)(const X_* x); \
	INLINE_ LmiSizeType(X_) LmiMaxSize(X_)(const X_* x); \
	INLINE_ LmiBool LmiEmpty(X_)(const X_* x);
#define DeclareInline_LmiContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiAssignable(X_, INLINE_)			 \
	DeclareInline_LmiContainerFuncsPart(X_, INLINE_)
#define Declare_LmiContainerFuncs(X_) \
	Declare_LmiAssignable(X_)			 \
	DeclareInline_LmiContainerFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiContainer(X_, T_, I_, CI_, S_, D_, INLINE_)	\
	Declare_LmiContainerTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiInputIterator(LmiIterator(X_), T_, const T_, D_, INLINE_)	\
	DeclareInline_LmiInputIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiContainerFuncs(X_, INLINE_)
#define Declare_LmiContainer(X_, T_, I_, CI_, S_, D_)	\
	Declare_LmiContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiInputIterator(LmiIterator(X_), T_, const T_, D_)	\
	Declare_LmiInputIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiContainerFuncs(X_)

/* Forward Container concept */
#define Declare_LmiForwardContainerTypesPart(X_)
#define Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardContainerTypesPart(X_)
#define DeclareInline_LmiForwardContainerFuncsPart(X_, INLINE_)
#define DeclareInline_LmiForwardContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiEqualityComparable(X_, INLINE_)				\
	DeclareInline_LmiLessThanComparable(X_, INLINE_)				\
	DeclareInline_LmiForwardContainerFuncsPart(X_, INLINE_)
#define Declare_LmiForwardContainerFuncs(X_) \
	Declare_LmiContainerFuncs(X_) \
	Declare_LmiEqualityComparable(X_)				\
	Declare_LmiLessThanComparable(X_)				\
	DeclareInline_LmiForwardContainerFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiForwardContainer(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiForwardContainerFuncs(X_, INLINE_)
#define Declare_LmiForwardContainer(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiForwardContainerFuncs(X_)

/* Reversible Container concept */
#define Declare_LmiReversibleContainerTypesPart(X_, I_, CI_) \
	typedef I_ LmiReverseIterator(X_); \
	typedef CI_ LmiConstReverseIterator(X_);
#define Declare_LmiReversibleContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiReversibleContainerTypesPart(X_, I_, CI_)
#define DeclareInline_LmiReversibleContainerFuncsPart(X_, INLINE_) \
	INLINE_ LmiReverseIterator(X_) LmiRBegin(X_)(X_* x); \
	INLINE_ LmiConstReverseIterator(X_) LmiRBeginConst(X_)(const X_* x); \
	INLINE_ LmiReverseIterator(X_) LmiREnd(X_)(X_* x); \
	INLINE_ LmiConstReverseIterator(X_) LmiREndConst(X_)(const X_* x);
#define DeclareInline_LmiReversibleContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiForwardContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiReversibleContainerFuncsPart(X_, INLINE_)
#define Declare_LmiReversibleContainerFuncs(X_) \
	Declare_LmiForwardContainerFuncs(X_) \
	DeclareInline_LmiReversibleContainerFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiReversibleContainer(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiReversibleContainerTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiBidirectionalIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiBidirectionalIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiBidirectionalIterator(LmiReverseIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiBidirectionalIterator(LmiConstReverseIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiReversibleContainerFuncs(X_, INLINE_)
#define Declare_LmiReversibleContainer(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiReversibleContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiBidirectionalIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiReverseIterator(X_), T_, const T_, D_) \
	Declare_LmiBidirectionalIterator(LmiConstReverseIterator(X_), const T_, const T_, D_) \
	Declare_LmiReversibleContainerFuncs(X_)

/* Random Access Container concept */
#define Declare_LmiRandomAccessContainerTypesPart(X_)
#define Declare_LmiRandomAccessContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiReversibleContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiRandomAccessContainerTypesPart(X_)
#define DeclareInline_LmiRandomAccessContainerFuncsPart(X_, INLINE_) \
	INLINE_ LmiValueType(X_)* LmiAt(X_)(X_* x, LmiSizeType(X_) n); \
	INLINE_ const LmiValueType(X_)* LmiAtConst(X_)(const X_* x, LmiSizeType(X_) n);
#define DeclareInline_LmiRandomAccessContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiReversibleContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiRandomAccessContainerFuncsPart(X_, INLINE_)
#define Declare_LmiRandomAccessContainerFuncs(X_) \
	Declare_LmiReversibleContainerFuncs(X_) \
	DeclareInline_LmiRandomAccessContainerFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiRandomAccessContainer(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiRandomAccessContainerTypes(X_, T_, I_, CI_, S_, D_)	\
	DeclareInline_LmiRandomAccessIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiRandomAccessIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiRandomAccessIterator(LmiReverseIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiRandomAccessIterator(LmiConstReverseIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiRandomAccessContainerFuncs(X_, INLINE_)
#define Declare_LmiRandomAccessContainer(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiRandomAccessContainerTypes(X_, T_, I_, CI_, S_, D_)	\
	Declare_LmiRandomAccessIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiRandomAccessIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiRandomAccessIterator(LmiReverseIterator(X_), T_, const T_, D_) \
	Declare_LmiRandomAccessIterator(LmiConstReverseIterator(X_), const T_, const T_, D_) \
	Declare_LmiRandomAccessContainerFuncs(X_)

/* Sequence concept */
#define Declare_LmiSequenceTypesPart(X_)
#define Declare_LmiSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiSequenceTypesPart(X_)
#define DeclareInline_LmiSequenceFuncsPart(X_, INLINE_) \
	INLINE_ X_* LmiConstructN(X_)(X_* x, LmiSizeType(X_) n, const LmiValueType(X_)* t, LmiAllocator* a); \
	INLINE_ X_* LmiConstructRange(X_)(X_* x, LmiConstIterator(X_) first, LmiConstIterator(X_) last, LmiAllocator* a); \
	INLINE_ LmiValueType(X_)* LmiFront(X_)(X_* x); \
	INLINE_ const LmiValueType(X_)* LmiFrontConst(X_)(const X_* x); \
	INLINE_ LmiIterator(X_) LmiInsert(X_)(X_* x, LmiIterator(X_) pos, const LmiValueType(X_)* t); \
	INLINE_ LmiBool LmiInsertN(X_)(X_* x, LmiIterator(X_) pos, LmiSizeType(X_) n, const LmiValueType(X_)* t); \
	INLINE_ LmiBool LmiInsertRange(X_)(X_* x, LmiIterator(X_) pos, LmiConstIterator(X_) first, LmiConstIterator(X_) last); \
	INLINE_ LmiIterator(X_) LmiErase(X_)(X_* x, LmiIterator(X_) pos); \
	INLINE_ LmiIterator(X_) LmiEraseRange(X_)(X_* x, LmiIterator(X_) first, LmiIterator(X_) last); \
	INLINE_ void LmiClear(X_)(X_* x); \
	INLINE_ LmiBool LmiResize(X_)(X_* x, LmiSizeType(X_) n, const LmiValueType(X_)* t);
#define DeclareInline_LmiSequenceFuncs(X_, INLINE_) \
	DeclareInline_LmiForwardContainerFuncs(X_, INLINE_) \
	DeclareInline_LmiDefaultConstructible(X_, INLINE_)	\
	DeclareInline_LmiSequenceFuncsPart(X_, INLINE_)
#define Declare_LmiSequenceFuncs(X_) \
	Declare_LmiForwardContainerFuncs(X_) \
	Declare_LmiDefaultConstructible(X_)	\
	DeclareInline_LmiSequenceFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiSequence(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiSequenceFuncs(X_, INLINE_)
#define Declare_LmiSequence(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiSequenceFuncs(X_)

/* Member Templates for constructing/inserting from a range defined by arbitrary iterators */
#define DeclareInline_LmiSequenceTemplateFuncs(X_, InputIterator_, INLINE_) \
	INLINE_ X_ * LmiConstructIteratorRange(X_, InputIterator_)(X_* x, InputIterator_ first, InputIterator_ last, LmiAllocator * a); \
	INLINE_ LmiBool LmiInsertIteratorRange(X_, InputIterator_)(X_* x, LmiIterator(X_) pos, InputIterator_ first, InputIterator_ last);
#define Declare_LmiSequenceTemplateFuncs(X_, InputIterator_) \
	DeclareInline_LmiSequenceTemplateFuncs(X_, InputIterator_, LMI_NO_INLINE)

/* Front Insertion Sequence concept */
#define Declare_LmiFrontInsertionSequenceTypesPart(X_)
#define Declare_LmiFrontInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiFrontInsertionSequenceTypesPart(X_)
#define DeclareInline_LmiFrontInsertionSequenceFuncsPart(X_, INLINE_) \
	INLINE_ LmiBool LmiPushFront(X_)(X_* x, const LmiValueType(X_)* t); \
	INLINE_ void LmiPopFront(X_)(X_* x);
#define DeclareInline_LmiFrontInsertionSequenceFuncs(X_, INLINE_) \
	DeclareInline_LmiSequenceFuncs(X_, INLINE_) \
	DeclareInline_LmiFrontInsertionSequenceFuncsPart(X_, INLINE_)
#define Declare_LmiFrontInsertionSequenceFuncs(X_) \
	Declare_LmiSequenceFuncs(X_) \
	DeclareInline_LmiFrontInsertionSequenceFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiFrontInsertionSequence(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiFrontInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiFrontInsertionSequenceFuncs(X_, INLINE_)

#define Declare_LmiFrontInsertionSequence(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiFrontInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiFrontInsertionSequenceFuncs(X_)

/* Back Insertion Sequence concept */
#define Declare_LmiBackInsertionSequenceTypesPart(X_)
#define Declare_LmiBackInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardContainerTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiBackInsertionSequenceTypesPart(X_)
#define DeclareInline_LmiBackInsertionSequenceFuncsPart(X_, INLINE_) \
	INLINE_ LmiValueType(X_)* LmiBack(X_)(X_* x); \
	INLINE_ const LmiValueType(X_)* LmiBackConst(X_)(const X_* x); \
	INLINE_ LmiBool LmiPushBack(X_)(X_* x, const LmiValueType(X_)* t); \
	INLINE_ void LmiPopBack(X_)(X_* x);
#define DeclareInline_LmiBackInsertionSequenceFuncs(X_, INLINE_) \
	DeclareInline_LmiSequenceFuncs(X_, INLINE_) \
	DeclareInline_LmiBackInsertionSequenceFuncsPart(X_, INLINE_)
#define Declare_LmiBackInsertionSequenceFuncs(X_) \
	Declare_LmiSequenceFuncs(X_) \
	DeclareInline_LmiBackInsertionSequenceFuncsPart(X_, LMI_NO_INLINE)
#define DeclareInline_LmiBackInsertionSequence(X_, T_, I_, CI_, S_, D_, INLINE_) \
	Declare_LmiBackInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	DeclareInline_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_, INLINE_) \
	DeclareInline_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_, INLINE_) \
	DeclareInline_LmiBackInsertionSequenceFuncs(X_, INLINE_)
#define Declare_LmiBackInsertionSequence(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiBackInsertionSequenceTypes(X_, T_, I_, CI_, S_, D_) \
	Declare_LmiForwardIterator(LmiIterator(X_), T_, const T_, D_) \
	Declare_LmiForwardIterator(LmiConstIterator(X_), const T_, const T_, D_) \
	Declare_LmiBackInsertionSequenceFuncs(X_)


#endif /* LMI_CONTAINERS_H_ */

