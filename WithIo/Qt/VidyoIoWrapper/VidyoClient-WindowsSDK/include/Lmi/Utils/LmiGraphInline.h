/**
{file:
	{name: LmiGraphInline.h}
	{description: Graph class.}
	{copyright:
		(c) 2008-2011 Vidyo, Inc.,
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
LMI_INLINE LmiGraphNode *LmiGraphLinkGetNode1(LmiGraphLink *link)
{
	return link->node1;
}

LMI_INLINE LmiGraphNode *LmiGraphLinkGetNode2(LmiGraphLink *link)
{
	return link->node2;
}

LMI_INLINE LmiGraphNode *LmiGraphLinkGetOtherNode(LmiGraphLink *link, LmiGraphNode *node)
{
	return node == link->node1 ? link->node2 : link->node1;
}

LMI_INLINE void *LmiGraphLinkGetUserData(LmiGraphLink *link)
{
	return link->data;
}

LMI_INLINE void LmiGraphLinkSetUserData(LmiGraphLink *link, void *data)
{
	link->data = data;
}

LMI_INLINE void LmiGraphLinkIteratorIncrement(LmiGraphLinkIterator *iter)
{
	LmiUnorderedMultimapConstIteratorIncrement(LmiUint, LmiGraphLinkPtr)(iter);
}

LMI_INLINE LmiGraphLink *LmiGraphLinkIteratorContentOf(LmiGraphLinkIterator *iter)
{
	return LmiUnorderedMultimapConstIteratorContentOf(LmiUint, LmiGraphLinkPtr)(iter)->second;
}

LMI_INLINE LmiGraphLinkIterator LmiGraphNodeBegin(const LmiGraphNode *node)
{
	return LmiUnorderedMultimapBeginConst(LmiUint, LmiGraphLinkPtr)(&node->links);
}

LMI_INLINE LmiGraphLinkIterator LmiGraphNodeEnd(const LmiGraphNode *node)
{
	return LmiUnorderedMultimapEndConst(LmiUint, LmiGraphLinkPtr)(&node->links);
}

LMI_INLINE void LmiGraphNodeGetLinks(const LmiGraphNode *node1, const LmiGraphNode *node2, LmiGraphLinkIterator *beginRange, LmiGraphLinkIterator *endRange)
{
	LmiPair(LmiUnorderedMultimapConstIterator(LmiUint, LmiGraphLinkPtr),
		LmiUnorderedMultimapConstIterator(LmiUint, LmiGraphLinkPtr)) pair =
		LmiUnorderedMultimapEqualRangeConst(LmiUint, LmiGraphLinkPtr)(&node1->links, &node2->id);
	*beginRange = pair.first;
	*endRange = pair.second;
}

LMI_INLINE LmiSizeT LmiGraphNodeGetLinkCount(const LmiGraphNode *node1, const LmiGraphNode *node2)
{
	return LmiUnorderedMultimapCount(LmiUint, LmiGraphLinkPtr)(&node1->links, &node2->id);
}

LMI_INLINE void *LmiGraphNodeGetUserData(LmiGraphNode *node)
{
	return node->data;
}

LMI_INLINE void LmiGraphNodeSetUserData(LmiGraphNode *node, void *data)
{
	node->data = data;
}

LMI_INLINE void LmiGraphNodeIteratorIncrement(LmiGraphNodeIterator *iter)
{
	LmiUnorderedMapConstIteratorIncrement(LmiUint, LmiGraphNodePtr)(iter);
}

LMI_INLINE LmiGraphNode *LmiGraphNodeIteratorContentOf(LmiGraphNodeIterator *iter)
{
	return LmiUnorderedMapConstIteratorContentOf(LmiUint, LmiGraphNodePtr)(iter)->second;
}

LMI_INLINE LmiGraphNodeIterator LmiGraphBegin(const LmiGraph *graph)
{
	return LmiUnorderedMapBeginConst(LmiUint, LmiGraphNodePtr)(&graph->nodes);
}

LMI_INLINE LmiGraphNodeIterator LmiGraphEnd(const LmiGraph *graph)
{
	return LmiUnorderedMapEndConst(LmiUint, LmiGraphNodePtr)(&graph->nodes);
}

LMI_INLINE LmiSizeT LmiGraphGetNodeCount(const LmiGraph *graph)
{
	return LmiUnorderedMapSize(LmiUint, LmiGraphNodePtr)(&graph->nodes);
}
