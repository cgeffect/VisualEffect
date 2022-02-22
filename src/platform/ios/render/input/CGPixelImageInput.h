//
//  CGPixelImageInput.h
//  CGPixel
//
//  Created by CGPixel on 2021/5/13.
//  Copyright © 2021 CGPixel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CGPixelOutput.h"
#import "CGPixelFramebuffer.h"

NS_ASSUME_NONNULL_BEGIN

@interface CGPixelImageInput : CGPixelOutput

- (instancetype)initWithImage:(UIImage *)newImageSource;

@end

NS_ASSUME_NONNULL_END
