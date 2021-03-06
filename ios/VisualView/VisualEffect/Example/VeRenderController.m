//
//  VeRenderController.m
//  CGPaintC
//
//  Created by Jason on 2021/6/11.
//

#import "VeRenderController.h"
#import "VeView.h"

@interface VeRenderController ()

@end

@implementation VeRenderController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSString *path = [[NSBundle mainBundle] pathForResource:@"rgba8_1125x1125" ofType:@"rgba"];
    NSData *rgba = [NSData dataWithContentsOfFile:path];
    
    VeView *veView = [[VeView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:veView];
    [veView setData:(UInt8 *)rgba.bytes width:1125 height:1125];
}

@end
