//
//  VgxDemo.m
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#import "CGDrawAgent.h"
#import "VeRenderManager.h"

@interface CGDrawAgent ()

@end

@implementation CGDrawAgent

- (instancetype)init {
    self = [super init];
    if (self) {

    }
    return self;
}

- (void)setInputData:(UInt8 *)data size:(CGSize)size {
    int texId = setData(data, size.width, size.height);
    if (self.delegate && [self.delegate respondsToSelector:@selector(glRequestRender:size:)]) {
        [self.delegate glRequestRender:texId size:size];
    }
}

@end
