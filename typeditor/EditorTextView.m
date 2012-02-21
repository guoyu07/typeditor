//
//  EditorTextView.m
//  typeditor
//
//  Created by  on 12-2-21.
//  Copyright (c) 2012年 MagnetJoy. All rights reserved.
//

#import "EditorTextView.h"

@implementation EditorTextView

@synthesize insertionPointWidth;

- (id) init {
    self = [super init];
    
    if (self) {
        insertionPointWidth = 2.0f;
    }
    
    return self;
}

- (void)drawInsertionPointInRect:(NSRect)rect color:(NSColor *)color turnedOn:(BOOL)flag
{
    rect.size.width = insertionPointWidth;
    
    if (flag) {
        [color set];
        [NSBezierPath fillRect:rect];
    } else {
        [self setNeedsDisplayInRect:[self visibleRect] avoidAdditionalLayout:NO];
    }
}

- (void)_drawInsertionPointInRect:(NSRect)rect color:(NSColor *)color
{
    [color set];
    rect.size.width = insertionPointWidth;
    [NSBezierPath fillRect:rect];
}

- (void)insertText:(id)insertString
{
    [super insertText:insertString];
    if (nil != [self delegate]) {
        [(id<EditorTextViewDelegate>)[self delegate] insertText:insertString];
    }
}

@end
