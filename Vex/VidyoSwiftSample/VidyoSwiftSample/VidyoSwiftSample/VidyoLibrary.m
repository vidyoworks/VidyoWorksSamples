//
//  VidyoLibrary.m
//  VidyoSwiftSample
//
//  Created by ApiSamples on 07/07/17.
//  Copyright © 2017 ApiSamples. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "VidyoLibrary.h"
#import "VidyoClientLibrary/include/VidyoClient.h"
#import "VidyoClientLibrary/include/VidyoClientMessages.h"
#import "VidyoClientLibrary/include/VidyoClientConstants.h"



@implementation VidyoLibrary
BOOL initiated;
unsigned lastKnownOrientation;
UIView* VidyoView;
BOOL _vidyoClientStarted;
BOOL didEverGoToBackground;


void vidyoClientEvents(VidyoClientOutEvent event,
                                         VidyoVoidPtr param, VidyoUint paramSize,
                                         VidyoVoidPtr data)
{
    VidyoClientOutEventLicense *eventLicense;
    VidyoClientOutEventSignIn *eventSignIn;
    
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
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_ROOM_LINK:
            {
                
                //Tratamento de ERRO 1020(URL SALA INVALIDA) e 1017(SALA BLOQUEADA)
                /*VidyoClientOutEventRoomLink *roomLink = (VidyoClientOutEventRoomLink *) param;
                if(roomLink->error == 1020)
                {
                   
                }
                else if(roomLink->error == 1017)
                {
                    
                }
                */
                
                
                break;
            }
                
            case VIDYO_CLIENT_OUT_EVENT_SIGNED_OUT:
            {
                break;
                /* Dismissing signin alert */
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
                
                VidyoClientRequestConfiguration conf = {0};
                VidyoUint error;
                if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK)
                {
                    NSLog(@"Failed to request configuration with error %u", error);
                } else{
                    
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
                
                VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_DISABLE_SHARE_EVENTS, 0, 0);
                
                break;
            }
            case VIDYO_CLIENT_OUT_EVENT_CONFERENCE_ENDED:
            {
                
                //Finalizar conferencia;
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

-(void) InitializeVidyo: (UIView*)vidyoRender{
    VidyoClientLogParams logParams = {0};
    
    logParams.logBaseFileName = "VidyoSample_";
    logParams.pathToLogDir = "";
    logParams.logSize = 1024 * 1024 * 10;
    logParams.logLevelsAndCategories = "fatal error warning info@App info@AppGui info@AppEmcpClient info@LmiApp info@LmiH264SvcPace info@AppWebProxy";
    
    VidyoClientConsoleLog((int)VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_ALL);
    if (VidyoClientInitialize(vidyoClientEvents, NULL, &logParams) == VIDYO_FALSE)
    {
        NSLog(@"VidyoClientInit() returned failure!\n");
    }
    
    VidyoBool ret;
    
    VidyoClientProfileParams profileParams = {0};
    
    VidyoView = vidyoRender;
    
    // determine video rectangle, from geometry of main window, assuming portrait right-side up orientation
    VidyoRect videoRect
    = {(VidyoInt)(0), (VidyoInt)(0),
        (VidyoUint)(vidyoRender.frame.size.width), (VidyoUint)(vidyoRender.frame.size.height)};
    
    // startup VidyoClient library
    ret = VidyoClientStart(vidyoClientEvents,
                           (__bridge VidyoVoidPtr)(self),
                           &logParams,
                           (__bridge VidyoWindowId) vidyoRender,
                           &videoRect,
                           NULL,
                           &profileParams,
                           VIDYO_FALSE);
    didEverGoToBackground = YES;
    if(ret)
    {
        _vidyoClientStarted = YES;
        
    }
    else
    {
        _vidyoClientStarted = NO;
    }
}

-(void) ConnectToRoom:(NSString *)portalUrl :(NSString *)key :(NSString *)name
{
    VidyoClientInEventRoomLink event = {0};
    
    NSString* pin = @"";
    
    strlcpy(event.portalUri, [portalUrl UTF8String], sizeof(event.portalUri));
    strlcpy(event.roomKey, [key UTF8String], sizeof(event.roomKey));
    strlcpy(event.displayName, [name UTF8String], sizeof(event.displayName));
    strlcpy(event.pin, [pin UTF8String], sizeof(event.pin));
    
    if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &event, sizeof(VidyoClientInEventRoomLink)) == false)
    {
    }

}



-(void)LeaveRoom
{
    if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LEAVE, NULL, 0) == false)
    {
    }
}


-(void)orientationDidChange:(NSNotification *)notification
{
    NSLog(@"Orientation changed %@", notification);
    
    // determine device orientation
    VidyoClientInEventSetOrientation event = {0};
    event.orientation = (VidyoClientOrientation)lastKnownOrientation;
    if (floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1) {
        event.control = VIDYO_CLIENT_ORIENTATION_CONTROL_CAPTURE;
    }
    else {
        event.control = VIDYO_CLIENT_ORIENTATION_CONTROL_BOTH;
    }
    BOOL willSetOrientation = NO;
    switch([[UIDevice currentDevice] orientation])
    {
        case UIDeviceOrientationUnknown:
            VIDYO_CLIENT_LOG_DEBUG("Unknown");
            VIDYO_CLIENT_CONSOLE_LOG("Unknown\n");
            break;
        case UIDeviceOrientationPortrait:
            VIDYO_CLIENT_LOG_DEBUG("Portrait");
            VIDYO_CLIENT_CONSOLE_LOG("Portrait\n");
            event.orientation = VIDYO_CLIENT_ORIENTATION_UP;
            willSetOrientation = YES;
            break;
        case UIDeviceOrientationPortraitUpsideDown:
            VIDYO_CLIENT_LOG_DEBUG("PortraitUpsideDown");
            VIDYO_CLIENT_CONSOLE_LOG("PortraitUpsideDown\n");
            event.orientation = VIDYO_CLIENT_ORIENTATION_DOWN;
            willSetOrientation = YES;
            break;
        case UIDeviceOrientationLandscapeLeft:
            VIDYO_CLIENT_LOG_DEBUG("LandscapeLeft");
            VIDYO_CLIENT_CONSOLE_LOG("LandscapeLeft\n");
            event.orientation = VIDYO_CLIENT_ORIENTATION_RIGHT;
            willSetOrientation = YES;
            break;
        case UIDeviceOrientationLandscapeRight:
            VIDYO_CLIENT_LOG_DEBUG("LandscapeRight");
            VIDYO_CLIENT_CONSOLE_LOG("LandscapeRight\n");
            event.orientation = VIDYO_CLIENT_ORIENTATION_LEFT;
            willSetOrientation = YES;
            break;
        case UIDeviceOrientationFaceUp:
            VIDYO_CLIENT_LOG_DEBUG("FaceUp");
            VIDYO_CLIENT_CONSOLE_LOG("FaceUp\n");
            break;
        case UIDeviceOrientationFaceDown:
            VIDYO_CLIENT_LOG_DEBUG("FaceDown");
            VIDYO_CLIENT_CONSOLE_LOG("FaceDown\n");
            break;
    }
    
    if (!initiated && willSetOrientation)
    {
        initiated=YES;
    }
    
    // cache orientation if needed
    if (willSetOrientation)
    {
        VidyoClientRequestCallState callState = {0};
        VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CALL_STATE, &callState, sizeof(callState));
        // new orientation becomes known, set as last known orientation
        lastKnownOrientation = (unsigned)(event.orientation);
        if (callState.callState == VIDYO_CLIENT_CALL_STATE_IN_CONFERENCE)
        {
                        [UIView animateWithDuration:1.0 delay:0.0 options:UIViewAnimationOptionCurveLinear
                             animations:^{
                                 [[UIApplication sharedApplication] setStatusBarOrientation:[[UIDevice currentDevice] orientation]];
                             }
                             completion:^(BOOL finished){
                             } ];
        }
    }
    
    // always send event to VidyoClient to set orientation, whether new or cached,
    // in case AppFramework objects were not created in time for first orientation change/poll
    (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SET_ORIENTATION,
                               &event, sizeof(VidyoClientInEventSetOrientation));
}

- (void)statusBarDidChangeFrame:(NSNotification *)notification {
    VidyoRect videoRect
    = {(VidyoInt)(0), (VidyoInt)(0),
        (VidyoUint)(VidyoView.frame.size.width), (VidyoUint)(VidyoView.frame.size.height)};
    (void)VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT, &videoRect, sizeof(videoRect));
    
    VidyoClientInEventResize event;
    event.height = videoRect.height;
    event.width = videoRect.width;
    event.x = videoRect.xPos;
    event.y = videoRect.yPos;
    (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESIZE, &event, sizeof(event));
    
}

-(void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     */
    NSLog(@"applicationWillTerminate called");
    
    // try to shutdown VidyoClient library
    if (!_vidyoClientStarted)
    {
        return;
    }
    
    if (VidyoClientStop() != VIDYO_TRUE)
    {
        // not expected condition
        NSLog(@"VidyoClientStop() returned error!");
        return;
    }
    
    VidyoClientUninitialize();
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];

}

-(BOOL)vidyoClientStarted
{
    return _vidyoClientStarted;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of
     temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and
     it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use
     this method to pause the game.
     */
    NSLog(@"going to background");
    VidyoUint error;
    VidyoClientRequestSetBackground request = {0};
    request.willBackground = VIDYO_TRUE;
    
    if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_BACKGROUND, &request, sizeof(request))) != VIDYO_CLIENT_ERROR_OK) {
        NSLog(@"problem going to background %d", error);
    }
    sleep(3);
    didEverGoToBackground = YES;

}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    if (didEverGoToBackground == YES) {
        /*
         Restart any tasks that were paused (or not yet started) while the application was inactive.
         */
        NSLog(@"going to foreground");
        
        VidyoUint error;
        VidyoClientRequestSetBackground request = {0};
        request.willBackground = VIDYO_FALSE;
        
        if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_BACKGROUND, &request, sizeof(request))) != VIDYO_CLIENT_ERROR_OK) {
            NSLog(@"problem going to foreground %d", error);
        }
    }
}

@end
