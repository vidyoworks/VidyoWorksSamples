/*
 *  LoginWindow.h
 *  VidyoClientSample_iOS
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>
#import <MessageUI/MFMailComposeViewController.h>
#import "SSZipArchive/SSZipArchive.h"

@interface LoginWindow : UIViewController <NSXMLParserDelegate, UITextFieldDelegate, MFMailComposeViewControllerDelegate>
{

	IBOutlet UILabel *myStatus;
    IBOutlet UITextField *vidyoPortal;
    IBOutlet UITextField *usernameField;
    IBOutlet UITextField *passwordField;
    IBOutlet UIButton *loginButton;
    IBOutlet UIButton *joinMyRoomButton;
    
    //IBOutlet UIButton *buttontestURI;
    
    IBOutlet UITextField *roomPinField;
    IBOutlet UITextField *guestnameField;
    IBOutlet UITextField *roomKeyField;
    IBOutlet UITextField *guestPortal;
    IBOutlet UIButton *guestLoginButton;
    

    
	NSMutableData *webData;
	NSMutableString *soapResults;
	NSXMLParser *xmlParser;
	NSMutableString *vidyoEntityID;
	BOOL entityIDResult;
	BOOL memberStatusResult;
	BOOL joinStatus;
    BOOL isSigningIn;
    UIAlertView *signingInAlert;
}

@property(nonatomic, retain) IBOutlet UIButton *loginButton;
@property(nonatomic, retain) IBOutlet UIButton *joinMyRoomButton;
@property(nonatomic, retain) UITextField *vidyoPortal;
@property(nonatomic, retain) UITextField *usernameField;
@property(nonatomic, retain) UITextField *passwordField;


@property (retain, nonatomic) IBOutlet UIButton *guestLoginButton;
@property(nonatomic, retain) UITextField *guestPortal;
@property(nonatomic, retain) UITextField *guestnameField;
@property(nonatomic, retain) UITextField *roomKeyField;
@property(nonatomic, retain) UITextField *roomPinField;

@property(nonatomic, retain) NSMutableData *webData;
@property(nonatomic, retain) NSMutableString *soapResults;
@property(nonatomic, retain) NSMutableString *vidyoMemberStatus;
@property(nonatomic, retain) NSString *vidyoClientStatus;
@property(nonatomic, retain) NSMutableString *vidyoEntityID;
@property(nonatomic, retain) NSXMLParser *xmlParser;
@property(nonatomic, retain) UIAlertView *signingInAlert;
@property                    BOOL isSigningIn;
@property                    BOOL isInCall;

- (IBAction)buttonPressed:(id)sender;
- (IBAction)buttonGuestPressed:(id)sender;

-(void)setGuestCredentials;

- (IBAction)sendLogs:(UIButton *)sender;
@end
