/**
{file:
	{name: LmiAlgorithm.h}
	{description: LMI template algorithms.}
	{copyright:
		(c) 2005-2016 Vidyo, Inc.,
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

#if !defined(LMI_ALGORITHM_H_)
#define LMI_ALGORITHM_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>

/**
{package:
	{name: Algorithms}
	{parent: Utils}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{library: LmiUtils}
	{description: A set of generic algorithms. Each operates on a range of elements or a pair of ranges.}
}
*/

/**
{function:
	{name: LmiCopy}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Copy a range of items from one container to another.}
	{prototype: OutputIterator_ LmiCopy(InputIterator_, OutputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, OutputIterator_ d_)}
	{template-parameter:
		{name: InputIterator_}
		{description: The iterator type of the container containing the items to be copied.  The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: OutputIterator_}
		{description: The iterator type of the container to which items are to be copied.  The iterator type must be a model of LmiOutputIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: first_}
		{description: An iterator to the first item in the container to copy.}
	}
	{parameter:
		{name: last_}
		{description: An iterator to one past the last item in the container to copy.}
	}
	{parameter:
		{name: d_}
		{description: An iterator into the destination container where the items are to be copied.}
	}
	{return: An iterator to the item one past the last item copied in the destination container or the exceptional iterator (0) on error.}
	{note:
		The macro Define_LmiCopy must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiCopy(LmiConstVectorIterator(LmiInt), LmiVectorIterator(LmiInt), LmiInt)
		void copy_vector(const LmiVector(LmiInt)* src, LmiVector(LmiInt)* dst) \{
			LmiCopy(LmiConstVectorIterator(LmiInt), LmiVectorIterator(LmiInt), LmiInt)(LmiVectorBeginConst(LmiInt)(&src), LmiVectorEndConst(LmiInt)(&src), LmiVectorBegin(LmiInt)(&dst));
		\}
	}
}
*/
#define LmiCopy(I_, O_, T_) LmiTemplate3(LmiCopy, I_, O_, T_)
#define Declare_LmiCopy(InputIterator_, OutputIterator_, T_) \
OutputIterator_ LmiCopy(InputIterator_, OutputIterator_, T_)(InputIterator_ first_, \
	InputIterator_ last_, OutputIterator_ d_);
#define Define_LmiCopy(InputIterator_, OutputIterator_, T_) \
OutputIterator_ LmiCopy(InputIterator_, OutputIterator_, T_)(InputIterator_ first_, \
	InputIterator_ last_, OutputIterator_ d_) { \
	for(; !LmiEqual(InputIterator_)(&first_, &last_); \
	  LmiIncrement(InputIterator_)(&first_), \
	  LmiIncrement(OutputIterator_)(&d_)) { \
		if (LmiAssign(T_)(LmiContentOf(OutputIterator_)(&d_), \
		LmiContentOf(InputIterator_)(&first_)) == NULL) { \
			OutputIterator_ ret; \
			LmiConstructExceptional(OutputIterator_)(&ret); \
			return ret; \
		} \
	} \
	return d_; \
}

/**
{function:
	{name: LmiFill}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Fill a range of items of a container with the specified value.}
	{prototype: LmiBool LmiFill(ForwardIterator_, T_)(ForwardIterator_ first_, ForwardIterator_ last_, const T_* t_)}
	{template-parameter:
		{name: ForwardIterator_}
		{description: The iterator type of the container containing the items to be filled.  The iterator type must be a model of LmiForwardIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: first_}
		{description: An iterator to the first item in the container to filled.}
	}
	{parameter:
		{name: last_}
		{description: An iterator to one past the last item in the container to filled.}
	}
	{parameter:
		{name: t_}
		{description: The fill value.}
	}
	{return: LMI_TRUE if successful, or LMI_FALSE otherwise.}
	{note:
		The macro Define_LmiFill must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiFill(LmiVectorIterator(LmiInt), LmiInt)
		void fill_vector(LmiVector(LmiInt)* v, LmiInt value) \{
			LmiFill(LmiVectorIterator(LmiInt), LmiInt)(LmiVectorBegin(LmiInt)(&v), LmiVectorEnd(LmiInt)(&v), value);
		\}
	}
}
*/
#define LmiFill(F_, T_) LmiTemplate2(LmiFill, F_, T_)
#define Declare_LmiFill(ForwardIterator_, T_) \
LmiBool LmiFill(ForwardIterator_, T_)(ForwardIterator_ first_, ForwardIterator_ last_, const T_* t_);
#define Define_LmiFill(ForwardIterator_, T_) \
LmiBool LmiFill(ForwardIterator_, T_)(ForwardIterator_ first_, ForwardIterator_ last_, const T_* t_) { \
	for(; !LmiEqual(ForwardIterator_)(&first_, &last_); \
	  LmiIncrement(ForwardIterator_)(&first_)) { \
		if (LmiAssign(T_)(LmiContentOf(ForwardIterator_)(&first_), t_) == NULL) \
			return LMI_FALSE; \
	} \
	return LMI_TRUE; \
}

/**
{function:
	{name: LmiFillN}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Fill a range of items of a container with the specified value.}
	{prototype: LmiBool LmiFillN(ForwardIterator_, Size_, T_)(ForwardIterator_ first_, Size_ n_, const T_* t_)}
	{template-parameter:
		{name: ForwardIterator_}
		{description: The iterator type of the container containing the items to be filled.  The iterator type must be a model of LmiForwardIterator.}
	}
	{template-parameter:
		{name: Size_}
		{description: The size type of T_.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: first_}
		{description: An iterator to the first item in the container to filled.}
	}
	{parameter:
		{name: n_}
		{description: The number of items to fill.}
	}
	{parameter:
		{name: t_}
		{description: The fill value.}
	}
	{return: LMI_TRUE if successful, or LMI_FALSE otherwise.}
	{note:
		The macro Define_LmiFillN must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiFillN(LmiVectorIterator(LmiInt), LmiSizeT, LmiInt)
		void filln_vector(LmiVector(LmiInt)* v, LmiSizeT n, LmiInt value) \{
			LmiFillN(LmiVectorIterator(LmiInt), LmiInt)(LmiVectorBegin(LmiInt)(&v), n, &value);
		\}
	}
}
*/
#define LmiFillN(F_, S_, T_) LmiTemplate3(LmiFillN, F_, S_, T_)
#define Declare_LmiFillN(ForwardIterator_, Size_, T_) \
ForwardIterator_ LmiFillN(ForwardIterator_, Size_, T_)(ForwardIterator_ first_, Size_ n_, const T_* t_);
#define Define_LmiFillN(ForwardIterator_, Size_, T_) \
ForwardIterator_ LmiFillN(ForwardIterator_, Size_, T_)(ForwardIterator_ first_, Size_ n_, const T_* t_) { \
	for(; n_ > 0; --n_, LmiIncrement(ForwardIterator_)(&first_)) { \
		if (LmiAssign(T_)(LmiContentOf(ForwardIterator_)(&first_), t_) == NULL) { \
			ForwardIterator_ ret; \
			LmiConstructExceptional(ForwardIterator_)(&ret); \
			return ret; \
		} \
	} \
	return first_; \
}

/**
{function:
	{name: LmiAlgorithmFind}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find the first item in range equal to the specified value.}
	{prototype: InputIterator_ LmiAlgorithmFind(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, const T_* value_)}
	{template-parameter:
		{name: InputIterator_}
		{description: The iterator type of the container containing the items to be searched.  The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiEqualityComparable.}
	}
	{parameter:
		{name: first_}
		{description: An iterator to the first item in the container to be searched.}
	}
	{parameter:
		{name: last_}
		{description: An iterator to one past the last item in the container to be searched.}
	}
	{parameter:
		{name: value_}
		{description: The value to find.}
	}
	{return: An iterator to the first item in the range whose value is equal to the value specified.}
	{note:
		The macro Define_LmiAlgorithmFind must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiAlgorithmFind(LmiVectorConstIterator(LmiInt),  LmiInt)
		LmiVectorConstIterator find_vector(const LmiVector(LmiInt)* v, LmiInt value) \{
			return LmiAlgorithmFind(LmiVectorConstIterator(LmiInt), LmiInt)(LmiVectorBeginConst(LmiInt)(&v), LmiVectorEndConst(LmiInt)(&v), &value);
		\}
	}
}
*/
#define LmiAlgorithmFind(I_, T_) LmiTemplate2(LmiAlgorithmFind, I_, T_)
#define Declare_LmiAlgorithmFind(InputIterator_, T_) \
InputIterator_ LmiAlgorithmFind(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, const T_* value_);
#define Define_LmiAlgorithmFind(InputIterator_, T_) \
InputIterator_ LmiAlgorithmFind(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, const T_* value_) { \
	for(; !LmiEqual(InputIterator_)(&first_, &last_); LmiIncrement(InputIterator_)(&first_)) { \
		if (LmiEqual(T_)(LmiContentOf(InputIterator_)(&first_), value_)) { \
			return first_; \
		} \
	} \
	return first_; \
}

/**
{function:
	{name: LmiAlgorithmFindIf}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find the first item in range equal to the specified value as determined by the predicate function.}
	{prototype: InputIterator_ LmiAlgorithmFindIf(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, LmiPredicate(T_) predicate_, void* data_)}
	{template-parameter:
		{name: InputIterator_}
		{description: The iterator type of the container containing the items to be searched. The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiEqualityComparable.}
	}
	{parameter:
		{name: first_}
		{description: An iterator to the first item in the container to be searched.}
	}
	{parameter:
		{name: last_}
		{description: An iterator to one past the last item in the container to be searched.}
	}
	{parameter:
		{name: predicate_}
		{description: The predicate function. The function must be a model of LmiPredicate.}
	}
	{parameter:
		{name: data_}
		{description: A user data pointer.}
	}
	{return: An iterator to the first item in the range for which the predicate returns true.}
	{note:
		The macro Define_LmiAlgorithmFindIf must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool greater_than_n(LmiInt* x, void* data) \{
			LmiInt n = *(LmiInt*)data;
			return *x > n;
		\}
		Define_LmiAlgorithmFindIf(LmiVectorConstIterator(LmiInt), LmiInt)
		LmiVectorConstIterator findif_vector(const LmiVector(LmiInt)* v) \{
			LmiInt n = 99;
			return LmiAlgorithmFindIf(LmiVectorConstIterator(LmiInt), LmiInt)(LmiVectorBeginConst(LmiInt)(&v), LmiVectorEndConst(LmiInt)(&v), greater_than_n, &n);
		\}
	}
}
*/
#define LmiAlgorithmFindIf(I_, T_) LmiTemplate2(LmiAlgorithmFindIf, I_, T_)
#define Declare_LmiAlgorithmFindIf(InputIterator_, T_) \
Declare_LmiPredicate(T_) \
InputIterator_ LmiAlgorithmFindIf(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, \
	LmiPredicate(T_) predicate_, void* data_);
#define Define_LmiAlgorithmFindIf(InputIterator_, T_) \
InputIterator_ LmiAlgorithmFindIf(InputIterator_, T_)(InputIterator_ first_, InputIterator_ last_, \
	LmiPredicate(T_) predicate_, void* data_) { \
	for (; !LmiEqual(InputIterator_)(&first_, &last_); LmiIncrement(InputIterator_)(&first_)) { \
		if (predicate_(LmiContentOf(InputIterator_)(&first_), data_)) { \
			return first_; \
		} \
	} \
	return first_; \
}

/* Equal */
#define LmiAlgorithmEqual(I1_, I2_, T_) LmiTemplate3(LmiAlgorithmEqual, I1_, I2_, T_)
#define Declare_LmiAlgorithmEqual(InputIterator1_, InputIterator2_, T_) \
LmiBool LmiAlgorithmEqual(InputIterator1_, InputIterator2_, T_)(InputIterator1_ first1_, \
	InputIterator1_ last1_, InputIterator2_ first2_);
#define Define_LmiAlgorithmEqual(InputIterator1_, InputIterator2_, T_) \
LmiBool LmiAlgorithmEqual(InputIterator1_, InputIterator2_, T_)(InputIterator1_ first1_, \
	InputIterator1_ last1_, InputIterator2_ first2_) { \
	for(; !LmiEqual(InputIterator1_)(&first1_, &last1_); \
	  LmiIncrement(InputIterator1_)(&first1_), \
	  LmiIncrement(InputIterator2_)(&first2_)) { \
		if (!LmiEqual(T_)(LmiContentOf(InputIterator1_)(&first1_), \
		  LmiContentOf(InputIterator2_)(&first2_))) { \
			return LMI_FALSE; \
		} \
	} \
	return LMI_TRUE; \
}

/**
{function:
	{name: LmiPartition}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Partition a range of elements into two groups. The first group shall contain all the elements for which a supplied predicate returns true.
		The second group shall contain all the elements for which the predicate returns false. This is not a stable partition: the order of the elements
		in each group may change.}
	{prototype: BI_ LmiPartition(BI_, T_)(BI_ first, BI_ last, LmiPredicate(T_) predicate, void *data)}
	{template-parameter:
		{name: BI_}
		{description: The iterator type of the container containing the items to be searched. The iterator type must be a model of LmiBidirectionalIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: first}
		{description: An iterator to the first item in the range.}
	}
	{parameter:
		{name: last}
		{description: An iterator to one past the last item in the range.}
	}
	{parameter:
		{name: predicate}
		{description: The predicate function. The function must be a model of LmiPredicate.}
	}
	{parameter:
		{name: data}
		{description: A user data pointer that will be passed to each invocation of the predicate.}
	}
	{return: An iterator marking the first element of the second group.}
	{note:
		The macro Define_LmiPartition must be called at global scope before calling
		this function.
	}
}
*/
#define LmiPartition(BI_, T_) LmiTemplate2(LmiPartition, BI_, T_)
#define Declare_LmiPartition(BI_, T_) \
	Declare_LmiPredicate(T_) \
	BI_ LmiPartition(BI_, T_)(BI_ x, BI_ y, LmiPredicate(T_) predicate, void *data);
#define Define_LmiPartition(BI_, T_) \
	BI_ LmiPartition(BI_, T_)(BI_ x, BI_ y, LmiPredicate(T_) predicate, void *data) \
	{ \
		for(;;) \
		{ \
			for(;;) \
			{ \
				if(LmiEqual(BI_)(&x, &y)) \
					return y; \
				if(!predicate(LmiContentOf(BI_)(&x), data)) \
					break; \
				LmiIncrement(BI_)(&x); \
			} \
	\
			for(;;) \
			{ \
				LmiDecrement(BI_)(&y); \
				if(LmiEqual(BI_)(&x, &y)) \
					return y; \
				if(predicate(LmiContentOf(BI_)(&y), data)) \
					break; \
			} \
	\
			LmiSwap(T_)(LmiContentOf(BI_)(&x), LmiContentOf(BI_)(&y)); \
			LmiIncrement(BI_)(&x); \
		} \
	}

/**
{function:
	{name: LmiSortComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Sort a range of items of a container using a comparison function.}
	{prototype: void LmiSortComp(Ran_, T_, Comp_)(Ran_ x_, Ran_ y_)}
	{template-parameter:
		{name: Ran_}
		{description: The iterator type of the container containing the items to sort.
		The iterator type must be a model of LmiRandomAccessIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{template-parameter:
		{name: Comp_}
		{description: The comparison function. The comparison function must be a model of LmiLessThanComparable.}
	}
	{parameter:
		{name: x_}
		{description: An iterator to the first item in the container to sort.}
	}
	{parameter:
		{name: y_}
		{description: an iterator to one past of the last item in the container to sort.}
	}
	{note:
		The macro Define_LmiSortComp must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool less(const LmiInt* a, const LmiInt* b) \{ return a < b; \}
		Define_LmiSortComp(LmiVectorIterator(LmiInt), LmiInt, less)
		void sortcomp_vector(LmiVector(LmiInt)* v) \{
			LmiSortComp(LmiVectorIterator(LmiInt), LmiInt, less)(LmiVectorBegin(LmiInt)(v), LmiVectorEnd(LmiInt)(v));
		\}
	}
}
*/
#define LmiSortComp(Ran_, T_, Comp_) LmiTemplate3(LmiSortComp, Ran_, T_, Comp_)
#define Declare_LmiSortComp(Ran_, T_, Comp_) \
	void LmiSortComp(Ran_, T_, Comp_)(Ran_ x_, Ran_ y_);
#define Define_LmiSortComp(Ran_, T_, Comp_) \
	void LmiSortComp(Ran_, T_, Comp_)(Ran_ x_, Ran_ y_) \
	{ \
		LmiDifferenceType(Ran_) d = LmiSubtract(Ran_)(&y_, &x_); \
		if(d > 1) \
		{ \
			Ran_ last, pivot, cur, pick; \
			LmiConstructCopy(Ran_)(&last, &y_); \
			LmiDecrement(Ran_)(&last); \
			LmiConstructCopy(Ran_)(&pivot, &x_); \
			LmiConstructCopy(Ran_)(&cur, &x_); \
			if(d > 2) \
			{ \
				LmiConstructCopy(Ran_)(&pick, &x_); \
				LmiIncrementN(Ran_)(&pick, d / 2); \
				LmiSwap(T_)(LmiContentOf(Ran_)(&pick), LmiContentOf(Ran_)(&last)); \
				LmiDestruct(Ran_)(&pick); \
			} \
			while(!LmiEqual(Ran_)(&cur, &last)) \
			{ \
				if(Comp_(LmiContentOf(Ran_)(&cur), LmiContentOf(Ran_)(&last))) \
				{ \
					LmiSwap(T_)(LmiContentOf(Ran_)(&cur), LmiContentOf(Ran_)(&pivot)); \
					LmiIncrement(Ran_)(&pivot); \
				} \
				LmiIncrement(Ran_)(&cur); \
			} \
			LmiSwap(T_)(LmiContentOf(Ran_)(&last), LmiContentOf(Ran_)(&pivot)); \
			LmiSortComp(Ran_, T_, Comp_)(x_, pivot); \
			LmiIncrement(Ran_)(&pivot); \
			LmiSortComp(Ran_, T_, Comp_)(pivot, y_); \
			LmiDestruct(Ran_)(&cur); \
			LmiDestruct(Ran_)(&pivot); \
			LmiDestruct(Ran_)(&last); \
		} \
	}

/**
{function:
	{name: LmiSort}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Sort a range of items of a container.}
	{prototype: void LmiSort(Ran_, T_)(Ran_ x_, Ran_ y_)}
	{template-parameter:
		{name: Ran_}
		{description: The iterator type of the container containing the items to sort.
		The iterator type must be a model of LmiRandomAccessIterator.}
	}
	{template-parameter:
		{name: T_}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: x_}
		{description: An iterator to the first item in the set to sort.}
	}
	{parameter:
		{name: y_}
		{description: an iterator to one-past-the-end of the last item in the set to sort.}
	}
	{note:
		The macro Define_LmiSort must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiSort(LmiVectorIterator(LmiInt), LmiInt)
		void sort_vector(LmiVector(LmiInt)* v) \{
			LmiSort(LmiVectorIterator(LmiInt), LmiInt)(LmiVectorBegin(LmiInt)(v), LmiVectorEnd(LmiInt)(v));
		\}
	}
}
*/
#define LmiSort(Ran_, T_)          LmiSortComp(Ran_, T_, LmiLess(T_))
#define Declare_LmiSort(Ran_, T_)  Declare_LmiSortComp(Ran_, T_, LmiLess(T_))
#define Define_LmiSort(Ran_, T_)   Define_LmiSortComp(Ran_, T_, LmiLess(T_))

/**
{function:
	{name: LmiUniqueComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Removes adjacent equivalent elements from a range. This function
		moves all the elements that are not to be removed to the front of the range, preserving their
		order. It returns an iterator marking the end of the retained elements. To complete the removal
		process, the caller can erase from this location to the end of the range.}
	{prototype: FI LmiUniqueComp(FI, T, Comp)(FI x, FI y)}
	{template-parameter:
		{name: FI}
		{description: The iterator type of the container containing the items to process.
		The iterator type must be a model of LmiForwardIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{template-parameter:
		{name: Comp}
		{description: The function to be used to test elements for equivalence.}
	}
	{parameter:
		{name: x}
		{description: Points to the first item in the range to be processed.}
	}
	{parameter:
		{name: y}
		{description: Points to one past the last item in the range to be processed.}
	}
	{return: An iterator pointing to the beginning of the invalidated part of the range.}
	{note:
		The macro Define_LmiUniqueComp must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool SameLastDigit(const LmiUint *a, const LmiUint *b)
		\{
			return (*a % 10) == (*b % 10);
		\}

		Define_LmiUniqueComp(LmiVectorIterator(LmiUint), LmiUint, SameLastDigit)

		void UniqueByLastDigit(LmiVector(LmiUint) *v)
		\{
			LmiVectorIterator(LmiUint) end = LmiUniqueComp(LmiVectorIterator(LmiUint), LmiUint, SameLastDigit)(
				LmiVectorBegin(LmiUint)(v), LmiVectorEnd(LmiUint)(v));
			LmiVectorEraseRange(LmiUint)(v, end, LmiVectorEnd(LmiUint)(v));
		\}
	}
}
*/
#define LmiUniqueComp(FI_, T_, Comp_) LmiTemplate3(LmiUniqueComp, FI_, T_, Comp_)
#define Declare_LmiUniqueComp(FI_, T_, Comp_) \
	FI_ LmiUniqueComp(FI_, T_, Comp_)(FI_ x, FI_ y);
#define Define_LmiUniqueComp(FI_, T_, Comp_) \
	FI_ LmiUniqueComp(FI_, T_, Comp_)(FI_ x, FI_ y) \
	{ \
		FI_ last; \
		if(LmiEqual(FI_)(&x, &y)) \
			return y; \
		LmiConstructCopy(FI_)(&last, &x); \
		for(;;) \
		{ \
			LmiIncrement(FI_)(&x); \
			if(LmiEqual(FI_)(&x, &y)) \
				break; \
			if(!Comp_(LmiContentOf(FI_)(&last), LmiContentOf(FI_)(&x))) \
			{ \
				LmiIncrement(FI_)(&last); \
				if(!LmiEqual(FI_)(&last, &x)) \
					LmiAssign(T_)(LmiContentOf(FI_)(&last), LmiContentOf(FI_)(&x)); \
			} \
		} \
		LmiIncrement(FI_)(&last); \
		return last; /* assumes FI_ is a simple type */ \
	}

/**
{function:
	{name: LmiUnique}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Removes adjacent equal elements from a range. This function
		moves all the elements that are not to be removed to the front of the range, preserving their
		order. It returns an iterator marking the end of the retained elements. To complete the removal
		process, the caller can erase from this location to the end of the range.}
	{prototype: FI LmiUnique(FI, T)(FI x, FI y)}
	{template-parameter:
		{name: FI}
		{description: The iterator type of the container containing the items to process.
		The iterator type must be a model of LmiForwardIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: x}
		{description: Points to the first item in the range to be processed.}
	}
	{parameter:
		{name: y}
		{description: Points to one past the last item in the range to be processed.}
	}
	{return: An iterator pointing to the beginning of the invalidated part of the range.}
	{note:
		The macro Define_LmiUnique must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiUnique(LmiVectorIterator(LmiUint), LmiUint)

		void Unique(LmiVector(LmiUint) *v)
		\{
			LmiVectorIterator(LmiUint) end = LmiUnique(LmiVectorIterator(LmiUint), LmiUint)(
				LmiVectorBegin(LmiUint)(v), LmiVectorEnd(LmiUint)(v));
			LmiVectorEraseRange(LmiUint)(v, end, LmiVectorEnd(LmiUint)(v));
		\}
	}
}
*/
#define LmiUnique(FI_, T_)         LmiUniqueComp(FI_, T_, LmiEqual(T_))
#define Declare_LmiUnique(FI_, T_) Declare_LmiUniqueComp(FI_, T_, LmiEqual(T_))
#define Define_LmiUnique(FI_, T_)  Define_LmiUniqueComp(FI_, T_, LmiEqual(T_))

/**
{function:
	{name: LmiRemoveIf}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Removes all the elements in a range matching a given condition. This function
		moves all the elements that are not to be removed to the front of the range, preserving their
		order. It returns an iterator marking the end of the retained elements. To complete the removal
		process, the caller can erase from this location to the end of the range.}
	{prototype: FI LmiRemoveIf(FI, T)(FI x, FI y, LmiPredicate(T) predicate, void *data)}
	{template-parameter:
		{name: FI}
		{description: The iterator type of the container containing the items to process.
		The iterator type must be a model of LmiForwardIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type stored in the container. The type must be a model of LmiAssignable.}
	}
	{parameter:
		{name: x}
		{description: Points to the first item in the range to be processed.}
	}
	{parameter:
		{name: y}
		{description: Points to one past the last item in the range to be processed.}
	}
	{parameter:
		{name: predicate}
		{description: A function to be called once for each element in the range. If the function returns
			LMI_TRUE, the element will be removed.}
	}
	{parameter:
		{name: data}
		{description: A pointer that will be passed to each invocation of the predicate function.}
	}
	{return: An iterator pointing to the beginning of the invalidated part of the range.}
	{note:
		The macro Define_LmiRemoveIf must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiRemoveIf(LmiVectorIterator(LmiUint), LmiUint)

		LmiBool IsEven(const LmiUint *x, void *data)
		\{
			return (*x % 2) == 0;
		\}

		void RemoveEven(LmiVector(LmiUint) *v)
		\{
			LmiVectorIterator(LmiUint) end = LmiRemoveIf(LmiVectorIterator(LmiUint), LmiUint)(
				LmiVectorBegin(LmiUint)(v), LmiVectorEnd(LmiUint)(v), IsEven, NULL);
			LmiVectorEraseRange(LmiUint)(v, end, LmiVectorEnd(LmiUint)(v));
		\}
	}
}
*/
#define LmiRemoveIf(FI_, T_) LmiTemplate2(LmiRemoveIf, FI_, T_)
#define Declare_LmiRemoveIf(FI_, T_) \
	Declare_LmiPredicate(T_) \
	FI_ LmiRemoveIf(FI_, T_)(FI_ x, FI_ y, LmiPredicate(T_) predicate_, void *data_);
#define Define_LmiRemoveIf(FI_, T_) \
	FI_ LmiRemoveIf(FI_, T_)(FI_ x, FI_ y, LmiPredicate(T_) predicate_, void *data_) \
	{ \
		while(!LmiEqual(FI_)(&x, &y)) \
		{ \
			if(predicate_(LmiContentOf(FI_)(&x), data_)) \
			{ \
				FI_ last; \
				LmiConstructCopy(FI_)(&last, &x); \
				for(;;) \
				{ \
					LmiIncrement(FI_)(&x); \
					if(LmiEqual(FI_)(&x, &y)) \
						return last; /* assumes FI_ is a simple type */ \
					if(!predicate_(LmiContentOf(FI_)(&x), data_)) \
					{ \
						LmiAssign(T_)(LmiContentOf(FI_)(&last), LmiContentOf(FI_)(&x)); \
						LmiIncrement(FI_)(&last); \
					} \
				} \
			} \
			LmiIncrement(FI_)(&x); \
		} \
		return x; \
	}

/**
{function:
	{name: LmiMismatchComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find the first place where two sequences differ.}
	{prototype: void LmiMismatchComp(I1, I2, Comp)(I1 ai, I1 ae, I2 bi, I2 be, I1 *am, I2 *bm)}
	{template-parameter:
		{name: I1}
		{description: The iterator type of the first sequence.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: I2}
		{description: The iterator type of the second sequence.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: am}
		{description: An iterator to the first unmatched element of the first sequence will be written into this variable.
		If set to ae (one past the last element of the first sequence) then the entire first sequence is contained in the
		second sequence.}
	}
	{parameter:
		{name: bm}
		{description: An iterator to the first unmatched element of the second sequence will be written into this variable.
		If set to be (one past the last element of the second sequence) then the entire second sequence is contained in the
		first sequence.}
	}
	{note:
		The macro Define_LmiMismatchComp must be called at global scope before calling
		this function.
	}
}
*/
#define LmiMismatchComp(I1_, I2_, Comp_) LmiTemplate3(LmiMismatchComp, I1_, I2_, Comp_)
#define Declare_LmiMismatchComp(I1_, I2_, Comp_) \
	void LmiMismatchComp(I1_, I2_, Comp_)(I1_ ai, I1_ ae, I2_ bi, I2_ be, I1_ *am, I2_ *bm);
#define Define_LmiMismatchComp(I1_, I2_, Comp_) \
	void LmiMismatchComp(I1_, I2_, Comp_)(I1_ ai, I1_ ae, I2_ bi, I2_ be, I1_ *am, I2_ *bm) \
	{ \
		while( \
			!LmiEqual(I1_)(&ai, &ae) && \
			!LmiEqual(I2_)(&bi, &be) && \
			Comp_(LmiContentOfConst(I1_)(&ai), LmiContentOfConst(I2_)(&bi))) \
		{ \
			LmiIncrement(I1_)(&ai); \
			LmiIncrement(I2_)(&bi); \
		} \
		*am = ai; \
		*bm = bi; \
	}

/**
{function:
	{name: LmiMismatch}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find the first place where two sequences differ.}
	{prototype: void LmiMismatch(T, I1, I2)(I1 ai, I1 ae, I2 bi, I2 be, I1 *am, I2 *bm)}
	{template-parameter:
		{name: T}
		{description: The type of the elements in the sequences.
		The type must be a model of LmiEqualityComparable.}
	}
	{template-parameter:
		{name: I1}
		{description: The iterator type of the first sequence.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: I2}
		{description: The iterator type of the second sequence.
		The iterator type must be a model of LmiInputIterator.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: am}
		{description: An iterator to the first unmatched element of the first sequence will be written into this variable.
		If set to ae (one past the last element of the first sequence) then the entire first sequence is contained in the
		second sequence.}
	}
	{parameter:
		{name: bm}
		{description: An iterator to the first unmatched element of the second sequence will be written into this variable.
		If set to be (one past the last element of the second sequence) then the entire second sequence is contained in the
		first sequence.}
	}
	{note:
		The macro Define_LmiMismatch must be called at global scope before calling
		this function.
	}
}
*/
#define LmiMismatch(T_, I1_, I2_)         LmiMismatchComp(I1_, I2_, LmiEqual(T_))
#define Declare_LmiMismatch(T_, I1_, I2_) Declare_LmiMismatchComp(I1_, I2_, LmiEqual(T_))
#define Define_LmiMismatch(T_, I1_, I2_)  Define_LmiMismatchComp(I1_, I2_, LmiEqual(T_))

/**
{function:
	{name: LmiLexicographicalCompareComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Do a lexicographical comparison of two sequences.}
	{prototype: LmiBool LmiLexicographicalCompareComp(I, Comp)(I ai, I ae, I bi, I be)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the containers containing the items to process.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{return: Returns LMI_TRUE if the first sequence precedes the second sequence
		in lexicographical order.}
	{note:
		The macro Define_LmiLexicographicalCompareComp must be called at global scope before calling
		this function.
	}
}
*/
#define LmiLexicographicalCompareComp(I_, Comp_) LmiTemplate2(LmiLexicographicalCompareComp, I_, Comp_)
#define Declare_LmiLexicographicalCompareComp(I_, Comp_) \
	LmiBool LmiLexicographicalCompareComp(I_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be);
#define Define_LmiLexicographicalCompareComp(I_, Comp_)                          \
	LmiBool LmiLexicographicalCompareComp(I_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be) \
	{                                                                            \
		for(;;)                                                                  \
		{                                                                        \
			if(LmiEqual(I_)(&bi, &be))                                           \
				return LMI_FALSE;                                                \
			if(LmiEqual(I_)(&ai, &ae))                                           \
				return LMI_TRUE;                                                 \
			if(Comp_(LmiContentOfConst(I_)(&ai), LmiContentOfConst(I_)(&bi)))    \
				return LMI_TRUE;                                                 \
			if(Comp_(LmiContentOfConst(I_)(&bi), LmiContentOfConst(I_)(&ai)))    \
				return LMI_FALSE;                                                \
			LmiIncrement(I_)(&ai);                                               \
			LmiIncrement(I_)(&bi);                                               \
		}                                                                        \
	}

/**
{function:
	{name: LmiLexicographicalCompare}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Do a lexicographical comparison of two sequences.}
	{prototype: LmiBool LmiLexicographicalCompare(I)(I ai, I ae, I bi, I be)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the containers containing the items to process.
		The iterator type must be a model of LmiInputIterator.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{return: Returns LMI_TRUE if the first sequence precedes the second sequence
		in lexicographical order.}
	{note:
		The macro Define_LmiLexicographicalCompare must be called at global scope before calling
		this function.
	}
}
*/
#define LmiLexicographicalCompare(T_, I_)         LmiLexicographicalCompareComp(I_, LmiLess(T_))
#define Declare_LmiLexicographicalCompare(T_, I_) Declare_LmiLexicographicalCompareComp(I_, LmiLess(T_))
#define Define_LmiLexicographicalCompare(T_, I_)  Define_LmiLexicographicalCompareComp(I_, LmiLess(T_))

/* $ allow heterogeneous types for set operations. */

/**
{function:
	{name: LmiSetIntersectionComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Creates the intersection of two sorted sequences. Each element of the first sequence
		that has a corresponding equivalent element in the second sequence will appear in the output sequence.
		Within each equivalence class, if there are m elements in the first sequence and n elements in the second
		sequence, then the first min(m,n) elements from the first sequence are written to the output.}
	{prototype: void LmiSetIntersectionComp(I, C, Comp)(I ai, I ae, I bi, I be, C *out)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: out}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetIntersectionComp must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool LastDigitLess(const LmiUint *a, const LmiUint *b)
		\{
			return (*a % 10) < (*b % 10);
		\}

		Define_LmiSetIntersectionComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, c;

			const LmiUint ae[] = \{1, 2, 2, 12, 12, 6, 8, 18\};
			const LmiUint be[] = \{11, 12, 12, 13, 14, 16, 16, 18\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&c, LmiMallocAllocatorGetDefault());

			LmiSetIntersectionComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b), &c);

			\/\* leaves c with \{1, 2, 2, 6, 8\} \*\/

			LmiVectorDestruct(LmiUint)(&c);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
#define LmiSetIntersectionComp(I_, C_, Comp_) LmiTemplate3(LmiSetIntersectionComp, I_, C_, Comp_)
#define Declare_LmiSetIntersectionComp(I_, C_, Comp_) \
	void LmiSetIntersectionComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *out);
#define Define_LmiSetIntersectionComp(I_, C_, Comp_)                                          \
	void LmiSetIntersectionComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *out)           \
	{                                                                                         \
		while(!LmiEqual(I_)(&ai, &ae) && !LmiEqual(I_)(&bi, &be))                             \
		{                                                                                     \
			if(Comp_(LmiContentOfConst(I_)(&ai), LmiContentOfConst(I_)(&bi)))                 \
				LmiIncrement(I_)(&ai);                                                        \
			else if(Comp_(LmiContentOfConst(I_)(&bi), LmiContentOfConst(I_)(&ai)))            \
				LmiIncrement(I_)(&bi);                                                        \
			else                                                                              \
			{                                                                                 \
				LmiPushBack(C_)(out, LmiContentOfConst(I_)(&ai));                             \
				LmiIncrement(I_)(&ai);                                                        \
				LmiIncrement(I_)(&bi);                                                        \
			}                                                                                 \
		}                                                                                     \
	}

/**
{function:
	{name: LmiSetIntersection}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Creates the intersection of two sorted sequences. Each element of the first sequence
		that has a corresponding equivalent element in the second sequence will appear in the output sequence.
		Within each equivalence class, if there are m elements in the first sequence and n elements in the second
		sequence, then the first min(m,n) elements from the first sequence are written to the output.}
	{prototype: void LmiSetIntersection(I, C, T)(I ai, I ae, I bi, I be, C *out)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements contained in the sequences.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: out}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetIntersection must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiSetIntersection(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, c;

			const LmiUint ae[] = \{1, 2, 2, 2, 2, 6, 8, 8\};
			const LmiUint be[] = \{1, 2, 2, 3, 4, 6, 6, 8\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&c, LmiMallocAllocatorGetDefault());

			LmiSetIntersection(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b), &c);

			\/\* leaves c with \{1, 2, 2, 6, 8\} \*\/

			LmiVectorDestruct(LmiUint)(&c);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
/* $ Can we eliminate T_ and use LmiValueType(C_)? */
#define LmiSetIntersection(I_, C_, T_)         LmiSetIntersectionComp(I_, C_, LmiLess(T_))
#define Declare_LmiSetIntersection(I_, C_, T_) Declare_LmiSetIntersectionComp(I_, C_, LmiLess(T_))
#define Define_LmiSetIntersection(I_, C_, T_)  Define_LmiSetIntersectionComp(I_, C_, LmiLess(T_))

/**
{function:
	{name: LmiSetIntersectionWithDifferencesComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Calculates simultaneously the set intersection and set differences of two sorted sequences.
		If all output containers are specified, then each input element will be copied to exactly one of the containers.}
	{prototype: void LmiSetIntersectionWithDifferencesComp(I, C, Comp)(I ai, I ae, I bi, I be, C *aBoth, C *bBoth, C *aOnly, C *bOnly)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: aBoth}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container. This is the same sequence that would be generated
		by LmiSetIntersectionComp.}
	}
	{parameter:
		{name: bBoth}
		{description: Elements from the second sequence that have a matching element in the first sequence
		will be added to the end of this container. Can be NULL if this set of elements is not desired.}
	}
	{parameter:
		{name: aOnly}
		{description: Elements from the first sequence that do not have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{parameter:
		{name: bOnly}
		{description: Elements from the second sequence that do not have a matching element in the first sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetIntersectionWithDifferencesComp must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool LastDigitLess(const LmiUint *a, const LmiUint *b)
		\{
			return (*a % 10) < (*b % 10);
		\}

		Define_LmiSetIntersectionWithDifferencesComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, aBoth, bBoth, aOnly, bOnly;

			const LmiUint ae[] = \{1, 2, 2, 12, 12, 6, 8, 18\};
			const LmiUint be[] = \{11, 12, 12, 13, 14, 16, 16, 18\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&aBoth, LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&bBoth, LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&aOnly, LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&bOnly, LmiMallocAllocatorGetDefault());

			LmiSetIntersectionWithDifferencesComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b),
				&aBoth, &bBoth, &aOnly, &bOnly);

			\/\* leaves aBoth with \{1, 2, 2, 6, 8\} \*\/
			\/\* leaves bBoth with \{11, 12, 12, 16, 18\} \*\/
			\/\* leaves aOnly with \{12, 12, 18\} \*\/
			\/\* leaves bOnly with \{13, 14, 16\} \*\/

			LmiVectorDestruct(LmiUint)(&bOnly);
			LmiVectorDestruct(LmiUint)(&aOnly);
			LmiVectorDestruct(LmiUint)(&bBoth);
			LmiVectorDestruct(LmiUint)(&aBoth);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
#define LmiSetIntersectionWithDifferencesComp(I_, C_, Comp_) LmiTemplate3(LmiSetIntersectionWithDifferencesComp, I_, C_, Comp_)
#define Declare_LmiSetIntersectionWithDifferencesComp(I_, C_, Comp_) \
	void LmiSetIntersectionWithDifferencesComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *aBoth, C_ *bBoth, C_ *aOnly, C_ *bOnly);
#define Define_LmiSetIntersectionWithDifferencesComp(I_, C_, Comp_) \
	void LmiSetIntersectionWithDifferencesComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *aBoth, C_ *bBoth, C_ *aOnly, C_ *bOnly) \
	{ \
		for(;;) \
		{ \
			if(LmiEqual(I_)(&ai, &ae)) \
			{ \
				while(!LmiEqual(I_)(&bi, &be)) \
				{ \
					LmiPushBack(C_)(bOnly, LmiContentOfConst(I_)(&bi)); \
					LmiIncrement(I_)(&bi); \
				} \
				break; \
			} \
			if(LmiEqual(I_)(&bi, &be)) \
			{ \
				while(!LmiEqual(I_)(&ai, &ae)) \
				{ \
					LmiPushBack(C_)(aOnly, LmiContentOfConst(I_)(&ai)); \
					LmiIncrement(I_)(&ai); \
				} \
				break; \
			} \
			if(Comp_(LmiContentOfConst(I_)(&ai), LmiContentOfConst(I_)(&bi))) \
			{ \
				LmiPushBack(C_)(aOnly, LmiContentOfConst(I_)(&ai)); \
				LmiIncrement(I_)(&ai); \
			} \
			else if(Comp_(LmiContentOfConst(I_)(&bi), LmiContentOfConst(I_)(&ai))) \
			{ \
				LmiPushBack(C_)(bOnly, LmiContentOfConst(I_)(&bi)); \
				LmiIncrement(I_)(&bi); \
			} \
			else \
			{ \
				LmiPushBack(C_)(aBoth, LmiContentOfConst(I_)(&ai)); \
				if(bBoth != NULL) \
					LmiPushBack(C_)(bBoth, LmiContentOfConst(I_)(&bi)); \
				LmiIncrement(I_)(&ai); \
				LmiIncrement(I_)(&bi); \
			} \
		} \
	}

/**
{function:
	{name: LmiSetIntersectionWithDifferences}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Calculates simultaneously the set intersection and set differences of two sorted sequences.
		If all output containers are specified, then each input element will be copied to exactly one of the containers.}
	{prototype: void LmiSetIntersectionWithDifferences(I, C, T)(I ai, I ae, I bi, I be, C *aBoth, C *bBoth, C *aOnly, C *bOnly)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements contained in the sequences.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: aBoth}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container. This is the same sequence that would be generated
		by LmiSetIntersection.}
	}
	{parameter:
		{name: bBoth}
		{description: Elements from the second sequence that have a matching element in the first sequence
		will be added to the end of this container. Can be NULL if this set of elements is not desired.}
	}
	{parameter:
		{name: aOnly}
		{description: Elements from the first sequence that do not have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{parameter:
		{name: bOnly}
		{description: Elements from the second sequence that do not have a matching element in the first sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetIntersectionWithDifferences must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiSetIntersectionWithDifferences(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, both, aOnly, bOnly;

			const LmiUint ae[] = \{1, 2, 2, 2, 2, 6, 8, 8\};
			const LmiUint be[] = \{1, 2, 2, 3, 4, 6, 6, 8\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&both,  LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&aOnly, LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&bOnly, LmiMallocAllocatorGetDefault());

			LmiSetIntersectionWithDifferences(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b),
				&both, NULL, &aOnly, &bOnly);

			\/\* leaves both  with \{1, 2, 2, 6, 8\} \*\/
			\/\* leaves aOnly with \{2, 2, 8\} \*\/
			\/\* leaves bOnly with \{3, 4, 6\} \*\/

			LmiVectorDestruct(LmiUint)(&bOnly);
			LmiVectorDestruct(LmiUint)(&aOnly);
			LmiVectorDestruct(LmiUint)(&both);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
/* $ Can we eliminate T_ and use LmiValueType(C_)? */
#define LmiSetIntersectionWithDifferences(I_, C_, T_)         LmiSetIntersectionWithDifferencesComp(I_, C_, LmiLess(T_))
#define Declare_LmiSetIntersectionWithDifferences(I_, C_, T_) Declare_LmiSetIntersectionWithDifferencesComp(I_, C_, LmiLess(T_))
#define Define_LmiSetIntersectionWithDifferences(I_, C_, T_)  Define_LmiSetIntersectionWithDifferencesComp(I_, C_, LmiLess(T_))

/**
{function:
	{name: LmiSetUnionComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Creates the union of two sorted sequences.
		Within each equivalence class, if there are m elements in the first sequence and n elements in the second
		sequence, then max(m,n) elements are written to the output. All m elements of the first sequence are written,
		and then if n>m the elements indexed m+1 through n of the second sequence are written.}
	{prototype: void LmiSetUnionComp(I, C, Comp)(I ai, I ae, I bi, I be, C *out)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: out}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetUnionComp must be called at global scope before calling
		this function.
	}
	{example:
		LmiBool LastDigitLess(const LmiUint *a, const LmiUint *b)
		\{
			return (*a % 10) < (*b % 10);
		\}

		Define_LmiSetUnionComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, c;

			const LmiUint ae[] = \{1, 2, 2, 12, 12, 6, 8, 18\};
			const LmiUint be[] = \{11, 12, 12, 13, 14, 16, 16, 18\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&c, LmiMallocAllocatorGetDefault());

			LmiSetUnionComp(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LastDigitLess)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b), &c);

			\/\* leaves c with \{1, 2, 2, 12, 12, 13, 14, 6, 16, 8, 18\} \*\/

			LmiVectorDestruct(LmiUint)(&c);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
#define LmiSetUnionComp(I_, C_, Comp_) LmiTemplate3(LmiSetUnionComp, I_, C_, Comp_)
#define Declare_LmiSetUnionComp(I_, C_, Comp_) \
	void LmiSetUnionComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *out);
#define Define_LmiSetUnionComp(I_, C_, Comp_)                                         \
	void LmiSetUnionComp(I_, C_, Comp_)(I_ ai, I_ ae, I_ bi, I_ be, C_ *out)          \
	{ \
		for(;;) \
		{ \
			if(LmiEqual(I_)(&ai, &ae)) \
			{ \
				while(!LmiEqual(I_)(&bi, &be)) \
				{ \
					LmiPushBack(C_)(out, LmiContentOfConst(I_)(&bi)); \
					LmiIncrement(I_)(&bi); \
				} \
				return; \
			} \
			if(LmiEqual(I_)(&bi, &be)) \
			{ \
				while(!LmiEqual(I_)(&ai, &ae)) \
				{ \
					LmiPushBack(C_)(out, LmiContentOfConst(I_)(&ai)); \
					LmiIncrement(I_)(&ai); \
				} \
				return; \
			} \
			if(Comp_(LmiContentOfConst(I_)(&bi), LmiContentOfConst(I_)(&ai))) \
			{ \
				LmiPushBack(C_)(out, LmiContentOfConst(I_)(&bi)); \
				LmiIncrement(I_)(&bi); \
			} \
			else \
			{ \
				LmiPushBack(C_)(out, LmiContentOfConst(I_)(&ai)); \
				if(!Comp_(LmiContentOfConst(I_)(&ai), LmiContentOfConst(I_)(&bi))) \
					LmiIncrement(I_)(&bi); \
				LmiIncrement(I_)(&ai); \
			} \
		} \
	}

/**
{function:
	{name: LmiSetUnion}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Creates the union of two sorted sequences.
		Within each equivalence class, if there are m elements in the first sequence and n elements in the second
		sequence, then max(m,n) elements are written to the output. All m elements of the first sequence are written,
		and then if n>m the elements indexed m+1 through n of the second sequence are written.}
	{prototype: void LmiSetUnion(I, C, T)(I ai, I ae, I bi, I be, C *out)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiInputIterator.}
	}
	{template-parameter:
		{name: C}
		{description: The type of the output container.
		The type must be a model of LmiBackInsertionSequence.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements contained in the sequences.}
	}
	{parameter:
		{name: ai}
		{description: Points to the first item in the first sequence.}
	}
	{parameter:
		{name: ae}
		{description: Points to one past the last item in the first sequence.}
	}
	{parameter:
		{name: bi}
		{description: Points to the first item in the second sequence.}
	}
	{parameter:
		{name: be}
		{description: Points to one past the last item in the second sequence.}
	}
	{parameter:
		{name: out}
		{description: Elements from the first sequence that have a matching element in the second sequence
		will be added to the end of this container.}
	}
	{note:
		The macro Define_LmiSetUnion must be called at global scope before calling
		this function.
	}
	{example:
		Define_LmiSetUnion(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)

		void f(void)
		\{
			LmiVector(LmiUint) a, b, c;

			const LmiUint ae[] = \{1, 2, 2, 2, 2, 6, 8, 8\};
			const LmiUint be[] = \{1, 2, 2, 3, 4, 6, 6, 8\};

			LmiVectorConstructRange(LmiUint)(&a, ae, ae + LmiNumElements(ae), LmiMallocAllocatorGetDefault());
			LmiVectorConstructRange(LmiUint)(&b, be, be + LmiNumElements(be), LmiMallocAllocatorGetDefault());
			LmiVectorConstructDefault(LmiUint)(&c, LmiMallocAllocatorGetDefault());

			LmiSetUnion(LmiVectorConstIterator(LmiUint), LmiVector(LmiUint), LmiUint)(
				LmiVectorBeginConst(LmiUint)(&a), LmiVectorEndConst(LmiUint)(&a),
				LmiVectorBeginConst(LmiUint)(&b), LmiVectorEndConst(LmiUint)(&b), &c);

			\/\* leaves c with \{1, 2, 2, 2, 2, 3, 4, 6, 6, 8, 8\} \*\/

			LmiVectorDestruct(LmiUint)(&c);
			LmiVectorDestruct(LmiUint)(&b);
			LmiVectorDestruct(LmiUint)(&a);
		\}
	}
}
*/
/* $ Can we eliminate T_ and use LmiValueType(C_)? */
#define LmiSetUnion(I_, C_, T_)         LmiSetUnionComp(I_, C_, LmiLess(T_))
#define Declare_LmiSetUnion(I_, C_, T_) Declare_LmiSetUnionComp(I_, C_, LmiLess(T_))
#define Define_LmiSetUnion(I_, C_, T_)  Define_LmiSetUnionComp(I_, C_, LmiLess(T_))

/**
{function:
	{name: LmiBinarySearchComp}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find an element in a sorted sequence of elements.}
	{prototype: I LmiBinarySearchComp(I, T, Comp)(I begin, I end, const T *val)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiRandomAccessIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements in the sequence.}
	}
	{template-parameter:
		{name: Comp}
		{description: The comparison function for elements.}
	}
	{parameter:
		{name: begin}
		{description: Points to the first item in the sequence.}
	}
	{parameter:
		{name: end}
		{description: Points to one past the last item in the sequence.}
	}
	{parameter:
		{name: val}
		{description: The element to search for.}
	}
	{return: Returns an iterator pointing to an element equivalent to the specified one.
		Returns end if no such element exists.
	}
	{note:
		The macro Define_LmiBinarySearchComp must be called at global scope before calling
		this function.
	}
}
*/
#define LmiBinarySearchComp(I_, T_, Comp_) LmiTemplate3(LmiBinarySearchComp, I_, T_, Comp_)
#define Declare_LmiBinarySearchComp(I_, T_, Comp_) \
	I_ LmiBinarySearchComp(I_, T_, Comp_)(I_ begin, I_ end, const T_ *val);
#define Define_LmiBinarySearchComp(I_, T_, Comp_) \
	I_ LmiBinarySearchComp(I_, T_, Comp_)(I_ begin, I_ end, const T_ *val) \
	{ \
		I_ notFound = end; \
		for(;;) \
		{ \
			LmiDifferenceType(I_) n = LmiSubtract(I_)(&end, &begin); \
			I_ mid; \
			if(n == 0) \
				return notFound; \
			mid = LmiAdd(I_)(&begin, n / 2); \
			if(Comp_(LmiContentOfConst(I_)(&mid), val)) \
				begin = LmiAdd(I_)(&mid, 1); \
			else if(Comp_(val, LmiContentOfConst(I_)(&mid))) \
				end = mid; \
			else \
				return mid; \
		} \
	}

/**
{function:
	{name: LmiBinarySearch}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Find an element in a sorted sequence of elements.}
	{prototype: I LmiBinarySearch(I, T)(I begin, I end, const T *val)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiRandomAccessIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements in the sequence.}
	}
	{parameter:
		{name: begin}
		{description: Points to the first item in the sequence.}
	}
	{parameter:
		{name: end}
		{description: Points to one past the last item in the sequence.}
	}
	{parameter:
		{name: val}
		{description: The element to search for.}
	}
	{return: Returns an iterator pointing to an element equivalent to the specified one.
		Returns end if no such element exists.
	}
	{note:
		The macro Define_LmiBinarySearch must be called at global scope before calling
		this function.
	}
}
*/
#define LmiBinarySearch(I_, T_)         LmiBinarySearchComp(I_, T_, LmiLess(T_))
#define Declare_LmiBinarySearch(I_, T_) Declare_LmiBinarySearchComp(I_, T_, LmiLess(T_))
#define Define_LmiBinarySearch(I_, T_)  Define_LmiBinarySearchComp(I_, T_, LmiLess(T_))

/**
{function:
	{name: LmiReverse}
	{parent: Algorithms}
	{include: Lmi/Utils/LmiAlgorithm.h}
	{description: Reverse a sequence of elements.}
	{prototype: void LmiReverse(I, T)(I first, I last)}
	{template-parameter:
		{name: I}
		{description: The iterator type of the input sequences.
		The iterator type must be a model of LmiBidirectionalIterator.}
	}
	{template-parameter:
		{name: T}
		{description: The type of the elements in the sequence.}
	}
	{parameter:
		{name: first}
		{description: Points to the first item in the sequence.}
	}
	{parameter:
		{name: last}
		{description: Points to one past the last item in the sequence.}
	}
	{note:
		The macro Define_LmiReverse must be called at global scope before calling
		this function.
	}
}
*/
#define LmiReverse(I_, T_) LmiTemplate2(LmiReverse, I_, T_)
#define Declare_LmiReverse(I_, T_) \
void LmiReverse(I_, T_)(I_ first_, I_ last_);
#define Define_LmiReverse(I_, T_) \
void LmiReverse(I_, T_)(I_ first_, I_ last_) { \
	while (!LmiEqual(I_)(&first_, &last_) && !LmiEqual(I_)(&first_, LmiDecrement(I_)(&last_))) { \
		LmiSwap(T_)(LmiContentOf(I_)(&first_), LmiContentOf(I_)(&last_)); \
		LmiIncrement(I_)(&first_); \
	} \
}

#endif /* LMI_ALGORITHM_H_ */
