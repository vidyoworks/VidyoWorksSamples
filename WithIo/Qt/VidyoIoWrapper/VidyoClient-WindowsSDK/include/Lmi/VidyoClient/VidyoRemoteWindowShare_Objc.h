//
//	VidyoRemoteWindowShare_Objc.h
//	VidyoClient
//
//	This file is auto generated, do not edit this file
//	Copyright (c) 2016 Vidyo, Inc. All rights reserved.
//

#import "VidyoLocalRenderer_Objc.h"
@interface RemoteWindowShare : NSObject
{
	void* objPtr;
	@public
	NSMutableString* id;
	NSMutableString* name;
}

	-(void) dealloc;
	-(long) AddToLocalRenderer:(LocalRenderer*)renderer;
	-(NSString*) GetId;
	-(NSString*) GetName;
	-(BOOL) RemoveFromLocalRenderer:(LocalRenderer*)renderer;
	-(BOOL) SetPositionInLocalRenderer:(LocalRenderer*)localRenderer X:(int)x Y:(int)y Width:(unsigned int)width Height:(unsigned int)height FrameInterval:(long)frameInterval;
	-(id) initWithObject:(void*)rPtr;
	-(void*)GetObjectPtr;
@end