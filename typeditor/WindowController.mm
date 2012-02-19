//
//  WindowController.m
//  typeditor
//
//  Created by 宁 祁 on 12-2-19.
//  Copyright (c) 2012年 MagnetJoy. All rights reserved.
//

#import "WindowController.h"

@implementation WindowController

- (id)initWithApp:(NSObject *)app
{
    self = [super initWithWindowNibName:@"WindowController"];
    if (self) {
        mainWindow = (INAppStoreWindow *)[self window];
        
        // Initialization code here.
        [mainWindow setTrafficLightButtonsLeftMargin:7.0f];
        [mainWindow setFullScreenButtonRightMargin:7.0f];
        [mainWindow setHideTitleBarInFullScreen:NO];
        [mainWindow setCenterFullScreenButton:YES];
        [mainWindow setTitleBarHeight:40.0f];
        [mainWindow setShowsBaselineSeparator:NO];
        
        // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
        editor = [[ScintillaViewController alloc] initWithWindow:mainWindow];
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
}

@end
