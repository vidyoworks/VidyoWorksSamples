/**
{file:
	{name: LmiBinaryTree.h }
	{description: LMI ordered (binary tree) container.}
	{copyright:
		(c) 2009-2014 Vidyo, Inc.,
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

#ifndef LMI_BINARY_TREE_H_
#define LMI_BINARY_TREE_H_

#include <Lmi/Utils/LmiTemplate.h>
#include <Lmi/Utils/LmiNames.h>
#include <Lmi/Utils/LmiConcepts.h>
#include <Lmi/Utils/LmiAssociativeContainers.h>
#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUtility.h>

#include <Lmi/Utils/LmiMisc.h>
#include <Lmi/Utils/LmiAllocator.h>

LMI_BEGIN_EXTERN_C

#define LmiBinaryTreeNode(C_) LmiTemplate1(C_, Node)
#define LmiBinaryTreeNodeDelete(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Delete)
#define LmiBinaryTreeNodeRotateLeft(C_) LmiClassFunc(LmiBinaryTreeNode(C_), RotateLeft)
#define LmiBinaryTreeNodeRotateRight(C_) LmiClassFunc(LmiBinaryTreeNode(C_), RotateRight)
#define LmiBinaryTreeNodeBalance(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Balance)
#define LmiBinaryTreeNodeInsert(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Insert)

#define LmiBinaryTreeNodeGetMinimum(C_) LmiClassFunc(LmiBinaryTreeNode(C_), GetMinimum)
#define LmiBinaryTreeNodeGetMinimumConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), GetMinimumConst)
#define LmiBinaryTreeNodeGetMaximum(C_) LmiClassFunc(LmiBinaryTreeNode(C_), GetMaximum)
#define LmiBinaryTreeNodeGetMaximumConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), GetMaximumConst)
#define LmiBinaryTreeNodeFind(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Find)
#define LmiBinaryTreeNodeFindConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), FindConst)
#define LmiBinaryTreeNodeCount(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Count)
#define LmiBinaryTreeNodeLowerBound(C_) LmiClassFunc(LmiBinaryTreeNode(C_), LowerBound)
#define LmiBinaryTreeNodeLowerBoundConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), LowerBoundConst)
#define LmiBinaryTreeNodeUpperBound(C_) LmiClassFunc(LmiBinaryTreeNode(C_), UpperBound)
#define LmiBinaryTreeNodeUpperBoundConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), UpperBoundConst)
#define LmiBinaryTreeNodeEqualRange(C_) LmiClassFunc(LmiBinaryTreeNode(C_), EqualRange)
#define LmiBinaryTreeNodeEqualRangeConst(C_) LmiClassFunc(LmiBinaryTreeNode(C_), EqualRangeConst)
#define LmiBinaryTreeNodeCopy(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Copy)
#define LmiBinaryTreeNodeCheck(C_) LmiClassFunc(LmiBinaryTreeNode(C_), Check)

#define LmiBinaryTreeGetNodeSize(C_) LmiClassFunc(C_, GetNodeSize)
#define LmiBinaryTreeCheck(C_) LmiClassFunc(C_, Check)

#define Declare_LmiBinaryTreeTypes(C_, V_) \
	typedef struct LmiBinaryTreeNode(C_) \
	{ \
		V_ value; \
		struct LmiBinaryTreeNode(C_)* left; \
		struct LmiBinaryTreeNode(C_)* right; \
		struct LmiBinaryTreeNode(C_)* parent; \
		struct LmiBinaryTreeNode(C_)** pPtr; \
		LmiSizeT height; \
	} LmiBinaryTreeNode(C_); \
	\
	typedef struct \
	{ \
		LmiBinaryTreeNode(C_) end; \
		LmiSizeT size; \
		LmiAllocator* alloc; \
	} C_;

#define Declare_LmiBinaryTreeConstruct(C_) \
C_* LmiConstruct(C_)(C_* bt, LmiAllocator* alloc);

#define Define_LmiBinaryTreeConstruct(C_) \
C_* LmiConstruct(C_)(C_* bt, LmiAllocator* alloc) \
{ \
	bt->end.left = NULL; \
	bt->end.right = NULL; \
	bt->end.parent = NULL; \
	bt->end.pPtr = NULL; \
	bt->size = 0; \
	bt->alloc = alloc; \
	return bt; \
}

#define Declare_LmiBinaryTreeNodeDelete(C_) \
void LmiBinaryTreeNodeDelete(C_)(LmiBinaryTreeNode(C_) *node, LmiAllocator *alloc);

#define Define_LmiBinaryTreeNodeDelete(C_, V_) \
void LmiBinaryTreeNodeDelete(C_)(LmiBinaryTreeNode(C_) *node, LmiAllocator *alloc) \
{ \
	if(node->left != NULL) \
		LmiBinaryTreeNodeDelete(C_)(node->left, alloc); \
	if(node->right != NULL) \
		LmiBinaryTreeNodeDelete(C_)(node->right, alloc); \
	LmiDestruct(V_)(&node->value); \
	LmiAllocatorDeallocate(alloc, node, sizeof(LmiBinaryTreeNode(C_))); \
}

#define Define_LmiBinaryTreeDestruct(C_) \
void LmiDestruct(C_)(C_ *bt) \
{ \
	if(bt->end.left != NULL) \
		LmiBinaryTreeNodeDelete(C_)(bt->end.left, bt->alloc); \
}

#define Define_LmiBinaryTreeClear(C_) \
void LmiClear(C_)(C_ *bt) \
{ \
	if(bt->end.left != NULL) \
	{ \
		LmiBinaryTreeNodeDelete(C_)(bt->end.left, bt->alloc); \
		bt->end.left = NULL; \
		bt->size = 0; \
	} \
} \

#define Declare_LmiBinaryTreeNodeRotateLeft(C_) \
void LmiBinaryTreeNodeRotateLeft(C_)(LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeRotateLeft(C_) \
void LmiBinaryTreeNodeRotateLeft(C_)(LmiBinaryTreeNode(C_) *node) \
{ \
	LmiBinaryTreeNode(C_) *r = node->right; \
	LmiBinaryTreeNode(C_) *l = r->left; \
	*node->pPtr = r; \
	r->parent = node->parent; \
	r->pPtr = node->pPtr; \
	node->right = l; \
	if(l != NULL) \
	{ \
		l->parent = node; \
		l->pPtr = &node->right; \
	} \
	r->left = node; \
	node->parent = r; \
	node->pPtr = &r->left; \
}

#define Declare_LmiBinaryTreeNodeRotateRight(C_) \
void LmiBinaryTreeNodeRotateRight(C_)(LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeRotateRight(C_) \
void LmiBinaryTreeNodeRotateRight(C_)(LmiBinaryTreeNode(C_) *node) \
{ \
	LmiBinaryTreeNode(C_) *l = node->left; \
	LmiBinaryTreeNode(C_) *r = l->right; \
	*node->pPtr = l; \
	l->parent = node->parent; \
	l->pPtr = node->pPtr; \
	node->left = r; \
	if(r != NULL) \
	{ \
		r->parent = node; \
		r->pPtr = &node->left; \
	} \
	l->right = node; \
	node->parent = l; \
	node->pPtr = &l->right; \
}

#define Declare_LmiBinaryTreeNodeBalance(C_) \
void LmiBinaryTreeNodeBalance(C_)(LmiBinaryTreeNode(C_) *node, LmiBool removing);

#define Define_LmiBinaryTreeNodeBalance(C_) \
void LmiBinaryTreeNodeBalance(C_)(LmiBinaryTreeNode(C_) *node, LmiBool removing) \
{ \
	if(node->parent != NULL) /* don't balance sentinel */ \
	{ \
		LmiBinaryTreeNode(C_) *l = node->left; \
		LmiBinaryTreeNode(C_) *r = node->right; \
		LmiSizeT lh = l == NULL ? 0 : l->height; \
		LmiSizeT rh = r == NULL ? 0 : r->height; \
		\
		if(lh > rh + 1) \
		{ \
			LmiBinaryTreeNode(C_) *ll = l->left; \
			LmiBinaryTreeNode(C_) *lr = l->right; \
			LmiSizeT llh = ll == NULL ? 0 : ll->height; \
			LmiSizeT lrh = lr == NULL ? 0 : lr->height; \
			if(lrh > llh) \
			{ \
				LmiBinaryTreeNodeRotateLeft(C_)(l); \
				LmiBinaryTreeNodeRotateRight(C_)(node); \
				--l->height; \
				++lr->height; \
				if(removing) \
				{ \
					node->height -= 2; \
					if(lr->parent != NULL) \
						LmiBinaryTreeNodeBalance(C_)(lr->parent, removing); \
				} \
				else \
					--node->height; \
			} \
			else \
			{ \
				LmiBinaryTreeNodeRotateRight(C_)(node); \
				if(removing) \
				{ \
					node->height = lrh + 1; \
					l->height = node->height + 1; \
					if(lrh < llh && l->parent != NULL) \
						LmiBinaryTreeNodeBalance(C_)(l->parent, removing); \
				} \
				else \
					--node->height; \
			} \
		} \
		else if(rh > lh + 1) \
		{ \
			LmiBinaryTreeNode(C_) *rl = r->left; \
			LmiBinaryTreeNode(C_) *rr = r->right; \
			LmiSizeT rlh = rl == NULL ? 0 : rl->height; \
			LmiSizeT rrh = rr == NULL ? 0 : rr->height; \
			if(rlh > rrh) \
			{ \
				LmiBinaryTreeNodeRotateRight(C_)(r); \
				LmiBinaryTreeNodeRotateLeft(C_)(node); \
				--r->height; \
				++rl->height; \
				if(removing) \
				{ \
					node->height -= 2; \
					if(rl->parent != NULL) \
						LmiBinaryTreeNodeBalance(C_)(rl->parent, removing); \
				} \
				else \
					--node->height; \
			} \
			else \
			{ \
				LmiBinaryTreeNodeRotateLeft(C_)(node); \
				if(removing) \
				{ \
					node->height = rlh + 1; \
					r->height = node->height + 1; \
					if(rlh < rrh && r->parent != NULL) \
						LmiBinaryTreeNodeBalance(C_)(r->parent, removing); \
				} \
				else \
					--node->height; \
			} \
		} \
		else \
		{ \
			node->height = LmiMax(lh, rh) + 1; \
			if(node->parent != NULL) \
				LmiBinaryTreeNodeBalance(C_)(node->parent, removing); \
		} \
	} \
}

#define Declare_LmiUniqueBinaryTreeNodeInsert(C_) \
LmiPair(LmiIterator(C_), LmiBool) LmiBinaryTreeNodeInsert(C_)(LmiBinaryTreeNode(C_) *curNode, LmiBinaryTreeNode(C_) *newNode);

#define Define_LmiUniqueBinaryTreeNodeInsert(C_, K_, GetKey, L_) \
LmiPair(LmiIterator(C_), LmiBool) LmiBinaryTreeNodeInsert(C_)(LmiBinaryTreeNode(C_) *curNode, LmiBinaryTreeNode(C_) *newNode) \
{ \
	const K_ *curKey = GetKey(&curNode->value); \
	const K_ *newKey = GetKey(&newNode->value); \
	LmiPair(LmiIterator(C_), LmiBool) ret; \
	\
	if(L_(newKey, curKey)) \
	{ \
		if(curNode->left != NULL) \
			return LmiBinaryTreeNodeInsert(C_)(curNode->left, newNode); \
		curNode->left = newNode; \
		newNode->pPtr = &curNode->left; \
	} \
	else if(L_(curKey, newKey)) \
	{ \
		if(curNode->right != NULL) \
			return LmiBinaryTreeNodeInsert(C_)(curNode->right, newNode); \
		curNode->right = newNode; \
		newNode->pPtr = &curNode->right; \
	} \
	else \
	{ \
		ret.first = curNode; \
		ret.second = LMI_FALSE; \
		return ret; \
	} \
	newNode->parent = curNode; \
	LmiBinaryTreeNodeBalance(C_)(curNode, LMI_FALSE); \
	ret.first = newNode; \
	ret.second = LMI_TRUE; \
	return ret; \
}

#define Define_LmiUniqueBinaryTreeInsert(C_, V_) \
LmiPair(LmiIterator(C_), LmiBool) LmiInsert(C_)(C_ *bt, const V_ *value) \
{ \
	LmiPair(LmiIterator(C_), LmiBool) ret = {&bt->end, 0}; \
	LmiBinaryTreeNode(C_) *node = (LmiBinaryTreeNode(C_) *)LmiAllocatorAllocate(bt->alloc, sizeof(LmiBinaryTreeNode(C_))); \
	\
	if (node == NULL) \
		return ret; \
	if (LmiConstructCopy(V_)(&node->value, value) == NULL) { \
		LmiAllocatorDeallocate(bt->alloc, node, sizeof(LmiBinaryTreeNode(C_))); \
		return ret; \
	} \
	node->left = node->right = node->parent = NULL; \
	node->height = 1; \
	\
	if(bt->end.left != NULL) \
	{ \
		ret = LmiBinaryTreeNodeInsert(C_)(bt->end.left, node); \
		if (!ret.second) { \
			LmiBinaryTreeNodeDelete(C_)(node, bt->alloc); \
			return ret; \
		} \
	} \
	else \
	{ \
		bt->end.left = node; \
		node->parent = &bt->end; \
		node->pPtr = &bt->end.left; \
		ret.first = node; \
		ret.second = LMI_TRUE; \
	} \
	\
	bt->size++; \
	return ret; \
}

#define Declare_LmiMultipleBinaryTreeNodeInsert(C_) \
LmiIterator(C_) LmiBinaryTreeNodeInsert(C_)(LmiBinaryTreeNode(C_) *curNode, LmiBinaryTreeNode(C_) *newNode);

#define Define_LmiMultipleBinaryTreeNodeInsert(C_, K_, GetKey, L_) \
LmiIterator(C_) LmiBinaryTreeNodeInsert(C_)(LmiBinaryTreeNode(C_) *curNode, LmiBinaryTreeNode(C_) *newNode) \
{ \
	const K_ *curKey = GetKey(&curNode->value); \
	const K_ *newKey = GetKey(&newNode->value); \
	\
	if(L_(newKey, curKey)) \
	{ \
		if(curNode->left != NULL) \
			return LmiBinaryTreeNodeInsert(C_)(curNode->left, newNode); \
		curNode->left = newNode; \
		newNode->pPtr = &curNode->left; \
	} \
	else \
	{ \
		if(curNode->right != NULL) \
			return LmiBinaryTreeNodeInsert(C_)(curNode->right, newNode); \
		curNode->right = newNode; \
		newNode->pPtr = &curNode->right; \
	} \
	newNode->parent = curNode; \
	LmiBinaryTreeNodeBalance(C_)(curNode, LMI_FALSE); \
	return newNode; \
}

#define Define_LmiMultipleBinaryTreeInsert(C_, V_) \
LmiIterator(C_) LmiInsert(C_)(C_ *bt, const V_ *value) \
{ \
	LmiBinaryTreeNode(C_) *node = (LmiBinaryTreeNode(C_) *)LmiAllocatorAllocate(bt->alloc, sizeof(LmiBinaryTreeNode(C_))); \
	LmiIterator(C_) ret; \
	\
	if (node == NULL) \
		return NULL; \
	if (LmiConstructCopy(V_)(&node->value, value) == NULL) { \
		LmiAllocatorDeallocate(bt->alloc, node, sizeof(LmiBinaryTreeNode(C_))); \
		return &bt->end; \
	} \
	node->left = node->right = node->parent = NULL; \
	node->height = 1; \
	\
	if(bt->end.left != NULL) \
	{ \
		ret = LmiBinaryTreeNodeInsert(C_)(bt->end.left, node); \
	} \
	else \
	{ \
		bt->end.left = node; \
		node->parent = &bt->end; \
		node->pPtr = &bt->end.left; \
		ret = node; \
	} \
	\
	bt->size++; \
	return ret; \
}

#define Declare_LmiBinaryTreeNodeGetMinimum(C_) \
LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeGetMinimum(C_)(LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeGetMinimum(C_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMinimum(C_)(LmiBinaryTreeNode(C_) *node) \
{ \
	return node->left != NULL ? LmiBinaryTreeNodeGetMinimum(C_)(node->left) : node; \
}

#define Declare_LmiBinaryTreeNodeGetMinimumConst(C_) \
const LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeGetMinimumConst(C_)(const LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeGetMinimumConst(C_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMinimumConst(C_)(const LmiBinaryTreeNode(C_) *node) \
{ \
	return node->left != NULL ? LmiBinaryTreeNodeGetMinimumConst(C_)(node->left) : node; \
}

#define Declare_LmiBinaryTreeNodeGetMaximum(C_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMaximum(C_)(LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeGetMaximum(C_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMaximum(C_)(LmiBinaryTreeNode(C_) *node) \
{ \
	return node->right != NULL ? LmiBinaryTreeNodeGetMaximum(C_)(node->right) : node; \
}

#define Declare_LmiBinaryTreeNodeGetMaximumConst(C_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMaximumConst(C_)(const LmiBinaryTreeNode(C_) *node);

#define Define_LmiBinaryTreeNodeGetMaximumConst(C_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeGetMaximumConst(C_)(const LmiBinaryTreeNode(C_) *node) \
{ \
	return node->right != NULL ? LmiBinaryTreeNodeGetMaximumConst(C_)(node->right) : node; \
}

#define Define_LmiBinaryTreeBegin(C_) \
LmiIterator(C_) LmiBegin(C_)(C_ *bt) \
{ \
	return bt->end.left != NULL ? LmiBinaryTreeNodeGetMinimum(C_)(bt->end.left) : &bt->end; \
}

#define Define_LmiBinaryTreeEnd(C_) \
LmiIterator(C_) LmiEnd(C_)(C_ *bt) \
{ \
	return &bt->end; \
}

#define Define_LmiBinaryTreeBeginConst(C_) \
LmiConstIterator(C_) LmiBeginConst(C_)(const C_ *bt) \
{ \
	return bt->end.left != NULL ? LmiBinaryTreeNodeGetMinimumConst(C_)(bt->end.left) : &bt->end; \
}

#define Define_LmiBinaryTreeEndConst(C_) \
LmiConstIterator(C_) LmiEndConst(C_)(const C_ *bt) \
{ \
	return &bt->end; \
}

/* $ RBegin, REnd */

#define DefineInline_LmiBinaryTreeIteratorIncrement(C_, INLINE_) \
INLINE_ LmiIterator(C_)* LmiIncrement(LmiIterator(C_))(LmiIterator(C_) *iter) \
{ \
	if((*iter)->right != NULL) \
		*iter = LmiBinaryTreeNodeGetMinimum(C_)((*iter)->right); \
	else \
	{ \
		for(;;) \
		{ \
			LmiBinaryTreeNode(C_) *last = *iter; \
			*iter = (*iter)->parent; \
			if((*iter)->parent == NULL || (*iter)->left == last) \
				break; \
		} \
	} \
	return iter; \
}

#define DefineInline_LmiBinaryTreeIteratorDecrement(C_, INLINE_) \
INLINE_ LmiIterator(C_)* LmiDecrement(LmiIterator(C_))(LmiIterator(C_) *iter) \
{ \
	if((*iter)->left != NULL) \
		*iter = LmiBinaryTreeNodeGetMaximum(C_)((*iter)->left); \
	else \
	{ \
		for(;;) \
		{ \
			LmiBinaryTreeNode(C_) *last = *iter; \
			*iter = (*iter)->parent; \
			if((*iter)->right == last) \
				break; \
		} \
	} \
	return iter; \
}

#define DefineInline_LmiBinaryTreeIteratorContentOf(C_, V_, INLINE_) \
INLINE_ V_* LmiContentOf(LmiIterator(C_))(LmiIterator(C_) *iter) \
{ \
	return &(*iter)->value; \
}

#define DefineInline_LmiBinaryTreeIteratorContentOfConst(C_, V_, INLINE_) \
INLINE_ const V_* LmiContentOfConst(LmiIterator(C_))(const LmiIterator(C_) *iter) \
{ \
	return &(*iter)->value; \
}

#define DefineInline_LmiBinaryTreeIteratorIsExceptional(C_, INLINE_) \
INLINE_ LmiBool LmiIsExceptional(LmiIterator(C_))(const LmiIterator(C_) iter) \
{ \
	return iter == NULL; \
}

#define DefineInline_LmiBinaryTreeIteratorConstructExceptional(C_, INLINE_) \
INLINE_ LmiIterator(C_)* LmiConstructExceptional(LmiIterator(C_))(LmiIterator(C_)* iter) \
{ \
	*iter = NULL; \
	return iter; \
}

#define DefineInline_LmiBinaryTreeConstIteratorIncrement(C_, INLINE_) \
INLINE_ LmiConstIterator(C_)* LmiIncrement(LmiConstIterator(C_))(LmiConstIterator(C_) *iter) \
{ \
	if((*iter)->right != NULL) \
		*iter = LmiBinaryTreeNodeGetMinimumConst(C_)((*iter)->right); \
	else \
	{ \
		for(;;) \
		{ \
			const LmiBinaryTreeNode(C_) *last = *iter; \
			*iter = (*iter)->parent; \
			if((*iter)->parent == NULL || (*iter)->left == last) \
				break; \
		} \
	} \
	return iter; \
}

#define DefineInline_LmiBinaryTreeConstIteratorDecrement(C_, INLINE_) \
INLINE_ LmiConstIterator(C_)* LmiDecrement(LmiConstIterator(C_))(LmiConstIterator(C_) *iter) \
{ \
	if((*iter)->left != NULL) \
		*iter = LmiBinaryTreeNodeGetMaximumConst(C_)((*iter)->left); \
	else \
	{ \
		for(;;) \
		{ \
			const LmiBinaryTreeNode(C_) *last = *iter; \
			*iter = (*iter)->parent; \
			if((*iter)->right == last) \
				break; \
		} \
	} \
	return iter; \
}

#define DefineInline_LmiBinaryTreeConstIteratorContentOf(C_, V_, INLINE_) \
INLINE_ const V_* LmiContentOf(LmiConstIterator(C_))(LmiConstIterator(C_) *iter) \
{ \
	return &(*iter)->value; \
}

#define DefineInline_LmiBinaryTreeConstIteratorContentOfConst(C_, V_, INLINE_) \
INLINE_ const V_* LmiContentOfConst(LmiConstIterator(C_))(const LmiConstIterator(C_) *iter) \
{ \
	return &(*iter)->value; \
}

#define DefineInline_LmiBinaryTreeConstIteratorIsExceptional(C_, INLINE_) \
INLINE_ LmiBool LmiIsExceptional(LmiConstIterator(C_))(const LmiConstIterator(C_) iter) \
{ \
	return iter == NULL; \
}

#define DefineInline_LmiBinaryTreeConstIteratorConstructExceptional(C_, INLINE_) \
INLINE_ LmiConstIterator(C_)* LmiConstructExceptional(LmiConstIterator(C_))(LmiConstIterator(C_)* iter) \
{ \
	*iter = NULL; \
	return iter; \
}

#define Declare_LmiBinaryTreeNodeFind(C_, K_) \
LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeFind(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeFind(C_, K_, GetKey, L_) \
LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeFind(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	if(L_(key, curKey)) \
		return node->left != NULL ? LmiBinaryTreeNodeFind(C_)(node->left, key) : NULL; \
	if(L_(curKey, key)) \
		return node->right != NULL ? LmiBinaryTreeNodeFind(C_)(node->right, key) : NULL; \
	return node; \
}

#define Declare_LmiBinaryTreeNodeFindConst(C_, K_) \
const LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeFindConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeFindConst(C_, K_, GetKey, L_) \
const LmiBinaryTreeNode(C_)* LmiBinaryTreeNodeFindConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	if(L_(key, curKey)) \
		return node->left != NULL ? LmiBinaryTreeNodeFindConst(C_)(node->left, key) : NULL; \
	if(L_(curKey, key)) \
		return node->right != NULL ? LmiBinaryTreeNodeFindConst(C_)(node->right, key) : NULL; \
	return node; \
}

#define Define_LmiBinaryTreeFind(C_, K_) \
LmiIterator(C_) LmiFind(C_)(C_ *bt, const K_ *key) \
{ \
	LmiBinaryTreeNode(C_) *n; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	n = LmiBinaryTreeNodeFind(C_)(bt->end.left, key); \
	return n != NULL ? n : &bt->end; \
}

#define Define_LmiBinaryTreeFindConst(C_, K_) \
LmiConstIterator(C_) LmiFindConst(C_)(const C_ *bt, const K_ *key) \
{ \
	const LmiBinaryTreeNode(C_) *n; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	n = LmiBinaryTreeNodeFindConst(C_)(bt->end.left, key); \
	return n != NULL ? n : &bt->end; \
}

#define Declare_LmiBinaryTreeNodeCount(C_, K_) \
LmiSizeType(C_) LmiBinaryTreeNodeCount(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeCount(C_, K_, GetKey, L_, AllowMultiples) \
LmiSizeType(C_) LmiBinaryTreeNodeCount(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	if(L_(key, curKey)) \
		return node->left != NULL ? LmiBinaryTreeNodeCount(C_)(node->left, key) : 0; \
	if(L_(curKey, key)) \
		return node->right != NULL ? LmiBinaryTreeNodeCount(C_)(node->right, key) : 0; \
	if(!AllowMultiples) \
		return 1; \
	return 1 + (node->left != NULL ? LmiBinaryTreeNodeCount(C_)(node->left, key) : 0) \
		+ (node->right != NULL ? LmiBinaryTreeNodeCount(C_)(node->right, key) : 0); \
}

#define Define_LmiBinaryTreeCount(C_, K_) \
LmiSizeType(C_) LmiCount(C_)(const C_ *bt, const K_ *key) \
{ \
	return bt->end.left != NULL ? LmiBinaryTreeNodeCount(C_)(bt->end.left, key) : 0; \
}

#define Declare_LmiBinaryTreeNodeLowerBound(C_, K_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeLowerBound(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeLowerBound(C_, K_, GetKey, L_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeLowerBound(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	LmiBinaryTreeNode(C_) *lb; \
	if(L_(curKey, key)) \
		return node->right != NULL ? LmiBinaryTreeNodeLowerBound(C_)(node->right, key) : NULL; \
	if(node->left == NULL) \
		return node; \
	lb = LmiBinaryTreeNodeLowerBound(C_)(node->left, key); \
	return lb != NULL ? lb : node; \
}

#define Declare_LmiBinaryTreeNodeLowerBoundConst(C_, K_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeLowerBoundConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeLowerBoundConst(C_, K_, GetKey, L_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeLowerBoundConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	const LmiBinaryTreeNode(C_) *lb; \
	if(L_(curKey, key)) \
		return node->right != NULL ? LmiBinaryTreeNodeLowerBoundConst(C_)(node->right, key) : NULL; \
	if(node->left == NULL) \
		return node; \
	lb = LmiBinaryTreeNodeLowerBoundConst(C_)(node->left, key); \
	return lb != NULL ? lb : node; \
}

#define Declare_LmiBinaryTreeNodeUpperBound(C_, K_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeUpperBound(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeUpperBound(C_, K_, GetKey, L_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeUpperBound(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	LmiBinaryTreeNode(C_) *ub; \
	if(!L_(key, curKey)) \
		return node->right != NULL ? LmiBinaryTreeNodeUpperBound(C_)(node->right, key) : NULL; \
	if(node->left == NULL) \
		return node; \
	ub = LmiBinaryTreeNodeUpperBound(C_)(node->left, key); \
	return ub != NULL ? ub : node; \
}

#define Declare_LmiBinaryTreeNodeUpperBoundConst(C_, K_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeUpperBoundConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeUpperBoundConst(C_, K_, GetKey, L_) \
const LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeUpperBoundConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	const LmiBinaryTreeNode(C_) *ub; \
	if(!L_(key, curKey)) \
		return node->right != NULL ? LmiBinaryTreeNodeUpperBoundConst(C_)(node->right, key) : NULL; \
	if(node->left == NULL) \
		return node; \
	ub = LmiBinaryTreeNodeUpperBoundConst(C_)(node->left, key); \
	return ub != NULL ? ub : node; \
}

#define Define_LmiBinaryTreeLowerBound(C_, K_) \
LmiIterator(C_) LmiLowerBound(C_)(C_ *bt, const K_ *key) \
{ \
	LmiBinaryTreeNode(C_) *lb; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	lb = LmiBinaryTreeNodeLowerBound(C_)(bt->end.left, key); \
	return lb != NULL ? lb : &bt->end; \
}

#define Define_LmiBinaryTreeLowerBoundConst(C_, K_) \
LmiConstIterator(C_) LmiLowerBoundConst(C_)(const C_ *bt, const K_ *key) \
{ \
	const LmiBinaryTreeNode(C_) *lb; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	lb = LmiBinaryTreeNodeLowerBoundConst(C_)(bt->end.left, key); \
	return lb != NULL ? lb : &bt->end; \
}

#define Define_LmiBinaryTreeUpperBound(C_, K_) \
LmiIterator(C_) LmiUpperBound(C_)(C_ *bt, const K_ *key) \
{ \
	LmiBinaryTreeNode(C_) *ub; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	ub = LmiBinaryTreeNodeUpperBound(C_)(bt->end.left, key); \
	return ub != NULL ? ub : &bt->end; \
}

#define Define_LmiBinaryTreeUpperBoundConst(C_, K_) \
LmiConstIterator(C_) LmiUpperBoundConst(C_)(const C_ *bt, const K_ *key) \
{ \
	const LmiBinaryTreeNode(C_) *ub; \
	if(bt->end.left == NULL) \
		return &bt->end; \
	ub = LmiBinaryTreeNodeUpperBoundConst(C_)(bt->end.left, key); \
	return ub != NULL ? ub : &bt->end; \
}

#define Declare_LmiBinaryTreeNodeEqualRange(C_, K_) \
LmiPair(LmiIterator(C_), LmiIterator(C_)) LmiBinaryTreeNodeEqualRange(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeEqualRange(C_, K_, GetKey, L_, AllowMultiples) \
LmiPair(LmiIterator(C_), LmiIterator(C_)) LmiBinaryTreeNodeEqualRange(C_)(LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	LmiPair(LmiIterator(C_), LmiIterator(C_)) ret; \
	if(L_(key, curKey)) \
	{ \
		if(node->left != NULL) \
			return LmiBinaryTreeNodeEqualRange(C_)(node->left, key); \
		else { \
			ret.first = NULL; \
			ret.second = NULL; \
			return ret; \
		} \
	} \
	if(L_(curKey, key)) \
	{ \
		if(node->right != NULL) \
			return LmiBinaryTreeNodeEqualRange(C_)(node->right, key); \
		else { \
			ret.first = NULL; \
			ret.second = NULL; \
			return ret; \
		} \
	} \
	if(!AllowMultiples) \
	{ \
		ret.first = node; \
		ret.second = node; \
		LmiIncrement(LmiIterator(C_))(&ret.second); \
		return ret; \
	} \
	ret.first = node->left != NULL ? LmiBinaryTreeNodeLowerBound(C_)(node->left, key) : NULL; \
	if(ret.first == NULL) \
		ret.first = node; \
	ret.second = node->right != NULL ? LmiBinaryTreeNodeUpperBound(C_)(node->right, key) : NULL; \
	if(ret.second == NULL) \
	{ \
		ret.second = node; \
		LmiIncrement(LmiIterator(C_))(&ret.second); \
	} \
	\
	return ret; \
}

#define Declare_LmiBinaryTreeNodeEqualRangeConst(C_, K_) \
LmiPair(LmiConstIterator(C_), LmiConstIterator(C_)) LmiBinaryTreeNodeEqualRangeConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key);

#define Define_LmiBinaryTreeNodeEqualRangeConst(C_, K_, GetKey, L_, AllowMultiples) \
LmiPair(LmiConstIterator(C_), LmiConstIterator(C_)) LmiBinaryTreeNodeEqualRangeConst(C_)(const LmiBinaryTreeNode(C_) *node, const K_ *key) \
{ \
	const K_ *curKey = GetKey(&node->value); \
	LmiPair(LmiConstIterator(C_), LmiConstIterator(C_)) ret; \
	if(L_(key, curKey)) \
	{ \
		if(node->left != NULL) \
			return LmiBinaryTreeNodeEqualRangeConst(C_)(node->left, key); \
		else { \
			ret.first = NULL; \
			ret.second = NULL; \
			return ret; \
		} \
	} \
	if(L_(curKey, key)) \
	{ \
		if(node->right != NULL) \
			return LmiBinaryTreeNodeEqualRangeConst(C_)(node->right, key); \
		else { \
			ret.first = NULL; \
			ret.second = NULL; \
			return ret; \
		} \
	} \
	if(!AllowMultiples) \
	{ \
		ret.first = node; \
		ret.second = node; \
		LmiIncrement(LmiConstIterator(C_))(&ret.second); \
		return ret; \
	} \
	ret.first = node->left != NULL ? LmiBinaryTreeNodeLowerBoundConst(C_)(node->left, key) : NULL; \
	if(ret.first == NULL) \
		ret.first = node; \
	ret.second = node->right != NULL ? LmiBinaryTreeNodeUpperBoundConst(C_)(node->right, key) : NULL; \
	if(ret.second == NULL) \
	{ \
		ret.second = node; \
		LmiIncrement(LmiConstIterator(C_))(&ret.second); \
	} \
	\
	return ret; \
}

#define Define_LmiBinaryTreeEqualRange(C_, K_) \
LmiPair(LmiIterator(C_), LmiIterator(C_)) LmiEqualRange(C_)(C_ *bt, const K_ *key) \
{ \
	LmiPair(LmiIterator(C_), LmiIterator(C_)) ret; \
	if(bt->end.left != NULL) { \
		ret = LmiBinaryTreeNodeEqualRange(C_)(bt->end.left, key); \
		if(ret.second == NULL) { \
			ret.second = &bt->end; \
			if(ret.first == NULL) \
				ret.first = &bt->end; \
		} \
	} \
	else { \
		ret.first = ret.second = &bt->end; \
	} \
	return ret; \
}

#define Define_LmiBinaryTreeEqualRangeConst(C_, K_) \
LmiPair(LmiConstIterator(C_), LmiConstIterator(C_)) LmiEqualRangeConst(C_)(const C_ *bt, const K_ *key) \
{ \
	LmiPair(LmiConstIterator(C_), LmiConstIterator(C_)) ret; \
	if(bt->end.left != NULL) { \
		ret = LmiBinaryTreeNodeEqualRangeConst(C_)(bt->end.left, key); \
		if(ret.second == NULL) { \
			ret.second = &bt->end; \
			if(ret.first == NULL) \
				ret.first = &bt->end; \
		} \
	} \
	else { \
		ret.first = ret.second = &bt->end; \
	} \
	return ret; \
}

#define Define_LmiBinaryTreeErase(C_, V_) \
LmiIterator(C_) LmiErase(C_)(C_ *bt, LmiIterator(C_) node) \
{ \
	LmiBinaryTreeNode(C_) *sub, *bal; \
	LmiIterator(C_) ret = node; \
	LmiIncrement(LmiIterator(C_))(&ret); \
	\
	if(node->left != NULL) \
	{ \
		sub = LmiBinaryTreeNodeGetMaximum(C_)(node->left); \
		bal = sub->parent; \
		*sub->pPtr = sub->left; \
		if(sub->left != NULL) \
		{ \
			sub->left->parent = sub->parent; \
			sub->left->pPtr = sub->pPtr; \
		} \
	} \
	else if(node->right != NULL) \
	{ \
		sub = LmiBinaryTreeNodeGetMinimum(C_)(node->right); \
		bal = sub->parent; \
		*sub->pPtr = sub->right; \
		if(sub->right != NULL) \
		{ \
			sub->right->parent = sub->parent; \
			sub->right->pPtr = sub->pPtr; \
		} \
	} \
	else \
	{ \
		sub = NULL; \
		bal = node->parent; \
		*node->pPtr = NULL; \
	} \
	\
	if(bal != NULL) \
		LmiBinaryTreeNodeBalance(C_)(bal, LMI_TRUE); \
	\
	if(sub != NULL) \
	{ \
		sub->left = node->left; \
		sub->right = node->right; \
		sub->parent = node->parent; \
		sub->pPtr = node->pPtr; \
		sub->height = node->height; \
		*sub->pPtr = sub; \
		if(sub->left != NULL) \
		{ \
			sub->left->parent = sub; \
			sub->left->pPtr = &sub->left; \
		} \
		if(sub->right != NULL) \
		{ \
			sub->right->parent = sub; \
			sub->right->pPtr = &sub->right; \
		} \
	} \
	\
	LmiDestruct(V_)(&node->value); \
	LmiAllocatorDeallocate(bt->alloc, node, sizeof(LmiBinaryTreeNode(C_))); \
	bt->size--; \
	\
	return ret; \
}

#define Define_LmiBinaryTreeEraseRange(C_) \
LmiIterator(C_) LmiEraseRange(C_)(C_ *bt, LmiIterator(C_) first, LmiIterator(C_) last) \
{ \
	while(first != last) \
	{ \
		LmiIterator(C_) p = first; \
		LmiIncrement(LmiIterator(C_))(&first); \
		LmiErase(C_)(bt, p); \
	} \
	return last; \
}

#define Define_LmiBinaryTreeEraseKey(C_, K_) \
LmiSizeT LmiEraseKey(C_)(C_ *bt, const K_ *key) \
{ \
	LmiPair(LmiIterator(C_), LmiIterator(C_)) range; \
	LmiSizeT rangeSize = 0; \
	\
	range = LmiEqualRange(C_)(bt, key); \
	while(range.first != range.second) { \
		LmiIterator(C_) p = range.first; \
		LmiIncrement(LmiIterator(C_))(&range.first); \
		LmiErase(C_)(bt, p); \
		rangeSize++; \
	} \
	return rangeSize; \
}

#define Define_LmiBinaryTreeSize(C_) \
LmiSizeT LmiSize(C_)(const C_ *bt) \
{ \
	return bt->size; \
}

#define Define_LmiBinaryTreeMaxSize(C_) \
LmiSizeT LmiMaxSize(C_)(const C_ *bt) \
{ \
	return LMI_SIZE_T_MAX; \
}

#define Define_LmiBinaryTreeEmpty(C_) \
LmiBool LmiEmpty(C_)(const C_ *bt) \
{ \
	return bt->size == 0; \
}

#define Declare_LmiBinaryTreeGetAllocator(C_) \
LmiAllocator *LmiGetAllocator(C_)(const C_ *bt);

#define Define_LmiBinaryTreeGetAllocator(C_) \
LmiAllocator *LmiGetAllocator(C_)(const C_ *bt) \
{ \
	return bt->alloc; \
}

#define Declare_LmiBinaryTreeGetNodeSize(C_) \
LMI_INLINE_DECLARATION LmiSizeT LmiBinaryTreeGetNodeSize(C_)(const C_* bt);

#define DefineInline_LmiBinaryTreeGetNodeSize(C_, INLINE_) \
INLINE_ LmiSizeT LmiBinaryTreeGetNodeSize(C_)(const C_* bt) { \
	return sizeof(LmiBinaryTreeNode(C_)); \
}

/* Not part of STL for map, but useful */
#define Declare_LmiBinaryTreeFront(C_, V_) \
V_* LmiFront(C_)(C_* bt);

#define Define_LmiBinaryTreeFront(C_, V_) \
V_* LmiFront(C_)(C_* bt) \
{ \
	LmiBinaryTreeNode(C_) *front; \
	\
	if (bt->end.left == NULL) return NULL; \
	front = LmiBinaryTreeNodeGetMinimum(C_)(bt->end.left); \
	return &front->value; \
}

#define Declare_LmiBinaryTreeBack(C_, V_) \
V_* LmiBack(C_)(C_* bt);

#define Define_LmiBinaryTreeBack(C_, V_) \
V_* LmiBack(C_)(C_* bt) \
{ \
	LmiBinaryTreeNode(C_) *back; \
	\
	if (bt->end.left == NULL) return NULL; \
	back = LmiBinaryTreeNodeGetMaximum(C_)(bt->end.left); \
	return &back->value; \
}

#define Declare_LmiBinaryTreeNodeCopy(C_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeCopy(C_)(LmiBinaryTreeNode(C_) *node, \
	LmiBinaryTreeNode(C_) *parent, LmiBinaryTreeNode(C_) **pPtr, LmiAllocator *alloc);

#define Define_LmiBinaryTreeNodeCopy(C_, V_) \
LmiBinaryTreeNode(C_) *LmiBinaryTreeNodeCopy(C_)(LmiBinaryTreeNode(C_) *node, \
	LmiBinaryTreeNode(C_) *parent, LmiBinaryTreeNode(C_) **pPtr, LmiAllocator *alloc) \
{ \
	LmiBinaryTreeNode(C_) *newNode = (LmiBinaryTreeNode(C_) *)LmiAllocatorAllocate(alloc, sizeof(LmiBinaryTreeNode(C_))); \
	if(newNode == NULL) \
		return NULL; \
	if(LmiConstructCopy(V_)(&newNode->value, &node->value) == NULL) \
		goto FAIL1; \
	if(node->left != NULL) \
	{ \
		newNode->left = LmiBinaryTreeNodeCopy(C_)(node->left, newNode, &newNode->left, alloc); \
		if(newNode->left == NULL) \
			goto FAIL2; \
	} \
	else \
		newNode->left = NULL; \
	if(node->right != NULL) \
	{ \
		newNode->right = LmiBinaryTreeNodeCopy(C_)(node->right, newNode, &newNode->right, alloc); \
		if(newNode->right == NULL) \
			goto FAIL3; \
	} \
	else \
		newNode->right = NULL; \
	newNode->parent = parent; \
	newNode->pPtr = pPtr; \
	newNode->height = node->height; \
	return newNode; \
	\
	FAIL3: if(newNode->left == NULL) \
		LmiBinaryTreeNodeDelete(C_)(newNode->left, alloc); \
	FAIL2: LmiDestruct(V_)(&newNode->value); \
	FAIL1: LmiAllocatorDeallocate(alloc, newNode, sizeof(LmiBinaryTreeNode(C_))); \
	return NULL; \
}

#define Define_LmiBinaryTreeConstructCopy(C_) \
C_ *LmiConstructCopy(C_ )(C_ *d, const C_ *s) \
{ \
	if(s->end.left != NULL) \
	{ \
		d->end.left = LmiBinaryTreeNodeCopy(C_ )(s->end.left, &d->end, &d->end.left, s->alloc); \
		if(d->end.left == NULL) \
			return NULL; \
	} \
	else \
		d->end.left = NULL; \
	d->end.right = NULL; \
	d->end.parent = NULL; \
	d->end.pPtr = NULL; \
	d->size = s->size; \
	d->alloc = s->alloc; \
	return d; \
}

#define Define_LmiBinaryTreeAssign(C_) \
C_ *LmiAssign(C_)(C_ *d, const C_ *s) \
{ \
	LmiBinaryTreeNode(C_) *newTree; \
	\
	if(s->end.left != NULL) \
	{ \
		newTree = LmiBinaryTreeNodeCopy(C_)(s->end.left, &d->end, &d->end.left, d->alloc); \
		if(newTree == NULL) \
			return NULL; \
	} \
	else \
		newTree = NULL; \
	\
	if(d->end.left != NULL) \
		LmiBinaryTreeNodeDelete(C_)(d->end.left, d->alloc); \
	d->end.left = newTree; \
	d->size = s->size; \
	return d; \
}

#define Define_LmiBinaryTreeSwap(C_) \
LmiBool LmiSwap(C_)(C_ *a, C_ *b) \
{ \
	if(a->alloc == b->alloc) \
	{ \
		LmiBinaryTreeNode(C_) *root = a->end.left; \
		LmiSizeT size = a->size; \
		a->end.left = b->end.left; \
		a->size = b->size; \
		b->end.left = root; \
		b->size = size; \
		if(a->end.left != NULL) \
		{ \
			a->end.left->parent = &a->end; \
			a->end.left->pPtr = &a->end.left; \
		} \
		if(b->end.left != NULL) \
		{ \
			b->end.left->parent = &b->end; \
			b->end.left->pPtr = &b->end.left; \
		} \
		return LMI_TRUE; \
	} \
	else \
	{ \
		C_ t; \
		LmiBool ok; \
		if (LmiConstruct(C_)(&t, a->alloc) == NULL) \
			return LMI_FALSE; \
		ok = LmiSwap(C_)(a, &t) && \
			LmiAssign(C_)(a, b) != NULL && \
			LmiAssign(C_)(b, &t) != NULL; \
		LmiDestruct(C_)(&t); \
		return ok; \
	} \
}

#define Define_LmiBinaryTreeCheck(C_, GetKey, L_, AllowMultiples, Test) \
	void LmiBinaryTreeNodeCheck(C_)(const LmiBinaryTreeNode(C_) *node, LmiSizeT *numNodes) \
	{ \
		const LmiBinaryTreeNode(C_) *L = node->left, *R = node->right; \
		LmiSizeT lh, rh; \
		LmiSizeT lSize, rSize; \
	\
		if(L != NULL) \
		{ \
			LmiBinaryTreeNodeCheck(C_)(L, &lSize); \
			if(AllowMultiples) \
				Test(!L_(GetKey(&node->value), GetKey(&L->value))); \
			else \
				Test(L_(GetKey(&L->value), GetKey(&node->value))); \
			Test(L->parent == node); \
			Test(L->pPtr == &node->left); \
			lh = L->height; \
		} \
		else \
		{ \
			lSize = 0; \
			lh = 0; \
		} \
	\
		if(R != NULL) \
		{ \
			LmiBinaryTreeNodeCheck(C_)(R, &rSize); \
			if(AllowMultiples) \
				Test(!L_(GetKey(&R->value), GetKey(&node->value))); \
			else \
				Test(L_(GetKey(&node->value), GetKey(&R->value))); \
			Test(R->parent == node); \
			Test(R->pPtr == &node->right); \
			rh = R->height; \
		} \
		else \
		{ \
			rSize = 0; \
			rh = 0; \
		} \
	\
		Test(rh <= (lh + 1)); \
		Test(lh <= (rh + 1)); \
	\
		Test(node->height == (LmiMax(lh, rh) + 1)); \
	\
		*numNodes = lSize + rSize + 1; \
	} \
	\
	void LmiBinaryTreeCheck(C_)(const C_ *t) \
	{ \
		Test(t->end.right == NULL); \
		Test(t->end.parent == NULL); \
		Test(t->end.pPtr == NULL); \
		if (t->end.left != NULL) { \
			LmiSizeT numNodes; \
			LmiBinaryTreeNodeCheck(C_)(t->end.left, &numNodes); \
			Test(numNodes == t->size); \
			Test(t->end.left->parent == &t->end); \
			Test(t->end.left->pPtr== &t->end.left); \
		} \
		else { \
			Test(t->size == 0); \
		} \
	}

#define Declare_LmiBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiBinaryTreeNodeDelete(C_) \
	Declare_LmiBinaryTreeNodeRotateLeft(C_) \
	Declare_LmiBinaryTreeNodeRotateRight(C_) \
	Declare_LmiBinaryTreeNodeBalance(C_) \
	Declare_LmiBinaryTreeNodeGetMinimum(C_) \
	Declare_LmiBinaryTreeNodeGetMinimumConst(C_) \
	Declare_LmiBinaryTreeNodeGetMaximum(C_) \
	Declare_LmiBinaryTreeNodeGetMaximumConst(C_) \
	Declare_LmiBinaryTreeNodeFind(C_, K_) \
	Declare_LmiBinaryTreeNodeFindConst(C_, K_) \
	Declare_LmiBinaryTreeNodeCount(C_, K_) \
	Declare_LmiBinaryTreeNodeLowerBound(C_, K_) \
	Declare_LmiBinaryTreeNodeLowerBoundConst(C_, K_) \
	Declare_LmiBinaryTreeNodeUpperBound(C_, K_) \
	Declare_LmiBinaryTreeNodeUpperBoundConst(C_, K_) \
	Declare_LmiBinaryTreeNodeEqualRange(C_, K_) \
	Declare_LmiBinaryTreeNodeEqualRangeConst(C_, K_) \
	Declare_LmiBinaryTreeNodeCopy(C_) \
	/* ... */

#define Declare_LmiUniqueBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiUniqueBinaryTreeNodeInsert(C_) \
	/* ... */

#define Declare_LmiMultipleBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiMultipleBinaryTreeNodeInsert(C_) \
	/* ... */

#define Define_LmiBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeNodeDelete(C_, V_) \
	Define_LmiBinaryTreeNodeRotateLeft(C_) \
	Define_LmiBinaryTreeNodeRotateRight(C_) \
	Define_LmiBinaryTreeNodeBalance(C_) \
	Define_LmiBinaryTreeNodeGetMinimum(C_) \
	Define_LmiBinaryTreeNodeGetMinimumConst(C_) \
	Define_LmiBinaryTreeNodeGetMaximum(C_) \
	Define_LmiBinaryTreeNodeGetMaximumConst(C_) \
	Define_LmiBinaryTreeNodeFind(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeFindConst(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeCount(C_, K_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeNodeLowerBound(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeLowerBoundConst(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeUpperBound(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeUpperBoundConst(C_, K_, GetKey, L_) \
	Define_LmiBinaryTreeNodeEqualRange(C_, K_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeNodeEqualRangeConst(C_, K_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeNodeCopy(C_, V_) \
	/* ... */

#define Define_LmiUniqueBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_) \
	Define_LmiUniqueBinaryTreeNodeInsert(C_, K_, GetKey, L_) \
	/* ... */

#define Define_LmiMultipleBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_) \
	Define_LmiMultipleBinaryTreeNodeInsert(C_, K_, GetKey, L_) \
	/* ... */

#define DefineInline_LmiBinaryTreeIteratorFuncs(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorIncrement(C_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorDecrement(C_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorContentOf(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorContentOfConst(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorIsExceptional(C_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorConstructExceptional(C_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorIncrement(C_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorDecrement(C_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorContentOf(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorContentOfConst(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorIsExceptional(C_, INLINE_) \
	DefineInline_LmiBinaryTreeConstIteratorConstructExceptional(C_, INLINE_) \
	/* ... */

/* Only those functions not implied by UniqueSortedAssociativeContainer */
#define Declare_LmiBinaryTreeFuncs(C_, K_, V_) \
	Declare_LmiBinaryTreeConstruct(C_) \
	Declare_LmiBinaryTreeGetAllocator(C_) \
	Declare_LmiBinaryTreeGetNodeSize(C_) \
	Declare_LmiBinaryTreeFront(C_, V_) \
	Declare_LmiBinaryTreeBack(C_, V_) \
	/* ... */

#define DefineInline_LmiBinaryTreeFuncs(C_, V_, INLINE_) \
	DefineInline_LmiBinaryTreeGetNodeSize(C_, INLINE_) \
	DefineInline_LmiBinaryTreeIteratorFuncs(C_, V_, INLINE_) \
	DefineInline_LmiReverseBidirectionalIterator(LmiReverseIterator(C_), LmiIterator(C_), V_, const V_, INLINE_) \
	DefineInline_LmiReverseBidirectionalIterator(LmiConstReverseIterator(C_), LmiConstIterator(C_), const V_, const V_, INLINE_)

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS

#define DefineInlineHeader_LmiBinaryTreeFuncs(C_, V_) \
	DefineInline_LmiBinaryTreeFuncs(C_, V_, LMI_INLINE)

#else

#define DefineInlineHeader_LmiBinaryTreeFuncs(C_, V_) /* (defined as empty) */

#endif

#if LMI_INLINE_NEED_SOURCE_FILE_DEFINITIONS

#define DefineInlineSource_LmiBinaryTreeFuncs(C_, V_) \
	DefineInline_LmiBinaryTreeFuncs(C_, V_, LMI_INLINE_SOURCE_FILE)

#else

#define DefineInlineSource_LmiBinaryTreeFuncs(C_, V_) /* (defined as empty) */

#endif

#define Define_LmiBinaryTree(C_, K_, V_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_, AllowMultiples) \
	Define_LmiBinaryTreeConstruct(C_) \
	Define_LmiBinaryTreeDestruct(C_) \
	Define_LmiBinaryTreeClear(C_) \
	Define_LmiBinaryTreeBegin(C_) \
	Define_LmiBinaryTreeEnd(C_) \
	Define_LmiBinaryTreeBeginConst(C_) \
	Define_LmiBinaryTreeEndConst(C_) \
	Define_LmiBinaryTreeFind(C_, K_) \
	Define_LmiBinaryTreeFindConst(C_, K_) \
	Define_LmiBinaryTreeCount(C_, K_) \
	Define_LmiBinaryTreeLowerBound(C_, K_) \
	Define_LmiBinaryTreeLowerBoundConst(C_, K_) \
	Define_LmiBinaryTreeUpperBound(C_, K_) \
	Define_LmiBinaryTreeUpperBoundConst(C_, K_) \
	Define_LmiBinaryTreeEqualRange(C_, K_) \
	Define_LmiBinaryTreeEqualRangeConst(C_, K_) \
	Define_LmiBinaryTreeErase(C_, V_) \
	Define_LmiBinaryTreeEraseRange(C_) \
	Define_LmiBinaryTreeEraseKey(C_, K_) \
	Define_LmiBinaryTreeSize(C_) \
	Define_LmiBinaryTreeMaxSize(C_) \
	Define_LmiBinaryTreeEmpty(C_) \
	Define_LmiBinaryTreeGetAllocator(C_) \
	Define_LmiBinaryTreeFront(C_, V_) \
	Define_LmiBinaryTreeBack(C_, V_) \
	Define_LmiBasicType(LmiIterator(C_)) \
	Define_LmiBasicType(LmiConstIterator(C_)) \
	Define_LmiBinaryTreeConstructCopy(C_) \
	Define_LmiBinaryTreeAssign(C_) \
	Define_LmiBinaryTreeSwap(C_) \
	DefineInlineSource_LmiBinaryTreeFuncs(C_, V_)
	/* ... */

#define Define_LmiUniqueBinaryTree(C_, K_, V_, GetKey, L_) \
	Define_LmiBinaryTree(C_, K_, V_, GetKey, L_, LMI_FALSE) \
	Define_LmiUniqueBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_) \
	Define_LmiUniqueBinaryTreeInsert(C_, V_) \
	/* ... */

#define Define_LmiMultipleBinaryTree(C_, K_, V_, GetKey, L_) \
	Define_LmiBinaryTree(C_, K_, V_, GetKey, L_, LMI_TRUE) \
	Define_LmiMultipleBinaryTreeNodeFuncs(C_, K_, V_, GetKey, L_) \
	Define_LmiMultipleBinaryTreeInsert(C_, V_) \
	/* ... */

#define Declare_LmiUniqueBinaryTree(C_, K_, V_, GetKey, L_) \
	Declare_LmiBinaryTreeTypes(C_, V_) \
	Declare_LmiUniqueSortedAssociativeContainer(C_, V_, LmiBinaryTreeNode(C_)*, const LmiBinaryTreeNode(C_)*, LmiSizeT, LmiDistanceT, K_) \
	Declare_LmiBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiUniqueBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiBinaryTreeFuncs(C_, K_, V_) \
	Declare_LmiBasicType(LmiIterator(C_)) \
	Declare_LmiBasicType(LmiConstIterator(C_)) \
	DefineInlineHeader_LmiBinaryTreeFuncs(C_, V_)

#define Declare_LmiMultipleBinaryTree(C_, K_, V_, GetKey, L_) \
	Declare_LmiBinaryTreeTypes(C_, V_) \
	Declare_LmiMultipleSortedAssociativeContainer(C_, V_, LmiBinaryTreeNode(C_)*, const LmiBinaryTreeNode(C_)*, LmiSizeT, LmiDistanceT, K_) \
	Declare_LmiBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiMultipleBinaryTreeNodeFuncs(C_, K_, V_) \
	Declare_LmiBinaryTreeFuncs(C_, K_, V_) \
	Declare_LmiBasicType(LmiIterator(C_)) \
	Declare_LmiBasicType(LmiConstIterator(C_)) \
	DefineInlineHeader_LmiBinaryTreeFuncs(C_, V_)

LMI_END_EXTERN_C

#endif /* LMI_BINARY_TREE_H_ */
