/*
 *  LoginWindow.m
 *  VidyoClientSample_iOS
 *
 *  Created by Chetan Gandhi on 08/19/11.
 *  Copyright 2011 Vidyo Inc. All rights reserved.
 *
 */

#import "LoginWindow.h"
#import "VidyoClientConstants.h"
#import "VidyoClientMessages.h"
#import "VidyoClient.h"
#import "NSString+Base64.h"
#import "VidyoClientSample.h"

@implementation LoginWindow


@synthesize vidyoPortal, usernameField, passwordField;
@synthesize loginButton, joinMyRoomButton;

@synthesize guestPortal,roomKeyField,guestnameField,roomPinField;
@synthesize guestLoginButton;

@synthesize webData, soapResults, xmlParser;
@synthesize vidyoEntityID, vidyoMemberStatus, vidyoClientStatus;
@synthesize signingInAlert, isSigningIn;

- (void) setCredentials {
	[vidyoPortal setText:@"http://<TenantName>.sandboxga.vidyo.com"];
	[usernameField setText:@"username"];
	[passwordField setText:@"password"];
    
}

-(void)setGuestCredentials {
    [guestPortal setText:@"http://<TenantName>.sandboxga.vidyo.com"];
    [guestnameField setText:@"GuestName"];
    [roomKeyField setText:@"RoomKeyXXXXXXXX"];
    [roomPinField setText:@""];
}

-(void) viewDidLoad
{
    [super viewDidLoad];
    [self setCredentials];
    [self setGuestCredentials];
}

- (IBAction)buttonGuestPressed:(id)sender {
    
    entityIDResult = FALSE;
	memberStatusResult = FALSE;
	joinStatus = FALSE;
	vidyoMemberStatus = nil;
    
    if (!([[guestPortal text] hasPrefix:@"http://"] || [[guestPortal text] hasPrefix:@"https://"]))
    {
        [guestPortal setText:[NSString stringWithFormat:@"http://%@", [guestPortal text]]];
    }
    
    
	if ([sender isEqual:guestLoginButton])
	{
        
		// Initaite the local sign in process
		VidyoClientInEventRoomLink event = {0};
		NSString *guestVPortal = guestPortal.text;
		NSString *guestVRoomKey = roomKeyField.text;
		NSString *guestVName = guestnameField.text;
        NSString *guestVRoomPin =roomPinField.text;
        
		strlcpy(event.portalUri, [guestVPortal UTF8String], sizeof(event.portalUri));
		strlcpy(event.roomKey, [guestVRoomKey UTF8String], sizeof(event.roomKey));
		strlcpy(event.displayName, [guestVName UTF8String], sizeof(event.displayName));
        strlcpy(event.pin, [guestVRoomPin UTF8String], sizeof(event.pin));
        
        // hide keyboard
        [self.view endEditing:TRUE];
        
        
        // Removed this block of code on 3/18 of 3.3.4.0004 version of library, since it was causing issues on guest login.
        /* Create wait alert
        signingInAlert = [[[UIAlertView alloc] initWithTitle:@"Signing in\nPlease Wait..." message:nil delegate:self cancelButtonTitle:nil otherButtonTitles: nil] autorelease];
        [signingInAlert show];
        
        UIActivityIndicatorView *indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        
        // Adjust the indicator so it is up a few pixels from the bottom of the alert
        indicator.center = CGPointMake(signingInAlert.bounds.size.width / 2, signingInAlert.bounds.size.height - 50);
        [indicator startAnimating];
        [signingInAlert addSubview:indicator];
        [indicator release]; */
        
		// send login-event as guest to VidyoClient
		if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_ROOM_LINK, &event, sizeof(VidyoClientInEventRoomLink)) == false)
        {
            [signingInAlert dismissWithClickedButtonIndex:0 animated:YES];
            
 			NSString *alertMsg = [NSString stringWithFormat:@"Failed to sign in"];
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
            [alert show];
            [alert release];
            
        }
        else
        {
            isSigningIn = TRUE;
        }
        
 	}
    
}

- (IBAction)singOutPressed:(id)sender {
    // hide keyboard
    [self.view endEditing:TRUE];
    
    if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_SIGNOFF, NULL, 0) == false)
    {
        [signingInAlert dismissWithClickedButtonIndex:0 animated:YES];
        
        NSString *alertMsg = [NSString stringWithFormat:@"Failed to sign out."];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
        [alert show];
        [alert release];
    }
    else
    {
        isSigningIn = FALSE;
    }
}

- (IBAction)buttonPressed:(id)sender {
	
	entityIDResult = FALSE;
	memberStatusResult = FALSE;
	joinStatus = FALSE;
	vidyoMemberStatus = nil;

    /* If portal URL does not start with schema than put it there explicetly */
	if(!([[vidyoPortal text] hasPrefix:@"http://"] || [[vidyoPortal text] hasPrefix:@"https://"]))
    {
        [vidyoPortal setText:[NSString stringWithFormat:@"http://%@", [vidyoPortal text]]];
    }
    
	NSString *userPortal = [vidyoPortal text]; 

	if ([sender isEqual:loginButton])
	{

		// Initaite the local sign in process
		VidyoClientInEventLogIn event = {0};
		NSString *userVPortal = vidyoPortal.text;    
		NSString *userVName = usernameField.text;    
		NSString *userVPass = passwordField.text;
 
		strlcpy(event.portalUri, [userVPortal UTF8String], sizeof(event.portalUri));
		strlcpy(event.userName, [userVName UTF8String], sizeof(event.userName));
		strlcpy(event.userPass, [userVPass UTF8String], sizeof(event.userPass));

        // hide keyboard
        [self.view endEditing:TRUE];
            
        /* Create wait alert */
        signingInAlert = [[[UIAlertView alloc] initWithTitle:@"Signing in\nPlease Wait..." message:nil delegate:self cancelButtonTitle:nil otherButtonTitles: nil] autorelease];
        [signingInAlert show];
        
        UIActivityIndicatorView *indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        
        // Adjust the indicator so it is up a few pixels from the bottom of the alert
        indicator.center = CGPointMake(signingInAlert.bounds.size.width / 2, signingInAlert.bounds.size.height - 50);
        [indicator startAnimating];
        [signingInAlert addSubview:indicator];
        [indicator release];

		// send login-event to VidyoClient
		if (VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_LOGIN, &event, sizeof(VidyoClientInEventLogIn)) == false)
        {
            [signingInAlert dismissWithClickedButtonIndex:0 animated:YES];
            
 			NSString *alertMsg = [NSString stringWithFormat:@"Failed to sign in"];															  
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
            [alert show];
            [alert release];
            
        }
        else 
        {
            isSigningIn = TRUE;
        }
        
 	} 
	else if ([sender isEqual:joinMyRoomButton])
	{
		
		/* The joinConference is broken into 2 steps
		 * Step1: get the entityID from VidyoPortal using WS User::myAccount() API
		 * Step2: if entityID is successfully retrieved and the entity is 'online', do WS User::joinConference
		 */
		vidyoEntityID = nil;
		NSString *urlString = [NSString stringWithFormat:@"%@/services/v1_1/VidyoPortalUserService", userPortal];
		NSURL *url = [NSURL URLWithString:urlString];
		NSMutableURLRequest *theRequest = [NSMutableURLRequest requestWithURL:url];
		
		// Get the EntityId from VidyoPortal using WS User::myAccount
		NSString *soapMessage = [NSString stringWithFormat:
								 @"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
								 "<env:Envelope xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ns1=\"http://portal.vidyo.com/user/v1_1\">"
								 "<env:Body>"
								 "<ns1:MyAccountRequest/>"
								 "</env:Body>"
								 "</env:Envelope>"];
			
		// NSLog(@"%@", soapMessage);
		
		NSString *msgLength = [NSString stringWithFormat:@"%lu",(unsigned long)[soapMessage length]];
		[theRequest addValue: @"application/soap+xml; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
		[theRequest addValue: @"myAccount" forHTTPHeaderField:@"SOAPAction"];
		[theRequest addValue: msgLength forHTTPHeaderField:@"Content-Length"];

		NSString *base64 = [[NSString stringWithFormat:@"%@:%@", usernameField.text, passwordField.text] base64];
        NSString *auth = [NSString stringWithFormat:@"Basic %@", base64];
		[theRequest addValue: auth forHTTPHeaderField:@"Authorization"];
        
		[theRequest setHTTPMethod:@"POST"];
		[theRequest setHTTPBody: [soapMessage dataUsingEncoding:NSUTF8StringEncoding]];

		NSURLConnection *theConnection = [[NSURLConnection alloc] initWithRequest:theRequest delegate:self];
		if( theConnection )
		{
			webData = [[NSMutableData data] retain];
		}
		else
		{
			NSLog(@"theConnection is NULL");
		}
		
		joinStatus = TRUE;
		NSLog(@"*********************SENT SOAP Request myAccount() ******************************");
	}
}

-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	[webData setLength: 0];
}
-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	[webData appendData:data];
}
-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
	NSLog(@"ERROR with theConenction");
	[connection release];
	[webData release];
}
-(void)connectionDidFinishLoading:(NSURLConnection *)connection
{
	NSLog(@"DONE. Received Bytes: %lu", (unsigned long)[webData length]);
	NSString *theXML = [[NSString alloc] initWithBytes: [webData mutableBytes] length:[webData length] encoding:NSUTF8StringEncoding];
	NSLog(@"%@", theXML);

	[theXML release];
	
	if(xmlParser)
	{
		[xmlParser release];
	}
	
	xmlParser = [[NSXMLParser alloc] initWithData: webData];
	[xmlParser setDelegate: self];
	[xmlParser setShouldResolveExternalEntities: YES];
	[xmlParser parse];
	
	[connection release];
	[webData release];
	
	// NSLog(@"entityID = %@", vidyoEntityID);
	/* Step2: Send the joinConference if the status is online */
	if ( joinStatus )
	{
		NSString *urlString = [NSString stringWithFormat:@"%@/services/v1_1/VidyoPortalUserService", [vidyoPortal text]];
		NSURL *url = [NSURL URLWithString:urlString];
		NSMutableURLRequest *theJoinRequest = [NSMutableURLRequest requestWithURL:url];
		
		// Get the EntityId from VidyoPortal using WS User::myAccount
		
		NSString *soapJoinMessage = [NSString stringWithFormat:
								 @"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
								 "<env:Envelope xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:ns1=\"http://portal.vidyo.com/user/v1_1\">"
								 "<env:Body>"
								 "<ns1:JoinConferenceRequest>"
								 "<ns1:conferenceID>%@</ns1:conferenceID>"
								 "</ns1:JoinConferenceRequest>"
								 "</env:Body>"
								 "</env:Envelope>", vidyoEntityID];
		
		// NSLog(@"%@", soapJoinMessage);
		
		NSString *msgLength = [NSString stringWithFormat:@"%lu", (unsigned long)[soapJoinMessage length]];
		
		[theJoinRequest addValue: @"application/soap+xml; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
		[theJoinRequest addValue: @"joinConference" forHTTPHeaderField:@"SOAPAction"];
		[theJoinRequest addValue: msgLength forHTTPHeaderField:@"Content-Length"];
		
		NSString *base64 = [[NSString stringWithFormat:@"%@:%@", usernameField.text, passwordField.text] base64];
        NSString *auth = [NSString stringWithFormat:@"Basic %@", base64];
		[theJoinRequest addValue: auth forHTTPHeaderField:@"Authorization"];
		[theJoinRequest setHTTPMethod:@"POST"];
		[theJoinRequest setHTTPBody: [soapJoinMessage dataUsingEncoding:NSUTF8StringEncoding]];
		
		NSURLConnection *theJoinConnection = [[NSURLConnection alloc] initWithRequest:theJoinRequest delegate:self];
		if( theJoinConnection )
		{
			webData = [[NSMutableData data] retain];
		}
		else
		{
			NSLog(@"theConnection is NULL");
		}
		
		joinStatus = FALSE;
		NSLog(@"*********************SENT SOAP Request joinConference() ******************************/n");
	}
	
}

- (NSString*) getElementFromElementName: (NSString *) elementName
{
	NSArray *split = [elementName componentsSeparatedByString:@":"];
	if (!split || ([split count] != 2))
	{
		NSLog(@"Not a valid elementName '%@'", elementName);
		return NULL;
	}
	NSString *element = [split objectAtIndex:1];
	if (!element)
	{
		NSLog(@"Element is null");
		return NULL;
	}
	return [NSString stringWithString:element];
}

-(void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *) namespaceURI qualifiedName:(NSString *)qName
   attributes: (NSDictionary *)attributeDict
{
	NSString *element = [self getElementFromElementName:elementName];
	if (!element)
	{
		return;
	}
	/* separate namespace from element name */
	if( [element isEqualToString:@"entityID"])
	{
		if(!vidyoEntityID)
		{
			vidyoEntityID = [[NSMutableString alloc] initWithCapacity:256];
		}
		entityIDResult = TRUE;
	}
	else if( [element isEqualToString:@"MemberStatus"])
	{
		if(!vidyoMemberStatus)
		{
			vidyoMemberStatus = [[NSMutableString alloc] initWithCapacity:256];
		}
		memberStatusResult = TRUE;

	}
}
-(void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
	if( entityIDResult )
	{
		[vidyoEntityID appendString: string];
		entityIDResult = FALSE;
		// NSLog(@"entityID = %@", vidyoEntityID);
	} 
	else if (memberStatusResult)
	{
		[vidyoMemberStatus appendString: string];
		memberStatusResult = FALSE;

		// NSLog(@"Endpoint is %@", vidyoMemberStatus);
		if(![vidyoMemberStatus isEqualToString:@"Online"])
		{
			joinStatus = FALSE;
			
			// Show the alert with the XML that was received
			dispatch_async(dispatch_get_main_queue(), ^{
				NSString *alertMsg = [NSString stringWithFormat:@"User NOT online. Make sure User is Logged In"];
				UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertMsg message:@"" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
				[alert show];

				[alert release];
			});
		}
	}
	
}
-(void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
	NSString *element = [self getElementFromElementName:elementName];
	if (!element)
	{
		return;
	}

	if( [element isEqualToString:@"MyAccountResponse"])
	{
		entityIDResult = FALSE;
	}
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    [self setCredentials];
    [self setGuestCredentials];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	[xmlParser release];
    [super dealloc];
}


- (BOOL) textFieldShouldReturn:(UITextField *)textField
{
	if (textField == [self passwordField])
	{
		[textField resignFirstResponder];
		[self buttonPressed: loginButton];
	}
	else if (textField == [self usernameField])
	{
		[[self passwordField] becomeFirstResponder];
	}
	else if (textField == [self vidyoPortal])
	{
		[[self usernameField] becomeFirstResponder];
	}
    else if (textField ==[self guestPortal])
    {
        [[self roomKeyField] becomeFirstResponder];
    }
    else if (textField == [self roomKeyField])
    {
        [[self guestnameField] becomeFirstResponder];
        
    }
    else if (textField == [self guestnameField])
    {
        [[self roomPinField] becomeFirstResponder];
        
    }
    else if (textField ==[self roomPinField])
    {
        
        [textField resignFirstResponder];
        [self buttonGuestPressed: guestLoginButton];
        
    }
    return YES;
}


- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	[[self view] endEditing:YES];
}

-(BOOL) shouldAutorotate
{
//    NSLog(@"shouldAutorotate invoked by %@", self.class);
//    Boolean shouldRotate = YES;
//    if (floor(NSFoundationVersionNumber) > NSFoundationVersionNumber_iOS_7_1)
//    {
//        if (self.isInCall)
//            shouldRotate = NO;
//    }
//    
//    NSLog(@"shouldRotate is returning %d", shouldRotate);
//    
//    return shouldRotate;
    return YES;
}

/*-(NSUInteger) supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}*/

- (void)sendLogs:(UIButton *)sender {
    if (![MFMailComposeViewController canSendMail]) {
        [[[UIAlertView alloc] initWithTitle:nil
                                    message: @"Send Logs"
                                   delegate:nil
                          cancelButtonTitle:@"OK"
                          otherButtonTitles:nil] show];
        return;
    }
    MFMailComposeViewController *mailComposer = [[MFMailComposeViewController alloc] init];
    NSData *zipFileData = [self zipLogs];

    mailComposer.mailComposeDelegate = self;

    [mailComposer setSubject:@"Sample Logs"];
    NSString *infoDev = @"TEST INFO";
    [mailComposer setMessageBody:infoDev isHTML:NO];
    [mailComposer addAttachmentData:zipFileData
                           mimeType:@"application/zip"
                           fileName:@"VidyoMobileLogs.zip"];

    [self presentViewController:mailComposer animated:YES completion:nil];
}

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (NSData *) zipLogs
{
    NSString *logsDir = [self logsDirectory];
    NSError *error;
    NSArray *files = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:logsDir error:&error];
    NSPredicate *textFilePredicate = [NSPredicate predicateWithFormat:@"self ENDSWITH '.txt' OR self ENDSWITH '.log'"];
    files = [files filteredArrayUsingPredicate:textFilePredicate];
    
    NSString *logZipPath = [logsDir stringByAppendingPathComponent:@"VidyoMobileLogs.zip"];
    if ([[NSFileManager defaultManager] fileExistsAtPath:logZipPath]) {
        [[NSFileManager defaultManager] removeItemAtPath:logZipPath error:nil];
    }
    
    NSMutableArray *inputFiles = [NSMutableArray array];
    for (NSString *file in files) {
        [inputFiles addObject:[logsDir stringByAppendingPathComponent:file]];
    }
    
    [SSZipArchive createZipFileAtPath:logZipPath withFilesAtPaths:inputFiles];
    NSData *zipData = [NSData dataWithContentsOfFile:logZipPath];
    [[NSFileManager defaultManager] removeItemAtPath:logZipPath error:nil];
    return zipData;
}

- (NSString *)logsDirectory
{
    NSString *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory /*NSCachesDirectory*/, NSUserDomainMask, YES)[0];
    BOOL isDir;
    BOOL exists = [[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:&isDir];
    if (!exists || !isDir) {
        NSError *error = nil;
        [[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:&error];
        if (error) {
            //DDLogError(@"ERROR creating Logs dir: %@. Error: %@", path, error);
        }
    }
    return path;
}

@end
