/**
{file:
	{name: LmiGraph.h}
	{description: Graph class.}
	{copyright:
		(c) 2008 Vidyo, Inc.,
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
#ifndef LMI_GRAPH_H
#define LMI_GRAPH_H

#include <Lmi/Utils/LmiTypes.h>
#include <Lmi/Utils/LmiUnordered.h>

LMI_BEGIN_EXTERN_C

struct LmiGraphNode_;

typedef struct
{
	struct LmiGraphNode_ *node1;
	struct LmiGraphNode_ *node2;
	void *data;
} LmiGraphLink;

LMI_INLINE_DECLARATION struct LmiGraphNode_ *LmiGraphLinkGetNode1(LmiGraphLink *link);
LMI_INLINE_DECLARATION struct LmiGraphNode_ *LmiGraphLinkGetNode2(LmiGraphLink *link);
LMI_INLINE_DECLARATION struct LmiGraphNode_ *LmiGraphLinkGetOtherNode(LmiGraphLink *link, struct LmiGraphNode_ *node);
LMI_INLINE_DECLARATION void *LmiGraphLinkGetUserData(LmiGraphLink *link);
LMI_INLINE_DECLARATION void LmiGraphLinkSetUserData(LmiGraphLink *link, void *data);

typedef LmiGraphLink *LmiGraphLinkPtr;
Declare_LmiBasicType(LmiGraphLinkPtr)
Declare_LmiUnorderedMultimap(LmiUint, LmiGraphLinkPtr)

typedef LmiUnorderedMultimapConstIterator(LmiUint, LmiGraphLinkPtr) LmiGraphLinkIterator;
LMI_INLINE_DECLARATION void LmiGraphLinkIteratorIncrement(LmiGraphLinkIterator *iter);
LMI_INLINE_DECLARATION LmiGraphLink *LmiGraphLinkIteratorContentOf(LmiGraphLinkIterator *iter);

typedef struct LmiGraphNode_
{
	LmiUint id;
	LmiUnorderedMultimap(LmiUint, LmiGraphLinkPtr) links;
	void *data;
} LmiGraphNode;

LMI_INLINE_DECLARATION LmiGraphLinkIterator LmiGraphNodeBegin(const LmiGraphNode *node);
LMI_INLINE_DECLARATION LmiGraphLinkIterator LmiGraphNodeEnd(const LmiGraphNode *node);
LMI_INLINE_DECLARATION void LmiGraphNodeGetLinks(const LmiGraphNode *node1, const LmiGraphNode *node2, LmiGraphLinkIterator *beginRange, LmiGraphLinkIterator *endRange);
LMI_INLINE_DECLARATION LmiSizeT LmiGraphNodeGetLinkCount(const LmiGraphNode *node1, const LmiGraphNode *node2);
LMI_INLINE_DECLARATION void *LmiGraphNodeGetUserData(LmiGraphNode *node);
LMI_INLINE_DECLARATION void LmiGraphNodeSetUserData(LmiGraphNode *node, void *data);

typedef LmiGraphNode *LmiGraphNodePtr;
Declare_LmiBasicType(LmiGraphNodePtr)
Declare_LmiUnorderedMap(LmiUint, LmiGraphNodePtr)

typedef LmiUnorderedMapConstIterator(LmiUint, LmiGraphNodePtr) LmiGraphNodeIterator;
LMI_INLINE_DECLARATION void LmiGraphNodeIteratorIncrement(LmiGraphNodeIterator *iter);
LMI_INLINE_DECLARATION LmiGraphNode *LmiGraphNodeIteratorContentOf(LmiGraphNodeIterator *iter);

typedef struct
{
	LmiUnorderedMap(LmiUint, LmiGraphNodePtr) nodes;
	LmiUint nextNodeId;
	LmiAllocator *alloc;
} LmiGraph;

LmiGraph *LmiGraphConstruct(LmiGraph *graph, LmiAllocator *alloc);
void LmiGraphDestruct(LmiGraph *graph);
LmiGraphNode *LmiGraphAddNode(LmiGraph *graph, void *data);
void LmiGraphRemoveNode(LmiGraph *graph, LmiGraphNode *node);
LMI_INLINE_DECLARATION LmiGraphNodeIterator LmiGraphBegin(const LmiGraph *graph);
LMI_INLINE_DECLARATION LmiGraphNodeIterator LmiGraphEnd(const LmiGraph *graph);
LMI_INLINE_DECLARATION LmiSizeT LmiGraphGetNodeCount(const LmiGraph *graph);
LmiGraphLink *LmiGraphAddLink(LmiGraph *graph, LmiGraphNode *node1, LmiGraphNode *node2, void *data);
void LmiGraphRemoveLink(LmiGraph *graph, LmiGraphLink *link);

LMI_END_EXTERN_C

#if LMI_INLINE_NEED_HEADER_FILE_DEFINITIONS
#include <Lmi/Utils/LmiGraphInline.h>
#endif

#endif
