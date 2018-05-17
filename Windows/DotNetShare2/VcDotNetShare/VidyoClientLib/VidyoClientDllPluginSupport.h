/*! @file VidyoClientDllPluginSupport.h
    @brief Vidyo Client Support for plugin when used as a DLL
    @copyright
    (c) 2006-2009 Vidyo, Inc.
    433 Hackensack Avenue, 6th Floor,
    Hackensack, NJ  07601.
    All rights reserved.
    The information contained herein is proprietary to Vidyo, Inc.
    and shall not be reproduced, copied (in whole or in part), adapted,
    modified, disseminated, transmitted, transcribed, stored in a retrieval
    system, or translated into any language in any form by any means
    without the express written consent of Vidyo, Inc.   
*/

#ifndef VIDYO_CLIENT_DLL_PLUGIN_SUPPORT_H
#define VIDYO_CLIENT_DLL_PLUGIN_SUPPORT_H


#if defined(BUILD_VIDYO_CLIENT_DLL) || defined(VIDYO_CLIENT_DLL_STATIC_LIB)
#ifdef BUILD_VIDYO_PLUGIN_API

#include "VidyoTypes.h"

#if defined(__cplusplus)
extern "C" {
#endif
/*! 
  @brief Start the plugin manager

  Returns success if plugin started properly

  @param[in] clientType            type of client - ClientTypeRoom / ClientTypeDesktop.
*/
DECLSPEC bool VidyoClientPluginManagerStart(unsigned clientType);


/*! 
  @brief Stop the plugin manager

  Returns success / failure
*/
DECLSPEC bool VidyoClientPluginManagerStop();


/*! 
  @brief Load all plugins

  Returns void

  @param[in] installPath            install location.
  @param[in] message                format of the message to be displayed to the user, if NULL no message is displayed
*/
DECLSPEC void VidyoClientLoadPlugins(const char *installPath, const wchar_t *message);


/*! 
  @brief Unload all pluginsr

  Returns void

  @param none
*/
DECLSPEC void VidyoClientUnloadPlugins();

/*! 
  @brief Inform of a message to the plugin

  Returns void

  @param[in] eventType              Enumeration of event to be forwarded
  @param[in] param                  Pointer to parameter structure, if any
  @param[in] paramSize              Size, in bytes, of parameter structure
  @param[in] data                   Pointer to data, registered with #VidyoClientStart
*/
DECLSPEC void VidyoClientSendEventToPlugins(VidyoClientOutEvent eventType,
												   VidyoVoidPtr param,
												   VidyoUint paramSize,
												   VidyoVoidPtr data);
#if defined(__cplusplus)
}
#endif

#endif
#endif
#endif
