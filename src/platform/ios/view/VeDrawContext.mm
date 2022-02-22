//
//  VeDrawContext.m
//  libVisualEffect
//
//  Created by Jason on 2022/2/22.
//

#import "VeDrawContext.h"
#include "VgxFramebuffer.h"
#include "VgxFilter.h"
#include "VgxDataInput.h"
#include "VgxTextureOutput.h"
#include "VgxDataInput.h"

@implementation VeDrawContext

- (int)glDrawData:(UInt8 *)data width:(int)width height:(int)height {

    auto _dataInput = new vgx::VgxDataInput();
    auto _filter = new vgx::VgxFilter();
    auto _output = new vgx::VgxTextureOutput();

    _dataInput->setInputData(data, width, height);
    _dataInput->addTarget(_filter);
    _filter->addTarget(_output);
    _dataInput->requestRender();
    int texId = _output->getTexId();
    return texId;
}
@end
