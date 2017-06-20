
/** 
{file:
	{name: LmiIterators.h}
	{description: Iterator Concepts.}
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
#if !defined(LMI_ITERATORS_H)
#define LMI_ITERATORS_H

#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>

/**
{package:
	{name: Iterators}
	{parent: Utils}
	{include: Lmi/Utils/LmiIterators.h}
	{description: A package of generalized pointer concepts. }
}
*/

/**
{type:
	{name: LmiBaseIterator}
	{parent: Iterators}
	{description: The base iterator concept. }
	{template-prototype: LmiBaseIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define Declare_LmiBaseIteratorTypesPart(X_, T_, D_)	   \
	typedef D_ LmiDifferenceType(X_); \
	typedef T_ LmiValueType(X_); \
	typedef T_* LmiPointer(X_);

#define DeclareInline_LmiBaseIterator(X_, T_, CT_, D_, INLINE_)	   \
	DeclareInline_LmiAssignable(X_, INLINE_) \
	Declare_LmiBaseIteratorTypesPart(X_, T_, D_)

#define Declare_LmiBaseIterator(X_, T_, CT_, D_) \
	Declare_LmiAssignable(X_) \
	Declare_LmiBaseIteratorTypesPart(X_, T_, D_)

/**
{type:
	{name: LmiTrivialIterator}
	{parent: Iterators}
	{derivation-of: LmiBaseIterator}
	{description: 
		The trivial iterator concept. Adds equality, exceptional state, 
		and content-of properties to the base iterator concept.
	}
	{template-prototype: LmiTrivialIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiTrivialIteratorFuncsPart(X_, T_, CT_, INLINE_)	\
	INLINE_ X_ * LmiConstructExceptional(X_)(X_ * x); \
	INLINE_ LmiBool LmiIsExceptional(X_)(const X_ x); \
	INLINE_ T_* LmiContentOf(X_)(X_* x); \
	INLINE_ CT_* LmiContentOfConst(X_)(const X_* x);

#define DeclareInline_LmiTrivialIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiBaseIterator(X_, T_, CT_, D_, INLINE_)			\
	DeclareInline_LmiEqualityComparable(X_, INLINE_)				\
	DeclareInline_LmiTrivialIteratorFuncsPart(X_, T_, CT_, INLINE_)

#define Declare_LmiTrivialIterator(X_, T_, CT_, D_)		\
	Declare_LmiBaseIterator(X_, T_, CT_, D_)			\
	Declare_LmiEqualityComparable(X_)					\
	DeclareInline_LmiTrivialIteratorFuncsPart(X_, T_, CT_, LMI_NO_INLINE)

/**
{type:
	{name: LmiInputIterator}
	{parent: Iterators}
	{derivation-of: LmiTrivialIterator}
	{description: 
		The input iterator concept. Adds increment property to the trivial iterator concept.
	}
	{template-prototype: LmiInputIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiInputIteratorFuncsPart(X_, INLINE_)	\
	INLINE_ X_* LmiIncrement(X_)(X_* x);

#define DeclareInline_LmiInputIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiTrivialIterator(X_, T_, CT_, D_, INLINE_)		\
	DeclareInline_LmiInputIteratorFuncsPart(X_, INLINE_)

#define Declare_LmiInputIterator(X_, T_, CT_, D_)	\
	Declare_LmiTrivialIterator(X_, T_, CT_, D_)		\
	DeclareInline_LmiInputIteratorFuncsPart(X_, LMI_NO_INLINE)

/**
{type:
	{name: LmiOutputIterator}
	{parent: Iterators}
	{derivation-of: LmiBaseIterator}
	{description: 
		The output iterator concept. Adds increment and content-of properties to the base iterator concept.
	}
	{template-prototype: LmiOutputIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiOutputIteratorFuncsPart(X_, T_, INLINE_)	\
	INLINE_ X_* LmiIncrement(X_)(X_* x); \
	INLINE_ T_* LmiContentOf(X_)(X_* x);

#define DeclareInline_LmiOutputIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiBaseIterator(X_, T_, CT_, D_, INLINE_)			\
	DeclareInline_LmiOutputIteratorFuncsPart(X_, T_, INLINE_)

#define Declare_LmiOutputIterator(X_, T_, CT_, D_)				\
	Declare_LmiBaseIterator(X_, T_, CT_, D_)					\
	DeclareInline_LmiOutputIteratorFuncsPart(X_, T_, LMI_NO_INLINE)

/**
{type:
	{name: LmiForwardIterator}
	{parent: Iterators}
	{derivation-of: LmiInputIterator}
	{description: 
		The forward iterator concept. Adds output properties to the input iterator concept.
	}
	{template-prototype: LmiForwardIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiForwardIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiInputIterator(X_, T_, CT_, D_, INLINE_)
	/*DeclareInline_LmiOutputIterator(X_, T_, INLINE_)  Unneeded and causes conflict */

#define Declare_LmiForwardIterator(X_, T_, CT_, D_) \
	Declare_LmiInputIterator(X_, T_, CT_, D_)
	/*Declare_LmiOutputIterator(X_, T_)  Unneeded and causes conflict */

/**
{type:
	{name: LmiBidirectionalIterator}
	{parent: Iterators}
	{derivation-of: LmiForwardIterator}
	{description: 
		The bidirectional iterator concept. Adds decrement property to the forward iterator concept.
	}
	{template-prototype: LmiBidirectionalIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiBidirectionalIteratorFuncsPart(X_, INLINE_)	\
	INLINE_ X_* LmiDecrement(X_)(X_* x);

#define DeclareInline_LmiBidirectionalIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiForwardIterator(X_, T_, CT_, D_, INLINE_)				\
	DeclareInline_LmiBidirectionalIteratorFuncsPart(X_, INLINE_)

#define Declare_LmiBidirectionalIterator(X_, T_, CT_, D_)	\
	Declare_LmiForwardIterator(X_, T_, CT_, D_)				\
	DeclareInline_LmiBidirectionalIteratorFuncsPart(X_, LMI_NO_INLINE)

/**
{type:
	{name: LmiRandomAccessIterator}
	{parent: Iterators}
	{derivation-of: LmiBidirectionalIterator}
	{description: 
		The random access iterator concept. Adds less-than, at, increment-by-N, decrement-by-N, 
		add, and subtract properties to the bidirectional iterator concept.
	}
	{template-prototype: LmiRandomAccessIterator(X_, T_, CT_, D_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (iterator type).}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{template-parameter: 
		{name: CT_}
		{description: The read-only value type of the iterator.}
	}
	{template-parameter: 
		{name: D_}
		{description: The distance type of the iterator.}
	}
}
*/
#define DeclareInline_LmiRandomAccessIteratorFuncsPart(X_, T_, INLINE_)	\
	INLINE_ T_* LmiAt(X_)(X_* x, LmiDifferenceType(X_) n); \
	INLINE_ X_* LmiIncrementN(X_)(X_* x,  LmiDifferenceType(X_) n); \
	INLINE_ X_* LmiDecrementN(X_)(X_* x, LmiDifferenceType(X_) n); \
	INLINE_ X_ LmiAdd(X_)(X_* x, LmiDifferenceType(X_) n); \
	INLINE_ LmiDifferenceType(X_) LmiSubtract(X_)(X_* x, X_* y);

#define DeclareInline_LmiRandomAccessIterator(X_, T_, CT_, D_, INLINE_) \
	DeclareInline_LmiBidirectionalIterator(X_, T_, CT_, D_, INLINE_)	\
	DeclareInline_LmiLessThanComparable(X_, INLINE_)					\
	DeclareInline_LmiRandomAccessIteratorFuncsPart(X_, T_, INLINE_)


#define Declare_LmiRandomAccessIterator(X_, T_, CT_, D_) \
	Declare_LmiBidirectionalIterator(X_, T_, CT_, D_)	\
	Declare_LmiLessThanComparable(X_)					\
	DeclareInline_LmiRandomAccessIteratorFuncsPart(X_, T_, LMI_NO_INLINE)


/**
{function:
	{name: LmiBaseIteratorDestruct}
	{parent: LmiBaseIterator}
	{description: Destructs an iterator.}
	{prototype: void LmiBaseIteratorDestruct(T_)(LmiBaseIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be destructed.}
	}
}
*/
/**
{function:
	{name: LmiBaseIteratorConstructCopy}
	{parent: LmiBaseIterator}
	{description: Constructs an iterator from another iterator.}
	{prototype: LmiBaseIterator(T_)* LmiBaseIteratorConstructCopy(T_)(LmiBaseIterator(T_)* x, const LmiBaseIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be constructed.}
	}
	{parameter:
		{name: y}
		{description: The iterator to use to initialize the iterator being constructed.}
	}
	{return: A pointer to the constructed iterator or NULL on error.}
}
*/

/**
{function:
	{name: LmiBaseIteratorAssign}
	{parent: LmiBaseIterator}
	{description: Copy one iterator to another.}
	{prototype: LmiBaseIterator(T_)* LmiBaseIteratorAssign(T_)(LmiBaseIterator(T_)* x, const LmiBaseIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The iterator to assign to.}
	}
	{parameter:
		{name: y}
		{description: The iterator to assign from.}
	}
	{return: A pointer to the assigned to iterator or NULL on error.}
}
*/

/**
{function:
	{name: LmiBaseIteratorSwap}
	{parent: LmiBaseIterator}
	{description: Swap two iterators.}
	{prototype: LmiBool LmiBaseIteratorSwap(T_)(LmiBaseIterator(T_)* x, LmiBaseIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The iterator to swap.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
}
*/


/**
{function:
	{name: LmiTrivialIteratorEqual}
	{parent: LmiTrivialIterator}
	{description: Compares two iterators for equality.}
	{prototype: LmiBool LmiTrivialIteratorEqual(T_)(const LmiTrivialIterator(T_)* x, const LmiTrivialIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator to compare.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to compare.}
	}
	{return: LMI_TRUE if the iterators are equal or LMI_FALSE if they are not.}
}
*/
/**
{function:
	{name: LmiTrivialIteratorContentOf}
	{parent: LmiTrivialIterator}
	{description: Gets the content of the object pointed to by the iterator.}
	{prototype: T_* LmiTrivialIteratorContentOf(T_)(LmiTrivialIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator whose content is requested.}
	}
	{return: A pointer to the content of the iterator.}
}
*/
/**
{function:
	{name: LmiTrivialIteratorContentOfConst}
	{parent: LmiTrivialIterator}
	{description: Gets the read-only content of the object pointed to by the iterator.}
	{prototype: const T_* LmiTrivialIteratorContentOfConst(T_)(const LmiTrivialIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator whose content is requested.}
	}
	{return: A pointer to the read-only content of the iterator.}
}
*/
/**
{function:
	{name: LmiTrivialIteratorConstructExceptional}
	{parent: LmiTrivialIterator}
	{description: 
		Constructs an exception iterator.  Exceptional iterators are used to 
		indicate failure in cases where the normal return is an iterator.
	}
	{prototype: LmiTrivialIterator(T_)* LmiTrivialIteratorConstructExceptional(T_)(LmiTrivialIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be constructed.}
	}
	{return: A pointer to the constructed iterator or NULL on error.}
}
*/
/**
{function:
	{name: LmiTrivialIteratorIsExceptional}
	{parent: LmiTrivialIterator}
	{description: 
		Determines whether or not the iterator has encountered an exception.
	}
	{prototype: LmiBool LmiTrivialIteratorIsExceptional(T_)(const LmiTrivialIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator.}
	}
	{return: LMI_TRUE if an exception has occurred on the iterator and LMI_FALSE if no exception has occurred.}
}
*/

/* Basic (pointers) implementation of iterator concepts */
#define DefineInline_LmiTrivialIterator(X_, T_, CT_, INLINE_) \
	DefineInline_LmiDestructible(X_, INLINE_) \
	DefineInline_LmiAssignable(X_, INLINE_) \
	INLINE_ LmiBool LmiEqual(X_)(const X_* x, const X_* y) { return *x == *y; } \
	INLINE_ T_* LmiContentOf(X_)(X_* x) {  return (T_*)(*x); } \
	INLINE_ CT_* LmiContentOfConst(X_)(const X_* x) { return (CT_*)(*x); } \
	INLINE_ X_* LmiConstructExceptional(X_)(X_ * x) { *x = NULL; return x; } \
	INLINE_ LmiBool LmiIsExceptional(X_)(const X_ x) { return x == NULL; }


/**
{function:
	{name: LmiInputIteratorIncrement}
	{parent: LmiInputIterator}
	{description: 
		Increments the iterator to point at the next object in the 
		container.  No checking is performed to ensure that the iterator is in
		range of the container after the operation.
	}
	{prototype: LmiInputIterator(T_)* LmiInputIteratorIncrement(T_)(LmiInputIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be incremented.}
	}
	{return: A pointer to the iterator after it has been incremented.}
}
*/

#define DefineInline_LmiInputIterator(X_, T_, CT_, INLINE_) \
	DefineInline_LmiTrivialIterator(X_, T_, CT_, INLINE_) \
	INLINE_ X_* LmiIncrement(X_)(X_* x) { ++(*x); return x; }

#define DefineInline_LmiOutputIterator(X_, T_, CT_, INLINE_) \
	INLINE_ X_* LmiConstructCopy(X_)(X_* x, const X_* y) { *x = *y; return x; } \
	INLINE_ X_* LmiAssign(X_)(X_* x, X_* y) { *x = *y; return x; } \
	INLINE_ LmiBool LmiSwap(X_)(X_* x, X_* y) { X_ z = *x; *x = *y; *y = z; return LMI_TRUE; } \
	INLINE_ X_* LmiIncrement(X_)(X_* x) { ++(*x); return x; } \
	INLINE_ T_* LmiContentOf(X_)(X_* x) { return (T_*)(*x); }

#define DefineInline_LmiForwardIterator(X_, T_, CT_, INLINE_) \
	DefineInline_LmiInputIterator(X_, T_, CT_, INLINE_)
	/* Define_LmiOutputIterator(X_, T_, CT_) Unneeded and causes conflict */

/**
{function:
	{name: LmiBidirectionalIteratorDecrement}
	{parent: LmiBidirectionalIterator}
	{description: 
		Decrements the iterator to point at the previous object in the 
		container.  No checking is perform to ensure that the iterator is in
		range of the container after the operation.
	}
	{prototype: LmiBidirectionalIterator(T_)* LmiBidirectionalIteratorDecrement(T_)(LmiBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be incremented.}
	}
	{return: A pointer to the iterator after it has been decremented.}
}
*/
#define DefineInline_LmiBidirectionalIterator(X_, T_, CT_, INLINE_) \
	DefineInline_LmiForwardIterator(X_, T_, CT_, INLINE_) \
	INLINE_ X_* LmiDecrement(X_)(X_* x) { --(*x); return x; }


/**
{function:
	{name: LmiRandomAccessIteratorLess}
	{parent: LmiRandomAccessIterator}
	{description: 
		Test whether one iterator is lexicographically less than another.
	}
	{prototype: LmiBool LmiRandomAccessIteratorLess(T_)(const LmiRandomAccessIterator(T_)* x, const LmiRandomAccessIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator to compare.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to compare.}
	}
	{return: LMI_TRUE if the first iterator is lexicographically less than the second iterator or LMI_FALSE if it is not.}
}
*/
/**
{function:
	{name: LmiRandomAccessIteratorAt}
	{parent: LmiRandomAccessIterator}
	{description: Retrieve a pointer to an element of the iterator's value type at an offset from the iterator.}
	{prototype: T_* LmiRandomAccessIteratorAt(T_)(LmiRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	}
	{parameter:
		{name: n}
		{description: The offset from the iterator to the element to retrieve.}
	}
	{return: A pointer to the element retrieved.}
}
*/

/**
{function:
	{name: LmiRandomAccessIteratorIncrementN}
	{parent: LmiRandomAccessIterator}
	{description: Increment the iterator by {italic:n}.}
	{prototype: LmiRandomAccessIterator(T_)* LmiRandomAccessIteratorIncrementN(T_)(LmiRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	} 
	{parameter:
		{name: n}
		{description: The distance to increment the iterator by.}
	}
	{return: A pointer to the incremented iterator.}
}
*/

/**
{function:
	{name: LmiRandomAccessIteratorDecrementN}
	{parent: LmiRandomAccessIterator}
	{description: Decrement the iterator by {italic:n}.}
	{prototype: LmiRandomAccessIterator(T_)* LmiRandomAccessIteratorDecrementN(T_)(LmiRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	} 
	{parameter:
		{name: n}
		{description: The distance to decrement the iterator by.}
	}
	{return: A pointer to the decremented iterator.}
}
*/

/**
{function:
	{name: LmiRandomAccessIteratorAdd}
	{parent: LmiRandomAccessIterator}
	{description: Return an iterator to the element {italic:n} elements from the iterator.}
	{prototype: LmiRandomAccessIterator(T_) LmiRandomAccessIteratorAdd(T_)(LmiRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator from which the new iterator is based.}
	} 
	{parameter:
		{name: n}
		{description: The distance from iterator {italic:x} the new iterator should point.}
	}
	{return: A new iterator pointing to an element {italic:n} elements from the iterator {italic:x}.}
}
*/
/**
{function:
	{name: LmiRandomAccessIteratorSubtract}
	{parent: LmiRandomAccessIterator}
	{description: Find the distance between two iterators.}
	{prototype: LmiDifferenceType(T_) LmiRandomAccessIteratorSubtract(T_)(LmiRandomAccessIterator(T_)* x, LmiRandomAccessIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The minuend iterator.}
	} 
	{parameter:
		{name: y}
		{description: The subtrahend iterator.}
	}
	{return: The distance in value type elements.}
}
*/

#define DefineInline_LmiRandomAccessIterator(X_, T_, CT_, INLINE_) \
	DefineInline_LmiBidirectionalIterator(X_, T_, CT_, INLINE_) \
	INLINE_ LmiBool LmiLess(X_)(const X_* x, const X_* y) { return *x < *y; } \
	INLINE_ T_* LmiAt(X_)(X_* x, LmiDifferenceType(X_) n) { return (T_*)(*x + n); } \
	INLINE_ X_* LmiIncrementN(X_)(X_* x, LmiDifferenceType(X_) n) { *x += n; return x; } \
	INLINE_ X_* LmiDecrementN(X_)(X_* x, LmiDifferenceType(X_) n) { *x -= n; return x; } \
	INLINE_ X_ LmiAdd(X_)(X_* x, LmiDifferenceType(X_) n) { return (*x + n); } \
	INLINE_ LmiDifferenceType(X_) LmiSubtract(X_)(X_* x, X_* y) { return *x - *y; }

/* Non-inline versions of basic iterator definitions. */
#define Define_LmiTrivialIterator(X_, T_, CT_) \
  DefineInline_LmiTrivialIterator(X_, T_, CT_, LMI_NO_INLINE)

#define Define_LmiInputIterator(X_, T_, CT_) \
  DefineInline_LmiInputIterator(X_, T_, CT_, LMI_NO_INLINE)

#define Define_LmiOutputIterator(X_, T_, CT_) \
  DefineInline_LmiOutputIterator(X_, T_, CT_, LMI_NO_INLINE)

#define Define_LmiForwardIterator(X_, T_, CT_) \
  DefineInline_LmiForwardIterator(X_, T_, CT_, LMI_NO_INLINE)

#define Define_LmiBidirectionalIterator(X_, T_, CT_) \
  DefineInline_LmiBidirectionalIterator(X_, T_, CT_, LMI_NO_INLINE)

#define Define_LmiRandomAccessIterator(X_, T_, CT_) \
  DefineInline_LmiRandomAccessIterator(X_, T_, CT_, LMI_NO_INLINE)
	
/**
{type:
	{name: LmiReverseBidirectionalIterator}
	{parent: Iterators}
	{description: The reverse bidirectional iterator concept.}
	{template-prototype: LmiReverseBidirectionalIterator(X_, F_, T_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (reverse iterator type).}
	}
	{template-parameter: 
		{name: F_}
		{description: The forward iterator type upon which the reverse iterator is to be based.}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorDestruct}
	{parent: LmiReverseBidirectionalIterator}
	{description: Destructs an iterator.}
	{prototype: void LmiReverseBidirectionalIteratorDestruct(T_)(LmiBaseIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be destructed.}
	}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorConstructCopy}
	{parent: LmiReverseBidirectionalIterator}
	{description: Constructs an iterator from another iterator.}
	{prototype: LmiReverseBidirectionalIterator(T_)* LmiReverseBidirectionalIteratorConstructCopy(T_)(LmiReverseBidirectionalIterator(T_)* x, const LmiReverseBidirectionalIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be constructed.}
	}
	{parameter:
		{name: y}
		{description: The iterator to use to initialize the iterator being constructed.}
	}
	{return: A pointer to the constructed iterator or NULL on error.}
}
*/

/**
{function:
	{name: LmiReverseBidirectionalIteratorAssign}
	{parent: LmiReverseBidirectionalIterator}
	{description: Copy one iterator to another.}
	{prototype: LmiReverseBidirectionalIterator(T_)* LmiReverseBidirectionalIteratorAssign(T_)(LmiReverseBidirectionalIterator(T_)* x, const LmiReverseBidirectionalIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The iterator to assign to.}
	}
	{parameter:
		{name: y}
		{description: The iterator to assign from.}
	}
	{return: A pointer to the assigned to iterator or NULL on error.}
}
*/

/**
{function:
	{name: LmiReverseBidirectionalIteratorSwap}
	{parent: LmiReverseBidirectionalIterator}
	{description: Swap two iterators.}
	{prototype: LmiBool LmiReverseBidirectionalIteratorSwap(T_)(LmiReverseBidirectionalIterator(T_)* x, LmiReverseBidirectionalIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The type stored in the vector.}
	}
	{parameter:
		{name: x}
		{description: The iterator to swap.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to swap.}
	}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
}
*/


/**
{function:
	{name: LmiReverseBidirectionalIteratorEqual}
	{parent: LmiReverseBidirectionalIterator}
	{description: Compares two iterators for equality.}
	{prototype: LmiBool LmiReverseBidirectionalIteratorEqual(T_)(const LmiReverseBidirectionalIterator(T_)* x, const LmiReverseBidirectionalIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator to compare.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to compare.}
	}
	{return: LMI_TRUE if the iterators are equal or LMI_FALSE if they are not.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorContentOf}
	{parent: LmiReverseBidirectionalIterator}
	{description: Gets the content of the object pointed to by the iterator.}
	{prototype: T_* LmiReverseBidirectionalIteratorContentOf(T_)(LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator whose content is requested.}
	}
	{return: A pointer to the content of the iterator.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorContentOfConst}
	{parent: LmiReverseBidirectionalIterator}
	{description: Gets the read-only content of the object pointed to by the iterator.}
	{prototype: const T_* LmiReverseBidirectionalIteratorContentOfConst(T_)(const LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator whose content is requested.}
	}
	{return: A pointer to the read-only content of the iterator.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorConstructExceptional}
	{parent: LmiReverseBidirectionalIterator}
	{description: 
		Constructs an exception iterator.  Exceptional iterators are used to 
		indicate failure in cases where the normal return is an iterator.
	}
	{prototype: LmiReverseBidirectionalIterator(T_)* LmiReverseBidirectionalIteratorConstructExceptional(T_)(LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be constructed.}
	}
	{return: A pointer to the constructed iterator or NULL on error.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorIsExceptional}
	{parent: LmiReverseBidirectionalIterator}
	{description: 
		Determines whether or not the iterator has encountered an exception.
	}
	{prototype: LmiBool LmiReverseBidirectionalIteratorIsExceptional(T_)(const LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator.}
	}
	{return: LMI_TRUE if an exception has occurred on the iterator and LMI_FALSE if no exception has occurred.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorIncrement}
	{parent: LmiReverseBidirectionalIterator}
	{description: 
		Increments the iterator to point at the next object in the 
		reverse container.  No checking is perform to ensure that the iterator is in
		range of the container after the operation.
	}
	{prototype: LmiReverseBidirectionalIterator(T_)* LmiReverseBidirectionalIteratorIncrement(T_)(LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be incremented.}
	}
	{return: A pointer to the iterator after it has been incremented.}
}
*/
/**
{function:
	{name: LmiReverseBidirectionalIteratorDecrement}
	{parent: LmiReverseBidirectionalIterator}
	{description: 
		Decrements the iterator to point at the previous object in the 
		reverse container.  No checking is perform to ensure that the iterator is in
		range of the container after the operation.
	}
	{prototype: LmiReverseBidirectionalIterator(T_)* LmiReverseBidirectionalIteratorDecrement(T_)(LmiReverseBidirectionalIterator(T_)* x)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter: 
		{name: x}
		{description: The iterator to be incremented.}
	}
	{return: A pointer to the iterator after it has been decremented.}
}
*/
#define DefineInline_LmiReverseBidirectionalIterator(X_, F_, T_, CT_, INLINE_) \
	INLINE_ void LmiDestruct(X_)(X_* x) { LmiDestruct(F_)(x); } \
	INLINE_ X_* LmiConstructCopy(X_)(X_* x, const X_* y) { return LmiConstructCopy(F_)(x, y); } \
	INLINE_ X_* LmiAssign(X_)(X_* x, const X_* y) { return LmiAssign(F_)(x, y); } \
	INLINE_ LmiBool LmiSwap(X_)(X_* x, X_* y) { return LmiSwap(F_)(x, y); } \
	INLINE_ LmiBool LmiEqual(X_)(const X_* x, const X_* y) { return LmiEqual(F_)(x, y); } \
	INLINE_ T_* LmiContentOf(X_)(X_* x) { \
		F_ tmp; \
		T_* ret; \
		LmiConstructCopy(F_)(&tmp, x); \
		LmiDecrement(F_)(&tmp); \
		ret = LmiContentOf(F_)(&tmp); \
		LmiDestruct(F_)(&tmp); \
		return ret; \
	} \
	INLINE_ CT_* LmiContentOfConst(X_)(const X_* x) { \
		F_ tmp; \
		CT_* ret; \
		LmiConstructCopy(F_)(&tmp, x); \
		LmiDecrement(F_)(&tmp); \
		ret = LmiContentOfConst(F_)(&tmp); \
		LmiDestruct(F_)(&tmp); \
		return ret; \
	} \
	INLINE_ X_* LmiIncrement(X_)(X_* x) { return LmiDecrement(F_)(x); } \
	INLINE_ X_* LmiDecrement(X_)(X_* x) { return LmiIncrement(F_)(x); } \
	INLINE_ X_* LmiConstructExceptional(X_)(X_* x) { return LmiConstructExceptional(F_)(x); } \
	INLINE_ LmiBool LmiIsExceptional(X_)(const X_ x) { return LmiIsExceptional(F_)(x); }
 

/**
{type:
	{name: LmiReverseRandomAccessIterator}
	{parent: Iterators}
	{description: The reverse random access iterator concept.}
	{template-prototype: LmiReverseRandomAccessIterator(X_, F_, T_) }
	{template-parameter: 
		{name: X_}
		{description: The model name (reverse iterator type).}
	}
	{template-parameter: 
		{name: F_}
		{description: The forward iterator type upon which the reverse iterator is to be based.}
	}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
}
*/
/**
{function:
	{name: LmiReverseRandomAccessIteratorLess}
	{parent: LmiReverseRandomAccessIterator}
	{description: 
		Test whether one iterator is lexicographically less than another.
	}
	{prototype: LmiBool LmiReverseRandomAccessIteratorLess(T_)(const LmiReverseRandomAccessIterator(T_)* x, const LmiReverseRandomAccessIterator(T_)* y)}
	{template-parameter: 
		{name: T_}
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator to compare.}
	}
	{parameter:
		{name: y}
		{description: The other iterator to compare.}
	}
	{return: LMI_TRUE if the first iterator is lexicographically less than the second iterator or LMI_FALSE if it is not.}
}
*/
/**
{function:
	{name: LmiReverseRandomAccessIteratorAt}
	{parent: LmiReverseRandomAccessIterator}
	{description: Retrieve a pointer to an element of the iterator's value type at an offset from the iterator.}
	{prototype: T_* LmiReverseRandomAccessIteratorAt(T_)(LmiReverseRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	}
	{parameter:
		{name: n}
		{description: The offset from the iterator to the element to retrieve.}
	}
	{return: A pointer to the element retrieved.}
}
*/

/**
{function:
	{name: LmiReverseRandomAccessIteratorIncrementN}
	{parent: LmiReverseRandomAccessIterator}
	{description: Increment the iterator by {italic:n}.}
	{prototype: LmiReverseRandomAccessIterator(T_)* LmiReverseRandomAccessIteratorIncrementN(T_)(LmiReverseRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	} 
	{parameter:
		{name: n}
		{description: The distance to increment the iterator by.}
	}
	{return: A pointer to the incremented iterator.}
}
*/

/**
{function:
	{name: LmiReverseRandomAccessIteratorDecrementN}
	{parent: LmiReverseRandomAccessIterator}
	{description: Decrement the iterator by {italic:n}.}
	{prototype: LmiReverseRandomAccessIterator(T_)* LmiReverseRandomAccessIteratorDecrementN(T_)(LmiReverseRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator.}
	} 
	{parameter:
		{name: n}
		{description: The distance to decrement the iterator by.}
	}
	{return: A pointer to the decremented iterator.}
}
*/

/**
{function:
	{name: LmiReverseRandomAccessIteratorAdd}
	{parent: LmiReverseRandomAccessIterator}
	{description: Return an iterator to the element {italic:n} elements from the iterator.}
	{prototype: LmiReverseRandomAccessIterator(T_) LmiReverseRandomAccessIteratorAdd(T_)(LmiReverseRandomAccessIterator(T_)* x, LmiSizeType(T_) n)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The iterator from which the new iterator is based.}
	} 
	{parameter:
		{name: n}
		{description: The distance from iterator {italic:x} the new iterator should point.}
	}
	{return: A new iterator pointing to an element {italic:n} elements from the iterator {italic:x}.}
}
*/
/**
{function:
	{name: LmiReverseRandomAccessIteratorSubtract}
	{parent: LmiReverseRandomAccessIterator}
	{description: Find the distance between two iterators.}
	{prototype: LmiDifferenceType(T_) LmiReverseRandomAccessIteratorSubtract(T_)(LmiReverseRandomAccessIterator(T_)* x, LmiReverseRandomAccessIterator(T_)* y)}
	{template-parameter:
		{name: T_} 
		{description: The value type of the iterator.}
	}
	{parameter:
		{name: x}
		{description: The minuend iterator.}
	} 
	{parameter:
		{name: y}
		{description: The subtrahend iterator.}
	}
	{return: The distance in value type elements.}
}
*/

#define DefineInline_LmiReverseRandomAccessIterator(X_, F_, T_, CT_, INLINE_) \
	DefineInline_LmiReverseBidirectionalIterator(X_, F_, T_, CT_, INLINE_) \
	INLINE_ LmiBool LmiLess(X_)(const X_* x, const X_* y) { return LmiLess(F_)(y, x); } \
	INLINE_ X_* LmiIncrementN(X_)(X_* x, LmiDifferenceType(X_) n) { return LmiDecrementN(F_)(x, n); } \
	INLINE_ X_* LmiDecrementN(X_)(X_* x, LmiDifferenceType(X_) n) { return LmiIncrementN(F_)(x, n); } \
	INLINE_ X_ LmiAdd(X_)(X_* x, LmiDifferenceType(X_) n) { return LmiAdd(F_)(x, -n); } \
	INLINE_ T_* LmiAt(X_)(X_* x, LmiDifferenceType(X_) n) { \
		X_ tmp; \
		T_* ret; \
		LmiConstructCopy(X_)(&tmp, x); \
		LmiIncrementN(X_)(&tmp, n); \
		ret = LmiContentOf(X_)(&tmp); \
		LmiDestruct(X_)(&tmp); \
		return ret; \
	} \
	INLINE_ LmiDifferenceType(X_) LmiSubtract(X_)(X_* x, X_* y) { return LmiSubtract(F_)(y, x); }

#endif
