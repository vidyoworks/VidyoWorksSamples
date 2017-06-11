/*
 *  VidyoClientSample.c
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import <assert.h>
#import <ctype.h>
#import <stdarg.h>
#import <stdio.h>
#import <string.h>
#import <unistd.h>
#import <wchar.h>
#import "VidyoClientSample_iOS_AppDelegate.h"
#import "LoginWindow.h"
#import "VidyoClientSample.h"

// Callback for out-events from VidyoClient
void vidyoClientSampleOnVidyoClientEvent(VidyoClientOutEvent event,
										 VidyoVoidPtr param, VidyoUint paramSize,
										 VidyoVoidPtr data)
{
	VidyoClientOutEventLicense *eventLicense;
	VidyoClientOutEventSignIn *eventSignIn;
	VidyoClientSample_iOS_AppDelegate *appDelegate = (VidyoClientSample_iOS_AppDelegate*)data;
    
	NSLog(@"Received event=%d", event);
	
	if (event >= VIDYO_CLIENT_OUT_EVENT_MIN
		&& event <= VIDYO_CLIENT_OUT_EVENT_MAX)
	{
        switch (event) {
            case VIDYO_CLIENT_OUT_EVENT_LICENSE:
            {
                /*
                * If there are any issues with Licenses, this event will be sent
                * by the VidyoClient library
                */
                eventLicense = (VidyoClientOutEventLicense *) param; 
                
                VidyoUint error = eventLicense->error;
                VidyoUint vmConnectionPath = eventLicense->vmConnectionPath;
                VidyoBool OutOfLicenses = eventLicense->OutOfLicenses;
                
                NSLog(@"License Error: errorid=%d vmConnectionPath=%d OutOfLicense=%d", error, vmConnectionPath, OutOfLicenses);
                
                break;
            }   
            case VIDYO_CLIENT_OUT_EVENT_SIGN_IN:
            {
                eventSignIn = (VidyoClientOutEventSignIn *) param; 
                
                VidyoUint activeEid = eventSignIn->activeEid;
                VidyoBool signinSecured = eventSignIn->signinSecured;
                
                NSLog(@"activeEid=%d signinSecured=%@", activeEid, signinSecured?@"Yes":@"No");
                /* 
                 * If the EID is not setup, it will resturn activeEid = 0
                 * in this case, we invoke the license request using below event
                 */
                if(!activeEid)
                    (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LICENSE, NULL, 0);
                
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_SIGNED_IN:
            {
				dispatch_async(dispatch_get_main_queue(), ^{
					/* Dismissing signin alert */
					if ([[appDelegate viewController] isSigningIn])
					{
						[[[appDelegate viewController] signingInAlert] dismissWithClickedButtonIndex:0 animated:YES];
						[[appDelegate viewController] setIsSigningIn:FALSE];
					}
					
					NSString *alertMsg = [NSString stringWithFormat:@"Successfully signed in"];															  
					UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
					[alert show];
					[alert release];
				});
                
                break;
                
                
                
            }
                
                //code added newly
                
            case VIDYO_CLIENT_OUT_EVENT_ROOM_LINK:
            {
                break;
            }

            case VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT:
            {
                /* Dismissing signin alert */
				dispatch_async(dispatch_get_main_queue(), ^{
					if ([[appDelegate viewController] isSigningIn])
					{
						[[[appDelegate viewController] signingInAlert] dismissWithClickedButtonIndex:0 animated:YES];
						[[appDelegate viewController] setIsSigningIn:FALSE];
					}
					
                    NSLog(@"Got VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT event - setting isInCall = false");
                    [[appDelegate viewController] setIsInCall:FALSE];
                    
					NSString *alertMsg = [NSString stringWithFormat:@"You are signed out"];															  
					UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
					[alert show];
					[alert release];
				});
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_INCOMING_CALL: 
            {
                /* Auto-accept all incoming calls */
                VidyoClientOutEventIncomingCall *incomingCall = (VidyoClientOutEventIncomingCall*)param;
                NSLog(@"Incoming call from %@ %s . Accepting.", incomingCall->onCallFlag?@"user":@"room", incomingCall->invitingUser);
                VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ANSWER, NULL, 0);
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE:
            {
                /* Add logic for joining to a conference logic */
                NSLog(@"Got VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ACTIVE event - setting isInCall = true");
                [[appDelegate viewController] setIsInCall:TRUE];
                
                VidyoClientRequestConfiguration conf = {0};
                VidyoUint error;
                if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK)
                {
                    NSLog(@"Failed to request configuration with error %u", error);
                } else{
                    //conf.enableShowConfParticipantName = VIDYO_FALSE;
                    conf.currentCamera = 1;
                    if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration)) != VIDYO_CLIENT_ERROR_OK)
                    {
                        NSLog(@"Failed to set configuration");
                    }
                    else
                    {
                        NSLog(@"Set configuration successfully for VIDYO_CLIENT_REQUEST_SET_CONFIGURATION");
                        if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK)
                        {
                            NSLog(@"Failed to request configuration with error %u", error);
                        } else {
                            NSLog(@"Got configuration again after VIDYO_CLIENT_OUT_EVENT_CONFERENCE ACTIVE");
                            //NSLog(@"conf.enableShowConfParticipantName = %d", conf.enableShowConfParticipantName);
                            //NSLog(@"conf.proxySettings = %d", conf.proxySettings);
                            NSLog(@"conf.currentCamera = %d", conf.currentCamera);
                        }
                    }
                }
                
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED:
            {
                VidyoClientRequestConfiguration conf = {0};
                VidyoUint error;
                if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK)
                {
                    NSLog(@"Failed to request configuration with error %u", error);
                } else{
                    //conf.enableShowConfParticipantName = VIDYO_FALSE;
                    //conf.proxySettings = PROXY_WEB_IE_AUTO_DETECT | PROXY_WEB_ENABLE | PROXY_VIDYO_FORCE_TO_VM;
                    conf.currentCamera = 1;
                    if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration)) != VIDYO_CLIENT_ERROR_OK)
                    {
                        NSLog(@"Failed to set configuration");
                    }
                    else
                    {
                        NSLog(@"Set configuration successfully for VIDYO_CLIENT_REQUEST_SET_CONFIGURATION");
                        if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK)
                        {
                            NSLog(@"Failed to request configuration with error %u", error);
                        } else {
                            NSLog(@"Got configuration again after VIDYO_CLIENT_OUT_EVENT_LOGIC_STARTED");
                            //NSLog(@"conf.enableShowConfParticipantName = %d", conf.enableShowConfParticipantName);
                            //NSLog(@"conf.proxySettings = %d", conf.proxySettings);
                            NSLog(@"conf.currentCamera = %d", conf.currentCamera);
                        }
                    }
                }
                
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_ADD_SHARE:
            {
                VidyoClientOutEventAddShare *share = (VidyoClientOutEventAddShare*)param;
                VidyoClientRequestWindowShares shares = {0};
                VidyoUint error;
                
                shares.requestType = LIST_SHARING_WINDOWS;
                error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_WINDOW_SHARES, (void*)&shares, sizeof(VidyoClientRequestWindowShares));
                if (error != VIDYO_CLIENT_ERROR_OK)
                {
                    NSLog(@"Failed to send a request for window shares. Error response %u", error);
                    break;
                }
                /* See if we have a share in a list. If we do set current share to a new one. */
                for (int i = 1 /* index starts from 1 */ ; i <= shares.shareList.numApp; i++) {
                    if (strcmp(shares.shareList.remoteAppUri[i], share->URI) == 0)
                    {
                        shares.requestType = ADD_SHARING_WINDOW;
                        shares.shareList.currApp = shares.shareList.newApp = i;
                        error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_WINDOW_SHARES, (void*)&shares, sizeof(VidyoClientRequestWindowShares));
                        if (error != VIDYO_CLIENT_ERROR_OK)
                        {
                            NSLog(@"Failed to send a request to change window share. Error response %u", error);
                            break;
						}
					}
					break;
                
            	}
            }
			case VIDYO_CLIENT_OUT_EVENT_PARTICIPANTS_CHANGED:
			{

				break;
			}
            default:
                break;
        }

	}
	else
	{
        NSLog(@"Unknown event %d", event);
	}
}