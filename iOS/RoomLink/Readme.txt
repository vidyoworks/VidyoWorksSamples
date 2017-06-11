Details on how to build properly for 64bit:

To build the application properly for 64bit operation, the user must make the following changes in the Xcode settings:

1. Remove linker option –all_load option from your project file. --> This can 
be found under "Build Settings" under "Linking" and under the exact title of 
"Other Linker Flags." By default, it has this set but you need to just remove 
it. 
2. Set valid architecture to arm64, armv7, armv7s 
3. Set architectures to $(ARCHS_STANDARD_INCLUDING_64_BIT) 

Details on how to orient video properly on iOS7 and iOS8:

Users should direct their attention to the following items for modifications made to resolve iOS8 orientation issues as well as allow the application to work properly in iOS7:

1. Do not lock the top view controller (any other locking in the project level are possible). ? Look in LoginWindow.m file as well which has –(BOOL) shoudlAutorotate which returns YES.  You should be happy about this because we no longer require this and I know at one time this was going to be the biggest challenge.
2. Add the following listeners:
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
3. Add the following methods:
// Notification handler for device orientation changes
- (void)orientationDidChange:(NSNotification *)notification
{
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
    
    // cache orientation if needed
    if (willSetOrientation )
    {
        // new orientation becomes known, set as last known orientation
        lastKnownOrientation = (unsigned)(event.orientation);
        if (clientStateManager.clientConferenceState == GUI_CLIENT_CONFERENCE_STATE_JOINED)
        {
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
    (void)VidyoClientSendRequest(VIDYO_CLIENT_REQUEST_SET_LAYOUT_RECT, &videoRect, sizeof(videoRect));

    VidyoClientInEventResize event;
    event.height = videoRect.height;
    event.width = videoRect.width;
    event.x = videoRect.xPos;
    event.y = videoRect.yPos;
    (void)VidyoClientSendEvent(VIDYO_CLIENT_IN_EVENT_RESIZE, &event, sizeof(event));
    
}
