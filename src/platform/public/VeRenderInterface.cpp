//
//  VeRenderInterface.cpp
//  libVisualEffect
//
//  Created by Jason on 2022/2/20.
//

#include "VeRenderInterface.h"

#include "CGDrawFramebuffer.h"
#include "CGDrawFilter.h"
#include "VgxDataInput.h"
#include "CGDrawTextureOutput.h"
#include "VgxDataInput.h"

using namespace vgx;

int setData1(unsigned const char *data, int width, int height) {

    auto _dataInput = new VgxDataInput();
    auto _filter = new CGDrawFilter();
    auto _output = new CGDrawTextureOutput();

    _dataInput->setInputData(data, width, height);
    _dataInput->addTarget(_filter);
    _filter->addTarget(_output);
    _dataInput->requestRender();
    int texId = _output->getTexId();
    return texId;
}
