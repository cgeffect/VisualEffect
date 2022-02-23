//
//  VeView.m
//  VisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import "VeView.h"
#include "CGPixel.h"
#include "VeContext.h"

@interface VeView ()
{
    VeContext *ctx;
}
@property(nonatomic, strong)CGPixelViewOutput *glView;
@end

@implementation VeView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _glView = [[CGPixelViewOutput alloc] initWithFrame:self.bounds];
        _glView.center = self.center;
        [self addSubview:_glView];
        ctx = [[VeContext alloc] init];
    }
    return self;
}

- (int)setData:(UInt8 *)data width:(int)width height:(int)height {
    runSyncOnSerialQueue(^{
        [[CGPixelContext sharedRenderContext] useAsCurrentContext];
        int texId = [self->ctx glDrawData:data width:width height:height];
        CGPixelFramebuffer *framebuffer = [[CGPixelFramebuffer alloc] initWithSize:CGSizeMake(width, height) texture:texId];
        [self->_glView setInputFramebuffer:framebuffer];
        CMSampleTimingInfo info = {0};
        [self->_glView newFrameReadyAtTime:kCMTimeZero timimgInfo:info];
    });
    return 0;
}
@end
