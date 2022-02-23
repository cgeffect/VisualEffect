//
//  VeContext.m
//  libVisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import "VeContext.h"
#import "Vgx.h"

@interface VeContext ()
{
    
}
@end

@implementation VeContext

- (int)glDrawData:(UInt8 *)data width:(int)width height:(int)height {

    auto dataInput = new vgx::VgxDataInput();
    auto filter = new vgx::VgxFilter();
    auto output = new vgx::VgxTextureOutput();

    dataInput->setInputData(data, width, height);
    dataInput->addTarget(filter);
    filter->addTarget(output);
    dataInput->requestRender();
    int texId = output->getTexId();
    return texId;
}
@end
