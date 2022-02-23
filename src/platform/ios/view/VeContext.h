//
//  VeContext.h
//  VisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VeContext : NSObject

- (int)glDrawData:(UInt8 *)data width:(int)width height:(int)height;

@end

NS_ASSUME_NONNULL_END
