// VidyoIoWrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "VidyoClientSwitch.h"
#include "ClientVidyoWorks.h"


VidyoClientPtr gClientPtr = NULL;

DECLSPEC VidyoClientPtr VcwGetClient(VidyoClientSwitchDefs::ClientType clientType)
{
	if (gClientPtr)
	{
		delete gClientPtr;
		gClientPtr = NULL;
	}
		
	if (clientType == VidyoClientSwitchDefs::ClientTypeVw)
	{
		gClientPtr = new ClientVidyoWorks();
		return gClientPtr;
	}
	return NULL;	
}
