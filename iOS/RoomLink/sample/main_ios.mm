/*
 *  main_ios.mm
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, nil);
    [pool release];
    return retVal;
}
