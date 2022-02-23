//
//  VeView.h
//  VisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

__attribute__((visibility("default"))) @interface VeView : UIView

- (int)setData:(UInt8 *)data width:(int)width height:(int)height;

@end

NS_ASSUME_NONNULL_END
