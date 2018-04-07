//
//  VidyoLibrary.h
//  VidyoSwiftSample
//
//  Created by ApiSamples on 07/07/17.
//  Copyright © 2017 ApiSamples. All rights reserved.
//

#ifndef VidyoLibrary_h
#define VidyoLibrary_h


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface VidyoLibrary : NSObject

-(void) InitializeVidyo: (UIView*) vidyoRender;
-(void) ConnectToRoom: (NSString*) portalUrl: (NSString*) key: (NSString*)name;
-(void)orientationDidChange:(NSNotification *)notification;
-(void)statusBarDidChangeFrame:(NSNotification *)notification;
-(void)applicationWillTerminate:(UIApplication *)application;
-(void)applicationWillResignActive:(UIApplication *)application;
-(void)applicationDidBecomeActive:(UIApplication *)application;
-(BOOL)vidyoClientStarted;
-(void)LeaveRoom;


@end


#endif /* VidyoLibrary_h */
