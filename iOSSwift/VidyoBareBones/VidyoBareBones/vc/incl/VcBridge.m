//
//  VcBridge.m
//  VidyoBareBones
//
//  Created by Dinesh Sinha on 3/15/17.
//  Copyright © 2017 Dinesh Sinha. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stddef.h>
#import "VidyoClientConstants.h"
#import "VidyoClientMessages.h"
#import "VidyoClient.h"

#import "../../VidyoBareBones-Bridging-Header.h"

@implementation VcTalker


void vidyoClientSampleOnVidyoClientEvent(VidyoClientOutEvent event,
                                         VidyoVoidPtr param, VidyoUint paramSize,
                                         VidyoVoidPtr data)
{
}

- (void) initializeVc {
    NSLog(@"SomeMethod Ran");
    
    VidyoClientLogParams logParams = {0};
    
    logParams.logBaseFileName = "VidyoSample_";
    logParams.pathToLogDir = "";
    logParams.logSize = 1024 * 1024 * 10;
    logParams.logLevelsAndCategories = "fatal error warning info@App info@AppGui info@AppEmcpClient info@LmiApp info@LmiH264SvcPace info@AppWebProxy";
    
    
    if (VidyoClientInitialize(vidyoClientSampleOnVidyoClientEvent, NULL, &logParams) == VIDYO_FALSE)
    {
        NSLog(@"VidyoClientInit() returned failure!\n");
    }

}

@end
