//
//  TypEditor.h
//  typeditor
//
//  Created by 宁 祁 on 12-2-25.
//  Copyright (c) 2012年 MagnetJoy. All rights reserved.
//

#ifndef typeditor_TE_h
#define typeditor_TE_h

#import <Foundation/Foundation.h>

// 一次最多可以定义128种
#define TE_MAX_GLYPH_STYLES_NUM 128
#define TEGlyphStyleAttributeName @"EditorStyleAttributeName"
#define TE_MAX_GLYPH_RANGES_NUM 1024 * 1024 * 64

#define TEMakeString(str) \
    [[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding]

#define TEGetGlyphStyleNames(names) \
    const char *names = "none boolean character number string conditional constant define delimiter float function " \
    "indentifier keyword label macro special_char special_comment match operator class statement structure " \
    "tag title todo typedef type comment"

@interface TEGlyphStyle : NSObject {
@public
    
    // font type
    NSNumber *type;
    
    // font name
    NSFont *font;
    
    // foreground color
    NSColor *color;
    
    // backgourn color
    NSColor *backgroundColor;
    
    // attributes
    NSDictionary *attributes;
}
@end

// make glyph style
NS_INLINE TEGlyphStyle *TEMakeGlyphStyle(NSUInteger _type, NSFont *_font, NSColor *_color, NSColor *_backgroundColor) {
    TEGlyphStyle *style = [[TEGlyphStyle alloc] init];
    
    style->type = [NSNumber numberWithInteger:_type];
    style->font = _font;
    style->color = _color;
    style->backgroundColor = _backgroundColor;
    style->attributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                         style->type, TEGlyphStyleAttributeName, 
                         style->font, NSFontAttributeName,
                         style->color, NSForegroundColorAttributeName,
                         style->backgroundColor, NSBackgroundColorAttributeName, nil];
    
    return style;
}

// 定义glyph range的结构体
typedef struct _TEGlyphRange {
    
    // 起始位置
    NSUInteger location;
    
    // 长度
    NSUInteger length;
    
    // 样式类型
    NSUInteger styleType;
    
} TEGlyphRange;

// make glyph range
NS_INLINE TEGlyphRange TEMakeGlyphRange(NSUInteger _location, NSUInteger _length, NSUInteger _styleType) {
    TEGlyphRange r;
    
    r.location = _location;
    r.length = _length;
    r.styleType = _styleType;
    
    return r;
}

// make font for text view
NS_INLINE NSFont *TEMakeTextViewFont(NSFont *defaultFont, NSString *fontFamily, CGFloat fontSize, NSInteger bold, NSInteger italic) {
    if (!defaultFont) {
        defaultFont = [NSFont fontWithName:@"Helvetica" size:12.0f];
    }
    
    NSFontTraitMask mask = [[defaultFont fontDescriptor] symbolicTraits];
    
    if (bold != NSNotFound) {
        mask |= bold ? NSBoldFontMask : NSUnboldFontMask;
    }
    
    if (italic != NSNotFound) {
        mask |= italic ? NSItalicFontMask : NSUnitalicFontMask;
    }
    
    return [[NSFontManager sharedFontManager] fontWithFamily:fontFamily ? fontFamily : [defaultFont familyName] 
                                                      traits:mask 
                                                      weight:0 
                                                        size:NSNotFound != fontSize ? fontSize : [defaultFont pointSize]];
}

// make color
NS_INLINE NSColor *TEMakeRGBColor(NSString *htmlString) {
    NSError *error = nil;
    int length = [htmlString length];
    NSRegularExpression *regex = [NSRegularExpression         
                                  regularExpressionWithPattern:@"^#[0-9a-f]{3,6}$"
                                  options:NSRegularExpressionCaseInsensitive
                                  error:&error];
    
    // not matches return black color for default
    if (1 != [regex numberOfMatchesInString:htmlString options:0 range:NSMakeRange(0, length)]
        || (length != 4 && length != 7)) {
        return [NSColor blackColor];
    }
    
    // sub color
    if (4 == [htmlString length]) {
        htmlString = [[NSString alloc] initWithFormat:@"%@%@", htmlString, [htmlString substringFromIndex:1]];
    }
    
    unsigned int r, g, b;
    [[NSScanner scannerWithString:[htmlString substringWithRange:NSMakeRange(1, 2)]] scanHexInt:&r];
    [[NSScanner scannerWithString:[htmlString substringWithRange:NSMakeRange(3, 2)]] scanHexInt:&g];
    [[NSScanner scannerWithString:[htmlString substringWithRange:NSMakeRange(5, 2)]] scanHexInt:&b];
    
    return [NSColor colorWithCalibratedRed:((float) r / 255.0f) 
                                     green:((float) g / 255.0f) blue:((float) b / 255.0f) alpha:1.0f];
}

#endif