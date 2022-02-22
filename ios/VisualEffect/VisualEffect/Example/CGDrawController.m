//
//  VgxController.m
//  CGPaintC
//
//  Created by Jason on 2021/6/11.
//

#import "CGDrawController.h"
#import "CGPixelViewOutput.h"
#import "CGDrawAgent.h"

@interface CGDrawController ()<CGDrawDelegate>
{
    NSData *rgba;
}
@property(nonatomic, strong)CGPixelViewOutput *glView;
@property(nonatomic, strong)CGDrawAgent *agent;
@end

@implementation CGDrawController

- (void)viewDidLoad {
    [super viewDidLoad];
    _glView = [[CGPixelViewOutput alloc] initWithFrame:CGRectMake(0, 0, UIScreen.mainScreen.bounds.size.width, UIScreen.mainScreen.bounds.size.width)];
    _glView.center = self.view.center;
    [self.view addSubview:_glView];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"rgba8_1125x1125" ofType:@"rgba"];
    rgba = [NSData dataWithContentsOfFile:path];
    
    runSyncOnSerialQueue(^{
        [[CGPixelContext sharedRenderContext] useAsCurrentContext];
        self->_agent = [[CGDrawAgent alloc] init];
        self->_agent.delegate = self;
        [self->_agent setInputData:(UInt8 *)self->rgba.bytes size:CGSizeMake(1125, 1125)];
    });

}

- (void)glRequestRender:(int)textureId size:(CGSize)size {
    CGPixelFramebuffer *framebuffer = [[CGPixelFramebuffer alloc] initWithSize:size texture:textureId];
    [_glView setInputFramebuffer:framebuffer];
    CMSampleTimingInfo info = {0};
    [_glView newFrameReadyAtTime:kCMTimeZero timimgInfo:info];
    
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
}
@end
