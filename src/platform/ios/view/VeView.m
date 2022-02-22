//
//  VeView.m
//  libVisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import "VeView.h"
#include "CGPixel.h"
#include "VeDrawContext.h"

@interface VeView ()
@property(nonatomic, strong)CGPixelViewOutput *glView;
//@property(nonatomic, strong)CGDrawAgent *agent;

@end

@implementation VeView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _glView = [[CGPixelViewOutput alloc] initWithFrame:self.bounds];
        _glView.center = self.center;
        [self addSubview:_glView];
    }
    return self;
}

- (int)setData:(UInt8 *)data width:(int)width height:(int)height {
    runSyncOnSerialQueue(^{
        [[CGPixelContext sharedRenderContext] useAsCurrentContext];
        VeDrawContext *ctx = [[VeDrawContext alloc] init];
        int texId = [ctx glDrawData:data width:1125 height:1125];
        CGPixelFramebuffer *framebuffer = [[CGPixelFramebuffer alloc] initWithSize:CGSizeMake(1125, 1125) texture:texId];
        [self->_glView setInputFramebuffer:framebuffer];
        CMSampleTimingInfo info = {0};
        [self->_glView newFrameReadyAtTime:kCMTimeZero timimgInfo:info];
    });
    return 0;
}
@end
