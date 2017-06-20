/**
{file:
	{name: VidyoChatMessageInline.h}
	{description: }
	{copyright:
		(c) 2014-2015 Vidyo, Inc.,
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

LMI_INLINE LmiBool VidyoChatMessageEqual(const VidyoChatMessage* a, const VidyoChatMessage* b)
{
	return LMI_FALSE;
}

LMI_INLINE LmiBool VidyoChatMessageLess(const VidyoChatMessage* a, const VidyoChatMessage* b)
{
	return LMI_FALSE;
}

LMI_INLINE const LmiString *VidyoChatMessageGetUserId(const VidyoChatMessage *c)
{
	return &c->userId;
}

LMI_INLINE const char *VidyoChatMessageGetUserIdCStr(const VidyoChatMessage *c)
{
	return LmiStringCStr(&c->userId);
}

LMI_INLINE VidyoChatMessageSenderType VidyoChatMessageGetSenderType(const VidyoChatMessage *c)
{
	return c->senderType;
}

LMI_INLINE LmiInt64 VidyoChatMessageGetId(const VidyoChatMessage *c)
{
	return c->id;
}

LMI_INLINE const LmiString *VidyoChatMessageGetBody(const VidyoChatMessage *c)
{
	return &c->body;
}

LMI_INLINE const char *VidyoChatMessageGetBodyCStr(const VidyoChatMessage *c)
{
	return LmiStringCStr(&c->body);
}

LMI_INLINE VidyoChatMessageType VidyoChatMessageGetType(const VidyoChatMessage *c)
{
	return c->type;
}

LMI_INLINE LmiTime VidyoChatMessageGetTimestamp(const VidyoChatMessage *c)
{
	return c->timestamp;
}
