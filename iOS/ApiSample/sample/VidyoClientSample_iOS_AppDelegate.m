/*
 *  VidyoClientSample_iOS_AppDelegate.m
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import "VidyoClientSample_iOS_AppDelegate.h"

#include "VidyoClientSample.h"

// Constants

@implementation VidyoClientSample_iOS_AppDelegate

@synthesize window, viewController;

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	didEverGoToBackground = NO;
	// make main window first responder, and visible on screen
	[self.window setRootViewController: viewController];
	[self.window makeKeyAndVisible];
	initiated = NO;
	// initialize client
	[self clientInit];
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    if (floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(statusBarDidChangeFrame:)
                                                     name:@"UIApplicationDidChangeStatusBarFrameNotification"
                                                   object:nil];
    }
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(orientationDidChange:)
												 name:@"UIDeviceOrientationDidChangeNotification"
											   object:nil];
	[viewController.vidyoPortal becomeFirstResponder];
    
    //[[UIDevice currentDevice] setValue:[NSNumber numberWithInteger:UIInterfaceOrientationMaskPortrait] forKey:@"orientation"];
    
	return YES;
}

-(BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    
    if (!url) {
        return NO;
    }
    NSString *URLvalue =[url host];
    
    NSString *URLString = [url query];
    
    NSArray *pairs = [URLString componentsSeparatedByString:@"&"];
    NSMutableDictionary *kvpairs = [NSMutableDictionary dictionary];
    for(NSString *pair in pairs)
    {
        NSArray *bits =[pair componentsSeparatedByString:@"="];
        NSString *key = [[bits objectAtIndex:0] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        NSString *value = [[bits objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        [kvpairs setObject:value forKey:key];
    }
    NSLog(@ "key = %@",[kvpairs objectForKey:@"key"]);
    NSLog(@ "guestname = %@",[kvpairs objectForKey:@"guestname"]);
    NSLog(@"pin =%@",[kvpairs objectForKey:@"pin"]);
    NSLog(@"host =%@", URLvalue);
    
    LoginWindow *guestAccess = (LoginWindow *)self.window.rootViewController;
    guestAccess.guestPortal.text = URLvalue;
    guestAccess.guestnameField.text =[kvpairs objectForKey:@"guestname"];
    guestAccess.roomKeyField.text = [kvpairs objectForKey:@"key"];
    guestAccess.roomPinField.text =[kvpairs objectForKey:@"pin"];
    
    return YES;
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

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillTerminate:(UIApplication *)application
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

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk)
	 later.
     */
}

- (void)dealloc
{
    [window release];
	[viewController release];
    [super dealloc];
}

#pragma mark -
#pragma mark Client initialization

// Perform client initialization, including startup of VidyoClient library
- (void)clientInit
{
	VidyoBool ret;
	// check if this method already previously entered
	if (_vidyoClientStarted)
		return;

	// configure console logging
	VidyoClientConsoleLogConfigure(VIDYO_CLIENT_CONSOLE_LOG_CONFIGURATION_ALL);
	
	// determine video rectangle, from geometry of main window, assuming portrait right-side up orientation
	VidyoRect videoRect
	= {(VidyoInt)(window.frame.origin.x), (VidyoInt)(window.frame.origin.y),
		(VidyoUint)(window.frame.size.width), (VidyoUint)(window.frame.size.height)};




	// determine path, default base filename, and levels and categories, used for logging
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSLog(@"paths = %@", paths);
	NSString *documentsDirectory = [paths objectAtIndex:0];
    NSLog(@"documentsDirectory = %@", documentsDirectory);
	documentsDirectory = [documentsDirectory stringByAppendingString:@"/"];
    NSLog(@"documentsDirectory = %@", documentsDirectory);
	const char *pathToLogDir = [documentsDirectory cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"pathToLogDir = %s", pathToLogDir);
    
    /*NSString *cacheDirectory = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSLog(@"cacheDirectory = %@", cacheDirectory);
    NSString *logDirectory = [NSString stringWithFormat:@"%@/Logs/VideoConference", cacheDirectory];
    NSLog(@"logDirectory = %@", logDirectory);
    const char *pathToLogDir = [logDirectory cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"pathToLogDir = %s", pathToLogDir);*/
	
	VidyoClientLogParams logParams = {0};
	
	logParams.logBaseFileName = "VidyoSample_";
	logParams.pathToLogDir = pathToLogDir;
    logParams.logSize = 1024 * 1024 * 10;
	logParams.logLevelsAndCategories = "fatal error warning info@App info@AppGui info@AppEmcpClient info@LmiApp info@LmiH264SvcPace info@AppWebProxy";
	
	
	if (VidyoClientInitialize(vidyoClientSampleOnVidyoClientEvent, self, &logParams) == VIDYO_FALSE)
	{
		NSLog(@"VidyoClientInit() returned failure!\n");
		goto FAIL;
	}
	
	VidyoClientProfileParams profileParams = {0};
	
	// startup VidyoClient library
	ret = VidyoClientStart(vidyoClientSampleOnVidyoClientEvent,
						   self,
						   &logParams,
						   (VidyoWindowId) window,
						   &videoRect,
						   NULL,
						   &profileParams,
						   VIDYO_FALSE);
	
	if (!ret)
	{
		NSLog(@"VidyoClientStart() returned failure!\n");
		goto FAIL;
	}
	else 
	{
		NSLog(@"VidyoClientStart() returned success!\n");
	}
	[self bootstrap];
	return;

	// cleanup on failure, exiting program
FAIL: /*[[UIApplication sharedApplication] terminate:self]*/;
}

// Notification handler for device orientation changes
- (void)orientationDidChange:(NSNotification *)notification
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
            inCall = YES;
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
    = {(VidyoInt)(window.frame.origin.x), (VidyoInt)(window.frame.origin.y),
        (VidyoUint)(window.frame.size.width), (VidyoUint)(window.frame.size.height)};
    //    VidyoWindowId vidyoWin = (__bridge VidyoWindowId)(/*NULL*/window);
    //    (void)GuiSendPrivateRequest(VIDYO_CLIENT_PRIVATE_REQUEST_SET_GUI_WINDOW,
    //                                &vidyoWin, sizeof(vidyoWin), 0);
    
    //    //Generate offset for the origin point
    //    videoRect.xPos = 50;
    //    videoRect.yPos = 100;
    (void)VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT, &videoRect, sizeof(videoRect));
    
    VidyoClientInEventResize event;
    event.height = videoRect.height;
    event.width = videoRect.width;
    event.x = videoRect.xPos;
    event.y = videoRect.yPos;
    (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESIZE, &event, sizeof(event));
    
}

/* Startup configuration code. */
-(void) bootstrap
{
	VidyoClientRequestConfiguration conf = {0};
	VidyoUint error;
	if ((error = VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_GET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration))) != VIDYO_CLIENT_ERROR_OK) {
		NSLog(@"Failed to request configuration with error %u", error);
	} else {
		[[UIApplication sharedApplication] setStatusBarOrientation:[[UIDevice currentDevice] orientation]];
		/* Default configuration */
		conf.enableShowConfParticipantName = VIDYO_TRUE;
		conf.enableHideCameraOnJoin = VIDYO_FALSE;
		conf.enableBackgrounding = VIDYO_TRUE;
		/* Disable autologin */
		conf.userID[0] = '\0';
		conf.portalAddress[0] = '\0';
		conf.serverAddress[0] = '\0';
		conf.password[0] = '\0';
		conf.selfViewLoopbackPolicy = 2;
		if (VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_CONFIGURATION, &conf, sizeof(VidyoClientRequestConfiguration)) != VIDYO_CLIENT_ERROR_OK) {
			NSLog(@"Failed to set configuration");
		}
	}
}

// Getter for attribute, indicating if VidyoClientStart() has been called
- (BOOL)vidyoClientStarted
{
	return _vidyoClientStarted;
}

@end
