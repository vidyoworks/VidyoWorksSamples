/**
{file:
	{name: VidyoRoomInfoInline.h}
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

LMI_INLINE const LmiString *VidyoRoomInfoGetId(const VidyoRoomInfo *info)
{
	return &info->id;
}

LMI_INLINE const LmiString *VidyoRoomInfoGetName(const VidyoRoomInfo *info)
{
	return &info->name;
}

LMI_INLINE const LmiString *VidyoRoomInfoGetDescription(const VidyoRoomInfo *info)
{
	return &info->description;
}

LMI_INLINE const LmiString *VidyoRoomInfoGetLanguage(const VidyoRoomInfo *info)
{
	return &info->language;
}

LMI_INLINE VidyoRoomType VidyoRoomInfoGetType(const VidyoRoomInfo *info)
{
	return info->type;
}

LMI_INLINE LmiBool VidyoRoomInfoIsPublic(const VidyoRoomInfo *info)
{
	return info->IsPublic;
}

LMI_INLINE LmiInt VidyoRoomInfoGetNumUsers(const VidyoRoomInfo *info)
{
	return info->numUsers;
}

LMI_INLINE const LmiVector(LmiString)* VidyoRoomInfoGetUserList(const VidyoRoomInfo *info)
{
	return &info->userList;
}

LMI_INLINE const LmiVector(VidyoChatMessage)* VidyoRoomInfoGetMessages(const VidyoRoomInfo *info)
{
	return &info->messageList;
}

LMI_INLINE LmiTime VidyoRoomInfoGetCreationTime(const VidyoRoomInfo *info)
{
	return info->creationTime;
}

