/**
   {file: 
     {name: LmiList.h}
     {description: LMI container class for generic doubly-linked lists.}
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

#ifndef LMI_LIST_H_
#define LMI_LIST_H_

/**
   {type visibility="private":
     {name: LmiList}
     {parent: Containers}
     {include: Lmi/Utils/LmiList.h}
     {description: Container class for doubly-linked lists.}
     {template-prototype: LmiList(T)}
     {template-parameter:
       {name: T}
       {description: The type stored in the list.}}
     {note: This is an LmiReversibleContainer, LmiFrontInsertionSequence,
            and LmiBackInsertionSequence; see LmiContainers and the STL.}
   }
*/

/**
{type visibility="private":
	{name: LmiListIterator}
	{parent: LmiList}
	{description: The iterator type of a list.}
	{template-prototype: LmiListIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the list.}
	}
	{note: This is a model of LmiBidirectionalIterator; see LmiContainers
		and the STL.}
	{note: 
		The macro Declare_LmiList must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type visibility="private":
	{name: LmiListConstIterator}
	{parent: LmiList}
	{description: The read-only iterator type of a list.}
	{template-prototype: LmiListConstIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the list.}
	}
	{note: This is a model of LmiBidirectionalIterator; see LmiContainers
		and the STL.}
	{note: 
		The macro Declare_LmiList must be called before declaring an 
		object of this type.  
	}
}
*/
/**
{type visibility="private":
	{name: LmiListReverseIterator}
	{parent: LmiList}
	{description: The reverse iterator type of a list.}
	{template-prototype: LmiListReverseIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the list.}
	}
	{note: This is a model of LmiReverseBidirectionalIterator; see
		LmiContainers and the STL.}
	{note: 
		The macro Declare_LmiList must be called before declaring an 
		object of this type.  
	}
}
*/

/**
{type visibility="private":
	{name: LmiListConstReverseIterator}
	{parent: LmiList}
	{description: The read-only reverse iterator type of a list.}
	{template-prototype: LmiListConstReverseIterator(T_)}
	{template-parameter:
		{name: T_}
		{description: The type stored in the list.}
	}
	{note: This is a model of LmiReverseBidirectionalIterator; see
		LmiContainers and the STL.}
	{note: 
		The macro Declare_LmiList must be called before declaring an 
		object of this type.  
	}
}
*/



#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiContainers.h>
#include <Lmi/Utils/LmiAllocator.h>
#include <Lmi/Utils/LmiAssert.h>

LMI_BEGIN_EXTERN_C

/* List names: */
#define LmiList(T_) LmiTemplate1(LmiList,T_)
#define LmiListFunc_(T_,Func_) LmiClassFunc(LmiList(T_),Func_)

/* Private templatized member functions of LmiList: */
#define LmiListCreateNode_(T_)      LmiListFunc_(T_, CreateNode_)
#define LmiListHookNode_(T_)        LmiListFunc_(T_, HookNode_)
#define LmiListUnhookNode_(T_)      LmiListFunc_(T_, UnhookNode_)


/* Public templatized member functions of LmiList: */
#define LmiListConstructDefault(T_) LmiConstructDefault(LmiList(T_))
#define LmiListDestruct(T_)         LmiDestruct(LmiList(T_))
#define LmiListConstructCopy(T_)    LmiConstructCopy(LmiList(T_))
#define LmiListGetAllocator(T_)		LmiGetAllocator(LmiList(T_))

#define LmiListAssign(T_)	LmiAssign(LmiList(T_))
#define LmiListSwap(T_)	LmiSwap(LmiList(T_))
#define LmiListEqual(T_)	LmiEqual(LmiList(T_))
#define LmiListLess(T_)	LmiLess(LmiList(T_))
#define LmiListEqualComp(T_, Comp_)   LmiClassTemplateFunc1(LmiList(T_), EqualComp, Comp_)
#define LmiListLessComp(T_, Comp_)    LmiClassTemplateFunc1(LmiList(T_), LessComp, Comp_)

#define LmiListBegin(T_)	LmiBegin(LmiList(T_))
#define LmiListBeginConst(T_)	LmiBeginConst(LmiList(T_))
#define LmiListEnd(T_)	LmiEnd(LmiList(T_))
#define LmiListEndConst(T_)	LmiEndConst(LmiList(T_))
#define LmiListSize(T_)	LmiSize(LmiList(T_))
#define LmiListMaxSize(T_)	LmiMaxSize(LmiList(T_))
#define LmiListEmpty(T_)	LmiEmpty(LmiList(T_))

#define LmiListRBegin(T_)	LmiRBegin(LmiList(T_))
#define LmiListRBeginConst(T_)	LmiRBeginConst(LmiList(T_))
#define LmiListREnd(T_)	LmiREnd(LmiList(T_))
#define LmiListREndConst(T_)	LmiREndConst(LmiList(T_))

#define LmiListConstructN(T_)	LmiConstructN(LmiList(T_))
#define LmiListConstructRange(T_)	LmiConstructRange(LmiList(T_))
#define LmiListFront(T_)	LmiFront(LmiList(T_))
#define LmiListFrontConst(T_)	LmiFrontConst(LmiList(T_))
#define LmiListInsert(T_)	LmiInsert(LmiList(T_))
#define LmiListInsertN(T_)	LmiInsertN(LmiList(T_))
#define LmiListInsertRange(T_)	LmiInsertRange(LmiList(T_))
#define LmiListErase(T_)	LmiErase(LmiList(T_))
#define LmiListEraseRange(T_)	LmiEraseRange(LmiList(T_))
#define LmiListClear(T_)	LmiClear(LmiList(T_))
#define LmiListResize(T_)	LmiResize(LmiList(T_))

#define LmiListPushFront(T_)	LmiPushFront(LmiList(T_))
#define LmiListPopFront(T_)	LmiPopFront(LmiList(T_))

#define LmiListBack(T_)	LmiBack(LmiList(T_))
#define LmiListBackConst(T_)	LmiBackConst(LmiList(T_))
#define LmiListPushBack(T_)	LmiPushBack(LmiList(T_))
#define LmiListPopBack(T_)	LmiPopBack(LmiList(T_))

#define LmiListSpliceOne(T_)	LmiListFunc_(T_, SpliceOne)
#define LmiListSplice(T_)	LmiListFunc_(T_, Splice)

#define LmiListGetNodeSize(T_) LmiListFunc_(T_, GetNodeSize)

#define LmiListConstructIteratorRange(T_, InputIterator_)	LmiConstructIteratorRange(LmiList(T_), InputIterator_)
#define LmiListInsertIteratorRange(T_, InputIterator_)	LmiInsertIteratorRange(LmiList(T_), InputIterator_)

/* These additional STL functions can be added if and when needed:
   Remove
   RemoveIf
   
   Unique
   Merge
   Reverse
*/


/* List node names: */
#define LmiListNode_(T_) LmiTemplate1(LmiListNode_,T_)
#define LmiListNodeBase_(T_) LmiTemplate1(LmiListNodeBase_,T_)
#define LmiListNodePtr_(T_) LmiTemplate1(LmiListNodePtr_,T_)

/* List iterator names: */
#define LmiListIterator(T_) LmiIterator(LmiList(T_))
#define LmiListConstIterator(T_) LmiConstIterator(LmiList(T_))
#define LmiListReverseIterator(T_) LmiReverseIterator(LmiList(T_))
#define LmiListConstReverseIterator(T_) LmiConstReverseIterator(LmiList(T_))

/* Public templatized member functions of LmiListIterator */
#define LmiListIteratorConstruct(T_)	LmiConstruct(LmiListIterator(T_))
#define LmiListIteratorDestruct(T_)	LmiDestruct(LmiListIterator(T_))
#define LmiListIteratorConstructCopy(T_)	LmiConstructCopy(LmiListIterator(T_))
#define LmiListIteratorAssign(T_)	LmiAssign(LmiListIterator(T_))
#define LmiListIteratorSwap(T_)	LmiSwap(LmiListIterator(T_))
#define LmiListIteratorEqual(T_)	LmiEqual(LmiListIterator(T_))
#define LmiListIteratorContentOf(T_)	LmiContentOf(LmiListIterator(T_))
#define LmiListIteratorContentOfConst(T_)	LmiContentOfConst(LmiListIterator(T_))
#define LmiListIteratorIncrement(T_)	LmiIncrement(LmiListIterator(T_))
#define LmiListIteratorDecrement(T_)	LmiDecrement(LmiListIterator(T_))
#define LmiListIteratorConstructExceptional(T_)	LmiConstructExceptional(LmiListIterator(T_))
#define LmiListIteratorIsExceptional(T_)	LmiIsExceptional(LmiListIterator(T_))

/* Public templatized member functions of LmiListConstIterator */
#define LmiListConstIteratorConstruct(T_)	LmiConstruct(LmiListConstIterator(T_))
#define LmiListConstIteratorDestruct(T_)	LmiDestruct(LmiListConstIterator(T_))
#define LmiListConstIteratorConstructCopy(T_)	LmiConstructCopy(LmiListConstIterator(T_))
#define LmiListConstIteratorAssign(T_)	LmiAssign(LmiListConstIterator(T_))
#define LmiListConstIteratorSwap(T_)	LmiSwap(LmiListConstIterator(T_))
#define LmiListConstIteratorEqual(T_)	LmiEqual(LmiListConstIterator(T_))
#define LmiListConstIteratorContentOf(T_)	LmiContentOf(LmiListConstIterator(T_))
#define LmiListConstIteratorContentOfConst(T_)	LmiContentOfConst(LmiListConstIterator(T_))
#define LmiListConstIteratorIncrement(T_)	LmiIncrement(LmiListConstIterator(T_))
#define LmiListConstIteratorDecrement(T_)	LmiDecrement(LmiListConstIterator(T_))
#define LmiListConstIteratorConstructExceptional(T_)	LmiConstructExceptional(LmiListConstIterator(T_))
#define LmiListConstIteratorIsExceptional(T_)	LmiIsExceptional(LmiListConstIterator(T_))

/* Public templatized member functions of LmiListIterator */
#define LmiListReverseIteratorConstruct(T_)	LmiConstruct(LmiListReverseIterator(T_))
#define LmiListReverseIteratorDestruct(T_)	LmiDestruct(LmiListReverseIterator(T_))
#define LmiListReverseIteratorConstructCopy(T_)	LmiConstructCopy(LmiListReverseIterator(T_))
#define LmiListReverseIteratorAssign(T_)	LmiAssign(LmiListReverseIterator(T_))
#define LmiListReverseIteratorSwap(T_)	LmiSwap(LmiListReverseIterator(T_))
#define LmiListReverseIteratorEqual(T_)	LmiEqual(LmiListReverseIterator(T_))
#define LmiListReverseIteratorContentOf(T_)	LmiContentOf(LmiListReverseIterator(T_))
#define LmiListReverseIteratorContentOfConst(T_)	LmiContentOfConst(LmiListReverseIterator(T_))
#define LmiListReverseIteratorIncrement(T_)	LmiIncrement(LmiListReverseIterator(T_))
#define LmiListReverseIteratorDecrement(T_)	LmiDecrement(LmiListReverseIterator(T_))
#define LmiListReverseIteratorConstructExceptional(T_)	LmiConstructExceptional(LmiListReverseIterator(T_))
#define LmiListReverseIteratorIsExceptional(T_)	LmiIsExceptional(LmiListReverseIterator(T_))

/* Public templatized member functions of LmiListConstReverseIterator */
#define LmiListConstReverseIteratorConstruct(T_)	LmiConstruct(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorDestruct(T_)	LmiDestruct(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorConstructCopy(T_)	LmiConstructCopy(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorAssign(T_)	LmiAssign(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorSwap(T_)	LmiSwap(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorEqual(T_)	LmiEqual(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorContentOf(T_)	LmiContentOf(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorContentOfConst(T_)	LmiContentOfConst(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorIncrement(T_)	LmiIncrement(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorDecrement(T_)	LmiDecrement(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorConstructExceptional(T_)	LmiConstructExceptional(LmiListConstReverseIterator(T_))
#define LmiListConstReverseIteratorIsExceptional(T_)	LmiIsExceptional(LmiListConstReverseIterator(T_))


/**
   {type visibility="internal":
     {name: LmiListNodeBase_}
     {parent: LmiList}
     {description: The "base type" for a list node.  This shares a common
     structure prefix with an LmiListNode(T_) object, but omits the {code:
     obj_} member.  This is kept internally in the LmiList object to simplify
     the code by maintaining a circular list.}
	 {template-prototype: LmiListNodeBase_(T_)}
	 {template-parameter: {name: T_} {description: The type stored in the list.}}
     {member: {name: prev_} {type: LmiListNode_(T_)*}
       {description: The previous node in the list, i.e. the tail of the list.}}
     {member: {name: next_} {type: LmiListNode_(T_)*}
       {description: The next node in the list, i.e. the head of the list.}}
   }
*/

/**
   {type visibility="internal":
   {name: LmiListNode_}
   {parent: LmiList}
   {description: One node in an LmiList.}
   {template-prototype: LmiListNode_(T_)}
   {template-parameter: {name: T_} {description: The type stored in the list.}}
   {member: {name: prev_} {type: LmiListNode(T_)*}
   {description: The previous node in the list.}}
   {member: {name: next_} {type: LmiListNode(T_)*}
   {description: The next node in the list.}}
   {member: {name: obj_} {type: T_}
   {description: The object stored in this node.}}
   }
*/
#define Declare_LmiListNode(T_) \
typedef union LmiListNodePtr_(T_) { \
	struct LmiListNode_(T_)* n;			\
	struct LmiListNodeBase_(T_)* b;				\
} LmiListNodePtr_(T_);							\
\
typedef struct LmiListNodeBase_(T_) { \
  union LmiListNodePtr_(T_) prev; \
  union LmiListNodePtr_(T_) next; \
} LmiListNodeBase_(T_); \
\
typedef struct LmiListNode_(T_) { \
  LmiListNodeBase_(T_) b; \
  T_ obj; \
} LmiListNode_(T_);

#define Declare_LmiListClass(T_) \
typedef struct { \
  LmiListNodeBase_(T_) node;	\
  LmiAllocator * allocator; \
} LmiList(T_);



/**
   {function visibility="internal":
    {name: LmiListCreateNode_}
    {parent: LmiList}
    {description: Create a list node with value given.}
    {prototype: LmiListNode_(T_)* LmiListCreateNode_(T_)(LmiList(T_)* l, const T_* t)}
    {template-parameter:
      {name: T_} {description: The type stored in the list.}}
    {parameter: {name: l} {description: The list.}}
    {parameter: {name: t} {description: The value of the node's object.}}
    {return: The newly-created node, or NULL on allocator or
      copy-constructor failure.}
   } 
*/
#define Declare_LmiListCreateNode_(T_) \
  LMI_INLINE_DECLARATION LmiListNode_(T_)* LmiListCreateNode_(T_)(LmiList(T_) * l_, const T_* t_);

#define DefineInline_LmiListCreateNode_(T_, INLINE_)                    \
  INLINE_ LmiListNode_(T_)* LmiListCreateNode_(T_)(LmiList(T_) * l_,    \
                                                   const T_* t_)        \
  {                                                                     \
    LmiListNode_(T_) * p_ =                                             \
      (LmiListNode_(T_)*)LmiAllocatorAllocate(l_->allocator,            \
                                              sizeof(LmiListNode_(T_))); \
    if (p_ == NULL) {                                                   \
      return NULL;                                                      \
    }                                                                   \
    if (!LmiConstructCopy(T_)(&p_->obj, t_)) {                          \
      LmiAllocatorDeallocate(l_->allocator, p_,                         \
                             sizeof(LmiListNode_(T_)));                 \
      return NULL;                                                      \
    }                                                                   \
    return p_;                                                          \
  }

/**
   {function visibility="internal":
     {name: LmiListHookNode_}
     {parent: LmiList}
     {description: Hook a list node into the list.}
     {prototype: void LmiListHookNode_(T_)(LmiListNodeBase_* node, LmiListNodeBase_* pos)}
     {template-parameter:
       {name: T_} {description: The type stored in the list.}}
     {parameter: {name: node} {description: The node to hook into the list.}}
     {parameter: {name: pos} {description: The position to hook into the list.}}
   }
*/
#define Declare_LmiListHookNode_(T_) \
  LMI_INLINE_DECLARATION void LmiListHookNode_(T_)(LmiListNode_(T_) *node, LmiListNodeBase_(T_) *pos);

#define DefineInline_LmiListHookNode_(T_, INLINE_)						\
  INLINE_ void LmiListHookNode_(T_)(LmiListNode_(T_)* node,				\
	  LmiListNodeBase_(T_)* pos)										\
  {																		\
	node->b.next.b = pos;												\
	node->b.prev = pos->prev;											\
	pos->prev.b->next.b = &node->b;										\
	pos->prev.b = &node->b;												\
  }


/**
   {function visibility="internal":
     {name: LmiListUnhookNode_}
     {parent: LmiList}
     {description: Unhook a list node from the list.}
     {prototype: void LmiListUnhookNode_(T_)(LmiListNodeBase_* node)}
     {template-parameter:
       {name: T_} {description: The type stored in the list.}}
     {parameter: {name: node} {description: The node to remove from the list.}}
   }
*/
#define Declare_LmiListUnhookNode_(T_) \
  LMI_INLINE_DECLARATION void LmiListUnhookNode_(T_)(LmiListNodeBase_(T_) *node);


#define DefineInline_LmiListUnhookNode_(T_, INLINE_)					\
  INLINE_ void LmiListUnhookNode_(T_)(LmiListNodeBase_(T_) *node)			\
  {																		\
	LmiListNodePtr_(T_) next = node->next;								\
	LmiListNodePtr_(T_) prev = node->prev;								\
																		\
	prev.b->next = next;												\
	next.b->prev = prev;												\
  }




#define Declare_LmiListInternalFuncs(T_) \
  Declare_LmiListCreateNode_(T_)				\
	   Declare_LmiListHookNode_(T_)				\
	   Declare_LmiListUnhookNode_(T_)


/**
  {function visibility="private":
    {name: LmiListConstructDefault}
	{parent: LmiList}
	{description: Construct an empty list.}
	{prototype: LmiList(T_)* LmiListConstructDefault(T_)(LmiList(T_)* l, LmiAllocator* a)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list to construct.}}
    {parameter: {name: a} {description: An allocator for the list.}}
	{return: A pointer to the constructed list.}
	{note: Like ISO C++ function {code: std::list<T_>::list(const allocator_type&)}.}
  }
*/
#define DefineInline_LmiListConstructDefault(T_, INLINE_) \
  INLINE_ LmiList(T_)* LmiListConstructDefault(T_)(LmiList(T_) * l_, LmiAllocator * a_) \
{ \
  l_->node.prev.b = &l_->node;	\
  l_->node.next.b = &l_->node; \
  l_->allocator = a_; \
  return l_; \
}


/**
  {function visibility="private":
    {name: LmiListDestruct}
	{parent: LmiList}
	{description: Destruct a list.}
	{prototype: void LmiListDestruct(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list to destruct.}}
	{note: Like ISO C++ function {code: std::list<T_>::~list()}.}
  }
*/
#define DefineInline_LmiListDestruct(T_, INLINE_)    \
  INLINE_ void LmiListDestruct(T_)(LmiList(T_) * l_) \
  {                                                  \
    LmiListClear(T_)(l_);                            \
  }


/**
  {function visibility="private":
    {name: LmiListConstructCopy}
	{parent: LmiList}
	{description: Construct a list from another list.}
	{prototype: LmiList(T_)* LmiListConstructCopy(T_)(LmiList(T_)* l, const LmiList(T_)* src)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list to construct.}}
    {parameter: {name: src} {description: the list to construct from.}}
	{return: A pointer to the constructed list.}
	{note: Like ISO C++ function {code: std::list<T_>::list(const list&)}.}
  }
*/
#define DefineInline_LmiListConstructCopy(T_, INLINE_) \
  INLINE_ LmiList(T_) * LmiListConstructCopy(T_)(LmiList(T_) * l_, \
                                                 const LmiList(T_) * src_) \
  {                                                                     \
	  l_->node.prev.b = &l_->node;										\
	  l_->node.next.b = &l_->node;										\
    l_->allocator = src_->allocator;                                    \
                                                                        \
    if (!LmiListInsertRange(T_)(l_, LmiListBegin(T_)(l_),               \
                                LmiListBeginConst(T_)(src_),            \
                                LmiListEndConst(T_)(src_))) {           \
      LmiListDestruct(T_)(l_);                                          \
      return NULL;                                                      \
    }                                                                   \
    return l_;                                                          \
  }


/**
  {function visibility="private":
    {name: LmiListAssign}
	{parent: LmiList}
	{description: Copy one list to another.}
	{prototype: LmiList(T_)* LmiListAssign(T_)(LmiList(T_)* l, const LmiList(T_)* src)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The target list.}}
    {parameter: {name: src} {description: The list to copy from.}}
	{return: A pointer to the assigned-to list or NULL on error.}
	{note: Like ISO C++ function {code: list& std::list<T_>::operator=(const list&)}.}
  }
*/
#define DefineInline_LmiListAssign(T_, INLINE_) \
  INLINE_ LmiList(T_) * LmiListAssign(T_)(LmiList(T_) * l_, \
                                          const LmiList(T_) * src_) \
  { \
    LmiListIterator(T_) first1, last1;                             \
    LmiListConstIterator(T_) first2, last2;                        \
                                                                   \
    if (l_ == src_) {                                              \
      return l_;                                                   \
    }                                                              \
    first1 = LmiListBegin(T_)(l_);                                 \
    last1 = LmiListEnd(T_)(l_);                                    \
    first2 = LmiListBeginConst(T_)(src_);                          \
    last2 = LmiListEndConst(T_)(src_);                             \
                                                                   \
    while (!LmiListIteratorEqual(T_)(&first1, &last1) &&           \
           !LmiListConstIteratorEqual(T_)(&first2, &last2)) {      \
      if (LmiAssign(T_)(LmiListIteratorContentOf(T_)(&first1),     \
                        LmiListConstIteratorContentOf(T_)(&first2)) \
          == NULL) {                                                \
        return NULL;                                                \
      }                                                            \
      LmiListIteratorIncrement(T_)(&first1);                       \
      LmiListConstIteratorIncrement(T_)(&first2);                  \
    }                                                              \
    if (LmiListConstIteratorEqual(T_)(&first2, &last2)) {          \
      LmiListEraseRange(T_)(l_, first1, last1);                    \
    }                                                              \
    else {                                                         \
      if (!LmiListInsertRange(T_)(l_, last1, first2, last2)) {     \
        return NULL;                                               \
      }                                                            \
    }                                                              \
    return l_;                                                     \
  }


/**
  {function visibility="private":
    {name: LmiListSwap}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::swap(list&)}.}
	{prototype: LmiBool LmiListSwap(T_)(LmiList(T_)* a, LmiList(T_)* b)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: a} {description: One of the lists to swap.}}
    {parameter: {name: b} {description: The other list to swap.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::swap(list&)}.}
  }
*/
#define DefineInline_LmiListSwap(T_, INLINE_)                       \
  INLINE_ LmiBool LmiListSwap(T_)(LmiList(T_) * a_, LmiList(T_) * b_) \
  {                                                                 \
    LmiAllocator * tmp_alloc;										\
	LmiListNodeBase_(T_)* a = &a_->node;							\
	LmiListNodeBase_(T_)* b = &b_->node;							\
                                                                    \
	if (a->next.b != a) {											\
		if (b->next.b != b) {										\
		/* Both a and b are not empty */							\
		LmiListNodePtr_(T_) tmp;									\
		tmp = a->next;												\
		a->next = b->next;											\
		b->next = tmp;												\
																	\
		tmp = a->prev;												\
		a->prev = b->prev;											\
		b->prev = tmp;												\
																	\
		a->next.b->prev.b = a;										\
		a->prev.b->next.b = a;										\
																	\
		b->next.b->prev.b = b;										\
		b->prev.b->next.b = b;										\
	  }																\
	  else {														\
		/* a is not empty, b is empty */							\
		b->next = a->next;											\
		b->prev = a->prev;											\
																	\
		b->next.b->prev.b = b;										\
		b->prev.b->next.b = b;										\
																	\
		a->next.b = a;												\
		a->prev.b = a;												\
	  }																\
	}																\
	else if (b->next.b != b) {										\
	  /* a is empty, b is not empty */								\
	  a->next = b->next;											\
	  a->prev = b->prev;											\
	  																\
	  a->next.b->prev.b = a;										\
	  a->prev.b->next.b = a;										\
																	\
	  b->next.b = b;												\
	  b->prev.b = b;												\
	}																\
																	\
    tmp_alloc = a_->allocator;										\
    a_->allocator = b_->allocator;                                  \
    b_->allocator = tmp_alloc;										\
                                                                    \
    return LMI_TRUE;                                                \
  }


/**
  {function visibility="private":
    {name: LmiListEqual}
	{parent: LmiList}
	{description: Like ISO C++ function {code: bool operator==(const std::list<T_>, const std::list<T_>)}.}
	{prototype: LmiBool LmiListEqual(T_)(const LmiList(T_)* a, const LmiList(T_)* b)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: a} {description: One of the lists to compare for equality.}}
    {parameter: {name: b} {description: The other list to compare for equality.}}
	{return: LMI_TRUE if the lists are equal or LMI_FALSE if they are not.}
	{note: Like ISO C++ function {code: bool operator==(const std::list<T_>, const std::list<T_>)}.}
  }
*/
#define DefineInline_LmiListEqual(T_, NAME_, COMP_, INLINE_)            \
  INLINE_ LmiBool NAME_(const LmiList(T_) * a_, const LmiList(T_) * b_) \
  {                                                                     \
    LmiListConstIterator(T_) end1 = LmiListEndConst(T_)(a_);            \
    LmiListConstIterator(T_) end2 = LmiListEndConst(T_)(b_);            \
                                                                        \
    LmiListConstIterator(T_) i1 = LmiListBeginConst(T_)(a_);            \
    LmiListConstIterator(T_) i2 = LmiListBeginConst(T_)(b_);            \
                                                                        \
    while (!LmiListConstIteratorEqual(T_)(&i1, &end1) &&                \
           !LmiListConstIteratorEqual(T_)(&i2, &end2) &&                \
           COMP_(LmiListConstIteratorContentOf(T_)(&i1),                \
                 LmiListConstIteratorContentOf(T_)(&i2))) {             \
      LmiListConstIteratorIncrement(T_)(&i1);                           \
      LmiListConstIteratorIncrement(T_)(&i2);                           \
    }                                                                   \
    return LmiListConstIteratorEqual(T_)(&i1, &end1) &&                 \
      LmiListConstIteratorEqual(T_)(&i2, &end2);                        \
  }


/**
  {function visibility="private":
    {name: LmiListLess}
	{parent: LmiList}
	{description: Like ISO C++ function {code: bool operator<(const std::list<T_>, const std::list<T_>)}.}
	{prototype: LmiBool LmiListLess(T_)(const LmiList(T_)* a, const LmiList(T_)* b)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: a} {description: One of the lists to compare for less.}}
    {parameter: {name: b} {description: The other list to compare for less.}}
	{return: LMI_TRUE if the first list is lexicographically less than the second list or LMI_FALSE if it is not.}
	{note: Like ISO C++ function {code: bool operator<(const std::list<T_>, const std::list<T_>)}.}
	{note: 
		The macro Declare_LmiListLess must be called at global scope before calling
		LmiListLess member functions.  LmiListLess is not included in the
		default set of LmiList functions.  It requires that the contained
		type be less-than comparable (i.e. have a Less member function).
	}
	{note: Equivalent to calling LmiLexicographicalCompare with the entire range of each list.}
  }
*/
#define DefineInline_LmiListLess(T_, NAME_, COMP_, INLINE_) \
  INLINE_ LmiBool NAME_(const LmiList(T_) * l1_, const LmiList(T_) * l2_) \
  { \
    LmiListConstIterator(T_) it1, end1, it2, end2; \
    it1 = LmiListBeginConst(T_)(l1_);              \
    end1 = LmiListEndConst(T_)(l1_);               \
    it2 = LmiListBeginConst(T_)(l2_);              \
    end2 = LmiListEndConst(T_)(l2_);               \
    \
    for(;;) {                                                     \
      if (LmiListConstIteratorEqual(T_)(&it2, &end2))             \
        return LMI_FALSE;                                         \
      if (LmiListConstIteratorEqual(T_)(&it1, &end1))             \
        return LMI_TRUE;                                          \
      if (COMP_(LmiListConstIteratorContentOf(T_)(&it1),          \
                LmiListConstIteratorContentOf(T_)(&it2)))         \
        return LMI_TRUE;                                          \
      if (COMP_(LmiListConstIteratorContentOf(T_)(&it2),          \
                LmiListConstIteratorContentOf(T_)(&it1)))         \
        return LMI_FALSE;                                         \
      LmiListConstIteratorIncrement(T_)(&it1);                    \
      LmiListConstIteratorIncrement(T_)(&it2);                    \
    }                                                             \
  }


/**
  {function visibility="private":
    {name: LmiListGetAllocator}
	{parent: LmiList}
	{description: Like ISO C++ function {code: allocator_type std::list<T_>::get_allocator() const}.}
	{prototype: LmiAllocator* LmiListGetAllocator(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list whose allocator is of interest.}}
	{return: A pointer to the list's allocator.}
	{note: Like ISO C++ function {code: allocator_type std::list<T_>::get_allocator() const}.}
  }
*/
#define DefineInline_LmiListGetAllocator(T_, INLINE_) \
  INLINE_ LmiAllocator * LmiListGetAllocator(T_)(const LmiList(T_) * l_) \
  { \
	return l_->allocator; \
  }


/**
  {function visibility="private":
    {name: LmiListBegin}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::iterator std::list<T_>::begin()}.}
	{prototype: LmiListIterator(T_) LmiListBegin(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A list iterator to the first element in the list.}
	{note: Like ISO C++ function {code: std::list<T_>::iterator std::list<T_>::begin()}.}
  }
*/
#define DefineInline_LmiListBegin(T_, INLINE_) \
  INLINE_ LmiListIterator(T_) LmiListBegin(T_)(LmiList(T_) * l_) \
{ \
  return l_->node.next.b; \
}


/**
  {function visibility="private":
    {name: LmiListBeginConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T>::const_iterator std::list<T_>::begin() const}.}
	{prototype: LmiListConstIterator(T_) LmiListBeginConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only list iterator to the first element in the list.}
	{note: Like ISO C++ function {code: std::list<T>::const_iterator std::list<T_>::begin() const}.}
  }
*/
#define DefineInline_LmiListBeginConst(T_, INLINE_) \
  INLINE_ LmiListConstIterator(T_)                      \
       LmiListBeginConst(T_)(const LmiList(T_) * l_)    \
{ \
  return l_->node.next.b; \
}


/**
  {function visibility="private":
    {name: LmiListEnd}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::iterator std::list<T_>::end()}.}
	{prototype: LmiListIterator(T_) LmiListEnd(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A list iterator to the element one past the end of the list.}
	{note: Like ISO C++ function {code: std::list<T_>::iterator std::list<T_>::end()}.}
  }
*/
#define DefineInline_LmiListEnd(T_, INLINE_) \
  INLINE_ LmiListIterator(T_) LmiListEnd(T_)(LmiList(T_) * l_) \
{ \
  return &l_->node; \
}


/**
  {function visibility="private":
    {name: LmiListEndConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::const_iterator std::list<T_>::end() const}.}
	{prototype: LmiListConstIterator(T_) LmiListEndConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only list iterator to the element one past the end of the list.}
	{note: Like ISO C++ function {code: std::list<T_>::const_iterator std::list<T_>::end() const}.}
  }
*/
#define DefineInline_LmiListEndConst(T_, INLINE_) \
  INLINE_ LmiListConstIterator(T_) \
       LmiListEndConst(T_)(const LmiList(T_) * l_)      \
{ \
  return &l_->node; \
}



/**
  {function visibility="private":
    {name: LmiListSize}
	{parent: LmiList}
	{description: Like ISO C++ function {code: size_type std::list<T_>::size() const}.}
	{prototype: LmiSizeT LmiListSize(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: The number of elements in the list.}
	{note: Like ISO C++ function {code: size_type std::list<T_>::size() const}.}
	{note: The complexity of LmiListSize is linear-time (O(N)) not constant-time (O(1)) as one might expect.}
  }
*/
/* This could use a generic LmiDistance algorithm. */
#define DefineInline_LmiListSize(T_, INLINE_) \
  INLINE_ LmiSizeType(LmiList(T_)) \
    LmiListSize(T_)(const LmiList(T_) * l_) \
  { \
	  const LmiListNodeBase_(T_) * n_;								\
    LmiSizeType(LmiList(T_)) ret_ = 0;                              \
    for (n_ = l_->node.next.b;										\
		 n_ != &l_->node;											\
		 n_ = n_->next.b) {											\
      ret_++;                                                       \
    }                                                               \
    return ret_; \
  }


/**
  {function visibility="private":
    {name: LmiListMaxSize}
	{parent: LmiList}
	{description: Like ISO C++ function {code: size_type std::list<T_>::max_size() const}.}
	{prototype: LmiSizeT LmiListMaxSize(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: The maximum number of elements the list is capable of holding.}
	{note: Like ISO C++ function {code: size_type std::list<T_>::max_size() const}.}
  }
*/
#define DefineInline_LmiListMaxSize(T_, INLINE_) \
  INLINE_ LmiSizeType(LmiList(T_)) \
    LmiListMaxSize(T_)(const LmiList(T_) * l_) \
  { \
    return (LmiSizeType(LmiList(T_)))(-1);      \
  }


/**
  {function visibility="private":
    {name: LmiListEmpty}
	{parent: LmiList}
	{description: Like ISO C++ function {code: bool std::list<T_>::empty() const}.}
	{prototype: LmiBool LmiListEmpty(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: LMI_TRUE if the list is empty or LMI_FALSE if it is not.}
	{note: Like ISO C++ function {code: bool std::list<T_>::empty() const}.}
  }
*/
#define DefineInline_LmiListEmpty(T_, INLINE_) \
  INLINE_ LmiBool LmiListEmpty(T_)(const LmiList(T_) * l_) \
  { \
    return (l_->node.next.b == &l_->node);	\
  }


/**
  {function visibility="private":
    {name: LmiListRBegin}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::reverse_iterator std::list<T_>::rbegin()}.}
	{prototype: LmiListReverseIterator(T_) LmiListRBegin(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A reverse iterator to the first element in the reversed list.}
	{note: Like ISO C++ function {code: std::list<T_>::reverse_iterator std::list<T_>::rbegin()}.}
  }
*/
#define DefineInline_LmiListRBegin(T_, INLINE_) \
  INLINE_ LmiListReverseIterator(T_) LmiListRBegin(T_)(LmiList(T_) * l_) \
  {                                                                     \
    return (LmiListReverseIterator(T_))(LmiListEnd(T_)(l_));            \
  }


/**
  {function visibility="private":
    {name: LmiListRBeginConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::const_reverse_iterator std::list<T_>::rbegin() const}.}
	{prototype: LmiListConstReverseIterator(T_) LmiListRBeginConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only reverse iterator to the first element in the reversed list.}
	{note: Like ISO C++ function {code: std::list<T_>::const_reverse_iterator std::list<T_>::rbegin() const}.}
  }
*/
#define DefineInline_LmiListRBeginConst(T_, INLINE_)                    \
  INLINE_ LmiListConstReverseIterator(T_)                               \
       LmiListRBeginConst(T_)(const LmiList(T_) * l_)                   \
  {                                                                     \
    return (LmiListConstReverseIterator(T_))(LmiListEndConst(T_)(l_));  \
  }




/**
  {function visibility="private":
    {name: LmiListREnd}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::reverse_iterator std::list<T_>::rend()}.}
	{prototype: LmiListReverseIterator(T_) LmiListREnd(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A reverse iterator to the element one past the last element in the reversed list.}
	{note: Like ISO C++ function {code: std::list<T_>::reverse_iterator std::list<T_>::rend()}.}
  }
*/
#define DefineInline_LmiListREnd(T_, INLINE_)                          \
  INLINE_ LmiListReverseIterator(T_) LmiListREnd(T_)(LmiList(T_) * l_) \
  {                                                                    \
    return (LmiListReverseIterator(T_))(LmiListBegin(T_)(l_));         \
  }


/**
  {function visibility="private":
    {name: LmiListREndConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::const_reverse_iterator std::list<T_>::rend() const}.}
	{prototype: LmiListConstReverseIterator(T_) LmiListREndConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only reverse iterator to the element one past the last element in the reversed list.}
	{note: Like ISO C++ function {code: std::list<T_>::const_reverse_iterator std::list<T_>::rend() const}.}
  }
*/
#define DefineInline_LmiListREndConst(T_, INLINE_)                      \
  INLINE_ LmiListConstReverseIterator(T_)                               \
       LmiListREndConst(T_)(const LmiList(T_) * l_)                     \
  {                                                                     \
    return (LmiListConstReverseIterator(T_))(LmiListBeginConst(T_)(l_)); \
  }


/**
  {function visibility="private":
    {name: LmiListConstructN}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::list(size_type, const T&, const allocator_type&)}.}
	{prototype: LmiList(T_)* LmiListConstructN(T_)(LmiList(T_)* l, LmiSizeT n, const T_* t, LmiAllocator* a)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list to construct.}}
	{parameter: {name: n} {description: The number of copies of {italic: t} to store in the list initially.}}
	{parameter: {name: t} {description: The object to store in the list initially.}}
	{parameter: {name: a} {description: An allocator for the list.}}
	{return: A pointer to the constructed list.}
	{note: Like ISO C++ function {code: std::list<T_>::list(size_type, const T&, const allocator_type&)}.}
  }
*/
#define DefineInline_LmiListConstructN(T_, INLINE_) \
  INLINE_ LmiList(T_) * \
  LmiListConstructN(T_)(LmiList(T_) * l_, LmiSizeType(LmiList(T_)) n_, \
                        const T_ * t_, LmiAllocator * a_) \
  { \
    LmiListIterator(T_) begin;                    \
                                                  \
    if (!LmiListConstructDefault(T_)(l_, a_)) {   \
      return NULL;                                \
    }                                             \
                                                  \
    begin = LmiListBegin(T_)(l_);                 \
    if (!LmiListInsertN(T_)(l_, begin, n_, t_)) { \
      LmiListDestruct(T_)(l_);                    \
      return NULL;                                \
    }                                             \
    return l_;                                    \
  }



/**
  {function visibility="private":
    {name: LmiListConstructRange}
	{parent: LmiList}
	{description: Like ISO C++ function {code: std::list<T_>::list<std::list<T_>::const_iterator>(const_iterator, const_iterator, const allocator_type&)}.}
	{prototype: LmiList(T_)* LmiListConstructRange(T_)(LmiList(T_)* l, LmiListConstIterator(T_) first, LmiListConstIterator(T_) last, LmiAllocator* a)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list to construct.}}
	{parameter: {name: first} {description: An iterator to the first element in a list to be copied to the constructed list.}}
	{parameter: {name: last} {description: An iterator to one-past-the-last element in a list to be copied to the constructed list.}}
	{parameter: {name: a} {description: An allocator for the list.}}
	{return: A pointer to the constructed list.}
	{note: Like ISO C++ function {code: std::list<T_>::list<std::list<T_>::const_iterator>(const_iterator, const_iterator, const allocator_type&)}.}
  }
*/
#define DefineInline_LmiListConstructRange(T_, INLINE_) \
  INLINE_ LmiList(T_) * \
  LmiListConstructRange(T_)(LmiList(T_) * l_, LmiListConstIterator(T_) first_, \
                            LmiListConstIterator(T_) last_, LmiAllocator * a_) \
  { \
    LmiListIterator(T_) begin;					\
                                                \
    if (!LmiListConstructDefault(T_)(l_, a_)) { \
      return NULL;                              \
    }                                           \
                                                \
    begin = LmiListBegin(T_)(l_);				\
    if (!LmiListInsertRange(T_)(l_, begin, first_, last_)) {   \
      LmiListDestruct(T_)(l_);                                 \
      return NULL;                                             \
    }                                                          \
    return l_; \
  }


/**
  {function visibility="private":
    {name: LmiListConstructIteratorRange}
	{parent: LmiList}
	{description: Like ISO C++ function {code: template<InputIterator_> std::list<T_>::list(InputIterator_, InputIterator_, const allocator_type&)}.}
	{prototype: LmiList(T_)* LmiListConstructIteratorRange(T_, InputIterator_)(LmiList(T_)* l, InputIterator_ first, InputIterator_ last, LmiAllocator* a)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{template-parameter:
	  {name: InputIterator_} {description: An input iterator whose ContentOf function returns T_*.}}
	{parameter: {name: l} {description: The list to construct.}}
	{parameter: {name: first} {description: An iterator to the first element in a list to be copied to the constructed list.}}
	{parameter: {name: last} {description: An iterator to one-past-the-last element in a list to be copied to the constructed list.}}
	{parameter: {name: a} {description: An allocator for the list.}}
	{return: A pointer to the constructed list.}
	{note: Like ISO C++ function {code: template<InputIterator_> std::list<T_>::list(InputIterator_, InputIterator_, const allocator_type&)}.}
  }
*/
#define DefineInline_LmiListConstructIteratorRange(T_, InputIterator_, INLINE_) \
  INLINE_ LmiList(T_) * \
  LmiListConstructIteratorRange(T_, InputIterator_)(LmiList(T_) * l_, \
                                                    InputIterator_ first_, \
                                                    InputIterator_ last_, \
                                                    LmiAllocator * a_) \
  { \
    LmiListIterator(T_) begin;					\
                                                \
    if (!LmiListConstructDefault(T_)(l_, a_)) { \
      return NULL;                              \
    }                                           \
                                                \
    begin = LmiListBegin(T_)(l_);									       \
    if (!LmiListInsertIteratorRange(T_, InputIterator_)(l_,                \
                                                        begin,			   \
                                                        first_, last_)) {  \
      LmiListDestruct(T_)(l_);                                             \
      return NULL;                                                         \
    }                                                                      \
    return l_;                                                             \
  }



/**
  {function visibility="private":
    {name: LmiListFront}
	{parent: LmiList}
	{description: Like ISO C++ function {code: T_& std::list<T_>::front()}.}
	{prototype: T_* LmiListFront(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A pointer first element in the list.}
	{note: Like ISO C++ function {code: T_& std::list<T_>::front()}.}
  }
*/
#define DefineInline_LmiListFront(T_, INLINE_) \
  INLINE_ T_* LmiListFront(T_)(LmiList(T_) * l_) \
  { \
    return &l_->node.next.n->obj;        \
  }



/**
  {function visibility="private":
    {name: LmiListFrontConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: const T_& std::list<T_>::front() const}.}
	{prototype: const T_* LmiListFrontConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only pointer first element in the list.}
	{note: Like ISO C++ function {code: const T_& std::list<T_>::front() const}.}
  }
*/
#define DefineInline_LmiListFrontConst(T_, INLINE_) \
  INLINE_ const T_* LmiListFrontConst(T_)(const LmiList(T_) * l_) \
  { \
    return &l_->node.next.n->obj;        \
  }


/**
   {function visibility="private":
    {name: LmiListInsert}
    {parent: LmiList}
    {description: Insert an element before position given with value given.}
    {prototype: LmiListIterator(T_) LmiListInsert(T_)(LmiList(T_)* l, LmiListIterator(T_) pos, const T_* t)}
    {template-parameter:
      {name: T_} {description: The type stored in the list.}}
    {parameter: {name: l} {description: The list.}}
    {parameter: {name: pos} {description: A position in the list before which the element will be inserted.}}
    {parameter: {name: t} {description: The element whose value is to be inserted in the list.}}
    {return: A list iterator referring to the newly-inserted element,
	  or an exceptional list iterator on failure.}
	{note: Like ISO C++ function {code: iterator std::list<T_>::insert(iterator, const T&)}.}
   } 
*/
#define DefineInline_LmiListInsert(T_, INLINE_)              \
  INLINE_ LmiListIterator(T_)                                        \
       LmiListInsert(T_)(LmiList(T_) * l_, LmiListIterator(T_) pos_, \
                         const T_* t_)                               \
  {                                                                  \
    LmiListNode_(T_) * p_ = LmiListCreateNode_(T_)(l_, t_);          \
    if (p_ == NULL) {												 \
      return NULL;													 \
    }																 \
    LmiListHookNode_(T_)(p_, pos_);									 \
    return &p_->b;													 \
  }


/**
  {function visibility="private":
    {name: LmiListInsertN}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::insert(iterator, size_type, const T&)}.}
	{prototype: LmiBool LmiListInsertN(T_)(LmiList(T_)* l, LmiListIterator(T_) pos, LmiSizeT n, const T_* t)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{parameter: {name: pos} {description: A position in the list before which the elements will be inserted.}}
	{parameter: {name: n} {description: The number of copies of the element to store in the list.}}
	{parameter: {name: t} {description: The element whose value is inserted in the list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::insert(iterator, size_type, const T&)}.}
  }
*/
#define DefineInline_LmiListInsertN(T_, INLINE_) \
  INLINE_ LmiBool LmiListInsertN(T_)(LmiList(T_) * l_,           \
                                     LmiListIterator(T_) pos_,   \
                                     LmiSizeType(LmiList(T_)) n, \
                                     const T_ * t_)              \
  { \
    LmiSizeType(LmiList(T_)) i;                 \
    for (i = 0; i < n; i++) {                                    \
      LmiListIterator(T_) ret = LmiListInsert(T_)(l_, pos_, t_); \
      if (LmiListIteratorIsExceptional(T_)(ret)) {               \
        return LMI_FALSE;                                        \
      }                                                          \
    }                                                            \
    return LMI_TRUE;                                             \
  }

#define DefineInline_LmiListInsertRange_Tmpl(T_, InputIterator_, Func_, INLINE_) \
  INLINE_ LmiBool Func_(LmiList(T_) * l_, \
                        LmiListIterator(T_) pos_,                 \
                        InputIterator_ first_,                    \
                        InputIterator_ last_) {                    \
    for(;                                                         \
        !LmiEqual(InputIterator_)(&first_, &last_);                \
        LmiIncrement(InputIterator_)(&first_)) {                  \
      LmiListIterator(T_) ret =                                   \
        LmiListInsert(T_)(l_, pos_,                               \
                          LmiContentOf(InputIterator_)(&first_)); \
      if (LmiListIteratorIsExceptional(T_)(ret)) {                \
        return LMI_FALSE;                                         \
      }                                                           \
    }                                                             \
    return LMI_TRUE;                                              \
  }


/**
  {function visibility="private":
    {name: LmiListInsertRange}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::insert<std::list<T_>::const_iterator>(iterator, const_iterator, const_iterator)}.}
	{prototype: LmiBool LmiListInsertRange(T_)(LmiList(T_)* l, LmiListIterator(T_) pos, LmiListConstIterator(T_) first, LmiListConstIterator(T_) last)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The target list.}}
	{parameter: {name: pos} {description: A position in the list before which the elements will be inserted.}}
	{parameter: {name: first} {description: An iterator to the first element in a list to be copied to the target list.}}
	{parameter: {name: last} {description: An iterator to one-past-the-last element in a list to be copied to the target list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::insert<std::list<T_>::const_iterator>(iterator, const_iterator, const_iterator)}.}
  }
*/
#define DefineInline_LmiListInsertRange(T_, INLINE_) \
  DefineInline_LmiListInsertRange_Tmpl(T_, LmiListConstIterator(T_), \
                                       LmiListInsertRange(T_), INLINE_)

/**
  {function visibility="private":
    {name: LmiListInsertIteratorRange}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void template<InputIterator_> std::list<T_>::insert(iterator, InputIterator_, InputIterator_)}.}
	{prototype: LmiBool LmiListInsertIteratorRange(T_, InputIterator_)(LmiList(T_)* l, LmiListIterator(T_) pos, InputIterator_ first, InputIterator_ last)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{template-parameter:
	  {name: InputIterator_} {description: The iterator type of the container from which elements are inserted.}}
	{parameter: {name: l} {description: The target list.}}
	{parameter: {name: pos} {description: A position in the list before which the elements will be inserted.}}
	{parameter: {name: first} {description: An iterator to the first element in a list to be copied to the target list.}}
	{parameter: {name: last} {description: An iterator to one-past-the-last element in a list to be copied to the target list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void template<InputIterator_> std::list<T_>::insert(iterator, InputIterator_, InputIterator_)}.}
  }
*/
#define DefineInline_LmiListInsertIteratorRange(T_, InputIterator_, INLINE_) \
  DefineInline_LmiListInsertRange_Tmpl(T_, InputIterator_, \
                                       LmiListInsertIteratorRange(T_, InputIterator_), \
                                       INLINE_)


/**
   {function visibility="private":
    {name: LmiListErase}
    {parent: LmiList}
    {description: Erase the list node at the position given.}
    {prototype: LmiListIterator(T_) LmiListErase(T_)(LmiList(T_)* l, LmiListIterator(T_) pos)}
    {template-parameter:
      {name: T_} {description: The type stored in the list.}}
    {parameter: {name: l} {description: The list.}}
    {parameter: {name: pos} {description: A position in the list of the element to erase.}}
    {return: A list iterator referring to the element after the one erased.}
	{note: Like ISO C++ function {code: iterator std::list<T_>::erase(iterator)}.}
   } 
*/
#define DefineInline_LmiListErase(T_, INLINE_)               \
  INLINE_ LmiListIterator(T_) LmiListErase(T_)(LmiList(T_) * l_, \
                                               LmiListIterator(T_) pos_) \
  {                                                                     \
	LmiListIterator(T_) ret_ = pos_->next.b;							\
    LmiListUnhookNode_(T_)(pos_);										\
    LmiDestruct(T_)(LmiListIteratorContentOf(T_)(&pos_));				\
    LmiAllocatorDeallocate(l_->allocator, pos_, sizeof(LmiListNode_(T_))); \
    return ret_;                                                        \
  }



/**
  {function visibility="private":
    {name: LmiListEraseRange}
	{parent: LmiList}
	{description: Like ISO C++ function {code: iterator std::list<T_>::erase(iterator, iterator)}.}
	{prototype: LmiListIterator(T_) LmiListEraseRange(T_)(LmiList(T_)* l, LmiListIterator(T_) first, LmiListIterator(T_) last)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{parameter: {name: first} {description: An iterator to the first element in the list to erase.}}
	{parameter: {name: last} {description: An iterator to one-past-the-last element in the list to erase.}}
	{return: A list iterator referring to the element after the one erased.}
	{note: Like ISO C++ function {code: iterator std::list<T_>::erase(iterator, iterator)}.}
  }
*/
#define DefineInline_LmiListEraseRange(T_, INLINE_)     \
  INLINE_ LmiListIterator(T_)                           \
       LmiListEraseRange(T_)(LmiList(T_) * l_,          \
                             LmiListIterator(T_) first_, \
                             LmiListIterator(T_) last_)   \
  {                                                     \
    while (!LmiListIteratorEqual(T_)(&first_, &last_)) {  \
      first_ = LmiListErase(T_)(l_, first_);              \
    }                                                   \
    return last_;                                        \
  }



/**
  {function visibility="private":
    {name: LmiListClear}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::clear()}.}
	{prototype: void LmiListClear(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{note: Like ISO C++ function {code: void std::list<T_>::clear()}.}
  }
*/
#define DefineInline_LmiListClear(T_, INLINE_)          \
  INLINE_ void LmiListClear(T_)(LmiList(T_) * l_)       \
  {                                                     \
    LmiListIterator(T_) cur_;                           \
    cur_ = l_->node.next.b;								\
    while (cur_ != LmiListEnd(T_)(l_)) {                \
      LmiListIterator(T_) tmp_ = cur_;                  \
      cur_ = cur_->next.b;									\
      LmiDestruct(T_)(LmiListIteratorContentOf(T_)(&tmp_));	\
      LmiAllocatorDeallocate(l_->allocator, tmp_,       \
                             sizeof(LmiListNode_(T_))); \
    }                                                   \
    l_->node.prev.b = &l_->node;							\
    l_->node.next.b = &l_->node;							\
 }


/**
  {function visibility="private":
    {name: LmiListResize}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::resize(size_type, T)}.}
	{prototype: LmiBool LmiListResize(T_)(LmiList(T_)* l, LmiSizeT n, const T_* t)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{parameter: {name: n} {description: The new size.}}
	{parameter: {name: t} {description: The element whose value is inserted in the list if the new size is greater than the current size of the list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::resize(size_type, T)}.}
  }
*/
#define DefineInline_LmiListResize(T_, INLINE_) \
  INLINE_ LmiBool LmiListResize(T_)(LmiList(T_) * l_, \
                                    LmiSizeType(LmiList(T_)) n_,        \
                                    const T_ * t_) {                    \
    LmiListIterator(T_) it, end;                 \
    LmiSizeType(LmiList(T_)) len;            \
    end = LmiListEnd(T_)(l_);                \
    for (it = LmiListBegin(T_)(l_), len = 0; \
         !LmiListIteratorEqual(T_)(&it, &end) && len < n_; \
         LmiListIteratorIncrement(T_)(&it), len++) \
      /* empty loop body */ ;                      \
    if (len == n_) {                               \
      LmiListEraseRange(T_)(l_, it, end);          \
      return LMI_TRUE;                             \
    }                                              \
    else {                                         \
      return                                       \
        LmiListInsertN(T_)(l_, end, n_ - len, t_); \
    }                                              \
  }



/**
  {function visibility="private":
    {name: LmiListPushFront}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::push_front(const T&)}.}
	{prototype: LmiBool LmiListPushFront(T_)(LmiList(T_)* l, const T_* t)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{parameter: {name: t} {description: The element whose value is inserted in the list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::push_front(const T&)}.}
  }
*/
#define DefineInline_LmiListPushFront(T_, INLINE_) \
  INLINE_ LmiBool LmiListPushFront(T_)(LmiList(T_) * l_, const T_ * t_) \
  {                                                            \
    LmiListIterator(T_) ret =                                  \
      LmiListInsert(T_)(l_, LmiListBegin(T_)(l_), t_);         \
    return LmiListIteratorIsExceptional(T_)(ret);              \
  }


/**
  {function visibility="private":
    {name: LmiListPopFront}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::pop_front()}.}
	{prototype: void LmiListPopFront(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{note: Like ISO C++ function {code: void std::list<T_>::pop_front()}.}
  }
*/
#define DefineInline_LmiListPopFront(T_, INLINE_) \
  INLINE_ void LmiListPopFront(T_)(LmiList(T_) * l_) \
  {                                                  \
    LmiListErase(T_)(l_, LmiListBegin(T_)(l_));      \
  }


/**
  {function visibility="private":
    {name: LmiListBack}
	{parent: LmiList}
	{description: Like ISO C++ function {code: T_& std::list<T_>::back()}.}
	{prototype: T_* LmiListBack(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A pointer to the last element in the list.}
	{note: Like ISO C++ function {code: T_& std::list<T_>::back()}.}
  }
*/
#define DefineInline_LmiListBack(T_, INLINE_) \
  INLINE_ T_* LmiListBack(T_)(LmiList(T_) * l_) \
  { \
	  return &l_->node.prev.n->obj;	\
  }


/**
  {function visibility="private":
    {name: LmiListBackConst}
	{parent: LmiList}
	{description: Like ISO C++ function {code: const T_& std::list<T_>::back() const}.}
	{prototype: const T_* LmiListBackConst(T_)(const LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{return: A read-only pointer to the last element in the list.}
	{note: Like ISO C++ function {code: const T_& std::list<T_>::back() const}.}
  }
*/
#define DefineInline_LmiListBackConst(T_, INLINE_) \
  INLINE_ const T_* LmiListBackConst(T_)(const LmiList(T_) * l_) \
  { \
    return &l_->node.prev.n->obj;   \
  }


/**
  {function visibility="private":
    {name: LmiListPushBack}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::push_back(const T&)}.}
	{prototype: LmiBool LmiListPushBack(T_)(LmiList(T_)* l, const T_* t)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{parameter: {name: t} {description: The element whose value is inserted in the list.}}
	{return: LMI_TRUE on success or LMI_FALSE on failure.}
	{note: Like ISO C++ function {code: void std::list<T_>::push_back(const T&)}.}
  }
*/
#define DefineInline_LmiListPushBack(T_, INLINE_) \
  INLINE_ LmiBool LmiListPushBack(T_)(LmiList(T_) * l_, const T_ * t_) \
  {                                                                 \
    LmiListIterator(T_) ret =                                       \
      LmiListInsert(T_)(l_, LmiListEnd(T_)(l_), t_);                \
    return !LmiListIteratorIsExceptional(T_)(ret);                   \
  }



/**
  {function visibility="private":
    {name: LmiListPopBack}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::pop_back()}.}
	{prototype: void LmiListPopBack(T_)(LmiList(T_)* l)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list.}}
	{note: Like ISO C++ function {code: void std::list<T_>::pop_back()}.}
  }
*/
#define DefineInline_LmiListPopBack(T_, INLINE_) \
  INLINE_ void LmiListPopBack(T_)(LmiList(T_) * l_)           \
  {                                                           \
    LmiListErase(T_)(l_, l_->node.prev.b); \
  }


#define DefineInline_LmiListIteratorContentOf(T_, INLINE_)              \
  INLINE_ T_* LmiListIteratorContentOf(T_)(LmiListIterator(T_) * i_)    \
  {                                                                     \
	  return &((LmiListNode_(T_)*)(*i_))->obj;							\
  }
    
#define DefineInline_LmiListIteratorContentOfConst(T_, INLINE_)              \
  INLINE_ const T_* LmiListIteratorContentOfConst(T_)(const LmiListIterator(T_) * i_)    \
  {                                                                     \
	  return &((LmiListNode_(T_)*)(*i_))->obj;							\
  }
    
#define DefineInline_LmiListIteratorIncrement(T_, INLINE_)      \
  INLINE_ LmiListIterator(T_)*                                  \
  LmiListIteratorIncrement(T_)(LmiListIterator(T_) * i_)        \
  {                                                             \
	  *i_ = (*i_)->next.b;                                      \
	  return i_;												\
  }
    
#define DefineInline_LmiListIteratorDecrement(T_, INLINE_)      \
  INLINE_ LmiListIterator(T_)*                                  \
  LmiListIteratorDecrement(T_)(LmiListIterator(T_) * i_)        \
  {                                                             \
    *i_ = (*i_)->prev.b;                                        \
    return i_;                                                  \
  }

#define DefineInline_LmiListIteratorIsExceptional(T_, INLINE_)              \
  INLINE_ LmiBool LmiListIteratorIsExceptional(T_)(const LmiListIterator(T_) i_)    \
  {                                                                     \
    return i_ == NULL;                                                  \
  }

    
#define DefineInline_LmiListIteratorConstructExceptional(T_, INLINE_)              \
  INLINE_ LmiListIterator(T_) * LmiListIteratorConstructExceptional(T_)(LmiListIterator(T_) * i_) \
  {                                                                     \
    *i_ = NULL;                                                         \
    return i_;                                                          \
  }

    
#define DefineInline_LmiListConstIteratorContentOf(T_, INLINE_)              \
  INLINE_ const T_* LmiListConstIteratorContentOf(T_)(LmiListConstIterator(T_) * i_)    \
  {                                                                     \
	  return &((LmiListNode_(T_)*)(*i_))->obj;							\
  }
    
#define DefineInline_LmiListConstIteratorContentOfConst(T_, INLINE_)              \
  INLINE_ const T_* LmiListConstIteratorContentOfConst(T_)(const LmiListConstIterator(T_) * i_)    \
  {                                                                     \
	  return &((LmiListNode_(T_)*)(*i_))->obj;							\
  }
    
#define DefineInline_LmiListConstIteratorIncrement(T_, INLINE_)      \
  INLINE_ LmiListConstIterator(T_)*                                  \
  LmiListConstIteratorIncrement(T_)(LmiListConstIterator(T_) * i_)        \
  {                                                             \
	  *i_ = (*i_)->next.b;										\
	  return i_;												\
  }
    
#define DefineInline_LmiListConstIteratorDecrement(T_, INLINE_)      \
  INLINE_ LmiListConstIterator(T_)*                                  \
  LmiListConstIteratorDecrement(T_)(LmiListConstIterator(T_) * i_)        \
  {                                                             \
	  *i_ = (*i_)->prev.b;										\
	  return i_;												\
  }
    
#define DefineInline_LmiListConstIteratorConstructExceptional(T_, INLINE_) \
  INLINE_ LmiListConstIterator(T_) * LmiListConstIteratorConstructExceptional(T_)(LmiListConstIterator(T_) * i_) \
  {                                                                     \
    *i_ = NULL;                                                         \
    return i_;                                                          \
  }

    
#define DefineInline_LmiListConstIteratorIsExceptional(T_, INLINE_)              \
  INLINE_ LmiBool LmiListConstIteratorIsExceptional(T_)(const LmiListConstIterator(T_) i_)    \
  {                                                                     \
    return i_ == NULL;                                                  \
  }


#define DefineInline_LmiListReverseIteratorFuncs(T_, INLINE_) \
	DefineInline_LmiReverseBidirectionalIterator(LmiReverseIterator(LmiList(T_)), LmiIterator(LmiList(T_)), T_, const T_, INLINE_) \
    DefineInline_LmiReverseBidirectionalIterator(LmiConstReverseIterator(LmiList(T_)), LmiConstIterator(LmiList(T_)), const T_, const T_, INLINE_)
    


/**
  {function visibility="private":
    {name: LmiListSplice}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::splice(iterator, list&, iterator, iterator)}.}
	{prototype: void LmiListSplice(T_)(LmiList(T_)* l, LmiListIterator(T_) pos, LmiList(T_)* src, LmiListIterator(T_) first, LmiListIterator(T_) last)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
  	{parameter: {name: l} {description: The list.}}
	{parameter: {name: pos} {description: A position in the list before which a sequence of elements will be inserted.}}
	{parameter: {name: src} {description: The list from which a sequence of elements will be spliced.}}
	{parameter: {name: first} {description: An iterator to the first element of a sequence to splice into the list.}}
	{parameter: {name: last} {description: An iterator to one past the last element of a sequence to splice into the list.}}
	{note: Like ISO C++ function {code: void std::list<T_>::splice(iterator, list&, iterator, iterator)}.}
	{note: The complexity of LmiListSplice is constant-time (O(1)).}
  }
*/
#define Declare_LmiListSplice(T_) \
  LMI_INLINE_DECLARATION void LmiListSplice(T_)(LmiList(T_) * l_, LmiListIterator(T_) pos_, \
                         LmiList(T_) * src_, LmiListIterator(T_) first_, \
                         LmiListIterator(T_) last_);


/* N.B. it is an error to splice two lists with different allocators. */
#define DefineInline_LmiListSplice(T_, INLINE_)              \
  INLINE_ void LmiListSplice(T_)(LmiList(T_) * l_,           \
                                 LmiListIterator(T_) pos,	 \
                                 LmiList(T_) * src_,         \
                                 LmiListIterator(T_) first_, \
                                 LmiListIterator(T_) last_)	 \
  {															 \
	LmiListNodePtr_(T_) tmp;								 \
	LmiAssert(l_->allocator == src_->allocator);			 \
															 \
	if (first_ == last_) {									 \
	  return;												 \
	}														 \
															 \
	/* Remove [first .. last) from the old list */			 \
	last_->prev.b->next.b = pos;							 \
	first_->prev.b->next.b = last_;							 \
	pos->prev.b->next.b = first_;							 \
															 \
	/* Insert [first .. last) into the new position. */		 \
	tmp = pos->prev;										 \
	pos->prev = last_->prev;								 \
	last_->prev = first_->prev;								 \
	first_->prev = tmp;										 \
  }

/**
  {function visibility="private":
    {name: LmiListSpliceOne}
	{parent: LmiList}
	{description: Like ISO C++ function {code: void std::list<T_>::splice(iterator, list&, iterator)}.}
	{prototype: void LmiListSpliceOne(T_)(LmiList(T_)* l, LmiListIterator(T_) pos, LmiList(T_)* src, LmiListIterator(T_) it)}
	{template-parameter:
	  {name: T_} {description: The type stored in the list.}}
  	{parameter: {name: l} {description: The list.}}
	{parameter: {name: pos} {description: A position in the list before which an element will be inserted.}}
	{parameter: {name: src} {description: The list from which an element will be spliced.}}
	{parameter: {name: it} {description: An iterator to splice into the list.}}
	{note: Like ISO C++ function {code: void std::list<T_>::splice(iterator, list&, iterator)}.}
	{note: The complexity of LmiListSpliceOne is constant-time (O(1)).}
  }
*/
#define Declare_LmiListSpliceOne(T_) \
  LMI_INLINE_DECLARATION void LmiListSpliceOne(T_)(LmiList(T_) * l_, LmiListIterator(T_) pos_, \
                         LmiList(T_) * src_, LmiListIterator(T_) it_);


/* N.B. it is an error to splice two lists with different allocators. */
#define DefineInline_LmiListSpliceOne(T_, INLINE_)              \
  INLINE_ void LmiListSpliceOne(T_)(LmiList(T_) * l_,        \
                                 LmiListIterator(T_) pos,	 \
                                 LmiList(T_) * src_,         \
                                 LmiListIterator(T_) it_)	 \
  {															 \
	LmiListIterator(T_) next;								 \
															 \
	LmiListIteratorAssign(T_)(&next, &it_);					 \
	LmiListIteratorIncrement(T_)(&next);					 \
															 \
	if (pos == it_ || pos == next) {						 \
	  return;												 \
	}														 \
															 \
	LmiListSplice(T_)(l_, pos, src_, it_, next);			 \
  }

/**
   {function visibility="private":
    {name: LmiListGetNodeSize}
    {parent: LmiList}
    {description: Get the size of this type\'s list node.}
    {prototype: LmiSizeT LmiListGetNodeSize(T_)(LmiList(T_)* l)}
    {template-parameter:
      {name: T_} {description: The type stored in the list.}}
	{parameter: {name: l} {description: The list or NULL.}}
    {return: The size of one node in the list.  All calls to the list\'s
	  allocator will be for allocations of this size.}
   } 
*/

#define Declare_LmiListGetNodeSize(T_) \
  LMI_INLINE_DECLARATION LmiSizeT LmiListGetNodeSize(T_)(const LmiList(T_)* l);

#define DefineInline_LmiListGetNodeSize(T_, INLINE_)				\
  INLINE_ LmiSizeT LmiListGetNodeSize(T_)(const LmiList(T_)* l) {	\
	return sizeof(LmiListNode_(T_));								\
  }

#define Declare_LmiListSpecificFuncs(T_) \
  Declare_LmiListSplice(T_) \
  Declare_LmiListSpliceOne(T_) \
	   Declare_LmiListGetNodeSize(T_)


#define DefineInline_LmiListFuncs(T_, INLINE_)            \
  DefineInline_LmiListIteratorContentOf(T_, INLINE_)      \
  	   DefineInline_LmiListIteratorContentOfConst(T_, INLINE_) \
       DefineInline_LmiListIteratorIncrement(T_, INLINE_) \
       DefineInline_LmiListIteratorDecrement(T_, INLINE_) \
       DefineInline_LmiListIteratorConstructExceptional(T_, INLINE_) \
       DefineInline_LmiListIteratorIsExceptional(T_, INLINE_) \
       DefineInline_LmiListConstIteratorContentOf(T_, INLINE_) \
       DefineInline_LmiListConstIteratorContentOfConst(T_, INLINE_) \
       DefineInline_LmiListConstIteratorIncrement(T_, INLINE_) \
       DefineInline_LmiListConstIteratorDecrement(T_, INLINE_) \
       DefineInline_LmiListConstIteratorConstructExceptional(T_, INLINE_) \
       DefineInline_LmiListConstIteratorIsExceptional(T_, INLINE_) \
       DefineInline_LmiListReverseIteratorFuncs(T_, INLINE_)   \
       DefineInline_LmiListCreateNode_(T_, INLINE_)            \
       DefineInline_LmiListHookNode_(T_, INLINE_)			   \
       DefineInline_LmiListUnhookNode_(T_, INLINE_)			   \
       DefineInline_LmiListGetAllocator(T_, INLINE_)		   \
       DefineInline_LmiListBegin(T_, INLINE_)             \
       DefineInline_LmiListBeginConst(T_, INLINE_)        \
       DefineInline_LmiListEnd(T_, INLINE_)               \
       DefineInline_LmiListEndConst(T_, INLINE_)          \
       DefineInline_LmiListSize(T_, INLINE_)              \
       DefineInline_LmiListMaxSize(T_, INLINE_)           \
       DefineInline_LmiListEmpty(T_, INLINE_)             \
       DefineInline_LmiListRBegin(T_, INLINE_)            \
       DefineInline_LmiListRBeginConst(T_, INLINE_)       \
       DefineInline_LmiListREnd(T_, INLINE_)              \
       DefineInline_LmiListREndConst(T_, INLINE_)         \
       DefineInline_LmiListFront(T_, INLINE_)             \
       DefineInline_LmiListFrontConst(T_, INLINE_)        \
       DefineInline_LmiListInsert(T_, INLINE_)            \
       DefineInline_LmiListInsertN(T_, INLINE_)           \
       DefineInline_LmiListInsertRange(T_, INLINE_)       \
       DefineInline_LmiListErase(T_, INLINE_)             \
       DefineInline_LmiListEraseRange(T_, INLINE_)        \
       DefineInline_LmiListClear(T_, INLINE_)             \
       DefineInline_LmiListResize(T_, INLINE_)            \
       DefineInline_LmiListPushFront(T_, INLINE_)         \
       DefineInline_LmiListPopFront(T_, INLINE_)          \
       DefineInline_LmiListBack(T_, INLINE_)              \
       DefineInline_LmiListBackConst(T_, INLINE_)         \
       DefineInline_LmiListPushBack(T_, INLINE_)          \
       DefineInline_LmiListPopBack(T_, INLINE_)           \
       DefineInline_LmiListConstructDefault(T_, INLINE_)  \
       DefineInline_LmiListDestruct(T_, INLINE_)          \
       DefineInline_LmiListConstructCopy(T_, INLINE_)     \
       DefineInline_LmiListAssign(T_, INLINE_)            \
       DefineInline_LmiListSwap(T_, INLINE_)              \
       DefineInline_LmiListConstructN(T_, INLINE_)        \
       DefineInline_LmiListConstructRange(T_, INLINE_)    \
       DefineInline_LmiListSplice(T_, INLINE_)            \
       DefineInline_LmiListSpliceOne(T_, INLINE_)            \
       DefineInline_LmiListGetNodeSize(T_, INLINE_)

#define DefineInline_LmiListTemplateFuncs(T_, InputIterator_, INLINE_) \
  DefineInline_LmiListInsertIteratorRange(T_, InputIterator_, INLINE_) \
       DefineInline_LmiListConstructIteratorRange(T_, InputIterator_, INLINE_)


#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS

#define DefineInlineHeader_LmiListFuncs(T_) \
  DefineInline_LmiListFuncs(T_, LMI_INLINE)
#define DefineInlineHeader_LmiListTemplateFuncs(T_, InputIterator_) \
  DefineInline_LmiListTemplateFuncs(T_, InputIterator_, LMI_INLINE)

#else

#define DefineInlineHeader_LmiListFuncs(T_) /* (defined as empty) */
#define DefineInlineHeader_LmiListTemplateFuncs(T_, InputIterator_) /* (defined as empty) */

#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS

#define DefineInlineSource_LmiListFuncs(T_) \
  DefineInline_LmiListFuncs(T_, LMI_INLINE_SOURCE_FILE)
#define DefineInlineSource_LmiListTemplateFuncs(T_, InputIterator_) \
  DefineInline_LmiListTemplateFuncs(T_, InputIterator_, LMI_INLINE_SOURCE_FILE)

#else

#define DefineInlineSource_LmiListFuncs(T_) /* (defined as empty) */
#define DefineInlineSource_LmiListTemplateFuncs(T_, InputIterator_) /* (defined as empty) */

#endif

#define Declare_LmiList(T_)                                             \
	Declare_LmiListNode(T_)												\
	Declare_LmiListClass(T_)											\
	DeclareInline_LmiReversibleContainer(LmiList(T_), T_,						\
		LmiListNodeBase_(T_) *,	const LmiListNodeBase_(T_) *,					\
		LmiSizeT, LmiDistanceT, LMI_INLINE_DECLARATION)										\
    DeclareInline_LmiSequenceFuncsPart(LmiList(T_), LMI_INLINE_DECLARATION)					\
    DeclareInline_LmiFrontInsertionSequenceFuncsPart(LmiList(T_), LMI_INLINE_DECLARATION)		\
    DeclareInline_LmiBackInsertionSequenceFuncsPart(LmiList(T_), LMI_INLINE_DECLARATION)		\
    Declare_LmiListInternalFuncs(T_)                                    \
    Declare_LmiListSpecificFuncs(T_)                                    \
    Declare_LmiBasicType(LmiListIterator(T_))                           \
    Declare_LmiBasicType(LmiListConstIterator(T_))                      \
    DefineInlineHeader_LmiListFuncs(T_)

#define Declare_LmiListTemplateFuncs(T_, InputIterator_) \
	DeclareInline_LmiSequenceTemplateFuncs(LmiList(T_), InputIterator_, LMI_INLINE_DECLARATION) \
    DefineInlineHeader_LmiListTemplateFuncs(T_, InputIterator_)


#define Define_LmiList(T_) \
  DefineInlineSource_LmiListFuncs(T_) \
       Define_LmiBasicType(LmiListIterator(T_)) \
       Define_LmiBasicType(LmiListConstIterator(T_))

#define Define_LmiListTemplateFuncs(T_, InputIterator_) \
    DefineInlineSource_LmiListTemplateFuncs(T_, InputIterator_)

#define Declare_LmiListEqual(T_) \
	LmiBool LmiListEqual(T_)(const LmiList(T_) *a, const LmiList(T_) *b);
#define Define_LmiListEqual(T_)        DefineInline_LmiListEqual(T_, LmiListEqual(T_), LmiEqual(T_), LMI_NO_INLINE)
#define Define_LmiListEqual_Static(T_) DefineInline_LmiListEqual(T_, LmiListEqual(T_), LmiEqual(T_), static)

#define Declare_LmiListEqualComp(T_, Comp_) \
	LmiBool LmiListEqualComp(T_, Comp_)(const LmiList(T_) *a, const LmiList(T_) *b);
#define Define_LmiListEqualComp(T_, Comp_)        DefineInline_LmiListEqual(T_, LmiListEqualComp(T_, Comp_), Comp_, LMI_NO_INLINE)
#define Define_LmiListEqualComp_Static(T_, Comp_) DefineInline_LmiListEqual(T_, LmiListEqualComp(T_, Comp_), Comp_, static)

#define Declare_LmiListLess(T_) \
	LmiBool LmiListLess(T_)(const LmiList(T_) *a, const LmiList(T_) *b);
#define Define_LmiListLess(T_)        DefineInline_LmiListLess(T_, LmiListLess(T_), LmiLess(T_), LMI_NO_INLINE)
#define Define_LmiListLess_Static(T_) DefineInline_LmiListLess(T_, LmiListLess(T_), LmiLess(T_), static)

#define Declare_LmiListLessComp(T_, Comp_) \
	LmiBool LmiListLessComp(T_, Comp_)(const LmiList(T_) *a, const LmiList(T_) *b);
#define Define_LmiListLessComp(T_, Comp_)        DefineInline_LmiListLess(T_, LmiListLessComp(T_, Comp_), Comp_, LMI_NO_INLINE)
#define Define_LmiListLessComp_Static(T_, Comp_) DefineInline_LmiListLess(T_, LmiListLessComp(T_, Comp_), Comp_, static)

#define LmiListSortRangeComp(T_, Comp_) LmiTemplate2(LmiListSortRangeComp, T_, Comp_)
#define LmiListSortComp(T_, Comp_)      LmiTemplate2(LmiListSortComp, T_, Comp_)
#define Declare_LmiListSortComp(T_, Comp_) \
	LmiListIterator(T_) LmiListSortRangeComp(T_, Comp_)(LmiList(T_) *list, LmiListIterator(T_) b, LmiListIterator(T_) e); \
	void LmiListSortComp(T_, Comp_)(LmiList(T_) *list);
#define Define_LmiListSortComp(T_, Comp_) \
	LmiListIterator(T_) LmiListSortRangeComp(T_, Comp_)(LmiList(T_) *list, LmiListIterator(T_) b, LmiListIterator(T_) e) \
	{ \
		LmiListIterator(T_) i = b; \
		LmiListIterator(T_) m = b; \
		LmiBool odd = LMI_FALSE; \
		while(i != e) \
		{ \
			LmiListIteratorIncrement(T_)(&i); \
			odd = !odd; \
			if(!odd) \
				LmiListIteratorIncrement(T_)(&m); \
		} \
		if(b != m) \
		{ \
			b = LmiListSortRangeComp(T_, Comp_)(list, b, m); \
			if(m != e) \
			{ \
				LmiBool first = LMI_TRUE; \
				m = LmiListSortRangeComp(T_, Comp_)(list, m, e); \
				i = b; \
				for(;;) \
				{ \
					if(Comp_(LmiListIteratorContentOf(T_)(&m), LmiListIteratorContentOf(T_)(&i))) \
					{ \
						LmiListIterator(T_) n = m; \
						LmiListIteratorIncrement(T_)(&n); \
						LmiListSpliceOne(T_)(list, i, list, m); \
						if(first) \
							b = m; \
						m = n; \
						if(m == e) \
							break; \
					} \
					else \
					{ \
						LmiListIteratorIncrement(T_)(&i); \
						if(i == m) \
							break; \
					} \
					first = LMI_FALSE; \
				} \
			} \
		} \
		return b; \
	} \
	void LmiListSortComp(T_, Comp_)(LmiList(T_) *list) \
	{ \
		LmiListSortRangeComp(T_, Comp_)(list, LmiListBegin(T_)(list), LmiListEnd(T_)(list)); \
	}

#define LmiListSortRange(T_)    LmiListSortRangeComp(T_, LmiLess(T_))
#define LmiListSort(T_)         LmiListSortComp(T_, LmiLess(T_))
#define Declare_LmiListSort(T_) Declare_LmiListSortComp(T_, LmiLess(T_))
#define Define_LmiListSort(T_)  Define_LmiListSortComp(T_, LmiLess(T_))

LMI_END_EXTERN_C

#endif /* LMI_LIST_H_ */
