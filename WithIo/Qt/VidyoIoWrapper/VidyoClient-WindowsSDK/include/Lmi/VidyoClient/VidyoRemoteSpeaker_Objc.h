//
//	VidyoRemoteSpeaker_Objc.h
//	VidyoClient
//
//	This file is auto generated, do not edit this file
//	Copyright (c) 2016 Vidyo, Inc. All rights reserved.
//

@interface RemoteSpeaker : NSObject
{
	void* objPtr;
}

	-(void) dealloc;
	-(NSString*) GetId;
	-(NSString*) GetName;
	-(id) initWithObject:(void*)rPtr;
	-(void*)GetObjectPtr;
@end
