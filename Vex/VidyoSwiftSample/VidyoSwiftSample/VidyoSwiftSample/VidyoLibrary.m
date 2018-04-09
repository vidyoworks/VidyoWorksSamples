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




@implementation VidyoLibrary
BOOL initiated;
unsigned lastKnownOrientation;
UIView* VidyoView;
BOOL _vidyoClientStarted;
BOOL didEverGoToBackground;




-(void) InitializeVidyo: (UIView*)vidyoRender{
    
}

-(void) ConnectToRoom:(NSString *)portalUrl :(NSString *)key :(NSString *)name
{
   
}



-(void)LeaveRoom
{
    
}


-(void)orientationDidChange:(NSNotification *)notification
{
   
    
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
        
       
    }
}

@end
