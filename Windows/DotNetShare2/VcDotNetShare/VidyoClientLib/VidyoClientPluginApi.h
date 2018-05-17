/**
{file:
{name: VidyoClientPluginApi.h}
{description: header to get all definitions
for plug in api
}
{copyright:
(c) 2006 - 2010 Vidyo, Inc.,
433 Hackensack Avenue, 6th Floor,
Hackensack, NJ  07601.
All rights reserved.
The information contained herein is proprietary to Vidyo, Inc.
and shall not be reproduced, copied (in whole or in part), adapted,
modified, disseminated, transmitted, transcribed, stored in a retrieval
system, or translated into any language in any form by any means
without the express written consent of Vidyo, Inc.}
}

*/
#pragma once
#include "VidyoClient.h"

/*An instance of this class is sent to each Vidyo Client plugin in its creator function
	Using this class pointer, a plugin can communicate with teh plaugin manager and 
	therefore the VidyoCLientLib
*/

class VidyoPluginContext
{
public:
	enum ProductType{
		ProductTypeDefault = 0,
		ProductTypeRoom,
		ProductTypeDesktop		
	};

	enum EntryType{
		EntryTypeInt = 0,
		EntryTypeString	
	};

	virtual unsigned int sendRequest(VidyoClientRequest request, VidyoVoidPtr param, VidyoSizeT paramSize) = 0;

	virtual char sendEvent(VidyoClientInEvent eventType,VidyoVoidPtr param, VidyoSizeT paramSize) = 0;

	virtual const char * getVersion() = 0;

	virtual void log(VidyoLogLevel level, const char *file,
					int line, const char *function,
					const char *message) = 0;

	virtual void readConfig(const char * entryName, EntryType entryType,
					VidyoVoidPtr param, VidyoSizeT paramSize) = 0;

	virtual bool writeConfig(const char * entryName, EntryType entryType,
					VidyoVoidPtr param, VidyoSizeT paramSize) = 0;

	virtual ProductType getProductType() = 0;

	virtual ~ VidyoPluginContext(void){}		
};
typedef  VidyoPluginContext* VidyoPluginContextPtr;


/* The class VidyoClientPlugin needs to be implemented by any dll that wants to 
become a VidyoCLient lib
*/

class VidyoClientPlugin
{
public:
	virtual ~VidyoClientPlugin(void) {};

	//return false for any error in posting event
	virtual bool postEvent(VidyoClientOutEvent eventType, VidyoVoidPtr param, VidyoUint paramSize, VidyoVoidPtr data)  = 0;

	virtual void stop() = 0 ;

	virtual  const char * getVersion() = 0 ;
};
typedef  VidyoClientPlugin* VidyoClientPluginPtr;