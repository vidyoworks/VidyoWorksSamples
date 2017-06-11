/*
 *  VidyoClientSample_iOS_AppDelegate.h
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#import "LoginWindow.h"

@interface VidyoClientSample_iOS_AppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
@private
	BOOL _vidyoClientStarted;
	unsigned lastKnownOrientation;
	BOOL initiated;
	BOOL didEverGoToBackground;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet LoginWindow *viewController;

- (void)clientInit;
- (BOOL)vidyoClientStarted;

@end

